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
    // TODO: Realization with panels linked list clear (both side registration) or just siple comment about 
    // destructor workflow rules - basic destructor from global space or My_SDL_panel.button_delete method
    // only for buttons inside panels
}

// =========================================================================================== CONSTRUCTOR AND DESTRUCTOR


// =========================================================================================== MAIN LOGIC

void My_SDL_button::update()
{
    // Hover check
    this->hover_check();

    // Hover logic
    if (this->hovered)
    {
        // Hover logic by the callback
        if (this->on_hover) this->on_hover();

        // New click or release check  
        this->click_check();
    }
    else
    {
        // Clicked flags reset with hover ending (blocks the click logic without hovering)
        this->clicked = false;
        this->clicked_tmp = false; 
    }


    // Click with hover check with the click permission logic by the button access type


    if (this->click_access_type == BUTTON_DEFAULT_CLICK_PERMISSION)
        if (this->hovered && this->clicked)
            if (!this->clicked_tmp) this->clicked_tmp = true;

    // There can not be anything instead of BUTTON_EXTERN_CLICK_PERMISSION
    else
    {
        // Permission check by the callback
        if (this->extern_click_permission)
        {
            this->click_permission = this->extern_click_permission();

            // Clicked logic by the callback if the permission obtained
            if (this->click_permission)
                if (this->hovered && this->clicked)
                    // Clicked logic by the callback
                    if (!this->clicked_tmp) this->clicked_tmp = true;

        }
        else 
        {
            // Error handler
            std::cerr << "No callback for the button access status check! Click can't be handled!" << std::endl;
        }
    }

    // If we press and then release - reset permission
    if (!this->clicked && this->clicked_tmp) 
    {
        // One callback call after release
        if (this->click_access_type == BUTTON_DEFAULT_CLICK_PERMISSION || this->click_permission)
            if (this->on_click) this->on_click();

        // Block repeats and reset
        this->clicked_tmp = false;
    }
}


void My_SDL_button::set_access_type(button_access_type new_access_type)
{
    // Error handling for invalid access type
    if (new_access_type != BUTTON_DEFAULT_CLICK_PERMISSION && new_access_type != BUTTON_EXTERN_CLICK_PERMISSION)
    {
        std::cerr << "Invalid button access type. Access type not changed." << std::endl;
    }

    // New type setting
    else this->click_access_type = new_access_type;
}





// =========================================================================================== MAIN LOGIC



// =========================================================================================== GUI


// =========================================================================================== GUI