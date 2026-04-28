// my_sdl_texture.h

#pragma once

// =========================================================================================== IMPORT

#include "../my_sdl_element/my_sdl_element.h" // Base class import

// =========================================================================================== IMPORT

class My_SDL_texture : public My_SDL_element // SDL_Element
{
    public:


        // ===== CONSTRUCTOR AND DESTRUCTOR =====

        My_SDL_texture();                           // Texture constructor

        // TODO: model with ownership of texture and without ownership
        
        void delete_element() override;             // Texture delete (clear links + destructor call)   

        ~My_SDL_texture();                          // Texture destructor

        // ===== CONSTRUCTOR AND DESTRUCTOR =====   



        // ===== MAIN LOGIC =====

        // void update() override;  // Nothing now

        // ===== MAIN LOGIC =====


        // ===== GUI ======



        // Renders the texture, based on its current state and visual configuration.
        void render(SDL_Renderer* renderer) override; 


        // Render point

        /**
         * @brief Texture render point setter
         * 
         * Setup the texture center-center render point for the texture rendering
         * by the coordinate system of the WINDOW, which contains the element 
         * 
         * After that - reset anchor points.
         * 
         * @param x_cc_rp x coordinate of the center-center render point
         * @param y_cc_rp y coordinate of the center-center render point
         * 
         */
        void set_render_point(int x_cc_rp, int y_cc_rp) override;


        // TODO: rescale, crop, 

         /**
         * @brief Sets the texture size.
         *
         * @param new_w New width of the texture in pixels
         * @param new_h New height of the texture in pixels
         * 
         */
        void set_size(unsigned int new_w, unsigned int new_h);

        // Return the basic texture size (without scale) - just for some logic, which needs to know the size of the texture, but not to render it with this size
        void reset_size();


        /**
         * @brief Returns the texture's width.
         *
         * @return Width of the texture in pixels
         * 
         */
        unsigned int get_width_size() const;


        /**
         * @brief Returns the texture's height.
         *
         * @return Height of the texture in pixels
         * 
         */
        unsigned int get_height_size() const;



        /**
         * @brief Sets the texture, which would displayed with render().
         *
         * Updates the texture (with old texture delete) and reset sizes, then calls the
         * anchor points reset
         *
         * @param new_texture New texture to display
         * 
         */
        void set_texture(SDL_Texture* new_texture);


    protected:

        // ===== GUI ======

        // Texture for rendering
        SDL_Texture* texture;


        // Variables for rendering with autoset 
        
        int width_size;  
        int height_size;


        // Texture's override for anchor points reset function
        
        void reset_anchor_points() override;


        // ===== GUI ======

};