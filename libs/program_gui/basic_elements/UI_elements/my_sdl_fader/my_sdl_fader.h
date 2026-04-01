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
         * @brief Fader value getter
         * 
         * Uses for external logic
         *
         * @return Current fader value (0.0 - 1.0)
         * 
         */
        float get_fader_value() const;


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
         * @brief Fader's slot render point setter
         * 
         * Setup the fader's slot center-center render point for the fader rendering
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
         * @param new_width New width of the fader's slot in pixels (> 120 px)
         * @param new_height New height of the fader's slot in pixels
         * 
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
         * @param new_width New width of the fader's knob in pixels (s.w - k.w  > 20px)
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


        // Styling

        /**
         * @brief Sets the border width of the slot.
         *
         * Updates the slot's border width while ensuring it does not exceed
         * half of the slot's width or height, and does not exceed the border radius.
         * 
         * If an invalid value is passed, the width is not changed and an error is logged.
         *
         * @param new_size New border width in pixels
         */
        void set_slot_border_width_size(unsigned int new_size);


        /**
         * @brief Sets the border radius of the slot.
         *
         * Updates the corner radius while ensuring it does not exceed
         * half of the slot's width or height.
         * 
         * If an invalid value is passed, the radius is not changed and an error is logged.
         * Also resets the current form to apply the new radius correctly.
         *
         * @param new_size New border radius in pixels
         */
        void set_slot_border_radius(unsigned int new_size);


        /**
         * @brief Sets the shadow offset of the slot.
         *
         * Updates the horizontal and vertical displacement of the slot's shadow
         * relative to the slot's position.
         *
         * @param new_x_offset Horizontal shadow offset in pixels
         * @param new_y_offset Vertical shadow offset in pixels
         */
        void set_slot_shadow_offset(int new_x_offset, int new_y_offset);
        

        /**
         * @brief Sets the slot's shadow scale factor.
         *
         * Adjusts the scaling of the slot's shadow relative to the slot's size.
         *
         * @param new_scale_factor Shadow scale multiplier (e.g., 1.0 = normal size)
         */
        void set_slot_shadow_scale_factor(float new_scale_factor);



        // Pallette setters

        // Slot 

        // Sets the default background color for the slot
        void set_slot_background_color(SDL_Color new_color);

        // Sets the default border color for the slot
        void set_slot_border_color(SDL_Color new_color);

        // Sets the default shadow color for the slot
        void set_slot_shadow_color(SDL_Color new_color);


        // Sets the hovered background color for the slot
        void set_slot_background_color_hovered(SDL_Color new_color);

        // Sets the hovered border color for the slot
        void set_slot_border_color_hovered(SDL_Color new_color);

        // Sets the hovered shadow color for the slot
        void set_slot_shadow_color_hovered(SDL_Color new_color);


        // Sets the clicked background color for the slot
        void set_slot_background_color_clicked(SDL_Color new_color);

        // Sets the clicked border color for the slot
        void set_slot_border_color_clicked(SDL_Color new_color);

        // Sets the clicked shadow color for the slot
        void set_slot_shadow_color_clicked(SDL_Color new_color);


        // Knob

        // Sets the default background color for the knob
        void set_knob_background_color(SDL_Color new_color);

        // Sets the default border color for the knob
        void set_knob_border_color(SDL_Color new_color);

        // Sets the default shadow color for the knob
        void set_knob_shadow_color(SDL_Color new_color);


        // Sets the hovered background color for the knob
        void set_knob_background_color_hovered(SDL_Color new_color);

        // Sets the hovered border color for the knob
        void set_knob_border_color_hovered(SDL_Color new_color);

        // Sets the hovered shadow color for the knob
        void set_knob_shadow_color_hovered(SDL_Color new_color);


        // Sets the clicked background color for the knob
        void set_knob_background_color_clicked(SDL_Color new_color);

        // Sets the clicked border color for the knob
        void set_knob_border_color_clicked(SDL_Color new_color);

        // Sets the clicked shadow color for the knob
        void set_knob_shadow_color_clicked(SDL_Color new_color);


        // ===== GUI ======

    private:

        // ===== MAIN LOGIC =====
        
        // Fader value (0.0 - 1.0)
        float fader_value;


        // Control flags for the fader's slot and knob
        // Knob z > slot z, so the hover and click checks for the knob are more important

        bool slot_hovered;                                // Fader's slot hover state
        void slot_hover_check();                          // Fader's slot hover check method (to be called in the main loop)

        bool slot_clicked;                                // Fader's slot click state
        bool slot_clicked_tmp;                            // Fader's slot click state temp for callback block until the next click
        bool slot_click_check();                          // Fader's slot click check method (to be called in the main loop)

        element_state current_slot_state;                 // Current fader's slot state for rendering logic


        bool knob_hovered;                                // Fader's knob hover state
        void knob_hover_check();                          // Fader's knob hover check method (to be called in the main loop)

        bool knob_clicked;                                // Fader's knob click state
        bool knob_clicked_tmp;                            // Fader's knob click state temp for callback block until the next click
        bool knob_click_check();                          // Fader's knob click check method (to be called in the main loop)
    
        element_state current_knob_state;                 // Current fader's knob state for rendering logic



        // Push mode control flags

        bool push_mode_on;                                // Current push display mode
        int press_offset;                                 // Current press offset for push animation


        // ===== MAIN LOGIC =====


        // ===== GUI ======

        // Render points 

        // Center-center x-render point
        int knob_x_render_point;

        // Center-center y-render point
        int knob_y_render_point;


        /**
         * @brief Fader's knob render point inner setter
         * 
         * Setup the fader's knob center-center render point for the fader rendering
         * by the fader_value.
         * 
         * Calls automatically in update() after the fader_value update. 
         * 
         * 
         * @param x_cc_rp x coordinate of the center-center render point
         * @param y_cc_rp y coordinate of the center-center render point
         * 
         */
        void set_render_point(float new_fader_value);


        // Sizes

        unsigned int slot_width_size;                       // Slot width
        unsigned int slot_height_size;                      // Slot height

        unsigned int knob_width_size;                       // Knob width
        unsigned int knob_height_size;                      // Knob height


        unsigned int slot_border_width_size;                // Slot border width          
        unsigned int slot_border_radius_size;               // Slot border radius 

        unsigned int knob_border_width_size;                // Knob border width          
        unsigned int knob_border_radius_size;               // Knob border radius 


        element_form slot_current_form;                     // Current slot form by the element_form enum
        void reset_slot_current_form();                     // Automatic slot current form reset


        element_form knob_current_form;                     // Current knob form by the element_form enum
        void reset_knob_current_form();                     // Automatic knob current form reset


        int slot_shadow_offset_x;                           // Slot's x-shadow offset    
        int slot_shadow_offset_y;                           // Slot's y-shadow offset

        float slot_shadow_scale_factor;                     // Slot's shadow scale factor - multiplies basic element size to get shadow size


        int knob_shadow_offset_x;                           // Knob's x-shadow offset    
        int knob_shadow_offset_y;                           // Knob's y-shadow offset

        float knob_shadow_scale_factor;                     // Knob's shadow scale factor - multiplies basic element size to get shadow size



        // Boarders (+DELTA_FOR_HOVER_CLICK_CHECKS for the hover and click check stability)

        element_rect_boundaries slot_boundaries_points;     // Slot rectangle bounds by the element_rect_boundaries struct

        void reset_slot_boundaries_points();                // Element slot bounds automatic recalculation

        element_rect_boundaries knob_boundaries_points;     // Knob rectangle bounds by the element_rect_boundaries struct

        void reset_knob_boundaries_points();                // Element's knob bounds automatic recalculation

        void reset_boundaries_points();                     // All element bounds automatic recalculation

        // Pallette


        // Slot basic colors by SDL type  

        SDL_Color slot_background_color;
        SDL_Color slot_border_color;
        SDL_Color slot_shadow_color;
        
        SDL_Color slot_background_color_hovered;
        SDL_Color slot_border_color_hovered;
        SDL_Color slot_shadow_color_hovered;

        SDL_Color slot_background_color_clicked;
        SDL_Color slot_border_color_clicked;
        SDL_Color slot_shadow_color_clicked;


        // Knob basic colors by SDL type  

        SDL_Color knob_background_color;
        SDL_Color knob_border_color;
        SDL_Color knob_shadow_color;

        SDL_Color knob_background_color_hovered;
        SDL_Color knob_border_color_hovered;
        SDL_Color knob_shadow_color_hovered;

        SDL_Color knob_background_color_clicked;
        SDL_Color knob_border_color_clicked;
        SDL_Color knob_shadow_color_clicked;


        // Variables for final rendering

        SDL_Color slot_render_background_color;
        SDL_Color slot_render_border_color;
        SDL_Color slot_render_shadow_color;

        SDL_Color knob_render_background_color;
        SDL_Color knob_render_border_color;
        SDL_Color knob_render_shadow_color;

        // Inner pallette prepare method
        void fader_pallette_prepare();


        // ===== GUI ======

};
// =========================================================================================== My_SDL_fader class