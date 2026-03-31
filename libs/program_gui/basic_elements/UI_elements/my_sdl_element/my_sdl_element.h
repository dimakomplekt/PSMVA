// my_sdl_element.h


#pragma once


// =========================================================================================== IMPORT

#include <functional>                                                   // for std::function
#include <cmath>                                                        // for std::round()


#include "../../../../engine/engine.h"                                     // SDL3 and SDL ttf import

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


// =========================================================================================== TYPES


// =========================================================================================== My_SDL_element class


class My_SDL_element
{

    public:

        // ===== MAIN LOGIC =====


        // Virtual method for inheritance (to do something like: "for (auto& el : elements) el->update();")
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
        virtual void set_render_point(int x_cc_rp, int y_cc_rp) = 0;


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
        Uint8 get_opacity() const;


        // ===== GUI =====


    protected:

            // ===== CONSTRUCTOR AND DESTRUCTOR =====

            My_SDL_element();                            // Element constructor (never calls, only for inheritance)
            virtual ~My_SDL_element() = default;         // Element destructor (never calls, only for inheritance)  

            // ===== CONSTRUCTOR AND DESTRUCTOR =====



            // ===== GUI =====


            // GUI type
            element_gui_type gui_type;

            // Render points (center-center)

            // Center-center x-render point
            int x_render_point;

            // Center-center y-render point
            int y_render_point;


            // Element opacity for SDL rendering with
            // calling of commands like:
            // SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g, background_color.b, alpha);
            // before rendering
            Uint8 opacity; // 0 = fully transperent, 255 = fully opaque
            
            // ===== GUI =====
};
