// my_sdl_panel.h


#pragma once


// =========================================================================================== IMPORT

#include <vector>                                   // For std::vector
#include "../my_sdl_element/my_sdl_element.h"       // Base class import

// =========================================================================================== IMPORT


// =========================================================================================== TYPES

// Struct for inner elements with local positioning
struct panel_inner_element
{

    My_SDL_element* element_pointer;

    int local_x_position;
    int local_y_position;

    unsigned int local_z_position;      // Current z for this element inside the panel

};

// =========================================================================================== TYPES


// =========================================================================================== My_SDL_panel class

class My_SDL_panel : public My_SDL_element
{

    public:

        // ===== MAIN LOGIC =====

        /**
         * @brief Updates the panel and all its inner elements.
         *
         * Calls update() on all registered inner elements.
         * 
         */
        void update() override;


        /**
         * @brief Adds an element to the panel at specified local coordinates.
         *
         * The element's position will be relative to the panel's center.
         * Call element render position setters by the element type. in dependence
         * of current panel position
         * 
         * Setup the parent_panel atribute link inside base class by this-> in implementation
         * 
         * Sorts the inner_elements list by the local-z increase inside. 
         *
         * @param element_pointer Pointer to the element to add
         * @param local_x Local X position relative to tl-point
         * @param local_y Local Y position relative to tl-point
         * @param local_z Local Z position relative to the current panel
         * 
         */
        void add_element(My_SDL_element* element_pointer, int local_x, int local_y, unsigned int local_z);


        /**
         * @brief Removes an element from the panel and call it's destructor.
         *
         * @param element_pointer Pointer to the element to remove
         * 
         */
        void remove_element(My_SDL_element* element_pointer);


        /**
         * @brief Clears all elements from the panel and call their destructors.
         * 
         * Just the iterative call of the remove_element(My_SDL_element* element_pointer) by vector
         * 
         */
        void clear_elements();


        /**
         * @brief Change the element coordinates by the new local coordinates inside the panel.
         *
         * The element's position will be relative to the panel's center.
         * Call element render position setters by the element type. in dependence
         * of current panel position
         * 
         * Sorts the inner_elements list by the local-z increase inside. 
         *
         * @param element_pointer Pointer to the element to add
         * @param new_local_x New local X position relative to tl-point
         * @param new_local_y New local Y position relative to tl-point
         * @param new_local_z New local Z position relative to the current panel
         * 
         */
        void change_element_local_coordinate(My_SDL_element* element_pointer, int new_local_x, int new_local_y, unsigned int new_local_z);


        // ===== MAIN LOGIC =====


        // ===== GUI =====

        /**
         * @brief Renders the panel and all its inner elements.
         *
         * Draws the panel's background, border, and shadow, then renders all inner elements
         * with their positions adjusted to the panel's coordinate system.
         *
         * @param renderer SDL renderer for drawing
         * 
         */
        void render(SDL_Renderer* renderer) override;


        /**
         * @brief Sets the panel's render point (center position).
         *
         * Updates the panel's position and adjusts the render points of all inner elements accordingly.
         *
         * @param x_cc_rp X coordinate of the center-center render point
         * @param y_cc_rp Y coordinate of the center-center render point
         * 
         */
        void set_render_point(int x_cc_rp, int y_cc_rp) override;


        /**
         * @brief Sets the panel's size.
         *
         * @param new_width New width of the panel in pixels
         * @param new_height New height of the panel in pixels
         * 
         */
        void set_size(unsigned int new_width, unsigned int new_height);


        /**
         * @brief Gets the panel's width.
         *
         * @return Width of the panel in pixels
         * 
         */
        unsigned int get_width_size() const;

        /**
         * @brief Gets the panel's height.
         *
         * @return Height of the panel in pixels
         * 
         */
        unsigned int get_height_size() const;


        /**
         * @brief Sets the border width.
         *
         * @param new_size New border width in pixels
         * 
         */
        void set_border_width_size(unsigned int new_size);


        /**
         * @brief Sets the border radius for rounded corners.
         *
         * @param new_radius_size New border radius in pixels
         * 
         */
        void set_border_radius_size(unsigned int new_radius_size);


        /**
         * @brief Sets the shadow offset.
         *
         * @param new_x_offset X offset for the shadow
         * @param new_y_offset Y offset for the shadow
         * 
         */
        void set_shadow_offset(int new_x_offset, int new_y_offset);


        /**
         * @brief Sets the shadow scale factor.
         *
         * @param new_scale_factor Scale factor for the shadow size
         * 
         */
        void set_shadow_scale_factor(float new_scale_factor);


        // Color setters

        // Sets the default background color for the panel.
        void set_panel_background_color(SDL_Color new_color);

        // Sets the default border color for the panel.
        void set_panel_border_color(SDL_Color new_color);

        // Sets the default shadow color for the panel.
        void set_panel_shadow_color(SDL_Color new_color);

        // ===== GUI =====

    protected:

        // ===== CONSTRUCTOR AND DESTRUCTOR =====

        /**
         * @brief Constructor for My_SDL_panel.
         *
         * Initializes default values for size, colors, and styling.
         */
        My_SDL_panel();

        /**
         * @brief Destructor for My_SDL_panel.
         */
        ~My_SDL_panel() = default;

        // ===== CONSTRUCTOR AND DESTRUCTOR =====


    private:

        // ===== MAIN LOGIC =====

        // Container for inner elements - fills by add_element() and used inside 
        // the update_elements_positions() and clear elements 
        std::vector<panel_inner_element> inner_elements;

        // Setup the new element position (atribute inside basic class) after operations, which could change them,
        // like element add inside the panel
        void update_inner_element_position(My_SDL_element* element_pointer, int local_x, int local_y);

        // Inner elements position update (calls with panel coordinates switch)
        void update_elements_positions();


        // Panel override for anchor points reset function

        void anchor_points_reset() override;

        // ===== MAIN LOGIC =====


        // ===== GUI =====

        // Panel dimensions

        unsigned int panel_width_size;
        unsigned int panel_height_size;


        // Styling attributes

        unsigned int border_width_size;
        unsigned int border_radius_size;

        int shadow_offset_x;
        int shadow_offset_y;

        float shadow_scale_factor;


        // Colors

        SDL_Color background_color;
        SDL_Color border_color;
        SDL_Color shadow_color;

        // ===== GUI =====

};

// =========================================================================================== My_SDL_panel class
