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

bool information_panel_visible_flag;

My_SDL_textbox* Info_1_textbox = nullptr;
My_SDL_texture* Plasma_spraying_texture = nullptr;

My_SDL_textbox* Info_2_textbox = nullptr;
My_SDL_texture* Plasma_spraying_texture = nullptr;

My_SDL_textbox* Info_3_textbox = nullptr;
My_SDL_texture* Plasma_spraying_texture = nullptr;


My_SDL_button* Information_close_button = nullptr;


// Settings panel

My_SDL_button* Settings_button = nullptr;

My_SDL_button* Switch_theme_button = nullptr;

My_SDL_button* Switch_language_button = nullptr;

My_SDL_button* Settings_reset_button = nullptr;

My_SDL_button* Settings_accept_button = nullptr;


// Exit button

My_SDL_button* Exit_button = nullptr;


// Panel with plasma spraying screen of video

My_SDL_panel* Plasma_spraying_panel = nullptr;

My_SDL_textbox* PSMVA_textbox = nullptr;

My_SDL_texture* Plasma_spraying_texture = nullptr;

// =========================================================================================== STATE DATA


// =========================================================================================== STATE INNER FUNCTIONS PREDECLARATION

void main_menu_elements_create();

void main_menu_elements_setup();

void main_menu_elements_free_and_nullptr();

void main_menu_elements_update();

void reset_passed_by_dictionary_textboxes_if_language_switched();

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
    Plasma_spraying_texture = new My_SDL_texture;

    Info_2_textbox = new My_SDL_textbox;
    Plasma_spraying_texture = new My_SDL_texture;

    Info_3_textbox = new My_SDL_textbox;
    Plasma_spraying_texture = new My_SDL_texture;


    Information_close_button = new My_SDL_button;


    // Settings panel

    Settings_button = new My_SDL_button;

    Switch_theme_button = new My_SDL_button;

    Switch_language_button = new My_SDL_button;

    Settings_reset_button = new My_SDL_button;

    Settings_accept_button = new My_SDL_button;


    // Exit button

    Exit_button = new My_SDL_button;


    // Panel with plasma spraying screen of video

    Plasma_spraying_panel = new My_SDL_panel;

    PSMVA_textbox = new My_SDL_textbox;

    Plasma_spraying_texture = new My_SDL_texture;

}


void main_menu_elements_setup()
{
    // Background

    Main_menu_panel->set_render_point(MAIN_WINDOW_H_SIZE / 2, MAIN_WINDOW_V_SIZE / 2);
    Main_menu_panel->set_size(MAIN_WINDOW_H_SIZE, MAIN_WINDOW_V_SIZE);

    // Next state

    Analysis_start_button->get_button_content_textbox()->set_content(str_by_dictionary(gd_analysis_start_button));
    Analysis_start_button->set_size();

    // Information panel

    Information_button->get_button_content_textbox()->set_content(str_by_dictionary(gd_information_button));

    information_panel_visible_flag = false;

    Information_panel->set_size(700, 800);
    Information_panel->set_render_point(MAIN_WINDOW_H_SIZE + Information_panel->get_width_size(), MAIN_WINDOW_V_SIZE + Information_panel->get_height_size());


    Info_1_textbox

    Info_2_textbox

    Info_3_textbox


    // Settings panel

    Settings_button->get_button_content_textbox()->set_content(str_by_dictionary(gd_analysis_start_button));

    Switch_theme_button->get_button_content_textbox()->set_content("🎨");

    Switch_language_button->get_button_content_textbox()->set_content(str_by_dictionary(gd_language_settings));

    Settings_reset_button->get_button_content_textbox()->set_content("⟲");
    Settings_accept_button->get_button_content_textbox()->set_content("✔");


    // Exit button

    Exit_button = new My_SDL_button;


    // Panel with plasma spraying screen of video



}


void main_menu_elements_free_and_nullptr()
{
    // Free all elements


    // Nullptr the pointers

}


void main_menu_elements_update()
{
    // Check if textboxes need content renew
    reset_passed_by_dictionary_textboxes_if_language_switched();


    // Update all elements

}


void reset_passed_by_dictionary_textboxes_if_language_switched()
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
    }
}


void main_menu_actions()
{


    if (App_inputs.is_just_released(Key_actions::SPECIAL_1))
    {
        App_palette.switch_to_the_next_palette();
    }
}


void main_menu_elements_render(SDL_Renderer* renderer)
{
    // Render all elements

}

// =========================================================================================== STATE INNER FUNCTIONS REALIZATION
