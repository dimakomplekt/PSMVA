// engine.h


#pragma once


// =========================================================================================== IMPORT

// Language state management (library contains links to language choose methods
// and program dictionary object)

#include "lang_state/lang_state.h"


// Current platform by preprocessor directives

#include "platform/platform.h"


// State machine include

#include "state_machine/state_machine.h"


// Includes both the frameworks and translation methods (library contains links 
// to both SDL3 and OpenCV2)

#include "special/opencv_to_sdl/opencv_to_sdl.h"

// SDL ttf include

#include "SDL3_ttf-3.1.0/include/SDL3_ttf/SDL_ttf.h"


// Mouse and keyboard read

#include "global_inputs/global_inputs.h" 

// =========================================================================================== IMPORT
