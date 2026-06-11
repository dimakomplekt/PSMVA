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

    "1) Choose an videofile for analysis",
    "1) Выберете видео для анализа"

};

inline Lang_string_type gd_information_textbox_2 = {

    "2) Fill the file data and setup the masks by the faders",
    "2) Заполните информацию о файле и настройте маски при помощи фейдеров"

};

inline Lang_string_type gd_information_textbox_3 = {

    "3) Start an analysis and wait until the report will formed",
    "3) Запустите анализ и дождитесь формирования отчета"

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


// =========================================================================================== STATE 1.1 DICTIONARY

inline Lang_string_type gd_choose_the_file = {

    "Choose the files:",
    "Выберите файлы:"
    
};

// =========================================================================================== STATE 1.1 DICTIONARY
