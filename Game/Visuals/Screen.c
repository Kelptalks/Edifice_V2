//
// Created by Spencer on 5/6/2024.
//

#include <stdio.h>
#include <stdbool.h>
#include "SDL.h"
#include "Screen.h"
#include "../Debuging/Test_Main.h"

void updateScreen(struct Screen* screen){
    SDL_SetRenderDrawColor(screen->renderer, 150, 255, 248, 255);
    SDL_RenderPresent(screen->renderer);
    SDL_RenderClear(screen->renderer);
}

void setScreenResolution(struct Screen* screen, int xRez, int yRez){
    screen->xRez = xRez;
    screen->yRez = yRez;
    SDL_SetWindowSize(screen->window, screen->xRez, screen->yRez);
}

struct Screen* createScreen(){
    struct Screen* screen =  malloc(sizeof (struct Screen));
    if (screen == NULL){
        FILE * debug;
        debug = fopen("debug", "a");
        fprintf(debug, "Screen | failed to malloc for screen struct \n");
        fclose(debug);
        return NULL;
    }

    screen->xRez = 1920;
    screen->yRez = 1080;

    //set run to true
    screen->run = true;
    screen->targetFPS = 256;
    screen->frameDelay = 1000 / screen->targetFPS;
    screen->currentFrame = 0;

    //create SDL window and render
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_CreateWindowAndRenderer(screen->xRez, screen->yRez, 0, &window, &renderer);
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetWindowTitle(window, "Edifice");

    if (window == NULL || renderer == NULL){
        FILE * debug;
        debug = fopen("debug", "a");
        fprintf(debug, "Screen | failed to create window and renderer \n");
        free(screen);
        fclose(debug);
        return NULL;
    }

    //create event var
    SDL_Event event;

    //set the variables
    //screen->audio = createAudio();
    screen->event = &event;
    screen->window = window;
    screen->renderer = renderer;

    return screen;
}