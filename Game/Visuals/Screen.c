//
// Created by Spencer on 5/6/2024.
//

#include <stdio.h>
#include <stdbool.h>
#include "SDL.h"
#include "Screen.h"

struct Screen* createScreen(){
    struct Screen* screen =  malloc(sizeof (struct Screen));
    if (screen == NULL){
        FILE * debug;
        debug = fopen("debug", "a");
        fprintf(debug, "Screen | failed to malloc for screen struct \n");
        fclose(debug);
        return NULL;
    }

    //set run to true
    screen->run = true;
    screen->menuType = MainMenu;
    screen->targetFPS = 144;
    screen->frameDelay = 1000 / screen->targetFPS;

    //create SDL window and render
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_CreateWindowAndRenderer(2560, 1440, 0, &window, &renderer);
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
    screen->event = &event;
    screen->window = window;
    screen->renderer = renderer;

    return screen;
}