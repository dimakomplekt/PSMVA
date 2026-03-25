// my_sdl_button.h


#pragma once


// =========================================================================================== IMPORT

#include <functional>                                   // for std::function
#include <cmath>                                        // for std::round()


#include "../../../engine/engine.h"                     // SDL3 and SDL ttf import

#include "../basic_figures_draw/basic_figures_draw.h"   // Basic figures

// =========================================================================================== IMPORT


// =========================================================================================== IMPORT


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

// Button signal type for GUI change logic
enum button_gui_type
{

    STATIC_BUTTON_GUI,        // One color pallette
    DYNAMIC_BUTTON_GUI,       // Different color pallettes for different extern logic

};


struct element_rect_boundaries
{

    int left_boundary;
    int right_boundary;
    int top_boundary;
    int bottom_boundary;

};

enum button_state
{

    DEFAULT_BS,
    HOVERED_BS,
    CLICKED_BS

};

// =========================================================================================== TYPES


class My_SDL_button
{

    public:

        // ===== CONSTRUCTOR AND DESTRUCTOR =====

        My_SDL_button();                            // Button constructor
        ~My_SDL_button();                           // Button destructor    

        // ===== CONSTRUCTOR AND DESTRUCTOR =====


        // ===== MAIN LOGIC =====

        
        // Element logic global update method (to be called in the main loop)
        void update();                                      


        /**
         * @brief Button access type setter 
         * 
         * Setup the button access type for click permission logic by the
         * button_access_type enum values
         * 
         * @param new_access_type - one of the two button_access_type enum values 
         */
        void set_access_type(button_access_type new_access_type);

        void push_mode_switch();

        // Extern click permission check callback method - to be called in the main loop if 
        // the button access type is BUTTON_CLICK_EXTERN_CLICK_PERMISSION
        std::function<bool()> extern_click_permission;

        // Hover callback method
        std::function<void()> on_hover;                    

        // Click callback method - one call after click and blocked until the next
        std::function<void()> on_click;     
        
        
        std::function<unsigned int()> get_required_palette;      

        // ===== MAIN LOGIC =====


        // ===== GUI ======

        // Button render with logic by the button state flags (hovered, clicked)
        void render(SDL_Renderer* renderer);


        /**
         * @brief GUI type setter
         * 
         * Choose the gui type (static or dynamic) for the button by the button_gui_type enum values
         * 
         * @param new_gui_type one of the two button_gui_type enum values
         * 
         */
        void set_gui_type(button_gui_type new_gui_type);


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
        void set_render_point(int x_cc_rp, int y_cc_rp);


        // Horizontal size getter
        int get_x_render_point() const;

        // Vertical size getter
        int get_y_render_point() const;


        // Size

        // Button size setter
        void set_size(unsigned int new_width, unsigned int new_height);

        // Horizontal size getter
        unsigned int get_width_size() const;

        // Vertical size getter
        unsigned int get_height_size() const;


        // Styling


        void set_border_width_size(unsigned int new_size);

        void set_border_radius(unsigned int new_size);


        // Shadow offset setter
        void set_shadow_offset(int new_x_offset, int new_y_offset);
        
        void set_shadow_scale_factor(float new_scale_factor);


        // Set the text displayed on the button
        void set_content(const std::string& new_text);

        // Set ttf font
        void set_ttf_font_link(TTF_Font* new_ttf_font_link);

        // Set font file path
        void set_font_path(const std::string& new_font_path);

        // Set font size
        void set_font_size(unsigned int new_size);


        // Opacity
        void set_opacity(Uint8 new_opacity);


        // Color setters

        void set_background_color_1(SDL_Color new_color);
        void set_border_color_1(SDL_Color new_color);
        void set_content_color_1(SDL_Color new_color);
        void set_shadow_color_1(SDL_Color new_color);
        void set_background_color_hovered_1(SDL_Color new_color);
        void set_border_color_hovered_1(SDL_Color new_color);
        void set_content_color_hovered_1(SDL_Color new_color);
        void set_shadow_color_hovered_1(SDL_Color new_color);
        void set_background_color_clicked_1(SDL_Color new_color);
        void set_border_color_clicked_1(SDL_Color new_color);
        void set_content_color_clicked_1(SDL_Color new_color);
        void set_shadow_color_clicked_1(SDL_Color new_color);

        void set_background_color_2(SDL_Color new_color);
        void set_border_color_2(SDL_Color new_color);
        void set_content_color_2(SDL_Color new_color);
        void set_shadow_color_2(SDL_Color new_color);
        void set_background_color_hovered_2(SDL_Color new_color);
        void set_border_color_hovered_2(SDL_Color new_color);
        void set_content_color_hovered_2(SDL_Color new_color);
        void set_shadow_color_hovered_2(SDL_Color new_color);
        void set_background_color_clicked_2(SDL_Color new_color);
        void set_border_color_clicked_2(SDL_Color new_color);
        void set_content_color_clicked_2(SDL_Color new_color);
        void set_shadow_color_clicked_2(SDL_Color new_color);


        // Texture setters

        void set_background_texture(SDL_Texture* new_texture);

        void set_border_texture(SDL_Texture* new_texture);
        
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
        
        bool push_mode_on;
        int press_offset;

        button_state current_element_state;

        // ===== MAIN LOGIC =====
        

        // ===== GUI ======

        // Render points (center-center)

        // Center-center x-render point
        int x_render_point;

        // Center-center y-render point
        int y_render_point;


        // Sizes

        unsigned int width_size;
        unsigned int height_size;

        element_rect_boundaries boundaries_points;     // Element rectangle bounds by the 

        void reset_boundaries_points();                // Element bounds automatic recalculation

        unsigned int border_width_size;
        unsigned int border_radius_size;


        element_form current_form;

        void reset_current_form();


        int shadow_offset_x;
        int shadow_offset_y;

        float shadow_scale_factor;

        unsigned int font_size;


        // Content

        // TTF Font pointer
        TTF_Font* ttf_font_link = nullptr;

        // Font path for button text
        std::string font_path;

        // Button text
        std::string content;

        int content_w;
        int content_h;

        bool content_dirty;


        // Button opacity by 
        // calling of commands like
        // SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g, background_color.b, alpha);
        // before rendering
        Uint8 opacity; // 0 = fully transperent, 255 = fully opaque

        // GUI type
        button_gui_type gui_type;

        unsigned int current_pallette_number; // 1 or 2

        // Pallette switch function - only by the extern logic inside
        // std::function<void()> pallette_switch_need_check;  
        void current_pallette_choose(unsigned int new_pallette_number);


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

        // Button textures by SDL type

        // Text texture for rendering
        SDL_Texture* background_texture;
        
        // Text texture for rendering
        SDL_Texture* border_texture;


        SDL_Texture* content_texture;

        void update_content_texture(SDL_Renderer* renderer, SDL_Color new_color);

        
        // ===== GUI ======
};
