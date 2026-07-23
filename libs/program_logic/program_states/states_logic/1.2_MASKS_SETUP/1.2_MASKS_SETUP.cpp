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


// Check
#include "../1.1_FILE_CHOOSE/1.1_FILE_CHOOSE.h"

// =========================================================================================== IMPORT


// =========================================================================================== STATE DATA

// RAII + lifecycle management

My_SDL_panel* Masks_setup_panel = nullptr;

My_SDL_textbox* Masks_setup_textbox = nullptr;

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
}


void masks_setup_elements_setup()
{
    // Masks_setup panel setup

    Masks_setup_panel->set_render_point(MAIN_WINDOW_H_SIZE / 2, MAIN_WINDOW_V_SIZE / 2);
    Masks_setup_panel->set_size(MAIN_WINDOW_H_SIZE, MAIN_WINDOW_V_SIZE);
    Masks_setup_panel->set_border_radius(0);

    // Masks_setup textbox setup
    Masks_setup_textbox->switch_textbox_type(HEADER_2);

    Masks_setup_textbox->set_content(str_by_dictionary(gd_masks_setup_info));

    Masks_setup_textbox->switch_blinking_mode_flag(true);



    // Put the texture inside the middle of the panel

    Masks_setup_panel->add_element(

        Masks_setup_textbox,
         (Masks_setup_panel->get_width_size()) * 0.5,
          (Masks_setup_panel->get_height_size()) * 0.5,
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
    
}


void masks_setup_elements_update()
{
    // Check if textboxes need content renew
    reset_passed_by_dictionary_textboxes_if_language_switched_ms();

    // Update all elements
    Masks_setup_panel->update();

}


void reset_passed_by_dictionary_textboxes_if_language_switched_ms()
{
    // Repeat content set if language switched
    if (App_lang.get_lang_reset_flag())
    {
        Masks_setup_textbox->set_content(str_by_dictionary(gd_masks_setup_info));
    }
}


void masks_setup_actions()
{
    // Switch the state to EXIT if EXIT pressed

    if (App_inputs.is_just_released(Key_actions::EXIT))
    {
        this_app.app_sm.request_state_change(FILE_CHOOSE_ID);
    }

    // Switch the state to MAIN MENU if ENTER pressed

    if (App_inputs.is_just_released(Key_actions::ENTER))
    {
        this_app.app_sm.request_state_change(MASKS_SETUP_ID_1);
    }

}


void masks_setup_elements_render(SDL_Renderer* renderer)
{
    // Render all elements
    Masks_setup_panel->render(renderer);

}

// =========================================================================================== STATE INNER FUNCTIONS REALIZATION


void masks_setup_2_enter()
{
    //
}


void masks_setup_2_exit()
{
    //
}


void masks_setup_2_update()
{
    //
}


void masks_setup_2_render(SDL_Renderer* renderer)
{
    //
}


void masks_setup_3_enter()
{
    //
}


void masks_setup_3_exit()
{
    //
}


void masks_setup_3_update()
{
    //
}


void masks_setup_3_render(SDL_Renderer* renderer)
{
    //
}


void masks_setup_4_enter()
{
    //
}


void masks_setup_4_exit()
{
    //
}


void masks_setup_4_update()
{
    //
}


void masks_setup_4_render(SDL_Renderer* renderer)
{
    //
}


void masks_setup_5_enter()
{
    //
}


void masks_setup_5_exit()
{
    //
}


void masks_setup_5_update()
{
    //
}


void masks_setup_5_render(SDL_Renderer* renderer)
{
    //
}


void masks_setup_6_enter()
{
    //
}


void masks_setup_6_exit()
{
    //
}


void masks_setup_6_update()
{
    //
}


void masks_setup_6_render(SDL_Renderer* renderer)
{
    //
}


