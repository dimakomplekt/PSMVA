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

    this->slot_x_render_point = this->slot_width_size / 2 + 1 + DELTA_FOR_HOVER_CLICK_CHECKS;
    this->slot_y_render_point = this->slot_height_size / 2 + 1 + DELTA_FOR_HOVER_CLICK_CHECKS;


    this->knob_x_render_point = this->knob_position_by_fader_value();
    this->knob_y_render_point = this->slot_y_render_point;


    // Boarders

    this->reset_knob_boundaries_points();
    this->reset_slot_boundaries_points();


    // Pallette

    this->set_opacity(255);

    // Basic colors

    this->set_slot_shadow_color(hex_to_sdl_color("#fd3108", 150));          // #fd3108
    this->set_slot_border_color({23, 23, 23, 255});                         // #f0e7d6
    this->set_slot_background_color(hex_to_sdl_color("#fd3108", 255));      // #fd3108

    this->set_slot_shadow_color_hovered({240, 231, 214, 155});
    this->set_slot_border_color_hovered({23, 23, 23, 255});
    this->set_slot_background_color_hovered({240, 231, 214, 255});

    this->set_slot_shadow_color_clicked({140, 122, 180, 150});
    this->set_slot_border_color_clicked({232, 222, 42, 255});
    this->set_slot_background_color_clicked({150, 120, 180, 255});



    this->set_knob_shadow_color(hex_to_sdl_color("#fd3108", 150));          // #fd3108
    this->set_knob_border_color({23, 23, 23, 255});                         // #f0e7d6
    this->set_knob_background_color(hex_to_sdl_color("#fd3108", 255));      // #fd3108

    this->set_knob_shadow_color_hovered({240, 231, 214, 155});
    this->set_knob_border_color_hovered({23, 23, 23, 255});
    this->set_knob_background_color_hovered({240, 231, 214, 255});
    
    this->set_knob_shadow_color_clicked({140, 122, 180, 150});
    this->set_knob_border_color_clicked({232, 222, 42, 255});
    this->set_knob_background_color_clicked({150, 120, 180, 255});


}


// =========================================================================================== CONSTRUCTOR AND DESTRUCTOR