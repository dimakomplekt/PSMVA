// global_fonts.cpp

// =========================================================================================== IMPORT

#include "global_fonts.h"

// =========================================================================================== IMPORT


// =========================================================================================== APP FONTS

// ===== Palette 1 =====

static app_fonts_palette_ctx make_fonts_palette_1()
{
    app_font_ctx font_1;

    font_1.font_path = absolute_by_relative_from_exe("content/ttf_fonts/basis33.ttf");

    app_fonts_palette_ctx palette;

    palette.header_1_font = font_1;
    palette.header_2_font = font_1;
    palette.header_3_font = font_1;
    palette.ordinary_text_font = font_1;
    palette.button_text_font = font_1;

    return palette;
}

// ===== Palette 1 =====


// =========================================================================================== APP FONTS


// =========================================================================================== APP FONTS PALETTE SINGLETON


Global_fonts& Global_fonts::Instance()
{
    static Global_fonts instance;

    static bool initialized = false;

    if (!initialized)
    {
        // Palettes initialization zone
        instance.add_fonts_palette(make_fonts_palette_1());
        
        initialized = true;
    }

    return instance;
}


Global_fonts::Global_fonts()
{
    this->current_fonts_palette_id = 0;

    this->fonts_palette_reset_flag = true;
    this->fonts_palette_reset_flag_loops_counter = 0;


    // Constructor is private and only called once by Instance().
    // No dynamic memory allocation needed here.
}


// ===== Palette workflow =====

void Global_fonts::fonts_init_in_update_loop()
{
    // Go through the palettes list and initialize / reinitialize the SDL_TTF fonts if the palette reset flag is set
    if (this->fonts_palette_reset_flag)
    {
        for (app_fonts_palette_ctx& palette : this->fonts_palettes_list)
        {
            // Initialize / reinitialize SDL_TTF fonts for the palette
            for (app_font_ctx* font_ctx : {

                &palette.header_1_font, 
                &palette.header_2_font, 
                &palette.header_3_font, 
                &palette.ordinary_text_font,
                &palette.button_text_font

            })
            {
                if (font_ctx->ttf_font_link)
                {
                    TTF_CloseFont(static_cast<TTF_Font*>(font_ctx->ttf_font_link));
                    font_ctx->ttf_font_link = nullptr;
                }

                if (!font_ctx->font_path.empty())
                {

                    // ====== FONT INITIALIZATION ======

                    // Calls before any state machine cycle comands - guarantees the valid use of the palette font inside the program code

                    font_ctx->ttf_font_link = TTF_OpenFont(font_ctx->font_path.c_str(), 12); // Default font size, can be changed

                    // ====== FONT INITIALIZATION ======

                    if (!font_ctx->ttf_font_link)
                    {
                        SDL_Log("TTF_OpenFont failed for font path %s: %s", font_ctx->font_path.c_str(), SDL_GetError());
                    }
                }
            }
        }
    }
}


void Global_fonts::add_fonts_palette(const app_fonts_palette_ctx& new_fonts_pallette)
{
    this->fonts_palettes_list.push_back(new_fonts_pallette);
}



const app_fonts_palette_ctx& Global_fonts::get_current_fonts_palette() const
{
    return this->fonts_palettes_list[this->current_fonts_palette_id];
}



void Global_fonts::switch_to_the_next_fonts_palette()
{
    if (this->current_fonts_palette_id + 1 < this->fonts_palettes_list.size())
    {
        this->current_fonts_palette_id++;
    }
    else
    {
        this->current_fonts_palette_id = 0;
    }

    this->fonts_palette_reset_flag = true;
    this->fonts_palette_reset_flag_loops_counter = 0;
}


void Global_fonts::switch_to_the_fonts_palette(unsigned int palette_id)
{
    if (palette_id < this->fonts_palettes_list.size())
    {
        this->current_fonts_palette_id = palette_id;

        this->fonts_palette_reset_flag = true;
        this->fonts_palette_reset_flag_loops_counter = 0;
    }
}


// ===== Palette reset =====

bool Global_fonts::get_fonts_palette_reset_flag() const
{
    return this->fonts_palette_reset_flag;
}


// Function, called inside the main loop, before state loop
// sets palette_reset_flag to false after 2 loops, to avoid constant resettings.
// Called inside SDL_app_cycle(SDL_app_ctx* app) in app.cpp
void Global_fonts::fonts_palette_reset_flag_state_loop_update()
{
    // If the flag is set, we need to track how many loops have passed
    if (fonts_palette_reset_flag)
    {
        fonts_palette_reset_flag_loops_counter++;

        // After 2 loops, reset the flag to avoid constant resetting
        if (fonts_palette_reset_flag_loops_counter >= 2)
        {
            fonts_palette_reset_flag = false;
            fonts_palette_reset_flag_loops_counter = 0; // Reset counter for next time
        }
    }
}
