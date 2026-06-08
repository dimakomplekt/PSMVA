// 1.1_FILE_CHOOSE.cpp


// =========================================================================================== IMPORT

#include "1.1_FILE_CHOOSE.h"


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
My_SDL_panel* File_choose_background_panel = nullptr;

My_SDL_textbox* File_choose_panel_textbox = nullptr;

// File choose panel (5 elements now)

My_SDL_panel* File_choose_panel = nullptr;

My_SDL_panel* File_1_panel = nullptr;
My_SDL_textbox* File_1_textbox = nullptr;
My_SDL_button* File_1_button = nullptr;

My_SDL_panel* File_2_panel = nullptr;
My_SDL_textbox* File_2_textbox = nullptr;
My_SDL_button* File_2_button = nullptr;

My_SDL_panel* File_3_panel = nullptr;
My_SDL_textbox* File_3_textbox = nullptr;
My_SDL_button* File_3_button = nullptr;

My_SDL_panel* File_4_panel = nullptr;
My_SDL_textbox* File_4_textbox = nullptr;
My_SDL_button* File_4_button = nullptr;

My_SDL_panel* File_5_panel = nullptr;
My_SDL_textbox* File_5_textbox = nullptr;
My_SDL_button* File_5_button = nullptr;


// Preview panel

My_SDL_panel* File_preview_panel = nullptr;
My_SDL_texture* File_preview_texture = nullptr;


// State control button

My_SDL_button* Study_start_button = nullptr;


// =========================================================================================== STATE DATA


// =========================================================================================== STATE INNER FUNCTIONS PREDECLARATION

void file_choose_elements_create();

void file_choose_elements_setup();

void file_choose_elements_free_and_nullptr();

void file_choose_elements_update();

void reset_passed_by_dictionary_textboxes_if_language_switched_fc();

void file_choose_actions();

void file_choose_elements_render(SDL_Renderer* renderer);

// =========================================================================================== STATE INNER FUNCTIONS PREDECLARATION


// =========================================================================================== MAIN STATE API


void file_choose_enter()
{
    // Log the enter in console
    std::cout << "Entering FILE_CHOOSE\n"; 

    // ===== State allocation =====

    file_choose_elements_create();

    // ===== State allocation =====


    // Elements setup

    file_choose_elements_setup();

}



void file_choose_exit()
{
    // ===== State deallocation =====

    file_choose_elements_free_and_nullptr();

    // ===== State deallocation =====


    // Log the exit in console

    std::cout << "Exiting FILE_CHOOSE\n"; 

}


void file_choose_update()
{
    // Update inputs
    App_inputs.update();

    file_choose_elements_update();

    file_choose_actions();
}


void file_choose_render(SDL_Renderer* renderer)
{
    file_choose_elements_render(renderer);
}


// =========================================================================================== MAIN STATE API


// =========================================================================================== STATE INNER FUNCTIONS REALIZATION

void file_choose_elements_create()
{
    // Background
    File_choose_background_panel = new My_SDL_panel;


    // File choose panel (5 elements now)

    File_choose_panel = new My_SDL_panel;

    File_choose_panel_textbox = new My_SDL_textbox;

    File_1_panel = new My_SDL_panel;
    File_1_textbox = new My_SDL_textbox;
    File_1_button = new My_SDL_button;

    File_2_panel = new My_SDL_panel;
    File_2_textbox = new My_SDL_textbox;
    File_2_button = new My_SDL_button;

    File_3_panel = new My_SDL_panel;
    File_3_textbox = new My_SDL_textbox;
    File_3_button = new My_SDL_button;

    File_4_panel = new My_SDL_panel;
    File_4_textbox = new My_SDL_textbox;
    File_4_button = new My_SDL_button;

    File_5_panel = new My_SDL_panel;
    File_5_textbox = new My_SDL_textbox;
    File_5_button = new My_SDL_button;


    // Preview panel

    File_preview_panel = new My_SDL_panel;
    File_preview_texture = new My_SDL_texture;


    // State control button

    Study_start_button = new My_SDL_button;
}


// ===== SETUP DATA =====

// ===== Main sizes =====

const int BACKGROUND_WIDTH  = MAIN_WINDOW_H_SIZE;
const int BACKGROUND_HEIGHT  = MAIN_WINDOW_V_SIZE;

const int FIRST_ZONE_WIDTH = static_cast<int>(MAIN_WINDOW_H_SIZE * 0.5);
const int SECOND_ZONE_WIDTH = MAIN_WINDOW_H_SIZE - FIRST_ZONE_WIDTH;

const int SCREEN_MARGIN_1 = 50;
const int SCREEN_MARGIN_2 = 50;

const int file_choose_panel_width = (FIRST_ZONE_WIDTH  - 1.5 * SCREEN_MARGIN_1);
const int file_choose_panel_height = (BACKGROUND_HEIGHT - 2 * SCREEN_MARGIN_2);


const int mini_panels_margin = 25;

const int file_choose_mini_panels_width = file_choose_panel_width - 2 * mini_panels_margin;
const int file_choose_mini_panels_height = (file_choose_panel_height - 7 * mini_panels_margin) / 6;

const int file_choose_buttons_width = file_choose_mini_panels_width * 0.2;
const int file_choose_buttons_height = file_choose_mini_panels_height;


const int file_preview_width = (SECOND_ZONE_WIDTH  - 1.5 * SCREEN_MARGIN_1);
const int file_preview_height = (BACKGROUND_HEIGHT - 3 * SCREEN_MARGIN_2) * 0.7;

const int study_start_button_width = file_preview_width;
const int study_start_button_height = (BACKGROUND_HEIGHT - 3 * SCREEN_MARGIN_2) - file_preview_height;



// ====== Main points ======

int file_choose_background_x = MAIN_WINDOW_H_SIZE * 0.5;
int file_choose_background_y = MAIN_WINDOW_V_SIZE * 0.5;


int file_choose_panel_x = FIRST_ZONE_WIDTH * 0.5;
int file_choose_panel_y = BACKGROUND_HEIGHT * 0.5;


int file_choose_preview_x = ;
int file_choose_preview_y = ;

int study_start_button_x = ; 
int study_start_button_y = ; 


// ===== SETUP DATA =====


void file_choose_elements_setup()
{     
    // ===== Setup =====

    // Background setup

    File_choose_background_panel->set_render_point(file_choose_background_x, file_choose_background_y);
    File_choose_background_panel->set_size(BACKGROUND_WIDTH, BACKGROUND_HEIGHT);
    File_choose_background_panel->set_border_radius_size(0);
    

}


void file_choose_elements_free_and_nullptr()
{
    // Protection
    if (File_choose_background_panel == nullptr) return;


    // ===== Free all elements =====

    // Background
    File_choose_background_panel->delete_element();


    // File choose panel (5 elements now)

    File_choose_panel->delete_element();

    // Preview panel

    File_preview_panel->delete_element();


    // State control button

    Study_start_button->delete_element();
    

    // ===== Nullptr the pointers =====

    // Background
    File_choose_background_panel = nullptr;


    // File choose panel (5 elements now)

    File_choose_panel = nullptr;

    File_choose_panel_textbox = nullptr;

    File_1_panel = nullptr;
    File_1_textbox = nullptr;
    File_1_button = nullptr;

    File_2_panel = nullptr;
    File_2_textbox = nullptr;
    File_2_button = nullptr;

    File_3_panel = nullptr;
    File_3_textbox = nullptr;
    File_3_button = nullptr;

    File_4_panel = nullptr;
    File_4_textbox = nullptr;
    File_4_button = nullptr;

    File_5_panel = nullptr;
    File_5_textbox = nullptr;
    File_5_button = nullptr;


    // Preview panel

    File_preview_panel = nullptr;
    File_preview_texture = nullptr;


    // State control button

    Study_start_button = nullptr;

}


void file_choose_elements_update()
{
    // ===== Check if textboxes need content renew =====

    reset_passed_by_dictionary_textboxes_if_language_switched_fc();


    // ===== Update all elements =====

    // Background
    File_choose_background_panel->update();

    // File choose panel (5 elements now)

    File_choose_panel->update();

    // Preview panel

    File_preview_panel->update();

    
    // State control button

    Study_start_button->update();
        
}


void reset_passed_by_dictionary_textboxes_if_language_switched_fc()
{
    // Repeat content set if language switched
    if (App_lang.get_lang_reset_flag())
    {
        // Textboxes for update

    }
}


void file_choose_actions()
{
    // State actions
}


void file_choose_elements_render(SDL_Renderer* renderer)
{
    // Render all elements

    // Background
    File_choose_background_panel->render(renderer);

    
    // File choose panel (5 elements now)

    File_choose_panel->render(renderer);

    // Preview panel

    File_preview_panel->render(renderer);

    
    // State control button

    Study_start_button->render(renderer);
}

// =========================================================================================== STATE INNER FUNCTIONS REALIZATION


// =========================================================================================== STATE ELEMENTS INNER FUNCTIONS


// =========================================================================================== STATE ELEMENTS INNER FUNCTIONS
