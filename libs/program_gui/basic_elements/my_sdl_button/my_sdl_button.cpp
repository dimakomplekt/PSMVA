// my_sdl_button.cpp

// =========================================================================================== IMPORT

#include "my_sdl_button.h"

// =========================================================================================== IMPORT


// =========================================================================================== CONSTRUCTOR AND DESTRUCTOR

My_SDL_button::My_SDL_button()
{
    // Basic settings setter

    // Types

    this->set_access_type(BUTTON_DEFAULT_CLICK_PERMISSION);

    this->set_gui_type(STATIC_BUTTON_GUI);


    // Callbacks nullptr

    this->extern_click_permission = nullptr;
    this->on_hover = nullptr;
    this->on_click = nullptr;
    this->pallette_switch = nullptr;

    // Data
    this->hovered = false;

    this->click_permission = true;
    this->clicked = false;
    this->clicked_tmp = false;

    this->set_size(100, 50);
    this->boarder_size = 5;
    this->boarder_radius = 0;

    this->set_shadow_offset(5, -5);
    this->shadow_scale_factor = 1.0f;


    this->font_size = 10; 

    this->ttf_font_link = nullptr;
    this->font_path = "";

    this->content = "";


    // ===== Default pallette =====

    this->set_opacity(255);


    this->set_background_color_1({220, 220, 220, 255});
    this->set_border_color_1({50, 50, 50, 255});
    this->set_content_color_1({30, 30, 30, 255});
    this->set_shadow_color_1({200, 200, 200, 255});

    this->set_background_color_hovered_1({200, 200, 200, 255});
    this->set_border_color_hovered_1({70, 70, 70, 255});
    this->set_content_color_hovered_1({50, 50, 50, 255});
    this->set_shadow_color_hovered_1({180, 180, 180, 255});

    this->set_background_color_clicked_1({180, 180, 180, 255});
    this->set_border_color_clicked_1({90, 90, 90, 255});
    this->set_content_color_clicked_1({70, 70, 70, 255});
    this->set_shadow_color_clicked_1({160, 160, 160, 255});


    // Nulled 2nd pallette
    this->set_background_color_2({0, 0, 0, 0});
    this->set_border_color_2({0, 0, 0, 0});
    this->set_content_color_2({0, 0, 0, 0});
    this->set_shadow_color_2({0, 0, 0, 0});

    this->set_background_color_hovered_2({0, 0, 0, 0});
    this->set_border_color_hovered_2({0, 0, 0, 0});
    this->set_content_color_hovered_2({0, 0, 0, 0});
    this->set_shadow_color_hovered_2({0, 0, 0, 0});

    this->set_background_color_clicked_2({0, 0, 0, 0});
    this->set_border_color_clicked_2({0, 0, 0, 0});
    this->set_content_color_clicked_2({0, 0, 0, 0});
    this->set_shadow_color_clicked_2({0, 0, 0, 0});


    this->current_pallette_number = 1;

    // Textures nullptr

    background_texture = nullptr;
    border_texture = nullptr;
    content_texture_renderer = nullptr;
    content_texture = nullptr;
}


My_SDL_button::~My_SDL_button()
{
    // TODO: Realization with panels linked list clear
}

// =========================================================================================== CONSTRUCTOR AND DESTRUCTOR


// =========================================================================================== MAIN LOGIC


// =========================================================================================== MAIN LOGIC



// =========================================================================================== GUI


// =========================================================================================== GUI