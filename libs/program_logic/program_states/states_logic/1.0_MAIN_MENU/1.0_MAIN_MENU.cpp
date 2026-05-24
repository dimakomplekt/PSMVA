// 1.0_MAIN_MENU.cpp


// =========================================================================================== IMPORT

#include "1.0_MAIN_MENU.h"


#include "../../../../program_gui/basic_elements/UI_elements/my_sdl_textbox/my_sdl_textbox.h"
#include "../../../../program_gui/basic_elements/UI_elements/my_sdl_panel/my_sdl_panel.h"
#include "../../../../program_gui/basic_elements/UI_elements/my_sdl_button/my_sdl_button.h"
#include "../../../../program_gui/basic_elements/UI_elements/my_sdl_texture/my_sdl_texture.h"


// Predeclare for switching states
#include "../../program_states.h"

#include "../../../app.h"

// Log
#include <iostream>

// =========================================================================================== IMPORT


// =========================================================================================== STATE DATA

// RAII + lifecycle management

// Background
My_SDL_panel* Main_menu_panel = nullptr;


// Next state
My_SDL_button* Analysis_start_button = nullptr;


// Information panel

My_SDL_button* Information_button = nullptr;

My_SDL_panel* Information_panel = nullptr;

bool information_panel_visible_flag = false;

My_SDL_textbox* Info_1_textbox = nullptr;
My_SDL_texture* Plasma_spraying_texture_1 = nullptr;

My_SDL_textbox* Info_2_textbox = nullptr;
My_SDL_texture* Plasma_spraying_texture_2 = nullptr;

My_SDL_textbox* Info_3_textbox = nullptr;
My_SDL_texture* Plasma_spraying_texture_3 = nullptr;


My_SDL_button* Information_close_button = nullptr;


// Settings panel

My_SDL_button* Settings_button = nullptr;


My_SDL_panel* Settings_panel = nullptr;

My_SDL_button* Switch_theme_button = nullptr;

My_SDL_button* Switch_language_button = nullptr;

My_SDL_button* Settings_reset_button = nullptr;

My_SDL_button* Settings_accept_button = nullptr;


// Exit button

My_SDL_button* Exit_button = nullptr;


// Panel with plasma spraying screen of video

My_SDL_panel* Plasma_spraying_panel = nullptr;

My_SDL_textbox* PSMVA_textbox = nullptr;

My_SDL_texture* Plasma_spraying_texture_4 = nullptr;

// =========================================================================================== STATE DATA


// =========================================================================================== STATE INNER FUNCTIONS PREDECLARATION

void main_menu_elements_create();

void main_menu_elements_setup();

void main_menu_elements_free_and_nullptr();

void main_menu_elements_update();

void reset_passed_by_dictionary_textboxes_if_language_switched_mm();

void main_menu_actions();

void main_menu_elements_render(SDL_Renderer* renderer);

// =========================================================================================== STATE INNER FUNCTIONS PREDECLARATION


// =========================================================================================== MAIN STATE API


void main_menu_enter()
{
    // Log the enter in console
    std::cout << "Entering MAIN_MENU\n"; 

    // ===== State allocation =====

    main_menu_elements_create();

    // ===== State allocation =====


    // Elements setup

    main_menu_elements_setup();

}



void main_menu_exit()
{
    // ===== State deallocation =====

    main_menu_elements_free_and_nullptr();

    // ===== State deallocation =====


    // Log the exit in console

    std::cout << "Exiting MAIN_MENU\n"; 

}


void main_menu_update()
{
    // Update inputs
    App_inputs.update();

    main_menu_elements_update();

    main_menu_actions();
}


void main_menu_render(SDL_Renderer* renderer)
{
    main_menu_elements_render(renderer);
}




// =========================================================================================== MAIN STATE API




// =========================================================================================== INNER STATE FUNCTIONS


// =========================================================================================== STATE INNER FUNCTIONS REALIZATION

void main_menu_elements_create()
{
    // Background
    Main_menu_panel = new My_SDL_panel;


    // Next state
    Analysis_start_button = new My_SDL_button;


    // Information panel

    Information_button = new My_SDL_button;

    Information_panel = new My_SDL_panel;


    Info_1_textbox = new My_SDL_textbox;
    Plasma_spraying_texture_1 = new My_SDL_texture;

    Info_2_textbox = new My_SDL_textbox;
    Plasma_spraying_texture_2 = new My_SDL_texture;

    Info_3_textbox = new My_SDL_textbox;
    Plasma_spraying_texture_3 = new My_SDL_texture;


    Information_close_button = new My_SDL_button;


    // Settings panel

    Settings_button = new My_SDL_button;

    Settings_panel = new My_SDL_panel;

    Switch_theme_button = new My_SDL_button;

    Switch_language_button = new My_SDL_button;

    Settings_reset_button = new My_SDL_button;

    Settings_accept_button = new My_SDL_button;


    // Exit button

    Exit_button = new My_SDL_button;


    // Panel with plasma spraying screen of video

    Plasma_spraying_panel = new My_SDL_panel;

    PSMVA_textbox = new My_SDL_textbox;

    Plasma_spraying_texture_4 = new My_SDL_texture;

}


void main_menu_elements_setup()
{
    // Background

    Main_menu_panel->set_render_point(MAIN_WINDOW_H_SIZE / 2, MAIN_WINDOW_V_SIZE / 2);
    Main_menu_panel->set_size(MAIN_WINDOW_H_SIZE, MAIN_WINDOW_V_SIZE);

    // Next state

    const int FIRST_ZONE_WIDTH = static_cast<int>(MAIN_WINDOW_H_SIZE * 0.4);
    const int SECOND_ZONE_WIDTH = MAIN_WINDOW_H_SIZE - FIRST_ZONE_WIDTH;

    const int SCREEN_MARGIN_1 = 50;
    const int SCREEN_MARGIN_2 = 50;

    int mm_buttons_h_size = FIRST_ZONE_WIDTH - 2 * SCREEN_MARGIN_1;
    int mm_buttons_v_size = static_cast<int>((MAIN_WINDOW_V_SIZE - 5 * SCREEN_MARGIN_1) / 4);

    int mm_panels_h_size = SECOND_ZONE_WIDTH - 2 * SCREEN_MARGIN_2;
    int mm_panels_v_size = static_cast<int>((MAIN_WINDOW_V_SIZE - 3 * SCREEN_MARGIN_1) / 2);

    int inf_panel_x_render_point = MAIN_WINDOW_H_SIZE - SECOND_ZONE_WIDTH * 0.5;
    int inf_panel_y_render_point = (SCREEN_MARGIN_1 + 0.5 * mm_panels_v_size);


    int ps_panel_x_render_point = inf_panel_x_render_point;
    int ps_panel_y_render_point = MAIN_WINDOW_V_SIZE - (SCREEN_MARGIN_1 + 0.5 * mm_panels_v_size);


    Analysis_start_button->get_button_content_textbox()->set_content(str_by_dictionary(gd_analysis_start_button));
    Analysis_start_button->set_size(mm_buttons_h_size, mm_buttons_v_size);
    Analysis_start_button->set_render_point(FIRST_ZONE_WIDTH * 0.5, SCREEN_MARGIN_1 + mm_buttons_v_size * 0.5);

    // Information button

    Information_button->get_button_content_textbox()->set_content(str_by_dictionary(gd_information_button));
    Information_button->set_size(mm_buttons_h_size, mm_buttons_v_size);
    Information_button->set_render_point(FIRST_ZONE_WIDTH * 0.5, (SCREEN_MARGIN_1 + mm_buttons_v_size * 0.5) + 1*(mm_buttons_v_size + SCREEN_MARGIN_1));

    // Information panel

    Information_panel->set_size(mm_panels_h_size, mm_panels_v_size);
    Information_panel->set_render_point(inf_panel_x_render_point, inf_panel_y_render_point);
    Information_panel->set_visible_flag(false);


    Info_1_textbox->set_content(str_by_dictionary(gd_information_textbox_1));

    Info_2_textbox->set_content(str_by_dictionary(gd_information_textbox_2));

    Info_3_textbox->set_content(str_by_dictionary(gd_information_textbox_3));


    // Settings panel

    Settings_button->get_button_content_textbox()->set_content(str_by_dictionary(gd_settings_button));
    Settings_button->set_size(mm_buttons_h_size, mm_buttons_v_size);
    Settings_button->set_render_point(FIRST_ZONE_WIDTH * 0.5, (SCREEN_MARGIN_1 + mm_buttons_v_size * 0.5) + 2*(mm_buttons_v_size + SCREEN_MARGIN_1));


    Settings_panel->set_size(mm_panels_h_size, mm_panels_v_size);
    Settings_panel->set_render_point(inf_panel_x_render_point, inf_panel_y_render_point);
    Settings_panel->set_visible_flag(false);


    Switch_theme_button->get_button_content_textbox()->set_content("🎨");


    Switch_language_button->get_button_content_textbox()->set_content(str_by_dictionary(gd_language_settings));


    Settings_reset_button->get_button_content_textbox()->set_content("⟲");


    Settings_accept_button->get_button_content_textbox()->set_content("✔");


    // Exit button

    Exit_button->get_button_content_textbox()->set_content(str_by_dictionary(gd_exit_button));
    Exit_button->set_size(mm_buttons_h_size, mm_buttons_v_size);
    Exit_button->set_render_point(FIRST_ZONE_WIDTH * 0.5, (SCREEN_MARGIN_1 + mm_buttons_v_size * 0.5) + 3*(mm_buttons_v_size + SCREEN_MARGIN_1));


    // Panel with plasma spraying screen of video
    Plasma_spraying_panel->set_size(mm_panels_h_size, mm_panels_v_size);
    Plasma_spraying_panel->set_render_point(ps_panel_x_render_point, ps_panel_y_render_point);
}


void main_menu_elements_free_and_nullptr()
{
    // Protection
    if (Main_menu_panel == nullptr) return;
    
    // Free all elements
    // Background
    Main_menu_panel->delete_element();


    // Next state
    Analysis_start_button->delete_element();


    // Information panel

    Information_button->delete_element();

    Information_panel->delete_element();


    Info_1_textbox->delete_element();
    Plasma_spraying_texture_1->delete_element();

    Info_2_textbox->delete_element();
    Plasma_spraying_texture_2->delete_element();

    Info_3_textbox->delete_element();
    Plasma_spraying_texture_3->delete_element();


    Information_close_button->delete_element();


    // Settings panel

    Settings_button->delete_element();

    Settings_panel->delete_element();

    Switch_theme_button->delete_element();

    Switch_language_button->delete_element();

    Settings_reset_button->delete_element();

    Settings_accept_button->delete_element();


    // Exit button

    Exit_button->delete_element();


    // Panel with plasma spraying screen of video

    Plasma_spraying_panel->delete_element();

    PSMVA_textbox->delete_element();

    Plasma_spraying_texture_4->delete_element();


    // Nullptr the pointers

    // Background
    Main_menu_panel = nullptr;


    // Next state
    Analysis_start_button = nullptr;


    // Information panel

    Information_button = nullptr;

    Information_panel = nullptr;


    Info_1_textbox = nullptr;
    Plasma_spraying_texture_1 = nullptr;

    Info_2_textbox = nullptr;
    Plasma_spraying_texture_2 = nullptr;

    Info_3_textbox = nullptr;
    Plasma_spraying_texture_3 = nullptr;


    Information_close_button = nullptr;


    // Settings panel

    Settings_button = nullptr;

    Settings_panel = nullptr;

    Switch_theme_button = nullptr;

    Switch_language_button = nullptr;

    Settings_reset_button = nullptr;

    Settings_accept_button = nullptr;


    // Exit button

    Exit_button = nullptr;


    // Panel with plasma spraying screen of video

    Plasma_spraying_panel = nullptr;

    PSMVA_textbox = nullptr;

    Plasma_spraying_texture_4 = nullptr;
}


void main_menu_elements_update()
{
    // Check if textboxes need content renew
    reset_passed_by_dictionary_textboxes_if_language_switched_mm();


    // Update all elements

    // Background
    Main_menu_panel->update();


    // Next state
    Analysis_start_button->update();


    // Information panel

    Information_button->update();

    Information_panel->update();


    Info_1_textbox->update();
    Plasma_spraying_texture_1->update();

    Info_2_textbox->update();
    Plasma_spraying_texture_2->update();

    Info_3_textbox->update();
    Plasma_spraying_texture_3->update();


    Information_close_button->update();


    // Settings panel

    Settings_button->update();

    Settings_panel->update();

    Switch_theme_button->update();

    Switch_language_button->update();

    Settings_reset_button->update();

    Settings_accept_button->update();


    // Exit button

    Exit_button->update();


    // Panel with plasma spraying screen of video

    Plasma_spraying_panel->update();

    PSMVA_textbox->update();

    Plasma_spraying_texture_4->update();

}


void reset_passed_by_dictionary_textboxes_if_language_switched_mm()
{
    // Repeat content set if language switched
    if (App_lang.get_lang_reset_flag())
    {
        // Next state

        Analysis_start_button->get_button_content_textbox()->set_content(str_by_dictionary(gd_analysis_start_button));

        // Information panel

        Information_button->get_button_content_textbox()->set_content(str_by_dictionary(gd_information_button));

        // Settings panel
        Settings_button->get_button_content_textbox()->set_content(str_by_dictionary(gd_analysis_start_button));

        Switch_language_button->get_button_content_textbox()->set_content(str_by_dictionary(gd_language_settings));

        Exit_button->get_button_content_textbox()->set_content(str_by_dictionary(gd_exit_button));
    }
}


void main_menu_actions()
{
    // Switch the state to EXIT if EXIT pressed

    if (App_inputs.is_just_released(Key_actions::EXIT))
    {
        this_app.app_sm.request_state_change(START_ID);
    }

    // Switch the state to MAIN MENU if ENTER pressed

    if (App_inputs.is_just_released(Key_actions::ENTER))
    {
        this_app.app_sm.request_state_change(START_ID);
    }

    if (App_inputs.is_just_released(Key_actions::SPECIAL_1))
    {
        App_palette.switch_to_the_next_palette();
        App_fonts.switch_to_the_next_font_palette();
        App_lang.switch_to_next_lang();
    }


    // Moving of the button

    if (App_inputs.is_just_released(Key_actions::LEFT))
    {
        Analysis_start_button->move_to_point(Analysis_start_button->get_x_render_point() - 25, Analysis_start_button->get_y_render_point(), LOGARITHMIC, 300);
    }

    if (App_inputs.is_just_released(Key_actions::UP))
    {
        Analysis_start_button->move_to_point(Analysis_start_button->get_x_render_point(), Analysis_start_button->get_y_render_point() - 25, LOGARITHMIC, 300);
    }

    if (App_inputs.is_just_released(Key_actions::RIGHT))
    {
        Analysis_start_button->move_to_point(Analysis_start_button->get_x_render_point() + 25, Analysis_start_button->get_y_render_point(), LOGARITHMIC, 300);
    }


    if (App_inputs.is_just_released(Key_actions::DOWN))
    {
        Analysis_start_button->move_to_point(Analysis_start_button->get_x_render_point(), Analysis_start_button->get_y_render_point() + 25, LOGARITHMIC, 300);
    }

}


void main_menu_elements_render(SDL_Renderer* renderer)
{
    // Render all elements

    // Update all elements
    
    // Background
    Main_menu_panel->render(renderer);


    // Next state
    Analysis_start_button->render(renderer);


    // Information panel

    Information_button->render(renderer);

    Information_panel->render(renderer);


    // Info_1_textbox->render(renderer);
    // Plasma_spraying_texture->render(renderer);

    // Info_2_textbox->render(renderer);
    // Plasma_spraying_texture->render(renderer);

    // Info_3_textbox->render(renderer);
    // Plasma_spraying_texture->render(renderer);


    // Information_close_button->render(renderer);


    // Settings panel

    Settings_button->render(renderer);

    Settings_panel->render(renderer);

    // Switch_theme_button->render(renderer);

    // Switch_language_button->render(renderer);

    // Settings_reset_button->render(renderer);

    // Settings_accept_button->render(renderer);


    // Exit button

    Exit_button->render(renderer);


    // Panel with plasma spraying screen of video

    Plasma_spraying_panel->render(renderer);

    // PSMVA_textbox->render(renderer);

    // Plasma_spraying_texture->render(renderer);

}

// =========================================================================================== STATE INNER FUNCTIONS REALIZATION
