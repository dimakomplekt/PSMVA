#pragma once

// =========================================================================================== IMPORT

#include <vector>
#include <string>
#include <utility> // for std::pair


#include "../../engine/engine.h"


// =========================================================================================== IMPORT


// =========================================================================================== STATE IDS

/**
 * @brief Unique hierarchical identifiers for all game states.
 *
 * Each ID defines the position of a state in the state machine hierarchy.
 * This makes it easy to determine parent-child relationships and manage
 * nested states.
 */
const State_ID START_ID                             = {0};           // Initial boot/start state
const State_ID MAIN_MENU_ID                         = {1};           // Main functions basic state
const State_ID FILE_CHOOSE_ID                       = {1, 1};        // File choose state
const State_ID MASKS_SETUP_ID                       = {1, 2};        // Masks setup state
const State_ID FLOW_PARAMETERS_CALCULATION_ID       = {1, 3};        // Flow parameters calculation state
const State_ID REPORT_FORMING_ID                    = {1, 4};        // Report forming state

const State_ID PROGRAM_END_ID                       = {2};           // Program exit state

/**
 * @brief Mapping of State_IDs to human-readable names.
 *
 * Useful for debugging, logging, or automatic state registration.
 */
const std::vector<std::pair<State_ID, std::string>> state_defs = {

    {{0},       "START"},                           // Просто запуск программы, загрузка чего-то, подготовка к работе
    {{1},       "MAIN_MENU"},                       // Дать возможность начать работу с программой или выйти
    {{1,1},     "FILE_CHOOSE"},                     // Меню выбора файлов для обработки    
    {{1,2},     "MASKS_SETUP"},                     // Меню выбора параметров масок для обработки видео        
    {{1,3},     "FLOW_PARAMETERS_CALCULATION"},     // Расчёт + статус бар + прогресс бар по каждому видео + сигнализация по успеху (с переходом вперед) неудаче (переход назад + лог)
    {{1,4},     "REPORT_FORMING"},                  // Формирование отчёта + выбор места сохранения + сигнализация об успехе + переход к следующему этапу
    {{2},       "PROGRAM_END"}                      // Сообщение о завершении работы + переход на этап MAIN_MENU при нажатии любой клавиши

};

// =========================================================================================== STATE IDS


// =========================================================================================== CALLBACKS

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

void start_enter();
void start_exit();
void start_render(SDL_Renderer* renderer);

void main_menu_enter();
void main_menu_exit();
void main_menu_render(SDL_Renderer* renderer);

void file_choose_enter();
void file_choose_exit();
void file_choose_render(SDL_Renderer* renderer);

void masks_setup_enter();
void masks_setup_exit();
void masks_setup_render(SDL_Renderer* renderer);

void flow_parameters_calculation_enter();
void flow_parameters_calculation_exit();
void flow_parameters_calculation_render(SDL_Renderer* renderer);

void report_forming_enter();
void report_forming_exit();
void report_forming_render(SDL_Renderer* renderer);


void program_end_enter();
void program_end_exit();
void program_end_render(SDL_Renderer* renderer);

// =========================================================================================== CALLBACKS


// =========================================================================================== INITIALIZATION

/**
 * @brief Initializes all game states and adds them to the state machine.
 *
 * - Creates State objects for each defined ID and name.
 * - Assigns the corresponding enter and exit callbacks.
 * - Automatically links parent and child states based on hierarchical IDs.
 *
 * @param app_state_machine Reference to the State_machine to populate.
 */
void init_game_states(State_machine& app_state_machine);

// =========================================================================================== INITIALIZATION
