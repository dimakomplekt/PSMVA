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

files_processing_data global_processing_data;

flow_calculation_progress_bar state_progress_bar;


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


// ===== DATA =====

cv::VideoCapture* video_capture_device_global_fpc = nullptr;

cv::Mat* calculation_cv_mat_mask_1_global = nullptr;
cv::Mat* calculation_cv_mat_mask_2_global = nullptr;
cv::Mat* calculation_cv_mat_mask_3_global = nullptr;


bool opencv_calculation_pipeline_reset_global = false;

opencv_calculation_update_ctx opencv_global_calculation_update_ctx;

// ===== DATA =====


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

        if (file_1_need_init) total_frames += 2 * files_metadata.video_1_data.frames_quantity;
        if (file_2_need_init) total_frames += 2 * files_metadata.video_2_data.frames_quantity;
        if (file_3_need_init) total_frames += 2 * files_metadata.video_3_data.frames_quantity;
        if (file_4_need_init) total_frames += 2 * files_metadata.video_4_data.frames_quantity;
        if (file_5_need_init) total_frames += 2 * files_metadata.video_5_data.frames_quantity;
        if (file_6_need_init) total_frames += 2 * files_metadata.video_6_data.frames_quantity;

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





bool global_calculation_end_flag = false;


parsed_video_data video_data;


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
                opencv_global_calculation_update_ctx.current_frame_processor = processing_stage_1;
                opencv_global_calculation_update_ctx.current_frame_processor(calculation_cv_mat_mask_1_global);


                opencv_global_calculation_update_ctx.operation = MASK_2_PROCESSING_CO;
                opencv_global_calculation_update_ctx.current_frame_processor = processing_stage_2;
                opencv_global_calculation_update_ctx.current_frame_processor(calculation_cv_mat_mask_2_global);

                opencv_global_calculation_update_ctx.operation = MASK_3_1_PROCESSING_CO;
                opencv_global_calculation_update_ctx.current_frame_processor = processing_stage_3_1;
                opencv_global_calculation_update_ctx.current_frame_processor(calculation_cv_mat_mask_3_global);


                // Update frame
                opencv_global_calculation_update_ctx.current_frame_index += 1;

                
                // Check if wee need to over 1st stage

                if (opencv_global_calculation_update_ctx.current_frame_index == opencv_global_calculation_update_ctx.total_frame_count)
                {
                    data_to_control->stage_1_end = true;
                    opencv_global_calculation_update_ctx.current_frame_index = 0;


                    // ===== Global video statistics calculation (Outside the frame loop) =====

                    // 1. Вычисляем общее среднее мощности света по всему видео
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


                    // 2. Вычисляем общую медиану амплитуды струи по всему видео
                    // Фильтруем нули (кадры без струи), чтобы они не ломали медиану для всего видеоролика
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


                    // ===== Global video statistics calculation =====
                    
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
                    }

                    curr_dtp_2->calculated = true;
                }


                // Operations counter update
                state_progress_bar.operations_counter += 1;
            }

            else if (data_to_control->stage_1_end && !data_to_control->stage_2_end)
            {
                opencv_global_calculation_update_ctx.global_operation = PROCESSING_STAGE_2_CGO;


                opencv_global_calculation_update_ctx.operation = MASK_3_2_PROCESSING_CO;
                opencv_global_calculation_update_ctx.current_frame_processor = processing_stage_3_2;
                opencv_global_calculation_update_ctx.current_frame_processor(calculation_cv_mat_mask_3_global);


                opencv_global_calculation_update_ctx.current_frame_index += 1;


                // Check if wee need to over 2nd stage

                if (opencv_global_calculation_update_ctx.current_frame_index == opencv_global_calculation_update_ctx.total_frame_count)
                {
                    data_to_control->stage_2_end = true;


                    // 2nd stage ended - so we set the flag to switch the video
                    // inside the for-loop at the start of this function
                    // The next update cycle will select another using file.
                    data_to_control->calculated_flag = true;


                    // For the next video
                    opencv_global_calculation_update_ctx.need_reset = true;

                    // Basic
                    opencv_global_calculation_update_ctx.global_operation = PROCESSING_STAGE_1_CGO;

                    // Current operation
                    opencv_global_calculation_update_ctx.operation = MASK_1_PROCESSING_CO;


                    // Drop the data to control for calculation end or reinit
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


nozzle_detection_mask nozzle_mask_to_process;
jet_detection_mask jet_mask_to_process;
particle_detection_mask particle_mask_to_process;


processing_1_data* data_to_process_1;
processing_2_data* data_to_process_2;
processing_3_data* data_to_process_3;


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
    if (!current_mat || current_mat->empty())
        return;

        
    // =======================================================================================
    // GET CONTROLLED MASK

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
        //     FINAL MASK
        //
        //
        // Поэтому теперь FINAL MASK становится новым FIRST MASK.
        //
        // Это удобно, потому что ниже по pipeline уже не нужно
        // создавать отдельную переменную для результата:
        //
        //     first_mask
        //
        // просто начинает означать "итоговую маску текущего этапа".
        //
        //
        // После этой строки:
        //
        //     first_mask
        //
        // содержит только те области, которые:
        //
        //     1. прошли HSV-фильтр;
        //     2. дали Canny-контур;
        //     3. после DILATE сформировали contour;
        //     4. прошли AREA;
        //     5. прошли LENGTH.
        //
        //
        // То есть это уже очищенный FINAL RESULT.


        first_mask = final_mask;
    }

    // =======================================================================================
    // TRANSLATE BACK TO BGR AND SHOW

    cv::Mat final_mask_bgr;

    cv::cvtColor(
        first_mask,
        final_mask_bgr,
        cv::COLOR_GRAY2BGR
    );

    final_mask_bgr.copyTo(*current_mat);
}


void processing_stage_3_2(cv::Mat* current_mat)
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
    if (!current_mat || current_mat->empty())
        return;

        
    // =======================================================================================
    // GET CONTROLLED MASK

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
        //     FINAL MASK
        //
        //
        // Поэтому теперь FINAL MASK становится новым FIRST MASK.
        //
        // Это удобно, потому что ниже по pipeline уже не нужно
        // создавать отдельную переменную для результата:
        //
        //     first_mask
        //
        // просто начинает означать "итоговую маску текущего этапа".
        //
        //
        // После этой строки:
        //
        //     first_mask
        //
        // содержит только те области, которые:
        //
        //     1. прошли HSV-фильтр;
        //     2. дали Canny-контур;
        //     3. после DILATE сформировали contour;
        //     4. прошли AREA;
        //     5. прошли LENGTH.
        //
        //
        // То есть это уже очищенный FINAL RESULT.


        first_mask = final_mask;
    }

    // =======================================================================================
    // TRANSLATE BACK TO BGR AND SHOW

    cv::Mat final_mask_bgr;

    cv::cvtColor(
        first_mask,
        final_mask_bgr,
        cv::COLOR_GRAY2BGR
    );

    final_mask_bgr.copyTo(*current_mat);   
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


