// my_sdl_texture.cpp

// =========================================================================================== IMPORT

#include "my_sdl_texture.h"

// Onetime CPP include for remove_element() method providing
#include "../my_sdl_panel/my_sdl_panel.h"

// =========================================================================================== IMPORT



// =========================================================================================== CONSTRUCTOR AND DESTRUCTOR

My_SDL_texture::My_SDL_texture()
{
    this->texture = nullptr;

    this->width_size = 0;
    this->height_size = 0;

    this->x_render_point = 0;
    this->y_render_point = 0;

    this->reset_anchor_points();
}


My_SDL_texture::~My_SDL_texture()
{
    // Texture destructor
    if (this->texture != nullptr)
    {
        SDL_DestroyTexture(this->texture);
        this->texture = nullptr;
    }
}


void My_SDL_texture::delete_element()
{
    My_SDL_panel* container = this->get_element_container();

    // Delete itself by upper level panel or by itself
    if (container)
    {
        container->remove_element(this);
    }
    else
    {
        delete this;
    }
}

// =========================================================================================== CONSTRUCTOR AND DESTRUCTOR



// =========================================================================================== MAIN LOGIC

void My_SDL_texture::update()
{
    // Nothing now
}

// =========================================================================================== MAIN LOGIC



// =========================================================================================== GUI

void My_SDL_texture::render(SDL_Renderer* renderer)
{
    if (this->texture == nullptr) return;

    SDL_FRect dst;

    dst.w = static_cast<float>(this->width_size);
    dst.h = static_cast<float>(this->height_size);

    dst.x = static_cast<float>(this->x_render_point) - dst.w / 2.0f;
    dst.y = static_cast<float>(this->y_render_point) - dst.h / 2.0f;

    // TODO: check double opacity change in panel
    SDL_SetTextureAlphaMod(this->texture, this->opacity);

    SDL_RenderTexture(renderer, this->texture, nullptr, &dst);
}


void My_SDL_texture::set_render_point(int x_cc_rp, int y_cc_rp)
{
    this->x_render_point = x_cc_rp;
    this->y_render_point = y_cc_rp;


    this->reset_anchor_points();
}


unsigned int My_SDL_texture::get_width_size() const
{
    return this->width_size;
}


unsigned int My_SDL_texture::get_height_size() const
{
    return this->height_size;
}


void My_SDL_texture::set_texture(SDL_Texture* new_texture)
{
    if (this->texture != nullptr)
    {
        SDL_DestroyTexture(this->texture);
        this->texture = nullptr;
    }

    this->texture = new_texture;

    // Error handler
    if (this->texture == nullptr)
    {
        this->width_size = 0;
        this->height_size = 0;
        this->reset_anchor_points();
        return;
    }

    // Sizes recalculation 

    float w = 0.0f;
    float h = 0.0f;

    SDL_GetTextureSize(this->texture, &w, &h);

    this->width_size = static_cast<int>(std::round(w));
    this->height_size = static_cast<int>(std::round(h));

    
    this->reset_anchor_points();
}


void My_SDL_texture::reset_anchor_points()
{
    int half_w = static_cast<int>(std::round(this->width_size * 0.5f));
    int half_h = static_cast<int>(std::round(this->height_size * 0.5f));

    int c_w = this->x_render_point;
    int c_h = this->y_render_point;

    this->element_anchor_points.top_left         = { c_w - half_w, c_h - half_h };
    this->element_anchor_points.top_center       = { c_w,          c_h - half_h };
    this->element_anchor_points.top_right        = { c_w + half_w, c_h - half_h };

    this->element_anchor_points.center_left      = { c_w - half_w, c_h };
    this->element_anchor_points.center_center    = { c_w,          c_h };
    this->element_anchor_points.center_right     = { c_w + half_w, c_h };

    this->element_anchor_points.bottom_left      = { c_w - half_w, c_h + half_h };
    this->element_anchor_points.bottom_center    = { c_w,          c_h + half_h };
    this->element_anchor_points.bottom_right     = { c_w + half_w, c_h + half_h };
}

// =========================================================================================== GUI