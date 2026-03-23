# Подход

1) Сделать контейнер (с названием "панель") который может быть частью окна или другого контейнера. Контейнер при передаче в него компонентов сохраняет информацию о том где они по z в этом контейнере и где они размещены внутри него x, y и с какой привязкой (делаю только три типа - ЛЦ, ЦЦ, ПЦ)
2) Сделать компоненты (допустим для начала просто кнопку, фейдер и окно под SDL_Texture) которые могут быть частями панели или окна, компоненты хранят инфу о своём рендеринге - цвета, содержимое, ширина, высота, и инфу о своей логике - всё на базе коллбеков
3) Просто собрать GUI на базе стейт машины и окон обычной вёрсткой компонент-панель типо вот пример работы стейт машины (типо просто в апп 2 колла по текущему стейту - апдейт и рендер + прокрутка работы апп в мейне) 


___

#### **При таком цикле**

``` cpp 

bool SDL_app_cycle(sdl_app_ctx* app)
{
    // State update
    if (app->app_sm.get_current_state()) app->app_sm.state_update();

    // State rendering
    if (app->app_sm.get_current_state())
    {
        SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
        SDL_RenderClear(app->renderer);

        app->app_sm.state_render(app->renderer);

        SDL_RenderPresent(app->renderer);
    }

    return app->app_state == SDL_APP_CONTINUE;
}

```
   

___

#### **И подобной работе движка на коллбеках стейт-машины***

``` cpp 

void start_enter()         { std::cout << "Entering START\n"; }
void start_exit()          { std::cout << "Exiting START\n"; }

void start_render(SDL_Renderer* renderer)
{


    // Red circle
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
        s->state_render = start_render;     // Rendering for the state
    }
}

```


___


#### **Имея на руках какую-то доработанную кнопку вроде такой**

``` cpp 
// my_sdl_button.h


#pragma once


// =========================================================================================== IMPORT

#include <functional>                   // for std::function

#include "../../../engine/engine.h"     // SDL3 and SDL ttf import


// =========================================================================================== IMPORT

// Button access type for click callback logic permission
enum button_access_type
{

    BUTTON_DEFAULT_CLICK_PERMISSION,        // Always can be clicked
    BUTTON_CLICK_EXTERN_CLICK_PERMISSION,   // Can be clicked only by the true return of the extern function for click permission check

};


class My_SDL_button
{


    public:

        // ===== CONSTRUCTOR AND DESTRUCTOR =====

        My_SDL_button();             // Button constructor
        ~My_SDL_button();            // Button destructor    

        // ===== CONSTRUCTOR AND DESTRUCTOR =====


        // ===== MAIN LOGIC =====

        // Button access type setter 
        void set_access_type(button_access_type new_access_type);

        // Element update method (to be called in the main loop)
        void update();                                      


        // Extern click permission check callback method - to be called in the main loop if 
        // the button access type is BUTTON_CLICK_EXTERN_CLICK_PERMISSION
        std::function<bool()> extern_click_permission();

        // Hover callback method
        std::function<void()> on_hover();                    

        // Click callback method - one call after click and blocked until the next
        std::function<void()> on_click();                    


        // ===== MAIN LOGIC =====


        // ===== GUI ======

        // Button render with logic by the button state flags (hovered, clicked)
        void render();

        // Button size setter
        void set_size(unsigned int width, unsigned int height);


        // Set the text displayed on the button
        void set_content(const std::string& text);

        // Set ttf font
        void set_ttf_font_link(TTF_Font* ttf_font_link);

        // Set font file path
        void set_font_path(const std::string& font_path);

        // Set font size
        void set_font_size(unsigned int size);


        // Opacity
        void set_opacity(Uint8 new_opacity);

        // Color setters

        void set_background_color(SDL_Color new_color);
        void set_border_color(SDL_Color new_color);
        void set_content_color(SDL_Color new_color);
        void set_background_color_hovered(SDL_Color new_color);
        void set_border_color_hovered(SDL_Color new_color);
        void set_content_color_hovered(SDL_Color new_color);
        void set_background_color_clicked(SDL_Color new_color);
        void set_border_color_clicked(SDL_Color new_color);
        void set_content_color_clicked(SDL_Color new_color);

        // Texture setters

        void set_background_texture(SDL_Texture* new_texture);
        void set_border_texture(SDL_Texture* new_texture);

        // Set the renderer for the SDL ttf workflow
        void set_content_texture_renderer(SDL_Renderer* renderer);
        void set_text_texture(SDL_Texture* new_texture);

        // ===== GUI ======


    protected:



    private:

        // ===== MAIN LOGIC =====

        bool hovered;                                // Button hover state
        bool hover_check();                          // Button hover check method (to be called in the main loop)


        // Only onetime click realization in this version

        button_access_type click_access_type;        // Button click access type for click callback logic permission

        bool click_permission_check();               // Button click check method (to be called in the main loop)
        bool click_permission;                       // Button click permission flag


        bool clicked;                                // Button click state
        bool clicked_tmp;                            // Button click state temp for callback block until the next click
        bool clicked_check();                        // Button click check method (to be called in the main loop)
        
        // ===== MAIN LOGIC =====
        

        // ===== GUI ======

        // Sizes

        unsigned int width_size;
        unsigned int height_size;

        unsigned int boarder_size;
        unsigned int boarder_radius;

        unsigned int content_size;


        // Content

        // TTF Font pointer
        TTF_Font* ttf_font_link = nullptr;

        // Font path for button text
        std::string font_path;

        // Button text
        std::string content;


        // Button opacity by 
        // calling of commands like
        // SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g, background_color.b, alpha);
        // before rendering
        Uint8 opacity = 255; // 0 = fully transperent, 255 = fully opaque


        // Button colors by SDL type  

        SDL_Color background_color;
        SDL_Color border_color;
        SDL_Color content_color;
        
        SDL_Color background_color_hovered;
        SDL_Color border_color_hovered;
        SDL_Color content_color_hovered;

        SDL_Color background_color_clicked;
        SDL_Color border_color_clicked;
        SDL_Color content_color_clicked;

        // Button textures by SDL type


        // Text texture for rendering
        SDL_Texture* background_texture = nullptr;
        
        // Text texture for rendering
        SDL_Texture* border_texture = nullptr;

        // Text texture for rendering
        SDL_Renderer* content_texture_renderer = nullptr;
        SDL_Texture* content_texture = nullptr;

        // ===== GUI ======
};

``` 
    

___

#### **Можно спокойно дефолтно чекать и ховер и клик перебором всех элементов объекта панели реализованной позже, каким-то c итератором, вроде:**


``` cpp 

for (auto& element : panel.elements)
{
    element.update();
}


for (auto& element : panel.elements)
{
    element.render();
}


``` 

 **+** вариант нормально оформить обработку вложенности панелей и их составляющих

___
