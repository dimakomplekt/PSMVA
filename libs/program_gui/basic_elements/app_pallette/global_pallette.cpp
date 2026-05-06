// global_pallette.cpp

// =========================================================================================== IMPORT

#include "global_pallette.h"

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

// ===== Pallette 1 =====

app_pallette_ctx app_pallette_1;

app_pallette_1.global_background_color = hex_to_sdl_color("#f0e7d6", 255);

app_pallette_1.basic_background_color = hex_to_sdl_color("#f5f219", 255);
app_pallette_1.basic_border_color = hex_to_sdl_color("#171717", 255);
app_pallette_1.basic_content_color = hex_to_sdl_color("#171717", 255);
app_pallette_1.basic_shadow_color = hex_to_sdl_color("#d6cf17", 180);

app_pallette_1.inverted_basic_background_color = hex_to_sdl_color("#171717", 255);
app_pallette_1.inverted_basic_border_color = hex_to_sdl_color("#f5f219", 255);
app_pallette_1.inverted_basic_content_color = hex_to_sdl_color("#f5f219", 255);
app_pallette_1.inverted_basic_shadow_color = hex_to_sdl_color("#0f0f0f", 180);

app_pallette_1.hover_background_color = hex_to_sdl_color("#E8DE2A", 255);
app_pallette_1.hover_border_color = hex_to_sdl_color("#171717", 255);
app_pallette_1.hover_content_color = hex_to_sdl_color("#171717", 255);
app_pallette_1.hover_shadow_color = hex_to_sdl_color("#cfc61f", 180);

app_pallette_1.click_background_color = hex_to_sdl_color("#d4c91a", 255);
app_pallette_1.click_border_color = hex_to_sdl_color("#171717", 255);
app_pallette_1.click_content_color = hex_to_sdl_color("#171717", 255);
app_pallette_1.click_shadow_color = hex_to_sdl_color("#b8af15", 180);

app_pallette_1.accept_denied_background_color = hex_to_sdl_color("#ff3b30", 255);
app_pallette_1.accept_denied_border_color = hex_to_sdl_color("#171717", 255);
app_pallette_1.accept_denied_content_color = hex_to_sdl_color("#171717", 255);
app_pallette_1.accept_denied_shadow_color = hex_to_sdl_color("#cc2f26", 180);

app_pallette_1.accept_permitted_background_color = hex_to_sdl_color("#34c759", 255);
app_pallette_1.accept_permitted_border_color = hex_to_sdl_color("#171717", 255);
app_pallette_1.accept_permitted_content_color = hex_to_sdl_color("#171717", 255);
app_pallette_1.accept_permitted_shadow_color = hex_to_sdl_color("#2da94c", 180);

app_pallette_1.accept_permitted_hover_background_color = hex_to_sdl_color("#3fe06a", 255);
app_pallette_1.accept_permitted_hover_border_color = hex_to_sdl_color("#171717", 255);
app_pallette_1.accept_permitted_hover_content_color = hex_to_sdl_color("#171717", 255);
app_pallette_1.accept_permitted_hover_shadow_color = hex_to_sdl_color("#35c25b", 180);

app_pallette_1.accept_permitted_click_background_color = hex_to_sdl_color("#2fb351", 255);
app_pallette_1.accept_permitted_click_border_color = hex_to_sdl_color("#171717", 255);
app_pallette_1.accept_permitted_click_content_color = hex_to_sdl_color("#171717", 255);
app_pallette_1.accept_permitted_click_shadow_color = hex_to_sdl_color("#279444", 180);

// ===== Pallette 1 =====


// ===== Pallette 2 =====

app_pallette_ctx app_pallette_2;

app_pallette_2.global_background_color = hex_to_sdl_color("#dedede", 255);

app_pallette_2.basic_background_color = hex_to_sdl_color("#f25623", 255);
app_pallette_2.basic_border_color = hex_to_sdl_color("#171717", 255);
app_pallette_2.basic_content_color = hex_to_sdl_color("#171717", 255);
app_pallette_2.basic_shadow_color = hex_to_sdl_color("#c9441c", 180);

app_pallette_2.inverted_basic_background_color = hex_to_sdl_color("#171717", 255);
app_pallette_2.inverted_basic_border_color = hex_to_sdl_color("#f25623", 255);
app_pallette_2.inverted_basic_content_color = hex_to_sdl_color("#f25623", 255);
app_pallette_2.inverted_basic_shadow_color = hex_to_sdl_color("#0f0f0f", 180);

app_pallette_2.hover_background_color = hex_to_sdl_color("#ff6a2e", 255);
app_pallette_2.hover_border_color = hex_to_sdl_color("#171717", 255);
app_pallette_2.hover_content_color = hex_to_sdl_color("#171717", 255);
app_pallette_2.hover_shadow_color = hex_to_sdl_color("#d45524", 180);

app_pallette_2.click_background_color = hex_to_sdl_color("#d94d1f", 255);
app_pallette_2.click_border_color = hex_to_sdl_color("#171717", 255);
app_pallette_2.click_content_color = hex_to_sdl_color("#171717", 255);
app_pallette_2.click_shadow_color = hex_to_sdl_color("#b53f19", 180);

app_pallette_2.accept_denied_background_color = hex_to_sdl_color("#ff3b30", 255);
app_pallette_2.accept_denied_border_color = hex_to_sdl_color("#171717", 255);
app_pallette_2.accept_denied_content_color = hex_to_sdl_color("#171717", 255);
app_pallette_2.accept_denied_shadow_color = hex_to_sdl_color("#cc2f26", 180);

app_pallette_2.accept_permitted_background_color = hex_to_sdl_color("#34c759", 255);
app_pallette_2.accept_permitted_border_color = hex_to_sdl_color("#171717", 255);
app_pallette_2.accept_permitted_content_color = hex_to_sdl_color("#171717", 255);
app_pallette_2.accept_permitted_shadow_color = hex_to_sdl_color("#2da94c", 180);

app_pallette_2.accept_permitted_hover_background_color = hex_to_sdl_color("#3fe06a", 255);
app_pallette_2.accept_permitted_hover_border_color = hex_to_sdl_color("#171717", 255);
app_pallette_2.accept_permitted_hover_content_color = hex_to_sdl_color("#171717", 255);
app_pallette_2.accept_permitted_hover_shadow_color = hex_to_sdl_color("#35c25b", 180);

app_pallette_2.accept_permitted_click_background_color = hex_to_sdl_color("#2fb351", 255);
app_pallette_2.accept_permitted_click_border_color = hex_to_sdl_color("#171717", 255);
app_pallette_2.accept_permitted_click_content_color = hex_to_sdl_color("#171717", 255);
app_pallette_2.accept_permitted_click_shadow_color = hex_to_sdl_color("#279444", 180);

// ===== Pallette 2 =====


// ===== Pallette 3 =====

app_pallette_ctx app_pallette_3;

app_pallette_3.global_background_color = hex_to_sdl_color("#cf93ff", 255);

app_pallette_3.basic_background_color = hex_to_sdl_color("#8f00ff", 255);
app_pallette_3.basic_border_color = hex_to_sdl_color("#171717", 255);
app_pallette_3.basic_content_color = hex_to_sdl_color("#171717", 255);
app_pallette_3.basic_shadow_color = hex_to_sdl_color("#6f00cc", 180);

app_pallette_3.inverted_basic_background_color = hex_to_sdl_color("#171717", 255);
app_pallette_3.inverted_basic_border_color = hex_to_sdl_color("#8f00ff", 255);
app_pallette_3.inverted_basic_content_color = hex_to_sdl_color("#8f00ff", 255);
app_pallette_3.inverted_basic_shadow_color = hex_to_sdl_color("#0f0f0f", 180);

app_pallette_3.hover_background_color = hex_to_sdl_color("#a020ff", 255);
app_pallette_3.hover_border_color = hex_to_sdl_color("#171717", 255);
app_pallette_3.hover_content_color = hex_to_sdl_color("#171717", 255);
app_pallette_3.hover_shadow_color = hex_to_sdl_color("#8219cc", 180);

app_pallette_3.click_background_color = hex_to_sdl_color("#7a00d9", 255);
app_pallette_3.click_border_color = hex_to_sdl_color("#171717", 255);
app_pallette_3.click_content_color = hex_to_sdl_color("#171717", 255);
app_pallette_3.click_shadow_color = hex_to_sdl_color("#6300b3", 180);

app_pallette_3.accept_denied_background_color = hex_to_sdl_color("#ff3b30", 255);
app_pallette_3.accept_denied_border_color = hex_to_sdl_color("#171717", 255);
app_pallette_3.accept_denied_content_color = hex_to_sdl_color("#171717", 255);
app_pallette_3.accept_denied_shadow_color = hex_to_sdl_color("#cc2f26", 180);

app_pallette_3.accept_permitted_background_color = hex_to_sdl_color("#34c759", 255);
app_pallette_3.accept_permitted_border_color = hex_to_sdl_color("#171717", 255);
app_pallette_3.accept_permitted_content_color = hex_to_sdl_color("#171717", 255);
app_pallette_3.accept_permitted_shadow_color = hex_to_sdl_color("#2da94c", 180);

app_pallette_3.accept_permitted_hover_background_color = hex_to_sdl_color("#3fe06a", 255);
app_pallette_3.accept_permitted_hover_border_color = hex_to_sdl_color("#171717", 255);
app_pallette_3.accept_permitted_hover_content_color = hex_to_sdl_color("#171717", 255);
app_pallette_3.accept_permitted_hover_shadow_color = hex_to_sdl_color("#35c25b", 180);

app_pallette_3.accept_permitted_click_background_color = hex_to_sdl_color("#2fb351", 255);
app_pallette_3.accept_permitted_click_border_color = hex_to_sdl_color("#171717", 255);
app_pallette_3.accept_permitted_click_content_color = hex_to_sdl_color("#171717", 255);
app_pallette_3.accept_permitted_click_shadow_color = hex_to_sdl_color("#279444", 180);

// ===== Pallette 3 =====


// =========================================================================================== APP PALLETES


// =========================================================================================== APP PALLETE SINGLETON



Global_pallette& Global_pallette::Instance()
{
    static Global_pallette instance;

    static bool initialized = false;

    if (!initialized)
    {
        // Pallettes initialization zone
        instance.add_pallette(app_pallette_1);
        instance.add_pallette(app_pallette_2);
        instance.add_pallette(app_pallette_3);
        
        initialized = true;
    }

    return instance;
}


Global_pallette::Global_pallette()
{
    this->current_pallette_id = 0;

    this->pallette_reset_flag = true;
    this->pallette_reset_flag_loops_counter = 0;


    // Constructor is private and only called once by Instance().
    // No dynamic memory allocation needed here.
}


// ===== Pallette workflow =====


void Global_pallette::add_pallette(const app_pallette_ctx& new_pallette)
{
    this->pallettes_list.push_back(new_pallette);
}



const app_pallette_ctx& Global_pallette::get_current_pallette() const
{
    return this->pallettes_list[this->current_pallette_id];
}



void Global_pallette::switch_to_the_next_pallette()
{
    if (this->current_pallette_id + 1 < this->pallettes_list.size())
    {
        this->current_pallette_id++;
    }
    else
    {
        this->current_pallette_id = 0;
    }

    this->pallette_reset_flag = true;
    this->pallette_reset_flag_loops_counter = 0;
}


void Global_pallette::switch_to_the_pallette(unsigned int pallette_id)
{
    if (pallette_id < this->pallettes_list.size())
    {
        this->current_pallette_id = pallette_id;

        this->pallette_reset_flag = true;
        this->pallette_reset_flag_loops_counter = 0;
    }

    this->pallette_reset_flag = true;
    this->pallette_reset_flag_loops_counter = 0;
}


// ===== Pallette reset =====

bool Global_pallette::get_pallette_reset_flag() const
{
    return this->pallette_reset_flag;
}


// Function, called inside the main loop, before state loop
// sets pallette_reset_flag to false after 2 loops, to avoid constant resettings.
// Called inside SDL_app_cycle(SDL_app_ctx* app) in app.cpp
void Global_pallette::pallette_reset_flag_state_loop_update()
{
    // If the flag is set, we need to track how many loops have passed
    if (pallette_reset_flag)
    {
        pallette_reset_flag_loops_counter++;

        // After 2 loops, reset the flag to avoid constant resetting
        if (pallette_reset_flag_loops_counter >= 2)
        {
            pallette_reset_flag = false;
            pallette_reset_flag_loops_counter = 0; // Reset counter for next time
        }
    }
}
