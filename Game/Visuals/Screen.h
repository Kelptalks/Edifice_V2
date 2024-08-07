//
// Created by Spencer on 5/6/2024.
//

#ifndef EDIFICE_SCREEN_H
#define EDIFICE_SCREEN_H

#include "SDL.h"
#include <stdbool.h>



struct Audio{
    SDL_AudioSpec* wavSpec;
    Uint32 wavLength;
    Uint8 *wavBuffer;
    SDL_AudioDeviceID deviceId;
};

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

void playPlaceSound(struct Audio* audio);

//Create the screen struct.
struct Screen* createScreen();

#endif //EDIFICE_SCREEN_H
