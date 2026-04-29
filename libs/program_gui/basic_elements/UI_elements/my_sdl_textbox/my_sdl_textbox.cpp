// My_SDL_textbox.cpp


// =========================================================================================== IMPORT

#include "my_sdl_textbox.h"

// Onetime CPP include for remove_element() method providing
#include "../my_sdl_panel/my_sdl_panel.h"

// =========================================================================================== IMPORT


// =========================================================================================== CONSTRUCTOR AND DESTRUCTOR

My_SDL_textbox::My_SDL_textbox()
{
    // Basic settings setter

    // Data

    // Render points

    this->x_render_point = 300;
    this->y_render_point = 300;


    // Font 

    this->font_size = 12; 

    // Relative path to the font file from the executable (can be changed by the setter for the font path)
    this->font_path = absolute_by_relative_from_exe("../../libs/program_gui/basic_elements/content/ttf_fonts/basis33.ttf");
    
    this->ttf_font_link = nullptr;

    if (!ttf_font_link) this->update();

    // Content and sizes set with anchor points reset
    this->set_content("Text");


    // ===== Default pallette =====

    this->set_opacity(255);


    // Basic text colors

    this->set_content_color(hex_to_sdl_color("#4af109", 255));


    this->content_texture = nullptr;

    // Reset flag for the next update in render
    this->content_dirty = true; 
}


void My_SDL_textbox::delete_element()
{
    if (this->element_container != nullptr)
    {
        this->element_container->remove_element(this);
    }
    else
    {
        delete this;
    }
}


My_SDL_textbox::~My_SDL_textbox()
{
    // TODO: Realization with panels linked list clear (both side registration) or just siple comment about 
    // destructor workflow rules - basic destructor from global space or My_SDL_panel.textbox_delete method
    // only for textboxes inside panels

    // Textures destructors
    if (this->content_texture) SDL_DestroyTexture(this->content_texture);

}


// =========================================================================================== CONSTRUCTOR AND DESTRUCTOR



void My_SDL_textbox::update()
{
    // Just font start initialization
    if (this->ttf_font_link == nullptr)
    {
        if(!this->font_path.empty()) this->set_ttf_font_link(TTF_OpenFont(this->font_path.c_str(), this->font_size));
    }

}

//

// =========================================================================================== GUI

void My_SDL_textbox::render(SDL_Renderer* renderer)
{
    // Render logic

    this->update_content_texture(renderer, this->content_render_color);
    
    this->text_draw(renderer);
}


void My_SDL_textbox::set_render_point(int x_cc_rp, int y_cc_rp)
{
    this->x_render_point = x_cc_rp;
    this->y_render_point = y_cc_rp;

    this->reset_anchor_points();
}


unsigned int My_SDL_textbox::get_width_size() const
{
    return this->content_width_size;
}


unsigned int My_SDL_textbox::get_height_size() const
{
    return this->content_height_size;
}



void My_SDL_textbox::set_content(const std::string& new_text)
{
    this->content = new_text;

    if (!this->ttf_font_link)
    {
        std::cerr << "Font not initialized!\n";
        return;
    }

    int w = 0;
    int h = 0;


    // SDL3 AND SDL2 CONFLICT
    if (!TTF_GetStringSize(
            this->ttf_font_link,
            this->content.c_str(),
            this->content.length(),
            &w,
            &h))
    {
        std::cerr << "TTF_GetStringSize failed: " << SDL_GetError() << std::endl;
        return;
    }

    this->content_width_size = w;
    this->content_height_size = h;

    this->reset_anchor_points();

    this->content_dirty = true;
}


void My_SDL_textbox::set_ttf_font_link(TTF_Font* new_ttf_font_link) 
{
    // TODO: Error handling for the invalid links
    if (!new_ttf_font_link)
    {
        std::cerr << "Invalid TTF_Font pointer! Font link not set!" << std::endl;
        return;
    }

    this->ttf_font_link = new_ttf_font_link;
}


void My_SDL_textbox::set_font_path(const std::string& new_font_path)
{
    // TODO: Error handling for the invalid links
    if (new_font_path.empty())
    {
        std::cerr << "Invalid font path! Font path not set!" << std::endl;
        return;
    }

    this->font_path = new_font_path;

    this->set_ttf_font_link(TTF_OpenFont(this->font_path.c_str(), this->font_size));

    if (!this->ttf_font_link)
    {
        SDL_Log("TTF_OpenFont failed: %s", SDL_GetError());
    }
}


std::string My_SDL_textbox::get_font_path() const
{
    return this->font_path;
}


void My_SDL_textbox::set_font_size(unsigned int new_size)
{
    if (new_size == 0)
    {
        std::cerr << "Invalid font size! Font size not set!" << std::endl;
        return;
    }

    this->font_size = new_size;

    // Content is dirty after reset
    this->content_dirty = true;
}


unsigned int My_SDL_textbox::get_font_size() const
{
    return this->font_size;
}


void My_SDL_textbox::set_content_color(SDL_Color new_color)
{
    // Safely check of equivalence
    if (this->content_render_color.r == new_color.r &&
        this->content_render_color.g == new_color.g &&
        this->content_render_color.b == new_color.b &&
        this->content_render_color.a == new_color.a)
    {
        return;     // Return if nothing changed
    }

    this->content_render_color = new_color;

    // Content is dirty after reset
    this->content_dirty = true;
}


void My_SDL_textbox::set_content_texture(SDL_Texture* new_texture)
{
    if (this->content_texture)
        SDL_DestroyTexture(this->content_texture);

    this->content_texture = new_texture;

    // Content is dirty after reset
    this->content_dirty = true;
}


void My_SDL_textbox::reset_anchor_points()
{
    // Uses current crop to set the current anchor points

    // Always the same rounding accuracy, because we work with crop map in initial scale and new scalers
    int half_w = static_cast<int>(std::round(static_cast<float>(this->content_width_size) * 0.5));
    int half_h = static_cast<int>(std::round(static_cast<float>(this->content_height_size) * 0.5));


    // element_anchor_points reset
    
    /**
     * 
     * P P P P P
     * 1 2 3 4 5
     * 
     * center is 3 -> (n + 1) / 2
     *
     */

    int c_w = this->x_render_point;         // Horizontal center
    int c_h = this->y_render_point;         // Vertical center

    // SDL windows points goes from TL(0; 0) to BR(Max_W, Max_H)
    
    this->element_anchor_points.top_left         =     { c_w - half_w, c_h - half_h };
    this->element_anchor_points.top_center       =     { c_w , c_h - half_h };
    this->element_anchor_points.top_right        =     { c_w + half_w, c_h - half_h };

    this->element_anchor_points.center_left      =     { c_w - half_w, c_h };
    this->element_anchor_points.center_center    =     { c_w, c_h };
    this->element_anchor_points.center_right     =     { c_w + half_w, c_h };

    this->element_anchor_points.bottom_left      =     { c_w - half_w, c_h + half_h  };
    this->element_anchor_points.bottom_center    =     { c_w, c_h + half_h };
    this->element_anchor_points.bottom_right     =     { c_w + half_w, c_h + half_h };
}


void My_SDL_textbox::update_content_texture(SDL_Renderer* renderer, SDL_Color new_color)
{
    // SDL ttf workflow

    if (!this->content_dirty) return;


    if (!this->ttf_font_link) 
    {
        std::cerr << "Font load error!" << SDL_GetError() << std::endl;
        return;
    }

    // Empty content check
    if (this->content.empty())
    {
        if (this->content_texture)
        {
            SDL_DestroyTexture(this->content_texture);
            this->content_texture = nullptr;
        }

        this->content_dirty = false;
        return;
    }


    // Old texture clear
    if (this->content_texture)
    {
        SDL_DestroyTexture(this->content_texture);
        this->content_texture = nullptr;
    }


    SDL_Color color = new_color; // By passed pallette 

    SDL_Surface* surface = TTF_RenderText_Blended(
        this->ttf_font_link,
        this->content.c_str(),
        0,
        color
    );

    if (!surface) return;

    this->content_texture = SDL_CreateTextureFromSurface(renderer, surface);

    this->content_width_size = surface->w;
    this->content_height_size = surface->h;

    SDL_DestroySurface(surface);

    this->content_dirty = false;
}


void My_SDL_textbox::text_draw(SDL_Renderer* renderer)
{
    if (this->content_texture)
    {
        SDL_FRect dst;

        dst.w = this->content_width_size;
        dst.h = this->content_height_size;

        dst.x = this->x_render_point - dst.w / 2.0f;
        dst.y = this->y_render_point - dst.h / 2.0f;

        SDL_RenderTexture(renderer, content_texture, nullptr, &dst);
    }
}

// =========================================================================================== GUI
