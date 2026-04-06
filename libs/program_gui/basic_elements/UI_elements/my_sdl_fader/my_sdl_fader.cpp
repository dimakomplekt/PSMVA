// my_sdl_fader.cpp


// =========================================================================================== IMPORT

#include "my_sdl_fader.h"

// =========================================================================================== IMPORT


// =========================================================================================== CONSTRUCTOR AND DESTRUCTOR

My_SDL_fader::My_SDL_fader()
{
    // Basic settings setter

    // Data

    this->fader_value = 0.5f;

    // Control flags

    this->slot_hovered = false;
    this->slot_clicked = false;
    this->slot_clicked_tmp = false;
    this->current_slot_state = DEFAULT_ES;

    this->knob_hovered = false;
    this->knob_clicked = false;
    this->knob_clicked_tmp = false;
    this->current_knob_state = DEFAULT_ES;


    this->push_mode_on = true;
    this->press_offset = 0;

    // Sizes

    this->set_slot_size(120, 20);

    this->set_knob_size(20, 40);

    this->slot_border_width_size = 2;
    this->slot_border_radius_size = 5;

    this->knob_border_width_size = 2;
    this->knob_border_radius_size = 5;


    this->set_slot_shadow_offset(3, -2);
    this->slot_shadow_scale_factor = 1.0f;

    this->set_knob_shadow_offset(3, -2);
    this->knob_shadow_scale_factor = 1.0f;


    this->slot_current_form = ROUNDED_RECTANGLE_EF;
    this->knob_current_form = ROUNDED_RECTANGLE_EF;


    // Render points

    this->slot_x_render_point = this->slot_width_size / 2 + 1;
    this->slot_y_render_point = this->slot_height_size / 2 + 1;


    this->knob_x_render_point = this->knob_position_by_fader_value();
    this->knob_y_render_point = this->slot_y_render_point;


    // Boarders

    this->reset_knob_boundaries_points();
    this->reset_slot_boundaries_points();


    // Pallette

    this->set_opacity(255);


    // Basic colors

    this->set_slot_shadow_color(hex_to_sdl_color("#fd3108", 150));          // #fd3108
    this->set_slot_border_color({23, 23, 23, 255});
    this->set_slot_background_color(hex_to_sdl_color("#fd3108", 255));      // #fd3108

    this->set_slot_shadow_color_hovered({240, 231, 214, 155});
    this->set_slot_border_color_hovered({23, 23, 23, 255});
    this->set_slot_background_color_hovered({240, 231, 214, 255});

    this->set_slot_shadow_color_clicked({140, 122, 180, 150});
    this->set_slot_border_color_clicked({232, 222, 42, 255});
    this->set_slot_background_color_clicked({150, 120, 180, 255});



    this->set_knob_shadow_color(hex_to_sdl_color("#fd3108", 150));          // #fd3108
    this->set_knob_border_color({23, 23, 23, 255});                       
    this->set_knob_background_color(hex_to_sdl_color("#fd3108", 255));      // #fd3108

    this->set_knob_shadow_color_hovered({240, 231, 214, 155});
    this->set_knob_border_color_hovered({23, 23, 23, 255});
    this->set_knob_background_color_hovered({240, 231, 214, 255});
    
    this->set_knob_shadow_color_clicked({140, 122, 180, 150});
    this->set_knob_border_color_clicked({232, 222, 42, 255});
    this->set_knob_background_color_clicked({150, 120, 180, 255});


    // Initial render pallette setup

    this->slot_render_shadow_color = this->slot_shadow_color;
    this->slot_render_border_color = this->slot_border_color;
    this->slot_render_background_color = this->slot_background_color;

    this->knob_render_shadow_color = this->knob_shadow_color;
    this->knob_render_border_color = this->knob_border_color;
    this->knob_render_background_color = this->knob_background_color;
}


// =========================================================================================== CONSTRUCTOR AND DESTRUCTOR


// =========================================================================================== MAIN LOGIC

float My_SDL_fader::get_fader_value() const
{
    return this->fader_value;
}

void My_SDL_fader::update() override
{
    // Slot hover check
    this->slot_hover_check();

    // Knob hover check
    this->knob_hover_check();


    // Slot hover logic - if slot is hovered and knob not hovered - we set the slot state as HOVERED and start to check mouse LB-click 

    if (this->slot_hovered && !this->knob_hovered)
    {   
        // Block the hover-click GUI conflict
        if(!this->slot_clicked_tmp)
            this->current_slot_state = HOVERED_ES;

        // New click or release check  
        this->slot_clicked = lb_click_check();
    }

    // Knob hover logic - if knob is hovered - we set the both knob and slot states as HOVERED and start to check the mouse LB-click

    else if (this->knob_hovered)
    {
        // Block the hover-click GUI conflict
        if (!this->knob_clicked_tmp)
        {
            this->current_slot_state = DEFAULT_ES;
            this->current_knob_state = HOVERED_ES;
        }

        // New click or release check  
        this->knob_clicked = lb_click_check();
    }

    else
    {
        // Clicked flags reset with hover ending (blocks the click logic without hovering)
        this->slot_clicked = false;
        this->slot_clicked_tmp = false; 

        if (!this->slot_clicked_tmp) // Only without press
            this->current_slot_state = DEFAULT_ES;


        // Clicked flags reset with hover ending (blocks the click logic without hovering)
        this->knob_clicked = false;
        this->knob_clicked_tmp = false; 

        if (!this->knob_clicked_tmp) // Only without press
            this->current_knob_state = DEFAULT_ES;
    }

    // If we click inside the slot zone and then release - just set the new pallete, then new values, then reset everything to default state
    // If we click inside the slot zone and then hold - we must moove to the zone where we click and follow the mouse x-position by the slot center
    // So the logic of 2 cases could be mixed only in the logic of second case

    // Furthemore - if we click inside the knob zone - we must act like in the 2nd case, but only with exeption. that we don't need to instantly
    // change the position of the knob by the small deltas between current knob center x-coordinate and the x-coordinate inside the knob zone, 
    // which was detected with the click - just moove the knob with taking of this delta into account
      
}


void My_SDL_fader::push_mode_switch()
{
    this->push_mode_on = !this->push_mode_on;
}



// =========================================================================================== MAIN LOGIC




// =========================================================================================== GUI



// =========================================================================================== GUI
