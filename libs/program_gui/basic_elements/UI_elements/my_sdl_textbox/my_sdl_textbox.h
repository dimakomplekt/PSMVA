// my_sdl_textbox.h


#pragma once


// =========================================================================================== IMPORT

#include "../my_sdl_element/my_sdl_element.h" // Base class import

// =========================================================================================== IMPORT



class My_SDL_textbox : public My_SDL_element // SDL_Element
{
    public:

        // ===== CONSTRUCTOR AND DESTRUCTOR =====

        My_SDL_textbox();                           // Text constructor

        ~My_SDL_textbox();                          // Text destructor  (call in state.exit)  

        void delete_element() override;             // Text delete (clear links + destructor call)   

        // ===== CONSTRUCTOR AND DESTRUCTOR =====   


        // ===== MAIN LOGIC =====

        void update() override;

        // ===== MAIN LOGIC =====


        // ===== GUI ======


        /**
         * @brief Renders the text, based on its current state and visual configuration.
         *
         * 
         */
        void render(SDL_Renderer* renderer) override; 


        // Render point

        /**
         * @brief Text render point setter
         * 
         * Setup the text center-center render point for the text rendering
         * by the coordinate system of the WINDOW, which contains the element 
         * 
         * After that - reset anchor points.
         * 
         * 
         * @param x_cc_rp x coordinate of the center-center render point
         * @param y_cc_rp y coordinate of the center-center render point
         * 
         * 
         */
        void set_render_point(int x_cc_rp, int y_cc_rp) override;


        /**
         * @brief Returns the text's width.
         *
         * @return Width of the text in pixels
         * 
         */
        unsigned int get_width_size() const;


        /**
         * @brief Returns the text's height.
         *
         * @return Height of the text in pixels
         * 
         */
        unsigned int get_height_size() const;


        /**
         * @brief Sets the text displayed on the text.
         *
         * Updates the text's content string and reset content sizes, then calls the
         * anchor points reset
         *
         * @param new_text New text to display on the text
         * 
         */
        void set_content(const std::string& new_text);


        /**
         * @brief Sets the font file path for the text.
         *
         * Updates the path to the font file used for text rendering.
         * If the string is empty, the font path is not set and an error is logged.
         *
         * @param new_font_path Path to the font file
         * 
         */
        void set_font_path(const std::string& new_font_path);

        // Font path getter function
        std::string get_font_path() const;


        /**
         * @brief Sets the TTF font link for the text.
         *
         * Assigns a pointer to a TTF_Font used for rendering text.
         * If the pointer is null, the font is not set and an error is logged.
         *
         * @param new_ttf_font_link Pointer to a valid TTF_Font
         * 
         */
        void set_ttf_font_link(TTF_Font* new_ttf_font_link);


        /**
         * @brief Sets the font size for the text.
         *
         * Updates the font size used for rendering. Must be greater than 0.
         * If zero is passed, the font size is not changed and an error is logged.
         *
         * @param new_size Font size in points
         * 
         */
        void set_font_size(unsigned int new_size);


        /**
         * @brief Font size getter.
         *
         * Returns the font size value.
         *
         * @return Current font size value
         * 
         */
        unsigned int get_font_size() const;


        // Sets the default content color for palette 1
        void set_content_color(SDL_Color new_color);

        
        // Texture setters

        // Sets the content texture of the text (replaces content color or text rendering)
        void set_content_texture(SDL_Texture* new_texture);

        // ===== GUI ======


    // Friend classes access permission (for example - change something by call from )
    protected:

        // ===== GUI ======

        // Only one stroke realization in this version (Time isn't on my side... No it isn't! (c))

        // Content

        std::string font_path;                         // Font path for text

        TTF_Font* ttf_font_link = nullptr;             // TTF Font pointer

        unsigned int font_size;                        // Content size


        std::string content;                           // Text


        // Variables for rendering with autoset 
        
        int content_width_size;  
        int content_height_size;


        // Text's override for anchor points reset function
        
        void reset_anchor_points() override;


        // Flag for render recalculation after new content or new content settings set
        bool content_dirty;


        // Text texture for rendering
        SDL_Texture* content_texture;


        /**
         * @brief Updates the text texture.
         * 
         * Calls inside render
         * 
         * Creates a new SDL_Texture from the current content string, font, and specified color.
         * If the content is unchanged or no font/text is set, the function does nothing.
         * Any existing texture is destroyed before creating a new one.
         * The resulting texture dimensions are stored in content_width_size and content_height_size.
         * Marks the content as clean (content_dirty = false).
         * 
         */
        void update_content_texture(SDL_Renderer* renderer, SDL_Color new_color);

        // Color for text rendering
        SDL_Color content_render_color;

        // Text drawing inner function
        void text_draw(SDL_Renderer* renderer);

        // ===== GUI ======

};

// =========================================================================================== My_SDL_textbox class
