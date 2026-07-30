// 1.2_MASKS_SETUP.cpp


// =========================================================================================== IMPORT

#include "1.2_MASKS_SETUP.h"


#include "../../../../program_gui/basic_elements/UI_elements/my_sdl_textbox/my_sdl_textbox.h"
#include "../../../../program_gui/basic_elements/UI_elements/my_sdl_panel/my_sdl_panel.h"
#include "../../../../program_gui/basic_elements/UI_elements/my_sdl_texture/my_sdl_texture.h"
#include "../../../../program_gui/basic_elements/UI_elements/my_sdl_button/my_sdl_button.h"
#include "../../../../program_gui/basic_elements/UI_elements/my_sdl_fader/my_sdl_fader.h"

// Predeclare for switching states
#include "../../program_states.h"

#include "../../../app.h"

// Log
#include <iostream>


// Math
#include <algorithm>


// Check
#include "../1.1_FILE_CHOOSE/1.1_FILE_CHOOSE.h"

// =========================================================================================== IMPORT


// =========================================================================================== DEFINES

#define FILES_QUANTITY 6
#define MASKS_QUANTITY 3

#define MASK_1_FADERS_QUANTITY 6
// =========================================================================================== DEFINES


// =========================================================================================== STATE DATA

// RAII + lifecycle management

// ===== Main panel ===== 

My_SDL_panel* Masks_setup_panel_ms_1 = nullptr;

// ===== Main panel ===== 


// ===== Video preview =====

My_SDL_texture* Video_preview_texture_ms_1 = nullptr;

My_SDL_panel* Video_preview_panel_ms_1 = nullptr;

// ===== Video preview =====


// ===== File choose =====

My_SDL_textbox* File_choose_textbox_ms_1 = nullptr;

My_SDL_button* File_1_button_ms_1 = nullptr;
My_SDL_button* File_2_button_ms_1 = nullptr;
My_SDL_button* File_3_button_ms_1 = nullptr;
My_SDL_button* File_4_button_ms_1 = nullptr;
My_SDL_button* File_5_button_ms_1 = nullptr;
My_SDL_button* File_6_button_ms_1 = nullptr;


My_SDL_panel* File_choose_panel_ms_1 = nullptr;

// ===== File choose =====


// ===== Mask choose =====

My_SDL_textbox* Mask_choose_textbox_ms_1 = nullptr;

My_SDL_button* Mask_1_choose_button_ms_1 = nullptr;
My_SDL_button* Mask_2_choose_button_ms_1 = nullptr;
My_SDL_button* Mask_3_choose_button_ms_1 = nullptr;


My_SDL_button* Save_preset_button_ms_1 = nullptr;
My_SDL_button* Load_preset_button_ms_1 = nullptr;


My_SDL_panel* Masks_choose_panel_ms_1 = nullptr;

// ===== Mask choose =====


// ===== MASK 1 panel =====

My_SDL_textbox* Mask_1_par_1_textbox_ms_1 = nullptr;
My_SDL_fader* Mask_1_par_1_fader_ms_1 = nullptr;

My_SDL_textbox* Mask_1_par_2_textbox_ms_1 = nullptr;
My_SDL_fader* Mask_1_par_2_fader_ms_1 = nullptr;

My_SDL_textbox* Mask_1_par_3_textbox_ms_1 = nullptr;
My_SDL_fader* Mask_1_par_3_fader_ms_1 = nullptr;

My_SDL_textbox* Mask_1_par_4_textbox_ms_1 = nullptr;
My_SDL_fader* Mask_1_par_4_fader_ms_1 = nullptr;


My_SDL_panel* Mask_1_setup_panel_ms_1 = nullptr;

// ===== MASK 1 panel =====


// ===== MASK 2 panel =====

My_SDL_textbox* Mask_2_par_1_textbox_ms_1 = nullptr;
My_SDL_fader* Mask_2_par_1_fader_ms_1 = nullptr;

My_SDL_textbox* Mask_2_par_2_textbox_ms_1 = nullptr;
My_SDL_fader* Mask_2_par_2_fader_ms_1 = nullptr;

My_SDL_textbox* Mask_2_par_3_textbox_ms_1 = nullptr;
My_SDL_fader* Mask_2_par_3_fader_ms_1 = nullptr;

My_SDL_textbox* Mask_2_par_4_textbox_ms_1 = nullptr;
My_SDL_fader* Mask_2_par_4_fader_ms_1 = nullptr;


My_SDL_panel* Mask_2_setup_panel_ms_1 = nullptr;

// ===== MASK 2 panel =====



// ===== MASK 3 panel =====

My_SDL_textbox* Mask_3_par_1_textbox_ms_1 = nullptr;
My_SDL_fader* Mask_3_par_1_fader_ms_1 = nullptr;

My_SDL_textbox* Mask_3_par_2_textbox_ms_1 = nullptr;
My_SDL_fader* Mask_3_par_2_fader_ms_1 = nullptr;

My_SDL_textbox* Mask_3_par_3_textbox_ms_1 = nullptr;
My_SDL_fader* Mask_3_par_3_fader_ms_1 = nullptr;

My_SDL_textbox* Mask_3_par_4_textbox_ms_1 = nullptr;
My_SDL_fader* Mask_3_par_4_fader_ms_1 = nullptr;


My_SDL_panel* Mask_3_setup_panel_ms_1 = nullptr;

// ===== MASK 3 panel =====



// ===== State change =====

My_SDL_button* file_choose_state_but_ms_1 = nullptr;

My_SDL_button* flow_parameters_calculation_state_but_ms_1 = nullptr;

// ===== State change =====


// =========================================================================================== STATE DATA


// =========================================================================================== CALLBACKS

void file_1_choose();
void file_2_choose();
void file_3_choose();
void file_4_choose();
void file_5_choose();
void file_6_choose();

void mask_1_choose();
void mask_2_choose();
void mask_3_choose();


void save_preset();
void load_preset();

void previous_state();
void next_state();

// =========================================================================================== CALLBACKS


// =========================================================================================== CLICK PERMISSION FUNCTIONS

bool file_1_choose_permission();
bool file_2_choose_permission();
bool file_3_choose_permission();
bool file_4_choose_permission();
bool file_5_choose_permission();
bool file_6_choose_permission();


bool next_state_permission();

// =========================================================================================== CLICK PERMISSION FUNCTIONS


// =========================================================================================== OPENCV PART OF THE STATE

// ===== Data =====


// Global capture
cv::VideoCapture* video_capture_device_ms_1 = nullptr; 

// Global MAT for capture frames
cv::Mat* video_cv_mat_ms_1 = nullptr;

// Global texture for test_cv_mat_translation
SDL_Texture* translated_texture_ms_1 = nullptr; 

bool video_reset_opencv_data_ms_1 = false;



// ===== Functions =====

void opencv_setup_ms_1();

void opencv_update_ms_1();

void opencv_render_by_translator_ms_1(SDL_Renderer* renderer);

void opencv_free_and_nullptr_ms_1();

// =========================================================================================== OPENCV PART OF THE STATE


// Video preview


// =========================================================================================== STATE DATA


// =========================================================================================== STATE INNER FUNCTIONS PREDECLARATION

void masks_setup_1_elements_create();

void masks_setup_1_elements_setup();

void masks_setup_1_elements_free_and_nullptr();

void masks_setup_1_elements_update();

void reset_passed_by_dictionary_textboxes_if_language_switched_ms_1();

void masks_setup_1_actions();

void masks_setup_1_elements_render(SDL_Renderer* renderer);

// =========================================================================================== STATE INNER FUNCTIONS PREDECLARATION


// =========================================================================================== MAIN STATE API


void masks_setup_1_enter()
{
    // Log the enter in console
    std::cout << "Entering MASKS_SETUP\n"; 

    // ===== State allocation =====

    masks_setup_1_elements_create();

    // ===== State allocation =====


    // Elements setup

    masks_setup_1_elements_setup();

    opencv_setup_ms_1();

}



void masks_setup_1_exit()
{
    // ===== State deallocation =====

    masks_setup_1_elements_free_and_nullptr();

    opencv_free_and_nullptr_ms_1();

    // ===== State deallocation =====


    // Log the exit in console

    std::cout << "Exiting MASKS_SETUP\n"; 

}


void masks_setup_1_update()
{
    // Update inputs
    if (App_timer_1.can_execute(Execute_zone_ID::HZ_1000))
    {
        App_inputs.update();
    }


    if (App_timer_1.can_execute(Execute_zone_ID::HZ_240))
    {

        masks_setup_1_elements_update();

        opencv_update_ms_1();

        masks_setup_1_actions();

    }
}


void masks_setup_1_render(SDL_Renderer* renderer)
{
    if (App_timer_1.can_execute(Execute_zone_ID::HZ_120))
    {
        masks_setup_1_elements_render(renderer);

        opencv_render_by_translator_ms_1(renderer);
    }
}




// =========================================================================================== MAIN STATE API




// =========================================================================================== INNER STATE FUNCTIONS


// =========================================================================================== STATE INNER FUNCTIONS REALIZATION

void masks_setup_1_elements_create()
{
    // Masks_setup panel create

    Masks_setup_panel_ms_1 = new My_SDL_panel;
    


    Video_preview_panel_ms_1 = new My_SDL_panel;
    Video_preview_texture_ms_1 = new My_SDL_texture;

    // ===== File choose =====

    File_choose_textbox_ms_1 = new My_SDL_textbox;

    File_1_button_ms_1 = new My_SDL_button;
    File_2_button_ms_1 = new My_SDL_button;
    File_3_button_ms_1 = new My_SDL_button;
    File_4_button_ms_1 = new My_SDL_button;
    File_5_button_ms_1 = new My_SDL_button;
    File_6_button_ms_1 = new My_SDL_button;

    File_choose_panel_ms_1 = new My_SDL_panel;

    // ===== File choose =====


    // ===== Mask choose =====

    Mask_choose_textbox_ms_1 = new My_SDL_textbox;

    Mask_1_choose_button_ms_1 = new My_SDL_button;
    Mask_2_choose_button_ms_1 = new My_SDL_button;
    Mask_3_choose_button_ms_1 = new My_SDL_button;

    Masks_choose_panel_ms_1 = new My_SDL_panel;


    Save_preset_button_ms_1 = new My_SDL_button;
    Load_preset_button_ms_1 = new My_SDL_button;

    // ===== Mask choose =====


    // ===== MASK 1 panel =====

    Mask_1_par_1_textbox_ms_1 = new My_SDL_textbox;
    Mask_1_par_1_fader_ms_1 = new My_SDL_fader;

    Mask_1_par_2_textbox_ms_1 = new My_SDL_textbox;
    Mask_1_par_2_fader_ms_1 = new My_SDL_fader;

    Mask_1_par_3_textbox_ms_1 = new My_SDL_textbox;
    Mask_1_par_3_fader_ms_1 = new My_SDL_fader;

    Mask_1_par_4_textbox_ms_1 = new My_SDL_textbox;
    Mask_1_par_4_fader_ms_1 = new My_SDL_fader;

    Mask_1_setup_panel_ms_1 = new My_SDL_panel;

    // ===== MASK 1 panel =====


    // ===== MASK 2 panel =====

    Mask_2_par_1_textbox_ms_1 = new My_SDL_textbox;
    Mask_2_par_1_fader_ms_1 = new My_SDL_fader;

    Mask_2_par_2_textbox_ms_1 = new My_SDL_textbox;
    Mask_2_par_2_fader_ms_1 = new My_SDL_fader;

    Mask_2_par_3_textbox_ms_1 = new My_SDL_textbox;
    Mask_2_par_3_fader_ms_1 = new My_SDL_fader;

    Mask_2_par_4_textbox_ms_1 = new My_SDL_textbox;
    Mask_2_par_4_fader_ms_1 = new My_SDL_fader;

    Mask_2_setup_panel_ms_1 = new My_SDL_panel;

    // ===== MASK 2 panel =====



    // ===== MASK 3 panel =====

    Mask_3_par_1_textbox_ms_1 = new My_SDL_textbox;
    Mask_3_par_1_fader_ms_1 = new My_SDL_fader;

    Mask_3_par_2_textbox_ms_1 = new My_SDL_textbox;
    Mask_3_par_2_fader_ms_1 = new My_SDL_fader;

    Mask_3_par_3_textbox_ms_1 = new My_SDL_textbox;
    Mask_3_par_3_fader_ms_1 = new My_SDL_fader;

    Mask_3_par_4_textbox_ms_1 = new My_SDL_textbox;
    Mask_3_par_4_fader_ms_1 = new My_SDL_fader;

    Mask_3_setup_panel_ms_1 = new My_SDL_panel;

    // ===== MASK 3 panel =====


    // ===== State change =====

    file_choose_state_but_ms_1 = new My_SDL_button;

    flow_parameters_calculation_state_but_ms_1 = new My_SDL_button;

    // ===== State change =====


}



// ===== SETUP DATA =====

// ===== Main sizes =====

// Static-size GUI

const int BACKGROUND_WIDTH  = MAIN_WINDOW_H_SIZE;
const int BACKGROUND_HEIGHT  = MAIN_WINDOW_V_SIZE;

const int SCREEN_MARGIN_0 = 25;
const int SCREEN_MARGIN_1 = 50;
const int SCREEN_MARGIN_2 = 100;


// Video panel

int video_width_ms_1= files_metadata.video_1_data.width;
int video_height_ms_1 = files_metadata.video_1_data.height; 

int video_panel_width_ms_1 = video_width_ms_1+ 2 * SCREEN_MARGIN_0;
int video_panel_height_ms_1 = video_height_ms_1 + 2 * SCREEN_MARGIN_0;


// Masks setup panels

int mask_setup_panel_width = BACKGROUND_WIDTH * 0.5 - SCREEN_MARGIN_1 - 0.5 * SCREEN_MARGIN_2;
int mask_setup_panel_height = 0.8 * (BACKGROUND_HEIGHT - 3 * SCREEN_MARGIN_1);


// Back / Forward buttons and save preset buttons

int control_buttons_width = 0.5 * (mask_setup_panel_width - SCREEN_MARGIN_2);
int control_buttons_height = mask_setup_panel_height * 0.25; // / 0.8 * 0.2


// Choose file and choose mask panels

int choose_panels_width = 0.5 * BACKGROUND_WIDTH - SCREEN_MARGIN_1 - 0.5 * SCREEN_MARGIN_2;
int choose_panels_height = 0.5 * (0.5 * BACKGROUND_HEIGHT - 3 * SCREEN_MARGIN_1 - control_buttons_height);


// Textboxes in choose panel

int header_textbox_width = 0.2 * choose_panels_width;
int header_textbox_height = choose_panels_height;

int file_choose_buttons_width_ms_1 = (choose_panels_width - header_textbox_width) / FILES_QUANTITY;
int file_choose_buttons_height_ms_1 = header_textbox_height;

int mask_choose_buttons_width = (choose_panels_width - header_textbox_width) / MASKS_QUANTITY;
int mask_choose_buttons_height = header_textbox_height;



// Panel 1 textbox and faders`

int faders_textboxes_width = 0.2 * (mask_setup_panel_width / 2 - 3 * SCREEN_MARGIN_0);

int faders_textboxes_height = static_cast<int>(std::min(

    (mask_setup_panel_height - SCREEN_MARGIN_0 - (0.5 * MASK_1_FADERS_QUANTITY) * SCREEN_MARGIN_0) / (0.5 * MASK_1_FADERS_QUANTITY),
    75.0

));


int faders_width = 0.8 * (mask_setup_panel_width / 2 - 3 * SCREEN_MARGIN_0);
int faders_height = faders_textboxes_height;

// ===== Main sizes =====



// ===== Main points =====


// Video panel

int video_panel_x_ms_1 = 0.25 * BACKGROUND_WIDTH;
int video_panel_y_ms_1 = 0.25 * BACKGROUND_HEIGHT;


// Masks setup panels

int mask_setup_panel_x = BACKGROUND_WIDTH - SCREEN_MARGIN_1 - 0.5 * mask_setup_panel_width;
int mask_setup_panel_y = SCREEN_MARGIN_1 + 0.5 * mask_setup_panel_height;


// Back / Forward buttons and save preset buttons

int prev_state_button_x = BACKGROUND_WIDTH - SCREEN_MARGIN_1 - SCREEN_MARGIN_2 - 3 * 0.5 * control_buttons_width;
int prev_state_button_y = BACKGROUND_HEIGHT - SCREEN_MARGIN_1 - 0.5 * control_buttons_height;

int next_state_button_x = prev_state_button_x + SCREEN_MARGIN_2 + 2 * 0.5 * control_buttons_width;
int next_state_button_y = prev_state_button_y;


int save_preset_button_x = SCREEN_MARGIN_1 + 0.5 * control_buttons_width;  
int save_preset_button_y = prev_state_button_y;  

int load_preset_button_x = save_preset_button_x + SCREEN_MARGIN_2 + 2 * 0.5 * control_buttons_width; 
int load_preset_button_y = prev_state_button_y; 


// Choose file and choose mask panels

int file_choose_panel_x_ms_1 = BACKGROUND_WIDTH / 4;
int file_choose_panel_y_ms_1 = BACKGROUND_HEIGHT / 2 + SCREEN_MARGIN_1 + 0.5 * choose_panels_height;

int masks_choose_panel_x_ms_1= BACKGROUND_WIDTH / 4;
int masks_choose_panel_y_ms_1 = file_choose_panel_y_ms_1 + choose_panels_height;

// ===== Main points =====





void masks_setup_1_elements_setup()
{
    // Masks setup panel

    Masks_setup_panel_ms_1->set_render_point(MAIN_WINDOW_H_SIZE / 2, MAIN_WINDOW_V_SIZE / 2);
    Masks_setup_panel_ms_1->set_size(MAIN_WINDOW_H_SIZE, MAIN_WINDOW_V_SIZE);
    Masks_setup_panel_ms_1->set_border_radius(0);



    // Video preview 

    Video_preview_panel_ms_1->set_render_point(video_panel_x_ms_1, video_panel_y_ms_1);
    Video_preview_panel_ms_1->set_size(video_panel_width_ms_1, video_panel_height_ms_1);
    Video_preview_panel_ms_1->set_border_radius(0);

    // Texture

    Video_preview_texture_ms_1->set_size(video_width_ms_1, video_height_ms_1);
    

    // Add texture in panel

    Video_preview_panel_ms_1->add_element(
        
        Video_preview_texture_ms_1,
        video_panel_width_ms_1 * 0.5,
        video_panel_height_ms_1 * 0.5,
        1
    
    );
    


    // File choose panel

    File_choose_panel_ms_1->set_render_point(file_choose_panel_x_ms_1, file_choose_panel_y_ms_1);
    File_choose_panel_ms_1->set_size(choose_panels_width, choose_panels_height);
    File_choose_panel_ms_1->set_border_radius(0);
    File_choose_panel_ms_1->set_shadow_scale_factor(0);

    File_choose_textbox_ms_1->set_content("F:");
    File_choose_textbox_ms_1->switch_textbox_type(ORDINARY_TEXT);


    // File 1 button

    File_1_button_ms_1->switch_button_textbox_type(ORDINARY_TEXT);
    File_1_button_ms_1->get_button_content_textbox()->set_content("1");
    File_1_button_ms_1->set_size(file_choose_buttons_width_ms_1, file_choose_buttons_height_ms_1);
    File_1_button_ms_1->on_click = file_1_choose;
    File_1_button_ms_1->extern_click_permission = file_1_choose_permission;
    File_1_button_ms_1->set_access_type(BUTTON_EXTERN_CLICK_PERMISSION);
    File_1_button_ms_1->set_border_radius(0);
    File_1_button_ms_1->set_shadow_scale_factor(0);


    // File 2 button

    File_2_button_ms_1->switch_button_textbox_type(ORDINARY_TEXT);
    File_2_button_ms_1->get_button_content_textbox()->set_content("2");
    File_2_button_ms_1->set_size(file_choose_buttons_width_ms_1, file_choose_buttons_height_ms_1);
    File_2_button_ms_1->on_click = file_2_choose;
    File_2_button_ms_1->extern_click_permission = file_2_choose_permission;
    File_2_button_ms_1->set_access_type(BUTTON_EXTERN_CLICK_PERMISSION);
    File_2_button_ms_1->set_border_radius(0);
    File_2_button_ms_1->set_shadow_scale_factor(0);


    // File 3 button

    File_3_button_ms_1->switch_button_textbox_type(ORDINARY_TEXT);
    File_3_button_ms_1->get_button_content_textbox()->set_content("3");
    File_3_button_ms_1->set_size(file_choose_buttons_width_ms_1, file_choose_buttons_height_ms_1);
    File_3_button_ms_1->on_click = file_3_choose;
    File_3_button_ms_1->extern_click_permission = file_3_choose_permission;
    File_3_button_ms_1->set_access_type(BUTTON_EXTERN_CLICK_PERMISSION);
    File_3_button_ms_1->set_border_radius(0);
    File_3_button_ms_1->set_shadow_scale_factor(0);


    // File 4 button

    File_4_button_ms_1->switch_button_textbox_type(ORDINARY_TEXT);
    File_4_button_ms_1->get_button_content_textbox()->set_content("4");
    File_4_button_ms_1->set_size(file_choose_buttons_width_ms_1, file_choose_buttons_height_ms_1);
    File_4_button_ms_1->on_click = file_4_choose;
    File_4_button_ms_1->extern_click_permission = file_4_choose_permission;
    File_4_button_ms_1->set_access_type(BUTTON_EXTERN_CLICK_PERMISSION);
    File_4_button_ms_1->set_border_radius(0);
    File_4_button_ms_1->set_shadow_scale_factor(0);


    // File 5 button

    File_5_button_ms_1->switch_button_textbox_type(ORDINARY_TEXT);
    File_5_button_ms_1->get_button_content_textbox()->set_content("5");
    File_5_button_ms_1->set_size(file_choose_buttons_width_ms_1, file_choose_buttons_height_ms_1);
    File_5_button_ms_1->on_click = file_5_choose;
    File_5_button_ms_1->extern_click_permission = file_5_choose_permission;
    File_5_button_ms_1->set_access_type(BUTTON_EXTERN_CLICK_PERMISSION);
    File_5_button_ms_1->set_border_radius(0);
    File_5_button_ms_1->set_shadow_scale_factor(0);


    // File 6 button

    File_6_button_ms_1->switch_button_textbox_type(ORDINARY_TEXT);
    File_6_button_ms_1->get_button_content_textbox()->set_content("6");
    File_6_button_ms_1->set_size(file_choose_buttons_width_ms_1, file_choose_buttons_height_ms_1);
    File_6_button_ms_1->on_click = file_6_choose;
    File_6_button_ms_1->extern_click_permission = file_6_choose_permission;
    File_6_button_ms_1->set_access_type(BUTTON_EXTERN_CLICK_PERMISSION);
    File_6_button_ms_1->set_border_radius(0);
    File_6_button_ms_1->set_shadow_scale_factor(0);


    // Add elements in panel

    File_choose_panel_ms_1->add_element(

        File_choose_textbox_ms_1,
        header_textbox_width / 2,
        choose_panels_height / 2,
        1

    );

    
    File_choose_panel_ms_1->add_element(

        File_1_button_ms_1,
        header_textbox_width + 0.5 * file_choose_buttons_width_ms_1,
        choose_panels_height / 2,
        1
        
    );


    File_choose_panel_ms_1->add_element(

        File_2_button_ms_1,
        header_textbox_width + 1.5 * file_choose_buttons_width_ms_1,
        choose_panels_height / 2,
        1
        
    );


    File_choose_panel_ms_1->add_element(

        File_3_button_ms_1,
        header_textbox_width + 2.5 * file_choose_buttons_width_ms_1,
        choose_panels_height / 2,
        1
        
    );


    File_choose_panel_ms_1->add_element(

        File_4_button_ms_1,
        header_textbox_width + 3.5 * file_choose_buttons_width_ms_1,
        choose_panels_height / 2,
        1
        
    );


    File_choose_panel_ms_1->add_element(

        File_5_button_ms_1,
        header_textbox_width + 4.5 * file_choose_buttons_width_ms_1,
        choose_panels_height / 2,
        1
        
    );


    File_choose_panel_ms_1->add_element(

        File_6_button_ms_1,
        header_textbox_width + 5.5 * file_choose_buttons_width_ms_1,
        choose_panels_height / 2,
        1
        
    );



    // Masks choose panel

    Masks_choose_panel_ms_1->set_render_point(masks_choose_panel_x_ms_1, masks_choose_panel_y_ms_1);
    Masks_choose_panel_ms_1->set_size(choose_panels_width, choose_panels_height);
    Masks_choose_panel_ms_1->set_border_radius(0);
    Masks_choose_panel_ms_1->set_shadow_scale_factor(0);

    Mask_choose_textbox_ms_1->set_content("M:");
    Mask_choose_textbox_ms_1->switch_textbox_type(ORDINARY_TEXT);


    // Mask 1 button

    Mask_1_choose_button_ms_1->switch_button_textbox_type(ORDINARY_TEXT);
    Mask_1_choose_button_ms_1->get_button_content_textbox()->set_content("1");
    Mask_1_choose_button_ms_1->set_size(mask_choose_buttons_width, mask_choose_buttons_height);
    Mask_1_choose_button_ms_1->on_click = mask_1_choose;
    Mask_1_choose_button_ms_1->set_border_radius(0);
    Mask_1_choose_button_ms_1->set_shadow_scale_factor(0);


    // Mask 2 button

    Mask_2_choose_button_ms_1->switch_button_textbox_type(ORDINARY_TEXT);
    Mask_2_choose_button_ms_1->get_button_content_textbox()->set_content("2");
    Mask_2_choose_button_ms_1->set_size(mask_choose_buttons_width, mask_choose_buttons_height);
    Mask_2_choose_button_ms_1->on_click = mask_2_choose;
    Mask_2_choose_button_ms_1->set_border_radius(0);
    Mask_2_choose_button_ms_1->set_shadow_scale_factor(0);


    // Mask 3 button

    Mask_3_choose_button_ms_1->switch_button_textbox_type(ORDINARY_TEXT);
    Mask_3_choose_button_ms_1->get_button_content_textbox()->set_content("3");
    Mask_3_choose_button_ms_1->set_size(mask_choose_buttons_width, mask_choose_buttons_height);
    Mask_3_choose_button_ms_1->on_click = mask_3_choose;
    Mask_3_choose_button_ms_1->set_border_radius(0);
    Mask_3_choose_button_ms_1->set_shadow_scale_factor(0);


    // Add elements to the panel

    Masks_choose_panel_ms_1->add_element(

        Mask_choose_textbox_ms_1,
        header_textbox_width / 2,
        choose_panels_height / 2,
        1
        
    );


    Masks_choose_panel_ms_1->add_element(

        Mask_1_choose_button_ms_1,
        header_textbox_width + 0.5 * mask_choose_buttons_width,
        choose_panels_height / 2,
        1
        
    );


    Masks_choose_panel_ms_1->add_element(

        Mask_2_choose_button_ms_1,
        header_textbox_width + 1.5 * mask_choose_buttons_width,
        choose_panels_height / 2,
        1
        
    );



    Masks_choose_panel_ms_1->add_element(

        Mask_3_choose_button_ms_1,
        header_textbox_width + 2.5 * mask_choose_buttons_width,
        choose_panels_height / 2,
        1
        
    );



    // Save preset button

    Save_preset_button_ms_1->set_render_point(save_preset_button_x, save_preset_button_y);
    Save_preset_button_ms_1->switch_button_textbox_type(HEADER_3);
    Save_preset_button_ms_1->get_button_content_textbox()->set_content(str_by_dictionary(gd_save_preset));
    Save_preset_button_ms_1->set_size(control_buttons_width, control_buttons_height);
    Save_preset_button_ms_1->on_click = save_preset;
    Save_preset_button_ms_1->set_border_radius(0);


    // Load preset button

    
    Load_preset_button_ms_1->set_render_point(load_preset_button_x, load_preset_button_y);
    Load_preset_button_ms_1->switch_button_textbox_type(HEADER_3);
    Load_preset_button_ms_1->get_button_content_textbox()->set_content(str_by_dictionary(gd_load_preset));
    Load_preset_button_ms_1->set_size(control_buttons_width, control_buttons_height);
    Load_preset_button_ms_1->on_click = load_preset;
    Load_preset_button_ms_1->set_border_radius(0);


    // State change buttons

    file_choose_state_but_ms_1->set_render_point(prev_state_button_x, prev_state_button_y);
    file_choose_state_but_ms_1->switch_button_textbox_type(HEADER_3);
    file_choose_state_but_ms_1->get_button_content_textbox()->set_content(str_by_dictionary(gd_masks_setup_exit));
    file_choose_state_but_ms_1->set_size(control_buttons_width, control_buttons_height);
    file_choose_state_but_ms_1->on_click = previous_state;
    file_choose_state_but_ms_1->set_border_radius(0);


    flow_parameters_calculation_state_but_ms_1->set_render_point(next_state_button_x, next_state_button_y);
    flow_parameters_calculation_state_but_ms_1->switch_button_textbox_type(HEADER_3);
    flow_parameters_calculation_state_but_ms_1->get_button_content_textbox()->set_content(str_by_dictionary(gd_calculation_start));
    flow_parameters_calculation_state_but_ms_1->set_size(control_buttons_width, control_buttons_height);
    flow_parameters_calculation_state_but_ms_1->on_click = next_state;
    flow_parameters_calculation_state_but_ms_1->extern_click_permission = next_state_permission;
    flow_parameters_calculation_state_but_ms_1->set_access_type(BUTTON_EXTERN_CLICK_PERMISSION);
    flow_parameters_calculation_state_but_ms_1->set_border_radius(0);



    // Mask 1 choose state - active at init

    Mask_1_setup_panel_ms_1->set_render_point(mask_setup_panel_x, mask_setup_panel_y);
    Mask_1_setup_panel_ms_1->set_size(mask_setup_panel_width, mask_setup_panel_height);
    Mask_1_setup_panel_ms_1->set_border_radius(0);


    // Panel 1 elements

    Mask_1_par_1_textbox_ms_1->set_content("P1:");
    Mask_1_par_1_textbox_ms_1->switch_textbox_type(ORDINARY_TEXT);

    Mask_1_par_1_fader_ms_1->set_knob_border_radius(5);
    Mask_1_par_1_fader_ms_1->set_knob_size(faders_width * 0.15, faders_height);
    Mask_1_par_1_fader_ms_1->set_slot_border_width_size(5);
    Mask_1_par_1_fader_ms_1->set_slot_size(faders_width, faders_height * 0.25);


    Mask_1_par_2_textbox_ms_1->set_content("P2:");
    Mask_1_par_2_textbox_ms_1->switch_textbox_type(ORDINARY_TEXT);

    Mask_1_par_2_fader_ms_1->set_knob_border_radius(5);
    Mask_1_par_2_fader_ms_1->set_knob_size(faders_width * 0.15, faders_height);
    Mask_1_par_2_fader_ms_1->set_slot_border_width_size(5);
    Mask_1_par_2_fader_ms_1->set_slot_size(faders_width, faders_height * 0.25);


    Mask_1_par_3_textbox_ms_1->set_content("P3:");
    Mask_1_par_3_textbox_ms_1->switch_textbox_type(ORDINARY_TEXT);

    Mask_1_par_3_fader_ms_1->set_knob_border_radius(5);
    Mask_1_par_3_fader_ms_1->set_knob_size(faders_width * 0.15, faders_height);
    Mask_1_par_3_fader_ms_1->set_slot_border_width_size(5);
    Mask_1_par_3_fader_ms_1->set_slot_size(faders_width, faders_height * 0.25);


    Mask_1_par_4_textbox_ms_1->set_content("P4:");
    Mask_1_par_4_textbox_ms_1->switch_textbox_type(ORDINARY_TEXT);

    Mask_1_par_4_fader_ms_1->set_knob_border_radius(5);
    Mask_1_par_4_fader_ms_1->set_knob_size(faders_width * 0.15, faders_height);
    Mask_1_par_4_fader_ms_1->set_slot_border_width_size(5);
    Mask_1_par_4_fader_ms_1->set_slot_size(faders_width, faders_height * 0.25);



    Mask_1_setup_panel_ms_1->add_element(

        Mask_1_par_1_textbox_ms_1,
        1 * SCREEN_MARGIN_0 + 0.5 * faders_textboxes_width,
        1 * SCREEN_MARGIN_0 + 0.5 *faders_textboxes_height,
        1

    );


    Mask_1_setup_panel_ms_1->add_element(

        Mask_1_par_1_fader_ms_1,
        2 * SCREEN_MARGIN_0 + 1 * faders_textboxes_width + 0.5 * faders_width,
        1 * SCREEN_MARGIN_0 + 0.5 *faders_textboxes_height,
        1

    );


    Mask_1_setup_panel_ms_1->add_element(

        Mask_1_par_2_textbox_ms_1,
        1 * SCREEN_MARGIN_0 + 0.5 * faders_textboxes_width,
        2 * SCREEN_MARGIN_0 + 1.5 * faders_textboxes_height,
        1

    );


    Mask_1_setup_panel_ms_1->add_element(

        Mask_1_par_2_fader_ms_1,
        2 * SCREEN_MARGIN_0 + 1 * faders_textboxes_width + 0.5 * faders_width,
        2 * SCREEN_MARGIN_0 + 1.5 * faders_textboxes_height,
        1

    );


    Mask_1_setup_panel_ms_1->add_element(

        Mask_1_par_3_textbox_ms_1,
        0.5 * mask_setup_panel_width + 1 * SCREEN_MARGIN_0 + 0.5 * faders_textboxes_width,
        1 * SCREEN_MARGIN_0 + 0.5 *faders_textboxes_height,
        1

    );


    Mask_1_setup_panel_ms_1->add_element(

        Mask_1_par_3_fader_ms_1,
        0.5 * mask_setup_panel_width + 2 * SCREEN_MARGIN_0 + 1 * faders_textboxes_width + 0.5 * faders_width,
        1 * SCREEN_MARGIN_0 + 0.5 *faders_textboxes_height,
        1

    );


    Mask_1_setup_panel_ms_1->add_element(

        Mask_1_par_4_textbox_ms_1,
        0.5 * mask_setup_panel_width + 1 * SCREEN_MARGIN_0 + 0.5 * faders_textboxes_width,
        2 * SCREEN_MARGIN_0 + 1.5 * faders_textboxes_height,
        1

    );


    Mask_1_setup_panel_ms_1->add_element(

        Mask_1_par_4_fader_ms_1,
        0.5 * mask_setup_panel_width + 2 * SCREEN_MARGIN_0 + 1 * faders_textboxes_width + 0.5 * faders_width,
        2 * SCREEN_MARGIN_0 + 1.5 * faders_textboxes_height,
        1

    );


    // Mask 2 choose state - inactive at init

    // Out of screen
    Mask_2_setup_panel_ms_1->set_render_point(2 * mask_setup_panel_x, mask_setup_panel_y);
    Mask_2_setup_panel_ms_1->set_size(mask_setup_panel_width, mask_setup_panel_height);
    Mask_2_setup_panel_ms_1->set_border_radius(0);
    

    // Panel 2 elements

    Mask_2_par_1_textbox_ms_1->set_content("P1:");
    Mask_2_par_1_textbox_ms_1->switch_textbox_type(ORDINARY_TEXT);

    Mask_2_par_1_fader_ms_1->set_knob_border_radius(5);
    Mask_2_par_1_fader_ms_1->set_knob_size(faders_width * 0.15, faders_height);
    Mask_2_par_1_fader_ms_1->set_slot_border_width_size(5);
    Mask_2_par_1_fader_ms_1->set_slot_size(faders_width, faders_height * 0.25);


    Mask_2_par_2_textbox_ms_1->set_content("P2:");
    Mask_2_par_2_textbox_ms_1->switch_textbox_type(ORDINARY_TEXT);

    Mask_2_par_2_fader_ms_1->set_knob_border_radius(5);
    Mask_2_par_2_fader_ms_1->set_knob_size(faders_width * 0.15, faders_height);
    Mask_2_par_2_fader_ms_1->set_slot_border_width_size(5);
    Mask_2_par_2_fader_ms_1->set_slot_size(faders_width, faders_height * 0.25);


    Mask_2_par_3_textbox_ms_1->set_content("P3:");
    Mask_2_par_3_textbox_ms_1->switch_textbox_type(ORDINARY_TEXT);

    Mask_2_par_3_fader_ms_1->set_knob_border_radius(5);
    Mask_2_par_3_fader_ms_1->set_knob_size(faders_width * 0.15, faders_height);
    Mask_2_par_3_fader_ms_1->set_slot_border_width_size(5);
    Mask_2_par_3_fader_ms_1->set_slot_size(faders_width, faders_height * 0.25);


    Mask_2_par_4_textbox_ms_1->set_content("P4:");
    Mask_2_par_4_textbox_ms_1->switch_textbox_type(ORDINARY_TEXT);

    Mask_2_par_4_fader_ms_1->set_knob_border_radius(5);
    Mask_2_par_4_fader_ms_1->set_knob_size(faders_width * 0.15, faders_height);
    Mask_2_par_4_fader_ms_1->set_slot_border_width_size(5);
    Mask_2_par_4_fader_ms_1->set_slot_size(faders_width, faders_height * 0.25);



    Mask_2_setup_panel_ms_1->add_element(

        Mask_2_par_1_textbox_ms_1,
        1 * SCREEN_MARGIN_0 + 0.5 * faders_textboxes_width,
        1 * SCREEN_MARGIN_0 + 0.5 *faders_textboxes_height,
        1

    );


    Mask_2_setup_panel_ms_1->add_element(

        Mask_2_par_1_fader_ms_1,
        2 * SCREEN_MARGIN_0 + 1 * faders_textboxes_width + 0.5 * faders_width,
        1 * SCREEN_MARGIN_0 + 0.5 *faders_textboxes_height,
        1

    );


    Mask_2_setup_panel_ms_1->add_element(

        Mask_2_par_2_textbox_ms_1,
        1 * SCREEN_MARGIN_0 + 0.5 * faders_textboxes_width,
        2 * SCREEN_MARGIN_0 + 1.5 * faders_textboxes_height,
        1

    );


    Mask_2_setup_panel_ms_1->add_element(

        Mask_2_par_2_fader_ms_1,
        2 * SCREEN_MARGIN_0 + 1 * faders_textboxes_width + 0.5 * faders_width,
        2 * SCREEN_MARGIN_0 + 1.5 * faders_textboxes_height,
        1

    );


    Mask_2_setup_panel_ms_1->add_element(

        Mask_2_par_3_textbox_ms_1,
        0.5 * mask_setup_panel_width + 1 * SCREEN_MARGIN_0 + 0.5 * faders_textboxes_width,
        1 * SCREEN_MARGIN_0 + 0.5 *faders_textboxes_height,
        1

    );


    Mask_2_setup_panel_ms_1->add_element(

        Mask_2_par_3_fader_ms_1,
        0.5 * mask_setup_panel_width + 2 * SCREEN_MARGIN_0 + 1 * faders_textboxes_width + 0.5 * faders_width,
        1 * SCREEN_MARGIN_0 + 0.5 *faders_textboxes_height,
        1

    );


    Mask_2_setup_panel_ms_1->add_element(

        Mask_2_par_4_textbox_ms_1,
        0.5 * mask_setup_panel_width + 1 * SCREEN_MARGIN_0 + 0.5 * faders_textboxes_width,
        2 * SCREEN_MARGIN_0 + 1.5 * faders_textboxes_height,
        1

    );


    Mask_2_setup_panel_ms_1->add_element(

        Mask_2_par_4_fader_ms_1,
        0.5 * mask_setup_panel_width + 2 * SCREEN_MARGIN_0 + 1 * faders_textboxes_width + 0.5 * faders_width,
        2 * SCREEN_MARGIN_0 + 1.5 * faders_textboxes_height,
        1

    );



    // Mask 3 choose state - inactive at init

    // Out of screen
    Mask_3_setup_panel_ms_1->set_render_point(2 * mask_setup_panel_x, mask_setup_panel_y);
    Mask_3_setup_panel_ms_1->set_size(mask_setup_panel_width, mask_setup_panel_height);
    Mask_3_setup_panel_ms_1->set_border_radius(0);


    // Panel 3 element

    Mask_3_par_1_textbox_ms_1->set_content("P1:");
    Mask_3_par_1_textbox_ms_1->switch_textbox_type(ORDINARY_TEXT);

    Mask_3_par_1_fader_ms_1->set_knob_border_radius(5);
    Mask_3_par_1_fader_ms_1->set_knob_size(faders_width * 0.15, faders_height);
    Mask_3_par_1_fader_ms_1->set_slot_border_width_size(5);
    Mask_3_par_1_fader_ms_1->set_slot_size(faders_width, faders_height * 0.25);


    Mask_3_par_2_textbox_ms_1->set_content("P2:");
    Mask_3_par_2_textbox_ms_1->switch_textbox_type(ORDINARY_TEXT);

    Mask_3_par_2_fader_ms_1->set_knob_border_radius(5);
    Mask_3_par_2_fader_ms_1->set_knob_size(faders_width * 0.15, faders_height);
    Mask_3_par_2_fader_ms_1->set_slot_border_width_size(5);
    Mask_3_par_2_fader_ms_1->set_slot_size(faders_width, faders_height * 0.25);


    Mask_3_par_3_textbox_ms_1->set_content("P3:");
    Mask_3_par_3_textbox_ms_1->switch_textbox_type(ORDINARY_TEXT);

    Mask_3_par_3_fader_ms_1->set_knob_border_radius(5);
    Mask_3_par_3_fader_ms_1->set_knob_size(faders_width * 0.15, faders_height);
    Mask_3_par_3_fader_ms_1->set_slot_border_width_size(5);
    Mask_3_par_3_fader_ms_1->set_slot_size(faders_width, faders_height * 0.25);


    Mask_3_par_4_textbox_ms_1->set_content("P4:");
    Mask_3_par_4_textbox_ms_1->switch_textbox_type(ORDINARY_TEXT);

    Mask_3_par_4_fader_ms_1->set_knob_border_radius(5);
    Mask_3_par_4_fader_ms_1->set_knob_size(faders_width * 0.15, faders_height);
    Mask_3_par_4_fader_ms_1->set_slot_border_width_size(5);
    Mask_3_par_4_fader_ms_1->set_slot_size(faders_width, faders_height * 0.25);



    Mask_3_setup_panel_ms_1->add_element(

        Mask_3_par_1_textbox_ms_1,
        1 * SCREEN_MARGIN_0 + 0.5 * faders_textboxes_width,
        1 * SCREEN_MARGIN_0 + 0.5 *faders_textboxes_height,
        1

    );


    Mask_3_setup_panel_ms_1->add_element(

        Mask_3_par_1_fader_ms_1,
        2 * SCREEN_MARGIN_0 + 1 * faders_textboxes_width + 0.5 * faders_width,
        1 * SCREEN_MARGIN_0 + 0.5 *faders_textboxes_height,
        1

    );


    Mask_3_setup_panel_ms_1->add_element(

        Mask_3_par_2_textbox_ms_1,
        1 * SCREEN_MARGIN_0 + 0.5 * faders_textboxes_width,
        2 * SCREEN_MARGIN_0 + 1.5 * faders_textboxes_height,
        1

    );


    Mask_3_setup_panel_ms_1->add_element(

        Mask_3_par_2_fader_ms_1,
        2 * SCREEN_MARGIN_0 + 1 * faders_textboxes_width + 0.5 * faders_width,
        2 * SCREEN_MARGIN_0 + 1.5 * faders_textboxes_height,
        1

    );


    Mask_3_setup_panel_ms_1->add_element(

        Mask_3_par_3_textbox_ms_1,
        0.5 * mask_setup_panel_width + 1 * SCREEN_MARGIN_0 + 0.5 * faders_textboxes_width,
        1 * SCREEN_MARGIN_0 + 0.5 *faders_textboxes_height,
        1

    );


    Mask_3_setup_panel_ms_1->add_element(

        Mask_3_par_3_fader_ms_1,
        0.5 * mask_setup_panel_width + 2 * SCREEN_MARGIN_0 + 1 * faders_textboxes_width + 0.5 * faders_width,
        1 * SCREEN_MARGIN_0 + 0.5 *faders_textboxes_height,
        1

    );


    Mask_3_setup_panel_ms_1->add_element(

        Mask_3_par_4_textbox_ms_1,
        0.5 * mask_setup_panel_width + 1 * SCREEN_MARGIN_0 + 0.5 * faders_textboxes_width,
        2 * SCREEN_MARGIN_0 + 1.5 * faders_textboxes_height,
        1

    );


    Mask_3_setup_panel_ms_1->add_element(

        Mask_3_par_4_fader_ms_1,
        0.5 * mask_setup_panel_width + 2 * SCREEN_MARGIN_0 + 1 * faders_textboxes_width + 0.5 * faders_width,
        2 * SCREEN_MARGIN_0 + 1.5 * faders_textboxes_height,
        1

    );

}


void masks_setup_1_elements_free_and_nullptr()
{
    // Free all elements


    
    // ===== Main panel ===== 

    Masks_setup_panel_ms_1->delete_element();

    // ===== Main panel ===== 


    // ===== File choose =====

    File_choose_panel_ms_1->delete_element();

    // ===== File choose =====


    // ===== Mask choose =====

    Masks_choose_panel_ms_1->delete_element();

    // ===== Mask choose =====


    // ===== MASK 1 panel =====

    Mask_1_setup_panel_ms_1->delete_element();

    // ===== MASK 1 panel =====


    // ===== MASK 2 panel =====

    Mask_2_setup_panel_ms_1->delete_element();

    // ===== MASK 2 panel =====


    // ===== MASK 3 panel =====

    Mask_3_setup_panel_ms_1->delete_element();

    // ===== MASK 3 panel =====



    // ===== State change =====

    Save_preset_button_ms_1->delete_element();
    Load_preset_button_ms_1->delete_element();


    file_choose_state_but_ms_1->delete_element();
    flow_parameters_calculation_state_but_ms_1->delete_element();
    
    // ===== State change =====



    // ========== Nullptr the pointers ==========

    // ===== Main panel ===== 

    Masks_setup_panel_ms_1 = nullptr;

    // ===== Main panel ===== 


    // ===== Video preview =====

    Video_preview_texture_ms_1 = nullptr;

    Video_preview_panel_ms_1 = nullptr;

    // ===== Video preview =====


    // ===== File choose =====

    File_choose_textbox_ms_1 = nullptr;

    File_1_button_ms_1 = nullptr;
    File_2_button_ms_1 = nullptr;
    File_3_button_ms_1 = nullptr;
    File_4_button_ms_1 = nullptr;
    File_5_button_ms_1 = nullptr;
    File_6_button_ms_1 = nullptr;


    File_choose_panel_ms_1 = nullptr;

    // ===== File choose =====


    // ===== Mask choose =====

    Mask_choose_textbox_ms_1 = nullptr;

    Mask_1_choose_button_ms_1 = nullptr;
    Mask_2_choose_button_ms_1 = nullptr;
    Mask_3_choose_button_ms_1 = nullptr;


    Save_preset_button_ms_1 = nullptr;
    Load_preset_button_ms_1 = nullptr;


    Masks_choose_panel_ms_1 = nullptr;

    // ===== Mask choose =====


    // ===== MASK 1 panel =====

    Mask_1_par_1_textbox_ms_1 = nullptr;
    Mask_1_par_1_fader_ms_1 = nullptr;

    Mask_1_par_2_textbox_ms_1 = nullptr;
    Mask_1_par_2_fader_ms_1 = nullptr;

    Mask_1_par_3_textbox_ms_1 = nullptr;
    Mask_1_par_3_fader_ms_1 = nullptr;

    Mask_1_par_4_textbox_ms_1 = nullptr;
    Mask_1_par_4_fader_ms_1 = nullptr;


    Mask_1_setup_panel_ms_1 = nullptr;

    // ===== MASK 1 panel =====


    // ===== MASK 2 panel =====

    Mask_2_par_1_textbox_ms_1 = nullptr;
    Mask_2_par_1_fader_ms_1 = nullptr;

    Mask_2_par_2_textbox_ms_1 = nullptr;
    Mask_2_par_2_fader_ms_1 = nullptr;

    Mask_2_par_3_textbox_ms_1 = nullptr;
    Mask_2_par_3_fader_ms_1 = nullptr;

    Mask_2_par_4_textbox_ms_1 = nullptr;
    Mask_2_par_4_fader_ms_1 = nullptr;


    Mask_2_setup_panel_ms_1 = nullptr;

    // ===== MASK 2 panel =====



    // ===== MASK 3 panel =====

    Mask_3_par_1_textbox_ms_1 = nullptr;
    Mask_3_par_1_fader_ms_1 = nullptr;

    Mask_3_par_2_textbox_ms_1 = nullptr;
    Mask_3_par_2_fader_ms_1 = nullptr;

    Mask_3_par_3_textbox_ms_1 = nullptr;
    Mask_3_par_3_fader_ms_1 = nullptr;

    Mask_3_par_4_textbox_ms_1 = nullptr;
    Mask_3_par_4_fader_ms_1 = nullptr;


    Mask_3_setup_panel_ms_1 = nullptr;

    // ===== MASK 3 panel =====

            

    // ===== State change =====

    file_choose_state_but_ms_1 = nullptr;

    flow_parameters_calculation_state_but_ms_1 = nullptr;

    // ===== State change =====

}


void masks_setup_1_elements_update()
{
    // Check if textboxes need content renew
    reset_passed_by_dictionary_textboxes_if_language_switched_ms_1();

    // Update all elements

    Masks_setup_panel_ms_1->update();


    Video_preview_panel_ms_1->update();


    File_choose_panel_ms_1->update();
    Masks_choose_panel_ms_1->update();


    Save_preset_button_ms_1->update();
    Load_preset_button_ms_1->update();


    Mask_1_setup_panel_ms_1->update();

    Mask_2_setup_panel_ms_1->update();

    Mask_3_setup_panel_ms_1->update();


    file_choose_state_but_ms_1->update();
    flow_parameters_calculation_state_but_ms_1->update();

}


void reset_passed_by_dictionary_textboxes_if_language_switched_ms_1()
{
    // Repeat content set if language switched
    if (App_lang.get_lang_reset_flag())
    {
        Save_preset_button_ms_1->get_button_content_textbox()->set_content(str_by_dictionary(gd_save_preset));
    
        Load_preset_button_ms_1->get_button_content_textbox()->set_content(str_by_dictionary(gd_load_preset));
    
        file_choose_state_but_ms_1->get_button_content_textbox()->set_content(str_by_dictionary(gd_masks_setup_exit));

        flow_parameters_calculation_state_but_ms_1->get_button_content_textbox()->set_content(str_by_dictionary(gd_calculation_start));
    }
}


void masks_setup_1_actions()
{
    // Switch the state to EXIT if EXIT pressed

    if (App_inputs.is_just_released(Key_actions::EXIT))
    {
        this_app.app_sm.request_state_change(MASKS_SETUP_ID);
    }

    // Switch the state to MAIN MENU if ENTER pressed

    if (App_inputs.is_just_released(Key_actions::ENTER))
    {
        if (*masks_data.file_2_masks.file_choose_state == true)
            this_app.app_sm.request_state_change(MASKS_SETUP_ID_2);
    }

}


void masks_setup_1_elements_render(SDL_Renderer* renderer)
{
    // Render all elements

    Masks_setup_panel_ms_1->render(renderer);


    Video_preview_panel_ms_1->render(renderer);


    File_choose_panel_ms_1->render(renderer);
    Masks_choose_panel_ms_1->render(renderer);


    Save_preset_button_ms_1->render(renderer);
    Load_preset_button_ms_1->render(renderer);


    Mask_1_setup_panel_ms_1->render(renderer);

    Mask_2_setup_panel_ms_1->render(renderer);

    Mask_3_setup_panel_ms_1->render(renderer);


    file_choose_state_but_ms_1->render(renderer);
    flow_parameters_calculation_state_but_ms_1->render(renderer);
    
}

// =========================================================================================== STATE INNER FUNCTIONS REALIZATION



// =========================================================================================== CALLBACKS

void file_1_choose()
{
    // 
}


void file_2_choose()
{
    // 
}


void file_3_choose()
{
    // 
}


void file_4_choose()
{
    // 
}


void file_5_choose()
{
    // 
}


void file_6_choose()
{
    // 
}



void mask_1_choose()
{
    // 
}


void mask_2_choose()
{
    // 
}


void mask_3_choose()
{
    // 
}




void save_preset()
{
    // 
}


void load_preset()
{
    // 
}



void previous_state()
{
    // 
}


void next_state()
{
    // 
}



// =========================================================================================== CALLBACKS


// =========================================================================================== CLICK PERMISSION FUNCTIONS

bool file_1_choose_permission()
{
    //
    return true;
}


bool file_2_choose_permission()
{
    //
    return false;
}


bool file_3_choose_permission()
{
    //
    return true;
}


bool file_4_choose_permission()
{
    //

    return true;


}



bool file_5_choose_permission()
{
    //

    return false;
}


bool file_6_choose_permission()
{
    //
    return true;
}



bool next_state_permission()
{
    //
    return true;
}



// =========================================================================================== CLICK PERMISSION FUNCTIONS



// =========================================================================================== OPENCV PART OF THE STATE

// ===== Functions =====

void opencv_setup_ms_1()
{
    //
}

void opencv_update_ms_1()
{
    //
}

void opencv_render_by_translator_ms_1(SDL_Renderer* renderer)
{
    //
}

void opencv_free_and_nullptr_ms_1()
{
    //
}

// =========================================================================================== OPENCV PART OF THE STATE