// 1.2_MASKS_SETUP.h


#pragma once

// =========================================================================================== IMPORT

#include "../../../../engine/engine.h"

#include "../../../../program_gui/basic_elements/global_palette/global_palette.h"
#include "../../../../program_gui/basic_elements/global_fonts/global_fonts.h"

#include "../../../global_data/global_data.h"


#include <array>

// =========================================================================================== IMPORT


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

void masks_setup_enter();
void masks_setup_exit();

void masks_setup_update();
void masks_setup_render(SDL_Renderer* renderer);

// =========================================================================================== MAIN STATE API


// =========================================================================================== DATA

inline constexpr std::array<int, 20> nozzle_diameters = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

// =========================================================================================== DATA


// =========================================================================================== GLOBAL DATA

// Mask for the nozzle detection
struct nozzle_detection_mask
{
    // Top point of the nozzle

    int x_1;
    int y_1;

    // Bottom point of the nozzle

    int x_2;
    int y_2;


    // Nozzle diameter
    int Dn;

};


// Mask for the nozzle detection
struct jet_detection_mask
{

};


// Mask for the nozzle detection
struct particle_detection_mask
{

};



enum class mask_state 
{

    EMPTY_STATE,
    FILLED_STATE

};


// Context for one file
struct file_masks_data
{
    bool* file_choose_state;

    mask_state masks_setup_state;


    nozzle_detection_mask nozzle_mask;
    jet_detection_mask jet_mask;
    particle_detection_mask particle_mask;

};


struct files_masks_data
{

    file_masks_data file_1_masks;
    file_masks_data file_2_masks;
    file_masks_data file_3_masks;
    file_masks_data file_4_masks;
    file_masks_data file_5_masks;
    file_masks_data file_6_masks;

};

// Data for masks setup
inline files_masks_data masks_data;

// =========================================================================================== GLOBAL DATA


// =========================================================================================== ADDITIONAL STATES API

void masks_setup_1_enter();
void masks_setup_1_exit();

void masks_setup_1_update();
void masks_setup_1_render(SDL_Renderer* renderer);


void masks_setup_2_enter();
void masks_setup_2_exit();

void masks_setup_2_update();
void masks_setup_2_render(SDL_Renderer* renderer);


void masks_setup_3_enter();
void masks_setup_3_exit();

void masks_setup_3_update();
void masks_setup_3_render(SDL_Renderer* renderer);


void masks_setup_4_enter();
void masks_setup_4_exit();

void masks_setup_4_update();
void masks_setup_4_render(SDL_Renderer* renderer);


void masks_setup_5_enter();
void masks_setup_5_exit();

void masks_setup_5_update();
void masks_setup_5_render(SDL_Renderer* renderer);


void masks_setup_6_enter();
void masks_setup_6_exit();

void masks_setup_6_update();
void masks_setup_6_render(SDL_Renderer* renderer);


// =========================================================================================== ADDITIONAL STATES API