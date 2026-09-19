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


        if (file_1_need_init) global_processing_data.file_1.using_flag = true;
        if (file_2_need_init) global_processing_data.file_2.using_flag = true;
        if (file_3_need_init) global_processing_data.file_3.using_flag = true;
        if (file_4_need_init) global_processing_data.file_4.using_flag = true;
        if (file_5_need_init) global_processing_data.file_5.using_flag = true;
        if (file_6_need_init) global_processing_data.file_6.using_flag = true;


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
        opencv_global_calculation_update_ctx.current_frame_processor = processing_1;

        if (FPC_TEST_MODE)
        {
            opencv_global_calculation_update_ctx.show_kingsize = true;
            opencv_global_calculation_update_ctx.kingsize_live_transmission = false;
        }
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
    if (opencv_global_calculation_update_ctx.kingsize_live_transmission)
    {
        cv::destroyWindow("KINGSIZE_TEST");
        opencv_global_calculation_update_ctx.kingsize_live_transmission = false;
    }
}


void opencv_calculation_global_update()
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
    switch (opencv_global_calculation_update_ctx.operation)
    {
        case (MASK_1_PROCESSING_CO):
        {
            current_basic_mat_to_process = calculation_cv_mat_mask_1_global;
            break;
        }

        case (MASK_2_PROCESSING_CO):
        {
            current_basic_mat_to_process = calculation_cv_mat_mask_2_global;
            break;
        }

        
        case MASK_3_1_PROCESSING_CO: [[fallthrough]]; // явно говорим, что так и задумано
        case MASK_3_2_PROCESSING_CO:
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
    {
        // Show from the start (if it's 1st call)
        if (current_basic_mat_to_process->empty())
        {
            opencv_global_calculation_update_ctx.current_frame_index = 0;
        }
    
        // Rewind to current frame
        video_capture_device_global_fpc->set(
            cv::CAP_PROP_POS_FRAMES,
            opencv_global_calculation_update_ctx.current_frame_index
        );
    
        // Read current frame
        *video_capture_device_global_fpc >> *current_basic_mat_to_process;
    
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


    

    // ===== SHOW SCALED COPY OF CURRENT MAT INSIDE OTHER WINDOW =====

    // Development stage
    if (FPC_TEST_MODE)
    {
        // If frame is empty, skip this update
        if (!current_basic_mat_to_process->empty())
        {
            if (opencv_global_calculation_update_ctx.show_kingsize)
            {
                // First call after activation
                if (!opencv_global_calculation_update_ctx.kingsize_live_transmission)
                {
                    kingsize_window_init_fpc(current_basic_mat_to_process);

                    // Block reinit
                    opencv_global_calculation_update_ctx.kingsize_live_transmission = true;
                }


                // USER INPUT ERROR HANDLER
                // Check whether user closed the window manually
                if (cv::getWindowProperty("KINGSIZE_TEST", cv::WND_PROP_VISIBLE) < 1)
                {
                    opencv_global_calculation_update_ctx.show_kingsize = false;
                    opencv_global_calculation_update_ctx.kingsize_live_transmission = false;

                    return;
                }


                // Create scaled copy
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

                // Show scaled image
                cv::imshow(
                    "KINGSIZE_TEST",
                    kingsize_mat
                );

                cv::waitKey(1);
            }
            else
            {
                // Close window after deactivation
                if (opencv_global_calculation_update_ctx.kingsize_live_transmission)
                {
                    kingsize_window_close_fpc();

                    // Allow init on next activation
                    opencv_global_calculation_update_ctx.kingsize_live_transmission = false;
                }
            }
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


void processing_1(cv::Mat* current_mat)
{
    processing_stage_1(current_mat);
    processing_stage_2(current_mat);
    processing_stage_3_1(current_mat);
}


void processing_2(cv::Mat* current_mat)
{
    processing_stage_3_2(current_mat);
}


void processing_stage_1(cv::Mat* current_mat)
{
    // TEST
    state_progress_bar.current_frame = 1 + (state_progress_bar.current_frame) % 8000;
    state_progress_bar.operations_counter += 1;


    if (state_progress_bar.operations_counter % 100 == 0)
    {
        std::cout
            << "operations_counter = "
            << state_progress_bar.operations_counter
            << " / "
            << state_progress_bar.operations_count
            << std::endl;
    }
}

void processing_stage_2(cv::Mat* current_mat)
{

}

void processing_stage_3_1(cv::Mat* current_mat)
{

}

void processing_stage_3_2(cv::Mat* current_mat)
{

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
            mask_number = "1";
            break;
        }

        case MASK_2_PROCESSING_CO:
        {
            mask_number = "2";
            break;
        }


        case MASK_3_1_PROCESSING_CO:
        {
            mask_number = "3";
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


    std::string file_string = str_by_dictionary(gd_calculation_file) + file_number;

    std::string mask_string = str_by_dictionary(gd_calculation_mask) + mask_number;
    
    std::string frame_string = str_by_dictionary(gd_calculation_frame) + frame_number;


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


