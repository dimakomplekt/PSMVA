// 1.1_FILE_CHOOSE.h


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

void file_choose_enter();
void file_choose_exit();

void file_choose_update();
void file_choose_render(SDL_Renderer* renderer);

// =========================================================================================== MAIN STATE API


// =========================================================================================== FILE CHOOSE GLOBAL DATA

enum class file_choose_panel_state 
{

    HIDEN,
    EMPTY,
    CHOSEN

};


typedef struct
{

    file_choose_panel_state file_1_panel_state;
    file_choose_panel_state file_2_panel_state;
    file_choose_panel_state file_3_panel_state;
    file_choose_panel_state file_4_panel_state;
    file_choose_panel_state file_5_panel_state;
    file_choose_panel_state file_6_panel_state;

} file_choose_panel_states;


typedef struct
{

    std::string file_1_path;
    std::string file_2_path;
    std::string file_3_path;
    std::string file_4_path;
    std::string file_5_path;
    std::string file_6_path;


    file_choose_panel_states panels_states;

} file_choose_ctx;


// Data for file choose - used for files access during the whole analysis (untill the new one)
file_choose_ctx file_choose_data;


// Calles at the file choose state enter (cause we use the same data through the whole analysis, 
// so we just reset values to default ones)  
void file_choose_data_init();

// =========================================================================================== FILE CHOOSE GLOBAL DATA
