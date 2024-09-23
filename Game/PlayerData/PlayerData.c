//
// Created by Spencer on 6/30/2024.
//


#include <malloc.h>
#include "PlayerData.h"
#include "../World/World.h"
#include "../InGameTime/TikManager.h"

struct PlayerData* createPlayerData(){
    struct PlayerData* playerData = malloc(sizeof (struct PlayerData));
    playerData->block = 1;
    int lastMouseXCor = 0;
    int lastMouseYCor = 0;


    playerData->playerDirection = EntityNorth;
    playerData->walkingFrame = 0;
    playerData->walkingTexture = 0;
    playerData->sprinting = false;

    playerData->worldX = -98;
    playerData->worldY = -96;
    playerData->worldZ = 52;

    playerData->sizeX = +0.5f;
    playerData->sizeY = +0.5f;


    playerData->velResistance = 1.85f;
    playerData->velX = 0;
    playerData->velY = 0;
    playerData->velZ = 0;

    playerData->gravity = 0.05f;
    playerData->walkingSpeed = 0.04f;
    playerData->sprintMod = 0.04f;


    return playerData;
}

void tikPlayer(struct GameData* gameData){
    struct PlayerData* playerData = gameData->playerData;

    int walkingAnimationSpeed = 1;
    if (playerData->sprinting){
        walkingAnimationSpeed = 2;
    }
    if ((playerData->velX < -0.01 || playerData->velX > 0.01) || (playerData->velY < -0.01 || playerData->velY > 0.01) ) {
        if (gameData->tikManager->tik % walkingAnimationSpeed == 0) {
            gameData->playerData->walkingFrame++;
            if (gameData->playerData->walkingFrame > 4) {
                gameData->playerData->walkingFrame = 0;
            }
            if (gameData->playerData->walkingFrame % 2 == 0) {
                gameData->playerData->walkingTexture = 0;
            } else if (gameData->playerData->walkingFrame == 1) {
                gameData->playerData->walkingTexture = 1;
            } else if (gameData->playerData->walkingFrame == 3) {
                gameData->playerData->walkingTexture = 2;
            }
        }
    }
    else{
        gameData->playerData->walkingFrame = 0;
    }

    //setBlockAtWorldCor(gameData->world, playerData->worldX, playerData->worldY, playerData->worldZ, Air);

    //Update player cords base off velocity
    float newWorldX = playerData->worldX + playerData->velX;
    float newWorldY = playerData->worldY + playerData->velY;
    float newWorldZ = playerData->worldZ + playerData->velZ;

    enum Block block;
    enum Block block2;

    block = getBlockAtWorldCor(gameData->world, newWorldX, playerData->worldY, playerData->worldZ);
    block2 = getBlockAtWorldCor(gameData->world, newWorldX, playerData->worldY, playerData->worldZ);
    if ((!isTransparent(block) && !isTranslucent(block)) || (!isTransparent(block2) && !isTranslucent(block2))){
        playerData->velX = 0;
    }
    else{
        playerData->worldX = newWorldX;
    }

    block = getBlockAtWorldCor(gameData->world, playerData->worldX, newWorldY, playerData->worldZ);
    block2 = getBlockAtWorldCor(gameData->world, playerData->worldX, newWorldY, playerData->worldZ);
    if ((!isTransparent(block) && !isTranslucent(block)) || (!isTransparent(block2) && !isTranslucent(block2))){
        playerData->velY = 0;
    }
    else{
        playerData->worldY = newWorldY;
    }

    block = getBlockAtWorldCor(gameData->world, playerData->worldX, playerData->worldY, newWorldZ);
    block2 = getBlockAtWorldCor(gameData->world, playerData->worldX, newWorldY, playerData->worldZ);
    if ((!isTransparent(block) && !isTranslucent(block))|| (!isTransparent(block2) && !isTranslucent(block2))){
        playerData->velZ = 0;
    }
    else{
        playerData->worldZ = newWorldZ;
    }


    //setBlockAtWorldCor(gameData->world, playerData->worldX, playerData->worldY, playerData->worldZ, Granite);

    //update velocity
    if (playerData->velX != 0){
        playerData->velX = playerData->velX / playerData->velResistance;
    }
    if (playerData->velY != 0){
        playerData->velY = playerData->velY / playerData->velResistance;
    }

    playerData->velZ -= playerData->gravity;
}