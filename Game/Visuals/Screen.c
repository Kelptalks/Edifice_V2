//
// Created by Spencer on 5/6/2024.
//

#include <stdio.h>
#include <stdbool.h>
#include "SDL.h"
#include "Screen.h"
#include "../Debuging/Test_Main.h"

void playPlaceSound(struct Audio* audio){
    SDL_QueueAudio(audio->deviceId, audio->wavBuffer, audio->wavLength);
    SDL_PauseAudioDevice(audio->deviceId, 0);
}


struct Audio* createAudio(){
    if (SDL_Init(SDL_INIT_AUDIO) != 0) {
        reportBug("Unable to initialize SDL: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8 *wavBuffer;

    if (SDL_LoadWAV("C:\\Users\\Spencer\\Desktop\\Edifice_V2\\Assets\\placeblock3.wav", &wavSpec, &wavBuffer, &wavLength) == NULL) {
        reportBug("Error loading WAV: %s", SDL_GetError());
        SDL_Quit();
        return NULL;
    }

    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
    if (deviceId == 0) {
        reportBug("Failed to open audio device: %s\n", SDL_GetError());
        SDL_FreeWAV(wavBuffer);
        SDL_Quit();
        return NULL;
    }

    struct Audio* audio = malloc(sizeof (struct Audio));
    if (audio == NULL){
        reportBug("Failed to malloc audio struct\n");
        return NULL;
    }

    audio->wavBuffer = wavBuffer;
    audio->wavLength = wavLength;
    audio->wavSpec = &wavSpec;
    audio->deviceId = deviceId;

    return audio;
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
    screen->menuType = MainMenu;
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