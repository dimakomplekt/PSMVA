// global_inputs.cpp


// =========================================================================================== IMPORT

#include "global_inputs.h"

// =========================================================================================== IMPORT


// =========================================================================================== MOUSE


GI_mouse& GI_mouse::Instance()
{
    // Local static ensures thread-safe lazy initialization in C++11+
    // Guarantees that only one instance of GI_mouse exists throughout the program.
    static GI_mouse instance;

    return instance;
}


void GI_mouse::update()
{
    // We call SDL_GetMouseState to update the mouse position and get bitmask of button states
    Uint32 buttons = SDL_GetMouseState(&this->x_pos, &this->y_pos);

    // We check the button bitmask to update our buttons pressing states
    this->lb_state = (buttons & SDL_BUTTON_LEFT) != 0;
    this->rb_state = (buttons & SDL_BUTTON_RIGHT) != 0;
}

// Simple returns 

float GI_mouse::get_x() const { return this->x_pos; }
float GI_mouse::get_y() const { return this->y_pos; }

bool GI_mouse::lb_clicked() const { return this->lb_state; }
bool GI_mouse::rb_clicked() const { return this->rb_state; }



bool lb_click_check()
{
    // Click status by GI_mouse singleton
    return App_mouse.lb_clicked();
}


// =========================================================================================== MOUSE