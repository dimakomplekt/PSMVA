// my_sdl_button.h


#pragma once


// =========================================================================================== IMPORT

#include <functional>                   // for std::function

#include "../../../engine/engine.h"     // SDL3 import

// =========================================================================================== IMPORT

// Button access type for click callback logic permission
enum button_access_type
{

    BUTTON_DEFAULT_CLICK_PERMISSION,        // Always can be clicked
    BUTTON_CLICK_EXTERN_CLICK_PERMISSION,   // Can be clicked only by the true return of the extern function for click permission check

};


class My_SDL_button
{


    public:

        // ===== CONSTRUCTOR AND DESTRUCTOR =====

        My_SDL_button();             // Button constructor
        ~My_SDL_button();            // Button destructor    

        // ===== CONSTRUCTOR AND DESTRUCTOR =====


        // ===== MAIN LOGIC =====

        // Button access type setter 
        void button_set_access_type(button_access_type new_access_type);

         // Button update method (to be called in the main loop)
        void button_update();                                      

        // Hover callback method
        std::function<void()> button_on_hover();                    

        // Extern click permission check callback method - to be called in the main loop if 
        // the button access type is BUTTON_CLICK_EXTERN_CLICK_PERMISSION
        std::function<bool()> button_extern_click_permission();

        // Click callback method - one call after click and blocked until the next
        std::function<void()> button_on_click();                    



        // ===== MAIN LOGIC =====


        // ===== GUI ======

        // Button render with logic by the button state flags (hovered, clicked)
        void button_render();

        // Button position setter
        void button_set_position(unsigned int x, unsigned int y);


        void set_position(unsigned int x, unsigned int y);
        void set_size(unsigned int width, unsigned int height);

        // Color setters

        void set_button_background_color(SDL_Color new_color);
        void set_button_border_color(SDL_Color new_color);
        void set_button_content_void(SDL_Color new_color);
        void set_button_background_color_hovered(SDL_Color new_color);
        void set_button_border_color_hovered(SDL_Color new_color);
        void set_button_content_color_void(SDL_Color new_color);
        void set_button_background_color_clicked(SDL_Color new_color);
        void set_button_border_color_clicked(SDL_Color new_color);
        void set_button_content_color_clicked(SDL_Color new_color);

        // ===== GUI ======


    protected:



    private:

        // ===== MAIN LOGIC =====

        bool button_hovered;                                // Button hover state
        bool button_hover_check();                          // Button hover check method (to be called in the main loop)


        // Only onetime click state

        button_access_type button_click_access_type;        // Button click access type for click callback logic permission

        bool button_click_permission_check();               // Button click check method (to be called in the main loop)
        bool button_click_permission;                       // Button click permission flag


        bool button_clicked;                                // Button click state
        bool button_clicked_tmp;                            // Button click state temp for callback block until the next click
        bool button_clicked_check();                        // Button click check method (to be called in the main loop)
        
        // ===== MAIN LOGIC =====
        

        // ===== GUI ======

        unsigned int button_x_size;
        unsigned int button_y_size;

        unsigned int button_boarder_size;
        unsigned int button_boarder_radius;

        unsigned int button_content_size;


        unsigned int button_x_c_position;
        unsigned int button_y_c_position;

        // Button color by SDL type  

        SDL_Color button_background_color;
        SDL_Color button_border_color;
        SDL_Color button_content_color;
        
        SDL_Color button_background_color_hovered;
        SDL_Color button_border_color_hovered;
        SDL_Color button_content_color_hovered;

        SDL_Color button_background_color_clicked;
        SDL_Color button_border_color_clicked;
        SDL_Color button_content_color_clicked;

        // ===== GUI ======

};
