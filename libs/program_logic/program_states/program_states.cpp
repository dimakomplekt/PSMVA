// game_states.cpp


// =========================================================================================== IMPORT

#include "program_states.h"
#include <iostream> // for std::cout, std::cerr

#include "../../program_gui/basic_elements/UI_elements/my_sdl_button/my_sdl_button.h"

// =========================================================================================== IMPORT


// =========================================================================================== CALLBACKS


// Это пример, сами функции будут лежать в своих либах или модулях, тут объявление и присвоение коллбеков 

// These are the callbacks executed when entering or exiting a state.
// Currently, they are simple stubs printing to the console.
// You can replace the body with more complex logic or calls to other modules.

// Button
My_SDL_button Button_1;

void cout_on_but_1_click()
{
    std::cout << "Button_1 is clicked... Finally." << std::endl;
}


void start_enter()
{
    std::cout << "Entering START\n";

    // Button 1 initialization
    Button_1.on_click = cout_on_but_1_click;
    Button_1.set_font_path(Button_1.get_font_path());
}


void start_exit()          { std::cout << "Exiting START\n"; }

void start_update()
{
    App_mouse.update();
    Button_1.update();
}

void start_render(SDL_Renderer* renderer)
{
    // Button 1
    Button_1.render(renderer);

    // Рисуем красный круг для чека работоспособности
    SDL_SetRenderDrawColor(renderer, 255, 100, 50, 255);

    int cx = 400, cy = 300, r = 50;

    for (int w = 0; w < r * 2; w++)
    {
        for (int h = 0; h < r * 2; h++)
        {
            int dx = r - w;
            int dy = r - h;

            if ((dx*dx + dy*dy) <= (r*r)) SDL_RenderPoint(renderer, cx + dx, cy + dy);
        }
    }
}


// =========================================================================================== MAIN MENU

/**
 * @brief Enter MAIN_MENU state.
 *
 * Инициализация главного меню:
 * - сброс временных данных
 * - подготовка UI
 */
void main_menu_enter()
{
    // TODO:
    // - Инициализировать элементы GUI (кнопки: "Начать", "Выход")
    // - Сбросить временные данные предыдущей сессии (если нужно)
    // - Подготовить ресурсы (текстуры, шрифты и т.д.)
}

/**
 * @brief Exit MAIN_MENU state.
 *
 * Очистка ресурсов главного меню.
 */
void main_menu_exit()
{
    // TODO:
    // - Освободить UI ресурсы
    // - Сохранить состояние (если требуется)
}

/**
 * @brief Render MAIN_MENU state.
 *
 * Отрисовка главного меню:
 * - кнопки
 * - фон
 * - подсказки
 */
void main_menu_render(SDL_Renderer* renderer)
{
    // TODO:
    // - Отрисовать фон
    // - Отрисовать кнопки ("Начать", "Выход")
    // - Обработать визуальные состояния (hover, click)
}


// =========================================================================================== FILE CHOOSE

/**
 * @brief Enter FILE_CHOOSE state.
 *
 * Подготовка выбора файлов:
 * - открытие диалога
 * - сброс выбранных файлов
 */
void file_choose_enter()
{
    // TODO:
    // - Открыть файловый диалог (или подготовить кнопку вызова)
    // - Очистить список выбранных файлов
    // - Подготовить UI
}

/**
 * @brief Exit FILE_CHOOSE state.
 *
 * Завершение выбора файлов.
 */
void file_choose_exit()
{
    // TODO:
    // - Проверить валидность выбранных файлов
    // - Сохранить пути и метаданные
}

/**
 * @brief Render FILE_CHOOSE state.
 *
 * Отрисовка интерфейса выбора файлов:
 * - список файлов
 * - кнопки выбора
 */
void file_choose_render(SDL_Renderer* renderer)
{
    // TODO:
    // - Отрисовать список выбранных файлов
    // - Отрисовать кнопку "Добавить файл"
    // - Отобразить подсказки
}


// =========================================================================================== MASKS SETUP

/**
 * @brief Enter MASKS_SETUP state.
 *
 * Подготовка настройки масок:
 * - загрузка видео
 * - инициализация параметров
 */
void masks_setup_enter()
{
    // TODO:
    // - Загрузить выбранные видео
    // - Инициализировать параметры масок
    // - Подготовить UI (слайдеры, переключатели)
}

/**
 * @brief Exit MASKS_SETUP state.
 *
 * Сохранение настроек масок.
 */
void masks_setup_exit()
{
    // TODO:
    // - Проверить заполненность параметров
    // - Сохранить настройки (в память или файл)
}

/**
 * @brief Render MASKS_SETUP state.
 *
 * Отрисовка:
 * - оригинального видео
 * - результата маски
 * - элементов управления
 */
void masks_setup_render(SDL_Renderer* renderer)
{
    // TODO:
    // - Отрисовать видео (оригинал)
    // - Отрисовать маску (результат обработки)
    // - Отрисовать слайдеры и переключатели
}


// =========================================================================================== FLOW PARAMETERS CALCULATION

/**
 * @brief Enter FLOW_PARAMETERS_CALCULATION state.
 *
 * Запуск расчётов:
 * - инициализация алгоритмов
 * - подготовка прогресса
 */
void flow_parameters_calculation_enter()
{
    // TODO:
    // - Инициализировать обработку видео
    // - Запустить расчёт (возможно в отдельном потоке)
    // - Подготовить структуру прогресса
}

/**
 * @brief Exit FLOW_PARAMETERS_CALCULATION state.
 *
 * Завершение расчётов.
 */
void flow_parameters_calculation_exit()
{
    // TODO:
    // - Проверить завершение обработки
    // - Сохранить результаты
    // - Обработать ошибки (если были)
}

/**
 * @brief Render FLOW_PARAMETERS_CALCULATION state.
 *
 * Отрисовка прогресса:
 * - progress bar
 * - статус по этапам
 */
void flow_parameters_calculation_render(SDL_Renderer* renderer)
{
    // TODO:
    // - Отрисовать progress bar / status bar для каждого видео
    // - Отрисовать сигнализацию об успехе или неудаче (вывести лог ошибок при неудаче)
}


// =========================================================================================== REPORT FORMING

/**
 * @brief Enter REPORT_FORMING state.
 *
 * Подготовка отчёта:
 * - получение результатов
 * - выбор пути сохранения
 */
void report_forming_enter()
{
    // TODO:
    // - Получить результаты расчётов
    // - Подготовить структуру отчёта
    // - Запросить путь сохранения
}

/**
 * @brief Exit REPORT_FORMING state.
 *
 * Завершение формирования отчёта.
 */
void report_forming_exit()
{
    // TODO:
    // - Проверить успешность сохранения
    // - Очистить временные данные
}

/**
 * @brief Render REPORT_FORMING state.
 *
 * Отрисовка:
 * - формы сохранения
 * - статуса генерации
 */
void report_forming_render(SDL_Renderer* renderer)
{
    // TODO:
    // - Отрисовать форму ввода имени файла
    // - Отобразить статус генерации
}


// =========================================================================================== PROGRAM END

/**
 * @brief Enter PROGRAM_END state.
 *
 * Завершение работы:
 * - уведомление пользователя
 */
void program_end_enter()
{
    // TODO:
    // - Показать сообщение о завершении
    // - Подготовить возврат в MAIN_MENU при нажатии любой кнопки
}

/**
 * @brief Exit PROGRAM_END state.
 *
 * Очистка перед возвратом.
 */
void program_end_exit()
{
    // TODO:
    // - Очистить ресурсы
}

/**
 * @brief Render PROGRAM_END state.
 *
 * Отрисовка финального экрана:
 * - сообщение
 * - инструкция (нажмите любую клавишу)
 */
void program_end_render(SDL_Renderer* renderer)
{
    // TODO:
    // - Отрисовать сообщение "Работа завершена"
    // - Отобразить подсказку для возврата в MAIN_MENU при нажатии любой клавиши
}


// =========================================================================================== CALLBACKS


// =========================================================================================== INITIALIZATION

void init_program_states(State_machine& app_state_machine)
{
    // Each block below creates a State object, assigns its enter/exit callbacks,
    // and adds it to the state machine. The hierarchy linking is handled
    // automatically by State_machine::add_state.

    // === START ===

    // Smart initialization by the state machine
    app_state_machine.initiate_state(START_ID, "START");

    // Callbacs setting by the state machine
    if (auto* s = app_state_machine.get_state(START_ID))
    {
        s->on_enter = start_enter;          // Actions on the state entering 
        s->on_exit  = start_exit;           // Actions on the state exit
        s->state_update = start_update;
        s->state_render = start_render;     // Rendering for the state
    }

    /*
    // === MAIN_MENU ===
    app_state_machine.initiate_state(MAIN_MENU_ID, "MAIN_MENU");

    if (auto* s = app_state_machine.get_state(MAIN_MENU_ID))
    {
        s->on_enter = main_menu_enter;
        s->on_exit  = main_menu_exit;
    }


    // === GAME ===
    app_state_machine.initiate_state(GAME_ID, "GAME");

    if (auto* s = app_state_machine.get_state(GAME_ID))
    {
        s->on_enter = game_enter;
        s->on_exit  = game_exit;
    }


    // === LEVEL_GAMEPLAY ===
    app_state_machine.initiate_state(LEVEL_GAMEPLAY_ID, "LEVEL_GAMEPLAY");

    if (auto* s = app_state_machine.get_state(LEVEL_GAMEPLAY_ID))
    {
        s->on_enter = level_gameplay_enter;
        s->on_exit  = level_gameplay_exit;
    }


    // === SMALL_MENU ===
    app_state_machine.initiate_state(SMALL_MENU_ID, "SMALL_MENU");

    if (auto* s = app_state_machine.get_state(SMALL_MENU_ID))
    {
        s->on_enter = small_menu_enter;
        s->on_exit  = small_menu_exit;
    }


    // === EXIT_PROGRAM ===
    app_state_machine.initiate_state(EXIT_PROGRAM_ID, "EXIT_PROGRAM");

    if (auto* s = app_state_machine.get_state(EXIT_PROGRAM_ID))
    {
        s->on_enter = exit_program_enter;
        s->on_exit  = exit_program_exit;
    }
    */  
    
    // At this point, all states are registered in the state machine.
    // State_machine handles connecting parents and children based on IDs,
    // so hierarchical updates and callback chaining will work automatically.
}

// =========================================================================================== INITIALIZATION
