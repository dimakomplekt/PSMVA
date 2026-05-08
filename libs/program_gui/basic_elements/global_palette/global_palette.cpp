// global_palette.cpp

// =========================================================================================== IMPORT

#include "global_palette.h"

// =========================================================================================== IMPORT


// =========================================================================================== APP PALLETES


/*
REFERENCE

```
    {background_screen_color: "#f0e7d6", main_color_1: "#f5f219", main_color_2: "#171717", hover_color: "#E8DE2A", click_color: "#8518F5"},
    {background_screen_color: "#dedede", main_color_1: "#f25623", main_color_2: "#171717", hover_color: "#f5f219", click_color: "#f26622"}, 
    {background_screen_color: "#cf93ff", main_color_1: "#8f00ff", main_color_2: "#171717", hover_color: "#f5ffff", click_color: "#9f91ff"}, 
```
*/

// ===== Palette 1 =====

static app_palette_ctx make_palette_1()
{
    app_palette_ctx palette;


    palette.global_background_color = hex_to_sdl_color("#f0e7d6", 255);

    palette.basic_background_color = hex_to_sdl_color("#f5f219", 255);
    palette.basic_border_color = hex_to_sdl_color("#171717", 255);
    palette.basic_content_color = hex_to_sdl_color("#171717", 255);
    palette.basic_shadow_color = hex_to_sdl_color("#d6cf17", 180);
    
    palette.inverted_basic_background_color = hex_to_sdl_color("#171717", 255);
    palette.inverted_basic_border_color = hex_to_sdl_color("#f5f219", 255);
    palette.inverted_basic_content_color = hex_to_sdl_color("#f5f219", 255);
    palette.inverted_basic_shadow_color = hex_to_sdl_color("#0f0f0f", 180);
    
    palette.hover_background_color = hex_to_sdl_color("#E8DE2A", 255);
    palette.hover_border_color = hex_to_sdl_color("#171717", 255);
    palette.hover_content_color = hex_to_sdl_color("#171717", 255);
    palette.hover_shadow_color = hex_to_sdl_color("#cfc61f", 180);
    
    palette.click_background_color = hex_to_sdl_color("#d4c91a", 255);
    palette.click_border_color = hex_to_sdl_color("#171717", 255);
    palette.click_content_color = hex_to_sdl_color("#171717", 255);
    palette.click_shadow_color = hex_to_sdl_color("#b8af15", 180);
    
    palette.access_denied_background_color = hex_to_sdl_color("#ff3b30", 255);
    palette.access_denied_border_color = hex_to_sdl_color("#171717", 255);
    palette.access_denied_content_color = hex_to_sdl_color("#171717", 255);
    palette.access_denied_shadow_color = hex_to_sdl_color("#cc2f26", 180);
    
    palette.access_permitted_background_color = hex_to_sdl_color("#34c759", 255);
    palette.access_permitted_border_color = hex_to_sdl_color("#171717", 255);
    palette.access_permitted_content_color = hex_to_sdl_color("#171717", 255);
    palette.access_permitted_shadow_color = hex_to_sdl_color("#2da94c", 180);
    
    palette.access_permitted_hover_background_color = hex_to_sdl_color("#3fe06a", 255);
    palette.access_permitted_hover_border_color = hex_to_sdl_color("#171717", 255);
    palette.access_permitted_hover_content_color = hex_to_sdl_color("#171717", 255);
    palette.access_permitted_hover_shadow_color = hex_to_sdl_color("#35c25b", 180);
    
    palette.access_permitted_click_background_color = hex_to_sdl_color("#2fb351", 255);
    palette.access_permitted_click_border_color = hex_to_sdl_color("#171717", 255);
    palette.access_permitted_click_content_color = hex_to_sdl_color("#171717", 255);
    palette.access_permitted_click_shadow_color = hex_to_sdl_color("#279444", 180);


    return palette;
}

// ===== Palette 1 =====


// ===== Palette 2 =====

static app_palette_ctx make_palette_2()
{
    app_palette_ctx palette;


    palette.global_background_color = hex_to_sdl_color("#dedede", 255);

    palette.basic_background_color = hex_to_sdl_color("#f25623", 255);
    palette.basic_border_color = hex_to_sdl_color("#171717", 255);
    palette.basic_content_color = hex_to_sdl_color("#171717", 255);
    palette.basic_shadow_color = hex_to_sdl_color("#c9441c", 180);
    
    palette.inverted_basic_background_color = hex_to_sdl_color("#171717", 255);
    palette.inverted_basic_border_color = hex_to_sdl_color("#f25623", 255);
    palette.inverted_basic_content_color = hex_to_sdl_color("#f25623", 255);
    palette.inverted_basic_shadow_color = hex_to_sdl_color("#0f0f0f", 180);
    
    palette.hover_background_color = hex_to_sdl_color("#ff6a2e", 255);
    palette.hover_border_color = hex_to_sdl_color("#171717", 255);
    palette.hover_content_color = hex_to_sdl_color("#171717", 255);
    palette.hover_shadow_color = hex_to_sdl_color("#d45524", 180);
    
    palette.click_background_color = hex_to_sdl_color("#d94d1f", 255);
    palette.click_border_color = hex_to_sdl_color("#171717", 255);
    palette.click_content_color = hex_to_sdl_color("#171717", 255);
    palette.click_shadow_color = hex_to_sdl_color("#b53f19", 180);
    
    palette.access_denied_background_color = hex_to_sdl_color("#ff3b30", 255);
    palette.access_denied_border_color = hex_to_sdl_color("#171717", 255);
    palette.access_denied_content_color = hex_to_sdl_color("#171717", 255);
    palette.access_denied_shadow_color = hex_to_sdl_color("#cc2f26", 180);
    
    palette.access_permitted_background_color = hex_to_sdl_color("#34c759", 255);
    palette.access_permitted_border_color = hex_to_sdl_color("#171717", 255);
    palette.access_permitted_content_color = hex_to_sdl_color("#171717", 255);
    palette.access_permitted_shadow_color = hex_to_sdl_color("#2da94c", 180);
    
    palette.access_permitted_hover_background_color = hex_to_sdl_color("#3fe06a", 255);
    palette.access_permitted_hover_border_color = hex_to_sdl_color("#171717", 255);
    palette.access_permitted_hover_content_color = hex_to_sdl_color("#171717", 255);
    palette.access_permitted_hover_shadow_color = hex_to_sdl_color("#35c25b", 180);
    
    palette.access_permitted_click_background_color = hex_to_sdl_color("#2fb351", 255);
    palette.access_permitted_click_border_color = hex_to_sdl_color("#171717", 255);
    palette.access_permitted_click_content_color = hex_to_sdl_color("#171717", 255);
    palette.access_permitted_click_shadow_color = hex_to_sdl_color("#279444", 180);


    return palette;
}

// ===== Palette 2 =====


// ===== Palette 3 =====

static app_palette_ctx make_palette_3()
{
    app_palette_ctx palette;

    palette.global_background_color = hex_to_sdl_color("#cf93ff", 255);

    palette.basic_background_color = hex_to_sdl_color("#8f00ff", 255);
    palette.basic_border_color = hex_to_sdl_color("#171717", 255);
    palette.basic_content_color = hex_to_sdl_color("#171717", 255);
    palette.basic_shadow_color = hex_to_sdl_color("#6f00cc", 180);
    
    palette.inverted_basic_background_color = hex_to_sdl_color("#171717", 255);
    palette.inverted_basic_border_color = hex_to_sdl_color("#8f00ff", 255);
    palette.inverted_basic_content_color = hex_to_sdl_color("#8f00ff", 255);
    palette.inverted_basic_shadow_color = hex_to_sdl_color("#0f0f0f", 180);
    
    palette.hover_background_color = hex_to_sdl_color("#a020ff", 255);
    palette.hover_border_color = hex_to_sdl_color("#171717", 255);
    palette.hover_content_color = hex_to_sdl_color("#171717", 255);
    palette.hover_shadow_color = hex_to_sdl_color("#8219cc", 180);
    
    palette.click_background_color = hex_to_sdl_color("#7a00d9", 255);
    palette.click_border_color = hex_to_sdl_color("#171717", 255);
    palette.click_content_color = hex_to_sdl_color("#171717", 255);
    palette.click_shadow_color = hex_to_sdl_color("#6300b3", 180);
    
    palette.access_denied_background_color = hex_to_sdl_color("#ff3b30", 255);
    palette.access_denied_border_color = hex_to_sdl_color("#171717", 255);
    palette.access_denied_content_color = hex_to_sdl_color("#171717", 255);
    palette.access_denied_shadow_color = hex_to_sdl_color("#cc2f26", 180);
    
    palette.access_permitted_background_color = hex_to_sdl_color("#34c759", 255);
    palette.access_permitted_border_color = hex_to_sdl_color("#171717", 255);
    palette.access_permitted_content_color = hex_to_sdl_color("#171717", 255);
    palette.access_permitted_shadow_color = hex_to_sdl_color("#2da94c", 180);
    
    palette.access_permitted_hover_background_color = hex_to_sdl_color("#3fe06a", 255);
    palette.access_permitted_hover_border_color = hex_to_sdl_color("#171717", 255);
    palette.access_permitted_hover_content_color = hex_to_sdl_color("#171717", 255);
    palette.access_permitted_hover_shadow_color = hex_to_sdl_color("#35c25b", 180);
    
    palette.access_permitted_click_background_color = hex_to_sdl_color("#2fb351", 255);
    palette.access_permitted_click_border_color = hex_to_sdl_color("#171717", 255);
    palette.access_permitted_click_content_color = hex_to_sdl_color("#171717", 255);
    palette.access_permitted_click_shadow_color = hex_to_sdl_color("#279444", 180);
    


    return palette;
}

// ===== Palette 3 =====


// =========================================================================================== APP PALLETES


// =========================================================================================== APP PALLETE SINGLETON



Global_palette& Global_palette::Instance()
{
    static Global_palette instance;

    static bool initialized = false;

    if (!initialized)
    {
        // Palettes initialization zone
        instance.add_palette(make_palette_1());
        instance.add_palette(make_palette_2());
        instance.add_palette(make_palette_3());
        
        initialized = true;
    }

    return instance;
}


Global_palette::Global_palette()
{
    this->current_palette_id = 0;

    this->palette_reset_flag = true;
    this->palette_reset_flag_loops_counter = 0;


    // Constructor is private and only called once by Instance().
    // No dynamic memory allocation needed here.
}


// ===== Palette workflow =====


void Global_palette::add_palette(const app_palette_ctx& new_palette)
{
    this->palettes_list.push_back(new_palette);
}



const app_palette_ctx& Global_palette::get_current_palette() const
{
    return this->palettes_list[this->current_palette_id];
}



void Global_palette::switch_to_the_next_palette()
{
    if (this->current_palette_id + 1 < this->palettes_list.size())
    {
        this->current_palette_id++;
    }
    else
    {
        this->current_palette_id = 0;
    }

    this->palette_reset_flag = true;
    this->palette_reset_flag_loops_counter = 0;
}


void Global_palette::switch_to_the_palette(unsigned int palette_id)
{
    if (palette_id < this->palettes_list.size())
    {
        this->current_palette_id = palette_id;

        this->palette_reset_flag = true;
        this->palette_reset_flag_loops_counter = 0;
    }
}


// ===== Palette reset =====

bool Global_palette::get_palette_reset_flag() const
{
    return this->palette_reset_flag;
}


// Function, called inside the main loop, before state loop
// sets palette_reset_flag to false after 2 loops, to avoid constant resettings.
// Called inside SDL_app_cycle(SDL_app_ctx* app) in app.cpp
void Global_palette::palette_reset_flag_state_loop_update()
{
    // If the flag is set, we need to track how many loops have passed
    if (palette_reset_flag)
    {
        palette_reset_flag_loops_counter++;

        // After 2 loops, reset the flag to avoid constant resetting
        if (palette_reset_flag_loops_counter >= 2)
        {
            palette_reset_flag = false;
            palette_reset_flag_loops_counter = 0; // Reset counter for next time
        }
    }
}
