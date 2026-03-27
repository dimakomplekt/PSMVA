// basic_figures_draw.cpp

// =========================================================================================== IMPORT

#include "basic_figures_draw.h"

// =========================================================================================== IMPORT



// =========================================================================================== RECTANGLE

void rectangle_draw_by_color(
    
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


void rectangle_draw_by_texture(

    int x_render_point,
    int y_render_point,

    unsigned int width,
    unsigned int height,

    SDL_Texture* texture,

    SDL_Renderer* renderer

)
{
    if (!texture || width < 1 || height < 1) return;

    SDL_FRect rect;

    rect.w = static_cast<float>(width);
    rect.h = static_cast<float>(height);
    rect.x = static_cast<float>(x_render_point - width / 2);
    rect.y = static_cast<float>(y_render_point - height / 2);

    SDL_RenderTexture(renderer, texture, nullptr, &rect);
}


// =========================================================================================== RECTANGLE



// =========================================================================================== ROUNDED RECTANGLE

void rounded_rectangle_draw_by_color(
    
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
        rectangle_draw_by_color(x_render_point, y_render_point, width, height, color, renderer);
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



void rounded_rectangle_draw_by_texture(

    int x_render_point,
    int y_render_point,

    unsigned int width,
    unsigned int height,

    unsigned int radius,

    SDL_Texture* texture,

    SDL_Renderer* renderer)
{
    if (!texture || width < 3 || height < 3) return;

    // Если радиус 0, просто растягиваем текстуру на весь прямоугольник
    if (radius == 0)
    {
        SDL_FRect rect{
            static_cast<float>(x_render_point - width / 2),
            static_cast<float>(y_render_point - height / 2),
            static_cast<float>(width),
            static_cast<float>(height)
        };
        SDL_RenderTexture(renderer, texture, nullptr, &rect);
        return;
    }

    // ---------------------- Создаём рендер-таргет

    SDL_Texture* target = SDL_CreateTexture(

        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        width,
        height

    );

    if (!target) return;

    // Сохраняем старый таргет

    SDL_Texture* old_target = SDL_GetRenderTarget(renderer);

    SDL_SetRenderTarget(renderer, target);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    // ---------------------- Рендерим текстуру на весь таргет
    SDL_FRect full_rect{0.0f, 0.0f, static_cast<float>(width), static_cast<float>(height)};
    SDL_RenderTexture(renderer, texture, nullptr, &full_rect);

    // ---------------------- Рендерим маску скруглённых углов
    // Маска: просто затираем прозрачным цветом углы
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // прозрачный
    int diameter = radius * 2;
    for (int dx = 0; dx < diameter; dx++)
    {
        for (int dy = 0; dy < diameter; dy++)
        {
            if (dx*dx + dy*dy > radius*radius)
            {
                // Левый верхний угол
                SDL_RenderPoint(renderer, static_cast<float>(dx), static_cast<float>(dy));
                // Правый верхний угол
                SDL_RenderPoint(renderer, static_cast<float>(width - diameter + dx), static_cast<float>(dy));
                // Левый нижний угол
                SDL_RenderPoint(renderer, static_cast<float>(dx), static_cast<float>(height - diameter + dy));
                // Правый нижний угол
                SDL_RenderPoint(renderer, static_cast<float>(width - diameter + dx), static_cast<float>(height - diameter + dy));
            }
        }
    }

    // ---------------------- Восстанавливаем старый рендер-таргет и выводим в окно
    SDL_SetRenderTarget(renderer, old_target);

    SDL_FRect dst{

        static_cast<float>(x_render_point - width / 2),
        static_cast<float>(y_render_point - height / 2),
        static_cast<float>(width),
        static_cast<float>(height)

    };

    
    SDL_RenderTexture(renderer, target, nullptr, &dst);

    SDL_DestroyTexture(target);
}

// =========================================================================================== ROUNDED RECTANGLE



// =========================================================================================== CIRCLE

void circle_draw_by_color(
    
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


void circle_draw_by_texture(

    int x_render_point,
    int y_render_point,

    unsigned int radius,

    SDL_Texture* texture,

    SDL_Renderer* renderer

)
{
    if (!texture || radius == 0) return;

    for (int dx = -static_cast<int>(radius); dx <= static_cast<int>(radius); dx++)
    {
        for (int dy = -static_cast<int>(radius); dy <= static_cast<int>(radius); dy++)
        {
            if (dx*dx + dy*dy <= static_cast<int>(radius*radius))
            {
                SDL_FRect pixel_rect{
                    static_cast<float>(x_render_point + dx),
                    static_cast<float>(y_render_point + dy),
                    1.0f, 1.0f
                };
                SDL_RenderTexture(renderer, texture, nullptr, &pixel_rect);
            }
        }
    }
}


// =========================================================================================== CIRCLE