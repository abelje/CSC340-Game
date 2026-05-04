#define SDL_MAIN_USE_CALLBACKS 1
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "level_designer.h"


SDL_AppResult SDL_AppInit(void **appstate, int, char**) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    try {
        std::string m, level;
        std::cout << "Input 'decor' or 'base' layer\n";
        std::cin >> m;
        std::cout << "Input a level ex. 'level_1'\n";
        std::cin >> level;
        Mode mode = Mode::Base;
        if (m == "decor") {
            mode = Mode::Decor;
        }
        else if (m == "base") {
            mode = Mode::Base;
        }
        else {
            throw std::runtime_error("Invalid mode input!");
        }
        auto designer = new LevelDesigner(level, 37, 15, mode);
        *appstate = designer;
        return SDL_APP_CONTINUE;  /* carry on with the program! */
    }
    catch(std::exception& e) {
        std::cerr << e.what() << '\n';
        return SDL_APP_FAILURE;
    }
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event *event) {
    auto designer = static_cast<LevelDesigner*>(appstate);
    if (event->type == SDL_EVENT_QUIT) {
        // save progress
        designer->save();
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }

    designer->handle_event(event);
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    auto designer = static_cast<LevelDesigner*>(appstate);

    designer->input();
    designer->render();

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

void SDL_AppQuit(void *appstate, SDL_AppResult) {
    auto designer = static_cast<LevelDesigner*>(appstate);
    delete designer;
}
