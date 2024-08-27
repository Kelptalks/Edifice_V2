//
// Created by Spencer on 6/11/2024.
//



#include <SDL_surface.h>
#include <stdio.h>
#include <windows.h>
#include <SDL_audio.h>
#include "../Game/Sound/SoundManager.h"
#include "../Game/Debuging/Test_Main.h"

void getExecutablePath(char* buffer, size_t bufferSize) {
    GetModuleFileNameA(NULL, buffer, bufferSize);
    char* lastSlash = strrchr(buffer, '\\');
    if (lastSlash) {
        *lastSlash = '\0'; // Cut off the executable name, leaving only the path
    }
}

//Load the sprite sheet from directory
SDL_Surface* loadSpriteSheet(){
    char pathBuffer[1024];
    getExecutablePath(pathBuffer, sizeof(pathBuffer));
    char texturePath[1024];
    sprintf(texturePath, "%s\\..\\Assets\\SpriteSheet.bmp", pathBuffer); // Construct the full path

    SDL_Surface* image = SDL_LoadBMP(texturePath); // Load the image file
    return image;
}

void loadSound(const char *fileName, struct Sound* sound) {
    // Get the path to the executable
    char pathBuffer[1024];
    getExecutablePath(pathBuffer, sizeof(pathBuffer));

    // Construct the full path to the sound file
    char soundPath[1024];
    sprintf(soundPath, "%s\\..\\Assets\\Sounds\\%s", pathBuffer, fileName); // Use fileName parameter

    // Load the WAV file
    if (SDL_LoadWAV(soundPath, &sound->spec, &sound->buffer, &sound->length) == NULL) {
        reportBug("Failed to load WAV file: %s\n", SDL_GetError());
        return;
    }

    sound->original_length = sound->length;
    sound->original_buffer = sound->buffer;
}
