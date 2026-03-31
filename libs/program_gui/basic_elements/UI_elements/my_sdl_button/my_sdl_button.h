// my_sdl_button.h


#pragma once


// =========================================================================================== IMPORT

#include "../my_sdl_element/my_sdl_element.h" // Base class import

// =========================================================================================== IMPORT



// =========================================================================================== DEFINES

constexpr unsigned int PALLETTES_QUANTITY = 2;

// =========================================================================================== DEFINES


// =========================================================================================== TYPES

// Button access type for click callback logic permission
enum button_access_type
{

    BUTTON_DEFAULT_CLICK_PERMISSION,        // Always can be clicked
    BUTTON_EXTERN_CLICK_PERMISSION,         // Can be clicked only by the true return of the extern function for click permission check

};

// =========================================================================================== TYPES


// =========================================================================================== My_SDL_button class

class My_SDL_button : public My_SDL_element // SDL_Element
{

    public:

        // ===== CONSTRUCTOR AND DESTRUCTOR =====

        My_SDL_button();                            // Button constructor (call in state.start)
        ~My_SDL_button();                           // Button destructor  (call in state.exit)  

        // ===== CONSTRUCTOR AND DESTRUCTOR =====


        // ===== MAIN LOGIC =====

        /**
         * @brief Updates the button.
         *
         * - Performs hover detection and updates hover state
         * - Handles click press/release logic
         * - Applies click access control (default or external permission)
         * - Triggers hover and click callbacks when conditions are met
         * - Ensures single-click behavior (prevents repeat while holding)
         * - Updates visual state (DEFAULT / HOVERED / CLICKED)
         * - Applies palette change if required
         *
         * Must be called every frame inside the main state.update loop.
         */
        void update() override;                                  


        /**
         * @brief Button access type setter 
         * 
         * Setup the button access type for click permission logic by the
         * button_access_type enum values
         * 
         * @param new_access_type - one of the two button_access_type enum values 
         */
        void set_access_type(button_access_type new_access_type);


        // Toggles the push mode flag (affects pressed-state rendering behavior)
        void push_mode_switch();


        /**
         * @brief External callback for click permission validation.
         *
         * This callback is used when the button access type is set to
         * BUTTON_EXTERN_CLICK_PERMISSION. It must return true if the button
         * is allowed to process a click, or false otherwise.
         *
         * Can be used to implement custom access logic (e.g. state checks,
         * conditions from other UI elements, game logic, etc.).
         *
         * Expected usage:
         * - Assign a function/lambda returning bool
         * - The function will be called during update() when a click occurs
         *
         * Must be set when using external click permission, otherwise
         * click handling will fail.
         */
        std::function<bool()> extern_click_permission; 


        /**
         * @brief Callback triggered when the button is hovered.
         *
         * Allows attaching custom external logic that will be executed
         * while the cursor is over the button.
         *
         * Can be used for visual effects, sound, tooltips, or any
         * additional hover-related behavior.
         *
         * Called during update() when the button is in hovered state.
         */
        std::function<void()> on_hover;                    

        
        /**
         * @brief Click callback (single-shot).
         *
         * Executed once after a complete click action (press + release).
         * The callback is triggered only once per click and is blocked
         * until the next valid click occurs.
         *
         * Used to attach custom logic to button activation.
         *
         * Called during update() on click release.
         */
        std::function<void()> on_click;     
            

        // ===== MAIN LOGIC =====


        // ===== GUI ======


        /**
         * @brief Callback for dynamic palette selection.
         *
         * Returns the required palette ID based on external logic.
         * Allows the button to adapt its visual appearance depending
         * on application state (e.g. enabled/disabled, valid/invalid, etc.).
         *
         * Can be used to implement context-dependent coloring
         * (e.g. red for blocked state, green for available state).
         *
         * Called during update() to determine the current palette.
         */
        std::function<unsigned int()> get_required_palette;  // SDL_E


        /**
         * @brief Renders the button based on its current state and visual configuration.
         *
         * - Selects the active palette (static or dynamic)
         * - Resolves colors for current state (DEFAULT / HOVERED / CLICKED)
         * - Applies global opacity to all visual components
         * - Calculates geometry for shadow, border, and background
         * - Simulates button press effect using offset (push mode)
         * - Renders shape (rectangle / rounded rectangle / circle)
         * - Updates and renders content (text/texture) centered inside the button
         *
         * Rendering depends on state flags updated in update().
         */
        void render(SDL_Renderer* renderer) override; // SDL_E


        // Render point

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
         * @brief Sets the button size.
         *
         * Updates the button's width and height for rendering and layout.
         *
         * @param new_width New width of the button in pixels
         * @param new_height New height of the button in pixels
         */
        void set_size(unsigned int new_width, unsigned int new_height);


        /**
         * @brief Returns the button's width.
         *
         * @return Width of the button in pixels
         */
        unsigned int get_width_size() const;


        /**
         * @brief Returns the button's height.
         *
         * @return Height of the button in pixels
         */
        unsigned int get_height_size() const;


        // Styling

        /**
         * @brief Sets the border width of the button.
         *
         * Updates the button's border width while ensuring it does not exceed
         * half of the button's width or height, and does not exceed the border radius.
         * If an invalid value is passed, the width is not changed and an error is logged.
         *
         * @param new_size New border width in pixels
         */
        void set_border_width_size(unsigned int new_size);


        /**
         * @brief Sets the border radius of the button.
         *
         * Updates the corner radius while ensuring it does not exceed
         * half of the button's width or height.
         * If an invalid value is passed, the radius is not changed and an error is logged.
         * Also resets the current form to apply the new radius correctly.
         *
         * @param new_size New border radius in pixels
         */
        void set_border_radius(unsigned int new_size);


        /**
         * @brief Sets the shadow offset of the button.
         *
         * Updates the horizontal and vertical displacement of the button's shadow
         * relative to the button's position.
         *
         * @param new_x_offset Horizontal shadow offset in pixels
         * @param new_y_offset Vertical shadow offset in pixels
         */
        void set_shadow_offset(int new_x_offset, int new_y_offset);
        

        /**
         * @brief Sets the shadow scale factor.
         *
         * Adjusts the scaling of the shadow relative to the button's size.
         *
         * @param new_scale_factor Shadow scale multiplier (e.g., 1.0 = normal size)
         */
        void set_shadow_scale_factor(float new_scale_factor);


        /**
         * @brief Sets the text displayed on the button.
         *
         * Updates the button's content string.
         *
         * @param new_text New text to display on the button
         */
        void set_content(const std::string& new_text);


        /**
         * @brief Sets the font file path for the button.
         *
         * Updates the path to the font file used for text rendering.
         * If the string is empty, the font path is not set and an error is logged.
         *
         * @param new_font_path Path to the font file
         */
        void set_font_path(const std::string& new_font_path);

        
        std::string get_font_path() const;


        /**
         * @brief Sets the font size for the button's text.
         *
         * Updates the font size used for rendering. Must be greater than 0.
         * If zero is passed, the font size is not changed and an error is logged.
         *
         * @param new_size Font size in points
         */
        void set_font_size(unsigned int new_size);


        // Color setters

        // Pallete 1

        // Sets the default background color for palette 1
        void set_background_color_1(SDL_Color new_color);

        // Sets the default border color for palette 1
        void set_border_color_1(SDL_Color new_color);

        // Sets the default content color for palette 1
        void set_content_color_1(SDL_Color new_color);

        // Sets the default shadow color for palette 1
        void set_shadow_color_1(SDL_Color new_color);

        // Sets the hovered background color for palette 1
        void set_background_color_hovered_1(SDL_Color new_color);

        // Sets the hovered border color for palette 1
        void set_border_color_hovered_1(SDL_Color new_color);

        // Sets the hovered content color for palette 1
        void set_content_color_hovered_1(SDL_Color new_color);

        // Sets the hovered shadow color for palette 1
        void set_shadow_color_hovered_1(SDL_Color new_color);

        // Sets the clicked background color for palette 1
        void set_background_color_clicked_1(SDL_Color new_color);

        // Sets the clicked border color for palette 1
        void set_border_color_clicked_1(SDL_Color new_color);

        // Sets the clicked content color for palette 1
        void set_content_color_clicked_1(SDL_Color new_color);

        // Sets the clicked shadow color for palette 1
        void set_shadow_color_clicked_1(SDL_Color new_color);


        // Pallete 2

        // Sets the default background color for palette 2
        void set_background_color_2(SDL_Color new_color);

        // Sets the default border color for palette 2
        void set_border_color_2(SDL_Color new_color);

        // Sets the default content color for palette 2
        void set_content_color_2(SDL_Color new_color);

        // Sets the default shadow color for palette 2
        void set_shadow_color_2(SDL_Color new_color);

        // Sets the hovered background color for palette 2
        void set_background_color_hovered_2(SDL_Color new_color);

        // Sets the hovered border color for palette 2
        void set_border_color_hovered_2(SDL_Color new_color);

        // Sets the hovered content color for palette 2
        void set_content_color_hovered_2(SDL_Color new_color);

        // Sets the hovered shadow color for palette 2
        void set_shadow_color_hovered_2(SDL_Color new_color);

        // Sets the clicked background color for palette 2
        void set_background_color_clicked_2(SDL_Color new_color);

        // Sets the clicked border color for palette 2
        void set_border_color_clicked_2(SDL_Color new_color);

        // Sets the clicked content color for palette 2
        void set_content_color_clicked_2(SDL_Color new_color);

        // Sets the clicked shadow color for palette 2
        void set_shadow_color_clicked_2(SDL_Color new_color);


        // Texture setters

        // Sets the content texture of the button (replaces content color or text rendering)
        void set_content_texture(SDL_Texture* new_texture);


        // ===== GUI ======


    private:

        // ===== MAIN LOGIC =====

        // Only onetime click realization in this version

        button_access_type click_access_type;        // Button click access type for click callback logic permission


        bool click_permission;                       // Button click permission flag


        bool hovered;                                // Button hover state
        void hover_check();                          // Button hover check method (to be called in the main loop)


        bool clicked;                                // Button click state
        bool clicked_tmp;                            // Button click state temp for callback block until the next click
        bool click_check();                          // Button click check method (to be called in the main loop)
        
        bool push_mode_on;                           // Current push display mode
        int press_offset;                            // Current press offset for push animation

        element_state current_element_state;

        // ===== MAIN LOGIC =====
        

        // ===== GUI ======

        unsigned int current_pallette_number; // 1 or 2

        // Pallette switch function - only by the extern logic inside
        // std::function<void()> pallette_switch_need_check;  
        void current_pallette_choose(unsigned int new_pallette_number);


        // Sizes

        unsigned int width_size;                       // Element width
        unsigned int height_size;                      // Element height

        element_rect_boundaries boundaries_points;      // Element rectangle bounds by the element_rect_boundaries struct

        void reset_boundaries_points();                // Element bounds automatic recalculation

        unsigned int border_width_size;                
        unsigned int border_radius_size;               


        element_form current_form;                     // Current element form by the element_form enum

        void reset_current_form();                     // Automatic current form reset


        int shadow_offset_x;    
        int shadow_offset_y;

        float shadow_scale_factor;                     // Shadow scale factor - multiplies basic element size to get shadow size


        // Content


        std::string font_path;                         // Font path for button text

        TTF_Font* ttf_font_link = nullptr;             // TTF Font pointer

        unsigned int font_size;                        // Content size


        std::string content;                           // Button text

        
        /**
         * @brief Sets the TTF font link for the button.
         *
         * Assigns a pointer to a TTF_Font used for rendering text.
         * If the pointer is null, the font is not set and an error is logged.
         *
         * @param new_ttf_font_link Pointer to a valid TTF_Font
         */
        void set_ttf_font_link(TTF_Font* new_ttf_font_link);


        // Variables for rendering with autoset 
        
        int content_w;  
        int content_h;

        bool content_dirty;

        // Text texture for rendering
        SDL_Texture* content_texture;

        
        /**
         * @brief Updates the button's text texture.
         * 
         * Creates a new SDL_Texture from the current content string, font, and specified color.
         * If the content is unchanged or no font/text is set, the function does nothing.
         * Any existing texture is destroyed before creating a new one.
         * The resulting texture dimensions are stored in content_w and content_h.
         * Marks the content as clean (content_dirty = false).
         */
        void update_content_texture(SDL_Renderer* renderer, SDL_Color new_color);


        // Button basic colors by SDL type  

        SDL_Color background_color_1;
        SDL_Color border_color_1;
        SDL_Color content_color_1;
        SDL_Color shadow_color_1;
        
        SDL_Color background_color_hovered_1;
        SDL_Color border_color_hovered_1;
        SDL_Color content_color_hovered_1;
        SDL_Color shadow_color_hovered_1;

        SDL_Color background_color_clicked_1;
        SDL_Color border_color_clicked_1;
        SDL_Color content_color_clicked_1;
        SDL_Color shadow_color_clicked_1;

        // Button additional colors for different states

        SDL_Color background_color_2;
        SDL_Color border_color_2;
        SDL_Color content_color_2;
        SDL_Color shadow_color_2;
        
        SDL_Color background_color_hovered_2;
        SDL_Color border_color_hovered_2;
        SDL_Color content_color_hovered_2;
        SDL_Color shadow_color_hovered_2;

        SDL_Color background_color_clicked_2;
        SDL_Color border_color_clicked_2;
        SDL_Color content_color_clicked_2;
        SDL_Color shadow_color_clicked_2;


        // Variables for final rendering
        SDL_Color render_background_color;
        SDL_Color render_border_color;
        SDL_Color render_content_color;
        SDL_Color render_shadow_color;


        // Inner pallette prepare method
        void button_pallette_prepare();
        
        // ===== GUI ======
};


// =========================================================================================== My_SDL_button class
