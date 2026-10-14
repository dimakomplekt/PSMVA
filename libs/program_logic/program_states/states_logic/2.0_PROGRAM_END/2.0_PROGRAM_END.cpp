#include "2.0_PROGRAM_END.h"

#include "../../../../program_gui/basic_elements/UI_elements/my_sdl_panel/my_sdl_panel.h"
#include "../../../../program_gui/basic_elements/UI_elements/my_sdl_textbox/my_sdl_textbox.h"
#include "../../../../program_gui/basic_elements/global_palette/global_palette.h"
#include "../../../../program_gui/basic_elements/global_fonts/global_fonts.h"
#include "../../../app.h"

namespace
{
    My_SDL_panel* program_end_panel = nullptr;
    My_SDL_textbox* program_end_textbox = nullptr;
    Uint64 program_end_start_time = 0;
}

void program_end_enter()
{
    program_end_panel = new My_SDL_panel();
    program_end_textbox = new My_SDL_textbox();
    program_end_start_time = SDL_GetTicks();

    program_end_panel->set_render_point(MAIN_WINDOW_H_SIZE / 2, MAIN_WINDOW_V_SIZE / 2);
    program_end_panel->set_size(MAIN_WINDOW_H_SIZE, MAIN_WINDOW_V_SIZE);
    program_end_panel->set_border_radius(0);

    program_end_textbox->switch_textbox_type(HEADER_2);
    program_end_textbox->set_content(str_by_dictionary(gd_study_complete));
    program_end_textbox->switch_blinking_mode_flag(true);
    program_end_panel->add_element(
        program_end_textbox,
        program_end_panel->get_width_size() * 0.5,
        program_end_panel->get_height_size() * 0.5,
        1
    );
}

void program_end_exit()
{
    program_end_panel->delete_element();
    program_end_panel = nullptr;
    program_end_textbox = nullptr;
}

void program_end_update()
{
    if (App_timer_1.can_execute(Execute_zone_ID::HZ_240))
    {
        program_end_panel->update();
    }

    if (SDL_GetTicks() - program_end_start_time >= 5000)
    {
        this_app.app_state = SDL_APP_SUCCESS;
    }
}

void program_end_render(SDL_Renderer* renderer)
{
    if (App_timer_1.can_execute(Execute_zone_ID::HZ_120))
    {
        program_end_panel->render(renderer);
    }
}
