//
// Created by Spencer on 6/30/2024.
//


#include <malloc.h>
#include "PlayerData.h"
#include "../World/World.h"

struct PlayerData* createPlayerData(){
    struct PlayerData* playerData = malloc(sizeof (struct PlayerData));
    playerData->block = 1;
    int lastMouseXCor = 0;
    int lastMouseYCor = 0;


    playerData->playerDirection = EntityNorth;

    playerData->worldX = -98;
    playerData->worldY = -96;
    playerData->worldZ = 52;

    playerData->sizeX = 0.5;
    playerData->sizeY = 0.5;


    playerData->velResistance = 2;
    playerData->velX = 0;
    playerData->velY = 0;
    playerData->velZ = 0;

    playerData->gravity = 0.05f;
    playerData->sprintMod = 0.1f;


    return playerData;
}

void tikPlayer(struct GameData* gameData){
    struct PlayerData* playerData = gameData->playerData;

    //setBlockAtWorldCor(gameData->world, playerData->worldX, playerData->worldY, playerData->worldZ, Air);

    //Update player cords base off velocity
    float newWorldX = playerData->worldX + playerData->velX;
    float newWorldY = playerData->worldY + playerData->velY;
    float newWorldZ = playerData->worldZ + playerData->velZ;

    enum Block block;

    block = getBlockAtWorldCor(gameData->world, newWorldX, playerData->worldY, playerData->worldZ);
    if (!isTransparent(block) && !isTranslucent(block)){
        playerData->velX = 0;
    }
    else{
        playerData->worldX = newWorldX;
    }

    block = getBlockAtWorldCor(gameData->world, playerData->worldX, newWorldY + playerData->sizeY, playerData->worldZ);
    if (!isTransparent(block) && !isTranslucent(block)){
        playerData->velY = 0;
    }
    else{
        playerData->worldY = newWorldY;
    }

    block = getBlockAtWorldCor(gameData->world, playerData->worldX, playerData->worldY, newWorldZ);
    if (!isTransparent(block) && !isTranslucent(block)){
        playerData->velZ = 0;
    }
    else{
        playerData->worldZ = newWorldZ;
    }


    //setBlockAtWorldCor(gameData->world, playerData->worldX, playerData->worldY, playerData->worldZ, Debug);

    //update velocity
    if (playerData->velX != 0){
        playerData->velX = playerData->velX / playerData->velResistance;
    }
    if (playerData->velY != 0){
        playerData->velY = playerData->velY / playerData->velResistance;
    }

    playerData->velZ -= playerData->gravity;
}