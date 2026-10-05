// 1.3_FLOW_PARAMETERS_CALCULATION.cpp


// =========================================================================================== IMPORT

#include "1.3_FLOW_PARAMETERS_CALCULATION.h"


#include "../../../../program_gui/basic_elements/UI_elements/my_sdl_textbox/my_sdl_textbox.h"
#include "../../../../program_gui/basic_elements/UI_elements/my_sdl_panel/my_sdl_panel.h"
#include "../../../../program_gui/basic_elements/UI_elements/my_sdl_texture/my_sdl_texture.h"
#include "../../../../program_gui/basic_elements/UI_elements/my_sdl_button/my_sdl_button.h"


// Predeclare for switching states
#include "../../program_states.h"

#include "../../../app.h"

// Log
#include <iostream>


// Check
#include "../1.1_FILE_CHOOSE/1.1_FILE_CHOOSE.h"


#include <cmath>



// =========================================================================================== IMPORT




// =========================================================================================== NOTE


/**
*        enter
*        │
*        ├─ create UI
*        ├─ opencv_calculation_global_setup()
*        │    ├─ определить используемые файлы
*        │    ├─ заполнить global_processing_data
*        │    ├─ посчитать operations_count
*        │    └─ создать 3 Mat
*        │
*        └─ setup UI
*            │
*        update ─────────────────────────────────────┐
*        │                                           │
*        ├─ UI @240                                  │
*        │    ├─ elements_update                     │
*        │    │    └─ progress_bar_update            │
*        │    │                                      |
*        │    └─ actions                             │
*        │                                           │
*        └─ opencv_calculation_global_update()       │
*            │                                       │
*            ├─ выбрать текущий файл                 │
*            ├─ при need_reset открыть видео         │
*            ├─ прочитать frame                      │
*            ├─ processing_stage_1                   │
*            ├─ processing_stage_2                   │
*            ├─ processing_stage_3_1                 │
*            ├─ обновить frame                       │
*            ├─ определить конец pass                │
*            └─ перейти к следующему файлу           │
*                                                    │
*        render @120                                 │
*        ├─ panel                                    │
*        └─ progress bar                             │
*
*
*/


// =========================================================================================== NOTE


// =========================================================================================== STATE DATA

// RAII + lifecycle management

My_SDL_panel* flow_parameters_calculation_panel = nullptr;

My_SDL_textbox* percentage_textbox;
My_SDL_textbox* file_textbox;
My_SDL_textbox* mask_textbox;
My_SDL_textbox* frame_textbox;

My_SDL_button* next_state_button;

// =========================================================================================== STATE DATA


// =========================================================================================== STATE INNER FUNCTIONS PREDECLARATION

void flow_parameters_calculation_elements_create();

void flow_parameters_calculation_elements_setup();

void flow_parameters_calculation_elements_free_and_nullptr();

void flow_parameters_calculation_elements_update();

void reset_passed_by_dictionary_textboxes_if_language_switched_fpc();

void flow_parameters_calculation_actions();

void flow_parameters_calculation_elements_render(SDL_Renderer* renderer);

// =========================================================================================== STATE INNER FUNCTIONS PREDECLARATION


// =========================================================================================== MAIN STATE API


void flow_parameters_calculation_enter()
{
    // Log the enter in console
    std::cout << "Entering flow_parameters_calculation\n"; 

    // ===== State allocation =====

    flow_parameters_calculation_elements_create();


    // !!! WARNING !!!
    //
    // CREATE MATs and texture which 
    // should be deallocated at the 
    // state 1.4
    //
    // !!! WARNING !!!

    opencv_calculation_global_setup();

    // ===== State allocation =====


    // Elements setup

    flow_parameters_calculation_elements_setup();

}



void flow_parameters_calculation_exit()
{
    // ===== State deallocation =====

    flow_parameters_calculation_elements_free_and_nullptr();

    opencv_calculation_global_free_and_nullptr();

    // ===== State deallocation =====


    // Log the exit in console

    std::cout << "Exiting flow_parameters_calculation\n"; 

}


void flow_parameters_calculation_update()
{
    // Update inputs
    if (App_timer_1.can_execute(Execute_zone_ID::HZ_1000))
    {
        App_inputs.update();
    }


    if (App_timer_1.can_execute(Execute_zone_ID::HZ_240))
    {

        flow_parameters_calculation_elements_update();

        flow_parameters_calculation_actions();
    }

    // Update OPENCV calculations part without freq limits
    opencv_calculation_global_update();

}


void flow_parameters_calculation_render(SDL_Renderer* renderer)
{
    if (App_timer_1.can_execute(Execute_zone_ID::HZ_120))
    {
        flow_parameters_calculation_elements_render(renderer);
    }
}

// =========================================================================================== MAIN STATE API


// =========================================================================================== DATA

int WINDOW_WIDTH = MAIN_WINDOW_H_SIZE;
int WINDOW_HEIGHT = MAIN_WINDOW_V_SIZE;


// Rectangle



int progress_bar_width = WINDOW_WIDTH;
int progress_bar_height = static_cast<int>(0.1 * WINDOW_HEIGHT);


int pb_x_1 = WINDOW_WIDTH / 2;
int pb_y_1 = WINDOW_HEIGHT / 2;


// Lines

int progress_bar_lines_width = 10;

int pb_l_1_x_1 = 0;
int pb_l_1_y_1 = WINDOW_HEIGHT / 2 - progress_bar_height / 2;

int pb_l_1_x_2 = progress_bar_width;
int pb_l_1_y_2 = WINDOW_HEIGHT / 2 - progress_bar_height / 2;


int pb_l_2_x_1 = 0;
int pb_l_2_y_1 = WINDOW_HEIGHT / 2 + progress_bar_height / 2;

int pb_l_2_x_2 = progress_bar_width;
int pb_l_2_y_2 = WINDOW_HEIGHT / 2 + progress_bar_height / 2;


// =========================================================================================== DATA


// =========================================================================================== INNER STATE FUNCTIONS


// =========================================================================================== STATE INNER FUNCTIONS REALIZATION

void flow_parameters_calculation_elements_create()
{
    // flow_parameters_calculation panel create
    flow_parameters_calculation_panel = new My_SDL_panel();


    percentage_textbox = new My_SDL_textbox();
    file_textbox = new My_SDL_textbox();
    mask_textbox = new My_SDL_textbox();
    frame_textbox = new My_SDL_textbox();

    next_state_button = new My_SDL_button();

}


void flow_parameters_calculation_elements_setup()
{
    // flow_parameters_calculation panel setup

    flow_parameters_calculation_panel->set_render_point(MAIN_WINDOW_H_SIZE / 2, MAIN_WINDOW_V_SIZE / 2);
    flow_parameters_calculation_panel->set_size(MAIN_WINDOW_H_SIZE, MAIN_WINDOW_V_SIZE);
    flow_parameters_calculation_panel->set_border_radius(0);


    percentage_textbox->switch_textbox_type(ORDINARY_TEXT);
    percentage_textbox->set_render_point(pb_x_1, pb_y_1);

    file_textbox->switch_textbox_type(SMALL_TEXT);
    file_textbox->set_render_point(0.1 * WINDOW_WIDTH, 0.6 * WINDOW_HEIGHT);

    mask_textbox->switch_textbox_type(SMALL_TEXT);
    mask_textbox->set_render_point(0.1 * WINDOW_WIDTH, 0.65 * WINDOW_HEIGHT);

    frame_textbox->switch_textbox_type(SMALL_TEXT);
    frame_textbox->set_render_point(0.1 * WINDOW_WIDTH, 0.7 * WINDOW_HEIGHT);

}


void flow_parameters_calculation_elements_free_and_nullptr()
{
    // Free all elements

    flow_parameters_calculation_panel->delete_element();

    percentage_textbox->delete_element();
    file_textbox->delete_element();
    mask_textbox->delete_element();
    frame_textbox->delete_element();

    next_state_button->delete_element();


    // Nullptr the pointers

    flow_parameters_calculation_panel = nullptr;


    percentage_textbox = nullptr;
    file_textbox = nullptr;
    mask_textbox = nullptr;
    frame_textbox = nullptr;

    next_state_button = nullptr;
    
}


void flow_parameters_calculation_elements_update()
{
    // Check if textboxes need content renew
    reset_passed_by_dictionary_textboxes_if_language_switched_fpc();

    // Update all elements
    flow_parameters_calculation_panel->update();

    // Update progress bar
    progress_bar_update();
}


void reset_passed_by_dictionary_textboxes_if_language_switched_fpc()
{
    // Repeat content set if language switched
    if (App_lang.get_lang_reset_flag())
    {
        // All textboxes here
        progress_bar_update();
    }
}


void flow_parameters_calculation_actions()
{
    // Switch the state to EXIT if EXIT pressed
    if (App_inputs.is_just_released(Key_actions::EXIT))
    {
        this_app.app_sm.request_state_change(MASKS_SETUP_ID_1);
    }


    // TEST
    if (App_inputs.is_just_released(Key_actions::ENTER))
    {
        
    }
}


void flow_parameters_calculation_elements_render(SDL_Renderer* renderer)
{
    // Render all elements
    flow_parameters_calculation_panel->render(renderer);

    // Progress bar render
    progress_bar_render(renderer);

}

// =========================================================================================== STATE INNER FUNCTIONS REALIZATION


// =========================================================================================== OPENCV PART OF THE STATE


// =========================================================================================== REDEFINE FOR EXTERN DATA

files_processing_data global_processing_data;


flow_calculation_progress_bar state_progress_bar;


cv::VideoCapture* video_capture_device_global_fpc = nullptr;

cv::Mat* calculation_cv_mat_mask_1_global = nullptr;
cv::Mat* calculation_cv_mat_mask_2_global = nullptr;
cv::Mat* calculation_cv_mat_mask_3_global = nullptr;

bool opencv_calculation_pipeline_reset_global = false;


opencv_calculation_update_ctx opencv_global_calculation_update_ctx;


bool global_calculation_end_flag = false;


parsed_video_data video_data;

nozzle_detection_mask nozzle_mask_to_process;
jet_detection_mask jet_mask_to_process;
particle_detection_mask particle_mask_to_process;

processing_1_data* data_to_process_1;
processing_2_data* data_to_process_2;
processing_3_data* data_to_process_3;

// =========================================================================================== REDEFINE FOR EXTERN DATA


// ===== Functions =====

void opencv_calculation_global_setup()
{
    // Block of the reinit
    if (opencv_calculation_pipeline_reset_global != true)
    {
        calculation_cv_mat_mask_1_global = new cv::Mat();
        calculation_cv_mat_mask_2_global = new cv::Mat();
        calculation_cv_mat_mask_3_global = new cv::Mat();

        // Will be reseted (for size correction) at the setup 
        // of each inner state (1.2.1  1.2.6)


        // ===== FILES DATA INIT =====

        bool file_1_need_init = file_choose_info.panels_states.file_1_panel_state ==
                                file_choose_panel_state::CHOSEN_STATE;

        bool file_2_need_init = file_choose_info.panels_states.file_2_panel_state ==
                                file_choose_panel_state::CHOSEN_STATE;

        bool file_3_need_init = file_choose_info.panels_states.file_3_panel_state ==
                                file_choose_panel_state::CHOSEN_STATE;

        bool file_4_need_init = file_choose_info.panels_states.file_4_panel_state ==
                                file_choose_panel_state::CHOSEN_STATE;

        bool file_5_need_init = file_choose_info.panels_states.file_5_panel_state ==
                                file_choose_panel_state::CHOSEN_STATE;

        bool file_6_need_init = file_choose_info.panels_states.file_6_panel_state ==
                                file_choose_panel_state::CHOSEN_STATE;


        // Set using flag                        

        if (file_1_need_init)
        {
            global_processing_data.file_1.using_flag = true;

            global_processing_data.file_1.file = FILE_1_CF;
            global_processing_data.file_1.file_path = file_choose_info.file_1_path;

        }

        if (file_2_need_init)
        {
            global_processing_data.file_2.using_flag = true;

            global_processing_data.file_2.file = FILE_2_CF;
            global_processing_data.file_2.file_path = file_choose_info.file_2_path;
        }

        if (file_3_need_init)
        {
            global_processing_data.file_3.using_flag = true;

            global_processing_data.file_3.file = FILE_3_CF;
            global_processing_data.file_3.file_path = file_choose_info.file_3_path;
        }

        if (file_4_need_init)
        {
            global_processing_data.file_4.using_flag = true;

            global_processing_data.file_4.file = FILE_4_CF;
            global_processing_data.file_4.file_path = file_choose_info.file_4_path;
        }

        if (file_5_need_init)
        {
            global_processing_data.file_5.using_flag = true;

            global_processing_data.file_5.file = FILE_5_CF;
            global_processing_data.file_5.file_path = file_choose_info.file_5_path;
        }

        if (file_6_need_init)
        {
            global_processing_data.file_6.using_flag = true;

            global_processing_data.file_6.file = FILE_6_CF;
            global_processing_data.file_6.file_path = file_choose_info.file_6_path;
        }


        // ===== FILES DATA INIT =====


        // ===== PROGRESS BAR INIT =====
        
        state_progress_bar.frames_quantity = files_metadata.video_1_data.frames_quantity;


        unsigned int total_frames = 0;

        // 1 pass for 1, 2, 3.1 and 1 pass for 3.2

        // Formula explanation: (2 * frames_quantity) - 1
        // Each video requires 2 global passes:
        // 1st pass: Processes each individual frame (N operations for N frames).
        // 2nd pass: Processes consecutive frame pairs (N - 1 operations for N frames).
        // Total operations per video = N + (N - 1) = 2N - 1.

        if (file_1_need_init) total_frames += 2 * files_metadata.video_1_data.frames_quantity - 1;
        if (file_2_need_init) total_frames += 2 * files_metadata.video_2_data.frames_quantity - 1;
        if (file_3_need_init) total_frames += 2 * files_metadata.video_3_data.frames_quantity - 1;
        if (file_4_need_init) total_frames += 2 * files_metadata.video_4_data.frames_quantity - 1;
        if (file_5_need_init) total_frames += 2 * files_metadata.video_5_data.frames_quantity - 1;
        if (file_6_need_init) total_frames += 2 * files_metadata.video_6_data.frames_quantity - 1;

        state_progress_bar.operations_count = total_frames;

        // ===== PROGRESS BAR INIT =====


        opencv_calculation_pipeline_reset_global = true;


        // TEST
        opencv_global_calculation_update_ctx.current_frame_processor = processing_stage_1;
    }

    if (TEST_MODE) std::cout << "Mats and texture created\n" << std::endl;   
}


void switch_video_for_calculation(const std::string& new_file_path) 
{
    // 1. DELETE old capture device if video is opened
    if (video_capture_device_global_fpc != nullptr)
    {
        if (video_capture_device_global_fpc->isOpened())
        {
            // Close file
            video_capture_device_global_fpc->release();
        }

        // Free the memory 
        delete video_capture_device_global_fpc;
        
        // Free the pointer
        video_capture_device_global_fpc = nullptr;
    }

    if (new_file_path.empty())
    {
        std::cerr << "Error: video path is empty\n";
        opencv_global_calculation_update_ctx.total_frame_count = 0;
        return;
    }

    // 2. Create new capture device
    video_capture_device_global_fpc = new cv::VideoCapture(new_file_path);

    // 3. Check
    if (!video_capture_device_global_fpc->isOpened())
    {
        std::cerr << "Error: Could not open video " << new_file_path << std::endl;
    } 
    else if (TEST_MODE)
    {
        std::cout << "Successfully switched to: " << new_file_path << "\n" << std::endl;
    }


    // 4. Update metadata and starting point

    // Set the 0 index
    opencv_global_calculation_update_ctx.current_frame_index = 0;

    // Get total frame count
    opencv_global_calculation_update_ctx.total_frame_count =
        video_capture_device_global_fpc->isOpened()
            ? static_cast<int>(video_capture_device_global_fpc->get(cv::CAP_PROP_FRAME_COUNT))
            : 0;


    // Reset the progress bar data
    state_progress_bar.current_frame = opencv_global_calculation_update_ctx.current_frame_index;
    state_progress_bar.frames_quantity = opencv_global_calculation_update_ctx.total_frame_count;
}




// Helpers for big screen translation

void kingsize_window_init_fpc(cv::Mat* mat)
{
    cv::namedWindow(
        "KINGSIZE_TEST",
        cv::WINDOW_NORMAL
    );

    cv::resizeWindow(
        "KINGSIZE_TEST",
        mat->cols * 3,
        mat->rows * 3
    );
}


void kingsize_window_close_fpc()
{
    cv::destroyWindow("KINGSIZE_TEST");
}



void opencv_calculation_global_update()
{
    static bool calculation_ends = false;

    if (calculation_ends) 
    {
        global_calculation_end_flag = true;
        return;
    }

    // ===== PREPROCESSING =====

    // Current data to work with

    current_file_ms file_to_check_now;

    std::string file_path;

    file_processing_data* data_to_control = nullptr;


    std::array<file_processing_data*, 6> files = {

        &global_processing_data.file_1,
        &global_processing_data.file_2,
        &global_processing_data.file_3,
        &global_processing_data.file_4,
        &global_processing_data.file_5,
        &global_processing_data.file_6

    };


    for (auto* file : files)
    {
        if (file->using_flag && !file->calculated_flag)
        {   
            // Set the current file to work with
            file_to_check_now = file->file;
            file_path = file->file_path;

            data_to_control = file;

            // Drop for cycle till the file data ain't calculated
            break;
        }
    }

     
    // Calculation ended or not possible
    if (data_to_control == nullptr)
    {
        calculation_ends = true;
        return;
    }


    nozzle_detection_mask curr_ndm;
    jet_detection_mask curr_jdm;
    particle_detection_mask curr_pdm;


    processing_1_data* curr_dtp_1;
    processing_2_data* curr_dtp_2;
    processing_3_data* curr_dtp_3;


    switch (file_to_check_now)
    {
        case FILE_1_CF:
        {
            opencv_global_calculation_update_ctx.current_file_for_mask_setup = FILE_1_CF;

            curr_ndm = masks_data.file_1_masks.nozzle_mask;
            curr_jdm = masks_data.file_1_masks.jet_mask;
            curr_pdm = masks_data.file_1_masks.particle_mask;


            curr_dtp_1 = &global_processing_data.file_1.processing_1;
            curr_dtp_2 = &global_processing_data.file_1.processing_2;
            curr_dtp_3 = &global_processing_data.file_1.processing_3;


            video_data = files_metadata.video_1_data;

            break;
        }

        case FILE_2_CF:
        {
            opencv_global_calculation_update_ctx.current_file_for_mask_setup = FILE_2_CF;

            curr_ndm = masks_data.file_2_masks.nozzle_mask;
            curr_jdm = masks_data.file_2_masks.jet_mask;
            curr_pdm = masks_data.file_2_masks.particle_mask;


            curr_dtp_1 = &global_processing_data.file_2.processing_1;
            curr_dtp_2 = &global_processing_data.file_2.processing_2;
            curr_dtp_3 = &global_processing_data.file_2.processing_3;

            video_data = files_metadata.video_2_data;

            
            break;
        }


        case FILE_3_CF:
        {
            opencv_global_calculation_update_ctx.current_file_for_mask_setup = FILE_3_CF;

            curr_ndm = masks_data.file_3_masks.nozzle_mask;
            curr_jdm = masks_data.file_3_masks.jet_mask;
            curr_pdm = masks_data.file_3_masks.particle_mask;


            curr_dtp_1 = &global_processing_data.file_3.processing_1;
            curr_dtp_2 = &global_processing_data.file_3.processing_2;
            curr_dtp_3 = &global_processing_data.file_3.processing_3;

            video_data = files_metadata.video_3_data;

            break;
        }


        case FILE_4_CF:
        {
            opencv_global_calculation_update_ctx.current_file_for_mask_setup = FILE_4_CF;

            curr_ndm = masks_data.file_4_masks.nozzle_mask;
            curr_jdm = masks_data.file_4_masks.jet_mask;
            curr_pdm = masks_data.file_4_masks.particle_mask;


            curr_dtp_1 = &global_processing_data.file_4.processing_1;
            curr_dtp_2 = &global_processing_data.file_4.processing_2;
            curr_dtp_3 = &global_processing_data.file_4.processing_3;


            video_data = files_metadata.video_4_data;

            break;
        }


        case FILE_5_CF:
        {
            opencv_global_calculation_update_ctx.current_file_for_mask_setup = FILE_5_CF;

            curr_ndm = masks_data.file_5_masks.nozzle_mask;
            curr_jdm = masks_data.file_5_masks.jet_mask;
            curr_pdm = masks_data.file_5_masks.particle_mask;


            curr_dtp_1 = &global_processing_data.file_5.processing_1;
            curr_dtp_2 = &global_processing_data.file_5.processing_2;
            curr_dtp_3 = &global_processing_data.file_5.processing_3;


            video_data = files_metadata.video_5_data;

            break;
        }

        case FILE_6_CF:
        {
            opencv_global_calculation_update_ctx.current_file_for_mask_setup = FILE_6_CF;

            curr_ndm = masks_data.file_6_masks.nozzle_mask;
            curr_jdm = masks_data.file_6_masks.jet_mask;
            curr_pdm = masks_data.file_6_masks.particle_mask;


            curr_dtp_1 = &global_processing_data.file_6.processing_1;
            curr_dtp_2 = &global_processing_data.file_6.processing_2;
            curr_dtp_3 = &global_processing_data.file_6.processing_3;

            video_data = files_metadata.video_6_data;

            break;
        }

        default: break;
    }


    // Set the current masks to work with
    nozzle_mask_to_process = curr_ndm;
    jet_mask_to_process = curr_jdm;
    particle_mask_to_process = curr_pdm;

    // Set the answers ctx to fill data
    data_to_process_1 = curr_dtp_1;
    data_to_process_2 = curr_dtp_2;
    data_to_process_3 = curr_dtp_3;


    // Write frame time to work with
    if (curr_dtp_2->frame_time == 0.0f)
    {
        curr_dtp_2->frame_time = video_data.frame_time;
    }


    // ===== PREPROCESSING =====



    // ===== DEFAULT TRANSLATION LOGIC =====

    // First call at the state start
    // we need to create new VCD

    if (opencv_global_calculation_update_ctx.need_reset)
    {
        // USE HELPER
        switch_video_for_calculation(file_path);

        // TODO:
        // FALSE AT INIT. NEED IT?
        // Set calculation stages status
        // data_to_control->stage_1_end = false;
        // data_to_control->stage_2_end = false;


        if (FPC_TEST_MODE)
        {
            std::cout
            << "\n=== SELECT FILE ===\n"
            << "file: " << static_cast<int>(file_to_check_now) << "\n"
            << "path: " << file_path << "\n"
            << "processing_2 ptr: " << data_to_process_2 << "\n";
        }
        

        // Block reinits after reset
        opencv_global_calculation_update_ctx.need_reset = false;

        if (video_capture_device_global_fpc == nullptr ||
            !video_capture_device_global_fpc->isOpened())
        {
            opencv_global_calculation_update_ctx.need_reset = true;
            return;
        }



    }

    if (video_capture_device_global_fpc == nullptr ||
        !video_capture_device_global_fpc->isOpened())
    {
        opencv_global_calculation_update_ctx.need_reset = true;
        return;
    }




    // Play logic (nothing at pause)

    /**
     * 
     *           frame 123
     *               │
     *       ┌───────┼───────┐
     *       ▼       ▼       ▼
     *     clone   clone    clone
     *       │       │       │
     *       ▼       ▼       ▼
     *    stage1   stage2  stage3.1
     *       │       │       │
     *       ▼       ▼       ▼
     *    result1  result2  result3
     * 
     */

    {
        // Show from the start (if it's 1st call)
        if (calculation_cv_mat_mask_1_global->empty())
        {
            opencv_global_calculation_update_ctx.current_frame_index = 0;
        }
    
        // Rewind to current frame
        video_capture_device_global_fpc->set(
            cv::CAP_PROP_POS_FRAMES,
            opencv_global_calculation_update_ctx.current_frame_index
        );
    

        // Read current frame to work with
        *video_capture_device_global_fpc >> *calculation_cv_mat_mask_1_global;


        if (calculation_cv_mat_mask_1_global->empty())
        {
            // EOF / read error
            return;
        }


        // Create independent copies of the original frame
        *calculation_cv_mat_mask_2_global = calculation_cv_mat_mask_1_global->clone();

        *calculation_cv_mat_mask_3_global = calculation_cv_mat_mask_1_global->clone();
    }


    if (TEST_MODE) std::cout << "Capture passed to MAT!\n" << std::endl;

    // ===== DEFAULT TRANSLATION LOGIC =====


    // ===== BLACKBOX WITH PROCESSING LOGIC BY CALLBACK =====

    if (opencv_global_calculation_update_ctx.current_frame_processor != nullptr)
    {
        if (calculation_cv_mat_mask_1_global != nullptr &&
            calculation_cv_mat_mask_2_global != nullptr &&
            calculation_cv_mat_mask_3_global != nullptr
        )
        {
            // CALL A CALLBACK FOR CURRENT MAT
            // THE RENDERER will show the video after processing
            if (!data_to_control->stage_1_end && !data_to_control->stage_2_end)
            {
                opencv_global_calculation_update_ctx.global_operation = PROCESSING_STAGE_1_CGO;

                opencv_global_calculation_update_ctx.operation = MASK_1_PROCESSING_CO;
                opencv_global_calculation_update_ctx.current_frame_processor = processing_stage_1; // set
                opencv_global_calculation_update_ctx.current_frame_processor(calculation_cv_mat_mask_1_global); // call


                opencv_global_calculation_update_ctx.operation = MASK_2_PROCESSING_CO;
                opencv_global_calculation_update_ctx.current_frame_processor = processing_stage_2; // set
                opencv_global_calculation_update_ctx.current_frame_processor(calculation_cv_mat_mask_2_global); // call

                opencv_global_calculation_update_ctx.operation = MASK_3_1_PROCESSING_CO;
                opencv_global_calculation_update_ctx.current_frame_processor = processing_stage_3_1; // set
                opencv_global_calculation_update_ctx.current_frame_processor(calculation_cv_mat_mask_3_global); // call


                // Update frame
                opencv_global_calculation_update_ctx.current_frame_index += 1;

                
                // Check whether Stage 1 has reached the current video's final frame.

                if (
                    
                    opencv_global_calculation_update_ctx.current_frame_index == 
                    opencv_global_calculation_update_ctx.total_frame_count

                )
                {


                    /*

                        Check whether Stage 2 has completed all processing operations for the
                        current video.

                        This check runs after the current frame has been processed and
                        current_frame_index has been incremented. When it reaches
                        total_frame_count, all Stage 2 frame and frame-pair operations for this
                        video are complete, so the final track results can be calculated.

                        The condition also keeps finalization out of the per-frame processing path:
                        it runs only at the end of the video, before the video is marked complete
                        and the processing context is prepared for the next one.

                    */


                    // ===== Finish Stage 1 and calculate video-wide values =====

                    // 1. Mark Stage 1 complete and reset the per-stage frame index.
                    data_to_control->stage_1_end = true;
                    opencv_global_calculation_update_ctx.current_frame_index = 0;


                    // 2. Calculate average light power across the processed frames.

                    // Average light power inside video frames (%).

                    if (!data_to_process_2->frames_mean_light_power_percentage.empty()) 
                    {
                        size_t v_len = curr_dtp_2->frames_mean_light_power_percentage.size();

                        float sum = std::accumulate(
                            
                            data_to_process_2->frames_mean_light_power_percentage.begin(), 
                             data_to_process_2->frames_mean_light_power_percentage.end(), 
                             0.0f
                                                    
                        );

                        
                        curr_dtp_2->video_mean_light_power_percentage = static_cast<float>(sum / v_len);

                    } 
                    else 
                    {
                        curr_dtp_2->video_mean_light_power_percentage = 0.0f;
                    }


                    // 3. Calculate the mean absolute light-power change between frames.
                    
                    if (!data_to_process_2->frames_mean_light_power_percentage.empty())
                    {
                        unsigned int deltas_counter = 0;
                        float sum_of_deltas = 0.0f;

                        for (int i = 0; i < data_to_process_2->frames_mean_light_power_percentage.size() - 1; i++)
                        {   
                            sum_of_deltas += std::abs(data_to_process_2->frames_mean_light_power_percentage[i + 1] -
                                (data_to_process_2->frames_mean_light_power_percentage[i]));

                            deltas_counter += 1; 
                        }   

                        float percent_mean_delta = sum_of_deltas / deltas_counter;

                        // Equal time between frames, so:
                        // divide on frame time (percent per second in answer)
                        if (curr_dtp_2->frame_time != 0)
                            curr_dtp_2->mean_light_power_delta_between_frames = percent_mean_delta; // Not the / curr_dtp_2->frame_time; - it's 1600 or stmthng like XD

                        else curr_dtp_2->mean_light_power_delta_between_frames = 0.0f;
                    }
                    else
                    {
                        curr_dtp_2->mean_light_power_delta_between_frames = 0.0f;
                    }


                    // 4. Calculate median and mean arc width for the whole video.
                    
                    // Zeroes width cases are filtered!
                    
                    std::vector<float> valid_video_jet_amplitudes;

                    valid_video_jet_amplitudes.reserve(data_to_process_2->frames_median_jet_amplitude.size());


                    for (float amp : data_to_process_2->frames_median_jet_amplitude) 
                    {
                        if (amp > 0.0f) 
                        {
                            valid_video_jet_amplitudes.push_back(amp);
                        }
                    }


                    if (!valid_video_jet_amplitudes.empty()) 
                    {
                        size_t mid_idx = valid_video_jet_amplitudes.size() / 2;

                        std::nth_element(
                            valid_video_jet_amplitudes.begin(), 
                            valid_video_jet_amplitudes.begin() + mid_idx, 
                            valid_video_jet_amplitudes.end()
                        );
                        
                        curr_dtp_2->video_median_jet_amplitude = valid_video_jet_amplitudes[mid_idx];



                        size_t v_size = curr_dtp_2->frames_mean_jet_amplitude.size();

                        float sum_mean_amplitude = std::accumulate(

                            curr_dtp_2->frames_mean_jet_amplitude.begin(),
                            curr_dtp_2->frames_mean_jet_amplitude.end(),
                            0.0f

                        );

                        curr_dtp_2->video_mean_jet_amplitude = static_cast<float>(sum_mean_amplitude / v_size);
                    } 
                    else 
                    {
                        curr_dtp_2->video_median_jet_amplitude = 0.0f;
                        curr_dtp_2->video_mean_jet_amplitude = 0.0f;
                    }



                    // 5. Calibrate the reference displacement from consecutive-frame point pairs:
                    //    a. Select an extreme point in frame n+1 inside zone 2.
                    //    b. Match it with a point in frame n inside zone 1.
                    //    c. Collect valid pairs, blend their pixel displacements, and convert
                    //       the result to millimeters for reference_dx and reference_dy.

                    // Buffers for deltas
                    std::vector<float> all_dx;
                    std::vector<float> all_dy;

                    // Frame width
                    int frame_width = video_data.width; 


                    // Borders 

                    float zone_1_x_min = curr_dtp_3->zone_1_x_min_c * frame_width;          // 0.6 * fw
                    float zone_1_x_max = curr_dtp_3->zone_1_x_max_c * frame_width;          // 0.8 * fw

                    float zone_2_x_min = curr_dtp_3->zone_2_x_min_c * frame_width;          // 0.7 * fw
                    float zone_2_x_max = curr_dtp_3->zone_2_x_max_c * frame_width;          // 0.9 * fw


                    // Quantity of frames
                    size_t total_frames = curr_dtp_3->frames_points.size();

                    // Error case
                    if (total_frames <= 0) 
                    {
                        std::cout << "ERROR ERROR ERROR\n\n" << std::endl;
                        return;
                    }
                    

                    // ===== !!! ATTENTION !!! =====

                    // Set the counter for the next step (processing 3.2)
                    curr_dtp_3->frames_points_vectors_count = total_frames - 1;

                    
                    // ===== !!! ATTENTION !!! =====


                    if (total_frames > 1)
                    {
                        for (size_t i = 0; i < total_frames - 1; ++i)
                        {
                            const auto& points_n   = curr_dtp_3->frames_points[i];
                            const auto& points_n1  = curr_dtp_3->frames_points[i + 1];


                            // 1. Find the BOTTOM-RIGHT point in frame (i + 1) within Zone 2 (0.7 to 0.9 * fw).
                            // In SDL/OpenCV coordinate systems, the bottommost point has the MAXIMUM y, and the rightmost has the MAXIMUM x.
                            // Look for the point closest to the bottom-right corner of this zone.

                            desc_c_2D pt_n1 = { -1, -1 };
                            float max_metric_n1 = -1.0f;

                            for (const auto& pt : points_n1)
                            {
                                if (pt.x > zone_2_x_min && pt.x < zone_2_x_max)
                                {
                                    // Метрика удаленности к правому нижнему углу (сумма координат)
                                    float current_metric = static_cast<float>(pt.x + pt.y);

                                    if (current_metric > max_metric_n1)
                                    {
                                        max_metric_n1 = current_metric;
                                        pt_n1 = pt;
                                    }
                                }
                            }

                            // If no point - go to the next case
                            if (pt_n1.x == -1) continue;


                            // 2. Locate the reference point in frame (i) within Zone 1 (0.6 to 0.8 * fw).
                            // Logic: The point must be to the LEFT (x_n < x_n1) and ABOVE (y_n < y_n1) relative to the found pt_n1.
                            // From all valid candidates, select the one with the minimal Y deviation (smallest delta: y_n1 - y_n).

                            desc_c_2D pt_n = { -1, -1 };


                            float min_delta_y = std::numeric_limits<float>::max();


                            for (const auto& pt : points_n)
                            {
                                if (pt.x > zone_1_x_min && pt.x < zone_1_x_max)
                                {
                                    // Check limitations

                                    if (pt.x < pt_n1.x && pt.y < pt_n1.y)
                                    {
                                        float delta_y = static_cast<float>(pt_n1.y - pt.y);

                                        if (delta_y < min_delta_y)
                                        {
                                            min_delta_y = delta_y;

                                            pt_n = pt;
                                        }
                                    }
                                }
                            }

                            
                            // 3. If BOTH points are successfully found, register the extreme pair for the frame.

                            if (pt_n.x != -1)
                            {
                                // Save the pair
                                std::array<desc_c_2D, 2> pair_nodes = { pt_n, pt_n1 };
                                curr_dtp_3->frames_extreme_pairs.push_back(pair_nodes);

                                // Calculate deltas
                                float dx = static_cast<float>(pt_n1.x - pt_n.x);
                                float dy = static_cast<float>(pt_n1.y - pt_n.y);

                                // Add deltas
                                all_dx.push_back(dx);
                                all_dy.push_back(dy);
                            }
                        }
                    }

                        
                    // Blend the collected displacements, convert them to millimeters,
                    // and save them as the reference displacement for Stage 3.2.

                    nozzle_detection_mask* controlled_mask = &nozzle_mask_to_process;


                    if (!all_dx.empty())
                    {
                        size_t mid_index = all_dx.size() / 2;


                        // --- A: Calculate median delta values ---
                        // Copy the arrays, as nth_element will partially reorder the source data.

                        std::vector<float> median_dx_vec = all_dx;
                        std::vector<float> median_dy_vec = all_dy;
                        

                        std::nth_element(median_dx_vec.begin(), median_dx_vec.begin() + mid_index, median_dx_vec.end());
                        std::nth_element(median_dy_vec.begin(), median_dy_vec.begin() + mid_index, median_dy_vec.end());
                        

                        float median_dx = median_dx_vec[mid_index];
                        float median_dy = median_dy_vec[mid_index];


                        // --- B: Calculate arithmetic mean delta values using std::accumulate ---

                        float sum_dx = std::accumulate(all_dx.begin(), all_dx.end(), 0.0f);
                        float sum_dy = std::accumulate(all_dy.begin(), all_dy.end(), 0.0f);
                        
                        float mean_dx = sum_dx / static_cast<float>(all_dx.size());
                        float mean_dy = sum_dy / static_cast<float>(all_dy.size());


                        // --- C: Implement Median-Mean Blend ---
                        // Take the weight from the structure (curr_dtp_3->median_weight) or use the local default (0.5f per specifications).

                        float w_med = curr_dtp_3->median_weight;

                        float w_mean = 1.0f - w_med;

                        float blended_dx_px = (median_dx * w_med) + (mean_dx * w_mean);
                        float blended_dy_px = (median_dy * w_med) + (mean_dy * w_mean);


                        // --- D: Convert pixels into physical millimeters ---

                        float mm_scale = controlled_mask->mm_in_pixel; 


                        // Save final calibration constants into the video structure (already in mm!)

                        curr_dtp_3->reference_dx = blended_dx_px * mm_scale;
                        curr_dtp_3->reference_dy = blended_dy_px * mm_scale;


                        if (FPC_TEST_MODE)
                        {
                            std::cout << ">>> Калибровка завершена успешно! Найдено пар: " << all_dx.size() << std::endl;
                            std::cout << ">>> [Медиана] dx: " << median_dx << " px, dy: " << median_dy << " px" << std::endl;
                            std::cout << ">>> [Среднее] dx: " << mean_dx << " px, dy: " << mean_dy << " px" << std::endl;
                        }

                    }
                    else
                    {
                        if (FPC_TEST_MODE)
                        {
                            std::cout << "[WARN] Не удалось найти крайние пары. Установлен масштабированный дефолтный фолбэк." << std::endl;
                        }
                    }
                                                        
                    
                    // 6. Print the video-wide results in test mode.
                    if (FPC_TEST_MODE)
                    {

                        std::cout
                        << "\n=== VIDEO FINISHED ===\n"
                        << "file: " << static_cast<int>(file_to_check_now) << "\n"
                        << "path: " << file_path << "\n"
                        << "frames light: "
                        << data_to_process_2->frames_mean_light_power_percentage.size()
                        << "\n"
                        << "frames amplitude: "
                        << data_to_process_2->frames_median_jet_amplitude.size()
                        << "\n";


                        std::cout << "\n\nVideo median arc amplitude: " << curr_dtp_2->video_median_jet_amplitude;
                        std::cout << "\n\nVideo mean arc amplitude: " << curr_dtp_2->video_mean_jet_amplitude;

                        std::cout << "\nVideo mean light percentage: " << curr_dtp_2->video_mean_light_power_percentage << std::endl;
                        std::cout << "\nVideo mean light percentage delta (% / frame): " << curr_dtp_2->mean_light_power_delta_between_frames << std::endl;
                    
                    
                        std::cout << ">>> Опорное смещение факела (Бленд в ММ): reference_dx = " << curr_dtp_3->reference_dx 
                        << " мм, reference_dy = " << curr_dtp_3->reference_dy << " мм" << std::endl;
                    
                    }

                    // 7. Mark Stage 1 data as calculated.
                    curr_dtp_2->calculated = true;

                }


                // Operations counter update
                state_progress_bar.operations_counter += 1;
            }


            else if (data_to_control->stage_1_end && !data_to_control->stage_2_end)
            {

                /*

                    Stage 2 processes the current video's frame data and calculates the final
                    flow characteristics. It runs after Stage 1 has completed and before the
                    video is marked as fully processed.

                    Processing pipeline:

                    1. Process the current frame for Stage 3.2:

                        Collect that frame's particle tracks and add them to the per-frame and
                        video-wide track containers. Advance the processed-pair counter and the
                        current operation index.


                    2. When the operation index reaches the current video's operation limit,
                    calculate the final results:

                        - For each frame, blend the median and mean track speed and angle.
                        - Compare consecutive frames and blend the absolute speed and shortest
                            angular deltas.
                        - Calculate the blended main flow across all tracks, classify tracks as
                            straight or deviated, and calculate the corresponding speed, angle,
                            and deviation percentage.

                    3. Print the Stage 3.2 results when test mode is enabled:

                        Then mark the current video as fully processed, set the context to reset, restore the
                        default operation state, and release the current file pointer. The next
                        update can then select and process another video, if one remains.

                */


                opencv_global_calculation_update_ctx.global_operation = PROCESSING_STAGE_2_CGO;


                // Here we must not only set the processing, but pass the particles vector pair
                // and increment the counter of processed pairs to go through vectors iteration cycle
                // without stopping of the other program processes

                opencv_global_calculation_update_ctx.operation = MASK_3_2_PROCESSING_CO;
                opencv_global_calculation_update_ctx.current_frame_processor = processing_stage_3_2; // set

                opencv_global_calculation_update_ctx.current_frame_processor(calculation_cv_mat_mask_3_global); // call
                

                // Increment the operations counter
                curr_dtp_3->frames_points_vectors_counter += 1;

                // This one will work as (curr_dtp_3->frames_points_vectors_counter <= curr_dtp_3->frames_points_vectors_count)
                opencv_global_calculation_update_ctx.current_frame_index += 1;



                // Stage 2 processes N frames and N - 1 frame pairs. When the operation
                // count reaches the current video's limit, calculate its final answers.
                if (opencv_global_calculation_update_ctx.current_frame_index == 
                    opencv_global_calculation_update_ctx.total_frame_count)
                {
                    // ===== Finish Stage 2 and calculate track results =====

                    // 1. Define the angle, mean, and median helpers used by the calculations.

                    auto normalize_angle = [](float angle) -> float
                    {
                        while (angle > 180.0f)
                            angle -= 360.0f;

                        while (angle < -180.0f)
                            angle += 360.0f;

                        return angle;
                    };


                    auto calculate_mean = [](const std::vector<single_track>& tracks,
                                             bool use_speed) -> float
                    {
                        if (tracks.empty())
                            return 0.0f;

                        float sum = 0.0f;

                        for (const single_track& track : tracks)
                        {
                            sum += use_speed
                                ? track.speed
                                : track.angle;
                        }

                        return sum / static_cast<float>(tracks.size());
                    };


                    auto calculate_median = [](const std::vector<single_track>& tracks,
                                               bool use_speed) -> float
                    {
                        if (tracks.empty())
                            return 0.0f;

                        std::vector<float> values;
                        values.reserve(tracks.size());

                        for (const single_track& track : tracks)
                        {
                            values.push_back(
                                use_speed
                                    ? track.speed
                                    : track.angle
                            );
                        }

                        const size_t middle = values.size() / 2;

                        std::nth_element(
                            values.begin(),
                            values.begin() + middle,
                            values.end()
                        );

                        if (values.size() % 2 != 0)
                        {
                            return values[middle];
                        }

                        const float upper = values[middle];

                        std::nth_element(
                            values.begin(),
                            values.begin() + middle - 1,
                            values.end()
                        );

                        const float lower = values[middle - 1];

                        return (lower + upper) * 0.5f;
                    };


                    // 2. Read the nozzle angle and the median/mean blend weights.

                    const float nozzle_axe_angle =
                        curr_dtp_1->nozzle_axe_angle;


                    const float median_weight =
                        curr_dtp_3->median_weight;

                    const float mean_weight =
                        1.0f - median_weight;


                    // 3. Calculate each frame's blended main speed and angle.

                    
                    const std::vector<std::vector<single_track>>& tracks_frames =
                        curr_dtp_3->tracks_frames;

                    std::vector<float> frame_main_speeds;
                    std::vector<float> frame_main_angles;

                    frame_main_speeds.reserve(tracks_frames.size());
                    frame_main_angles.reserve(tracks_frames.size());

                    for (const std::vector<single_track>& frame_tracks : tracks_frames)
                    {
                        const float frame_blended_speed =
                            calculate_median(frame_tracks, true) * median_weight +
                            calculate_mean(frame_tracks, true) * mean_weight;

                        const float frame_blended_angle =
                            calculate_median(frame_tracks, false) * median_weight +
                            calculate_mean(frame_tracks, false) * mean_weight;

                        frame_main_speeds.push_back(frame_blended_speed);
                        frame_main_angles.push_back(
                            normalize_angle(frame_blended_angle - nozzle_axe_angle)
                        );
                    }


                    // 4. Compare consecutive frame values and blend their absolute deltas.
                    //    Angle deltas use the shortest path across the -180/180 boundary.
                   
                    std::vector<float> delta_speed;
                    std::vector<float> delta_angle;


                    if (tracks_frames.size() > 1)
                    {
                        delta_speed.reserve(tracks_frames.size() - 1);
                        delta_angle.reserve(tracks_frames.size() - 1);

                        for (size_t i = 0; i + 1 < tracks_frames.size(); ++i)
                        {
                            delta_speed.push_back(
                                std::abs(
                                    frame_main_speeds[i + 1] - frame_main_speeds[i]
                                )
                            );

                            delta_angle.push_back(
                                std::abs(
                                    normalize_angle(
                                        frame_main_angles[i + 1] - frame_main_angles[i]
                                    )
                                )
                            );
                        }
                    }

                    auto calculate_delta_median = [](const std::vector<float>& values) -> float
                    {
                        if (values.empty())
                            return 0.0f;

                        std::vector<float> sorted_values = values;
                        const size_t middle = sorted_values.size() / 2;

                        std::nth_element(
                            sorted_values.begin(),
                            sorted_values.begin() + middle,
                            sorted_values.end()
                        );

                        const float upper = sorted_values[middle];
                        if (sorted_values.size() % 2 != 0)
                            return upper;

                        std::nth_element(
                            sorted_values.begin(),
                            sorted_values.begin() + middle - 1,
                            sorted_values.end()
                        );

                        return (sorted_values[middle - 1] + upper) * 0.5f;
                    };


                    auto calculate_delta_blend =
                        [&](const std::vector<float>& values) -> float
                    {
                        if (values.empty())
                            return 0.0f;

                        const float sum =
                            std::accumulate(values.begin(), values.end(), 0.0f);
                        const float mean =
                            sum / static_cast<float>(values.size());
                        const float median = calculate_delta_median(values);

                        return median * median_weight + mean * mean_weight;
                    };


                    curr_dtp_3->frames_speed_delta =
                        calculate_delta_blend(delta_speed);


                    curr_dtp_3->frames_angle_delta =
                        calculate_delta_blend(delta_angle);


                    // 5. Calculate the blended main flow across all tracks.
                    std::vector<single_track>& tracks = curr_dtp_3->tracks;


                    // Nothing to calculate
                    if (tracks.empty())
                    {
                        curr_dtp_3->main_angle = 0.0f;
                        curr_dtp_3->main_speed = 0.0f;
                        curr_dtp_3->straight_speed = 0.0f;
                        curr_dtp_3->deviation_angle = 0.0f;
                        curr_dtp_3->deviation_speed = 0.0f;
                        curr_dtp_3->deviation_percentage = 0.0f;
                    }
                    else
                    {
                        // Calculate median and mean speed and angle for all tracks.

                        const float tracks_median_speed =
                            calculate_median(tracks, true);

                        const float tracks_mean_speed =
                            calculate_mean(tracks, true);


                        const float tracks_median_angle =
                            calculate_median(tracks, false);

                        const float tracks_mean_angle =
                            calculate_mean(tracks, false);


                        // Median + mean blend
                        const float blended_angle =
                            tracks_median_angle * median_weight +
                            tracks_mean_angle * mean_weight;


                        const float blended_speed =
                            tracks_median_speed * median_weight +
                            tracks_mean_speed * mean_weight;


                        // Main angle is expressed relative to the nozzle axis.
                        curr_dtp_3->main_angle = normalize_angle(blended_angle - nozzle_axe_angle);

                        curr_dtp_3->main_speed = blended_speed;


                        // 6. Determine the deviation boundary and classify each track.

                        const float minimal_deviation_angle = 10.0f;


                        const float deviation_angle_limit =
                            std::max(
                                minimal_deviation_angle,
                                std::abs(blended_angle) *
                                curr_dtp_3->deflection_percentage / 100.0f
                            );



                        curr_dtp_3->straight_tracks.clear();
                        curr_dtp_3->deviated_tracks.clear();

                        curr_dtp_3->straight_tracks.reserve(tracks.size());
                        curr_dtp_3->deviated_tracks.reserve(tracks.size());


                        for (const single_track& track : tracks)
                        {
                            const float angle_difference =
                                normalize_angle(
                                    track.angle - blended_angle
                                );

                            if (std::abs(angle_difference) >
                                deviation_angle_limit)
                            {
                                curr_dtp_3->deviated_tracks.push_back(track);
                            }
                            else
                            {
                                curr_dtp_3->straight_tracks.push_back(track);
                            }
                        }


                        // 7. Calculate blended speed for straight tracks.

                        const float straight_tracks_median_angle =
                            calculate_median(
                                curr_dtp_3->straight_tracks,
                                false
                            );

                        const float straight_tracks_mean_angle =
                            calculate_mean(
                                curr_dtp_3->straight_tracks,
                                false
                            );


                        const float straight_tracks_median_speed =
                            calculate_median(
                                curr_dtp_3->straight_tracks,
                                true
                            );

                        const float straight_tracks_mean_speed =
                            calculate_mean(
                                curr_dtp_3->straight_tracks,
                                true
                            );


                        // Straight speed
                        curr_dtp_3->straight_speed =
                            straight_tracks_median_speed * median_weight +
                            straight_tracks_mean_speed * mean_weight;


                        // 8. Calculate deviation angle, speed, and percentage.

                        const float deviated_tracks_median_angle =
                            calculate_median(
                                curr_dtp_3->deviated_tracks,
                                false
                            );

                        const float deviated_tracks_mean_angle =
                            calculate_mean(
                                curr_dtp_3->deviated_tracks,
                                false
                            );


                        const float deviated_tracks_median_speed =
                            calculate_median(
                                curr_dtp_3->deviated_tracks,
                                true
                            );

                        const float deviated_tracks_mean_speed =
                            calculate_mean(
                                curr_dtp_3->deviated_tracks,
                                true
                            );


                        if (!curr_dtp_3->deviated_tracks.empty())
                        {
                            const float deviated_blended_angle =
                                deviated_tracks_median_angle * median_weight +
                                deviated_tracks_mean_angle * mean_weight;


                            const float deviated_blended_speed =
                                deviated_tracks_median_speed * median_weight +
                                deviated_tracks_mean_speed * mean_weight;


                            // Deviation relative to the main flow direction.
                            curr_dtp_3->deviation_angle =
                                normalize_angle(
                                    deviated_blended_angle -
                                    blended_angle
                                );


                            curr_dtp_3->deviation_speed =
                                deviated_blended_speed;
                        }
                        else
                        {
                            curr_dtp_3->deviation_angle = 0.0f;
                            curr_dtp_3->deviation_speed = 0.0f;
                        }


                        curr_dtp_3->deviation_percentage =

                            static_cast<float>(curr_dtp_3->deviated_tracks.size()) /
                            static_cast<float>(tracks.size()) *
                            100.0f;

                            

                        // 9. Print the calculated Stage 3.2 results in test mode.
                        if (FPC_TEST_MODE)
                        {
                            std::cout << "\n";
                            std::cout << "========== STAGE 3.2 TRACK RESULTS ==========\n";

                            std::cout << "\n--- INPUT ---\n";
                            std::cout << "Nozzle axe angle: "
                                      << nozzle_axe_angle << " deg\n";

                            std::cout << "Median weight: "
                                      << median_weight << "\n";

                            std::cout << "Mean weight: "
                                      << mean_weight << "\n";


                            std::cout << "\n--- ALL TRACKS ---\n";
                            std::cout << "Tracks count: "
                                      << tracks.size() << "\n";

                            std::cout << "Median speed: "
                                      << tracks_median_speed << " m/s\n";

                            std::cout << "Mean speed: "
                                      << tracks_mean_speed << " m/s\n";

                            std::cout << "Median angle: "
                                      << tracks_median_angle << " deg\n";

                            std::cout << "Mean angle: "
                                      << tracks_mean_angle << " deg\n";


                            std::cout << "\n--- BLENDED MAIN FLOW ---\n";
                            std::cout << "Blended speed: "
                                      << blended_speed << " m/s\n";

                            std::cout << "Blended angle: "
                                      << blended_angle << " deg\n";

                            std::cout << "Main angle relative to nozzle: "
                                      << curr_dtp_3->main_angle << " deg\n";

                            std::cout << "Main speed: "
                                      << curr_dtp_3->main_speed << " m/s\n";

                            std::cout << "\n--- FRAME-TO-FRAME DELTAS ---\n";
                            std::cout << "Frames compared: "
                                      << delta_speed.size() << "\n";

                            std::cout << "Blended absolute main speed delta: "
                                      << curr_dtp_3->frames_speed_delta
                                      << " m/s\n";

                            std::cout << "Blended absolute main angle delta: "
                                      << curr_dtp_3->frames_angle_delta
                                      << " deg\n";


                            std::cout << "\n--- CLASSIFICATION ---\n";
                            std::cout << "Deflection percentage setting: "
                                      << curr_dtp_3->deflection_percentage
                                      << " %\n";

                            std::cout << "Deviation angle limit: "
                                      << deviation_angle_limit << " deg\n";

                            std::cout << "Straight tracks count: "
                                      << curr_dtp_3->straight_tracks.size()
                                      << "\n";

                            std::cout << "Deviated tracks count: "
                                      << curr_dtp_3->deviated_tracks.size()
                                      << "\n";


                            std::cout << "\n--- STRAIGHT TRACKS ---\n";
                            std::cout << "Median angle: "
                                      << straight_tracks_median_angle
                                      << " deg\n";

                            std::cout << "Mean angle: "
                                      << straight_tracks_mean_angle
                                      << " deg\n";

                            std::cout << "Median speed: "
                                      << straight_tracks_median_speed
                                      << " m/s\n";

                            std::cout << "Mean speed: "
                                      << straight_tracks_mean_speed
                                      << " m/s\n";

                            std::cout << "Straight speed: "
                                      << curr_dtp_3->straight_speed
                                      << " m/s\n";


                            std::cout << "\n--- DEVIATED TRACKS ---\n";
                            std::cout << "Median angle: "
                                      << deviated_tracks_median_angle
                                      << " deg\n";

                            std::cout << "Mean angle: "
                                      << deviated_tracks_mean_angle
                                      << " deg\n";

                            std::cout << "Median speed: "
                                      << deviated_tracks_median_speed
                                      << " m/s\n";

                            std::cout << "Mean speed: "
                                      << deviated_tracks_mean_speed
                                      << " m/s\n";

                            std::cout << "Deviation angle: "
                                      << curr_dtp_3->deviation_angle
                                      << " deg\n";

                            std::cout << "Deviation speed: "
                                      << curr_dtp_3->deviation_speed
                                      << " m/s\n";

                            std::cout << "Deviation percentage: "
                                      << curr_dtp_3->deviation_percentage
                                      << " %\n";


                            std::cout << "\n--- FINAL ANSWERS ---\n";
                            std::cout << "main_angle = "
                                      << curr_dtp_3->main_angle
                                      << " deg\n";

                            std::cout << "main_speed = "
                                      << curr_dtp_3->main_speed
                                      << " m/s\n";

                            std::cout << "straight_speed = "
                                      << curr_dtp_3->straight_speed
                                      << " m/s\n";

                            std::cout << "deviation_angle = "
                                      << curr_dtp_3->deviation_angle
                                      << " deg\n";

                            std::cout << "deviation_speed = "
                                      << curr_dtp_3->deviation_speed
                                      << " m/s\n";

                            std::cout << "deviation_percentage = "
                                      << curr_dtp_3->deviation_percentage
                                      << " %\n";

                            std::cout << "frames_speed_delta = "
                                      << curr_dtp_3->frames_speed_delta
                                      << " m/s\n";

                            std::cout << "frames_angle_delta = "
                                      << curr_dtp_3->frames_angle_delta
                                      << " deg\n";

                            std::cout << "\n==============================================\n";
                        }
                    }

                    // 10. Mark this video complete and reset the operation context.
                    //     The next update will select another video if one remains.
                    data_to_control->stage_2_end = true;

                    data_to_control->calculated_flag = true;


                    opencv_global_calculation_update_ctx.need_reset = true;

                    opencv_global_calculation_update_ctx.global_operation = PROCESSING_STAGE_1_CGO;

                    opencv_global_calculation_update_ctx.operation = MASK_1_PROCESSING_CO;


                    data_to_control = nullptr;
                }


                // Operations counter update
                state_progress_bar.operations_counter += 1;
            }

            // Update progress bar
            state_progress_bar.current_frame = opencv_global_calculation_update_ctx.current_frame_index;
        }
    }

    // ===== BLACKBOX WITH PROCESSING LOGIC BY CALLBACK =====


    

    // ===== SHOW SCALED COPY OF CURRENT MAT INSIDE OTHER WINDOW =====

    if (FPC_TEST_MODE)
    {
        static bool kingsize_live_transmission = false;

        static std::size_t mat_index = 0;

        static float last_mat_switch_time = App_timer_1.get_current_time();

        constexpr float MAT_SWITCH_INTERVAL = 3.0f;


        // ============================================================
        // SELECT MAT
        // ============================================================

        const float current_time = App_timer_1.get_current_time();


        if (current_time - last_mat_switch_time >= MAT_SWITCH_INTERVAL)
        {
            mat_index = (mat_index + 1) % 3;

            last_mat_switch_time = current_time;
        }

        if (opencv_global_calculation_update_ctx.global_operation == PROCESSING_STAGE_2_CGO) mat_index = 2;


        const std::array<cv::Mat*, 3> test_mats =
        {

            calculation_cv_mat_mask_1_global,
            calculation_cv_mat_mask_2_global,
            calculation_cv_mat_mask_3_global

        };


        cv::Mat* current_basic_mat_to_process = test_mats[mat_index];


        // ============================================================
        // SHOW MAT
        // ============================================================

        if (!current_basic_mat_to_process->empty())
        {
            if (!kingsize_live_transmission)
            {
                kingsize_window_init_fpc(
                    current_basic_mat_to_process
                );

                kingsize_live_transmission = true;
            }


            // USER INPUT ERROR HANDLER
            if (cv::getWindowProperty(
                    "KINGSIZE_TEST",
                    cv::WND_PROP_VISIBLE
                ) < 1)
            {
                kingsize_live_transmission = false;

                return;
            }


            cv::Mat kingsize_mat;

            cv::resize(
                *current_basic_mat_to_process,
                kingsize_mat,
                cv::Size(
                    current_basic_mat_to_process->cols * 3,
                    current_basic_mat_to_process->rows * 3
                ),
                0,
                0,
                cv::INTER_NEAREST
            );


            cv::imshow(
                "KINGSIZE_TEST",
                kingsize_mat
            );

            cv::waitKey(1);
        }
    }

    // ===== SHOW SCALED COPY OF CURRENT MAT INSIDE OTHER WINDOW =====

}



void opencv_calculation_global_free_and_nullptr()
{
    // 1. Clear mats

    if (calculation_cv_mat_mask_1_global != nullptr)
    {
        delete calculation_cv_mat_mask_1_global;

        calculation_cv_mat_mask_1_global = nullptr; 
    }

    if (calculation_cv_mat_mask_2_global != nullptr)
    {
        delete calculation_cv_mat_mask_2_global;

        calculation_cv_mat_mask_2_global = nullptr; 
    }

    if (calculation_cv_mat_mask_3_global != nullptr)
    {
        delete calculation_cv_mat_mask_3_global;

        calculation_cv_mat_mask_3_global = nullptr; 
    }


    // Activate reinit
    // TODO:??? Need or not?>
    opencv_calculation_pipeline_reset_global = false;
}


// ===== Functions =====

// =========================================================================================== OPENCV PART OF THE STATE


// =========================================================================================== PROCESSING FUNCTIONS


void processing_stage_1(cv::Mat* current_mat)
{
    // Расчёт производится на 1 кадре 


    // Mask analysis output data already found
    if (data_to_process_1->calculated) return;


    if (!current_mat || current_mat->empty()) return;

    // Mask processing logic


    // ===== MASK SETUP LOGIC =====

    nozzle_detection_mask* controlled_mask = &nozzle_mask_to_process;


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

    // Draw crosshair only in test case
    if (FPC_TEST_MODE)
    {

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


        draw_crosshair(*current_mat, controlled_mask->x_1, controlled_mask->y_1, cv::Scalar(0, 255, 0)); // Зеленый
        draw_crosshair(*current_mat, controlled_mask->x_2, controlled_mask->y_2, cv::Scalar(0, 0, 255)); // Красный
    }
    

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

    int cols = current_mat->cols;
    int rows = current_mat->rows;

    // Пересечение с левой границей (x = 0)
    if (std::abs(b_2) > epsilon) 
    {
        double y = -c_2 / b_2;

        if (y >= 0 && y < rows) edge_points.push_back(cv::Point(0, std::round(y)));

    }

    // Пересечение с правой границей (x = cols - 1)
    if (std::abs(b_2) > epsilon) 
    {
        double y = -(a_2 * (cols - 1) + c_2) / b_2;

        if (y >= 0 && y < rows) edge_points.push_back(cv::Point(cols - 1, std::round(y)));

    }

    // Пересечение с верхней границей (y = 0)
    if (std::abs(a_2) > epsilon) 
    {
        double x = -c_2 / a_2;

        if (x >= 0 && x < cols) edge_points.push_back(cv::Point(std::round(x), 0));
    }

    // Пересечение с нижней границей (y = rows - 1)
    if (std::abs(a_2) > epsilon) 
    {
        double x = -(b_2 * (rows - 1) + c_2) / a_2;

        if (x >= 0 && x < cols) edge_points.push_back(cv::Point(std::round(x), rows - 1));

    }


    // === 4th step === 

    if (edge_points.size() >= 2) 
    {
        // Берем первые две найденные точки пересечения с границами

        cv::Point p_start = edge_points[0];
        cv::Point p_end = edge_points[1];

        // Инициализируем итератор линии (8-связность для непрерывного прохода)
        cv::LineIterator line_it(*current_mat, p_start, p_end, 8);
        
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
                cv::circle(*current_mat, line_it.pos(), 1, cv::Scalar(255, 0, 0), -1);
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
    int top_x_scale = current_mat->cols - scale_size.width - 10;
    int top_y_scale = scale_size.height + 10; 

    cv::putText(

        *current_mat,
        scale_str,
        cv::Point(top_x_scale, top_y_scale),
        font_face,
        text_scale,
        yellow_color,
        text_thickness,
        cv::LINE_AA

    );

    // Координаты для 2-й строки (Угол): встает строго под первой строкой с учетом базовой линии
    int top_x_angle = current_mat->cols - angle_size.width - 10;
    int top_y_angle = top_y_scale + angle_size.height + text_baseline + 8; // 8 пикселей — аккуратный межстрочный интервал

    cv::putText(

        *current_mat,
        angle_str,
        cv::Point(top_x_angle, top_y_angle),
        font_face,
        text_scale,
        yellow_color,
        text_thickness,
        cv::LINE_AA

    );


    // Просто повторное присвоение c блокировкой пересчёта

    data_to_process_1->scale = controlled_mask->mm_in_pixel;                            // Масштаб на видео
    
    data_to_process_1->nozzle_axe.a = controlled_mask->axe_line_coefficients.a;         // Осевая линия на видео
    data_to_process_1->nozzle_axe.b = controlled_mask->axe_line_coefficients.b;         // Осевая линия на видео
    data_to_process_1->nozzle_axe.c = controlled_mask->axe_line_coefficients.c;         // Осевая линия на видео

    data_to_process_1->nozzle_axe_angle = controlled_mask->basic_axe_angle;             // Угол оси сопла на видео

    data_to_process_1->calculated = true;                                               // Блокировка перерасчёта
    
    // ===== MASK MAIN CALCULATED VALUES ===== 

    // ===== MASK SETUP LOGIC =====
}



void processing_stage_2(cv::Mat* current_mat)
{
    if (!current_mat || current_mat->empty())
        return;


    // =======================================================================================
    // GET CONTROLLED MASK

    // Get current jet mask settings.
    //
    // This context contains the HSV boundaries selected by the user
    // or loaded from a preset.

    jet_detection_mask* controlled_mask = &jet_mask_to_process;

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

    // Convert the source current_mat from BGR to HSV.
    //
    // HSV allows us to independently control:
    //
    //      H = Hue
    //      S = Saturation
    //      V = Value

    cv::Mat image_hsv;

    cv::cvtColor(
        *current_mat,
        image_hsv,
        cv::COLOR_BGR2HSV
    );



    // ===== PRECALCULATION =====

    float current_scale = data_to_process_1->scale;

    unsigned int video_width = video_data.width;
    unsigned int video_height = video_data.height;

    // ===== PRECALCULATION =====


    // ===== Light power calculation =====


    // Используем cv::Vec3b для быстрого и безопасного доступа к пикселям.
    // Рекомендуется обходить матрицу: внешний цикл по строкам (Y), внутренний по столбцам (X)
    // для оптимального использования кэша процессора.
    
    // Unsigned char занимает ровно 1 байт памяти и может хранить числа строго от 0 до 255.
    std::vector<unsigned char> pixels_light_power_values;
    pixels_light_power_values.reserve(current_mat->rows * current_mat->cols);

    for (int y = 0; y < current_mat->rows; ++y)
    {
        for (int x = 0; x < current_mat->cols; ++x)
        {
            // В OpenCV HSV-пиксель упорядочен как: [0]=H, [1]=S, [2]=V
            unsigned char v_val = image_hsv.at<cv::Vec3b>(y, x)[2];
            pixels_light_power_values.push_back(v_val);
        }
    }

    // Вычисляем сумму элементов через std::accumulate. 
    // Используем 0ULL (unsigned long long), чтобы гарантированно избежать переполнения.
    size_t v_size = pixels_light_power_values.size();

    float total_sum = std::accumulate(

        pixels_light_power_values.begin(), 
        pixels_light_power_values.end(),
         0.0f
        
    );

    // Вычисляем среднее арифметическое (значение от 0.0 до 255.0)
    // Делаем проверку на v_size > 0, чтобы избежать деления на ноль, если матрица пустая
    float mean_v_raw = v_size > 0 ? static_cast<float>(total_sum) / v_size : 0.0f;

    // Переводим в проценты (от 0.0 до 100.0%)
    float frame_mean_light_power_percentage = (mean_v_raw / 255.0f) * 100.0f;

    // Запись в общий буфер видео
    data_to_process_2->frames_mean_light_power_percentage.push_back(frame_mean_light_power_percentage);
    // ===== Light power calculation =====




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



    // ===== Median jet amplitude calculation =====

    // Настройки фильтрации
    const int MIN_SEGMENT_LENGTH = 25;          // Минимальная длина струи в пикселях
    const int MAX_GAP_ALLOWED = 25;             // Сколько черных пикселей подряд можно "простить" внутри струи

    // Вектор для хранения амплитуды (высоты) струи для каждого столбца X.
    // Инициализируем нулями, размер равен ширине маски.
    std::vector<int> frame_median_jet_amplitude(image_mask.cols, 0);

    // Проходим по каждому столбцу X (слева направо)
    for (int x = 0; x < image_mask.cols; ++x) 
    {
        int max_segment_length = 0;             // Самая длинная непрерывная струя в этом столбце
        int current_segment_length = 0;         // Длина текущего проверяемого участка
        int current_gap = 0;                    // Счетчик идущих подряд черных пикселей внутри струи

        // Сканируем снизу вверх (от сопла/земли к вершине кадра)
        for (int y = image_mask.rows - 1; y >= 0; --y)
        {
            uchar pixel_value = image_mask.at<uchar>(y, x);

            if (pixel_value == 255)
            {
                // Если встретили белый пиксель:
                // Если до этого была небольшая "дыра", прибавляем её к общей длине
                if (current_gap > 0) 
                {
                    current_segment_length += current_gap;
                    current_gap = 0;
                }

                current_segment_length++;
            } 
            else 
            {
                // Если встретили черный пиксель:
                if (current_segment_length > 0) 
                {
                    // Мы уже находимся внутри струи. Начинаем считать длину "дыры"
                    current_gap++;

                    // Если дыра стала слишком большой — это честный разрыв струи
                    if (current_gap > MAX_GAP_ALLOWED)
                    {
                        // Проверяем, подходит ли завершившийся сегмент под условия
                        if (current_segment_length >= MIN_SEGMENT_LENGTH &&
                            current_segment_length > max_segment_length) 
                        {
                            max_segment_length = current_segment_length;
                        }

                        // Сбрасываем все счетчики для поиска следующего кандидата выше
                        current_segment_length = 0;
                        current_gap = 0;
                    }
                }
            }
        }

        // Финальная проверка после выхода из цикла по Y (если струя уперлась в самый верхний край кадра)
        if (current_segment_length >= MIN_SEGMENT_LENGTH && current_segment_length > max_segment_length) 
        {
            max_segment_length = current_segment_length;
        }

        // Сохраняем итоговую амплитуду для текущей координаты X
        frame_median_jet_amplitude[x] = max_segment_length;
    }


    // Собираем только те столбцы, где струя РЕАЛЬНО была обнаружена (> 0)
    std::vector<int> valid_amplitudes;

    valid_amplitudes.reserve(frame_median_jet_amplitude.size());

    for (int amp : frame_median_jet_amplitude) 
    {
        if (amp > 0) 
        {
            valid_amplitudes.push_back(amp);
        }
    }

    float frame_jet_amplitude_median_mm = 0.0f;


    // Считаем медиану только если нашли струю хотя бы в одном столбце
    if (!valid_amplitudes.empty()) 
    {

            // ===== Mean-calculation zone =====

            float frame_jet_amplitude_mean_mm = 0.0f;

            float amplitude_sum = std::accumulate(
                valid_amplitudes.begin(),
                valid_amplitudes.end(),
                0.0f
            );


            frame_jet_amplitude_mean_mm =
                (amplitude_sum / static_cast<float>(valid_amplitudes.size()))
                * current_scale;
            

            data_to_process_2->frames_mean_jet_amplitude.push_back(
                frame_jet_amplitude_mean_mm
            );

            // ===== Mean-calculation zone =====



        size_t jet_mid_index = valid_amplitudes.size() / 2;

        std::nth_element(

            valid_amplitudes.begin(), 
            valid_amplitudes.begin() + jet_mid_index, 
            valid_amplitudes.end()

        );
        
        int jet_median_px = valid_amplitudes[jet_mid_index];

        // Переводим в мм
        frame_jet_amplitude_median_mm = static_cast<float>(jet_median_px) * current_scale;
    }

    // Запись в общий буфер видео
    data_to_process_2->frames_median_jet_amplitude.push_back(frame_jet_amplitude_median_mm);

    // ===== Median jet anplitude calculation =====




    // =======================================================================================
    // CREATE BINARY MASK


    // =======================================================================================
    // MASK -> BGR

    // image_mask is CV_8UC1.
    //
    // The rest of the current rendering pipeline expects the current_mat
    // to remain a 3-channel BGR image.
    //
    // Therefore convert the binary mask back to BGR before writing it
    // into the main current_mat.
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
    // WRITE RESULT BACK TO current_mat

    // Replace the current current_mat with the processed jet mask.
    //
    // IMPORTANT:
    // current_mat remains CV_8UC3 BGR, so the next processing stage
    // and the OpenCV -> SDL translation can continue working
    // with the same image format.

    image_mask_bgr.copyTo(*current_mat);

    // =======================================================================================
    // WRITE RESULT BACK TO FRAME


}



void processing_stage_3_1(cv::Mat* current_mat)
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
                          │
                          ▼
              ┌───────────────────────┐
              │ Color Filter          │
              │                       │
              │ H/S/V min/max         │
              └───────────┬───────────┘
                          │
                          ▼
                    FIRST MASK
                          │
                          │
                    ──────┼────── 
                NEXT STEPS ARE INACTIVE IF 
    masks_data.CURR_FILE_MASKS.particle_mask.controlled_submask != SUBMASK_2_CSM3
                SO IF IT's SUBMASK_1_CSM3 we translate FIRST SUBMASK and stop processing
                IT IT's SUBMASK_2_CSM3 we continue processing and apply the next steps
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

    if (!current_mat || current_mat->empty()) return;

        
    // =======================================================================================
    // GET CONTROLLED MASK
    // =======================================================================================


    // Get current particle mask settings.

    particle_detection_mask* controlled_mask = &particle_mask_to_process;


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
    // BGR -> HSV

    // Convert the source current_mat from BGR to HSV with coloring.
    //
    // HSV allows us to independently control:
    //
    //      H = Hue
    //      S = Saturation
    //      V = Value

    cv::Mat image_hsv;

    cv::cvtColor(
        *current_mat,
        image_hsv,
        cv::COLOR_BGR2HSV
    );


    // =======================================================================================
    // LIGHT GAUSSIAN BLUR - could be deactivated

    // Apply a very small blur to suppress small pixel-to-pixel
    // fluctuations around the particles boundary.
    //
    // 0x0 means that blur is disabled.
    // 1x1 / 3x3 are valid blur sizes.

    bool do_blur = !(controlled_mask->b_h == 0 || controlled_mask->b_v == 0);

    if (do_blur)
    {
        cv::GaussianBlur(
            image_hsv,
            image_hsv,
            cv::Size(
                controlled_mask->b_h,
                controlled_mask->b_v
            ),
            0
        );
    }


    // =======================================================================================
    // CREATE COLOR RANGE

    cv::Mat first_mask;

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

    cv::inRange(
        image_hsv,
        lower_color,
        upper_color,
        first_mask
    );


    // =======================================================================================
    // DESIDE SHOW OR CONTINUE TO PROCESSING

    // We work with 2nd part of the mask, so it's always true
    bool to_proc = true;


    // Temporary container for the frame points, 
    // which will be passed inside frames_points container inside processing_3_data
    // for current file by data_to_process_3 pass-variable
    std::vector<desc_c_2D> current_frame_points;
    

    if (to_proc)
    {
        /*
            На этом этапе FIRST MASK уже содержит результат HSV-фильтрации.

            То есть:

                ORIGINAL IMAGE
                    │
                    ▼
                BGR -> HSV
                    │
                    ▼
                optional BLUR
                    │
                    ▼
                HSV inRange
                    │
                    ▼
                FIRST MASK
                    │
                    │
                    │  ЧЁРНО-БЕЛОЕ ИЗОБРАЖЕНИЕ:
                    │
                    │  WHITE (255) = пиксель прошёл HSV-фильтр
                    │  BLACK (0)   = пиксель не прошёл HSV-фильтр
                    │
                    ▼
                CANNY -> DILATE -> CONTOURS
                    │
                    ▼
                AREA / LENGTH
                    │
                    ▼
                  ERODE
                    │
                    ▼
                FINAL MASK

            Поэтому все следующие операции работают уже НЕ с исходным
            цветным изображением, а только с областями, которые были
            предварительно выделены HSV-фильтром.
        */


        // =======================================================================================
        // CANNY EDGE DETECTION
        //
        // INPUT:
        //
        //     first_mask
        //
        //     Это бинарная маска после HSV-фильтрации.
        //
        //     WHITE = нужный цвет / область
        //     BLACK = всё остальное
        //
        //
        // Что делает Canny:
        //
        //     Canny ищет границы (edges) внутри этой бинарной маски.
        //
        //     В результате вместо самой области мы получаем в основном
        //     её границы.
        //
        //
        // OUTPUT:
        //
        //     canny_mask
        //
        //     Это новая бинарная маска, где:
        //
        //     WHITE = найденная граница
        //     BLACK = отсутствие границы
        //
        //     https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcQbLUmt-YA19XxyVH8QtIEFEu8fRLbSSSlO--yMj9Rz_g&s
        //
        //     То есть данные проходят так:
        //
        //         FIRST MASK
        //             │
        //             │ HSV-selected regions
        //             ▼
        //           CANNY
        //             │
        //             │ edges of selected regions
        //             ▼
        //         CANNY MASK


        cv::Mat canny_mask;

        cv::Canny(

            first_mask,
            canny_mask,
            controlled_mask->canny_low,
            controlled_mask->canny_high

        );


        // =======================================================================================
        // DILATE
        //
        // INPUT:
        //
        //     canny_mask
        //
        //     Это результат Canny, то есть тонкие линии/границы,
        //     найденные внутри HSV-маски.
        //
        //
        // WHAT DILATE DOES:
        //
        //     Dilate расширяет белые области изображения.
        //
        //     Для нашего случая это нужно для того, чтобы:
        //
        //     1. сделать найденные Canny-границы толще;
        //     2. соединить близко расположенные участки границы;
        //     3. уменьшить вероятность того, что одна траектория
        //        будет разбита на несколько отдельных частей.
        //
        //
        //     Размер kernel определяет, насколько сильно расширяется
        //     белая область за одну итерацию.
        //
        //     Количество iterations определяет, сколько раз выполняется
        //     операция расширения.
        //
        //
        // OUTPUT:
        //
        //     dilated_mask
        //
        //     Это всё ещё бинарная маска.
        //
        //     Но теперь Canny-линии становятся толще и/или соединяются.
        //     
        //     https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcS_yfLnZ1NkpUn-dMEWJHbk6fGtTYYy6_bGfxPiF0iuK5tbP_UUy5wRAE19&s=10
        //
        //     То есть:
        //
        //         CANNY MASK
        //             │
        //             │ thin edges
        //             ▼
        //           DILATE
        //             │
        //             │ thicker / connected edges
        //             ▼
        //         DILATED MASK


        cv::Mat dilated_mask;

        cv::Mat dilate_kernel = cv::getStructuringElement(
            cv::MORPH_RECT,
            cv::Size(

                controlled_mask->dilate_size,
                controlled_mask->dilate_size
                
            )
        );

        cv::dilate(
            canny_mask,
            dilated_mask,
            dilate_kernel,
            cv::Point(-1, -1),
            controlled_mask->dilate_iterations
        );


        // =======================================================================================
        // FIND CONTOURS
        //
        // INPUT:
        //
        //     dilated_mask
        //
        //     На этом этапе у нас уже есть подготовленная бинарная маска
        //     с расширенными Canny-границами.
        //
        //
        // WHAT FINDCONTOURS DOES:
        //
        //     findContours ищет связанные между собой белые области
        //     и превращает каждую найденную область в набор точек.
        //
        //     Каждая такая последовательность точек называется contour.
        //
        //
        //     Например:
        //
        //         DILATED MASK
        //
        //             ███
        //               ███
        //                  ██
        //
        //     становится примерно:
        //
        //         contour = [P1, P2, P3, P4, ...]
        //
        //
        // RETR_EXTERNAL:
        //
        //     Нас интересуют только внешние контуры.
        //     Вложенные внутренние контуры не собираются.
        //
        //
        // CHAIN_APPROX_NONE:
        //
        //     Сохраняет все точки контура без дополнительного
        //     упрощения последовательности.
        //
        //     Это важно для последующего измерения геометрии
        //     траектории.
        //
        //
        // OUTPUT:
        //
        //     contours
        //
        //     vector всех найденных контуров.
        //
        //     Каждый contour содержит набор cv::Point.
        //
        //
        //     То есть:
        //
        //         DILATED MASK
        //             │
        //             │ connected white regions
        //             ▼
        //       FIND CONTOURS
        //             │
        //             │ vector<vector<Point>>
        //             ▼
        //          CONTOURS


        std::vector<std::vector<cv::Point>> contours;

        cv::findContours(
            dilated_mask,
            contours,
            cv::RETR_EXTERNAL,
            cv::CHAIN_APPROX_NONE
        );


        // =======================================================================================
        // AREA / LENGTH FILTERING
        //
        // Здесь мы уже работаем не с изображением напрямую,
        // а с отдельными найденными CONTOURS.
        //
        //
        // INPUT:
        //
        //     contours
        //
        //     Каждый contour представляет одну отдельную найденную
        //     связанную область/траекторию.
        //
        //
        // Задача этого этапа:
        //
        //     определить, какие из найденных контуров действительно
        //     подходят под параметры particle trajectory.
        //
        //
        // Для этого каждый contour проверяется по двум независимым
        // геометрическим характеристикам:
        //
        //     1. AREA   = площадь контура
        //     2. LENGTH = длина контура
        //
        //
        // Если contour не проходит хотя бы один из фильтров,
        // он полностью отбрасывается.
        //
        //
        // Если contour проходит оба фильтра,
        // он переносится в FINAL MASK.
        //
        //
        //     CONTOURS
        //        │
        //        ├── contour #1 -> AREA -> LENGTH -> ACCEPT
        //        │
        //        ├── contour #2 -> AREA -> REJECT
        //        │
        //        ├── contour #3 -> AREA -> LENGTH -> ACCEPT
        //        │
        //        └── contour #4 -> LENGTH -> REJECT
        //        │
        //        ▼
        //     FINAL MASK
        //
        //
        // Создаём пустую маску того же размера,
        // что и предыдущий этап.
        //
        // В неё попадут ТОЛЬКО принятые контуры.
        //
        // BLACK = contour не прошёл фильтрацию
        // WHITE = contour принят


        // Final mask init 

        cv::Mat final_mask = cv::Mat::zeros(
            dilated_mask.size(),
            CV_8UC1
        );


        for (const auto& contour : contours)
        {
            // -------------------------------------------------------------------------------
            // AREA
            //
            // INPUT:
            //
            //     contour
            //
            //     Один конкретный contour из общего списка contours.
            //
            //
            // WHAT:
            //
            //     contourArea вычисляет площадь области,
            //     ограниченной данным contour.
            //
            //
            // Это позволяет отсечь:
            //
            //     слишком маленькие объекты / шум
            //     слишком большие области, которые не могут быть
            //     нужной частицей или траекторией.
            //
            //
            // Если площадь находится вне допустимого диапазона,
            // contour сразу отбрасывается.
            //
            //
            //     contour
            //        │
            //        ▼
            //     AREA CHECK
            //        │
            //        ├── too small -> REJECT
            //        │
            //        ├── too large -> REJECT
            //        │
            //        └── valid     -> NEXT CHECK (LENGTH)


            double contour_area = cv::contourArea(
                contour
            );

            if (
                contour_area < controlled_mask->area_min ||
                contour_area > controlled_mask->area_max
            )
            {
                continue;
            }


            // -------------------------------------------------------------------------------
            // LENGTH
            //
            // INPUT:
            //
            //     Тот же contour, но только если он уже прошёл
            //     проверку AREA.
            //
            //
            // WHAT:
            //
            //     arcLength вычисляет длину контура.
            //
            //     false означает, что контур рассматривается
            //     как незамкнутый при вычислении длины.
            //
            //
            // Это позволяет дополнительно отсечь:
            //
            //     слишком короткие контуры
            //     слишком длинные контуры
            //
            // Например, маленький случайный объект может иметь
            // подходящую площадь, но при этом иметь недостаточную
            // длину для реальной траектории.
            //
            //
            // Поэтому AREA и LENGTH работают вместе:
            //
            //     AREA  отвечает за размер области
            //     LENGTH отвечает за протяжённость контура
            //
            //
            //     contour
            //        │
            //        ▼
            //     LENGTH CHECK
            //        │
            //        ├── too short -> REJECT
            //        │
            //        ├── too long  -> REJECT
            //        │
            //        └── valid     -> ACCEPT


            double contour_length = cv::arcLength(
                contour,
                false
            );

            if (
                contour_length < controlled_mask->length_min ||
                contour_length > controlled_mask->length_max
            )
            {
                continue;
            }



            // ===== 1.1. Описываем вокруг контура строгий геометрический прямоугольник =====

            cv::Rect rect = cv::boundingRect(contour);

            // Считаем площадь этого прямоугольника
            double rect_area = static_cast<double>(rect.width * rect.height);
            
            // Вычисляем плотность заполнения (Solidity)
            double solidity = rect_area > 0.0 ? contour_area / rect_area : 0.0;

            // ===== 1.2. ФИЛЬТР КЛЯКС: Если контур сплошной и плотный (solidity > 0.65) — ПРОПУСКАЕМ ЕГО.
            // Также страхуемся от аномально огромных конгломератов по габаритам (> 45 пикселей). =====

            if (solidity > 0.65 || rect.width > 45 || rect.height > 45)
            {
                continue; // "Убираем" заполненное пятно, переходя к следующему контуру
            }

            
            // ===== 1.3. Вычисляем точные координаты геометрического центра этой рамки =====

            // ЕСЛИ ОБЪЕКТ ПРОШЕЛ ВСЕ ФИЛЬТРЫ — ОН ПОЛЫЙ И ПРАВИЛЬНЫЙ

            desc_c_2D point;

            point.x = rect.x + rect.width / 2;
            point.y = rect.y + rect.height / 2;
            

            // Закидываем точку в контейнер текущего кадра
            current_frame_points.push_back(point);


            // -------------------------------------------------------------------------------
            // ACCEPT CONTOUR
            //
            // Если выполнение дошло сюда, contour успешно прошёл:
            //
            //     1. AREA filter
            //     2. LENGTH filter
            //
            //
            // Теперь этот contour считается подходящим.
            //
            // Мы переносим его в final_mask.
            //
            //
            // Важно:
            //
            //     final_mask изначально полностью BLACK.
            //
            //     Поэтому сюда попадают только те контуры,
            //     которые были явно приняты фильтрами.
            //
            //
            // FILLED означает, что внутренняя область контура
            // также заполняется белым цветом.
            //
            //
            //     ACCEPTED CONTOUR
            //           │
            //           ▼
            //      DRAW TO MASK
            //           │
            //           ▼
            //       FINAL MASK
            //
            //     WHITE = accepted trajectory
            //     BLACK = everything rejected


            // Fill final mask by founded countours 
            
            cv::drawContours(
                final_mask,
                std::vector{ contour },
                -1,
                cv::Scalar(255),
                cv::FILLED
            );

        }


        // =======================================================================================
        // REPLACE FIRST MASK
        //
        // До этого момента first_mask содержал результат ТОЛЬКО HSV-фильтрации.
        //
        //
        // Но поскольку controlled_submask == SUBMASK_2_CSM3,
        // мы прошли дополнительную цепочку:
        //
        //     FIRST MASK
        //         ↓
        //       CANNY
        //         ↓
        //       DILATE
        //         ↓
        //     CONTOURS
        //         ↓
        //     AREA FILTER
        //         ↓
        //     LENGTH FILTER
        //         ↓
        //   POINTS DETECTION
        //         ↓
        //   POINTS PASS
        //         ↓
        //     FINAL MASK
        //


        // ===== 1.4. Cохраняем весь набор в глобальный архив видео =====

        // frame_points — это std::vector<std::vector<desc_c_2D>>

        data_to_process_3->frames_points.push_back(current_frame_points);

        first_mask = final_mask;

    }   // if (to_proc) { } ... }



    // =======================================================================================
    // TRANSLATE BACK TO BGR AND SHOW

    cv::Mat final_mask_bgr;

    cv::cvtColor(

        first_mask,
        final_mask_bgr,
        cv::COLOR_GRAY2BGR

    );



    if (FPC_TEST_MODE)
    {
        // ===== 1.5. Добавляем отрисовку найденного центра (точки) =====


        // cv::Scalar(0, 0, 255) — это чистый КРАСНЫЙ цвет в OpenCV (палитра BGR)
        // 3 — радиус точки в пикселях (можно поставить 2, если покажется крупной)
        // -1 — заполнить точку целиком

        for (const auto& point : current_frame_points)
        {
            // cv::Scalar(0, 0, 255) — это чистый КРАСНЫЙ цвет в OpenCV (палитра BGR)
            // 3 — радиус точки в пикселях (можно поставить 2, если покажется крупной)
            // -1 — заполнить точку целиком
            cv::circle(
                final_mask_bgr,
                cv::Point(point.x, point.y),
                1,
                cv::Scalar(0, 0, 255),
                -1
            );
        }
    }

    final_mask_bgr.copyTo(*current_mat);
}


// ===== Stage 3.2 helpers =====

// Analysis of all pairs
void analyse_pairs(

    /**
     * @brief Output 2D analysis grid storing comparison contexts for every possible point combination.
     * Passed by non-const reference because the function directly populates each cell's 
     * tracking metadata and calculated target_compare_result scores.
     */
    std::vector<std::vector<pair_analysis_ctx>>& passed_analysis_matrix,

    /**
     * @brief Read-only list of 2D source points from the previous frame (Frame N).
     * Passed by const-reference to efficiently read coordinates [x, y] without overhead.
     */
    const std::vector<desc_c_2D>& passed_frame_n_points, 

    /**
     * @brief Read-only list of 2D destination points from the current frame (Frame N+1).
     * Passed by const-reference to read destination coordinates [x, y] for delta calculations.
     */
    const std::vector<desc_c_2D>& passed_frame_n_plus_points, 

    /**
     * @brief The expected baseline pixel displacement along the X-axis between frames.
     * Used as the target reference value to evaluate tracking error on the horizontal axis.
     */
    float passed_t_dx, 

    /**
     * @brief The expected baseline pixel displacement along the Y-axis between frames.
     * Used as the target reference value to evaluate tracking error on the vertical axis.
     */
    float passed_t_dy

)
{

    // Fill the passed_analysis_matrix by the results of frames points comparation
    // and left the approved flag as false


    /**
     * @brief Pairwise Feature Analysis and Proximity Matrix Generation
     * 
     * This function evaluates all possible pairings between points in Frame N and Frame N+1.
     * It computes a similarity score for each combination based on spatial constraints 
     * and predicted frame displacement (deltas), populating a 2D analysis matrix.
     * 
     * @algorithm_flow
     * 
     * 1. MATRIX POPULATION GRID:
     *    - Executes a nested loop over all points 'i' in Frame N and points 'j' in Frame N+1,
     *      ensuring an exhaustive O(N * M) cross-comparison.
     * 
     * 2. HARD SPATIAL CONSTRAINTS (Early Rejection):
     *    - Evaluates physical constraints before calculating complex scores.
     *    - If a point moves backward or remains completely stagnant along the X-axis (curr_dx <= 0),
     *      the combination is immediately invalidated by setting the score to 0.0.
     * 
     * 3. GAUSSIAN EXPONENTIAL ERROR DECAY:
     *    - Calculates absolute pixel displacement errors relative to expected tracking deltas (passed_t_dx, passed_t_dy).
     *    - Transforms these raw pixel errors into normalized similarity scores (0.0 to 1.0) using exponential decay.
     *    - Perfect tracking alignment yields a score of 1.0, while increasing displacement errors cause the score to decay toward 0.0.
     * 
     * 4. BLENDED PROPORTIONAL SCORING:
     *    - Combines the separate X and Y proximity scores into a single final metric using weighted blending proportions.
     *    - In the current configuration, Y-axis displacement accuracy has double the influence (1.0 weight) 
     *      compared to X-axis accuracy (0.5 weight) during score evaluation.
     */



    // ===== !!! ATTENTION !!! =====

    // Blend proportions!

    float dx_blend_part = 0.5;
    float dy_blend_part = 1.0 - dx_blend_part; 

    // ===== !!! ATTENTION !!! =====


    unsigned int f_n_size = passed_frame_n_points.size(); 
    unsigned int f_n_p_size = passed_frame_n_plus_points.size();


    float scale = data_to_process_1->scale;


    // Matrix fill 
    for (unsigned int i = 0; i < f_n_size; i++)
    {
        for (unsigned int j = 0; j < f_n_p_size; j++)
        {
            // ===== Fill the indexes =====

            passed_analysis_matrix[i][j].n_number = i;
            passed_analysis_matrix[i][j].n_plus_number = j;


            // ===== Calculate the target_compare_result =====

            float curr_target_compare_res = 0.0;

            bool compare_end = false;


            while (!compare_end)
            {

                int x_n = passed_frame_n_points[i].x;
                int y_n = passed_frame_n_points[i].y;

                int x_n_p = passed_frame_n_plus_points[j].x;
                int y_n_p = passed_frame_n_plus_points[j].y;

                
                // Deltas in mm
                float curr_dx = (x_n_p - x_n) * scale;                   // Need to know direction on compare
                float curr_dy = std::abs(y_n_p - y_n) * scale;           // Don't need to know direction on compare 

                // Can't go back or stay on previous position 
                if (curr_dx <= 0) 
                {
                    compare_end = true;

                    curr_target_compare_res = 0.0;

                    // End while and fill result
                    continue;
                }


                // Compare with passed deltas with blend proportions of results

                // 1. Count errors

                float error_x = std::fabs(curr_dx - passed_t_dx);
                float error_y = std::fabs(curr_dy - passed_t_dy);


                // 2. Calculate the Proximity Score (Range: 0.0 to 1.0)

                // We use an exponential decay (Gaussian-like function) to convert absolute pixel error 
                // into a similarity score.
                //
                // Math logic:
                // - If error is 0 (perfect match) -> std::exp(0) results in 1.0.
                // - As error grows, std::exp(-error) smoothly decays toward 0.0.
                // - The denominator (5.0f) controls the filtering stiffness (sensitivity tolerance):
                //   A smaller value makes it strict (sharp drop), a larger value allows a wider error window.

                const float score_scale_mm = 5.0f * scale;

                float score_x = std::exp(-error_x / score_scale_mm); 
                float score_y = std::exp(-error_y / score_scale_mm);


                // 3. Blend with coefficients

                curr_target_compare_res = (score_x * dx_blend_part) + (score_y * dy_blend_part);


                // 4. Exit

                compare_end = true;

            }

            // ===== Fill the target_compare_result =====

            passed_analysis_matrix[i][j].target_compare_result = curr_target_compare_res;

        }
    }
}



// Recursive pairs search and illimination stages by target_compare_result obtained at analyse_pairs stage
void find_pairs(

    /**
     * @brief A 2D matrix containing pre-calculated similarity scores between points.
     * Passed by const-reference to prevent expensive copying of the 2D grid.
     * Accessing `matrix[i][j]` provides the comparison data between point 'i' (Frame N) and point 'j' (Frame N+1).
     */
    const std::vector<std::vector<pair_analysis_ctx>>& passed_analysis_matrix,


    /**
     * @brief Output container that stores the final, validated pairs of matched points.
     * Passed by non-const reference because the function directly appends (push_back) 
     * the confirmed pairs into this external vector.
     */
    std::vector<std::array<desc_c_2D, 2>>& passed_frame_pairs,

    /**
     * @brief Read-only list of all 2D point descriptors from the previous frame (Frame N).
     * Passed by const-reference for performance. Used to read spatial coordinates (like .y) 
     * and to pull the original points when writing winners to the output container.
     */
    const std::vector<desc_c_2D>& passed_frame_n_points,

    /**
     * @brief Read-only list of all 2D point descriptors from the current frame (Frame N+1).
     * Passed by const-reference for performance. Used for target destination coordinates 
     * and to resolve conflicts based on movement direction.
     */
    const std::vector<desc_c_2D>& passed_frame_n_plus_points

)
{
    /**
     * 
     * @brief Iterative Greedy Matching Algorithm with Conflict Resolution
     * 
     * This function matches point features between two consecutive frames (Frame N and Frame N+1)
     * using an analysis matrix (similarity scores) and vertical movement constraints.
     * 
     * @algorithm_flow
     * 
     * 1. INITIALIZATION:
     *    - Populate two index pools ('remainder_n' and 'remainder_n_plus') with all available points.
     *    - These pools represent the tracking "search space" and act as elimination zones.
     *    - Set the quality threshold ('min_score_threshold = 0.5f') to ignore weak matches.
     * 
     * 2. THE MAIN ITERATIVE LOOP (while global_pair_found):
     *    - Reset the loop control flag ('global_pair_found = false') and clear the temporary match board.
     * 
     * 3. GREEDY CANDIDATE SELECTION:
     *    - For each currently unmatched point 'i' in Frame N, scan all remaining unmatched points 'j' in Frame N+1.
     *    - Find the single best candidate 'best_j' that yields the highest similarity score ('max_score').
     *    - If 'max_score' passes the 50% threshold, point 'i' attempts to claim 'best_j'.
     * 
     * 4. CASCADE CONFLICT RESOLUTION (Arena Phase):
     *    - Since multiple points from Frame N can select the same target 'best_j', conflicts are evaluated:
     *      - Priority 1 (Similarity): If the new candidate has a strictly higher score than the previous match, 
     *        it immediately takes over the spot.
     *      - Priority 2 (Directional Fallback): If the scores are not superior, the algorithm falls back 
     *        to check the physical Y-axis movement direction (e.g., favoring downward motion if 'filter' is enabled).
     *      - Priority 3 (Rejection): If the new candidate is weaker in both score and direction, it is discarded.
     * 
     * 5. MATCH LOCK-IN & POOL TRIMMING:
     *    - At the end of the iteration, all surviving unique pairs in 'tentative_matches' are finalized.
     *    - The pairs are recorded into the output container 'passed_frame_pairs'.
     *    - To guarantee convergence, these matched indices are completely erased from 'remainder_n' and 'remainder_n_plus'.
     *    - 'global_pair_found' is flipped to true, triggering a new sub-cycle for the remaining unmatched points.
     * 
     * 6. TERMINATION:
     *    - The loop naturally terminates when no new pairs can be formed (either pools are empty or remaining scores are < 0.5).
     * 
     */


    size_t size_n = passed_frame_n_points.size();
    size_t size_n_plus = passed_frame_n_plus_points.size();


    /**
     * @brief Temporary storage for resolving mapping conflicts between Frame N and Frame N+1.
     * 
     * Key (int): 
     *   The unique index 'j' of a point from the NEXT frame (Frame N+1).
     * 
     * Value (temporary_match): 
     *   The current best candidate 'i' from the PREVIOUS frame (Frame N) 
     *   that wants to pair with 'j', along with its similarity score.
     * 
     * How it is used in the algorithm:
     * 
     *   1. Exclusive ownership: Since a map can only hold ONE value per key, 
     *      each point 'j' in Frame N+1 can temporarily belong to only one point 'i' from Frame N.
     *   2. Conflict resolution: If multiple points from Frame N claim the same 
     *      point 'j' during the iteration, a custom filter checks their vertical 
     *      movement direction and similarity score. The "winner" overwrites the value, 
     *      while the "loser" is kicked out to try finding another pair in the next iteration.
     *   3. Finalization: At the end of each sub-cycle, all surviving pairs in this map 
     *      are confirmed as absolute matches, locked into the final container, and removed 
     *      from future consideration.
     */
    std::unordered_map<int, temporary_match> tentative_matches;


    // 1.0: Init step reminders

    // After pair findings, the remaining unpaired points from Frame N and Frame N+1 will be stored in these sets.

    std::set<int> remainder_n;
    std::set<int> remainder_n_plus;
    
    // 1st set - remainder_n and remainder_n_plus will be eliminated zones

    for (size_t i = 0; i < size_n; ++i) remainder_n.insert(i);
    for (size_t j = 0; j < size_n_plus; ++j) remainder_n_plus.insert(j);



    // Minimal active transition score
    const float min_score_threshold = 0.5f;

    // Stop-flag
    bool global_pair_found = true;


    // Recursive cycle actions
    while (global_pair_found)
    {
        global_pair_found = false;

        // Clear at every mini-cycle
        tentative_matches.clear();


        // Step 3: Check the best pairs ONLY FOR REMINDERS
        for (int i : remainder_n) 
        {

            int best_j = -1;
            float max_score = -1.0f;


            // Check free pairs of N+1 frame
            for (int j : remainder_n_plus) 
            {
                // Inject current score from passed score-matrix
                float current_score = passed_analysis_matrix[i][j].target_compare_result;

                // Write max
                if (current_score > max_score) 
                {
                    max_score = current_score;
                    best_j = j;
                }
            }
            

            // Step 4: Conflicts resolve.
            if (best_j != -1 && max_score >= min_score_threshold) 
            {
                // If j is not used with other i (find() passet to .end()):
                if (tentative_matches.find(best_j) == tentative_matches.end()) 
                {
                    tentative_matches[best_j] = { i, max_score };
                } 
                else
                {
                    // Resolve part
                    // Cascade filter of 2 values

                    const auto& previous_match = tentative_matches[best_j];

                    const float current_y_n =
                        passed_frame_n_points[i].y;

                    const float previous_y_n =
                        passed_frame_n_points[previous_match.index_n].y;

                    const float target_y =
                        passed_frame_n_plus_points[best_j].y;


                    const float current_dy =
                        target_y - current_y_n;

                    const float previous_dy =
                        target_y - previous_y_n;


                    const int current_vertical_direction =
                        current_dy > 0.0f ? 1 :
                        current_dy < 0.0f ? -1 : 0;


                    const int previous_vertical_direction =
                        previous_dy > 0.0f ? 1 :
                        previous_dy < 0.0f ? -1 : 0;


                    // Control vertical filter
                    bool filter = false;


                    if (max_score > previous_match.score)
                    {
                        tentative_matches[best_j] = { i, max_score };
                    }
                    else if (previous_vertical_direction == 1 && current_vertical_direction != 1)
                    {
                        //
                    }

                    // One candidate moves down, the other does not.
                    else if (current_vertical_direction == 1 && previous_vertical_direction != 1)
                    {
                        // Only if filter is enabled, we give the worst candidate by score (or equal)
                        // a 50% chance to knock out the leader based on movement direction
                        if (filter) 
                        {
                            if (rand() % 2 == 0)
                            {
                                tentative_matches[best_j] = { i, max_score };
                            }
                        }
                    }
                }
            }

        }

        // No pairs at this cycle part
        if (tentative_matches.empty())
        {
            break; 
        }

        // Pass the winners to the winners container
        for (const auto& [j, match] : tentative_matches) 
        {
            passed_frame_pairs.push_back({ passed_frame_n_points[match.index_n], passed_frame_n_plus_points[j]});
            
            // Erase winners from the reminders!
            remainder_n.erase(match.index_n);
            remainder_n_plus.erase(j);

            // New circle start
            global_pair_found = true;
        }

    }

    // ===== ENDED =====

}




// ===== Stage 3.2 helpers =====


void processing_stage_3_2(cv::Mat* current_mat)
{

    /**
     * @brief High-Level Pipeline for Inter-Frame Feature Tracking and Kinematics Calculation (Stage 3.2)
     * 
     * This function orchestrates the complete spatial feature-matching workflow between two sequential 
     * video frames. It calculates physical path trajectories, scales pixel deltas to real-world metric units, 
     * computes velocity profiles, and handles debug visualization.
     * 
     * @pipeline_flow
     * 
     * 1. FRAME DATA EXTRACTION:
     *    - Extracts point descriptor vectors for the baseline frame (Frame N) and the target frame (Frame N+1) 
     *      from the global processing data block using the current sequence counter.
     *    - Retrieves historical reference shifts (t_dx, t_dy) to guide the "pseudo-Hungarian" tracking logic.
     * 
     * 2. PAIRWISE ANALYSIS & SCORE GENERATION (Stage 1.0):
     *    - Instantiates a dense 2D 'analysis_matrix' mapping all points in Frame N against all points in Frame N+1.
     *    - Delegates execution to 'analyse_pairs' to compute a grid of normalized proximity and similarity scores.
     * 
     * 3. EXCLUSIVE MATCH SEARCH & CONFLICT RESOLUTION (Stage 2.0):
     *    - Invokes 'find_pairs' to recursively isolate optimal point-to-point associations.
     *    - Resolves multi-candidate mapping conflicts using score hierarchy and directional rules, 
     *      outputting deterministic pairs into the 'frame_pairs' container.
     * 
     * 4. KINEMATIC TRANSFORMATION & PHYSICS CALCULATION:
     *    - Iterates through verified pairs to compute actual physical attributes:
     *      - Computes directional pixel deltas (dx, dy).
     *      - Scales raw pixel motion to absolute metric measurements (millimeters) via pixel scaling coefficients.
     *      - Calculates full linear path distance (track length) using the Pythagorean theorem.
     *      - Derives real-world velocity (meters per second) relative to the video frame-rate timestamp delta.
     *      - Calculates exact trajectory vectors (angles in degrees, ranging from -180 to 180) 
     *        mapped directly to the OpenCV flipped Y-axis layout using std::atan2.
     * 
     * 5. PERSISTENT STORAGE:
     *    - Pushes calculated frame trajectories into the global tracking history storage object.
     * 
     * 6. DIAGNOSTIC RENDERING (Test Mode Overlay):
     *    - If FPC_TEST_MODE is enabled, initializes a black hardware canvas mask.
     *    - Draws a vector diagram overlay using anti-aliased geometry primitives (yellow trajectory vectors 
     *      and solid red position anchors) to visualize feature transitions.
     *    - Performs a destructive data copy, baking the diagnostic overlay directly back into the 'current_mat' buffer 
     *      to ensure formatting compatibility with downstream graphic renderers (e.g., SDL).
     * 
     */

    // If we not inside test mode - calculate the transitions:

    // If we inside test mode - calculate the transitions and show the transitions between frames:


    // Block the not initialized state
    if (!current_mat || current_mat->empty()) return;

     
    // Get current video frame settings.

    unsigned int frames_width = video_data.width;

    unsigned int frames_height = video_data.height;


    // Check traces "dots" from 2 setted massives passed to struct iteration cycle variables last time

    // Frame "n"
    std::vector<desc_c_2D> frame_n_points = 
        data_to_process_3->frames_points[data_to_process_3->frames_points_vectors_counter];

    // Frame "n + 1"
    std::vector<desc_c_2D> frame_n_plus_points = 
        data_to_process_3->frames_points[data_to_process_3->frames_points_vectors_counter + 1];


    // Target dx and dy for my "pseudoHungary 
    float t_dx = data_to_process_3->reference_dx;      // mm !!!
    float t_dy = data_to_process_3->reference_dy;      // mm !!!


    // 1.0. Point to point comparation

    size_t size_n = frame_n_points.size();
    size_t size_n_plus = frame_n_plus_points.size();

    // Analysis matrix init
    std::vector<std::vector<pair_analysis_ctx>> analysis_matrix(

        size_n, 
        std::vector<pair_analysis_ctx>(size_n_plus)

    );


    // Analysis of all pairs -
    // fill the analysis_matrix
    // with the comparation result

    analyse_pairs(

        analysis_matrix, 
        frame_n_points, 
        frame_n_plus_points, 
        t_dx, 
        t_dy

    );


    // 2.0 Recursive pairs search by point to point comparation result

    // Answer container
    std::vector<std::array<desc_c_2D, 2>> frame_pairs;


    std::set<int> remainder_n;      // Остатки кадра N (индексы i строк матрицы)
    std::set<int> remainder_n_plus; // Остатки кадра N+1 (индексы j столбцов матрицы)


    // Изначально все точки находятся в остатках
    for (int i = 0; i < size_n; ++i) remainder_n.insert(i);
    for (int j = 0; j < size_n_plus; ++j) remainder_n_plus.insert(j);


    // Recursive pairs search and illimination stages by target_compare_result obtained at analyse_pairs stage
    find_pairs(

        analysis_matrix,
        frame_pairs,
        frame_n_points,
        frame_n_plus_points
        
    );


    // Init the vector of frame
    std::vector<single_track> frame_tracks;
    
    
    // Fill the frame tracks
    for (unsigned int i = 0; i < frame_pairs.size(); i++)
    {
        single_track pair_track;

        int x_n = frame_pairs[i][0].x;
        int y_n = frame_pairs[i][0].y;

        int x_n_p = frame_pairs[i][1].x;
        int y_n_p = frame_pairs[i][1].y;

        // mm per pixel
        float scale = data_to_process_1->scale;

        // seconds
        float time_step = video_data.frame_time;


        // 1. Pixel deltas
        int dx_px = x_n_p - x_n;
        int dy_px = y_n_p - y_n;

        // 2. MM cast
        float dx_mm = static_cast<float>(dx_px) * scale;
        float dy_mm = static_cast<float>(dy_px) * scale;

        // 3. Size of the track - mm: by triangle
        pair_track.length = std::sqrt(dx_mm * dx_mm + dy_mm * dy_mm);

        // 4. Speed in meters per second
        if (time_step > 0.0f) 
        {
            pair_track.speed = (pair_track.length / 1000.0f) / time_step;
        }
        else 
        {
            pair_track.speed = 0.0f; // Защита от деления на ноль, если время не инициализировано
        }

        // 5. Angle in degrees (from -180 to 180):
        // with opencv axes orientation
        const float PI = 3.1415926535f;

        pair_track.angle = std::atan2(dy_mm, dx_mm) * (180.0f / PI);


        frame_tracks.push_back(pair_track);

    }


    // Add vector of frame to the vector of video

    for (unsigned int i = 0; i < frame_tracks.size(); i++)
    {
        data_to_process_3->tracks.push_back(frame_tracks[i]);
    }

    data_to_process_3->tracks_frames.push_back(frame_tracks); 

    // Remainder



    // Just draw obtained transitions inside test mode
    if (!FPC_TEST_MODE) return;

    // Init an empty black mat to fill
    cv::Mat image_mask_bgr = cv::Mat::zeros(current_mat->size(), current_mat->type());


    // Fill by connected pairs (2 red dots and yellow line) 
    for (size_t i = 0; i < frame_pairs.size(); i++)
    {
        // Cast decs_2D to cv::Point
        cv::Point pt_n(frame_pairs[i][0].x, frame_pairs[i][0].y);
        cv::Point pt_n_plus(frame_pairs[i][1].x, frame_pairs[i][1].y);

        // 1. Yellow 1px line between
        cv::line(image_mask_bgr, pt_n, pt_n_plus, cv::Scalar(0, 255, 255), 1, cv::LINE_AA);

        // 2. Red dots 2mm
        cv::circle(image_mask_bgr, pt_n, 2, cv::Scalar(0, 0, 255), -1, cv::LINE_AA);
        cv::circle(image_mask_bgr, pt_n_plus, 2, cv::Scalar(0, 0, 255), -1, cv::LINE_AA);
    }


    // =======================================================================================
    // WRITE RESULT BACK TO current_mat

    // Replace the current current_mat with the processed jet mask.
    //
    // IMPORTANT:
    // current_mat remains CV_8UC3 BGR, so the next processing stage
    // and the OpenCV -> SDL translation can continue working
    // with the same image format.

    image_mask_bgr.copyTo(*current_mat);

    // =======================================================================================
    // WRITE RESULT BACK TO FRAME

}



// =========================================================================================== PROCESSING FUNCTIONS



// =========================================================================================== PROGRESS BAR

void progress_bar_update()
{
    if (state_progress_bar.operations_count == 0)
    {
        state_progress_bar.percentage = 0.0f;
        return;
    }
    else
    {
            
        state_progress_bar.percentage =

                (static_cast<float>(state_progress_bar.operations_counter)
                / static_cast<float>(state_progress_bar.operations_count))
                * 100.0f;
    }


    if (state_progress_bar.percentage >= 100) state_progress_bar.percentage = 100;

    /*

        state_progress_bar.percentage += 0.25;

        if (state_progress_bar.percentage > 100) state_progress_bar.percentage = 0;
    
    */


    std::string percentage_string =
        std::to_string(
            static_cast<int>(std::round(state_progress_bar.percentage))
        ) + "%.";


    std::string file_number;
    std::string mask_number;
    std::string frame_number;

    std::string file_string;
    std::string mask_string;
    std::string frame_string;


    if (!global_calculation_end_flag)
    {

        switch (opencv_global_calculation_update_ctx.current_file_for_mask_setup)
        {
            case FILE_1_CF:
            {
                file_number = "1";
                break;
            }

            case FILE_2_CF:
            {
                file_number = "2";
                break;
            }


            case FILE_3_CF:
            {
                file_number = "3";
                break;
            }


            case FILE_4_CF:
            {
                file_number = "4";
                break;
            }

            case FILE_5_CF:
            {
                file_number = "5";
                break;
            }

            case FILE_6_CF:
            {
                file_number = "6";
                break;
            }

            default: break;
        }


        switch (opencv_global_calculation_update_ctx.operation)
        {
            case MASK_1_PROCESSING_CO:
            {
                mask_number = "1-3";
                break;
            }

            case MASK_2_PROCESSING_CO:
            {
                mask_number = "1-3";
                break;
            }


            case MASK_3_1_PROCESSING_CO:
            {
                mask_number = "1-3";
                break;
            }


            case MASK_3_2_PROCESSING_CO:
            {
                mask_number = "4";
                break;
            }

            default: break;
        }


        frame_number = std::to_string(state_progress_bar.current_frame) +
                    " / " +
                    std::to_string(state_progress_bar.frames_quantity);


        file_string = str_by_dictionary(gd_calculation_file) + file_number;

        mask_string = str_by_dictionary(gd_calculation_stage) + mask_number;
        
        frame_string = str_by_dictionary(gd_calculation_frame) + frame_number;
    }
    else
    {
        file_string = str_by_dictionary(gd_calculation_file) + "-";

        mask_string = str_by_dictionary(gd_calculation_stage) + "-";
        
        frame_string = str_by_dictionary(gd_calculation_frame) + "-";
    }

    // Set the textboxes slots

    percentage_textbox->set_content(percentage_string);
    file_textbox->set_content(file_string);
    mask_textbox->set_content(mask_string);
    frame_textbox->set_content(frame_string);

}


void progress_bar_render(SDL_Renderer* renderer)
{

    SDL_Color progress_bar_fill_color = hex_to_sdl_color("#ff891a", 255);

    SDL_Color progress_bar_border_color = App_palette.get_current_palette().basic_border_color;         // hex_to_sdl_color("#090400", 255);
    

    int current_width = static_cast<int>(
        (static_cast<double>(state_progress_bar.percentage) / 100.0)
        * (progress_bar_width - 2 * flow_parameters_calculation_panel->get_border_width_size())
    );
    // Render rectangle


    if (current_width != 0)
    {
        rectangle_draw_by_color(

            pb_x_1,
            pb_y_1,
            current_width,
            progress_bar_height,
            progress_bar_fill_color,
            renderer

        );
    }

    // Render 2 lines

    line_draw(

        pb_l_1_x_1, 
        pb_l_1_y_1,

        pb_l_1_x_2, 
        pb_l_1_y_2,


        progress_bar_lines_width,

        progress_bar_border_color,

        renderer

    );


    
    line_draw(

        pb_l_2_x_1, 
        pb_l_2_y_1,

        pb_l_2_x_2, 
        pb_l_2_y_2,


        progress_bar_lines_width,

        progress_bar_border_color,

        renderer

    );



    // Render textboxes

    percentage_textbox->render(renderer);
    file_textbox->render(renderer);
    mask_textbox->render(renderer);
    frame_textbox->render(renderer);
}

// =========================================================================================== PROGRESS BAR
