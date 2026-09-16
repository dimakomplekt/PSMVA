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


// =========================================================================================== STATE DATA

// RAII + lifecycle management

My_SDL_panel* flow_parameters_calculation_panel = nullptr;

My_SDL_textbox* flow_parameters_calculation_textbox = nullptr;

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
}


void flow_parameters_calculation_render(SDL_Renderer* renderer)
{
    if (App_timer_1.can_execute(Execute_zone_ID::HZ_120))
    {
        flow_parameters_calculation_elements_render(renderer);
    }
}

// =========================================================================================== MAIN STATE API



// =========================================================================================== INNER STATE FUNCTIONS


// =========================================================================================== STATE INNER FUNCTIONS REALIZATION

void flow_parameters_calculation_elements_create()
{
    // flow_parameters_calculation panel create
    flow_parameters_calculation_panel = new My_SDL_panel();

    // flow_parameters_calculation textbox create
    flow_parameters_calculation_textbox = new My_SDL_textbox();
}


void flow_parameters_calculation_elements_setup()
{
    // flow_parameters_calculation panel setup

    flow_parameters_calculation_panel->set_render_point(MAIN_WINDOW_H_SIZE / 2, MAIN_WINDOW_V_SIZE / 2);
    flow_parameters_calculation_panel->set_size(MAIN_WINDOW_H_SIZE, MAIN_WINDOW_V_SIZE);
    flow_parameters_calculation_panel->set_border_radius(0);

    // flow_parameters_calculation textbox setup
    flow_parameters_calculation_textbox->switch_textbox_type(HEADER_2);

    flow_parameters_calculation_textbox->set_content(str_by_dictionary(gd_flow_parameters_calculation_info));

    flow_parameters_calculation_textbox->switch_blinking_mode_flag(true);



    // Put the texture inside the middle of the panel

    flow_parameters_calculation_panel->add_element(

        flow_parameters_calculation_textbox,
         (flow_parameters_calculation_panel->get_width_size()) * 0.5,
          (flow_parameters_calculation_panel->get_height_size()) * 0.5,
           1
    );

}


void flow_parameters_calculation_elements_free_and_nullptr()
{
    // Free all elements

    flow_parameters_calculation_panel->delete_element();

    // Nullptr the pointers

    flow_parameters_calculation_panel = nullptr;
    flow_parameters_calculation_textbox = nullptr;
    
}


void flow_parameters_calculation_elements_update()
{
    // Check if textboxes need content renew
    reset_passed_by_dictionary_textboxes_if_language_switched_ms();

    // Update all elements
    flow_parameters_calculation_panel->update();

}


void reset_passed_by_dictionary_textboxes_if_language_switched_ms()
{
    // Repeat content set if language switched
    if (App_lang.get_lang_reset_flag())
    {
        flow_parameters_calculation_textbox->set_content(str_by_dictionary(gd_flow_parameters_calculation_info));
    }
}


void flow_parameters_calculation_actions()
{
    // Switch the state to EXIT if EXIT pressed


}


void flow_parameters_calculation_elements_render(SDL_Renderer* renderer)
{
    // Render all elements
    flow_parameters_calculation_panel->render(renderer);

}

// =========================================================================================== STATE INNER FUNCTIONS REALIZATION




// =========================================================================================== OPENCV PART OF THE STATE


// ===== DATA =====

cv::VideoCapture* video_capture_device_global = nullptr;

cv::Mat* calculation_cv_mat_mask_1_global = nullptr;
cv::Mat* calculation_cv_mat_mask_2_global = nullptr;
cv::Mat* calculation_cv_mat_mask_3_global = nullptr;


bool opencv_calculation_pipeline_reset_global = false;

opencv_calculation_update_ctx opencv_global_calculation_update_ctx;

// ===== DATA =====


// ===== Functions =====

void opencv_global_setup()
{
    // Block of the reinit
    if (opencv_pipeline_reset_global != true)
    {
        calculation_cv_mat_mask_1_global = new cv::Mat();
        calculation_cv_mat_mask_2_global = new cv::Mat();
        calculation_cv_mat_mask_3_global = new cv::Mat();

        // Will be reseted (for size correction) at the setup 
        // of each inner state (1.2.1  1.2.6)


        // ===== PROGRESS BAR INIT =====


        // ===== PROGRESS BAR INIT =====


        opencv_pipeline_reset_global = true;
    }

    if (TEST_MODE) std::cout << "Mats and texture created\n" << std::endl;   
}


void switch_video_for_calculation(const std::string& new_file_path) 
{
    // 1. DELETE old capture device if video is opened
    if (video_capture_device_global != nullptr)
    {
        if (video_capture_device_global->isOpened())
        {
            // Close file
            video_capture_device_global->release();
        }

        // Free the memory 
        delete video_capture_device_global;
        
        // Free the pointer
        video_capture_device_global = nullptr;
    }

    if (new_file_path.empty())
    {
        std::cerr << "Error: video path is empty\n";
        opencv_global_calculation_update_ctx.total_frame_count = 0;
        return;
    }

    // 2. Create new capture device
    video_capture_device_global = new cv::VideoCapture(new_file_path);

    // 3. Check
    if (!video_capture_device_global->isOpened())
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
        video_capture_device_global->isOpened()
            ? static_cast<int>(video_capture_device_global->get(cv::CAP_PROP_FRAME_COUNT))
            : 0;
}


void opencv_global_update()
{

    // ===== PREPROCESSING =====

    // Current data to work with

    std::string file_path;

    cv::Mat* current_basic_mat_to_process = nullptr;

    // Which file
    switch (opencv_global_calculation_update_ctx.current_file_for_mask_setup)
    {
        case (FILE_1_CF):
        {
            file_path =  file_choose_info.file_1_path;
            break;
        }

        case (FILE_2_CF):
        {
            file_path =  file_choose_info.file_2_path;
            break;
        }

        case (FILE_3_CF):
        {
            file_path =  file_choose_info.file_3_path;
            break; 
        }

        case (FILE_4_CF):
        {
            file_path =  file_choose_info.file_4_path;
            break;
        }

        case (FILE_5_CF):
        {
            file_path =  file_choose_info.file_5_path;
            break;
        }

        case (FILE_6_CF):
        {
            file_path =  file_choose_info.file_6_path;
            break;
        }

        default: break;
    }

    // Which mask
    switch (opencv_global_calculation_update_ctx.current_mask_for_mask_setup)
    {
        case (MASK_1_CM):
        {
            current_basic_mat_to_process = calculation_cv_mat_mask_1_global;
            break;
        }

        case (MASK_2_CM):
        {
            current_basic_mat_to_process = calculation_cv_mat_mask_2_global;
            break;
        }

        case (MASK_3_CM):
        {
            current_basic_mat_to_process = calculation_cv_mat_mask_3_global;
            break;
        }

        default: break;
    }


    if (current_basic_mat_to_process == nullptr)
    {
        std::cerr << "ERROR: current_basic_mat_to_process == nullptr\n";
        return;
    }


    // ===== PREPROCESSING =====


    // ===== DEFAULT TRANSLATION LOGIC =====

    // First call at the state start
    // we need to create new VCD

    if (opencv_global_calculation_update_ctx.need_reset)
    {
        // USE HELPER
        switch_video_for_calculation(file_path);

        // Block reinits after reset
        opencv_global_calculation_update_ctx.need_reset = false;

        if (video_capture_device_global == nullptr ||
            !video_capture_device_global->isOpened())
        {
            opencv_global_calculation_update_ctx.need_reset = true;
            return;
        }
    }

    if (video_capture_device_global == nullptr ||
        !video_capture_device_global->isOpened())
    {
        opencv_global_calculation_update_ctx.need_reset = true;
        return;
    }

    // Play logic (nothing at pause)
    {
        // Show from the start (if it's 1st call)
        if (current_basic_mat_to_process->empty())
        {
            opencv_global_calculation_update_ctx.current_frame_index = 0;
        }
    
        // Rewind to current frame
        video_capture_device_global->set(
            cv::CAP_PROP_POS_FRAMES,
            opencv_global_calculation_update_ctx.current_frame_index
        );
    
        // Read current frame
        *video_capture_device_global >> *current_basic_mat_to_process;
    
        // Move to the next frame for the next update()
        opencv_global_calculation_update_ctx.current_frame_index++;
    }


    if (TEST_MODE) std::cout << "Capture passed to MAT!\n" << std::endl;

    // ===== DEFAULT TRANSLATION LOGIC =====


    // ===== BLACKBOX WITH PROCESSING LOGIC BY CALLBACK =====

    if (opencv_global_calculation_update_ctx.current_frame_processor != nullptr)
    {
        if (current_basic_mat_to_process != nullptr)
            // CALL A CALLBACK FOR CURRENT MAT
            // THE RENDERER will show the video after processing
            opencv_global_calculation_update_ctx.current_frame_processor(current_basic_mat_to_process);
    }

    // ===== BLACKBOX WITH PROCESSING LOGIC BY CALLBACK =====
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
    opencv_pipeline_reset_global = false;
}


// ===== Functions =====

// =========================================================================================== OPENCV PART OF THE STATE






