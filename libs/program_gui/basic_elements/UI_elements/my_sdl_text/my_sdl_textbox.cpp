// my_sdl_text.cpp


// =========================================================================================== IMPORT

#include "my_sdl_textbox.h"

// Onetime CPP include for remove_element() method providing
#include "../my_sdl_panel/my_sdl_panel.h"

// =========================================================================================== IMPORT


// =========================================================================================== CONSTRUCTOR AND DESTRUCTOR

My_SDL_text::My_SDL_textbox()
{
    // Basic settings setter

    // Data

    // Render points

    this->x_render_point = this->button_width_size / 2 + 1;
    this->y_render_point = this->button_height_size / 2 + 1;


    this->reset_boundaries_points();

    // Anchor points
    this->anchor_points_reset();


    // Font 

    this->current_form = ROUNDED_RECTANGLE_EF;

    this->font_size = 12; 

    // Relative path to the font file from the executable (can be changed by the setter for the font path)
    this->font_path = absolute_by_relative_from_exe("../../libs/program_gui/basic_elements/content/ttf_fonts/Amiga_forever_pro.ttf");
    
    this->ttf_font_link = nullptr;

    this->content = "Text";

    
    // Sizes

    this->content_w = 0;                    // TODO: WTF???
    this->content_h = 0;                    // TODO: WTF???

    this->content_dirty = true;


    // ===== Default pallette =====

    this->set_opacity(255);


    // Basic colors

    this->set_shadow_color_1(hex_to_sdl_color("#fd3108", 150));      
    this->set_border_color_1({23, 23, 23, 255});  
    this->set_background_color_1(hex_to_sdl_color("#fd3108", 255));
    this->set_content_color_1({23, 23, 23, 255});


    // Hover colors

    this->set_shadow_color_hovered_1({240, 231, 214, 155});
    this->set_border_color_hovered_1({23, 23, 23, 255});
    this->set_background_color_hovered_1({240, 231, 214, 255});
    this->set_content_color_hovered_1({23, 23, 23, 255});


    // button_clicked colors

    this->set_shadow_color_clicked_1({140, 122, 180, 150});
    this->set_border_color_clicked_1({232, 222, 42, 255});
    this->set_background_color_clicked_1({150, 120, 180, 255}); 
    this->set_content_color_clicked_1({232, 222, 42, 255});


    // Nulled 2nd pallette

    this->set_shadow_color_2({0, 0, 0, 0});
    this->set_border_color_2({0, 0, 0, 0});
    this->set_background_color_2({0, 0, 0, 0});
    this->set_content_color_2({0, 0, 0, 0});

    this->set_shadow_color_hovered_2({0, 0, 0, 0});
    this->set_border_color_hovered_2({0, 0, 0, 0});
    this->set_background_color_hovered_2({0, 0, 0, 0});
    this->set_content_color_hovered_2({0, 0, 0, 0});

    this->set_shadow_color_clicked_2({0, 0, 0, 0});
    this->set_border_color_clicked_2({0, 0, 0, 0});
    this->set_background_color_clicked_2({0, 0, 0, 0});
    this->set_content_color_clicked_2({0, 0, 0, 0});


    this->current_pallette_number = 1;

    content_texture = nullptr;
}