//
// Created by Spencer on 5/6/2024.
//

#ifndef EDIFICE_SCREEN_H
#define EDIFICE_SCREEN_H

#include "SDL.h"
#include <stdbool.h>

enum MenuType{
    WorldCamera,
    MainMenu
};

struct Screen{
    //SDL Components
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event* event;

    //Menu management
    enum MenuType menuType;

    double frameRenderTime;

    //Weather the screen should run
    bool run;
};

//Create the screen struct.
struct Screen* createScreen();

#endif //EDIFICE_SCREEN_H
