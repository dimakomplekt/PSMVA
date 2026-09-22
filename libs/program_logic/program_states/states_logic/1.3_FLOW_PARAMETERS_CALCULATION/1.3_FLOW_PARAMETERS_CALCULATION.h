// 1.3_FLOW_PARAMETERS_CALCULATION.h


#pragma once

// =========================================================================================== IMPORT

#include "../../../../engine/engine.h"


#include "../1.2_MASKS_SETUP/1.2_MASKS_SETUP.h"

#include "../1.1_FILE_CHOOSE/txt_parse.h"


#include "../../../../program_gui/basic_elements/global_palette/global_palette.h"
#include "../../../../program_gui/basic_elements/global_fonts/global_fonts.h"

#include "../../../global_data/global_data.h"


#include <array>

// For frame processor
#include <functional>

#include <cmath>   // Для std::atan2
#include <cstdio>  // Для std::snprintf

#include <numeric>

// =========================================================================================== IMPORT


// =========================================================================================== DEFINES

#define FPC_TEST_MODE 1

// =========================================================================================== DEFINES


// =========================================================================================== MAIN STATE API

/**
 * Functions called when entering or exiting a specific state.
 *
 * These are assigned to the `on_enter` and `on_exit` callbacks of the
 * corresponding State objects in the state machine.
 *
 * Example:
 * 
 * app_state_machine.add_state(std::make_unique<State>(START_ID, "START"));
 * state->on_enter = start_enter;
 * 
 */

void flow_parameters_calculation_enter();
void flow_parameters_calculation_exit();

void flow_parameters_calculation_update();
void flow_parameters_calculation_render(SDL_Renderer* renderer);

// =========================================================================================== MAIN STATE API


// =========================================================================================== DATA



// =========================================================================================== DATA


// =========================================================================================== GLOBAL DATA


// =========================================================================================== GLOBAL DATA


// =========================================================================================== GLOBAL OPENCV PART

// !!! WARNING !!!


// This data is handled using a dynamic memory allocation pattern but is deallocated in a non-standard way
// (relative to the program's overall style).

// INIT - AT THE STATE 1.2
// DELETE - AT THE STATE 1.4 (CAUSE THE DATA WILL BE USED AT THE STATES 1.2, 1.3)

// There could be 6 files with 3 equal masks at each
// so the profitable way to implement them is to
// create pipeline data for 1 and use it to all 6,
// just change the parameters of the masks with different states, 
// but continue to work with 1 video capture, 3 global MATs and 
// 1 translated texture (with passed MAT change with current mask change)

// !!! All this parts will be initiated (with reinit block) at the ENTER of state 1.2 !!!

// !!! And will be destroyed at the ENTER of state 1.4 !!!

// Basic initialization will be performed in state 1.2.
// At the states 1.2.1 - 1.2.6 additional settings (like the choose of the masks parameters 
// for each file, choose of the My_SDL_Texture* which will contain translsated_texture_global) will be performed


// !!! WARNING !!!


// ===== DATA =====

// Global capture
extern cv::VideoCapture* video_capture_device_global_fpc;


// Global MAT for capture frameus

// Nozzle mask
extern cv::Mat* calculation_cv_mat_mask_1_global;

// Jet mask
extern cv::Mat* calculation_cv_mat_mask_2_global;

// Particle trace mask
extern cv::Mat* calculation_cv_mat_mask_3_global;



// Global reinit block flag
extern bool opencv_calculation_pipeline_reset_global;

// Block calculations repeat and open
// the switch state button
extern bool global_calculation_end_flag = false;

// ===== DATA =====


// ===== Functions =====


// Setup function with all needed ctx
// setting up 
void opencv_calculation_global_setup();


// Global variable for current file check


// Enum for calculation state machine



// Marker of the global operation
enum current_global_operation 
{

    PROCESSING_STAGE_1_CGO,
    PROCESSING_STAGE_2_CGO

};


// Marker of the inner operation
enum current_operation 
{

    MASK_1_PROCESSING_CO,
    MASK_2_PROCESSING_CO,
    MASK_3_1_PROCESSING_CO,
    MASK_3_2_PROCESSING_CO

};


// Struct for calculation processing
// uses unside global update to form
// the frames switch logic, processing stages switch
// logic and other...
struct opencv_calculation_update_ctx
{
    // Current file (uses for translator setup)
    current_file_ms current_file_for_mask_setup = FILE_1_CF;

    current_global_operation global_operation = PROCESSING_STAGE_1_CGO;

    // Current operation
    current_operation operation = MASK_1_PROCESSING_CO;

    // Pointer to the frame_processor
    frame_processor current_frame_processor = nullptr;



    // Current frame number
    int current_frame_index = 0;

    // Total frame number
    // initiates at the switch_videp()
    int total_frame_count;


    // Need reset flag for switch_video call in update function
    bool need_reset = true;

};


// Global ctx for calculation processing control
extern opencv_calculation_update_ctx opencv_global_calculation_update_ctx;



// Global update function, which
// works different in depending of current structure 
// (opencv_global_update_ctx) data 
void opencv_calculation_global_update();


// "Destructor" of the calculation data
void opencv_calculation_global_free_and_nullptr();

// ===== Functions =====

// =========================================================================================== GLOBAL OPENCV PART


// =========================================================================================== PROCESSING

// ===== PROCESSING CTX =====

// Current copy of nozzle mask from state 1.2 to work with
// uses to switch between files mask inside functions 
extern nozzle_detection_mask nozzle_mask_to_process;

// Current copy of jet mask from state 1.2 to work with
// uses to switch between files mask inside functions
extern jet_detection_mask jet_mask_to_process;


// Current copy of particle mask from state 1.2 to work with
// uses to switch between files mask inside functions
extern particle_detection_mask particle_mask_to_process;


// Ax + By + C = 0
struct line_equation
{

    float a;
    float b;
    float c;

};


// 1st mask processing output ctx
struct processing_1_data
{
    float scale;                            // In mm / px - equal for both axes


    line_equation nozzle_axe;               // By line equation coefficients
    float nozzle_axe_angle;                 // In degrees

    bool calculated = false;                // Processing end flag

};


// 2nd mask processing output ctx
struct processing_2_data
{

    std::vector<float> frames_mean_light_power_percentage;      // Light power inside frames - mead V / Vmax (HSV)

    std::vector<float> frames_median_jet_amplitude;             // Median jet amplitude inside frames
    std::vector<float> frames_mean_jet_amplitude;               // Mean jet amplitudes inside frames

    float video_mean_light_power_percentage;                    // Light power inside video - mead V / Vmax (HSV)
    float video_median_jet_amplitude;                           // Median jet amplitude inside video   
    float video_mean_jet_amplitude;                             // Mean jet amplitudes inside video

    bool calculated = false;                                    // Processing end flag

};


// 2rd mask processing output ctx
struct processing_3_data
{

};


// Global processing 1 data pointer to work with.
// Uses to switch between processing 1 ctx-s inside functions  
extern processing_1_data* data_to_process_1;

// Global processing 2 data pointer to work with.
// Uses to switch between processing 2 ctx-s inside functions  
extern processing_2_data* data_to_process_2;

// Global processing 3 data pointer to work with.
// Uses to switch between processing 3 ctx-s inside functions  
extern processing_3_data* data_to_process_3;

// Current copy of current video data to work with
// Uses to switch between video data ctx-s inside functions   
extern parsed_video_data video_data;


// 1 File processing control ctx
struct file_processing_data
{
    current_file_ms file;
    std::string file_path;

    bool using_flag = false;


    bool stage_1_end = false;
    bool stage_2_end = false;

    // Updates at init stage of the state
    bool calculated_flag = false;


    processing_1_data processing_1;
    processing_2_data processing_2;
    processing_3_data processing_3;

};


// All files processing control ctx
struct files_processing_data
{

    file_processing_data file_1;
    file_processing_data file_2;
    file_processing_data file_3;
    file_processing_data file_4;
    file_processing_data file_5;
    file_processing_data file_6;

};

// Global files processing control ctx to work with
extern files_processing_data global_processing_data;


// ===== PROCESSING CTX =====



// ===== PROCESSING FUNCTIONS =====

// Calculation of the scale and main axe line coefficients
void processing_stage_1(cv::Mat* current_mat);

// Calculation of the video light power, light power delta speed, mean / median
// jet amplitude  
void processing_stage_2(cv::Mat* current_mat);


// Pre...
void processing_stage_3_1(cv::Mat* current_mat);

// Calcult....
void processing_stage_3_2(cv::Mat* current_mat);


// ===== PROCESSING FUNCTIONS =====


// =========================================================================================== PROCESSING


// =========================================================================================== PROGRESS BAR


// Logic of update inside calculation is - open 1 video, process 1 frame with 1st mask, with 2nd
// mask and with 3rd mask stage 1.
// 
// After 1st pass there will be answer with mask 1 / mask 2 parameters values and answer for the 1st stage 
// of the 3rd mask calculation. 
// 
// Frame will rewind to the 1st and there will be 2nd pass of the file with 2nd stage of 3rd mask
// calculation


// Progress bar ctx will be updated through the whole opencv_calculation_update() without speed block
// Progress bar GUI will be updated at the 240HZ freq zone and rendered at 120HZ zone.  

// Progress bar wil contain one scale and one text row 
// Scale will show the percentage of the whole operations
// Text will show which operation is processed now (not exactly, but for human viewer more than enough) 


// Progress bar ctx
struct flow_calculation_progress_bar
{

    // (operations_counter / operations_count) * 100;
    float percentage = 0.0f;


    unsigned int operations_counter = 0;        // Current ended operations counter
    unsigned int operations_count = 0;          // Sum file_frames * 2 for all files 


    unsigned int current_frame = 0;             // Current file processed frames quantity
    unsigned int frames_quantity = 0;           // Current file frames quantity

};


// Global progress bar ctx to work with
extern flow_calculation_progress_bar state_progress_bar;

// Update progress bar data (4 textboxes)
void progress_bar_update();

// Render progress bar (4 textboxes + 2 lines + 1 rectangle)
void progress_bar_render(SDL_Renderer* renderer);

// =========================================================================================== PROGRESS BAR
