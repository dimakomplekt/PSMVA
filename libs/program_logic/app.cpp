// app.cpp

#include "app.h"

#include <iostream>


bool SDL_app_init(sdl_app_ctx* app, int w, int h, const char* title)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        app->app_state = SDL_APP_FAILURE;
        return false;
    }

    // Создаем окно и рендерер одновременно

    if (!SDL_CreateWindowAndRenderer(title, w, h, SDL_WINDOW_RESIZABLE, &app->window, &app->renderer))
    {
        // Обработка ошибки
        SDL_Log("SDL_CreateWindowAndRenderer failed: %s", SDL_GetError());
        app->app_state = SDL_APP_FAILURE;
        return false;
    }

    SDL_SetRenderVSync(app->renderer, 1);

    SDL_SetRenderDrawBlendMode(app->renderer, SDL_BLENDMODE_BLEND);

    SDL_SetWindowTitle(app->window, title);

    app->app_state = SDL_APP_CONTINUE;
    return true;
}


void SDL_app_event(sdl_app_ctx* app, SDL_Event* event)
{
    // Main SDL events handler
    if (event->type == SDL_EVENT_QUIT)
    {
        app->app_state = SDL_APP_SUCCESS;
        return;
    }

    // Other functions delegation to state machine
    if (app->app_sm.get_current_state()) app->app_sm.state_handle_event(*event);
}


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


void SDL_app_shutdown(sdl_app_ctx* app)
{
    if (app->renderer) SDL_DestroyRenderer(app->renderer);
    if (app->window) SDL_DestroyWindow(app->window);

    SDL_Quit();
}