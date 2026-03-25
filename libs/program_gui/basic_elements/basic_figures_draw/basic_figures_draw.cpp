// basic_figures_draw.cpp

// =========================================================================================== IMPORT

#include "basic_figures_draw.h"

// =========================================================================================== IMPORT



// =========================================================================================== RECTANGLE

void rectangle_draw(
    
    int x_render_point,
    int y_render_point,

    unsigned int width,
    unsigned int height,

    SDL_Color color,

    SDL_Renderer* renderer

)
{
    if (width < 1 || height < 1)
    {
        return;
    }

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    int center_x = x_render_point;
    int center_y = y_render_point;

    int rect_width  = static_cast<int>(width);
    int rect_height = static_cast<int>(height);

    SDL_FRect rect;

    // Center-center
    rect.x = center_x - rect_width  / 2;
    rect.y = center_y - rect_height / 2;

    rect.w = rect_width;
    rect.h = rect_height;

    SDL_RenderFillRect(renderer, &rect);
}

// =========================================================================================== RECTANGLE



// =========================================================================================== ROUNDED RECTANGLE

void rounded_rectangle_draw(
    
    int x_render_point,
    int y_render_point,

    unsigned int width,
    unsigned int height,

    unsigned int radius,

    SDL_Color color,

    SDL_Renderer* renderer

)
{
    if (width < 3 || height < 3)
    {
        return;
    }

    if (radius == 0)
    {
        rectangle_draw(x_render_point, y_render_point, width, height, color, renderer);
        return;
    }

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    int center_x = x_render_point;
    int center_y = y_render_point;

    int rect_width  = static_cast<int>(width);
    int rect_height = static_cast<int>(height);
    int corner_radius = static_cast<int>(radius);

    // Clamp radius
    int max_radius = std::min((rect_width - 1) / 2, (rect_height - 1) / 2);

    if (corner_radius > max_radius)
    {
        corner_radius = max_radius;
    }

    int half_width  = rect_width  / 2;
    int half_height = rect_height / 2;

    // ========================= CENTER

    SDL_FRect center_rect{

        static_cast<float>(center_x - half_width + corner_radius),
        static_cast<float>(center_y - half_height),
        static_cast<float>(rect_width - 2 * corner_radius),
        static_cast<float>(rect_height)

    };


    SDL_RenderFillRect(renderer, &center_rect);

    // ========================= SIDES

    SDL_FRect left_rect{

        static_cast<float>(center_x - half_width),
        static_cast<float>(center_y - half_height + corner_radius),
        static_cast<float>(corner_radius),
        static_cast<float>(rect_height - 2 * corner_radius)

    };

    SDL_RenderFillRect(renderer, &left_rect);

    SDL_FRect right_rect{

        static_cast<float>(center_x + half_width - corner_radius),
        static_cast<float>(center_y - half_height + corner_radius),
        static_cast<float>(corner_radius),
        static_cast<float>(rect_height - 2 * corner_radius)

    };

    SDL_RenderFillRect(renderer, &right_rect);

    // ========================= CORNERS

    int diameter = corner_radius * 2;

    for (int x = 0; x < diameter; x++)
    {
        for (int y = 0; y < diameter; y++)
        {
            int dx = x - corner_radius;
            int dy = y - corner_radius;

            // 1 full circle in 4 different places
            if (dx * dx + dy * dy <= corner_radius * corner_radius)
            {
                // Left top
                SDL_RenderPoint(renderer,
                    static_cast<float>(center_x - half_width + corner_radius + dx),
                    static_cast<float>(center_y - half_height + corner_radius + dy));

                // Right top
                SDL_RenderPoint(renderer,
                    static_cast<float>(center_x + half_width - corner_radius + dx),
                    static_cast<float>(center_y - half_height + corner_radius + dy));

                // Left bottom
                SDL_RenderPoint(renderer,
                    static_cast<float>(center_x - half_width + corner_radius + dx),
                    static_cast<float>(center_y + half_height - corner_radius + dy));

                // Right bottom
                SDL_RenderPoint(renderer,
                    static_cast<float>(center_x + half_width - corner_radius + dx),
                    static_cast<float>(center_y + half_height - corner_radius + dy));
            }
        }
    }
}

// =========================================================================================== ROUNDED RECTANGLE



// =========================================================================================== CIRCLE

void circle_draw(
    
    int x_render_point,
    int y_render_point,

    unsigned int radius,

    SDL_Color color,

    SDL_Renderer* renderer
)
{
    if (radius == 0)
    {
        return;
    }

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    int center_x = x_render_point;
    int center_y = y_render_point;

    int circle_radius = static_cast<int>(radius);

    for (int dx = -circle_radius; dx <= circle_radius; dx++)
    {
        for (int dy = -circle_radius; dy <= circle_radius; dy++)
        {
            if (dx * dx + dy * dy <= circle_radius * circle_radius)
            {
                SDL_RenderPoint(renderer, static_cast<float>(center_x + dx), static_cast<float>(center_y + dy));
            }
        }
    }
}

// =========================================================================================== CIRCLE