//
// Created by Spencer on 6/11/2024.
//

#ifndef EDIFICE_ASSETMANAGER_H
#define EDIFICE_ASSETMANAGER_H

#include <SDL_surface.h>

void getExecutablePath(char* buffer, size_t bufferSize);

SDL_Surface* loadSpriteSheet();

#endif //EDIFICE_ASSETMANAGER_H
