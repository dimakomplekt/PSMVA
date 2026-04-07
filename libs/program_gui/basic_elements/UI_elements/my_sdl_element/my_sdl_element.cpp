// my_sdl_element.h


// =========================================================================================== IMPORT

#include "my_sdl_element.h"

// =========================================================================================== IMPORT


// =========================================================================================== HELPER-FUNCTIONS

bool hover_check_by_boundaries(const element_rect_boundaries& boundaries)
{
    int curr_x = static_cast<int>(std::round(App_mouse.get_x()));
    int curr_y = static_cast<int>(std::round(App_mouse.get_y()));


    if (curr_x >= boundaries.left_boundary &&
        curr_x <= boundaries.right_boundary &&
        curr_y <= boundaries.bottom_boundary &&
        curr_y >= boundaries.top_boundary) 
        
        // Mouse inside the element zone 
        return true;
    
    else 

        // Mouse outside the element zone
        return false;
}


// =========================================================================================== HELPER-FUNCTIONS



// =========================================================================================== CONSTRUCTOR AND DESTRUCTOR


My_SDL_element::My_SDL_element() : gui_type(STATIC_ELEMENT_GUI), x_render_point(0), y_render_point(0), opacity(255)
{
    // Default
}


// =========================================================================================== CONSTRUCTOR AND DESTRUCTOR


// =========================================================================================== GUI

// GUI type setter 

void My_SDL_element::set_gui_type(element_gui_type new_gui_type)
{
    // Error handling for invalid GUI type
    if (new_gui_type != STATIC_ELEMENT_GUI && new_gui_type != DYNAMIC_ELEMENT_GUI)
    {
        std::cerr << "Invalid element GUI type. GUI type not changed." << std::endl;
        return;
    }

    // New type setting
    else this->gui_type = new_gui_type;
}


// Render point getters 

int My_SDL_element::get_x_render_point() const { return this->x_render_point; }

int My_SDL_element::get_y_render_point() const { return this->y_render_point; }


// Opacity setter and getter

void My_SDL_element::set_opacity(Uint8 new_opacity) 
{
    this->opacity = new_opacity;
}


Uint8 My_SDL_element::get_opacity() const 
{
    return this->opacity;
}

// =========================================================================================== GUI