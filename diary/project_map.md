# Приложение 1. Карта проекта

## Файлы

```text
PSMVA/
├── src/
│   └── main.cpp                          # Точка входа: запускает SDL_app_init_and_run()
├── libs/
│   ├── engine/                           # Технический слой, минимально зависит от предметной области
│   │   ├── engine.h                      # Мастер-заголовок движка
│   │   ├── state_machine/                # State_ID, State, State_machine
│   │   ├── lang_state/                   # Язык интерфейса, типы EN/RU
│   │   ├── global_inputs/                # Mouse/keyboard state and global input singletons
│   │   ├── platform/                     # Определение платформы (Windows/Linux)
│   │   ├── special/
│   │   │   ├── opencv_to_sdl/            # Перевод cv::Mat -> SDL_Texture
│   │   │   └── absolute_by_relative/     # Путь к ресурсам относительно папки .exe
│   │   ├── SDL3-3.4.2/                   # SDL3 headers/libs
│   │   ├── SDL3_ttf-3.2.2/               # SDL3_ttf
│   │   └── SDL3_image-3.4.4/             # SDL3_image
│   │
│   ├── program_gui/                      # GUI-слой поверх SDL
│   │   └── basic_elements/
│   │       ├── UI_elements/              # my_sdl_button, textbox, panel, fader, texture
│   │       ├── GUI_functions/            # Геометрия, цвета, графические примитивы
│   │       ├── global_palette/           # Общая палитра интерфейса
│   │       ├── global_fonts/             # Общие шрифты и загрузка TTF
│   │       └── content/                  # Шрифты и ресурсы, копируются в папку exe
│   │
│   └── program_logic/                    # Прикладная логика приложения
│       ├── app.h / app.cpp               # Контекст приложения, главный цикл, SDL init/shutdown
│       ├── global_data/
│       │   ├── global_data.h             # Размеры окна, приложение, флаги окна
│       │   ├── app_timer/                # Таймер частотных зон
│       │   └── program_dictionary/       # Текстовые строки интерфейса EN/RU
│       └── program_states/
│           ├── program_states.h/.cpp     # Регистрация всех состояний и их идентификаторов
│           └── states_logic/
│               ├── 0.0_START/
│               ├── 0.0_empty_state_template/
│               ├── 1.0_MAIN_MENU/
│               ├── 1.1_FILE_CHOOSE/
│               ├── 1.2_MASKS_SETUP/
│               │   ├── 1.2.1_MASKS_SETUP_1.cpp
│               │   ├── 1.2.2_MASKS_SETUP_2.cpp
│               │   ├── 1.2.3_MASKS_SETUP_3.cpp
│               │   ├── 1.2.4_MASKS_SETUP_4.cpp
│               │   ├── 1.2.5_MASKS_SETUP_5.cpp
│               │   ├── 1.2.6_MASKS_SETUP_6.cpp
│               │   ├── 1.2_MASKS_SETUP.cpp
│               │   └── 1.2_MS_HELPER.*
│               ├── 1.3_FLOW_PARAMETERS_CALCULATION/
│               ├── 1.4_REPORT_FORMING/
│               └── 2.0_PROGRAM_END/
│
├── diary/
│   ├── notes/analysis/                   # Архитектурные заметки и описания поведения
│   └── project_map.md                    # Эта карта проекта
├── build/                                # Сборочные артефакты CMake
├── CMakeLists.txt                        # Настройка проекта и зависимостей
├── run.ps1                               # Сборка и запуск проекта
├── README.md                             # Общее описание проекта и сценарии использования
└── LICENSE
```

## Как устроена логика

Проект построен как иерархическая машина состояний.

- В корне приложения есть `src/main.cpp`: он вызывает `SDL_app_init_and_run()`.
- В `libs/program_logic/app.cpp` находятся:
  - `this_app_init()` — инициализация SDL, TTF, окна, рендерера, машины состояний
  - `this_app_loop()` — главный цикл
  - `SDL_app_cycle()` — один такт обновления/рендера
  - `SDL_app_event()` — маршрутизация SDL-событий
  - `SDL_app_shutdown()` — очистка ресурсов
- В `libs/engine/state_machine/state_machine.h` находятся базовые сущности:
  - `State_ID` — иерархический идентификатор состояния
  - `State` — состояние с колбэками `on_enter`, `on_exit`, `state_update`, `state_render`
  - `State_machine` — управляющий контейнер состояний
- Смена состояния делается через отложенную заявку (`state_change_request`), чтобы не менять состояние прямо изнутри рендера или обновления.

Схема выполнения цикла примерно такая:

```text
main.cpp
   -> SDL_app_init_and_run()
      -> this_app_init()
         -> SDL_Init()
         -> SDL_CreateWindowAndRenderer()
         -> init_program_states()
         -> app_sm.go_to(START_ID)
      -> this_app_loop()
         -> App_timer_1.update()
         -> SDL_PollEvent()
         -> SDL_app_cycle()
         -> App_timer_1.end_cycle()
```

## Где что искать

| Вопрос | Файл / место |
|---|---|
| Точка входа приложения | `src/main.cpp`, `main()` |
| Как создаётся окно и запускается основной цикл | `libs/program_logic/app.cpp`, `SDL_app_init_and_run()`, `this_app_init()`, `this_app_loop()` |
| Где хранится глобальный контекст SDL-приложения | `libs/program_logic/app.h`, `SDL_app_ctx` |
| Где лежат размеры окна и имя приложения | `libs/program_logic/global_data/global_data.h` |
| Как работает таймер частотных зон | `libs/program_logic/global_data/app_timer/app_timer.h`, `App_timer`, `Execute_zone_ID` |
| Где описаны IDs всех состояний | `libs/program_logic/program_states/program_states.h` |
| Где регистрируются все состояния | `libs/program_logic/program_states/program_states.cpp`, `init_program_states()` |
| Где живёт стартовый экран | `libs/program_logic/program_states/states_logic/0.0_START/` |
| Где живёт главное меню | `libs/program_logic/program_states/states_logic/1.0_MAIN_MENU/` |
| Где выбирают видеофайлы и исходные данные | `libs/program_logic/program_states/states_logic/1.1_FILE_CHOOSE/` |
| Где настраиваются маски для анализа | `libs/program_logic/program_states/states_logic/1.2_MASKS_SETUP/` |
| Где находятся подэтапы настройки масок | `1.2.1_MASKS_SETUP_1.cpp` ... `1.2.6_MASKS_SETUP_6.cpp` |
| Где хранится логика помощи/вспомогательных функций масок | `1.2_MS_HELPER.cpp`, `1.2_MS_HELPER.h` |
| Где выполняется расчёт параметров потока | `libs/program_logic/program_states/states_logic/1.3_FLOW_PARAMETERS_CALCULATION/` |
| Где формируется отчёт | `libs/program_logic/program_states/states_logic/1.4_REPORT_FORMING/` |
| Где завершение работы | `libs/program_logic/program_states/states_logic/2.0_PROGRAM_END/` |
| Где лежат строки интерфейса EN/RU | `libs/program_logic/global_data/program_dictionary/program_dictionary.h` |
| Где живут общие шрифты | `libs/program_gui/basic_elements/global_fonts/` |
| Где живут базовые виджеты | `libs/program_gui/basic_elements/UI_elements/` |
| Как реализована палитра UI | `libs/program_gui/basic_elements/global_palette/` |
| Как переводится `cv::Mat` в `SDL_Texture` | `libs/engine/special/opencv_to_sdl/` |
| Где берутся пути к ресурсам от папки exe | `libs/engine/special/absolute_by_relative/` |
| Как устроен базовый стек SDL и глобальный доступ к рендереру | `libs/engine/engine.h`, `libs/program_logic/app.h` |

## Состояния проекта

Идентификаторы в проекте устроены иерархически:

| ID | Состояние | Назначение |
|---|---|---|
| `{0}` | `START` | Старт приложения, подготовка |
| `{1}` | `MAIN_MENU` | Главное меню |
| `{1, 1}` | `FILE_CHOOSE` | Выбор файлов и ввода метаданных |
| `{1, 2}` | `MASKS_SETUP` | Настройка масок |
| `{1, 3}` | `FLOW_PARAMETERS_CALCULATION` | Расчёт параметров потока |
| `{1, 4}` | `REPORT_FORMING` | Формирование отчёта |
| `{1, 5}` | `PROGRAM_END` | Завершение работы |

Подмаски `MASKS_SETUP` идут отдельными дочерними состояниями: `MASKS_SETUP_1` ... `MASKS_SETUP_6`.

## Таймер и частотные зоны

Главный таймер находится в `App_timer` и работает по частотным зонам:

```cpp
enum class Execute_zone_ID
{
    HZ_10000,
    HZ_1000,
    HZ_240,
    HZ_120,
    HZ_60,
    HZ_30,
    HZ_15,
    COUNT
};
```

Основной цикл вызывает обновление таймера в начале каждого кадра и сброс разрешений в конце. Это нужно, чтобы не гонять тяжёлые части рендера и логики слишком часто.

Именно в этом слое задаются повторения вроде:

- `HZ_240` — частая глобальная синхронизация флагов языка/палитры
- `HZ_120` — очистка и рендер
- `HZ_60`, `HZ_30`, `HZ_15` — более редкие операции и обновления

## Числа, которые полезно помнить

| Величина | Значение | Откуда |
|---|---|---|
| Размер окна | `1500 × 1000` | `MAIN_WINDOW_H_SIZE`, `MAIN_WINDOW_V_SIZE` |
| Название окна | `PSMVA_1.0` | `THIS_APP_NAME` |
| Частотные зоны | `HZ_10000`, `HZ_1000`, `HZ_240`, `HZ_120`, `HZ_60`, `HZ_30`, `HZ_15` | `Execute_zone_ID` |
| Основной цикл UI | `HZ_240` | `SDL_app_cycle()`, `App_timer_1.can_execute(...)` |
| Очистка и рендер | `HZ_120` | `SDL_app_cycle()`, `SDL_RenderClear` |
| Платформа | Windows / Linux | `platform.h` |
| Количество подэтапов масок | 6 | `MASKS_SETUP_ID_1 ... _6` |
| Иерархия состояния | dot-строка типа `1.2` | `State_ID::string()` |

## Настройка алгоритма и экспертная проверка

Основные коэффициенты трекинга частиц собраны в структуре `processing_3_data` в `libs/program_logic/program_states/states_logic/1.3_FLOW_PARAMETERS_CALCULATION/1.3_FLOW_PARAMETERS_CALCULATION.h`, внутри блока `// ===== Setup =====`. Их подбирают под разрешение видео и условия эксперимента.

| Параметр | Значение по умолчанию | Что задаёт |
|---|---:|---|
| `zone_2_x_min_c` | `0.85` | Левая граница правой зоны поиска точки `N + 1`, доля ширины кадра |
| `zone_2_x_max_c` | `1.0` | Правая граница зоны поиска точки `N + 1`, доля ширины кадра |
| `zone_1_x_min_c_delta` | `0.02` | Минимальное горизонтальное смещение для поиска предыдущей точки, доля ширины кадра |
| `zone_1_x_max_c_delta` | `0.15` | Максимальное горизонтальное смещение для поиска предыдущей точки, доля ширины кадра |
| `pixel_spread` | `10` пикселей | Максимальное вертикальное расстояние между сопоставляемыми точками |
| `deflection_percentage` | `5.0%` | Допуск при классификации отклонённых треков относительно основного направления |
| `minimal_deviation_angle` | `3.0°` | Минимальный угол отклонения |
| `median_weight` | `0.5` | Вес медианы в смеси медианы и среднего; оставшийся вес приходится на среднее |

При настройке `median_weight` в README предлагается исследовать значения от `0` до `1` с шагом `0.25`.

Режим проверки экспертной разметкой переключается макросом `FPC_TEST_MODE` в том же заголовке:

```cpp
#define FPC_TEST_MODE 0
```

Сейчас режим выключен (`0`). Чтобы включить проверку автоматически построенных межкадровых треков сравнением с треками, размеченными экспертом, значение макроса меняют на `1`. Подробное описание алгоритма трекинга находится в `libs/program_logic/program_states/states_logic/1.3_FLOW_PARAMETERS_CALCULATION/about/particles_detection.md`.

## Где обычно смотреть при отладке

Если нужно быстро понять, как работает сценарий, лучше идти в таком порядке:

1. `src/main.cpp` — старт
2. `libs/program_logic/app.cpp` — главный цикл и рендер
3. `libs/program_logic/program_states/program_states.cpp` — список зарегистрированных экранов
4. нужная папка `states_logic/<N>_*` — конкретный сценарий
5. GUI-виджеты в `libs/program_gui/basic_elements/UI_elements/` — как элементы взаимодействуют с пользователем
6. `absolute_by_relative` и `global_fonts` — ресурсы и пути

Это даёт правильный ориентир: сначала понять жизненный цикл, затем — экран, затем — его виджеты и ядро логики.

___

Итого: проект выглядит как классический C++ SDL GUI-приложение с машиной состояний, красивым разделением на `engine`, `program_gui`, `program_logic`, и с отдельными стадиями обработки видеопотока. Для навигации по коду чаще всего полезно начинать не с библиотек, а с `app.cpp` и `program_states.cpp`.
