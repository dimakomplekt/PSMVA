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
