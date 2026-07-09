// 1.2_MASKS_SETUP.cpp


// =========================================================================================== IMPORT

#include "1.2_MASKS_SETUP.h"


#include "../../../../program_gui/basic_elements/UI_elements/my_sdl_textbox/my_sdl_textbox.h"
#include "../../../../program_gui/basic_elements/UI_elements/my_sdl_panel/my_sdl_panel.h"

#include "../../../../program_gui/basic_elements/UI_elements/my_sdl_button/my_sdl_button.h"


// Predeclare for switching states
#include "../../program_states.h"

#include "../../../app.h"

// Log
#include <iostream>

// =========================================================================================== IMPORT


// =========================================================================================== STATE DATA

// RAII + lifecycle management

My_SDL_panel* Masks_setup_panel = nullptr;

My_SDL_textbox* Masks_setup_textbox = nullptr;

My_SDL_textbox* Masks_setup_textbox_2 = nullptr;

My_SDL_textbox* Masks_setup_textbox_3 = nullptr;

My_SDL_textbox* Masks_setup_textbox_4 = nullptr;

My_SDL_button* Information_button_1 = nullptr;

// =========================================================================================== STATE DATA


// =========================================================================================== STATE INNER FUNCTIONS PREDECLARATION

void masks_setup_elements_create();

void masks_setup_elements_setup();

void masks_setup_elements_free_and_nullptr();

void masks_setup_elements_update();

void reset_passed_by_dictionary_textboxes_if_language_switched_ms();

void masks_setup_actions();

void masks_setup_elements_render(SDL_Renderer* renderer);

// =========================================================================================== STATE INNER FUNCTIONS PREDECLARATION


// =========================================================================================== MAIN STATE API


void masks_setup_enter()
{
    // Log the enter in console
    std::cout << "Entering MASKS_SETUP\n"; 

    // ===== State allocation =====

    masks_setup_elements_create();

    // ===== State allocation =====


    // Elements setup

    masks_setup_elements_setup();

}



void masks_setup_exit()
{
    // ===== State deallocation =====

    masks_setup_elements_free_and_nullptr();

    // ===== State deallocation =====


    // Log the exit in console

    std::cout << "Exiting MASKS_SETUP\n"; 

}


void masks_setup_update()
{
    // Update inputs
    if (App_timer_1.can_execute(Execute_zone_ID::HZ_1000))
    {
        App_inputs.update();
    }

    if (App_timer_1.can_execute(Execute_zone_ID::HZ_240))
    {

        masks_setup_elements_update();

        masks_setup_actions();

    }
}


void masks_setup_render(SDL_Renderer* renderer)
{
    if (App_timer_1.can_execute(Execute_zone_ID::HZ_120))
    {
        masks_setup_elements_render(renderer);
    }
}




// =========================================================================================== MAIN STATE API




// =========================================================================================== INNER STATE FUNCTIONS


// =========================================================================================== STATE INNER FUNCTIONS REALIZATION

void masks_setup_elements_create()
{
    // Masks_setup panel create
    Masks_setup_panel = new My_SDL_panel();

    // Masks_setup textbox create
    Masks_setup_textbox = new My_SDL_textbox();

    Masks_setup_textbox_2 = new My_SDL_textbox();
    Masks_setup_textbox_3 = new My_SDL_textbox();
    Masks_setup_textbox_4 = new My_SDL_textbox();

    Information_button_1 = new My_SDL_button();
}


void masks_setup_elements_setup()
{
    // Masks_setup panel setup

    Masks_setup_panel->set_render_point(MAIN_WINDOW_H_SIZE / 2, MAIN_WINDOW_V_SIZE / 2);
    Masks_setup_panel->set_size(MAIN_WINDOW_H_SIZE, MAIN_WINDOW_V_SIZE);
    Masks_setup_panel->set_border_radius(0);

    // Masks_setup textbox setup
    Masks_setup_textbox->switch_textbox_type(HEADER_2);

    Masks_setup_textbox->set_content(str_by_dictionary(gd_press_any_key));

    Masks_setup_textbox->switch_blinking_mode_flag(true);


    Masks_setup_textbox_2->switch_textbox_type(HEADER_2);
    Masks_setup_textbox_2->set_content(str_by_dictionary(gd_press_any_key));
    Masks_setup_textbox_2->switch_blinking_mode_flag(true);


    Masks_setup_textbox_3->switch_textbox_type(HEADER_2);
    Masks_setup_textbox_3->set_content(str_by_dictionary(gd_press_any_key));
    Masks_setup_textbox_3->switch_blinking_mode_flag(true);


    Masks_setup_textbox_4->switch_textbox_type(HEADER_2);
    Masks_setup_textbox_4->set_content(str_by_dictionary(gd_press_any_key));
    Masks_setup_textbox_4->switch_blinking_mode_flag(true);


    Information_button_1->switch_button_textbox_type(HEADER_2);
    Information_button_1->get_button_content_textbox()->set_content(str_by_dictionary(gd_information_button));
    Information_button_1->set_size(100, 150);
    Information_button_1->set_render_point(300, 200);




    // Put the texture inside the middle of the panel

    Masks_setup_panel->add_element(

        Masks_setup_textbox,
         (Masks_setup_panel->get_width_size()) * 0.5,
          (Masks_setup_panel->get_height_size()) * 0.2,
           1
    );

    Masks_setup_panel->add_element(

        Masks_setup_textbox_2,
         (Masks_setup_panel->get_width_size()) * 0.5,
          (Masks_setup_panel->get_height_size()) * 0.4,
           1
    );

    Masks_setup_panel->add_element(

        Masks_setup_textbox_3,
         (Masks_setup_panel->get_width_size()) * 0.5,
          (Masks_setup_panel->get_height_size()) * 0.6,
           1
    );

    Masks_setup_panel->add_element(

        Masks_setup_textbox_4,
         (Masks_setup_panel->get_width_size()) * 0.5,
          (Masks_setup_panel->get_height_size()) * 0.8,
           1
    );


}


void masks_setup_elements_free_and_nullptr()
{
    // Free all elements

    Masks_setup_panel->delete_element();

    // Nullptr the pointers

    Masks_setup_panel = nullptr;
    Masks_setup_textbox = nullptr;
    
    Masks_setup_textbox_2 = nullptr;
    Masks_setup_textbox_3 = nullptr;
    Masks_setup_textbox_4 = nullptr;


    Information_button_1->delete_element();
    Information_button_1 = nullptr;
}


void masks_setup_elements_update()
{
    // Check if textboxes need content renew
    reset_passed_by_dictionary_textboxes_if_language_switched_ms();

    // Update all elements
    Masks_setup_panel->update();

    Information_button_1->update();

}


void reset_passed_by_dictionary_textboxes_if_language_switched_ms()
{
    // Repeat content set if language switched
    if (App_lang.get_lang_reset_flag())
    {
        Masks_setup_textbox->set_content(str_by_dictionary(gd_press_any_key));
    }
}


void masks_setup_actions()
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
        App_lang.switch_to_next_lang();
        App_fonts.switch_to_the_next_font_palette();
    
        static bool to_second = false;
    
        if (!to_second)
        {
            int old_x = Masks_setup_textbox->get_x_render_point();
            int old_y = Masks_setup_textbox->get_y_render_point();
    
            // Masks_setup_panel->move_to_point(old_x - 100, old_y - 200, EXPONENTIAL, 500);
            Masks_setup_textbox->move_to_point(old_x + 100, old_y + 200, LINEAR, 300);

            to_second = true;
        }
        else
        {
            int old_x = Masks_setup_textbox->get_x_render_point();
            int old_y = Masks_setup_textbox->get_y_render_point();

            // Masks_setup_panel->move_to_point(old_x + 100, old_y + 200, EXPONENTIAL, 500);
            Masks_setup_textbox->move_to_point(old_x - 100, old_y - 200, LINEAR, 300);

            to_second = false;
        }
    }
}


void masks_setup_elements_render(SDL_Renderer* renderer)
{
    // Render all elements
    Masks_setup_panel->render(renderer);

    Information_button_1->render(renderer);

}

// =========================================================================================== STATE INNER FUNCTIONS REALIZATION
