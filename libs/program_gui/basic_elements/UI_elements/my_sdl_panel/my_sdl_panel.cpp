// my_sdl_panel.cpp


// =========================================================================================== IMPORT

#include "my_sdl_panel.h"
#include <algorithm>                                     // For std::remove_if

// =========================================================================================== IMPORT


// =========================================================================================== CONSTRUCTOR AND DESTRUCTOR

My_SDL_panel::My_SDL_panel()
{
    // Basic settings setter
    this->panel_width_size = 100;
    this->panel_height_size = 100;

    this->x_render_point = panel_width_size / 2 + 1;
    this->y_render_point = panel_height_size / 2 + 1;

    this->border_width_size = 1;
    this->border_radius_size = 0;

    this->shadow_offset_x = 2;
    this->shadow_offset_y = 2;
    this->shadow_scale_factor = 1.0f;

    this->set_panel_background_color(hex_to_sdl_color("#fd3108", 250));
    this->set_panel_border_color(hex_to_sdl_color("#8af520", 250));
    this->set_panel_shadow_color(hex_to_sdl_color("#d400ff", 250));

    this->inner_elements.clear();
}


void My_SDL_panel::on_destroy()
{
    // что-то или даже пусто
}

// =========================================================================================== CONSTRUCTOR AND DESTRUCTOR


// =========================================================================================== MAIN LOGIC

void My_SDL_panel::update()
{
    // Just update all inner elements by auto type link and overrided update() methods
    for (auto& inner : inner_elements)
    {
        inner.element_pointer->update();
    }
}

// =========================================================================================== MAIN LOGIC


// =========================================================================================== GUI

void My_SDL_panel::render(SDL_Renderer* renderer)
{
    /*
    // Calculate panel boundaries
    int left_boundary = x_render_point - static_cast<int>(panel_width_size) / 2;
    int right_boundary = x_render_point + static_cast<int>(panel_width_size) / 2;
    int top_boundary = y_render_point - static_cast<int>(panel_height_size) / 2;
    int bottom_boundary = y_render_point + static_cast<int>(panel_height_size) / 2;

    // Draw shadow if scale factor > 0
    if (shadow_scale_factor > 0.0f)
    {
        SDL_Color shadow_color_with_opacity = shadow_color;
        shadow_color_with_opacity.a = static_cast<Uint8>(shadow_color.a * opacity / 255.0f);

        int shadow_left = left_boundary + shadow_offset_x;
        int shadow_top = top_boundary + shadow_offset_y;
        int shadow_width = panel_width_size;
        int shadow_height = panel_height_size;

        draw_filled_rounded_rect(renderer, shadow_left, shadow_top, shadow_width, shadow_height, border_radius_size, shadow_color_with_opacity);
    }

    // Draw background
    SDL_Color background_color_with_opacity = background_color;
    background_color_with_opacity.a = static_cast<Uint8>(background_color.a * opacity / 255.0f);

    draw_filled_rounded_rect(renderer, left_boundary, top_boundary, panel_width_size, panel_height_size, border_radius_size, background_color_with_opacity);

    // Draw border if width > 0
    if (border_width_size > 0)
    {
        SDL_Color border_color_with_opacity = border_color;
        border_color_with_opacity.a = static_cast<Uint8>(border_color.a * opacity / 255.0f);

        draw_rounded_rect(renderer, left_boundary, top_boundary, panel_width_size, panel_height_size, border_radius_size, border_width_size, border_color_with_opacity);
    }

    // Render all inner elements with adjusted positions
    for (auto& inner : inner_elements)
    {
        int absolute_x = x_render_point + inner.local_x_position;
        int absolute_y = y_render_point + inner.local_y_position;
        inner.element_pointer->set_render_point(absolute_x, absolute_y);
        inner.element_pointer->render(renderer);
    }

    // Render the panel


    // Render the elements by the z-order (just gothrough the vector it's already sorted)


    */
}

void My_SDL_panel::set_render_point(int x_cc_rp, int y_cc_rp)
{
    // Set panel position
    this->x_render_point = x_cc_rp;
    this->y_render_point = y_cc_rp;

    // Update inner elements positions (though they will be set again in render, this ensures consistency)
    for (auto& inner : inner_elements)
    {
        int absolute_x = x_render_point + inner.local_x_position;
        int absolute_y = y_render_point + inner.local_y_position;
        inner.element_pointer->set_render_point(absolute_x, absolute_y);
    }
}


// Size setters and getters

void My_SDL_panel::set_size(unsigned int new_width, unsigned int new_height)
{
    panel_width_size = new_width;
    panel_height_size = new_height;
}

unsigned int My_SDL_panel::get_width_size() const { return panel_width_size; }

unsigned int My_SDL_panel::get_height_size() const { return panel_height_size; }


// Styling setters

void My_SDL_panel::set_border_width_size(unsigned int new_size)
{
    border_width_size = new_size;
}

void My_SDL_panel::set_border_radius_size(unsigned int new_radius_size)
{
    border_radius_size = new_radius_size;
}

void My_SDL_panel::set_shadow_offset(int new_x_offset, int new_y_offset)
{
    shadow_offset_x = new_x_offset;
    shadow_offset_y = new_y_offset;
}

void My_SDL_panel::set_shadow_scale_factor(float new_scale_factor)
{
    shadow_scale_factor = new_scale_factor;
}


// Color setters

void My_SDL_panel::set_panel_background_color(SDL_Color new_color)
{
    background_color = new_color;
}

void My_SDL_panel::set_panel_border_color(SDL_Color new_color)
{
    border_color = new_color;
}

void My_SDL_panel::set_panel_shadow_color(SDL_Color new_color)
{
    shadow_color = new_color;
}


void My_SDL_panel::anchor_points_reset()
{
    
    /**
     * 
     * P P P P P
     * 1 2 3 4 5
     * 
     * center is 3 -> (n + 1) / 2
     *
     */

    /*

    // Uses current crop to set the current anchor points

    // Always the same rounding accuracy, because we work with crop map in initial scale and new scalers
    unsigned int half_w = static_cast<unsigned int>(std::round(static_cast<float>(this->slot_width_size) * 0.5));
    unsigned int half_h = static_cast<unsigned int>(std::round(static_cast<float>(this->slot_height_size) * 0.5));

    // element_anchor_points reset


    unsigned int c_w = this->slot_x_render_point;         // Horizontal center
    unsigned int c_h = this->slot_y_render_point;         // Vertical center


    // SDL windows points goes from TL(0; 0) to BR(Max_W, Max_H)
    
    this->element_anchor_points.top_left     = { c_w - half_w, c_h - half_h };
    this->element_anchor_points.top_center   = { c_w , c_h - half_h };
    this->element_anchor_points.top_right    = { c_w + half_w, c_h - half_h };

    this->element_anchor_points.center_left  = { c_w - half_w, c_h };
    this->element_anchor_points.center_center= { c_w, c_h };
    this->element_anchor_points.center_right = { c_w + half_w, c_h };

    this->element_anchor_points.bottom_left  = { c_w - half_w, c_h + half_h  };
    this->element_anchor_points.bottom_center= { c_w, c_h + half_h };
    this->element_anchor_points.bottom_right = { c_w + half_w, c_h + half_h };

    */
}


// =========================================================================================== GUI


// =========================================================================================== PANEL SPECIFIC

void My_SDL_panel::add_element(My_SDL_element* element_pointer, int local_x, int local_y, unsigned int local_z)
{
    panel_inner_element new_inner = {element_pointer, local_x, local_y};
    inner_elements.push_back(new_inner);
}


void My_SDL_panel::remove_element(My_SDL_element* element_pointer)
{
    inner_elements.erase(
        std::remove_if(inner_elements.begin(), inner_elements.end(),
            [element_pointer](const panel_inner_element& inner) {
                return inner.element_pointer == element_pointer;
            }),
        inner_elements.end());
}


void My_SDL_panel::clear_elements()
{
    inner_elements.clear();
}

// =========================================================================================== PANEL SPECIFIC
