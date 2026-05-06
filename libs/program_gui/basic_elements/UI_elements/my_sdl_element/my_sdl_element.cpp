// my_sdl_element.h


// =========================================================================================== IMPORT

#include "my_sdl_element.h"

#include "../my_sdl_panel/my_sdl_panel.h"       // Methods pass

// =========================================================================================== IMPORT


// =========================================================================================== HELPER-FUNCTIONS

bool hover_check_by_boundaries(const element_rect_boundaries& boundaries)
{
    int curr_x = static_cast<int>(std::round(App_mouse.get_x()));
    int curr_y = static_cast<int>(std::round(App_mouse.get_y()));


    if (curr_x >= boundaries.left_boundary - DELTA_FOR_HOVER_CLICK_CHECKS &&
        curr_x <= boundaries.right_boundary + DELTA_FOR_HOVER_CLICK_CHECKS &&
        curr_y <= boundaries.bottom_boundary + DELTA_FOR_HOVER_CLICK_CHECKS &&
        curr_y >= boundaries.top_boundary - DELTA_FOR_HOVER_CLICK_CHECKS) 
        
        // Mouse inside the element zone 
        return true;
    
    else 

        // Mouse outside the element zone
        return false;
}


// =========================================================================================== HELPER-FUNCTIONS



// =========================================================================================== CONSTRUCTOR AND DESTRUCTOR


My_SDL_element::My_SDL_element()
{
    // Default settings

    this->gui_type = STATIC_ELEMENT_GUI;


    this->x_render_point = 0;
    this->y_render_point = 0;


    this->opacity = 255;
    this->basic_opacity = 255;


    // Basic GUI elements colors setted by pallette (default)
    this->passed_by_pallette = true;
}


// =========================================================================================== CONSTRUCTOR AND DESTRUCTOR


// =========================================================================================== MAIN LOGIC

My_SDL_panel* My_SDL_element::get_element_container() const
{
    return this->element_container;
}

// =========================================================================================== MAIN LOGIC


// =========================================================================================== GUI

// Render point getters 

int My_SDL_element::get_x_render_point() const { return this->x_render_point; }

int My_SDL_element::get_y_render_point() const { return this->y_render_point; }


// Anchor points getter

anchor_points My_SDL_element::get_anchor_points() const
{
    return this->element_anchor_points;
}


// Opacity setter and getter

void My_SDL_element::set_opacity(Uint8 new_opacity) 
{
    this->basic_opacity = new_opacity;
    
    // In case where we got the container
    if (this->element_container != nullptr)
    {
        this->recalculate_opacity_by_container();
    }
    else
    {
        // Equal opacity in case without container
        this->opacity = new_opacity;
    }
}


void My_SDL_element::recalculate_opacity_by_container()
{
    My_SDL_panel* container = this->get_element_container();

    if (!container)
    {
        this->opacity = this->basic_opacity;
        return;
    }

    float result =
        static_cast<float>(this->basic_opacity) *
        static_cast<float>(container->get_opacity()) / 255.0f;

    if (result < 0.0f) result = 0.0f;
    if (result > 255.0f) result = 255.0f;

    this->opacity = static_cast<Uint8>(std::lround(result));
}
 


Uint8 My_SDL_element::get_opacity() const 
{
    return this->opacity;
}


Uint8 My_SDL_element::get_basic_opacity() const 
{
    return this->basic_opacity;
}


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


void My_SDL_element::switch_passed_by_pallette_flag(bool new_status)
{
    this->passed_by_pallette = new_status;
}

// =========================================================================================== GUI
