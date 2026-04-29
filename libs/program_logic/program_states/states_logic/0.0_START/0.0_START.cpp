// 0.0_START.cpp

/*


// =========================================================================================== IMPORT

#include "0.0_START.h"


#include "../../../../program_gui/basic_elements/UI_elements/my_sdl_textbox/my_sdl_textbox.h"


// =========================================================================================== IMPORT


// =========================================================================================== STATE DATA

// RAII + lifecycle management
My_SDL_textbox* Start_textbox = nullptr;

// =========================================================================================== STATE DATA


// =========================================================================================== MAIN STATE API


void start_enter()
{
    // ===== State allocation =====

    Start_textbox = new My_SDL_textbox();

    // ===== State allocation =====

    start_elements_setup();

    
}



void start_exit()
{

    // ===== State deallocation =====

    Start_textbox->delete_element();
    Start_textbox = nullptr;

    // ===== State deallocation =====



}


void start_update()
{
    // If user press any button, except EXIT: go to the next state
}


void start_render(SDL_Renderer* renderer)
{
    Start_textbox->render(renderer);
}




// =========================================================================================== MAIN STATE API




// =========================================================================================== INNER STATE FUNCTIONS

void start_elements_setup()
{
    // Start textbox setup

    Start_textbox->set_render_point(MAIN_WINDOW_H_SIZE / 2, MAIN_WINDOW_V_SIZE / 2);

    Start_textbox->set_font_size(24);

    Start_textbox->set_content(str_by_dictionary(gd_press_any_key));

}

// =========================================================================================== INNER STATE FUNCTIONS

*/