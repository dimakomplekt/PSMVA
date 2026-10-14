# Архитектура PSMVA

Документ описывает общую архитектуру приложения: слои, жизненный цикл, машину состояний, глобальные сервисы и систему сборки. Стилевые правила кода — в `diary/notes/copilot_rules.md`, дневник разработки — в `diary/`.

---

## Обзор

PSMVA — десктопное приложение (C++17, Windows/MSVC, x64) для анализа высокоскоростной видеосъёмки плазменного напыления. Весь интерфейс рисуется вручную средствами SDL3 (собственная библиотека виджетов), OpenCV используется для обработки кадров видео. Кадры OpenCV (`cv::Mat`) транслируются в `SDL_Texture` и отображаются в общем GUI (см. `libs/program_gui/gui_description.md`).

Приложение построено как **иерархическая машина состояний**: каждый экран программы — отдельное состояние со своими колбэками входа/выхода/обновления/рендера.

---

## Слои

```
src/
└── main.cpp                  # Точка входа: return SDL_app_init_and_run();

libs/
├── engine/                   # Переиспользуемый слой, не знает о предметной области
│   ├── engine.h              # Зонтичный заголовок всего движка
│   ├── state_machine/        # State_ID, State, State_machine
│   ├── lang_state/           # Синглтон текущего языка (App_lang), типы строк EN/RU
│   ├── global_inputs/        # Синглтоны мыши/клавиатуры (GI_mouse и др.)
│   ├── platform/             # Определение платформы препроцессором
│   ├── special/
│   │   ├── opencv_to_sdl/    # Трансляция cv::Mat -> SDL_Texture (мост OpenCV/SDL)
│   │   └── absolute_by_relative/  # Абсолютный путь к ресурсу от папки .exe
│   ├── SDL3-3.4.2/           # Вендоренные библиотеки (заголовки + .lib + .dll)
│   ├── SDL3_ttf-3.2.2/
│   └── SDL3_image-3.4.4/
│
├── program_gui/              # Собственная библиотека GUI поверх SDL3
│   └── basic_elements/
│       ├── UI_elements/      # Виджеты: my_sdl_element (база), button, textbox,
│       │                     #          fader, panel, texture
│       ├── GUI_functions/    # Рисование фигур, транслятор цветов HEX -> SDL_Color
│       ├── global_palette/   # Синглтон палитры (App_palette)
│       ├── global_fonts/     # Синглтон шрифтов (App_fonts)
│       └── content/          # Ресурсы (ttf-шрифты), копируются к .exe при сборке
│
└── program_logic/            # Прикладной слой — сама программа
    ├── app.h / app.cpp       # Контекст приложения, инициализация, главный цикл
    ├── global_data/          # Константы окна, App_timer, словарь строк EN/RU
    └── program_states/       # Регистрация состояний + папка на каждое состояние
        └── states_logic/
            ├── 0.0_START/
            ├── 1.0_MAIN_MENU/
            ├── 1.1_FILE_CHOOSE/
            ├── 1.2_MASKS_SETUP/
            ├── 1.3_FLOW_PARAMETERS_CALCULATION/
            ├── 1.4_REPORT_FORMING/
            └── 2.0_PROGRAM_END/
```

Направление зависимостей: `program_logic` → `program_gui` → `engine`. Слой `engine` ничего не знает о состояниях программы и её GUI.

---

## Жизненный цикл приложения

Точка входа `src/main.cpp` вызывает `SDL_app_init_and_run()` (`libs/program_logic/app.cpp`):

1. **Инициализация** (`this_app_init`): SDL_ttf → SDL_image → `SDL_app_init` (создание окна 1500×1000 и рендерера, VSync, blend mode) → `init_program_states()` (регистрация всех состояний) → переход в `START_ID`.
2. **Главный цикл** (`this_app_loop`), пока `app_state == SDL_APP_CONTINUE`:
   - `App_timer_1.update()` — обновление частотных зон;
   - `SDL_PollEvent` → `SDL_app_event` — `SDL_EVENT_QUIT` завершает цикл, остальные события делегируются активному состоянию;
   - `SDL_app_cycle` — основной такт (см. ниже);
   - `App_timer_1.end_cycle()` — сброс разрешений на выполнение.
3. **Завершение** (`SDL_app_shutdown`): уничтожение рендерера, окна, `SDL_Quit()`.

Глобальный контекст — `SDL_app_ctx this_app` (окно, рендерер, машина состояний, флаг состояния приложения). Доступ к рендереру из любого модуля — через `get_app_renderer()`.

### Такт `SDL_app_cycle`

```
1. Если есть отложенный запрос смены состояния -> выполнить go_to() и ПРОПУСТИТЬ кадр
2. Глобальные обновления в зоне HZ_240 (флаги сброса языка/палитры/шрифтов)
3. state_update() активного состояния
4. Рендер: RenderClear (в зоне HZ_120) -> state_render() -> RenderPresent
```

---

## Машина состояний

Реализация — `libs/engine/state_machine/`.

- **`State_ID`** — иерархический идентификатор, вектор целых (`{1,2}` — потомок `{1}`). Методы `parent()`, `child(i)`, `is_parent_of()`, `string()` ("1.2").
- **`State`** — id, имя и пять колбэков: `on_enter`, `on_exit`, `state_handle_event(SDL_Event&)`, `state_update()`, `state_render(SDL_Renderer*)`.
- **`State_machine`** — владеет состояниями (`unique_ptr`), `initiate_state()` создаёт и регистрирует состояние, `go_to()` выполняет переход (on_exit → смена → on_enter).

### Отложенная смена состояний

Прямой вызов `go_to()` из колбэков запрещён (небезопасен во время обхода update/render). Вместо этого:

```cpp
// В колбэке (клик кнопки и т.п.):
this_app.app_sm.request_state_change(MASKS_SETUP_ID);

// В начале SDL_app_cycle запрос обрабатывается в безопасной точке:
if (app->app_sm.check_state_change())
{
    app->app_sm.go_to(app->app_sm.consume_next_state());
    return ...; // кадр пропускается, чтобы не смешивать выполнение двух состояний
}
```

### Состояния программы (конвейер обработки)

Идентификаторы и регистрация — `libs/program_logic/program_states/program_states.h|.cpp`. Каждое состояние — папка `states_logic/<N>_<NAME>/` с функциями `<name>_enter/_exit/_update/_render`.

| State_ID | Состояние | Назначение |
|----------|-----------|------------|
| {0}   | START | Запуск, подготовка ("нажмите ENTER") |
| {1}   | MAIN_MENU | Главное меню: начать анализ или выйти |
| {1,1} | FILE_CHOOSE | Выбор видеофайлов и ввод их параметров |
| {1,2} | MASKS_SETUP | Настройка OpenCV-масок фейдерами, превью |
| {1,3} | FLOW_PARAMETERS_CALCULATION | Расчёт параметров потока, прогресс-бары |
| {1,4} | REPORT_FORMING | Формирование и сохранение отчёта |
| {2}   | PROGRAM_END | Завершение работы |

**Текущий статус:** зарегистрированы START, MAIN_MENU, FILE_CHOOSE, MASKS_SETUP и PROGRAM_END; состояния 1.3 и 1.4 существуют как файлы, но закомментированы в `program_states.cpp`. Мост `opencv_to_sdl` пока заглушка — вычислительная часть OpenCV в разработке (алгоритм расчёта описан в `diary/notes/description.md`).

---

## Таймер и частотные зоны

`App_timer` (`libs/program_logic/global_data/app_timer/`) — синглтон, ограничивающий частоту выполнения участков кода без отдельных потоков. Зоны: `HZ_10000`, `HZ_1000`, `HZ_240`, `HZ_120`.

```cpp
if (App_timer_1.can_execute(Execute_zone_ID::HZ_240))
{
    // выполнится не чаще 240 раз в секунду
}
```

`update()` в начале такта выставляет разрешения по времени, `end_cycle()` в конце — сбрасывает. Так, например, очистка экрана перед рендером выполняется в зоне HZ_120.

---

## Глобальные сервисы (синглтоны)

Все глобальные сервисы — синглтоны Мейерса, доступные через inline-ссылки:

| Ссылка | Класс | Назначение |
|--------|-------|------------|
| `App_lang` | `Lang_state` | Текущий язык интерфейса (EN/RU), переключение |
| `App_palette` | `Global_palette` | Цвета всех UI-элементов (фон, рамки, hover/click, access) |
| `App_fonts` | `Global_fonts` | Загрузка и хранение TTF-шрифтов |
| `App_timer_1` | `App_timer` | Частотные зоны главного цикла |
| `GI_mouse` и др. | `GI_*` | Централизованное состояние мыши/клавиатуры |

### Механизм reset-флагов

Смена языка или палитры не «проталкивается» в виджеты напрямую. Сервис выставляет флаг сброса; виджеты, привязанные к словарю/палитре, опрашивают его при своём обновлении и перестраивают текстуры. Главный цикл (зона HZ_240) обновляет счётчики флагов (`lang_reset_flag_state_loop_update()` и т.п.), чтобы сброс действовал ограниченное число тактов и не вызывал постоянную реинициализацию (особенно шрифтов).

---

## GUI-библиотека

`libs/program_gui/basic_elements/UI_elements/` — собственные виджеты поверх SDL_Renderer:

- **`my_sdl_element`** — базовые типы: координаты, границы для hover/click-проверок (с дельтой 3px), контекст анимации перемещения (easing: линейный, экспоненциальный, логарифмический), статическая/динамическая привязка к палитре.
- **Виджеты**: `my_sdl_button` (с режимами доступа и push-анимацией), `my_sdl_textbox`, `my_sdl_fader` (слот + ручка, основной инструмент настройки масок), `my_sdl_panel`, `my_sdl_texture`.

Тексты виджетов берутся из словаря `program_dictionary.h` — структуры `Lang_string_type` с парой строк (EN, RU); активная строка выбирается по `App_lang`.

---

## Ресурсы и пути

Ресурсы (шрифты из `libs/program_gui/basic_elements/content/`) при сборке копируются в `<папка exe>/content/`. Загрузка в коде — только через

```cpp
absolute_by_relative_from_exe("content/ttf_fonts/Miracode.ttf")
```

(`libs/engine/special/absolute_by_relative/`, с платформенным роутингом win/lin), чтобы программа работала независимо от текущего каталога запуска.

---

## Сборка

CMake (`CMakeLists.txt`) + PowerShell-обёртка `run.ps1` (конфигурация → сборка Release → запуск).

- Исходники собираются рекурсивным глобом `src/*.cpp` + `libs/**/*.cpp` с `CONFIGURE_DEPENDS` — новые .cpp подхватываются автоматически.
- SDL3, SDL3_ttf, SDL3_image вендорены в `libs/engine/` (x64 .lib; .dll копируются к exe post-build вместе с `content/`).
- OpenCV подключается через `find_package` с жёстко заданным `OpenCV_DIR = C:/opencv/build`; DLL OpenCV должны быть в PATH (`run.ps1` добавляет `C:\opencv\build\x64\vc16\bin`).
- Результат: `build/Release/PSMVA.exe`.
