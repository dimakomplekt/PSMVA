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


// HELPER-FUNCTIONS (LOAD and SAVE presets, ...)
#include "1.2_MS_HELPER.h"

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

My_SDL_button* Video_backwards_button_ms_1 = nullptr;
My_SDL_button* Video_play_pause_button_ms_1 = nullptr;
My_SDL_button* Video_forward_button_ms_1 = nullptr;
My_SDL_button* Video_kingsize_button_ms_1 = nullptr;

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

My_SDL_textbox* Mask_1_par_5_textbox_ms_1 = nullptr;
My_SDL_fader* Mask_1_par_5_fader_ms_1 = nullptr;


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

My_SDL_textbox* Mask_2_par_5_textbox_ms_1 = nullptr;
My_SDL_fader* Mask_2_par_5_fader_ms_1 = nullptr;

My_SDL_textbox* Mask_2_par_6_textbox_ms_1 = nullptr;
My_SDL_fader* Mask_2_par_6_fader_ms_1 = nullptr;


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


void video_rewind_backwards_ms_1();

void video_play_or_pause_ms_1();

void video_rewind_forward_ms_1();

void video_show_kingsize_ms_1();



void file_1_choose_ms_1();
void file_2_choose_ms_1();
void file_3_choose_ms_1();
void file_4_choose_ms_1();
void file_5_choose_ms_1();
void file_6_choose_ms_1();

void mask_1_choose_ms_1();
void mask_2_choose_ms_1();
void mask_3_choose_ms_1();


void save_preset_ms_1();
void load_preset_ms_1();

void previous_state_ms_1();
void next_state_ms_1();

// =========================================================================================== CALLBACKS


// =========================================================================================== OPENCV PIPELINE SETUP FUNCTIONS

// Choosing functions 

// Mask higligths and processing setup (by click on the mask)

void choose_mask_1_ms_1();

void choose_mask_2_ms_1();

void choose_mask_3_ms_1();

// File higligths setup (by init of the state)

void choose_current_file_ms_1();


// Processing callbacks for every mask
void mask_1_processing_ms_1(cv::Mat* frame);

void mask_2_processing_ms_1(cv::Mat* frame);

void mask_3_processing_ms_1(cv::Mat* frame);

// =========================================================================================== OPENCV PIPELINE SETUP FUNCTIONS


// =========================================================================================== CHOOSEN MASK AND FILE HIGHLIGHT

struct mask_and_file_highlight_ctx
{
    int x_m;
    int y_m;
    int w_m;
    int h_m;


    int x_f;
    int y_f;
    int w_f;
    int h_f;

    int highlight_line_width;
    std::string highlight_hex_color;
};

mask_and_file_highlight_ctx highlight_ms_1;

void choosen_mask_and_file_init();

void highlight_choosen_mask_ms_1(SDL_Renderer* renderer);

void highlight_choosen_file_ms_1(SDL_Renderer* renderer);

void highlight_video_texture_ms_1(SDL_Renderer* renderer);

// =========================================================================================== CHOOSEN MASK AND FILE HIGHLIGHT



// =========================================================================================== CLICK PERMISSION FUNCTIONS

bool file_1_choose_ms_1_permission();
bool file_2_choose_ms_1_permission();
bool file_3_choose_ms_1_permission();
bool file_4_choose_ms_1_permission();
bool file_5_choose_ms_1_permission();
bool file_6_choose_ms_1_permission();


bool next_state_permission_ms_1();

// =========================================================================================== CLICK PERMISSION FUNCTIONS


// =========================================================================================== OPENCV PART OF THE STATE


// ===== Functions =====

void opencv_setup_ms_1();

void opencv_update_ms_1();

void opencv_render_by_translator_ms_1(SDL_Renderer* renderer);

void opencv_free_and_nullptr_ms_1();

// ===== Functions =====

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


// =========================================================================================== HELPERS


// ===== MASK 1 =====

void m_1_x_1_update_ms_1()
{
    int choosen_x_1 = Mask_1_par_1_fader_ms_1->fader_value_to_int_from_range(

        0,
        files_metadata.video_1_data.width

    );

    std::string mask_1_par_1_curr_value_to_show = 

        str_by_dictionary(gd_coordinate) + " X1: " + 
        std::to_string(choosen_x_1) + " " +
        str_by_dictionary(gd_pixels) + ".";


    Mask_1_par_1_textbox_ms_1->set_content(mask_1_par_1_curr_value_to_show);


    // Update value
    masks_data.file_1_masks.nozzle_mask.x_1 = choosen_x_1;

};


void m_1_y_1_update_ms_1()
{

    int choosen_y_1 = Mask_1_par_2_fader_ms_1->fader_value_to_int_from_range(

        0,
        files_metadata.video_1_data.height

    );

    std::string mask_1_par_2_curr_value_to_show = 

        str_by_dictionary(gd_coordinate) + " Y1: " + 
        std::to_string(choosen_y_1) + " " +
        str_by_dictionary(gd_pixels) + ".";


    Mask_1_par_2_textbox_ms_1->set_content(mask_1_par_2_curr_value_to_show);


    // Update value
    masks_data.file_1_masks.nozzle_mask.y_1 = choosen_y_1;

};


void m_1_x_2_update_ms_1()
{
    int choosen_x_2 = Mask_1_par_3_fader_ms_1->fader_value_to_int_from_range(

        0,
        files_metadata.video_1_data.width

    );

    std::string mask_1_par_3_curr_value_to_show = 

        str_by_dictionary(gd_coordinate) + " X2: " + 
        std::to_string(choosen_x_2) + " " +
        str_by_dictionary(gd_pixels) + ".";


    Mask_1_par_3_textbox_ms_1->set_content(mask_1_par_3_curr_value_to_show);


    // Update value
    masks_data.file_1_masks.nozzle_mask.x_2 = choosen_x_2;

};


void m_1_y_2_update_ms_1()
{
    int choosen_y_2 = Mask_1_par_4_fader_ms_1->fader_value_to_int_from_range(

        0,
        files_metadata.video_1_data.height

    );

    std::string mask_1_par_4_curr_value_to_show = 

        str_by_dictionary(gd_coordinate) + " Y1: " + 
        std::to_string(choosen_y_2) + " " +
        str_by_dictionary(gd_pixels) + ".";


    Mask_1_par_4_textbox_ms_1->set_content(mask_1_par_4_curr_value_to_show);


    // Update value
    masks_data.file_1_masks.nozzle_mask.y_2 = choosen_y_2;

};


void m_1_dn_update_ms_1()
{

    int choosen_diameter = Mask_1_par_5_fader_ms_1->fader_value_to_int_from_range(

        nozzle_diameters[0],
        nozzle_diameters[nozzle_diameters.size() - 1]

    );

    std::string mask_1_par_5_curr_value_to_show = 

        str_by_dictionary(gd_diameter) + ": " + 
        std::to_string(choosen_diameter) + " " +
        str_by_dictionary(gd_millimeters) + ".";


    Mask_1_par_5_textbox_ms_1->set_content(mask_1_par_5_curr_value_to_show);


    // Update value
    masks_data.file_1_masks.nozzle_mask.d_n = choosen_diameter;
}


void mask_1_faders_init_ms_1()
{

    // 1st call / 2nd call

    // ===== MASK 1 =====
    
    if (!masks_data.file_1_masks.nozzle_mask.initialized)
    {
        Mask_1_par_1_fader_ms_1->set_fader_value(0.5);
        Mask_1_par_2_fader_ms_1->set_fader_value(0.5);
        Mask_1_par_3_fader_ms_1->set_fader_value(0.5);
        Mask_1_par_4_fader_ms_1->set_fader_value(0.5);
        Mask_1_par_5_fader_ms_1->set_fader_value(0.5);

        // Block next 50% reinit
        masks_data.file_1_masks.nozzle_mask.initialized = true;

        masks_data.file_1_masks.nozzle_mask.mm_in_pixel = 0.0f;

        masks_data.file_1_masks.nozzle_mask.basic_axe_angle = 0.0f;

        masks_data.file_1_masks.nozzle_mask.axe_line_coefficients.a = 0.0f;
        masks_data.file_1_masks.nozzle_mask.axe_line_coefficients.b = 0.0f;
        masks_data.file_1_masks.nozzle_mask.axe_line_coefficients.c = 0.0f;

        masks_data.file_1_masks.nozzle_mask.axe_line_coefficients.calculated = false;
    }
    else
    {
        // Set the fader know and value, according to the early choosen

        // x_1 parameter value
        Mask_1_par_1_fader_ms_1->set_fader_value_by_int_from_range(

            masks_data.file_1_masks.nozzle_mask.x_1,
            0,
            files_metadata.video_1_data.width
        
        );

        // y_1 parameter value
        Mask_1_par_2_fader_ms_1->set_fader_value_by_int_from_range(

            masks_data.file_1_masks.nozzle_mask.y_1,
            0,
            files_metadata.video_1_data.height
        
        );

        // x_2 parameter value
        Mask_1_par_3_fader_ms_1->set_fader_value_by_int_from_range(

            masks_data.file_1_masks.nozzle_mask.x_2,
            0,
            files_metadata.video_1_data.width
        
        );

        // y_2 parameter value
        Mask_1_par_4_fader_ms_1->set_fader_value_by_int_from_range(

            masks_data.file_1_masks.nozzle_mask.y_2,
            0,
            files_metadata.video_1_data.height
        
        );

        // d_n parameter value
        Mask_1_par_5_fader_ms_1->set_fader_value_by_int_from_range(

            masks_data.file_1_masks.nozzle_mask.d_n,
            nozzle_diameters[0],
            nozzle_diameters[nozzle_diameters.size() - 1] 
        
        );

    }


    
    m_1_x_1_update_ms_1();
    m_1_y_1_update_ms_1();

    m_1_x_2_update_ms_1();
    m_1_y_2_update_ms_1();

    m_1_dn_update_ms_1();

    // ===== MASK 1 =====
}


// ===== MASK 1 =====



// ===== MASK 2 =====

// Parameters update

void m_2_h_min_update_ms_1()
{
    int choosen_h_min = Mask_2_par_1_fader_ms_1->fader_value_to_int_from_range(

        0,
        179

    );

    // Overcome check
    if (choosen_h_min >= masks_data.file_1_masks.jet_mask.h_max)
    {
        // Correct value
        choosen_h_min = masks_data.file_1_masks.jet_mask.h_max - 1;

        // Correct fader position
        Mask_2_par_1_fader_ms_1->set_fader_value_by_int_from_range(

            choosen_h_min,
            0,
            179
        
        );
    }

    std::string mask_2_par_1_curr_value_to_show = 

        "HUE minimal: " + 
        std::to_string(choosen_h_min) + ".";


    Mask_2_par_1_textbox_ms_1->set_content(mask_2_par_1_curr_value_to_show);


    // Update value
    masks_data.file_1_masks.jet_mask.h_min = choosen_h_min;
}


void m_2_h_max_update_ms_1()
{
    int choosen_h_max = Mask_2_par_2_fader_ms_1->fader_value_to_int_from_range(

        0,
        179

    );


    // Overcome check
    if (choosen_h_max <= masks_data.file_1_masks.jet_mask.h_min)
    {
        // Correct value
        choosen_h_max = masks_data.file_1_masks.jet_mask.h_min + 1;

        // Correct fader position
        Mask_2_par_2_fader_ms_1->set_fader_value_by_int_from_range(

            choosen_h_max,
            0,
            179
        
        );
    }



    std::string mask_2_par_2_curr_value_to_show = 

        "HUE maximal: " + 
        std::to_string(choosen_h_max) + ".";


    Mask_2_par_2_textbox_ms_1->set_content(mask_2_par_2_curr_value_to_show);


    // Update value
    masks_data.file_1_masks.jet_mask.h_max = choosen_h_max;
}


void m_2_s_min_update_ms_1()
{
    int choosen_s_min = Mask_2_par_3_fader_ms_1->fader_value_to_int_from_range(

        0,
        255

    );


    // Overcome check
    if (choosen_s_min >= masks_data.file_1_masks.jet_mask.s_max)
    {
        // Correct value
        choosen_s_min = masks_data.file_1_masks.jet_mask.s_max - 1;

        // Correct fader position
        Mask_2_par_3_fader_ms_1->set_fader_value_by_int_from_range(

            choosen_s_min,
            0,
            255
        
        );
    }


    std::string mask_2_par_3_curr_value_to_show = 

        "SAT minimal: " + 
        std::to_string(choosen_s_min) + ".";


    Mask_2_par_3_textbox_ms_1->set_content(mask_2_par_3_curr_value_to_show);


    // Update value
    masks_data.file_1_masks.jet_mask.s_min = choosen_s_min;
}


void m_2_s_max_update_ms_1()
{
    int choosen_s_max = Mask_2_par_4_fader_ms_1->fader_value_to_int_from_range(

        0,
        255

    );


    // Overcome check
    if (choosen_s_max <= masks_data.file_1_masks.jet_mask.s_min)
    {
        // Correct value
        choosen_s_max = masks_data.file_1_masks.jet_mask.s_min + 1;

        // Correct fader position
        Mask_2_par_4_fader_ms_1->set_fader_value_by_int_from_range(

            choosen_s_max,
            0,
            255
        
        );
    }


    std::string mask_2_par_4_curr_value_to_show = 

        "SAT maximal: " + 
        std::to_string(choosen_s_max) + ".";


    Mask_2_par_4_textbox_ms_1->set_content(mask_2_par_4_curr_value_to_show);


    // Update value
    masks_data.file_1_masks.jet_mask.s_max = choosen_s_max;
}


void m_2_v_min_update_ms_1()
{
    int choosen_v_min = Mask_2_par_5_fader_ms_1->fader_value_to_int_from_range(

        0,
        255

    );


    // Overcome check
    if (choosen_v_min >= masks_data.file_1_masks.jet_mask.v_max)
    {
        // Correct value
        choosen_v_min = masks_data.file_1_masks.jet_mask.v_max - 1;

        // Correct fader position
        Mask_2_par_5_fader_ms_1->set_fader_value_by_int_from_range(

            choosen_v_min,
            0,
            255
        
        );
    }


    std::string mask_2_par_5_curr_value_to_show = 

        "VAL minimal: " + 
        std::to_string(choosen_v_min) + ".";


    Mask_2_par_5_textbox_ms_1->set_content(mask_2_par_5_curr_value_to_show);


    // Update value
    masks_data.file_1_masks.jet_mask.v_min = choosen_v_min;
}


void m_2_v_max_update_ms_1()
{
    int choosen_v_max = Mask_2_par_6_fader_ms_1->fader_value_to_int_from_range(

        0,
        255

    );

    // Overcome check
    if (choosen_v_max <= masks_data.file_1_masks.jet_mask.v_min)
    {
        // Correct value
        choosen_v_max = masks_data.file_1_masks.jet_mask.v_min + 1;

        // Correct fader position
        Mask_2_par_6_fader_ms_1->set_fader_value_by_int_from_range(

            choosen_v_max,
            0,
            255
        
        );
    }

    std::string mask_2_par_6_curr_value_to_show = 

        "VAL maximal: " + 
        std::to_string(choosen_v_max) + ".";


    Mask_2_par_6_textbox_ms_1->set_content(mask_2_par_6_curr_value_to_show);


    // Update value
    masks_data.file_1_masks.jet_mask.v_max = choosen_v_max;
}


void mask_2_faders_init_ms_1()
{

    // 1st call / 2nd call

    // ===== MASK 2 =====
    
    if (!masks_data.file_1_masks.jet_mask.initialized)
    {
        Mask_2_par_1_fader_ms_1->set_fader_value(0.0);
        Mask_2_par_2_fader_ms_1->set_fader_value(1.0);
        Mask_2_par_3_fader_ms_1->set_fader_value(0.0);
        Mask_2_par_4_fader_ms_1->set_fader_value(1.0);
        Mask_2_par_5_fader_ms_1->set_fader_value(0.0);
        Mask_2_par_6_fader_ms_1->set_fader_value(1.0);


        masks_data.file_1_masks.jet_mask.h_min = 0;
        masks_data.file_1_masks.jet_mask.h_max = 179;

        masks_data.file_1_masks.jet_mask.s_min = 0;
        masks_data.file_1_masks.jet_mask.s_max = 255;

        masks_data.file_1_masks.jet_mask.v_min = 0;
        masks_data.file_1_masks.jet_mask.v_max = 255;

        // Block next 50% reinit
        masks_data.file_1_masks.jet_mask.initialized = true;
    }
    else
    {
        // Set the fader know and value, according to the early choosen

        // h_min parameter value
        Mask_2_par_1_fader_ms_1->set_fader_value_by_int_from_range(

            masks_data.file_1_masks.jet_mask.h_min,
            0,
            179
        
        );

        // h_max parameter value
        Mask_2_par_2_fader_ms_1->set_fader_value_by_int_from_range(

            masks_data.file_1_masks.jet_mask.h_max,
            0,
            179
        
        );


        // s_min parameter value
        Mask_2_par_3_fader_ms_1->set_fader_value_by_int_from_range(

            masks_data.file_1_masks.jet_mask.s_min,
            0,
            255
        
        );

        // s_max parameter value
        Mask_2_par_4_fader_ms_1->set_fader_value_by_int_from_range(

            masks_data.file_1_masks.jet_mask.s_max,
            0,
            255
        
        );


        // v_min parameter value
        Mask_2_par_5_fader_ms_1->set_fader_value_by_int_from_range(

            masks_data.file_1_masks.jet_mask.v_min,
            0,
            255
        
        );

        // v_max parameter value
        Mask_2_par_6_fader_ms_1->set_fader_value_by_int_from_range(

            masks_data.file_1_masks.jet_mask.v_max,
            0,
            255
        
        );

    }


    
    m_2_h_min_update_ms_1();
    m_2_h_max_update_ms_1();

    m_2_s_min_update_ms_1();
    m_2_s_max_update_ms_1();

    m_2_v_min_update_ms_1();
    m_2_v_max_update_ms_1();


    // ===== MASK 2 =====
}

// ===== MASK 2 =====


// ===== MASK 3 =====

/*

    PARTICLE DETECTION MASK
    │
    ├── PART 1: PIXEL FILTERING
    │   ├── Brightness Min
    │   ├── Brightness Max
    │   ├── B Min
    │   ├── B Max
    │   ├── G Min
    │   ├── G Max
    │   ├── R Min
    │   └── R Max
    │
    └── PART 2: TRAJECTORY FILTERING
        ├── Canny Low
        ├── Canny High
        ├── Dilate Size
        ├── Dilate Iterations
        ├── Length Min
        ├── Length Max
        ├── Area Min
        └── Area Max

*/



// ===== MASK 3 =====


// =========================================================================================== HELPERS


// =========================================================================================== MAIN STATE API


void masks_setup_1_enter()
{
    // Log the enter in console
    std::cout << "Entering MASKS_SETUP\n"; 

    // ===== State allocation =====

    masks_setup_1_elements_create();

    // ===== State allocation =====


    // ===== Faders initiation / reinitiation =====

    // Need to be called before elements_setup

    mask_1_faders_init_ms_1();
    
    mask_2_faders_init_ms_1();

    // ===== Faders initiation / reinitiation =====


    // ===== Elements setup =====

    masks_setup_1_elements_setup();

    // ===== Elements setup =====  

    
    // ===== Faders initiation / reinitiation =====

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

    // ===== OPENCV =====

    // Max speed update not to loose synchronization
    // TODO: maybe block max speed by timer?
    if (App_timer_1.can_execute(Execute_zone_ID::HZ_30))
    {
        opencv_update_ms_1();
    }

    // ===== OPENCV =====



    // Update inputs
    if (App_timer_1.can_execute(Execute_zone_ID::HZ_1000))
    {
        App_inputs.update();
    }


    if (App_timer_1.can_execute(Execute_zone_ID::HZ_240))
    {

        masks_setup_1_elements_update();

        masks_setup_1_actions();

    }
}


void masks_setup_1_render(SDL_Renderer* renderer)
{
    if (App_timer_1.can_execute(Execute_zone_ID::HZ_120))
    {
        masks_setup_1_elements_render(renderer);
    }


    if (App_timer_1.can_execute(Execute_zone_ID::HZ_60))
    {
        opencv_render_by_translator_ms_1(renderer);

        highlight_video_texture_ms_1(renderer);
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

    Video_backwards_button_ms_1 = new My_SDL_button;
    Video_play_pause_button_ms_1 = new My_SDL_button;
    Video_forward_button_ms_1 = new My_SDL_button;
    Video_kingsize_button_ms_1 = new My_SDL_button;


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

    Mask_1_par_5_textbox_ms_1 = new My_SDL_textbox;
    Mask_1_par_5_fader_ms_1 = new My_SDL_fader;


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

    Mask_2_par_5_textbox_ms_1 = new My_SDL_textbox;
    Mask_2_par_5_fader_ms_1 = new My_SDL_fader;

    Mask_2_par_6_textbox_ms_1 = new My_SDL_textbox;
    Mask_2_par_6_fader_ms_1 = new My_SDL_fader;

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


// ===== !!! =====

// Only declarations are placed here.
// Initialization from files_metadata is intentionally NOT performed here,
// because global variables are initialized during program startup,
// before the TXT parser fills files_metadata with actual values.

unsigned int video_width_ms_1;
unsigned int video_height_ms_1;

int video_panel_width_ms_1;
int video_panel_height_ms_1;

int video_control_buttons_width;
int video_control_buttons_height;

// ===== !!! =====

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


int big_faders_textboxes_width = 0.5 * (mask_setup_panel_width - 3 * SCREEN_MARGIN_0);

int big_faders_textboxes_height = static_cast<int>(std::min(

    (mask_setup_panel_height - SCREEN_MARGIN_0 - (0.5 * MASK_1_FADERS_QUANTITY) * SCREEN_MARGIN_0) / (0.5 * MASK_1_FADERS_QUANTITY),
    75.0

));


int big_faders_width = 0.5 * (mask_setup_panel_width - 3 * SCREEN_MARGIN_0);
int big_faders_height = big_faders_textboxes_height;



// ===== Main sizes =====



// ===== Main points =====

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


    // ===== !!! =====

    // Initialize layout values after the metadata has been loaded.
    // These assignments cannot be performed as global initializers because
    // files_metadata contains valid data only after the previous state finishes parsing.

    // Otherwise there will be "Static Initialization Order Fiasco"

    video_width_ms_1 = files_metadata.video_1_data.width;
    video_height_ms_1 = files_metadata.video_1_data.height; 

    video_panel_width_ms_1 = mask_setup_panel_width;

    video_panel_height_ms_1 = BACKGROUND_HEIGHT - (4 * SCREEN_MARGIN_1 + 2 * choose_panels_height + control_buttons_height);

    video_control_buttons_width = static_cast<int>(video_panel_width_ms_1 / 4.0);
    video_control_buttons_height = 0.25 * video_panel_height_ms_1;

    // Video panel

    int video_panel_x_ms_1 = 0.25 * BACKGROUND_WIDTH;
    int video_panel_y_ms_1 = SCREEN_MARGIN_1 + 0.5 * video_panel_height_ms_1;

    // ===== !!! =====



    // ===== STATE GUI =====

    Masks_setup_panel_ms_1->set_render_point(MAIN_WINDOW_H_SIZE / 2, MAIN_WINDOW_V_SIZE / 2);
    Masks_setup_panel_ms_1->set_size(MAIN_WINDOW_H_SIZE, MAIN_WINDOW_V_SIZE);
    Masks_setup_panel_ms_1->set_border_radius(0);



    // Video preview 

    Video_preview_panel_ms_1->set_render_point(video_panel_x_ms_1, video_panel_y_ms_1);
    Video_preview_panel_ms_1->set_size(video_panel_width_ms_1, video_panel_height_ms_1);
    Video_preview_panel_ms_1->set_border_radius(0);
    Video_preview_panel_ms_1->set_shadow_scale_factor(0);


    Video_backwards_button_ms_1->switch_button_textbox_type(HEADER_3);
    Video_backwards_button_ms_1->get_button_content_textbox()->set_content("<-");
    Video_backwards_button_ms_1->set_size(video_control_buttons_width, video_control_buttons_height);
    Video_backwards_button_ms_1->on_click = video_rewind_backwards_ms_1;
    Video_backwards_button_ms_1->set_border_radius(0);
    Video_backwards_button_ms_1->set_shadow_scale_factor(0);
    Video_backwards_button_ms_1->switch_push_mode();

    Video_play_pause_button_ms_1->switch_button_textbox_type(HEADER_3);
    // Init with paused state
    Video_play_pause_button_ms_1->get_button_content_textbox()->set_content(">");
    Video_play_pause_button_ms_1->set_size(video_control_buttons_width, video_control_buttons_height);
    Video_play_pause_button_ms_1->on_click = video_play_or_pause_ms_1;
    Video_play_pause_button_ms_1->set_border_radius(0);
    Video_play_pause_button_ms_1->set_shadow_scale_factor(0);
    Video_play_pause_button_ms_1->switch_push_mode();

    Video_forward_button_ms_1->switch_button_textbox_type(HEADER_3);
    Video_forward_button_ms_1->get_button_content_textbox()->set_content("->");
    Video_forward_button_ms_1->set_size(video_control_buttons_width, video_control_buttons_height);
    Video_forward_button_ms_1->on_click = video_rewind_forward_ms_1;
    Video_forward_button_ms_1->set_border_radius(0);
    Video_forward_button_ms_1->set_shadow_scale_factor(0);
    Video_forward_button_ms_1->switch_push_mode();


    Video_kingsize_button_ms_1->switch_button_textbox_type(HEADER_3);
    Video_kingsize_button_ms_1->get_button_content_textbox()->set_content("[]");
    Video_kingsize_button_ms_1->set_size(video_control_buttons_width, video_control_buttons_height);
    Video_kingsize_button_ms_1->on_click = video_show_kingsize_ms_1;
    Video_kingsize_button_ms_1->set_border_radius(0);
    Video_kingsize_button_ms_1->set_shadow_scale_factor(0);
    Video_kingsize_button_ms_1->switch_push_mode();
    
    // Texture

    Video_preview_texture_ms_1->set_size(video_width_ms_1, video_height_ms_1);
    

    // Add texture in panel

    Video_preview_panel_ms_1->add_element(
        
        Video_preview_texture_ms_1,
        video_panel_width_ms_1 * 0.5,
        video_panel_height_ms_1 * (0.75 * 0.5),
        1
    
    );


    Video_preview_panel_ms_1->add_element(
        
        Video_backwards_button_ms_1,
        video_control_buttons_width * 0.5,
        video_panel_height_ms_1 * (0.75) + video_control_buttons_height * 0.5,
        1
    
    );

    Video_preview_panel_ms_1->add_element(
        
        Video_play_pause_button_ms_1,
        video_control_buttons_width * 1.5,
        video_panel_height_ms_1 * (0.75) + video_control_buttons_height * 0.5,
        1
    
    );

    Video_preview_panel_ms_1->add_element(
        
        Video_forward_button_ms_1,
        video_control_buttons_width * 2.5,
        video_panel_height_ms_1 * (0.75) + video_control_buttons_height * 0.5,
        1
    
    );


    Video_preview_panel_ms_1->add_element(
        
        Video_kingsize_button_ms_1,
        video_control_buttons_width * 3.5,
        video_panel_height_ms_1 * (0.75) + video_control_buttons_height * 0.5,
        1
    
    );
    

    // File choose panel

    File_choose_panel_ms_1->set_render_point(file_choose_panel_x_ms_1, file_choose_panel_y_ms_1);
    File_choose_panel_ms_1->set_size(choose_panels_width, choose_panels_height);
    File_choose_panel_ms_1->set_border_radius(0);
    File_choose_panel_ms_1->set_shadow_scale_factor(0);

    File_choose_textbox_ms_1->set_content(str_by_dictionary(gd_file_choose_panel_name));
    File_choose_textbox_ms_1->switch_textbox_type(ORDINARY_TEXT);


    // File 1 button

    File_1_button_ms_1->switch_button_textbox_type(ORDINARY_TEXT);
    File_1_button_ms_1->get_button_content_textbox()->set_content("1");
    File_1_button_ms_1->set_size(file_choose_buttons_width_ms_1, file_choose_buttons_height_ms_1);
    File_1_button_ms_1->on_click = file_1_choose_ms_1;
    File_1_button_ms_1->extern_click_permission = file_1_choose_ms_1_permission;
    File_1_button_ms_1->set_access_type(BUTTON_EXTERN_CLICK_PERMISSION);
    File_1_button_ms_1->set_border_radius(0);

    File_1_button_ms_1->set_access_denied_border_color(App_palette.get_current_palette().basic_border_color);
    File_1_button_ms_1->set_access_permitted_border_color(App_palette.get_current_palette().basic_border_color);

    File_1_button_ms_1->set_shadow_scale_factor(0);
    File_1_button_ms_1->switch_push_mode();


    // File 2 button

    File_2_button_ms_1->switch_button_textbox_type(ORDINARY_TEXT);
    File_2_button_ms_1->get_button_content_textbox()->set_content("2");
    File_2_button_ms_1->set_size(file_choose_buttons_width_ms_1, file_choose_buttons_height_ms_1);
    File_2_button_ms_1->on_click = file_2_choose_ms_1;
    File_2_button_ms_1->extern_click_permission = file_2_choose_ms_1_permission;
    File_2_button_ms_1->set_access_type(BUTTON_EXTERN_CLICK_PERMISSION);
    File_2_button_ms_1->set_border_radius(0);

    File_2_button_ms_1->set_access_denied_border_color(App_palette.get_current_palette().basic_border_color);
    File_2_button_ms_1->set_access_permitted_border_color(App_palette.get_current_palette().basic_border_color);

    File_2_button_ms_1->set_shadow_scale_factor(0);
    File_2_button_ms_1->switch_push_mode();

    // File 3 button

    File_3_button_ms_1->switch_button_textbox_type(ORDINARY_TEXT);
    File_3_button_ms_1->get_button_content_textbox()->set_content("3");
    File_3_button_ms_1->set_size(file_choose_buttons_width_ms_1, file_choose_buttons_height_ms_1);
    File_3_button_ms_1->on_click = file_3_choose_ms_1;
    File_3_button_ms_1->extern_click_permission = file_3_choose_ms_1_permission;
    File_3_button_ms_1->set_access_type(BUTTON_EXTERN_CLICK_PERMISSION);
    File_3_button_ms_1->set_border_radius(0);

    File_3_button_ms_1->set_access_denied_border_color(App_palette.get_current_palette().basic_border_color);
    File_3_button_ms_1->set_access_permitted_border_color(App_palette.get_current_palette().basic_border_color);

    File_3_button_ms_1->set_shadow_scale_factor(0);
    File_3_button_ms_1->switch_push_mode();

    // File 4 button

    File_4_button_ms_1->switch_button_textbox_type(ORDINARY_TEXT);
    File_4_button_ms_1->get_button_content_textbox()->set_content("4");
    File_4_button_ms_1->set_size(file_choose_buttons_width_ms_1, file_choose_buttons_height_ms_1);
    File_4_button_ms_1->on_click = file_4_choose_ms_1;
    File_4_button_ms_1->extern_click_permission = file_4_choose_ms_1_permission;
    File_4_button_ms_1->set_access_type(BUTTON_EXTERN_CLICK_PERMISSION);
    File_4_button_ms_1->set_border_radius(0);

    File_4_button_ms_1->set_access_denied_border_color(App_palette.get_current_palette().basic_border_color);
    File_4_button_ms_1->set_access_permitted_border_color(App_palette.get_current_palette().basic_border_color);

    File_4_button_ms_1->set_shadow_scale_factor(0);
    File_4_button_ms_1->switch_push_mode();

    // File 5 button

    File_5_button_ms_1->switch_button_textbox_type(ORDINARY_TEXT);
    File_5_button_ms_1->get_button_content_textbox()->set_content("5");
    File_5_button_ms_1->set_size(file_choose_buttons_width_ms_1, file_choose_buttons_height_ms_1);
    File_5_button_ms_1->on_click = file_5_choose_ms_1;
    File_5_button_ms_1->extern_click_permission = file_5_choose_ms_1_permission;
    File_5_button_ms_1->set_access_type(BUTTON_EXTERN_CLICK_PERMISSION);
    File_5_button_ms_1->set_border_radius(0);

    File_5_button_ms_1->set_access_denied_border_color(App_palette.get_current_palette().basic_border_color);
    File_5_button_ms_1->set_access_permitted_border_color(App_palette.get_current_palette().basic_border_color);

    File_5_button_ms_1->set_shadow_scale_factor(0);
    File_5_button_ms_1->switch_push_mode();

    // File 6 button

    File_6_button_ms_1->switch_button_textbox_type(ORDINARY_TEXT);
    File_6_button_ms_1->get_button_content_textbox()->set_content("6");
    File_6_button_ms_1->set_size(file_choose_buttons_width_ms_1, file_choose_buttons_height_ms_1);
    File_6_button_ms_1->on_click = file_6_choose_ms_1;
    File_6_button_ms_1->extern_click_permission = file_6_choose_ms_1_permission;
    File_6_button_ms_1->set_access_type(BUTTON_EXTERN_CLICK_PERMISSION);
    File_6_button_ms_1->set_border_radius(0);

    File_6_button_ms_1->set_access_denied_border_color(App_palette.get_current_palette().basic_border_color);
    File_6_button_ms_1->set_access_permitted_border_color(App_palette.get_current_palette().basic_border_color);

    File_6_button_ms_1->set_shadow_scale_factor(0);
    File_6_button_ms_1->switch_push_mode();

    
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

    Mask_choose_textbox_ms_1->set_content(str_by_dictionary(gd_mask_choose_panel_name));
    Mask_choose_textbox_ms_1->switch_textbox_type(ORDINARY_TEXT);


    // Mask 1 button

    Mask_1_choose_button_ms_1->switch_button_textbox_type(ORDINARY_TEXT);
    Mask_1_choose_button_ms_1->get_button_content_textbox()->set_content("1");
    Mask_1_choose_button_ms_1->set_size(mask_choose_buttons_width, mask_choose_buttons_height);
    Mask_1_choose_button_ms_1->on_click = mask_1_choose_ms_1;
    Mask_1_choose_button_ms_1->set_border_radius(0);
    Mask_1_choose_button_ms_1->set_shadow_scale_factor(0);
    Mask_1_choose_button_ms_1->switch_push_mode();

    // Mask 2 button

    Mask_2_choose_button_ms_1->switch_button_textbox_type(ORDINARY_TEXT);
    Mask_2_choose_button_ms_1->get_button_content_textbox()->set_content("2");
    Mask_2_choose_button_ms_1->set_size(mask_choose_buttons_width, mask_choose_buttons_height);
    Mask_2_choose_button_ms_1->on_click = mask_2_choose_ms_1;
    Mask_2_choose_button_ms_1->set_border_radius(0);
    Mask_2_choose_button_ms_1->set_shadow_scale_factor(0);
    Mask_2_choose_button_ms_1->switch_push_mode();


    // Mask 3 button

    Mask_3_choose_button_ms_1->switch_button_textbox_type(ORDINARY_TEXT);
    Mask_3_choose_button_ms_1->get_button_content_textbox()->set_content("3");
    Mask_3_choose_button_ms_1->set_size(mask_choose_buttons_width, mask_choose_buttons_height);
    Mask_3_choose_button_ms_1->on_click = mask_3_choose_ms_1;
    Mask_3_choose_button_ms_1->set_border_radius(0);
    Mask_3_choose_button_ms_1->set_shadow_scale_factor(0);
    Mask_3_choose_button_ms_1->switch_push_mode();


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
    Save_preset_button_ms_1->on_click = save_preset_ms_1;
    Save_preset_button_ms_1->set_border_radius(0);


    // Load preset button

    
    Load_preset_button_ms_1->set_render_point(load_preset_button_x, load_preset_button_y);
    Load_preset_button_ms_1->switch_button_textbox_type(HEADER_3);
    Load_preset_button_ms_1->get_button_content_textbox()->set_content(str_by_dictionary(gd_load_preset));
    Load_preset_button_ms_1->set_size(control_buttons_width, control_buttons_height);
    Load_preset_button_ms_1->on_click = load_preset_ms_1;
    Load_preset_button_ms_1->set_border_radius(0);


    // State change buttons

    file_choose_state_but_ms_1->set_render_point(prev_state_button_x, prev_state_button_y);
    file_choose_state_but_ms_1->switch_button_textbox_type(HEADER_3);
    file_choose_state_but_ms_1->get_button_content_textbox()->set_content(str_by_dictionary(gd_masks_setup_exit));
    file_choose_state_but_ms_1->set_size(control_buttons_width, control_buttons_height);
    file_choose_state_but_ms_1->on_click = previous_state_ms_1;
    file_choose_state_but_ms_1->set_border_radius(0);


    flow_parameters_calculation_state_but_ms_1->set_render_point(next_state_button_x, next_state_button_y);
    flow_parameters_calculation_state_but_ms_1->switch_button_textbox_type(HEADER_3);
    flow_parameters_calculation_state_but_ms_1->get_button_content_textbox()->set_content(str_by_dictionary(gd_calculation_start));
    flow_parameters_calculation_state_but_ms_1->set_size(control_buttons_width, control_buttons_height);
    flow_parameters_calculation_state_but_ms_1->on_click = next_state_ms_1;
    flow_parameters_calculation_state_but_ms_1->extern_click_permission = next_state_permission_ms_1;
    flow_parameters_calculation_state_but_ms_1->set_access_type(BUTTON_EXTERN_CLICK_PERMISSION);
    flow_parameters_calculation_state_but_ms_1->set_border_radius(0);



    // ====== Panel 1 elements =====

    // Mask 1 choose state - active at init

    Mask_1_setup_panel_ms_1->set_render_point(mask_setup_panel_x, mask_setup_panel_y);
    Mask_1_setup_panel_ms_1->set_size(mask_setup_panel_width, mask_setup_panel_height);
    Mask_1_setup_panel_ms_1->set_border_radius(0);
    Mask_1_setup_panel_ms_1->set_shadow_scale_factor(0);


    // Panel 1 elements

    Mask_1_par_1_textbox_ms_1->set_content("X1:");
    Mask_1_par_1_textbox_ms_1->switch_textbox_type(ORDINARY_TEXT);

    Mask_1_par_1_fader_ms_1->set_knob_border_radius(5);
    Mask_1_par_1_fader_ms_1->set_knob_size(big_faders_width * 0.1, big_faders_height);
    Mask_1_par_1_fader_ms_1->set_slot_border_width_size(5);
    Mask_1_par_1_fader_ms_1->set_slot_size(big_faders_width, big_faders_height * 0.25);


    Mask_1_par_2_textbox_ms_1->set_content("Y1:");
    Mask_1_par_2_textbox_ms_1->switch_textbox_type(ORDINARY_TEXT);

    Mask_1_par_2_fader_ms_1->set_knob_border_radius(5);
    Mask_1_par_2_fader_ms_1->set_knob_size(big_faders_width * 0.1, big_faders_height);
    Mask_1_par_2_fader_ms_1->set_slot_border_width_size(5);
    Mask_1_par_2_fader_ms_1->set_slot_size(big_faders_width, big_faders_height * 0.25);


    Mask_1_par_3_textbox_ms_1->set_content("X2:");
    Mask_1_par_3_textbox_ms_1->switch_textbox_type(ORDINARY_TEXT);

    Mask_1_par_3_fader_ms_1->set_knob_border_radius(5);
    Mask_1_par_3_fader_ms_1->set_knob_size(big_faders_width * 0.1, big_faders_height);
    Mask_1_par_3_fader_ms_1->set_slot_border_width_size(5);
    Mask_1_par_3_fader_ms_1->set_slot_size(big_faders_width, big_faders_height * 0.25);


    Mask_1_par_4_textbox_ms_1->set_content("Y2:");
    Mask_1_par_4_textbox_ms_1->switch_textbox_type(ORDINARY_TEXT);

    Mask_1_par_4_fader_ms_1->set_knob_border_radius(5);
    Mask_1_par_4_fader_ms_1->set_knob_size(big_faders_width * 0.1, big_faders_height);
    Mask_1_par_4_fader_ms_1->set_slot_border_width_size(5);
    Mask_1_par_4_fader_ms_1->set_slot_size(big_faders_width, big_faders_height * 0.25);

    
    Mask_1_par_5_textbox_ms_1->set_content("d_n:");
    Mask_1_par_5_textbox_ms_1->switch_textbox_type(ORDINARY_TEXT);

    Mask_1_par_5_fader_ms_1->set_knob_border_radius(5);
    Mask_1_par_5_fader_ms_1->set_knob_size(big_faders_width * 0.1, big_faders_height);
    Mask_1_par_5_fader_ms_1->set_slot_border_width_size(5);
    Mask_1_par_5_fader_ms_1->set_slot_size(big_faders_width, big_faders_height * 0.25);

    // Update textboxes

    m_1_x_1_update_ms_1();
    m_1_y_1_update_ms_1();

    m_1_x_2_update_ms_1();
    m_1_y_2_update_ms_1();

    m_1_dn_update_ms_1();


    Mask_1_setup_panel_ms_1->add_element(

        Mask_1_par_1_fader_ms_1,
        1 * SCREEN_MARGIN_0 + 0.5 * big_faders_width,
        1 * SCREEN_MARGIN_0 + 0.5 * big_faders_textboxes_height,
        1

    );


    Mask_1_setup_panel_ms_1->add_element(

        Mask_1_par_1_textbox_ms_1,
        2 * SCREEN_MARGIN_0 + 1 * big_faders_width + 0.5 * big_faders_textboxes_width,
        1 * SCREEN_MARGIN_0 + 0.5 * big_faders_textboxes_height,
        1

    );


    Mask_1_setup_panel_ms_1->add_element(

        Mask_1_par_2_fader_ms_1,
        1 * SCREEN_MARGIN_0 + 0.5 * big_faders_width,
        2 * SCREEN_MARGIN_0 + 1.5 * big_faders_textboxes_height,
        1

    );


    Mask_1_setup_panel_ms_1->add_element(

        Mask_1_par_2_textbox_ms_1,
        2 * SCREEN_MARGIN_0 + 1 * big_faders_width + 0.5 * big_faders_textboxes_width,
        2 * SCREEN_MARGIN_0 + 1.5 * big_faders_textboxes_height,
        1

    );


    Mask_1_setup_panel_ms_1->add_element(

        Mask_1_par_3_fader_ms_1,
        1 * SCREEN_MARGIN_0 + 0.5 * big_faders_width,
        3 * SCREEN_MARGIN_0 + 2.5 * big_faders_textboxes_height,
        1

    );


    Mask_1_setup_panel_ms_1->add_element(

        Mask_1_par_3_textbox_ms_1,
        2 * SCREEN_MARGIN_0 + 1 * big_faders_width + 0.5 * big_faders_textboxes_width,
        3 * SCREEN_MARGIN_0 + 2.5 * big_faders_textboxes_height,
        1

    );


    Mask_1_setup_panel_ms_1->add_element(

        Mask_1_par_4_fader_ms_1,
        1 * SCREEN_MARGIN_0 + 0.5 * big_faders_width,
        4 * SCREEN_MARGIN_0 + 3.5 * big_faders_textboxes_height,
        1

    );


    Mask_1_setup_panel_ms_1->add_element(

        Mask_1_par_4_textbox_ms_1,
        2 * SCREEN_MARGIN_0 + 1 * big_faders_width + 0.5 * big_faders_textboxes_width,
        4 * SCREEN_MARGIN_0 + 3.5 * big_faders_textboxes_height,
        1

    );

    
    Mask_1_setup_panel_ms_1->add_element(

        Mask_1_par_5_fader_ms_1,
        1 * SCREEN_MARGIN_0 + 0.5 * big_faders_width,
        5 * SCREEN_MARGIN_0 + 4.5 * big_faders_textboxes_height,
        1

    );


    Mask_1_setup_panel_ms_1->add_element(

        Mask_1_par_5_textbox_ms_1,
        2 * SCREEN_MARGIN_0 + 1 * big_faders_width + 0.5 * big_faders_textboxes_width,
        5 * SCREEN_MARGIN_0 + 4.5 * big_faders_textboxes_height,
        1

    );



    // ===== Mask 2 choose state - inactive at init =====

    // Out of screen
    Mask_2_setup_panel_ms_1->set_render_point(2 * mask_setup_panel_x, mask_setup_panel_y);
    Mask_2_setup_panel_ms_1->set_size(mask_setup_panel_width, mask_setup_panel_height);
    Mask_2_setup_panel_ms_1->set_border_radius(0);
    Mask_2_setup_panel_ms_1->set_shadow_scale_factor(0);


    // Panel 2 elements

    Mask_2_par_1_textbox_ms_1->set_content("h_min:");
    Mask_2_par_1_textbox_ms_1->switch_textbox_type(ORDINARY_TEXT);

    Mask_2_par_1_fader_ms_1->set_knob_border_radius(5);
    Mask_2_par_1_fader_ms_1->set_knob_size(big_faders_width * 0.1, big_faders_height);
    Mask_2_par_1_fader_ms_1->set_slot_border_width_size(5);
    Mask_2_par_1_fader_ms_1->set_slot_size(big_faders_width, big_faders_height * 0.25);


    Mask_2_par_2_textbox_ms_1->set_content("h_max:");
    Mask_2_par_2_textbox_ms_1->switch_textbox_type(ORDINARY_TEXT);

    Mask_2_par_2_fader_ms_1->set_knob_border_radius(5);
    Mask_2_par_2_fader_ms_1->set_knob_size(big_faders_width * 0.1, big_faders_height);
    Mask_2_par_2_fader_ms_1->set_slot_border_width_size(5);
    Mask_2_par_2_fader_ms_1->set_slot_size(big_faders_width, big_faders_height * 0.25);


    Mask_2_par_3_textbox_ms_1->set_content("s_min:");
    Mask_2_par_3_textbox_ms_1->switch_textbox_type(ORDINARY_TEXT);

    Mask_2_par_3_fader_ms_1->set_knob_border_radius(5);
    Mask_2_par_3_fader_ms_1->set_knob_size(big_faders_width * 0.1, big_faders_height);
    Mask_2_par_3_fader_ms_1->set_slot_border_width_size(5);
    Mask_2_par_3_fader_ms_1->set_slot_size(big_faders_width, big_faders_height * 0.25);


    Mask_2_par_4_textbox_ms_1->set_content("s_max:");
    Mask_2_par_4_textbox_ms_1->switch_textbox_type(ORDINARY_TEXT);

    Mask_2_par_4_fader_ms_1->set_knob_border_radius(5);
    Mask_2_par_4_fader_ms_1->set_knob_size(big_faders_width * 0.1, big_faders_height);
    Mask_2_par_4_fader_ms_1->set_slot_border_width_size(5);
    Mask_2_par_4_fader_ms_1->set_slot_size(big_faders_width, big_faders_height * 0.25);

    
    Mask_2_par_5_textbox_ms_1->set_content("v_min:");
    Mask_2_par_5_textbox_ms_1->switch_textbox_type(ORDINARY_TEXT);

    Mask_2_par_5_fader_ms_1->set_knob_border_radius(5);
    Mask_2_par_5_fader_ms_1->set_knob_size(big_faders_width * 0.1, big_faders_height);
    Mask_2_par_5_fader_ms_1->set_slot_border_width_size(5);
    Mask_2_par_5_fader_ms_1->set_slot_size(big_faders_width, big_faders_height * 0.25);


    Mask_2_par_6_textbox_ms_1->set_content("v_max:");
    Mask_2_par_6_textbox_ms_1->switch_textbox_type(ORDINARY_TEXT);

    Mask_2_par_6_fader_ms_1->set_knob_border_radius(5);
    Mask_2_par_6_fader_ms_1->set_knob_size(big_faders_width * 0.1, big_faders_height);
    Mask_2_par_6_fader_ms_1->set_slot_border_width_size(5);
    Mask_2_par_6_fader_ms_1->set_slot_size(big_faders_width, big_faders_height * 0.25);


    // Update textboxes

    m_2_h_min_update_ms_1();
    m_2_h_max_update_ms_1();

    m_2_s_min_update_ms_1();
    m_2_s_max_update_ms_1();

    m_2_v_min_update_ms_1();
    m_2_v_max_update_ms_1();


    Mask_2_setup_panel_ms_1->add_element(

        Mask_2_par_1_fader_ms_1,
        1 * SCREEN_MARGIN_0 + 0.5 * big_faders_width,
        1 * SCREEN_MARGIN_0 + 0.5 * big_faders_textboxes_height,
        1

    );


    Mask_2_setup_panel_ms_1->add_element(

        Mask_2_par_1_textbox_ms_1,
        2 * SCREEN_MARGIN_0 + 1 * big_faders_width + 0.5 * big_faders_textboxes_width,
        1 * SCREEN_MARGIN_0 + 0.5 * big_faders_textboxes_height,
        1

    );


    Mask_2_setup_panel_ms_1->add_element(

        Mask_2_par_2_fader_ms_1,
        1 * SCREEN_MARGIN_0 + 0.5 * big_faders_width,
        2 * SCREEN_MARGIN_0 + 1.5 * big_faders_textboxes_height,
        1

    );


    Mask_2_setup_panel_ms_1->add_element(

        Mask_2_par_2_textbox_ms_1,
        2 * SCREEN_MARGIN_0 + 1 * big_faders_width + 0.5 * big_faders_textboxes_width,
        2 * SCREEN_MARGIN_0 + 1.5 * big_faders_textboxes_height,
        1

    );


    Mask_2_setup_panel_ms_1->add_element(

        Mask_2_par_3_fader_ms_1,
        1 * SCREEN_MARGIN_0 + 0.5 * big_faders_width,
        3 * SCREEN_MARGIN_0 + 2.5 * big_faders_textboxes_height,
        1

    );


    Mask_2_setup_panel_ms_1->add_element(

        Mask_2_par_3_textbox_ms_1,
        2 * SCREEN_MARGIN_0 + 1 * big_faders_width + 0.5 * big_faders_textboxes_width,
        3 * SCREEN_MARGIN_0 + 2.5 * big_faders_textboxes_height,
        1

    );


    Mask_2_setup_panel_ms_1->add_element(

        Mask_2_par_4_fader_ms_1,
        1 * SCREEN_MARGIN_0 + 0.5 * big_faders_width,
        4 * SCREEN_MARGIN_0 + 3.5 * big_faders_textboxes_height,
        1

    );


    Mask_2_setup_panel_ms_1->add_element(

        Mask_2_par_4_textbox_ms_1,
        2 * SCREEN_MARGIN_0 + 1 * big_faders_width + 0.5 * big_faders_textboxes_width,
        4 * SCREEN_MARGIN_0 + 3.5 * big_faders_textboxes_height,
        1

    );

    
    Mask_2_setup_panel_ms_1->add_element(

        Mask_2_par_5_fader_ms_1,
        1 * SCREEN_MARGIN_0 + 0.5 * big_faders_width,
        5 * SCREEN_MARGIN_0 + 4.5 * big_faders_textboxes_height,
        1

    );


    Mask_2_setup_panel_ms_1->add_element(

        Mask_2_par_5_textbox_ms_1,
        2 * SCREEN_MARGIN_0 + 1 * big_faders_width + 0.5 * big_faders_textboxes_width,
        5 * SCREEN_MARGIN_0 + 4.5 * big_faders_textboxes_height,
        1

    );


    Mask_2_setup_panel_ms_1->add_element(

        Mask_2_par_6_fader_ms_1,
        1 * SCREEN_MARGIN_0 + 0.5 * big_faders_width,
        6 * SCREEN_MARGIN_0 + 5.5 * big_faders_textboxes_height,
        1

    );


    Mask_2_setup_panel_ms_1->add_element(

        Mask_2_par_6_textbox_ms_1,
        2 * SCREEN_MARGIN_0 + 1 * big_faders_width + 0.5 * big_faders_textboxes_width,
        6 * SCREEN_MARGIN_0 + 5.5 * big_faders_textboxes_height,
        1

    );







    // Mask 3 choose state - inactive at init

    // Out of screen
    Mask_3_setup_panel_ms_1->set_render_point(2 * mask_setup_panel_x, mask_setup_panel_y);
    Mask_3_setup_panel_ms_1->set_size(mask_setup_panel_width, mask_setup_panel_height);
    Mask_3_setup_panel_ms_1->set_border_radius(0);
    Mask_3_setup_panel_ms_1->set_shadow_scale_factor(0);


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

    // ===== STATE GUI =====


    // ===== OPENCV =====

    opencv_setup_ms_1();

    // ===== OPENCV =====

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

    Video_backwards_button_ms_1 = nullptr;
    Video_play_pause_button_ms_1 = nullptr;
    Video_forward_button_ms_1 = nullptr;
    Video_kingsize_button_ms_1 = nullptr;

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

    Mask_1_par_5_textbox_ms_1 = nullptr;
    Mask_1_par_5_fader_ms_1 = nullptr;

    
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


    // Update textbox only if value of fader been changed

    if (Mask_1_par_1_fader_ms_1->fader_value_changed_at_last_step())
        m_1_x_1_update_ms_1();

    if (Mask_1_par_2_fader_ms_1->fader_value_changed_at_last_step())
        m_1_y_1_update_ms_1();

    if (Mask_1_par_3_fader_ms_1->fader_value_changed_at_last_step())
        m_1_x_2_update_ms_1();

    if (Mask_1_par_4_fader_ms_1->fader_value_changed_at_last_step())
        m_1_y_2_update_ms_1();

    if (Mask_1_par_5_fader_ms_1->fader_value_changed_at_last_step())
        m_1_dn_update_ms_1();


    Mask_1_setup_panel_ms_1->update();


    if (Mask_2_par_1_fader_ms_1->fader_value_changed_at_last_step())
        m_2_h_min_update_ms_1();

    if (Mask_2_par_2_fader_ms_1->fader_value_changed_at_last_step())
        m_2_h_max_update_ms_1();

    if (Mask_2_par_3_fader_ms_1->fader_value_changed_at_last_step())
        m_2_s_min_update_ms_1();

    if (Mask_2_par_4_fader_ms_1->fader_value_changed_at_last_step())
        m_2_s_max_update_ms_1();

    if (Mask_2_par_5_fader_ms_1->fader_value_changed_at_last_step())
        m_2_v_min_update_ms_1();

    if (Mask_2_par_6_fader_ms_1->fader_value_changed_at_last_step())
        m_2_v_max_update_ms_1();


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
    
        File_choose_textbox_ms_1->set_content(str_by_dictionary(gd_file_choose_panel_name));

        Mask_choose_textbox_ms_1->set_content(str_by_dictionary(gd_mask_choose_panel_name));

        m_1_x_1_update_ms_1();
        m_1_y_1_update_ms_1();
    
        m_1_x_2_update_ms_1();
        m_1_y_2_update_ms_1();

        m_1_dn_update_ms_1();

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

    // Renders at opencv part
    // Video_preview_panel_ms_1->render(renderer);


    File_choose_panel_ms_1->render(renderer);
    Masks_choose_panel_ms_1->render(renderer);


    Save_preset_button_ms_1->render(renderer);
    Load_preset_button_ms_1->render(renderer);


    Mask_1_setup_panel_ms_1->render(renderer);

    Mask_2_setup_panel_ms_1->render(renderer);

    Mask_3_setup_panel_ms_1->render(renderer);


    file_choose_state_but_ms_1->render(renderer);
    flow_parameters_calculation_state_but_ms_1->render(renderer);

    
    // Highlight choosen mask and file

    highlight_choosen_mask_ms_1(renderer);

    highlight_choosen_file_ms_1(renderer);
}

// =========================================================================================== STATE INNER FUNCTIONS REALIZATION



// =========================================================================================== CALLBACKS


void video_rewind_backwards_ms_1()
{
    // 10 frames with 0 frame stop if video plays
    // 1 frame with 0 frame stop if video paused

    if (opencv_global_update_ctx.playback_state == VIDEO_PLAYING_VPS)
    {
        opencv_global_update_ctx.current_frame_index -= 10;

        if (opencv_global_update_ctx.current_frame_index < 0)
            opencv_global_update_ctx.current_frame_index = 0;
    }

    if (opencv_global_update_ctx.playback_state == VIDEO_PAUSED_VPS)
    {
        opencv_global_update_ctx.current_frame_index -= 1;

        if (opencv_global_update_ctx.current_frame_index < 0)
            opencv_global_update_ctx.current_frame_index = 0;
    }
}


void video_play_or_pause_ms_1()
{
    switch (opencv_global_update_ctx.playback_state)
    {
        case VIDEO_PLAYING_VPS:
        {
            opencv_global_update_ctx.playback_state = VIDEO_PAUSED_VPS;
            Video_play_pause_button_ms_1->get_button_content_textbox()->set_content(">");


            break;
        }
        
        case VIDEO_PAUSED_VPS:
        {
            opencv_global_update_ctx.playback_state = VIDEO_PLAYING_VPS;
            Video_play_pause_button_ms_1->get_button_content_textbox()->set_content("||");

            break;
        }

        default:
        {
            opencv_global_update_ctx.playback_state = VIDEO_PLAYING_VPS;
            break;
        }
    }
}


void video_rewind_forward_ms_1()
{
    // 10 frames with MAX frame stop if video plays
    // 1 frame with MAX frame stop if video paused

    if (opencv_global_update_ctx.playback_state == VIDEO_PLAYING_VPS)
    {
        opencv_global_update_ctx.current_frame_index += 10;

        if (opencv_global_update_ctx.current_frame_index >=
            opencv_global_update_ctx.total_frame_count)
        {
            opencv_global_update_ctx.current_frame_index =
                opencv_global_update_ctx.total_frame_count - 1;
        }
    }

    if (opencv_global_update_ctx.playback_state == VIDEO_PAUSED_VPS)
    {
        opencv_global_update_ctx.current_frame_index += 1;

        if (opencv_global_update_ctx.current_frame_index >=
            opencv_global_update_ctx.total_frame_count)
        {
            opencv_global_update_ctx.current_frame_index =
                opencv_global_update_ctx.total_frame_count - 1;
        }
    }
}


void video_show_kingsize_ms_1()
{
    opencv_global_update_ctx.show_kingsize = !opencv_global_update_ctx.show_kingsize;
}



void file_1_choose_ms_1()
{
    // 
}


void file_2_choose_ms_1()
{
    // 
}


void file_3_choose_ms_1()
{
    // 
}


void file_4_choose_ms_1()
{
    // 
}


void file_5_choose_ms_1()
{
    // 
}


void file_6_choose_ms_1()
{
    // 
}



void mask_1_choose_ms_1()
{
    choose_mask_1_ms_1();
}


void mask_2_choose_ms_1()
{
    choose_mask_2_ms_1();
}


void mask_3_choose_ms_1()
{
    choose_mask_3_ms_1();
}




void save_preset_ms_1()
{
    // TEST
    std::cout << "CALL SAVE CALLBACK" << "\n\n";

    save_mask_preset(1);
}


void load_preset_ms_1()
{
    // TEST
    std::cout << "CALL LOAD CALLBACK" << "\n\n";

    load_mask_preset(1);
 
    // Reinit faders
    mask_1_faders_init_ms_1();
    mask_2_faders_init_ms_1();
}



void previous_state_ms_1()
{
    // 
}


void next_state_ms_1()
{
    // 
}

// =========================================================================================== CALLBACKS


// =========================================================================================== OPENCV PIPELINE SETUP FUNCTIONS

void choose_mask_1_ms_1()
{
    // Set highlight

    highlight_ms_1.x_m = Mask_1_choose_button_ms_1->get_x_render_point();
    
    highlight_ms_1.y_m = Mask_1_choose_button_ms_1->get_y_render_point();

    highlight_ms_1.w_m = Mask_1_choose_button_ms_1->get_width_size();
    
    highlight_ms_1.h_m = Mask_1_choose_button_ms_1->get_height_size();


    // Set callback and switch status

    opencv_global_update_ctx.current_mask_for_mask_setup = MASK_1_CM;
    opencv_global_update_ctx.current_frame_processor = mask_1_processing_ms_1;


    // ===== Move panels =====

    Mask_1_setup_panel_ms_1->move_to_point(

        mask_setup_panel_x,
        mask_setup_panel_y,
        EXPONENTIAL,
        300

    );

    Mask_2_setup_panel_ms_1->move_to_point(

        2 * mask_setup_panel_x,
        mask_setup_panel_y,
        EXPONENTIAL,
        300

    );

    Mask_3_setup_panel_ms_1->move_to_point(

        2 * mask_setup_panel_x,
        mask_setup_panel_y,
        EXPONENTIAL,
        300

    );
}


void choose_mask_2_ms_1()
{
    highlight_ms_1.x_m = Mask_2_choose_button_ms_1->get_x_render_point();
    
    highlight_ms_1.y_m = Mask_2_choose_button_ms_1->get_y_render_point();

    highlight_ms_1.w_m = Mask_2_choose_button_ms_1->get_width_size();
    
    highlight_ms_1.h_m = Mask_2_choose_button_ms_1->get_height_size();


    // Set callback and switch status

    opencv_global_update_ctx.current_mask_for_mask_setup = MASK_2_CM;
    opencv_global_update_ctx.current_frame_processor = mask_2_processing_ms_1;


    // ===== Move panels =====

    Mask_1_setup_panel_ms_1->move_to_point(

        2 * mask_setup_panel_x,
        mask_setup_panel_y,
        EXPONENTIAL,
        300

    );

    Mask_2_setup_panel_ms_1->move_to_point(

        mask_setup_panel_x,
        mask_setup_panel_y,
        EXPONENTIAL,
        300

    );

    Mask_3_setup_panel_ms_1->move_to_point(

        2 * mask_setup_panel_x,
        mask_setup_panel_y,
        EXPONENTIAL,
        300

    );
}


void choose_mask_3_ms_1()
{
    highlight_ms_1.x_m = Mask_3_choose_button_ms_1->get_x_render_point();
    
    highlight_ms_1.y_m = Mask_3_choose_button_ms_1->get_y_render_point();

    highlight_ms_1.w_m = Mask_3_choose_button_ms_1->get_width_size();
    
    highlight_ms_1.h_m = Mask_3_choose_button_ms_1->get_height_size();


    // Set callback and switch status

    opencv_global_update_ctx.current_mask_for_mask_setup = MASK_3_CM;
    opencv_global_update_ctx.current_frame_processor = mask_3_processing_ms_1;


    // ===== Move panels =====

    Mask_1_setup_panel_ms_1->move_to_point(

        2 * mask_setup_panel_x,
        mask_setup_panel_y,
        EXPONENTIAL,
        300

    );

    Mask_2_setup_panel_ms_1->move_to_point(

        2 * mask_setup_panel_x,
        mask_setup_panel_y,
        EXPONENTIAL,
        300

    );

    Mask_3_setup_panel_ms_1->move_to_point(

        mask_setup_panel_x,
        mask_setup_panel_y,
        EXPONENTIAL,
        300

    );
}


void choose_current_file_ms_1()
{
    highlight_ms_1.x_f = File_1_button_ms_1->get_x_render_point();
    
    highlight_ms_1.y_f = File_1_button_ms_1->get_y_render_point();

    highlight_ms_1.w_f = File_1_button_ms_1->get_width_size();
    
    highlight_ms_1.h_f = File_1_button_ms_1->get_height_size();


    opencv_global_update_ctx.current_file_for_mask_setup = FILE_1_CF;
}



// Processing callbacks for every mask
void mask_1_processing_ms_1(cv::Mat* frame)
{
    if (!frame || frame->empty()) return;

    // Mask processing logic


    // ===== MASK SETUP LOGIC =====

    nozzle_detection_mask* controlled_mask = &masks_data.file_1_masks.nozzle_mask;

    // Need or not to show axe line and precalculate scale
    // Always show if 2 points are not the same
    bool show_axe_and_calculate_scale = !(

        (controlled_mask->x_1 == controlled_mask->x_2) && 
        (controlled_mask->y_1 == controlled_mask->y_2)

    );

    // No more job here in basic case
    if (!show_axe_and_calculate_scale) 
    {
        // reinit

        controlled_mask->mm_in_pixel = 0.0f;

        controlled_mask->basic_axe_angle = 0.0f;

        controlled_mask->axe_line_coefficients.a = 0.0f;
        controlled_mask->axe_line_coefficients.b = 0.0f;
        controlled_mask->axe_line_coefficients.c = 0.0f;

        controlled_mask->axe_line_coefficients.calculated = false;


        return;
    }

    // else

    // This mask is only mask with precalculation (no calculation on the next step)

    /*

        0) Put a green and red crosshair at 2 points ((controlled_mask->x_1, controlled_mask->y_1) 
        and (controlled_mask->x_2, controlled_mask->y_2))

        Crosshair: lines: 5px length, 2px width 2 on 2 pixels Center Dot (Center Gap)

        1) Determine the coefficients of the line equation for the line connecting two selected points.

        2) Find the midpoint between them, then calculate the coefficients of the equation for the line that is
        perpendicular to the first line and passes through that midpoint.

        3) Identify two points at the edges of the visibility zone that lie on this second line.

        4) Draw a dashed blue line with a thickness of 3 pixels connecting these two points.

        5) Calculate the scale (controlled_mask->mm_in_pixels by distance between 2 choosen points and 
        controlled_mask->d_n)

        6) Save calculated data

    */

    // === 1st step === 

    auto draw_crosshair = [](cv::Mat& img, int cx, int cy, const cv::Scalar& color) 
    {
        int length = 5;
        int thickness = 2;
        int gap = 2;
        cv::Size img_size = img.size();

        // Лямбда для безопасного рисования линии с предварительным клиппингом
        auto safe_line = [&](cv::Point p_1, cv::Point p_2) 
        {
            // clipLine возвращает true, если линия хотя бы частично внутри кадра
            if (cv::clipLine(img_size, p_1, p_2)) {
                cv::line(img, p_1, p_2, color, thickness);
            }
        };

        // Левая линия
        safe_line(cv::Point(cx - gap - length, cy), cv::Point(cx - gap, cy));
        // Правая линия
        safe_line(cv::Point(cx + gap, cy), cv::Point(cx + gap + length, cy));
        // Верхняя линия
        safe_line(cv::Point(cx, cy - gap - length), cv::Point(cx, cy - gap));
        // Нижняя линия
        safe_line(cv::Point(cx, cy + gap), cv::Point(cx, cy + gap + length));
    };


    draw_crosshair(*frame, controlled_mask->x_1, controlled_mask->y_1, cv::Scalar(0, 255, 0)); // Зеленый
    draw_crosshair(*frame, controlled_mask->x_2, controlled_mask->y_2, cv::Scalar(0, 0, 255)); // Красный
    
    
    // === 2nd step === 

    // =========================================================================
    // 1) Коэффициенты исходной прямой: a_1*x + b_1*y + c_1 = 0
    // =========================================================================

    double x_1 = controlled_mask->x_1;
    double y_1 = controlled_mask->y_1;
    double x_2 = controlled_mask->x_2;
    double y_2 = controlled_mask->y_2;

    // Формула прямой через две точки: (y_1 - y_2)*x + (x_2 - x_1)*y + (x_1*y_2 - x_2*y_1) = 0
    double a_1 = y_1 - y_2;
    double b_1 = x_2 - x_1;
    double c_1 = x_1 * y_2 - x_2 * y_1;


    // =========================================================================
    // 2) Поиск средней точки и коэффициентов перпендикуляра: a_2*x + b_2*y + c_2 = 0
    // =========================================================================
    
    // Координаты центра между двумя точками
    double mid_x = (x_1 + x_2) / 2.0;
    double mid_y = (y_1 + y_2) / 2.0;

    // Для перпендикуляра инвертируем и меняем местами коэффициенты
    double a_2 = -b_1; 
    double b_2 = a_1;

    // Находим c_2 из условия прохождения через среднюю точку:
    double c_2 = -(a_2 * mid_x + b_2 * mid_y);


    // === 3rd step === 

    std::vector<cv::Point> edge_points;

    const double epsilon = 1e-5;

    int cols = frame->cols;
    int rows = frame->rows;

    // Пересечение с левой границей (x = 0)
    if (std::abs(b_2) > epsilon) 
    {
        double y = -c_2 / b_2;

        if (y >= 0 && y < rows) 
        {
            edge_points.push_back(cv::Point(0, std::round(y)));
        }
    }

    // Пересечение с правой границей (x = cols - 1)
    if (std::abs(b_2) > epsilon) 
    {
        double y = -(a_2 * (cols - 1) + c_2) / b_2;

        if (y >= 0 && y < rows) 
        {
            edge_points.push_back(cv::Point(cols - 1, std::round(y)));
        }
    }

    // Пересечение с верхней границей (y = 0)
    if (std::abs(a_2) > epsilon) {
        double x = -c_2 / a_2;
        if (x >= 0 && x < cols) {
            edge_points.push_back(cv::Point(std::round(x), 0));
        }
    }

    // Пересечение с нижней границей (y = rows - 1)
    if (std::abs(a_2) > epsilon) 
    {
        double x = -(b_2 * (rows - 1) + c_2) / a_2;

        if (x >= 0 && x < cols) 
        {
            edge_points.push_back(cv::Point(std::round(x), rows - 1));
        }
    }


    // === 4th step === 

    if (edge_points.size() >= 2) 
    {
        // Берем первые две найденные точки пересечения с границами
        cv::Point p_start = edge_points[0];
        cv::Point p_end = edge_points[1];

        // Инициализируем итератор линии (8-связность для непрерывного прохода)
        cv::LineIterator line_it(*frame, p_start, p_end, 8);
        
        int dash_length = 10;   // Длина закрашенного штриха в пикселях
        int space_length = 10;  // Длина пустого пространства в пикселях
        int current_step = 0;

        for (int i = 0; i < line_it.count; ++i, ++line_it) 
        {
            // Если мы находимся в пределах длины штриха — рисуем пиксель
            if (current_step < dash_length) 
            {
                // Синий цвет в BGR — cv::Scalar(255, 0, 0)
                // Толщина 3px создается закрашенным кругом с радиусом 1 (диаметр = 3 пикселя)
                cv::circle(*frame, line_it.pos(), 1, cv::Scalar(255, 0, 0), -1);
            }
            
            // Сбрасываем шаг по достижении полной длины одного цикла (штрих + пробел)
            current_step = (current_step + 1) % (dash_length + space_length);
        }
    }


    // === 5th step === 

    double delta_x = x_2 - x_1;
    double delta_y = y_2 - y_1;
    double distance_pixels = std::hypot(delta_x, delta_y);
    
    // Защита от деления на ноль (если точки совпали, масштаб равен 0)
    if (distance_pixels > epsilon) 
    {
        // d_n — это реальный диаметр сопла в мм. 
        // Делим мм на пиксели, чтобы узнать, сколько мм в одном пикселе.
        controlled_mask->mm_in_pixel = controlled_mask->d_n / distance_pixels;
    } 
    else 
    {
        controlled_mask->mm_in_pixel = 0.0;
    }

    // === 6th step === 

    // 1. Запись коэффициентов перпендикулярной (осевой) линии
    controlled_mask->axe_line_coefficients.a = static_cast<float>(a_2);
    controlled_mask->axe_line_coefficients.b = static_cast<float>(b_2);
    controlled_mask->axe_line_coefficients.c = static_cast<float>(c_2);
    controlled_mask->axe_line_coefficients.calculated = true;

    // 2. Расчет угла наклона оси относительно базовой горизонтали экрана
    double angle_rad = std::atan2(a_2, -b_2);

    // Переводим радианы в градусы (от -180 до 180) с использованием M_PI из C++17
    #ifndef M_PI
    #define M_PI 3.14159265358979323846
    #endif

    // Need to reverse)
    controlled_mask->basic_axe_angle = -static_cast<float>(angle_rad * 180.0 / M_PI);


    // === Bonus step ===

    // Render main calculated values

    
    // ===== MASK MAIN CALCULATED VALUES ===== 

    int font_face = cv::FONT_HERSHEY_SIMPLEX;
    double font_scale = 1.0;


    char scale_str[64];
    char angle_str[64];

    std::snprintf(scale_str, sizeof(scale_str), "Scale: %.4f mm/px", controlled_mask->mm_in_pixel);
    std::snprintf(angle_str, sizeof(angle_str), "Angle: %.2f deg", controlled_mask->basic_axe_angle);

    // Шрифт в 2 раза меньше базового, толщина 1
    double text_scale = font_scale * 0.5;
    int text_thickness = 1; 
    int text_baseline = 0;

    // Считаем метрики для первой строки, чтобы идеально выровнять по правому краю
    cv::Size scale_size = cv::getTextSize(scale_str, font_face, text_scale, text_thickness, &text_baseline);
    cv::Size angle_size = cv::getTextSize(angle_str, font_face, text_scale, text_thickness, &text_baseline);

    // Желтый цвет в формате BGR
    cv::Scalar yellow_color(0, 255, 255);

    // Координаты для 1-й строки (Масштаб): отступ 10px сверху, выравнивание по правому краю кадра
    int top_x_scale = frame->cols - scale_size.width - 10;
    int top_y_scale = scale_size.height + 10; 

    cv::putText(

        *frame,
        scale_str,
        cv::Point(top_x_scale, top_y_scale),
        font_face,
        text_scale,
        yellow_color,
        text_thickness,
        cv::LINE_AA

    );

    // Координаты для 2-й строки (Угол): встает строго под первой строкой с учетом базовой линии
    int top_x_angle = frame->cols - angle_size.width - 10;
    int top_y_angle = top_y_scale + angle_size.height + text_baseline + 8; // 8 пикселей — аккуратный межстрочный интервал

    cv::putText(

        *frame,
        angle_str,
        cv::Point(top_x_angle, top_y_angle),
        font_face,
        text_scale,
        yellow_color,
        text_thickness,
        cv::LINE_AA

    );
    
    // ===== MASK MAIN CALCULATED VALUES ===== 

    // ===== MASK SETUP LOGIC =====

}


// =========================================================================================== MASK 2 PROCESSING
// =========================================================================================== MASK 2 PROCESSING

void mask_2_processing_ms_1(cv::Mat* frame)
{
    if (!frame || frame->empty())
        return;


    // =======================================================================================
    // GET CONTROLLED MASK

    // Get current jet mask settings.
    //
    // This context contains the HSV boundaries selected by the user
    // or loaded from a preset.

    jet_detection_mask* controlled_mask = &masks_data.file_1_masks.jet_mask;

    // =======================================================================================
    // GET CONTROLLED MASK


    // =======================================================================================
    // CHECK HSV RANGE

    // The lower boundary must be strictly smaller than the upper boundary.
    //
    // H: 0..179
    // S: 0..255
    // V: 0..255

    if (
        controlled_mask->h_min >= controlled_mask->h_max ||
        controlled_mask->s_min >= controlled_mask->s_max ||
        controlled_mask->v_min >= controlled_mask->v_max
    )
    {
        return;
    }

    // =======================================================================================
    // CHECK HSV RANGE


    // =======================================================================================
    // BGR -> HSV

    // Convert the source frame from BGR to HSV.
    //
    // HSV allows us to independently control:
    //
    //      H = Hue
    //      S = Saturation
    //      V = Value

    cv::Mat image_hsv;

    cv::cvtColor(
        *frame,
        image_hsv,
        cv::COLOR_BGR2HSV
    );

    // =======================================================================================
    // BGR -> HSV


    // =======================================================================================
    // LIGHT GAUSSIAN BLUR

    // Apply a very small blur to suppress small pixel-to-pixel
    // fluctuations around the jet boundary.
    //
    // 3x3 is intentionally small.
    //
    // The purpose is to make the resulting binary boundary more stable
    // without significantly changing the geometry of the detected jet.

    cv::GaussianBlur(
        image_hsv,
        image_hsv,
        cv::Size(3, 3),
        0
    );

    // =======================================================================================
    // LIGHT GAUSSIAN BLUR


    // =======================================================================================
    // CREATE HSV RANGE

    cv::Scalar lower_color(

        controlled_mask->h_min,
        controlled_mask->s_min,
        controlled_mask->v_min

    );

    cv::Scalar upper_color(

        controlled_mask->h_max,
        controlled_mask->s_max,
        controlled_mask->v_max

    );

    // =======================================================================================
    // CREATE HSV RANGE


    // =======================================================================================
    // CREATE BINARY MASK

    // Pixels inside the selected HSV range become 255.
    // Pixels outside the range become 0.
    //
    // Result:
    //
    //      255 = detected jet
    //        0 = background

    cv::Mat image_mask;

    cv::inRange(
        image_hsv,
        lower_color,
        upper_color,
        image_mask
    );

    // =======================================================================================
    // CREATE BINARY MASK


    // =======================================================================================
    // MASK -> BGR

    // image_mask is CV_8UC1.
    //
    // The rest of the current rendering pipeline expects the frame
    // to remain a 3-channel BGR image.
    //
    // Therefore convert the binary mask back to BGR before writing it
    // into the main frame.
    //
    // Result:
    //
    //      detected jet  -> (255,255,255)
    //      background    -> (0,0,0)

    cv::Mat image_mask_bgr;

    cv::cvtColor(

        image_mask,
        image_mask_bgr,
        cv::COLOR_GRAY2BGR

    );

    // =======================================================================================
    // MASK -> BGR


    // =======================================================================================
    // WRITE RESULT BACK TO FRAME

    // Replace the current frame with the processed jet mask.
    //
    // IMPORTANT:
    // frame remains CV_8UC3 BGR, so the next processing stage
    // and the OpenCV -> SDL translation can continue working
    // with the same image format.

    image_mask_bgr.copyTo(*frame);

    // =======================================================================================
    // WRITE RESULT BACK TO FRAME
}


void mask_3_processing_ms_1(cv::Mat* frame)
{
    /*
                    ORIGINAL IMAGE
                          │
                          ▼
                ┌───────────────────┐
                │ Light Blur        │
                │ optional          │
                │ 1×1 / OFF         │
                └─────────┬─────────┘
                          │
                          ▼
              ┌───────────────────────┐
              │ Brightness Threshold  │
              │                       │
              │ V > V_min             │
              └───────────┬───────────┘
                          │
                          ▼
              ┌───────────────────────┐
              │ Color Filter          │
              │                       │
              │ B/G/R min/max         │
              └───────────┬───────────┘
                          │
                          ▼
                    FIRST MASK
                          │
                          │
                    ──────┼──────
                          │
                          ▼
                        CANNY
                          │
                          ▼
                        DILATE
                          │
                          ▼
                    AREA / LENGTH FILTERING
                 min area / max area
                 min length / max length
                          │
                          ▼
                    FINAL MASK
    
    */


    if (!frame || frame->empty()) return;

    // Mask processing logic

    const std::string text = "MASK_3";

    int font_face = cv::FONT_HERSHEY_SIMPLEX;
    double font_scale = 1.0;
    int thickness = 2;

    int baseline = 0;

    cv::Size text_size = cv::getTextSize(
        text,
        font_face,
        font_scale,
        thickness,
        &baseline
    );

    int x = (frame->cols) - 1 * text_size.width - 10;
    int y = (frame->rows) - 10;

    cv::putText(
        *frame,
        text,
        cv::Point(x, y),
        font_face,
        font_scale,
        cv::Scalar(0, 255, 0),
        thickness,
        cv::LINE_AA
    );

}


// =========================================================================================== OPENCV PIPELINE SETUP FUNCTIONS


// =========================================================================================== CHOOSEN MASK AND FILE HIGHLIGHT


void choosen_mask_and_file_init()
{
    highlight_ms_1.highlight_hex_color = "#eaff00";
    highlight_ms_1.highlight_line_width = 5;

    choose_mask_1_ms_1();
    choose_current_file_ms_1();
}


void highlight_choosen_mask_ms_1(SDL_Renderer* renderer)
{
    rectangle_borders_draw_by_color(

        highlight_ms_1.x_m,
        highlight_ms_1.y_m,
        highlight_ms_1.w_m,
        highlight_ms_1.h_m,
        highlight_ms_1.highlight_line_width,
        hex_to_sdl_color(highlight_ms_1.highlight_hex_color, 255),
        renderer

    );
}


void highlight_choosen_file_ms_1(SDL_Renderer* renderer)
{
    rectangle_borders_draw_by_color(

        highlight_ms_1.x_f,
        highlight_ms_1.y_f,
        highlight_ms_1.w_f,
        highlight_ms_1.h_f,
        highlight_ms_1.highlight_line_width,
        hex_to_sdl_color(highlight_ms_1.highlight_hex_color, 255),
        renderer

    );
}


void highlight_video_texture_ms_1(SDL_Renderer* renderer)
{
    rectangle_borders_draw_by_color(

        Video_preview_texture_ms_1->get_x_render_point(),
        Video_preview_texture_ms_1->get_y_render_point(),
        Video_preview_texture_ms_1->get_width_size() + highlight_ms_1.highlight_line_width,
        Video_preview_texture_ms_1->get_height_size() + highlight_ms_1.highlight_line_width,
        highlight_ms_1.highlight_line_width,
        App_palette.get_current_palette().basic_border_color,
        renderer

    );
}



// =========================================================================================== CHOOSEN MASK AND FILE HIGHLIGHT





// =========================================================================================== CLICK PERMISSION FUNCTIONS

bool file_1_choose_ms_1_permission()
{
    //
    return true;
}


bool file_2_choose_ms_1_permission()
{
    //
    return false;
}


bool file_3_choose_ms_1_permission()
{
    //
    return true;
}


bool file_4_choose_ms_1_permission()
{
    //

    return true;


}



bool file_5_choose_ms_1_permission()
{
    //

    return false;
}


bool file_6_choose_ms_1_permission()
{
    //
    return true;
}



bool next_state_permission_ms_1()
{
    //
    return true;
}



// =========================================================================================== CLICK PERMISSION FUNCTIONS



// =========================================================================================== OPENCV PART OF THE STATE

// ===== Functions =====

void opencv_setup_ms_1()
{

    // opencv_global_update_ctx.current_file_for_mask_setup = FILE_1_CF; 
    // opencv_global_update_ctx.current_mask_for_mask_setup = MASK_1_CM;
    // opencv_global_update_ctx.current_frame_processor = mask_1_processing_ms_1;
    choosen_mask_and_file_init();


    opencv_global_update_ctx.current_texture_container = Video_preview_texture_ms_1;

    opencv_global_update_ctx.playback_state = VIDEO_PAUSED_VPS;
    opencv_global_update_ctx.current_frame_index = 0;

    opencv_global_update_ctx.need_reset = true;
    opencv_global_update_ctx.show_kingsize = false;
    opencv_global_update_ctx.kingsize_live_transmission = false; 

}


void opencv_update_ms_1()
{
    opencv_global_update();
}

void opencv_render_by_translator_ms_1(SDL_Renderer* renderer)
{
    Video_preview_panel_ms_1->render(renderer);
}

void opencv_free_and_nullptr_ms_1()
{
    // Nothing more (check 1.2 state header to know why)
    
    kingsize_window_close();
    
    opencv_global_update_ctx.show_kingsize = false;
    opencv_global_update_ctx.kingsize_live_transmission = false; 
}

// =========================================================================================== OPENCV PART OF THE STATE