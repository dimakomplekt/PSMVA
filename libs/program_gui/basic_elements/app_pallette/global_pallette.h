// global_pallette.h

#pragma once

// =========================================================================================== IMPORT

#include "../GUI_functions/translators/color_translator.h"      // Color translator from HEX to SDL_Color

#include <string>
#include <vector>

// =========================================================================================== IMPORT


// =========================================================================================== PALLETTE STRUCT

// App pallette structure, which contains all basic colors for basic UI
struct app_pallette_ctx
{
    // Global bacground
    SDL_Color global_background_color;

    // Basic background colors (for UI elements - buttons, textboxes, faders)

    SDL_Color basic_background_color;
    SDL_Color basic_border_color;
    SDL_Color basic_content_color;
    SDL_Color basic_shadow_color;

    // Basic background colors (for UI elements - panels)

    SDL_Color inverted_basic_background_color;
    SDL_Color inverted_basic_border_color;
    SDL_Color inverted_basic_content_color;
    SDL_Color inverted_basic_shadow_color;


    // Basic hover and click state colors (for UI elements - buttons, faders)

    SDL_Color hover_background_color;
    SDL_Color hover_border_color;
    SDL_Color hover_content_color;
    SDL_Color hover_shadow_color;

    SDL_Color click_background_color;
    SDL_Color click_border_color;
    SDL_Color click_content_color;
    SDL_Color click_shadow_color;


    // Denied element access colors (for UI elements with click permission logic)

    SDL_Color accept_denied_background_color;
    SDL_Color accept_denied_border_color;
    SDL_Color accept_denied_content_color;
    SDL_Color accept_denied_shadow_color;

    // Permitted element access colors (for UI elements with click permission logic)

    SDL_Color accept_permitted_background_color;
    SDL_Color accept_permitted_border_color;
    SDL_Color accept_permitted_content_color;
    SDL_Color accept_permitted_shadow_color;

    SDL_Color accept_permitted_hover_background_color;
    SDL_Color accept_permitted_hover_border_color;
    SDL_Color accept_permitted_hover_content_color;
    SDL_Color accept_permitted_hover_shadow_color;

    SDL_Color accept_permitted_click_background_color;
    SDL_Color accept_permitted_click_border_color;
    SDL_Color accept_permitted_click_content_color;
    SDL_Color accept_permitted_click_shadow_color;

};

// =========================================================================================== PALLETTE STRUCT


// =========================================================================================== PALLETTES DECLARATION

app_pallette_ctx app_pallette_1;
app_pallette_ctx app_pallette_2;

// =========================================================================================== PALLETTES DECLARATION


// =========================================================================================== APP PALLETTE SINGLETON CLASS


/**
 * @brief Singleton class that holds the pallettes structures and current pallette.
 *
 * Ensures there is only one global instance of app pallette.
 * 
 * Provides methods to set the pallettes list, get the current pallette colors 
 * and switch current pallette to the specific pallette or next pallette inside the pallettes
 * list.
 *
 */
class Global_pallette
{

    public:

        // ===== Instance =====

        /**
         * @brief Returns the singleton instance.
         *
         * Guarantees a single global instance of Global_pallette.
         * 
         */
        static Global_pallette& Instance();

        // ===== Instance =====


        // ===== Pallette workflow =====

        /**
         * @brief Adds a palette to the internal list.
         *
         * @param new_pallette Palette data to be stored.
         *
         * Palette is copied into internal std::vector storage.
         * No dynamic allocation or ownership transfer is involved.
         */
        void add_pallette(const app_pallette_ctx& new_pallette);


        /**
         * @brief Gets the current active palette.
         *
         * @return Const reference to the current palette.
         *
         * Returned as const reference to:
         * - avoid copying large structure (performance)
         * - prevent modification of global palette state
         *
         * NOTE:
         * Reference remains valid as long as pallettes_list
         * is not structurally modified (no push_back / reallocation).
         */
        const app_pallette_ctx& get_current_pallette() const;


        /**
         * @brief Switches to the next palette in the list.
         *
         * Cycles through available palettes.
         * Wraps to the first palette when the end is reached.
         *
         * Also sets reset flag to notify UI about palette change.
         */
        void switch_to_the_next_pallette();


        /**
         * @brief Switches to a specific palette by id.
         *
         * @param pallette_id Index of palette in internal list.
         *
         * Sets current palette if id is valid.
         * Preferred over pointer-based access to avoid invalid memory references.
         *
         * Also sets reset flag to notify UI about palette change.
         */
        void switch_to_the_pallette(unsigned int pallette_id);

        // ===== Pallette workflow =====


        // ===== Pallette reset =====

        /**
         * @brief Gets the pallette reset flag.
         *
         * @return true if the pallette has been reset, false otherwise.
         * 
         */
        bool get_pallette_reset_flag() const;

        // Function, called inside the main loop, before state loop
        // sets pallette_reset_flag to false after 2 loops, to avoid constant resettings.
        // Called inside SDL_app_cycle(SDL_app_ctx* app) in app.cpp
        void pallette_reset_flag_state_loop_update();

        // ===== Pallette reset =====
        

    private:

        // ===== Constructor and Destuctor =====
        
        // Private constructor ensures no external instances can be created.
        Global_pallette();

        // Default destructor is fine; no dynamic allocation to clean up.
        ~Global_pallette() = default;

        // Copy constructor is deleted to prevent copying the singleton.
        Global_pallette(const Global_pallette&) = delete;

        // Assignment operator is deleted to prevent copying the singleton.
        Global_pallette& operator=(const Global_pallette&) = delete;

        // ===== Constructor and Destuctor =====

        
        // ===== Pallettes =====

        // Pallettes list
        std::vector<app_pallette_ctx> pallettes_list;


        // Currently active pallette ID (by pallettes list)
        unsigned int current_pallette_id;

        // ===== Pallettes =====


        // ===== Reset logic =====

        // Flag to indicate if the pallette has been reset (for UI updates, etc.)
        bool pallette_reset_flag;

        // Counter to track how many loops have passed since the pallette reset flag was set
        unsigned int pallette_reset_flag_loops_counter;

        // ===== Reset logic =====
};

// =========================================================================================== APP PALLETTE SINGLETON CLASS


// =========================================================================================== APP PALLETTE SINGLETON FOR USE

// Global singleton instance of app pallette for easy access throughout the program
inline Global_pallette& App_pallette = Global_pallette::Instance();

// =========================================================================================== APP PALLETTE SINGLETON FOR USE
