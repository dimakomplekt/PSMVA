// my_sdl_fader.h


#pragma once


// =========================================================================================== IMPORT

#include "../my_sdl_element/my_sdl_element.h" // Base class import

// =========================================================================================== IMPORT


// =========================================================================================== My_SDL_fader class

class My_SDL_fader : public My_SDL_element // SDL_Element
{

    public:

        // ===== CONSTRUCTOR AND DESTRUCTOR =====

        My_SDL_fader();                            // Fader constructor (call in state.start)
        ~My_SDL_fader();                           // Fader destructor  (call in state.exit)  

        // ===== CONSTRUCTOR AND DESTRUCTOR =====


        // ===== MAIN LOGIC =====

        /**
         * @brief Updates the fader
         *
         * //
         * //
         * //
         * 
         * Must be called every frame inside the main state.update loop.
         */
        void update() override;      
        
        


        // Toggles the push mode flag (affects pressed-state rendering behavior)
        void push_mode_switch();

        // ===== MAIN LOGIC =====


        // ===== GUI ======

        
        /**
         * @brief Renders the fader based on its current state and visual configuration.
         *
         * //
         * //
         * //
         *
         * Rendering depends on state flags updated in update().
         */
        void render(SDL_Renderer* renderer) override;

                /**
         * @brief Button render point setter
         * 
         * Setup the button center-center render point for the button rendering
         * by the coordinate system of the WINDOW, which contains the element 
         * 
         * 
         * @param x_cc_rp x coordinate of the center-center render point
         * @param y_cc_rp y coordinate of the center-center render point
         * 
         */
        void set_render_point(int x_cc_rp, int y_cc_rp) override;



        // Size - unique logic for every element

        /**
         * @brief Sets the fader's slot size.
         *
         * Updates the fader's slot width and height for rendering and layout.
         *
         * @param new_width New width of the fader's slot in pixels
         * @param new_height New height of the fader's slot in pixels
         */
        void set_slot_size(unsigned int new_width, unsigned int new_height);


        /**
         * @brief Returns the fader's slot width.
         *
         * @return Width of the fader's slot in pixels
         */
        unsigned int get_slot_width_size() const;


        /**
         * @brief Returns the fader's slot  height.
         *
         * @return Height of the fader's slot in pixels
         */
        unsigned int get_slot_height_size() const;


        /**
         * @brief Sets the fader's knob size.
         *
         * Updates the fader's knob width and height for rendering and layout.
         *
         * @param new_width New width of the fader's knob in pixels
         * @param new_height New height of the fader's knob in pixels
         */
        void set_knob_size(unsigned int new_width, unsigned int new_height);


        /**
         * @brief Returns the fader's knob width.
         *
         * @return Width of the fader's knob in pixels
         */
        unsigned int get_knob_width_size() const;


        /**
         * @brief Returns the fader's knob height.
         *
         * @return Height of the fader's knob in pixels
         */
        unsigned int get_knob_height_size() const;



        // ===== GUI ======

    private:

        // ===== MAIN LOGIC =====


        

        // ===== GUI ======


        // ===== GUI ======

};
// =========================================================================================== My_SDL_fader class