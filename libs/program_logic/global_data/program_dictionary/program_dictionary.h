// program_dictionary.h

#pragma once


// =========================================================================================== IMPORT

#include "../../../engine/lang_state/lang_types.h"

// =========================================================================================== IMPORT


// =========================================================================================== STATE 0.0 DICTIONARY

// Could be not inline - replace with extern and define in cpp, but for simplicity - inline, as it's just a small 
// struct with const char* and no dynamic memory management

inline Lang_string_type gd_press_any_key = {

    "Press ENTER to continue...",
    "Нажмите ENTER для продолжения..."

};



// =========================================================================================== STATE 0.0 DICTIONARY


// =========================================================================================== STATE 1.0 DICTIONARY

// Could be not inline - replace with extern and define in cpp, but for simplicity - inline, as it's just a small 
// struct with const char* and no dynamic memory management

inline Lang_string_type gd_analysis_start_button = {

    "Analysis",
    "Анализ"

};


inline Lang_string_type gd_information_button = {

    "Information",
    "Информация"

};



inline Lang_string_type gd_information_textbox_1 = {

    "Information 1",
    "Информация 1"

};

inline Lang_string_type gd_information_textbox_2 = {

    "Information 2",
    "Информация 2"

};

inline Lang_string_type gd_information_textbox_3 = {

    "Information 3",
    "Информация 3"

};


inline Lang_string_type gd_settings_button = {

    "Settings",
    "Настройки"

};


inline Lang_string_type gd_exit_button = {

    "Exit",
    "Выход"

};





// =========================================================================================== STATE 1.0 DICTIONARY