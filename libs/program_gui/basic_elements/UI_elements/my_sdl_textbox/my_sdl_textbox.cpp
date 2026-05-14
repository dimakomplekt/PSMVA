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
    this->font_path = App_fonts.get_current_fonts_palette().ordinary_text_font.font_path;
    
    if (App_fonts.get_current_fonts_palette().ordinary_text_font.ttf_font_link != nullptr)
    {
        this->ttf_font_link = App_fonts.get_current_fonts_palette().ordinary_text_font.ttf_font_link;
    }
     else
    {
        this->ttf_font_link = TTF_OpenFont(this->font_path.c_str(), this->font_size);

        if (!this->ttf_font_link)
        {
            SDL_Log("TTF_OpenFont failed: %s", SDL_GetError());
        }
    }

    this->passed_by_font_palette = true;


    // if (!ttf_font_link) this->update();

    // Content and sizes set with anchor points reset
    this->set_content("Text");


    // ===== Default palette =====

    this->set_opacity(255);


    // Basic text color by palette
    // flag for showing that the color setted by the pallet, automatically set to true inside the basic class constructor
    set_content_color(App_palette.get_current_palette().basic_content_color);


    this->content_texture = nullptr;

    // Reset flag for the next update in render
    this->content_dirty = true; 


    // Blinking mode setup

    // Turn off by default 

    this->blinking_mode_context.blinking_mode_on = false;


    this->blinking_mode_context.blinking_period = 1400;
    this->blinking_mode_context.blinking_duty = 0.4;

    this->blinking_mode_context.active_time = static_cast<Uint64>(std::round(

        this->blinking_mode_context.blinking_period * 
        this->blinking_mode_context.blinking_duty
        
    ));

    this->blinking_mode_context.phase = 0;

    // Start with inactive condition (constantly switch inside the 1st update)
    this->blinking_mode_context.active_now = true;
}


void My_SDL_textbox::delete_element()
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


My_SDL_textbox::~My_SDL_textbox()
{
    // TODO: Realization with panels linked list clear (both side registration) or just siple comment about 
    // destructor workflow rules - basic destructor from global space or My_SDL_panel.textbox_delete method
    // only for textboxes inside panels

    // Textures destructors
    this->cleanup();
}


void My_SDL_textbox::cleanup()
{
    // Texture delete
    if (this->content_texture)
    {
        SDL_DestroyTexture(this->content_texture);
        this->content_texture = nullptr;
    }

    this->set_content("");
}


// =========================================================================================== CONSTRUCTOR AND DESTRUCTOR

// Helper-function predeclare
void blinking_mode_control(blinkig_textbox_ctx &blinking_ctx);

void My_SDL_textbox::update()
{
    // Control blinking if it's needed
    blinking_mode_control(this->blinking_mode_context);

    // Just font start initialization
    if (this->ttf_font_link == nullptr && !this->passed_by_font_palette)
    {
        if(!this->font_path.empty()) this->set_ttf_font_link(TTF_OpenFont(this->font_path.c_str(), this->font_size));
    }

    // Reset the font if current font palette was switched and the font was set by the font palette,
    // to update the font by the new palette
    if (this->passed_by_font_palette && App_fonts.get_fonts_palette_reset_flag())
    {
        this->font_path = App_fonts.get_current_fonts_palette().ordinary_text_font.font_path;
    
        if (App_fonts.get_current_fonts_palette().ordinary_text_font.ttf_font_link != nullptr)
        {
            this->ttf_font_link = App_fonts.get_current_fonts_palette().ordinary_text_font.ttf_font_link;
        }
         else
        {
            this->ttf_font_link = TTF_OpenFont(this->font_path.c_str(), this->font_size);
    
            if (!this->ttf_font_link)
            {
                SDL_Log("TTF_OpenFont failed: %s", SDL_GetError());
            }
        }
    }

    // Check if the palette was switched and update the colors by the new palette if it was
    this->reset_colors_if_palette_switched();
}

// Helper-function for blinking mode parameters calculation
void blinking_mode_control(blinkig_textbox_ctx &blinking_ctx)
{
    if (!blinking_ctx.blinking_mode_on)
    {
        blinking_ctx.active_now = true;
        return;
    }

    // Current time
    Uint64 t = SDL_GetTicks();

    // 1. Phase inside cycle
    blinking_ctx.phase = t % blinking_ctx.blinking_period;

    // 2. Condition
    blinking_ctx.active_now = (blinking_ctx.phase < blinking_ctx.active_time);
}


// =========================================================================================== GUI

void My_SDL_textbox::render(SDL_Renderer* renderer)
{
    // Render logic

    this->update_content_texture(renderer, this->content_render_color);
    
    // Basic draw if blinking mode is off
    if (!this->blinking_mode_context.blinking_mode_on) this->text_draw(renderer);

    else
    {
        // Draw only if the drawing is active
        if (this->blinking_mode_context.active_now) this->text_draw(renderer);
    }
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
            &h

    ))
    {
        std::cerr << "TTF_GetStringSize failed: " << SDL_GetError() << std::endl;
        return;
    }

    this->content_width_size = w;
    this->content_height_size = h;

    this->reset_anchor_points();

    this->content_dirty = true;
}


void My_SDL_textbox::switch_passed_by_font_palette_flag(bool new_flag)
{
    this->passed_by_font_palette = new_flag;
}

bool My_SDL_textbox::get_passed_by_font_palette_flag() const
{
    return this->passed_by_font_palette;
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

    // close old font
    if (this->ttf_font_link)
    {
        TTF_CloseFont(this->ttf_font_link);
        this->ttf_font_link = nullptr;
    }

    // open new font
    this->ttf_font_link = TTF_OpenFont(this->font_path.c_str(), this->font_size);

    if (!this->ttf_font_link)
    {
        SDL_Log("TTF_OpenFont failed: %s", SDL_GetError());
        return;
    }

    // rebuild geometry
    this->set_content(this->content);

    // force texture rebuild
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



void My_SDL_textbox::reset_colors_if_palette_switched()
{
    // Pass case

    if (!this->passed_by_palette || !App_palette.get_palette_reset_flag()) return;

    // Renew case 
    
    //     !!!    Elements with dynamic content color textboxes  (like buttons) should          !!!
    //     !!!    call switch_passed_by_palette_flag(false) for inner textbox                   !!!
    //     !!!    and switch content color by the pallet or not by the palette by themselves    !!!
    //     !!!    for double calls protection                                                   !!!

    set_content_color(App_palette.get_current_palette().basic_content_color);
}



void My_SDL_textbox::switch_blinking_mode_flag(bool new_flag)
{
    if (this->blinking_mode_context.blinking_mode_on)
    {
        if (new_flag) return;
        else
        {
            // Reset values to basic
            this->blinking_mode_context.active_now = true;
        }
    }

    this->blinking_mode_context.blinking_mode_on = new_flag;
}



void My_SDL_textbox::set_blinking_period(Uint64 new_blinking_period)
{
    bool tmp_mode_on_flag;


    if (this->blinking_mode_context.blinking_mode_on) tmp_mode_on_flag = true;

    else tmp_mode_on_flag = false;


    // Stop anyway and reset values to default
    this->blinking_mode_context.blinking_mode_on = false;


    this->blinking_mode_context.active_now = true;


    // Set new value
    this->blinking_mode_context.blinking_period = new_blinking_period;

    // Recalculate active time value
    this->blinking_mode_context.active_time = static_cast<Uint64>(std::round(

        this->blinking_mode_context.blinking_period * 
        this->blinking_mode_context.blinking_duty

    ));

    // Phase reset
    this->blinking_mode_context.phase = 0;

    // Set temped flag value
    this->blinking_mode_context.blinking_mode_on = tmp_mode_on_flag;
}


void My_SDL_textbox::set_blinking_duty(float new_blinking_duty)
{
    bool tmp_mode_on_flag;


    if (this->blinking_mode_context.blinking_mode_on) tmp_mode_on_flag = true;

    else tmp_mode_on_flag = false;


    // Stop anyway and reset values to default
    this->blinking_mode_context.blinking_mode_on = false;


    this->blinking_mode_context.active_now = true;


    // Set new value
    this->blinking_mode_context.blinking_duty = new_blinking_duty;

    // Recalculate active time value
    this->blinking_mode_context.active_time = static_cast<Uint64>(std::round(

        this->blinking_mode_context.blinking_period * 
        this->blinking_mode_context.blinking_duty

    ));

    // Phase reset
    this->blinking_mode_context.phase = 0;

    // Set temped flag value
    this->blinking_mode_context.blinking_mode_on = tmp_mode_on_flag;
}


void My_SDL_textbox::reset_anchor_points()
{
    // Uses current crop to set the current anchor points

    // Always the same rounding accuracy, because we work with crop map in initial scale and new scalers
    int half_w = static_cast<int>(std::round(static_cast<float>(this->content_width_size) * 0.5));
    int half_h = static_cast<int>(std::round(static_cast<float>(this->content_height_size) * 0.5));


    // Element_anchor_points reset
    
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


    SDL_Color color = new_color; // By passed palette 

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
