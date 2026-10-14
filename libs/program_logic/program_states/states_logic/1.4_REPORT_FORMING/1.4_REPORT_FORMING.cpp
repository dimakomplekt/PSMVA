#include "1.4_REPORT_FORMING.h"

#include "xlsx_report_writer.h"

#include "../../../../engine/engine.h"
#include "../../../../program_gui/basic_elements/UI_elements/my_sdl_button/my_sdl_button.h"
#include "../../../../program_gui/basic_elements/UI_elements/my_sdl_panel/my_sdl_panel.h"
#include "../../../../program_gui/basic_elements/UI_elements/my_sdl_textbox/my_sdl_textbox.h"
#include "../../../../program_gui/basic_elements/global_palette/global_palette.h"
#include "../../../../program_gui/basic_elements/global_fonts/global_fonts.h"
#include "../../../app.h"
#include "../1.1_FILE_CHOOSE/1.1_FILE_CHOOSE.h"
#include "../1.2_MASKS_SETUP/1.2_MASKS_SETUP.h"
#include "../1.3_FLOW_PARAMETERS_CALCULATION/1.3_FLOW_PARAMETERS_CALCULATION.h"
#include "../../program_states.h"

#include <algorithm>
#include <array>
#include <cctype>
#include <filesystem>
#include <iostream>
#include <mutex>
#include <string>
#include <utility>

namespace
{
    enum class save_dialog_result
    {
        IDLE,
        WAITING,
        CANCELLED,
        SELECTED,
        FAILED
    };

    enum class report_status
    {
        CALCULATION_COMPLETE,
        CHOOSING_LOCATION,
        SAVED,
        FAILED
    };

    My_SDL_panel* report_background_panel = nullptr;
    std::array<My_SDL_panel*, 4> report_status_panels = {};
    std::array<My_SDL_button*, 4> report_buttons = {};
    std::array<My_SDL_textbox*, 4> report_status_textboxes = {};
    std::array<Uint64, 4> report_status_panel_hide_times = {};
    std::mutex save_dialog_mutex;
    save_dialog_result current_save_dialog_result = save_dialog_result::IDLE;
    std::string selected_report_path;
    std::string save_dialog_default_location;
    report_status current_report_status = report_status::CALCULATION_COMPLETE;
    int active_report_status_panel = -1;
    Uint64 report_enter_time = 0;
    bool automatic_save_dialog_started = false;

    constexpr int screen_margin = 50;
    constexpr int first_zone_width = static_cast<int>(MAIN_WINDOW_H_SIZE * 0.4);
    constexpr int second_zone_width = MAIN_WINDOW_H_SIZE - first_zone_width;
    constexpr int button_width = first_zone_width - 2 * screen_margin;
    constexpr int button_height = (MAIN_WINDOW_V_SIZE - 5 * screen_margin) / 4;
    constexpr int button_gap = screen_margin;
    constexpr int panel_width = second_zone_width - 2 * screen_margin;
    constexpr int panel_height = MAIN_WINDOW_V_SIZE - 2 * screen_margin;
    constexpr int panel_x = MAIN_WINDOW_H_SIZE - second_zone_width / 2;
    constexpr int panel_y = MAIN_WINDOW_V_SIZE / 2;
    constexpr Uint64 automatic_dialog_delay_ms = 1000;
    constexpr Uint64 report_panel_animation_ms = 600;
    constexpr int report_panel_offscreen_x = MAIN_WINDOW_H_SIZE + panel_width / 2;

    const SDL_DialogFileFilter report_file_filters[] = {
        {"Excel workbook", "xlsx"}
    };

    void save_dialog_callback(void*, const char* const* file_list, int)
    {
        std::lock_guard<std::mutex> lock(save_dialog_mutex);
        selected_report_path.clear();

        if (file_list == nullptr)
        {
            current_save_dialog_result = save_dialog_result::FAILED;
        }
        else if (file_list[0] == nullptr)
        {
            current_save_dialog_result = save_dialog_result::CANCELLED;
        }
        else
        {
            selected_report_path = file_list[0];
            current_save_dialog_result = save_dialog_result::SELECTED;
        }
    }

    std::size_t report_status_index(report_status status)
    {
        return static_cast<std::size_t>(status);
    }

    std::string report_status_text(report_status status)
    {
        if (status == report_status::CALCULATION_COMPLETE)
        {
            return str_by_dictionary(gd_calculation_complete);
        }
        if (status == report_status::CHOOSING_LOCATION)
        {
            return str_by_dictionary(gd_choose_report_location);
        }
        if (status == report_status::SAVED)
        {
            return str_by_dictionary(gd_report_saved);
        }

        return str_by_dictionary(gd_report_failed);
    }

    void show_report_status(report_status status)
    {
        current_report_status = status;
        const std::size_t next_panel_index = report_status_index(status);
        report_status_textboxes[next_panel_index]->set_content(report_status_text(status));

        if (active_report_status_panel == static_cast<int>(next_panel_index))
        {
            return;
        }

        if (active_report_status_panel >= 0)
        {
            const std::size_t old_panel_index =
                static_cast<std::size_t>(active_report_status_panel);

            report_status_panels[old_panel_index]->move_to_point(
                panel_x,
                4 * panel_y,
                EXPONENTIAL,
                report_panel_animation_ms
            );

            report_status_panel_hide_times[old_panel_index] =
                SDL_GetTicks() + report_panel_animation_ms;
        }

        My_SDL_panel* next_panel = report_status_panels[next_panel_index];

        if (report_status_panel_hide_times[next_panel_index] != 0)
        {
            next_panel->set_visible_flag(false);
            report_status_panel_hide_times[next_panel_index] = 0;
        }

        next_panel->set_render_point(report_panel_offscreen_x, panel_y);
        next_panel->set_visible_flag(true);
        next_panel->move_to_point(panel_x, panel_y, EXPONENTIAL, report_panel_animation_ms);
        active_report_status_panel = static_cast<int>(next_panel_index);
    }

    void reset_study_contexts()
    {
        opencv_global_free_and_nullptr();
        flow_parameters_calculation_reset_context();

        file_choose_info = {};
        file_data_choose_info = {};
        files_choose_status = {};
        files_metadata = {};
        masks_data = {};
    }

    void show_report_save_dialog()
    {
        show_report_status(report_status::CHOOSING_LOCATION);
        {
            std::lock_guard<std::mutex> lock(save_dialog_mutex);
            current_save_dialog_result = save_dialog_result::WAITING;
            selected_report_path.clear();
        }

        const char* base_path = SDL_GetBasePath();
        if (base_path == nullptr)
        {
            std::lock_guard<std::mutex> lock(save_dialog_mutex);
            current_save_dialog_result = save_dialog_result::FAILED;
            std::cerr << "Unable to get the application directory: " << SDL_GetError() << '\n';
            return;
        }

        save_dialog_default_location = base_path;
        if (!save_dialog_default_location.empty() &&
            save_dialog_default_location.back() != '\\' &&
            save_dialog_default_location.back() != '/')
        {
            save_dialog_default_location.push_back('\\');
        }
        save_dialog_default_location += "PSMVA_report.xlsx";

        SDL_ShowSaveFileDialog(
            save_dialog_callback,
            nullptr,
            this_app.window,
            report_file_filters,
            1,
            save_dialog_default_location.c_str()
        );
    }

    void report_buttons_create()
    {
        report_background_panel = new My_SDL_panel();
        report_background_panel->set_render_point(
            MAIN_WINDOW_H_SIZE / 2,
            MAIN_WINDOW_V_SIZE / 2
        );
        report_background_panel->set_size(MAIN_WINDOW_H_SIZE, MAIN_WINDOW_V_SIZE);
        report_background_panel->set_border_radius(0);

        for (My_SDL_button*& button : report_buttons)
        {
            button = new My_SDL_button();
        }

        for (std::size_t index = 0; index < report_status_panels.size(); ++index)
        {
            report_status_panels[index] = new My_SDL_panel();
            report_status_panels[index]->set_size(panel_width, panel_height);
            report_status_panels[index]->set_render_point(report_panel_offscreen_x, panel_y);

            report_status_textboxes[index] = new My_SDL_textbox();
            report_status_textboxes[index]->switch_textbox_type(HEADER_2);
            report_status_textboxes[index]->set_content(report_status_text(
                static_cast<report_status>(index)
            ));
            report_status_panels[index]->add_element(
                report_status_textboxes[index],
                panel_width / 2,
                panel_height / 2,
                1
            );
            report_status_panels[index]->set_visible_flag(false);
        }
    }

    void report_buttons_setup()
    {
        const std::array<Lang_string_type*, 4> labels = {
            &gd_exit,
            &gd_back,
            &gd_new_study,
            &gd_report_forming
        };
        for (std::size_t index = 0; index < report_buttons.size(); ++index)
        {
            My_SDL_button* button = report_buttons[index];
            button->switch_button_textbox_type(HEADER_2);
            button->get_button_content_textbox()->set_content(str_by_dictionary(*labels[index]));
            button->set_size(button_width, button_height);
            button->set_render_point(
                first_zone_width / 2,
                static_cast<int>(
                    screen_margin + button_height * 0.5 +
                    index * (button_height + button_gap)
                )
            );
        }

        report_buttons[0]->on_click = []()
        {
            reset_study_contexts();
            this_app.app_sm.request_state_change(PROGRAM_END_ID);
        };
        report_buttons[1]->on_click = []()
        {
            this_app.app_sm.request_state_change(FLOW_PARAMETERS_CALCULATION_ID);
        };
        report_buttons[2]->on_click = []()
        {
            reset_study_contexts();
            this_app.app_sm.request_state_change(MAIN_MENU_ID);
        };
        report_buttons[3]->on_click = show_report_save_dialog;

    }

    void report_buttons_free()
    {
        report_background_panel->delete_element();
        report_background_panel = nullptr;

        for (std::size_t index = 0; index < report_status_panels.size(); ++index)
        {
            report_status_panels[index]->delete_element();
            report_status_panels[index] = nullptr;
            report_status_textboxes[index] = nullptr;
            report_status_panel_hide_times[index] = 0;
        }
        active_report_status_panel = -1;

        for (My_SDL_button*& button : report_buttons)
        {
            button->delete_element();
            button = nullptr;
        }
    }

    bool save_dialog_is_waiting()
    {
        std::lock_guard<std::mutex> lock(save_dialog_mutex);
        return current_save_dialog_result == save_dialog_result::WAITING;
    }

    std::array<report_video_results, 6> collect_report_results()
    {
        const std::array<const file_processing_data*, 6> files = {
            &global_processing_data.file_1,
            &global_processing_data.file_2,
            &global_processing_data.file_3,
            &global_processing_data.file_4,
            &global_processing_data.file_5,
            &global_processing_data.file_6
        };

        std::array<report_video_results, 6> report_results = {};
        for (std::size_t index = 0; index < files.size(); ++index)
        {
            const file_processing_data& file = *files[index];
            if (!file.using_flag || !file.calculated_flag)
            {
                continue;
            }

            report_video_results& report = report_results[index];
            report.available = true;
            report.values = {
                file.processing_2.video_mean_light_power_percentage,
                file.processing_2.mean_light_power_delta_between_frames,
                file.processing_2.video_median_jet_amplitude,
                file.processing_2.video_mean_jet_length,
                file.processing_3.main_angle,
                file.processing_3.deviation_angle,
                file.processing_3.max_deviation_angle,
                file.processing_3.frames_angle_delta,
                file.processing_3.straight_speed,
                file.processing_3.deviation_speed,
                file.processing_3.frames_speed_delta,
                file.processing_3.deviation_percentage
            };
        }

        return report_results;
    }

    void save_report_if_ready()
    {
        save_dialog_result result;
        std::string output_path;
        {
            std::lock_guard<std::mutex> lock(save_dialog_mutex);
            result = current_save_dialog_result;
            if (result == save_dialog_result::IDLE || result == save_dialog_result::WAITING)
            {
                return;
            }
            output_path = selected_report_path;
            current_save_dialog_result = save_dialog_result::IDLE;
            selected_report_path.clear();
        }

        if (result == save_dialog_result::CANCELLED)
        {
            show_report_status(report_status::CALCULATION_COMPLETE);
            return;
        }
        if (result == save_dialog_result::FAILED)
        {
            show_report_status(report_status::FAILED);
            std::cerr << "The report save dialog failed: " << SDL_GetError() << '\n';
            return;
        }

        std::filesystem::path report_path = std::filesystem::u8path(output_path);
        std::string extension = report_path.extension().u8string();
        std::transform(extension.begin(), extension.end(), extension.begin(), [](unsigned char character)
        {
            return static_cast<char>(std::tolower(character));
        });
        if (extension != ".xlsx")
        {
            report_path += ".xlsx";
        }

        std::string error_message;
        if (!write_report_xlsx(report_path, collect_report_results(), error_message))
        {
            show_report_status(report_status::FAILED);
            std::cerr << "Failed to create report: " << error_message << '\n';
            return;
        }

        show_report_status(report_status::SAVED);
        std::cout << "Report saved to " << report_path.u8string() << '\n';
    }

    void reset_report_labels_if_language_changed()
    {
        if (!App_lang.get_lang_reset_flag())
        {
            return;
        }

        const std::array<Lang_string_type*, 4> labels = {
            &gd_exit,
            &gd_back,
            &gd_new_study,
            &gd_report_forming
        };
        for (std::size_t index = 0; index < report_buttons.size(); ++index)
        {
            report_buttons[index]->get_button_content_textbox()->set_content(
                str_by_dictionary(*labels[index])
            );
        }

        report_status_textboxes[report_status_index(current_report_status)]->set_content(
            report_status_text(current_report_status)
        );
    }
}

void report_forming_enter()
{
    report_buttons_create();
    report_buttons_setup();
    show_report_status(report_status::CALCULATION_COMPLETE);
    report_enter_time = SDL_GetTicks();
    automatic_save_dialog_started = false;
}

void report_forming_exit()
{
    report_buttons_free();

    std::lock_guard<std::mutex> lock(save_dialog_mutex);
    current_save_dialog_result = save_dialog_result::IDLE;
    selected_report_path.clear();
}

void report_forming_update()
{
    if (App_timer_1.can_execute(Execute_zone_ID::HZ_1000))
    {
        App_inputs.update();
    }

    if (App_timer_1.can_execute(Execute_zone_ID::HZ_240))
    {
        reset_report_labels_if_language_changed();
        report_background_panel->update();
        for (std::size_t index = 0; index < report_status_panels.size(); ++index)
        {
            report_status_panels[index]->update();
            if (report_status_panel_hide_times[index] != 0 &&
                SDL_GetTicks() >= report_status_panel_hide_times[index])
            {
                report_status_panels[index]->set_visible_flag(false);
                report_status_panel_hide_times[index] = 0;
            }
        }
        save_report_if_ready();

        if (!automatic_save_dialog_started &&
            SDL_GetTicks() - report_enter_time >= automatic_dialog_delay_ms)
        {
            automatic_save_dialog_started = true;
            show_report_save_dialog();
        }

        if (!save_dialog_is_waiting())
        {
            for (My_SDL_button* button : report_buttons)
            {
                button->update();
            }
        }
    }
}

void report_forming_render(SDL_Renderer* renderer)
{
    if (!App_timer_1.can_execute(Execute_zone_ID::HZ_120))
    {
        return;
    }

    report_background_panel->render(renderer);
    for (My_SDL_button* button : report_buttons)
    {
        button->render(renderer);
    }
    for (My_SDL_panel* panel : report_status_panels)
    {
        panel->render(renderer);
    }
}
