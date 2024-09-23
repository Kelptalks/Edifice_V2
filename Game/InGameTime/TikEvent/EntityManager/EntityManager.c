//
// Created by Spencer on 9/16/2024.
//

#include "EntityManager.h"
#include "Puff/PuffLogic.h"

void getEntitySpriteSheetLocation(enum EntityType entity, int* xCor, int* yCor, int* width, int* height, int* frameCount){
    if (entity == EntityMan){
         *xCor = 768;
         *yCor = 896;
         *width = 64;
         *height = 128;
         *frameCount = 3;
    }
    else if (entity == EntityPuff){
        *xCor = 1024;
        *yCor = 832;
        *width = 32;
        *height = 64;
        *frameCount = 1;
    }
}

SDL_Rect getEntitySpriteSheetSourceRect(enum EntityType entity, enum EntityDirection entityDirection, int frame){
    int startXCor; int startYCor; int spriteWidth; int spriteHeight; int maxFrame;
    getEntitySpriteSheetLocation(entity, &startXCor, &startYCor, &spriteWidth, &spriteHeight, &maxFrame);

    SDL_Rect srcRect = {startXCor + (spriteWidth * entityDirection), startYCor + (spriteHeight * frame), spriteWidth, spriteHeight};
    return srcRect;
}

void tikEntity(struct GameData* gameData, struct Entity* entity){
    if (entity != NULL) {
        switch (entity->entityType) {
            case EntityMan:
                break;
            case EntityPuff:
                tickPuffEntity(gameData, entity);
                break;
            case EntityWorm:
                break;
        }
    }
}