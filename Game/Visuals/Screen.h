//
// Created by Spencer on 5/6/2024.
//

#ifndef EDIFICE_SCREEN_H
#define EDIFICE_SCREEN_H

#include "SDL.h"
#include <stdbool.h>

struct Screen{
    //Basics
    int xRez;
    int yRez;

    //SDL Components
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event* event;
    struct Audio* audio;

    //Frame rendering
    int targetFPS;
    int frameDelay;
    Uint32 frameRenderTime;
    int currentFrame;

    //Weather the screen should run
    bool run;
};

void updateScreen(struct Screen* screen);

//Create the screen struct.
struct Screen* createScreen();

#endif //EDIFICE_SCREEN_H
