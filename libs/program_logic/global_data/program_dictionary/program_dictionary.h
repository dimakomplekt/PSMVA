// program_dictionary.h

#pragma once


// =========================================================================================== IMPORT

#include "../../../engine/lang_state/lang_types.h"

// =========================================================================================== IMPORT


// =========================================================================================== STATE 0.0 DICTIONARY

// Could be not inline - replace with extern and define in cpp, but for simplicity - inline, as it's just a small 
// struct with const char* and no dynamic memory management

inline Lang_string_type gd_press_any_key = {

    "Press any key to continue...",
    "Нажмите любую клавишу для продолжения..."

};

// =========================================================================================== STATE 0.0 DICTIONARY
