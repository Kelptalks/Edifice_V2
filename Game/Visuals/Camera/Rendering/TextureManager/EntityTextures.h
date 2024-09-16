//
// Created by Spencer on 9/16/2024.
//

#ifndef EDIFICE_ENTITYTEXTURES_H
#define EDIFICE_ENTITYTEXTURES_H

#include "../../../../InGameTime/TikEvent/EntityManager/EntityManager.h"
#include "SDL.h"

struct EntityTexture{
    SDL_Texture* textures[8];
};


struct EntityTextures{
    int numOfEntityTypes;
    struct EntityTexture* entityTextures;

};


struct EntityTextures* createEntityTextures(struct SDL_Renderer* renderer, int numOfEntityTypes);

#endif //EDIFICE_ENTITYTEXTURES_H
