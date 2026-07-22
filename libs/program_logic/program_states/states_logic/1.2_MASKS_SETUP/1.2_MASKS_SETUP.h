// 1.2_MASKS_SETUP.h


#pragma once

// =========================================================================================== IMPORT

#include "../../../../engine/engine.h"

#include "../../../../program_gui/basic_elements/global_palette/global_palette.h"
#include "../../../../program_gui/basic_elements/global_fonts/global_fonts.h"

#include "../../../global_data/global_data.h"

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