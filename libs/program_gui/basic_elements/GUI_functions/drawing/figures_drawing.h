// figures_drawing.h

#pragma once

// =========================================================================================== IMPORT

#include "../../../engine/engine.h"     // SDL3 and SDL ttf import

#include <algorithm>                    // For std::min()

// =========================================================================================== IMPORT


enum element_form
{

    RECTANGLE_EF,       
    ROUNDED_RECTANGLE_EF,
    CIRCLE_EF       

};


void rectangle_draw_by_color(
    
    int x_render_point,
    int y_render_point,

    unsigned int width,
    unsigned int height,

    SDL_Color color,

    SDL_Renderer* renderer

);


void rectangle_draw_by_texture(

    int x_render_point,
    int y_render_point,

    unsigned int width,
    unsigned int height,

    SDL_Texture* texture,

    SDL_Renderer* renderer

);



void rounded_rectangle_draw_by_color(
    
    int x_render_point,
    int y_render_point,

    unsigned int width,
    unsigned int height,

    unsigned int radius,

    SDL_Color color,

    SDL_Renderer* renderer

);


void rounded_rectangle_draw_by_texture(

    int x_render_point,
    int y_render_point,

    unsigned int width,
    unsigned int height,

    unsigned int radius,

    SDL_Texture* texture,

    SDL_Renderer* renderer
);


void circle_draw_by_color(

    int x_render_point,
    int y_render_point,

    unsigned int radius,

    SDL_Color color,

    SDL_Renderer* renderer
    
);

void circle_draw_by_texture(

    int x_render_point,
    int y_render_point,

    unsigned int radius,

    SDL_Texture* texture,

    SDL_Renderer* renderer

);
