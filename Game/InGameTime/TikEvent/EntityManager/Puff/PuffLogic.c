//
// Created by Spencer on 9/11/2024.
//
#include "../EntityManager.h"
#include "PuffLogic.h"
#include "../../../../World/World.h"

struct Entity* createPuffEntity(){
    struct Entity* entity = malloc(sizeof (struct Entity));
    entity->worldX = -98;
    entity->worldY = -96;
    entity->worldZ = 52;
    entity->frame = 0;

    entity->entityType = EntityPuff;

    entity->direction = EntityNorth;


    if (entity == NULL){
        reportBug("failed to malloc for Puff entity\n");
        return NULL;
    }

    entity->typeSpecificStruct = malloc(sizeof (struct EntityPuffSpecificData));
    if (entity->typeSpecificStruct == NULL){
        free(entity);
        reportBug("failed to malloc for Puff entity\n");
        return NULL;
    }

    struct EntityPuffSpecificData* puffData = entity->typeSpecificStruct;

    puffData->resistance = 1.01f;
    puffData->velX = 0;
    puffData->velY = 0;
    puffData->velZ = 0;
    puffData->speed = 0.02f;

    entity->worldX = -98;
    entity->worldY = -96;
    entity->worldZ = 52;

    return entity;
}

void tickPuffEntity(struct GameData* gameData, struct Entity* entity){
    struct EntityPuffSpecificData* puffData = entity->typeSpecificStruct;

    //Give random speed and direction
    if (rand() % 100 == 0){
        int randomDirection = rand() % 10;
        switch(randomDirection){
            case 0:
                entity->direction = EntityNorth;
                puffData->velX = +puffData->speed;
                puffData->velY = +puffData->speed;
                break;
            case 1:
                entity->direction = EntityNorthEast;
                puffData->velY = +puffData->speed;
                break;
            case 2:
                entity->direction = EntityEast;
                puffData->velY = +puffData->speed;
                puffData->velX = -puffData->speed;
                break;
            case 3:
                entity->direction = EntitySouthEast;
                puffData->velX = -puffData->speed;
                break;
            case 4:
                entity->direction = EntitySouth;
                puffData->velX = -puffData->speed;
                puffData->velY = -puffData->speed;
                break;
            case 5:
                entity->direction = EntitySouthWest;
                puffData->velY = -puffData->speed;
                break;
            case 6:
                entity->direction = EntityWest;
                puffData->velY = -puffData->speed;
                puffData->velX = +puffData->speed;
                break;
            case 7:
                entity->direction = EntityNorthWest;
                puffData->velX = +puffData->speed;
                break;
            case 8:
                puffData->velZ = +puffData->speed;
                break;

            case 9:
                puffData->velZ = -puffData->speed;
                break;
        }
    }

    //Slow speed every tick
    puffData->velX = puffData->velX / puffData->resistance;
    puffData->velY = puffData->velY / puffData->resistance;
    puffData->velZ = puffData->velZ / puffData->resistance;

    //Apply velocity
    float newWorldX = puffData->velX + entity->worldX;
    float newWorldY = puffData->velY  + entity->worldY;
    float newWorldZ = puffData->velZ + entity->worldZ;

    enum Block block = getBlockAtWorldCor(gameData->world, newWorldX, newWorldY, newWorldZ);
    if (!isTranslucent(block) && !isTransparent(block)){
        puffData->velX = 0;
        puffData->velY = 0;
        puffData->velZ = 0;
    }
    else{
        entity->worldX = newWorldX;
        entity->worldY = newWorldY;
        entity->worldZ = newWorldZ;
    }
}