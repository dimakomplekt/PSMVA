// my_sdl_panel.cpp


// =========================================================================================== IMPORT

#include "my_sdl_panel.h"
#include "../../GUI_functions/drawing/figures_drawing.h" // For drawing functions
#include <algorithm>                                     // For std::remove_if

// =========================================================================================== IMPORT


// =========================================================================================== CONSTRUCTOR AND DESTRUCTOR

My_SDL_panel::My_SDL_panel()
    : My_SDL_element(),
      panel_width_size(100),
      panel_height_size(100),
      border_width_size(1),
      border_radius_size(0),
      shadow_offset_x(2),
      shadow_offset_y(2),
      shadow_scale_factor(1.0f),
      background_color({200, 200, 200, 255}),
      border_color({0, 0, 0, 255}),
      shadow_color({0, 0, 0, 128}),
      inner_elements()
{
    // Basic settings setter
}

// =========================================================================================== CONSTRUCTOR AND DESTRUCTOR


// =========================================================================================== MAIN LOGIC

void My_SDL_panel::update()
{
    // Update all inner elements
    for (auto& inner : inner_elements)
    {
        inner.element_pointer->update();
    }
}

// =========================================================================================== MAIN LOGIC


// =========================================================================================== GUI

void My_SDL_panel::render(SDL_Renderer* renderer)
{
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
}

void My_SDL_panel::set_render_point(int x_cc_rp, int y_cc_rp)
{
    // Set panel position
    My_SDL_element::set_render_point(x_cc_rp, y_cc_rp);

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

void My_SDL_panel::set_background_color(SDL_Color new_color)
{
    background_color = new_color;
}

void My_SDL_panel::set_border_color(SDL_Color new_color)
{
    border_color = new_color;
}

void My_SDL_panel::set_shadow_color(SDL_Color new_color)
{
    shadow_color = new_color;
}

// =========================================================================================== GUI


// =========================================================================================== PANEL SPECIFIC

void My_SDL_panel::add_element(My_SDL_element* element_pointer, int local_x, int local_y)
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
