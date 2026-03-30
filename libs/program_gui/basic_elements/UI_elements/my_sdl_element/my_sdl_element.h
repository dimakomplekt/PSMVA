// my_sdl_ui_element.h


#pragma once


// =========================================================================================== IMPORT

#include <functional>                                                   // for std::function
#include <cmath>                                                        // for std::round()


#include "../../../engine/engine.h"                                     // SDL3 and SDL ttf import

#include "../../GUI_functions/drawing/figures_drawing.h"                // Basic figures
#include "../../GUI_functions/translators/color_translator.h"           // HEX to SDL_Color 

// =========================================================================================== IMPORT


// =========================================================================================== TYPES

// Element signal type for GUI change logic
enum element_gui_type
{

    STATIC_ELEMENT_GUI,        // One color pallette
    DYNAMIC_ELEMENT_GUI,       // Different color pallettes for different extern logic

};


struct element_rect_boundaries
{

    int left_boundary;
    int right_boundary;
    int top_boundary;
    int bottom_boundary;

};

// =========================================================================================== TYPES


// =========================================================================================== My_SDL_element class


class My_SDL_element
{

    public:

        // ===== CONSTRUCTOR AND DESTRUCTOR =====

        virtual My_SDL_element();                            // Element constructor (never calls, only for inheritance)
        virtual ~My_SDL_element();                           // Element destructor (never calls, only for inheritance)  

        // ===== CONSTRUCTOR AND DESTRUCTOR =====


        // ===== MAIN LOGIC =====


        // Virtual method for inheretence (to do something like: "for (auto& el : elements) el->update();")
        virtual void update() = 0;


        // ===== MAIN LOGIC =====


        // ===== GUI =====
        

        /**
         * @brief GUI type setter
         * 
         * Choose the gui type (static or dynamic) for the elementby the element_gui_type enum values
         * 
         * @param new_gui_type one of the two element_gui_type enum values
         * 
         */
        void set_gui_type(element_gui_type new_gui_type);


        /**
         * @brief Callback for dynamic palette selection.
         *
         * Returns the required palette ID based on external logic.
         * Allows the elementto adapt its visual appearance depending
         * on application state (e.g. enabled/disabled, valid/invalid, etc.).
         *
         * Can be used to implement context-dependent coloring
         * (e.g. red for blocked state, green for available state).
         *
         * Called during update() to determine the current palette.
         * 
         */
        std::function<unsigned int()> get_required_palette;


        /**
         * @brief Virtual render method for the UI-element
         * 
         */
        virtual void render(SDL_Renderer* renderer) = 0;


        /**
         * @brief Element render point setter
         * 
         * Setup the element center-center render point for the element rendering
         * by the coordinate system of the WINDOW, which contains the element 
         * 
         * 
         * @param x_cc_rp x coordinate of the center-center render point
         * @param y_cc_rp y coordinate of the center-center render point
         * 
         */
        void set_render_point(int x_cc_rp, int y_cc_rp);


        /**
         * @brief Returns the X coordinate of the element's render center.
         *
         * @return X coordinate (center of the element for rendering)
         * 
         */
        int get_x_render_point() const;


        /**
         * @brief Returns the Y coordinate of the element's render center.
         *
         * @return Y coordinate (center of the element for rendering)
         * 
         */
        int get_y_render_point() const;


        
        /**
         * @brief Sets the element's global opacity.
         *
         * Updates the alpha value applied to all button visual elements,
         * including background, border, shadow, and content.
         *
         * @param new_opacity Opacity value (0 = fully transparent, 255 = fully opaque)
         * 
         */
        void set_opacity(Uint8 new_opacity);


        
        /**
         * @brief Get the element's global opacity.
         *
         * @return Opacity value (0 = fully transparent, 255 = fully opaque)
         * 
         */
        Uint8 get_opacity();


        // ===== GUI =====

}


