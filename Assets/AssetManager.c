//
// Created by Spencer on 6/11/2024.
//



#include <SDL_surface.h>
#include <stdio.h>
#include <windows.h>

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
