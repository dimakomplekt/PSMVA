// global_data.h

#pragma once

// =========================================================================================== IMPORT

#include "program_dictionary/program_dictionary.h"

#include <SDL3/SDL.h>

// =========================================================================================== IMPORT


// =========================================================================================== GLOBAL WINDOW SETTINGS

// Main window horizontal size
#define MAIN_WINDOW_H_SIZE 1500 

// Main window vertical size
#define MAIN_WINDOW_V_SIZE 1000


// =========================================================================================== GLOBAL WINDOW SETTINGS


// =========================================================================================== FPS LIMITER

// FPS
extern const int TARGET_FPS;                // Change in CPP file
extern const Uint64 FRAME_TIME_MS;          // Autoset in CPP file based on TARGET_FPS

// Frame timing variables

extern Uint64 frame_start;
extern Uint64 frame_end;
extern Uint64 frame_duration;


// =========================================================================================== FPS LIMITER