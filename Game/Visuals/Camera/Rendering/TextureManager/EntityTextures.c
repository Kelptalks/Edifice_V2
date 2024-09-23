//
// Created by Spencer on 9/16/2024.
//

#include "EntityTextures.h"
#include "../../../../Debuging/Test_Main.h"
#include "../../../../../Assets/AssetManager.h"

struct EntityTexture createEntityTexture(struct SDL_Renderer* renderer, SDL_Surface* spriteSheet, enum EntityType entity){
    //Create surface from sprite sheet
    int xCor;
    int yCor;
    int width;
    int height;
    int frameCount;
    getEntitySpriteSheetLocation(entity, &xCor, &yCor, &width, &height, &frameCount);

    struct EntityTexture entityTexture;

    entityTexture.textures = malloc(sizeof (SDL_Texture*) * frameCount);
    for (int t = 0; t < 3; t++) {
        entityTexture.textures[t] = malloc(sizeof(SDL_Texture*) * 8);
        for (int i = 0; i < 8; i++) {
            SDL_Rect srcRect = {xCor + (width * i), yCor + (height * t), width, height};
            SDL_Surface *croppedSurface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA32);
            SDL_BlitSurface(spriteSheet, &srcRect, croppedSurface, NULL);
            entityTexture.textures[t][i] = SDL_CreateTextureFromSurface(renderer, croppedSurface);
        }
    }

    return entityTexture;
}

struct EntityTextures* createEntityTextures(struct SDL_Renderer* renderer, int numOfEntityTypes){
    //Create the struct
    struct EntityTextures* textures = malloc(sizeof (struct EntityTextures));
    if (textures == NULL){
        reportBug("Failed to create textures array\n");
        return NULL;
    }
    textures->numOfEntityTypes = numOfEntityTypes;
    textures->entityTextures = malloc(sizeof (struct EntityTexture) * numOfEntityTypes);
    if (textures->entityTextures == NULL){
        reportBug("Failed to create entity textures array\n");
        free(textures);
        return NULL;
    }

    SDL_Surface* spriteSheet = loadSpriteSheet();
    //Splice the textures
    for (int i = 0; i < numOfEntityTypes; i++){
        textures->entityTextures[i] = createEntityTexture(renderer, spriteSheet, i);
    }

    return textures;
}