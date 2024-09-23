//
// Created by Spencer on 9/16/2024.
//

#ifndef EDIFICE_ENTITYMANAGER_H
#define EDIFICE_ENTITYMANAGER_H

#include "SDL.h"
#include "../../../GameData.h"

enum EntityDirection{
    EntityNorth,
    EntityNorthEast,
    EntityEast,
    EntitySouthEast,
    EntitySouth,
    EntitySouthWest,
    EntityWest,
    EntityNorthWest
};


enum EntityType{
    //Sprite Based entity
    EntityMan,
    EntityPuff,

    //Block Based entity
    EntityWorm
};


struct Entity{
    enum EntityType entityType;
    void* typeSpecificStruct;

    enum EntityDirection direction;
    int frame;

    float worldX;
    float worldY;
    float worldZ;
};

void getEntitySpriteSheetLocation(enum EntityType entity, int* xCor, int* yCor, int* width, int* height, int* frameCount);

SDL_Rect getEntitySpriteSheetSourceRect(enum EntityType entity, enum EntityDirection entityDirection, int frame);

void tikEntity(struct GameData* gameData, struct Entity* entity);




#endif //EDIFICE_ENTITYMANAGER_H
