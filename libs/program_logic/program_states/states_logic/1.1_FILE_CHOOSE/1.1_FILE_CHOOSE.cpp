// 1.1_FILE_CHOOSE.cpp


// =========================================================================================== IMPORT

#include "1.1_FILE_CHOOSE.h"


#include "../../../../program_gui/basic_elements/UI_elements/my_sdl_textbox/my_sdl_textbox.h"
#include "../../../../program_gui/basic_elements/UI_elements/my_sdl_panel/my_sdl_panel.h"
#include "../../../../program_gui/basic_elements/UI_elements/my_sdl_button/my_sdl_button.h"
#include "../../../../program_gui/basic_elements/UI_elements/my_sdl_texture/my_sdl_texture.h"


// Predeclare for switching states
#include "../../program_states.h"

#include "../../../app.h"

// Log
#include <iostream>


// System file manager
#include <windows.h>
#include <commdlg.h>

// =========================================================================================== IMPORT


// =========================================================================================== STATE DATA

// RAII + lifecycle management

// Background
My_SDL_panel* File_choose_background_panel = nullptr;

// File choose panel (5 elements now)


My_SDL_panel* File_choose_panel = nullptr;

My_SDL_panel* File_1_panel = nullptr;
My_SDL_textbox* File_1_textbox = nullptr;
My_SDL_button* File_1_button = nullptr;


My_SDL_panel* File_2_panel = nullptr;
My_SDL_textbox* File_2_textbox = nullptr;
My_SDL_button* File_2_button = nullptr;


My_SDL_panel* File_3_panel = nullptr;
My_SDL_textbox* File_3_textbox = nullptr;
My_SDL_button* File_3_button = nullptr;


My_SDL_panel* File_4_panel = nullptr;
My_SDL_textbox* File_4_textbox = nullptr;
My_SDL_button* File_4_button = nullptr;


My_SDL_panel* File_5_panel = nullptr;
My_SDL_textbox* File_5_textbox = nullptr;
My_SDL_button* File_5_button = nullptr;


My_SDL_panel* File_6_panel = nullptr;
My_SDL_textbox* File_6_textbox = nullptr;
My_SDL_button* File_6_button = nullptr;


// Preview panel

My_SDL_panel* File_preview_panel = nullptr;
My_SDL_texture* File_preview_texture = nullptr;


// State control button

My_SDL_button* Study_start_button = nullptr;


// =========================================================================================== STATE DATA


// =========================================================================================== STATE INNER FUNCTIONS PREDECLARATION

void file_choose_elements_create();

void file_choose_elements_setup();

void file_choose_elements_free_and_nullptr();

void file_choose_elements_update();

void reset_passed_by_dictionary_textboxes_if_language_switched_fc();

void file_choose_actions();

void file_choose_elements_render(SDL_Renderer* renderer);

// =========================================================================================== STATE INNER FUNCTIONS PREDECLARATION


// =========================================================================================== MAIN STATE API


void file_choose_enter()
{
    // Log the enter in console
    std::cout << "Entering FILE_CHOOSE\n"; 

    // ===== State allocation =====

    file_choose_elements_create();

    // ===== State allocation =====


    // File choose data init

    file_choose_data_init();

    // Elements setup

    file_choose_elements_setup();

}



void file_choose_exit()
{
    // ===== State deallocation =====

    file_choose_elements_free_and_nullptr();

    // ===== State deallocation =====


    // Log the exit in console

    std::cout << "Exiting FILE_CHOOSE\n"; 

}


void file_choose_update()
{
    // Update inputs
    App_inputs.update();

    file_choose_elements_update();

    file_choose_actions();
}


void file_choose_render(SDL_Renderer* renderer)
{
    file_choose_elements_render(renderer);
}


// =========================================================================================== MAIN STATE API


// =========================================================================================== STATE INNER FUNCTIONS REALIZATION

void file_choose_elements_create()
{
    // Background
    File_choose_background_panel = new My_SDL_panel;


    // File choose panel (5 elements now)

    File_choose_panel = new My_SDL_panel;


    File_1_panel = new My_SDL_panel;
    File_1_textbox = new My_SDL_textbox;
    File_1_button = new My_SDL_button;

    File_2_panel = new My_SDL_panel;
    File_2_textbox = new My_SDL_textbox;
    File_2_button = new My_SDL_button;

    File_3_panel = new My_SDL_panel;
    File_3_textbox = new My_SDL_textbox;
    File_3_button = new My_SDL_button;

    File_4_panel = new My_SDL_panel;
    File_4_textbox = new My_SDL_textbox;
    File_4_button = new My_SDL_button;

    File_5_panel = new My_SDL_panel;
    File_5_textbox = new My_SDL_textbox;
    File_5_button = new My_SDL_button;

    File_6_panel = new My_SDL_panel;
    File_6_textbox = new My_SDL_textbox;
    File_6_button = new My_SDL_button;


    // Preview panel

    File_preview_panel = new My_SDL_panel;
    // File_preview_texture = new My_SDL_texture;


    // State control button

    Study_start_button = new My_SDL_button;
}


// ===== SETUP DATA =====

// ===== Main sizes =====

// Static-size GUI

const int BACKGROUND_WIDTH  = MAIN_WINDOW_H_SIZE;
const int BACKGROUND_HEIGHT  = MAIN_WINDOW_V_SIZE;

const int FIRST_ZONE_WIDTH = static_cast<int>(MAIN_WINDOW_H_SIZE * 0.5);
const int SECOND_ZONE_WIDTH = MAIN_WINDOW_H_SIZE - FIRST_ZONE_WIDTH;

const int SCREEN_MARGIN_1 = 50;
const int SCREEN_MARGIN_2 = 50;

const int file_choose_panel_width = (FIRST_ZONE_WIDTH  - 1.5 * SCREEN_MARGIN_1);
const int file_choose_panel_height = (BACKGROUND_HEIGHT - 2 * SCREEN_MARGIN_2);


const int mini_panels_margin = 25;

const int file_choose_mini_panels_width = file_choose_panel_width - 2 * mini_panels_margin;
const int file_choose_mini_panels_height = (file_choose_panel_height - 7 * mini_panels_margin) / 6;

const int file_choose_buttons_width = file_choose_mini_panels_width * 0.2;
const int file_choose_buttons_height = file_choose_mini_panels_height;


const int file_preview_width = (SECOND_ZONE_WIDTH  - 1.5 * SCREEN_MARGIN_1);
const int file_preview_height = (BACKGROUND_HEIGHT - 3 * SCREEN_MARGIN_2) * 0.7;

const int study_start_button_width = file_preview_width;
const int study_start_button_height = (BACKGROUND_HEIGHT - 3 * SCREEN_MARGIN_2) - file_preview_height;



// ====== Main points ======

int file_choose_background_x = MAIN_WINDOW_H_SIZE * 0.5;
int file_choose_background_y = MAIN_WINDOW_V_SIZE * 0.5;


int file_choose_panel_x = FIRST_ZONE_WIDTH * 0.5;
int file_choose_panel_y = BACKGROUND_HEIGHT * 0.5;


int file_choose_preview_x = FIRST_ZONE_WIDTH + SECOND_ZONE_WIDTH * 0.5;
int file_choose_preview_y = SCREEN_MARGIN_2 + file_preview_height * 0.5;

int study_start_button_x = file_choose_preview_x; 
int study_start_button_y = BACKGROUND_HEIGHT - SCREEN_MARGIN_2 - 0.5 * study_start_button_height; 


// ===== SETUP DATA =====

// ===== CALLBACKS FOR BUTTONS =====

void file_choose_or_clear(int file_number);

void study_start();

bool check_start_study_access();

// ===== CALLBACKS FOR BUTTONS =====


void file_choose_elements_setup()
{     
    // ===== Setup =====

    // Background setup

    File_choose_background_panel->set_render_point(file_choose_background_x, file_choose_background_y);
    File_choose_background_panel->set_size(BACKGROUND_WIDTH, BACKGROUND_HEIGHT);
    File_choose_background_panel->set_border_radius(0);
    

    // File choose panel
    File_choose_panel->set_render_point(file_choose_panel_x, file_choose_panel_y);
    File_choose_panel->set_size(file_choose_panel_width, file_choose_panel_height);
    File_choose_panel->set_border_radius(mini_panels_margin + 10);


    // 1st file choose
    File_1_panel->set_size(file_choose_mini_panels_width , file_choose_mini_panels_height);
    
    File_1_textbox->switch_textbox_type(HEADER_3);
    File_1_textbox->set_content("File 1");

    File_1_button->switch_button_textbox_type(HEADER_3);
    File_1_button->get_button_content_textbox()->set_content("+");
    File_1_button->set_size(file_choose_buttons_width, file_choose_buttons_height);

    // Lambda for callback with args
    File_1_button->on_click = []() { file_choose_or_clear(1); };

    File_1_button->switch_push_mode();
    File_1_panel->set_border_radius(10);
    File_1_button->set_border_radius(10);


    // 2nd file choose
    File_2_panel->set_size(file_choose_mini_panels_width , file_choose_mini_panels_height);

    File_2_textbox->switch_textbox_type(HEADER_3);
    File_2_textbox->set_content("");

    File_2_button->switch_button_textbox_type(HEADER_3);
    File_2_button->get_button_content_textbox()->set_content("+");
    File_2_button->set_size(file_choose_buttons_width, file_choose_buttons_height);

    File_2_button->on_click = []() { file_choose_or_clear(2); };

    File_2_button->switch_push_mode();
    File_2_panel->set_border_radius(10);
    File_2_button->set_border_radius(10);


    // 3rd file choose
    File_3_panel->set_size(file_choose_mini_panels_width , file_choose_mini_panels_height);

    File_3_textbox->switch_textbox_type(HEADER_3);
    File_3_textbox->set_content("");

    File_3_button->switch_button_textbox_type(HEADER_3);
    File_3_button->get_button_content_textbox()->set_content("+");
    File_3_button->set_size(file_choose_buttons_width, file_choose_buttons_height);
    File_3_button->on_click = []() { file_choose_or_clear(3); };

    File_3_button->switch_push_mode();
    File_3_panel->set_border_radius(10);
    File_3_button->set_border_radius(10);


    // 4th file choose
    File_4_panel->set_size(file_choose_mini_panels_width , file_choose_mini_panels_height);

    File_4_textbox->switch_textbox_type(HEADER_3);
    File_4_textbox->set_content("");

    File_4_button->switch_button_textbox_type(HEADER_3);
    File_4_button->get_button_content_textbox()->set_content("+");
    File_4_button->set_size(file_choose_buttons_width, file_choose_buttons_height);
    File_4_button->on_click = []() { file_choose_or_clear(4); };

    File_4_button->switch_push_mode();
    File_4_panel->set_border_radius(10);
    File_4_button->set_border_radius(10);


    // 5th file choose
    File_5_panel->set_size(file_choose_mini_panels_width , file_choose_mini_panels_height);

    File_5_textbox->switch_textbox_type(HEADER_3);
    File_5_textbox->set_content("");

    File_5_button->switch_button_textbox_type(HEADER_3);
    File_5_button->get_button_content_textbox()->set_content("+");
    File_5_button->set_size(file_choose_buttons_width, file_choose_buttons_height);
    File_5_button->on_click = []() { file_choose_or_clear(5); };

    File_5_button->switch_push_mode();
    File_5_panel->set_border_radius(10);
    File_5_button->set_border_radius(10);

    // 6th file choose
    File_6_panel->set_size(file_choose_mini_panels_width , file_choose_mini_panels_height);

    File_6_textbox->switch_textbox_type(HEADER_3);
    File_6_textbox->set_content("");

    File_6_button->switch_button_textbox_type(HEADER_3);
    File_6_button->get_button_content_textbox()->set_content("+");
    File_6_button->set_size(file_choose_buttons_width, file_choose_buttons_height);
    File_6_button->on_click = []() { file_choose_or_clear(6); };

    File_6_button->switch_push_mode();
    File_6_panel->set_border_radius(10);
    File_6_button->set_border_radius(10);


    // Put elements in panels

    // File 1 choose

    File_1_panel->add_element(

        File_1_textbox,
        (file_choose_mini_panels_width - file_choose_buttons_width) / 2,       // Плохо - текст плавает или не задан
        file_choose_mini_panels_height * 0.5,
        1

    );

    File_1_panel->add_element(

        File_1_button,
        file_choose_mini_panels_width - 0.5 * file_choose_buttons_width,
        file_choose_mini_panels_height * 0.5,
        1

    );


    File_choose_panel->add_element(

        File_1_panel,
        file_choose_panel_width * 0.5, // Centered with equal margin
        1 * mini_panels_margin + 0.5 * file_choose_mini_panels_height,
        1

    );

    // File 2 choose
    
    File_2_panel->add_element(

        File_2_textbox,
        (file_choose_mini_panels_width - file_choose_buttons_width) * 0.5,
        file_choose_mini_panels_height * 0.5,
        1

    );

    File_2_panel->add_element(

        File_2_button,
        file_choose_mini_panels_width - 0.5 * file_choose_buttons_width,
        file_choose_mini_panels_height * 0.5,
        1

    );


    File_choose_panel->add_element(

        File_2_panel,
        file_choose_panel_width * 0.5, // Centered with equal margin
        2 * mini_panels_margin + 1.5 * file_choose_mini_panels_height,
        1

    );

    // File 3 choose

    File_3_panel->add_element(

        File_3_textbox,
        (file_choose_mini_panels_width - file_choose_buttons_width) * 0.5,
        file_choose_mini_panels_height * 0.5,
        1

    );

    File_3_panel->add_element(

        File_3_button,
        file_choose_mini_panels_width - 0.5 * file_choose_buttons_width,
        file_choose_mini_panels_height * 0.5,
        1

    );


    File_choose_panel->add_element(

        File_3_panel,
        file_choose_panel_width * 0.5, // Centered with equal margin
        3 * mini_panels_margin + 2.5 * file_choose_mini_panels_height,
        1

    );

    // File 4 choose

    File_4_panel->add_element(

        File_4_textbox,
        (file_choose_mini_panels_width - file_choose_buttons_width) * 0.5,
        file_choose_mini_panels_height * 0.5,
        1

    );

    File_4_panel->add_element(

        File_4_button,
        file_choose_mini_panels_width - 0.5 * file_choose_buttons_width,
        file_choose_mini_panels_height * 0.5,
        1

    );


    File_choose_panel->add_element(

        File_4_panel,
        file_choose_panel_width * 0.5, // Centered with equal margin
        4 * mini_panels_margin + 3.5 * file_choose_mini_panels_height,
        1

    );

    // File 5 choose

    File_5_panel->add_element(

        File_5_textbox,
        (file_choose_mini_panels_width - file_choose_buttons_width) * 0.5,
        file_choose_mini_panels_height * 0.5,
        1

    );

    File_5_panel->add_element(

        File_5_button,
        file_choose_mini_panels_width - 0.5 * file_choose_buttons_width,
        file_choose_mini_panels_height * 0.5,
        1

    );


    File_choose_panel->add_element(

        File_5_panel,
        file_choose_panel_width * 0.5, // Centered with equal margin
        5 * mini_panels_margin + 4.5 * file_choose_mini_panels_height,
        1

    );

    // File 6 choose

    File_6_panel->add_element(

        File_6_textbox,
        (file_choose_mini_panels_width - file_choose_buttons_width) * 0.5,
        file_choose_mini_panels_height * 0.5,
        1

    );

    File_6_panel->add_element(

        File_6_button,
        file_choose_mini_panels_width - 0.5 * file_choose_buttons_width,
        file_choose_mini_panels_height * 0.5,
        1

    );


    File_choose_panel->add_element(

        File_6_panel,
        file_choose_panel_width * 0.5, // Centered with equal margin
        6 * mini_panels_margin + 5.5 * file_choose_mini_panels_height,
        1

    );

    // Deactivate panels
    File_2_panel->set_visible_flag(false);
    File_3_panel->set_visible_flag(false);
    File_4_panel->set_visible_flag(false);
    File_5_panel->set_visible_flag(false);
    File_6_panel->set_visible_flag(false);



    // Preview panel
    File_preview_panel->set_size(file_preview_width, file_preview_height);
    File_preview_panel->set_render_point(file_choose_preview_x, file_choose_preview_y);
    File_preview_panel->set_border_radius(mini_panels_margin + 10);

    // Texture
    //

    // Study start button

    Study_start_button->switch_button_textbox_type(HEADER_2);
    Study_start_button->get_button_content_textbox()->set_content(str_by_dictionary(gd_study_start));
    Study_start_button->set_size(study_start_button_width, study_start_button_height);
    Study_start_button->set_render_point(study_start_button_x, study_start_button_y);

    Study_start_button->on_click = study_start;

    Study_start_button->extern_click_permission = check_start_study_access;
    Study_start_button->set_access_type(BUTTON_EXTERN_CLICK_PERMISSION);

    Study_start_button->set_border_radius(mini_panels_margin + 10);
}


void file_choose_elements_free_and_nullptr()
{
    // Protection
    if (File_choose_background_panel == nullptr) return;


    // ===== Free all elements =====

    // Background
    File_choose_background_panel->delete_element();


    // File choose panel (5 elements now)

    File_choose_panel->delete_element();

    // Preview panel

    File_preview_panel->delete_element();


    // State control button

    Study_start_button->delete_element();
    

    // ===== Nullptr the pointers =====

    // Background
    File_choose_background_panel = nullptr;


    // File choose panel (5 elements now)

    File_choose_panel = nullptr;

    File_1_panel = nullptr;
    File_1_textbox = nullptr;
    File_1_button = nullptr;

    File_2_panel = nullptr;
    File_2_textbox = nullptr;
    File_2_button = nullptr;

    File_3_panel = nullptr;
    File_3_textbox = nullptr;
    File_3_button = nullptr;

    File_4_panel = nullptr;
    File_4_textbox = nullptr;
    File_4_button = nullptr;

    File_5_panel = nullptr;
    File_5_textbox = nullptr;
    File_5_button = nullptr;

    File_6_panel = nullptr;
    File_6_textbox = nullptr;
    File_6_button = nullptr;


    // Preview panel

    File_preview_panel = nullptr;
    File_preview_texture = nullptr;


    // State control button

    Study_start_button = nullptr;

}


void file_choose_elements_update()
{
    // ===== Check if textboxes need content renew =====

    reset_passed_by_dictionary_textboxes_if_language_switched_fc();


    // ===== Update all elements =====

    // Background
    File_choose_background_panel->update();

    // File choose panel (5 elements now)

    File_choose_panel->update();

    // Preview panel

    File_preview_panel->update();

    
    // State control button

    Study_start_button->update();
        
}


void reset_passed_by_dictionary_textboxes_if_language_switched_fc()
{
    // Repeat content set if language switched
    if (App_lang.get_lang_reset_flag())
    {
        // Textboxes for update




    }
}


void file_choose_actions()
{
    // State actions
}


void file_choose_elements_render(SDL_Renderer* renderer)
{
    // Render all elements

    // Background
    File_choose_background_panel->render(renderer);

    
    // File choose panel (5 elements now)

    File_choose_panel->render(renderer);

    // Preview panel

    File_preview_panel->render(renderer);

    
    // State control button

    Study_start_button->render(renderer);
}

// =========================================================================================== STATE INNER FUNCTIONS REALIZATION


// =========================================================================================== STATE ELEMENTS INNER FUNCTIONS


void file_choose_data_init()
{
    file_choose_data.file_1_path = "";
    file_choose_data.file_2_path = "";
    file_choose_data.file_3_path = "";
    file_choose_data.file_4_path = "";
    file_choose_data.file_5_path = "";
    file_choose_data.file_6_path = "";


    file_choose_data.panels_states.file_1_panel_state = file_choose_panel_state::EMPTY_STATE;
    file_choose_data.panels_states.file_2_panel_state = file_choose_panel_state::HIDDEN_STATE;
    file_choose_data.panels_states.file_3_panel_state = file_choose_panel_state::HIDDEN_STATE;
    file_choose_data.panels_states.file_4_panel_state = file_choose_panel_state::HIDDEN_STATE;
    file_choose_data.panels_states.file_5_panel_state = file_choose_panel_state::HIDDEN_STATE;
    file_choose_data.panels_states.file_6_panel_state = file_choose_panel_state::HIDDEN_STATE;

}


std::string utf16_to_utf8(const std::wstring& wstr)
{
    if (wstr.empty())
        return "";

    int size_needed = WideCharToMultiByte(
        CP_UTF8,
        0,
        wstr.c_str(),
        -1,
        nullptr,
        0,
        nullptr,
        nullptr
    );

    std::string result(size_needed - 1, '\0');

    WideCharToMultiByte(
        CP_UTF8,
        0,
        wstr.c_str(),
        -1,
        result.data(),
        size_needed,
        nullptr,
        nullptr
    );

    return result;
}


std::string file_name_from_path(std::string path)
{


    // Find the last slash (Windows '\' or Unix '/')
    size_t last_slash_idx = path.find_last_of("\\/");
    
    // Return the substring before slash
    // std::string::npos - special constant, which returned if there is no slashes 
    // inside the link
    if (std::string::npos != last_slash_idx)
    {
        return path.substr(last_slash_idx + 1);
    }
    
    // No slashes or EMPTY_STATE case
    return path;

    // Same by library
    // return std::filesystem::path(path).filename().string();
}



std::string get_path_by_file_manager()
{
    // For cyrillic
    wchar_t file_name[MAX_PATH] = L"";

    OPENFILENAMEW ofn;
    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);

    // We may pass SDL-window descriptor, but NULL works as well
    ofn.hwndOwner = NULL;
    
    // File filter
    ofn.lpstrFilter =
        L"All files (*.*)\0*.*\0"
        L"Txt files (*.txt)\0*.txt\0";

    ofn.lpstrFile = file_name;
    ofn.nMaxFile = MAX_PATH;
    
    // Flags: file should exists, path must be valid

    ofn.Flags =
        OFN_EXPLORER |
        OFN_FILEMUSTEXIST |
        OFN_HIDEREADONLY;


    // Calls the window, returns the path, if user choosed the path
    if (GetOpenFileNameW(&ofn))
    {
        return utf16_to_utf8(file_name);
    }

    return ""; // User closed the window or error occures
}


void add_path(unsigned int file_number)
{

    // Check if rebuild is needed
    if (file_number == 0) return;

    unsigned int add_index = file_number - 1;

    // Massive of variables links
    std::string* paths[] = {

        &file_choose_data.file_1_path,
        &file_choose_data.file_2_path,
        &file_choose_data.file_3_path,
        &file_choose_data.file_4_path,
        &file_choose_data.file_5_path,
        &file_choose_data.file_6_path

    };

    file_choose_panel_state* panel_states[] = {

        &file_choose_data.panels_states.file_1_panel_state,
        &file_choose_data.panels_states.file_2_panel_state,
        &file_choose_data.panels_states.file_3_panel_state,
        &file_choose_data.panels_states.file_4_panel_state,
        &file_choose_data.panels_states.file_5_panel_state,
        &file_choose_data.panels_states.file_6_panel_state

    };

    if (*panel_states[add_index] != file_choose_panel_state::EMPTY_STATE) std::cerr << "Error on the file pass!";

    std::string selected_path = get_path_by_file_manager();

    if (selected_path.empty())
    {
        return;
    }
    
    *paths[add_index] = selected_path;
    *panel_states[add_index] = file_choose_panel_state::CHOSEN_STATE;
    
    // Show next panel
    if (add_index < 5)
    {
        *panel_states[add_index + 1] = file_choose_panel_state::EMPTY_STATE;
    }
    
    // Reset panels textboxes content according to the new list
    File_1_textbox->set_content(file_name_from_path(file_choose_data.file_1_path));
    File_2_textbox->set_content(file_name_from_path(file_choose_data.file_2_path));
    File_3_textbox->set_content(file_name_from_path(file_choose_data.file_3_path));
    File_4_textbox->set_content(file_name_from_path(file_choose_data.file_4_path));
    File_5_textbox->set_content(file_name_from_path(file_choose_data.file_5_path));
    File_6_textbox->set_content(file_name_from_path(file_choose_data.file_6_path));

}


void clear_path(unsigned int file_number)
{
    // Clear file index
    int cleared_idx = file_number - 1;

    // Massive of variables links
    std::string* paths[] = {

        &file_choose_data.file_1_path,
        &file_choose_data.file_2_path,
        &file_choose_data.file_3_path,
        &file_choose_data.file_4_path,
        &file_choose_data.file_5_path,
        &file_choose_data.file_6_path

    };


    file_choose_panel_state* panel_states[] = {

        &file_choose_data.panels_states.file_1_panel_state,
        &file_choose_data.panels_states.file_2_panel_state,
        &file_choose_data.panels_states.file_3_panel_state,
        &file_choose_data.panels_states.file_4_panel_state,
        &file_choose_data.panels_states.file_5_panel_state,
        &file_choose_data.panels_states.file_6_panel_state

    };


    // Move the names
    if (cleared_idx >= 0 && cleared_idx < 6)
    {
        // From the deleted one
        for (int i = cleared_idx; i < 5; ++i)
        {
            *paths[i] = *paths[i + 1];
        }

        // EMPTY_STATE string to the last one (previos becomes EMPTY_STATE automatically
        // during the iteration loop)
        *paths[5] = "";
    }

    // Reset panels textboxes content according to the new list
    File_1_textbox->set_content(file_name_from_path(file_choose_data.file_1_path));
    File_2_textbox->set_content(file_name_from_path(file_choose_data.file_2_path));
    File_3_textbox->set_content(file_name_from_path(file_choose_data.file_3_path));
    File_4_textbox->set_content(file_name_from_path(file_choose_data.file_4_path));
    File_5_textbox->set_content(file_name_from_path(file_choose_data.file_5_path));
    File_6_textbox->set_content(file_name_from_path(file_choose_data.file_6_path));


    // Reset statuses
    // TODO:: RESET LOOGIC TO CORRECT ONE!!!
    if ((cleared_idx >= 0 && cleared_idx < 6) && panel_states[cleared_idx + 1])
    {
        // From the deleted one
        for (int i = cleared_idx; i < 5; ++i)
        {
            *panel_states[i] = *panel_states[i + 1];
        }

        // HIDE last one (previos becomes HIDDEN_STATE automatically
        // during the iteration loop)
        *panel_states[5] = file_choose_panel_state::HIDDEN_STATE;

        if (*panel_states[0] == file_choose_panel_state::HIDDEN_STATE) *panel_states[0] = file_choose_panel_state::EMPTY_STATE;
    }

}


void file_choose_or_clear(int file_number)
{
    // EH
    if (file_number < 1 || file_number > 6) return;


    // Clear file index
    int cleared_idx = file_number - 1;


    file_choose_panel_state* panel_states[] = {

        &file_choose_data.panels_states.file_1_panel_state,
        &file_choose_data.panels_states.file_2_panel_state,
        &file_choose_data.panels_states.file_3_panel_state,
        &file_choose_data.panels_states.file_4_panel_state,
        &file_choose_data.panels_states.file_5_panel_state,
        &file_choose_data.panels_states.file_6_panel_state

    };

    bool add = false;
    bool clear = false;

    if (*panel_states[cleared_idx] == file_choose_panel_state::EMPTY_STATE) add = true;
    else if (*panel_states[cleared_idx] == file_choose_panel_state::CHOSEN_STATE) clear = true;

    if (add)
    {
        add_path(file_number);
    }

    if (clear)
    {
        clear_path(file_number);
    }


    // Set new textboxes

    My_SDL_button* buttons[] = {

        File_1_button,
        File_2_button,
        File_3_button,
        File_4_button,
        File_5_button,
        File_6_button

    };

    My_SDL_panel* panels[] = {

        File_1_panel,
        File_2_panel,
        File_3_panel,
        File_4_panel,
        File_5_panel,
        File_6_panel

    };


    for (int i = 0; i <= 5; i++)
    {
        if (*panel_states[i] == file_choose_panel_state::EMPTY_STATE) 
        {
            buttons[i]->get_button_content_textbox()->set_content("+");
            
            panels[i]->set_visible_flag(true);
        }

        else if (*panel_states[i] == file_choose_panel_state::CHOSEN_STATE)
        {
            buttons[i]->get_button_content_textbox()->set_content("X");

            panels[i]->set_visible_flag(true);
        }

        else panels[i]->set_visible_flag(false);
    }


    // Check
    std::cout << file_choose_data.file_1_path << "\n" << std::endl;
    std::cout << file_choose_data.file_2_path << "\n" << std::endl;
    std::cout << file_choose_data.file_3_path << "\n" << std::endl;
    std::cout << file_choose_data.file_4_path << "\n" << std::endl;
    std::cout << file_choose_data.file_5_path << "\n" << std::endl;
    std::cout << file_choose_data.file_6_path << "\n" << std::endl;
    std::cout << static_cast<int>(file_choose_data.panels_states.file_1_panel_state) << "\n" << std::endl;
    std::cout << static_cast<int>(file_choose_data.panels_states.file_2_panel_state) << "\n" << std::endl;
    std::cout << static_cast<int>(file_choose_data.panels_states.file_3_panel_state) << "\n" << std::endl;
    std::cout << static_cast<int>(file_choose_data.panels_states.file_4_panel_state) << "\n" << std::endl;
    std::cout << static_cast<int>(file_choose_data.panels_states.file_5_panel_state) << "\n" << std::endl;
    std::cout << static_cast<int>(file_choose_data.panels_states.file_6_panel_state) << "\n" << std::endl;
}


void study_start()
{
    //
}


bool check_start_study_access()
{
    if (

        file_choose_data.panels_states.file_1_panel_state == file_choose_panel_state::CHOSEN_STATE &&
        file_choose_data.panels_states.file_2_panel_state == file_choose_panel_state::CHOSEN_STATE &&
        file_choose_data.panels_states.file_3_panel_state == file_choose_panel_state::CHOSEN_STATE &&
        file_choose_data.panels_states.file_4_panel_state == file_choose_panel_state::CHOSEN_STATE &&
        file_choose_data.panels_states.file_5_panel_state == file_choose_panel_state::CHOSEN_STATE &&
        file_choose_data.panels_states.file_6_panel_state == file_choose_panel_state::CHOSEN_STATE 
    
    ) return true;

    else return false;
}


// =========================================================================================== STATE ELEMENTS INNER FUNCTIONS
