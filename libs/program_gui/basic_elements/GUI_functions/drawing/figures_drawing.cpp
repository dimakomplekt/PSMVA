// figures_drawing.cpp

// =========================================================================================== IMPORT

#include "figures_drawing.h"

// =========================================================================================== IMPORT



// =========================================================================================== RECTANGLE


/**
 * @brief Draws a line between two points with a specified width and color.
 * 
 * @param x_1_render_point render point 1 x coordinate
 * @param y_1_render_point render point 1 y coordinate
 * @param x_2_render_point render point 2 x coordinate
 * @param y_2_render_point render point 2 y coordinate
 * @param line_width line width
 * @param color line color
 * @param renderer renderer
 * 
 * 
 */
void line_draw(

    int x_1_render_point, 
    int y_1_render_point,

    int x_2_render_point, 
    int y_2_render_point,


    unsigned int line_width,

    SDL_Color color,

    SDL_Renderer* renderer

)
{
    if (!renderer || line_width == 0) return;

    // Set the drawing color once for all lines below
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    // Standard case for 1px line thickness
    if (line_width == 1) {
        SDL_RenderLine(renderer, x_1_render_point, y_1_render_point, x_2_render_point, y_2_render_point);
        return;
    }

    // Horizontal thick lines are filled as one rectangle instead of a batch
    // of thin line commands, avoiding edge artifacts in the Mini backend.
    if (y_1_render_point == y_2_render_point) {
        SDL_FRect rect = {
            (float)std::min(x_1_render_point, x_2_render_point),
            (float)y_1_render_point - ((float)line_width * 0.5f),
            (float)std::abs(x_2_render_point - x_1_render_point),
            (float)line_width
        };
        SDL_RenderFillRect(renderer, &rect);
        return;
    }

    // Check direction vector
    float dx = (float)(x_2_render_point - x_1_render_point);
    float dy = (float)(y_2_render_point - y_1_render_point);
    float length = std::sqrt(dx * dx + dy * dy);

    if (length == 0.0f) return; // Point-to-point error (coinciding points)

    // Normalize direction vector
    dx /= length;
    dy /= length;

    // Find the perpendicular unit vector (normal)
    float nx = -dy;
    float ny = dx;

    // Calculate half width for symmetric drawing
    float half_width = (float)line_width / 2.0f;

    // Draw the thick line as a set of parallel thin lines
    // Step by 0.5 pixels to prevent gaps due to rounding errors
    for (float i = -half_width; i <= half_width; i += 0.5f) {
        int x1_offset = std::round((float)x_1_render_point + nx * i);
        int y1_offset = std::round((float)y_1_render_point + ny * i);
        int x2_offset = std::round((float)x_2_render_point + nx * i);
        int y2_offset = std::round((float)y_2_render_point + ny * i);

        SDL_RenderLine(renderer, x1_offset, y1_offset, x2_offset, y2_offset);
    }
}


void rectangle_borders_draw_by_color(
    
    int x_render_point,
    int y_render_point,

    unsigned int width,
    unsigned int height,

    unsigned int line_width,
    SDL_Color color,

    SDL_Renderer* renderer

)
{
    if (width < 1 || height < 1 || line_width < 1)
    {
        return;
    }

    if (line_width >= width || line_width >= height)
    {
        rectangle_draw_by_color(x_render_point, y_render_point, width, height, color, renderer);
        return;
    }

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    int rect_width  = static_cast<int>(width);
    int rect_height = static_cast<int>(height);
    int lw          = static_cast<int>(line_width);


    int outer_x = x_render_point - rect_width / 2;
    int outer_y = y_render_point - rect_height / 2;


    SDL_FRect rects[4];

    // 1. Upper line
    rects[0].x = outer_x;
    rects[0].y = outer_y;
    rects[0].w = rect_width;
    rects[0].h = lw;

    // 2. Downer line
    rects[1].x = outer_x;
    rects[1].y = outer_y + rect_height - lw;
    rects[1].w = rect_width;
    rects[1].h = lw;

    // 3. Left line
    rects[2].x = outer_x;
    rects[2].y = outer_y + lw;
    rects[2].w = lw;
    rects[2].h = rect_height - (lw * 2);

    // 4. Right line
    rects[3].x = outer_x + rect_width - lw;
    rects[3].y = outer_y + lw;
    rects[3].w = lw;
    rects[3].h = rect_height - (lw * 2);

    // Render all at once
    SDL_RenderFillRects(renderer, rects, 4);
}



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

    // SDL3 AND SDL2 CONFLICT
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

    // SDL3 AND SDL2 CONFLICT
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
    if (width < 3 || height < 3 || !renderer)
    {
        return;
    }

    if (radius == 0)
    {
        rectangle_draw_by_color(x_render_point, y_render_point, width, height, color, renderer);
        return;
    }

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    int cx = x_render_point;
    int cy = y_render_point;

    int w = static_cast<int>(width);
    int h = static_cast<int>(height);
    int r = static_cast<int>(radius);

    int max_r = std::min((w - 1) / 2, (h - 1) / 2);
    if (r > max_r) r = max_r;

    int hw = w / 2;
    int hh = h / 2;

    // ========================= CENTER

    // SDL3 AND SDL2 CONFLICT

    SDL_FRect center_rect{
        (float)(cx - hw + r),
        (float)(cy - hh),
        (float)(w - 2 * r),
        (float)(h)
    };

    SDL_RenderFillRect(renderer, &center_rect);

    // ========================= SIDES

    SDL_FRect left_rect{
        (float)(cx - hw),
        (float)(cy - hh + r),
        (float)(r),
        (float)(h - 2 * r)
    };

    SDL_RenderFillRect(renderer, &left_rect);


    SDL_FRect right_rect{
        (float)(cx + hw - r),
        (float)(cy - hh + r),
        (float)(r),
        (float)(h - 2 * r)
    };

    SDL_RenderFillRect(renderer, &right_rect);

    // ========================= SMOOTH CORNERS

    const int segments = std::max(8, (int)(r * 10.0f));

    const float step = (SDL_PI_F * 0.5f) / segments;


    SDL_FColor fcolor{

        color.r / 255.0f,
        color.g / 255.0f,
        color.b / 255.0f,
        color.a / 255.0f
        
    };

    
    auto draw_corner = [&](float center_x, float center_y, float start_angle)
    {
        for (int i = 0; i < segments; ++i)
        {
            float a1 = start_angle + i * step;
            float a2 = start_angle + (i + 1) * step;

            SDL_Vertex verts[3];

            verts[0].position = { center_x, center_y };

            verts[0].color = fcolor;

            verts[1].position = {

                center_x + r * cosf(a1),
                center_y + r * sinf(a1)

            };

            verts[1].color = fcolor;

            verts[2].position = {

                center_x + r * cosf(a2),
                center_y + r * sinf(a2)

            };

            verts[2].color = fcolor;

            SDL_RenderGeometry(renderer, nullptr, verts, 3, nullptr, 0);
        }
    };

    // Left Top
    draw_corner(cx - hw + r, cy - hh + r, SDL_PI_F);

    // Right Top
    draw_corner(cx + hw - r, cy - hh + r, -SDL_PI_F * 0.5f);

    // Left Bottom
    draw_corner(cx - hw + r, cy + hh - r, SDL_PI_F * 0.5f);

    // Right Bottom
    draw_corner(cx + hw - r, cy + hh - r, 0.0f);
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

        // SDL3 AND SDL2 CONFLICT

        SDL_FRect rect{

            static_cast<float>(x_render_point - width / 2),
            static_cast<float>(y_render_point - height / 2),
            static_cast<float>(width),
            static_cast<float>(height)
            
        };

        SDL_RenderTexture(renderer, texture, nullptr, &rect);
        return;
    }

    // ---------------------- Render target creation

    SDL_Texture* target = SDL_CreateTexture(

        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        width,
        height

    );

    if (!target) return;

    // Save old target

    SDL_Texture* old_target = SDL_GetRenderTarget(renderer);

    SDL_SetRenderTarget(renderer, target);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    // ---------------------- Render texture by target

    // SDL3 AND SDL2 CONFLICT

    SDL_FRect full_rect{0.0f, 0.0f, static_cast<float>(width), static_cast<float>(height)};
    SDL_RenderTexture(renderer, texture, nullptr, &full_rect);


    // ---------------------- Render the mask of rounded corners - just fill the corners with 0 opacity color

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); 

    int diameter = radius * 2;

    for (int dx = 0; dx < diameter; dx++)
    {
        for (int dy = 0; dy < diameter; dy++)
        {
            if (dx*dx + dy*dy > radius*radius)
            {
                // Top left corner
                SDL_RenderPoint(renderer, static_cast<float>(dx), static_cast<float>(dy));

                // Top right corner
                SDL_RenderPoint(renderer, static_cast<float>(width - diameter + dx), static_cast<float>(dy));

                // Bottom left corner
                SDL_RenderPoint(renderer, static_cast<float>(dx), static_cast<float>(height - diameter + dy));

                // Bottom right corner
                SDL_RenderPoint(renderer, static_cast<float>(width - diameter + dx), static_cast<float>(height - diameter + dy));
            }
        }
    }

    
    // Reset old target and show it in window
    SDL_SetRenderTarget(renderer, old_target);

    // SDL3 AND SDL2 CONFLICT

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
    if (radius == 0 || !renderer)
    {
        return;
    }

    const float cx = static_cast<float>(x_render_point);
    const float cy = static_cast<float>(y_render_point);
    const float r  = static_cast<float>(radius);


    // Segment quantity calculation

    const int segments = std::max(12, static_cast<int>(r * 10.0f));

    const float step = 2.0f * SDL_PI_F / segments;

    for (int i = 0; i < segments; ++i)
    {
        float a1 = i * step;
        float a2 = (i + 1) * step;

        float x1 = cx + r * cosf(a1);
        float y1 = cy + r * sinf(a1);

        float x2 = cx + r * cosf(a2);
        float y2 = cy + r * sinf(a2);

        SDL_Vertex verts[3];

        SDL_FColor fcolor{

            color.r / 255.0f,
            color.g / 255.0f,
            color.b / 255.0f,
            color.a / 255.0f

        };

        // Center
        verts[0].position = { cx, cy };
        verts[0].color = fcolor;
        verts[0].tex_coord = { 0.0f, 0.0f };

        // Edge 1
        verts[1].position = { x1, y1 };
        verts[1].color = fcolor;
        verts[1].tex_coord = { 0.0f, 0.0f };

        // Edge 2
        verts[2].position = { x2, y2 };
        verts[2].color = fcolor;
        verts[2].tex_coord = { 0.0f, 0.0f };

        SDL_RenderGeometry(renderer, nullptr, verts, 3, nullptr, 0);
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
    if (!texture || radius == 0 || !renderer) return;

    const float cx = static_cast<float>(x_render_point);
    const float cy = static_cast<float>(y_render_point);
    const float r  = static_cast<float>(radius);

    // Segments quantity calculation
    const int segments = std::max(12, static_cast<int>(r * 10.0f));
    const float step = 2.0f * SDL_PI_F / segments;

    for (int i = 0; i < segments; ++i)
    {
        float a1 = i * step;
        float a2 = (i + 1) * step;

        float x1 = cx + r * cosf(a1);
        float y1 = cy + r * sinf(a1);

        float x2 = cx + r * cosf(a2);
        float y2 = cy + r * sinf(a2);

        SDL_Vertex verts[3];

        // Center
        verts[0].position = { cx, cy };

        verts[0].tex_coord = { 0.5f, 0.5f };

        verts[0].color = {255.0f, 255.0f, 255.0f, 255.0f};


        // Edge 1
        verts[1].position = { x1, y1 };

        verts[1].tex_coord = {

            0.5f + cosf(a1) * 0.5f,
            0.5f + sinf(a1) * 0.5f

        };

        verts[1].color = {255, 255, 255, 255};


        // Edge 2
        verts[2].position = { x2, y2 };

        verts[2].tex_coord = {

            0.5f + cosf(a2) * 0.5f,
            0.5f + sinf(a2) * 0.5f

        };

        verts[2].color = {255.0f, 255.0f, 255.0f, 255.0f};

        SDL_RenderGeometry(renderer, texture, verts, 3, nullptr, 0);
    }
}


// =========================================================================================== CIRCLE
