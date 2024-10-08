//
// Created by Spencer on 6/30/2024.
//


#include <malloc.h>
#include "PlayerData.h"
#include "../World/World.h"
#include "../InGameTime/TikManager.h"
#include "../Visuals/Camera/CameraData.h"

struct PlayerData* createPlayerData(){
    struct PlayerData* playerData = malloc(sizeof (struct PlayerData));
    playerData->hotBar = createHotBar(9);
    int totalBlockCount = getTotalBlockCount();
    playerData->blockSelectionMenu = createBlockSelectionMenu(getTotalBlockCount(), totalBlockCount / 5);

    playerData->block = 1;
    int lastMouseXCor = 0;
    int lastMouseYCor = 0;


    playerData->playerDirection = EntityNorth;
    playerData->walkingFrame = 0;
    playerData->walkingTexture = 0;
    playerData->sprinting = false;

    playerData->worldX = 0;
    playerData->worldY = 0;
    playerData->worldZ = 100;

    playerData->sizeX = +0.5f;
    playerData->sizeY = +0.5f;


    playerData->velResistance = 1.2;
    playerData->velX = 0;
    playerData->velY = 0;
    playerData->velZ = 0;

    playerData->gravity = 0.05f;
    playerData->walkingSpeed = 0.1f;
    playerData->sprintMod = 0.05f;


    return playerData;
}

void tikPlayer(struct GameData* gameData){
    struct PlayerData* playerData = gameData->playerData;

    int walkingAnimationSpeed = 6;
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
    if ((!isTransparent(block) && !isTranslucent(block))){
        block = getBlockAtWorldCor(gameData->world, newWorldX, playerData->worldY, playerData->worldZ + 1);
        if ((!isTransparent(block) && !isTranslucent(block))){
            playerData->velX = 0;
        }
        else {
            playerData->worldZ++;
        }
    }
    else{
        playerData->worldX = newWorldX;
    }

    block = getBlockAtWorldCor(gameData->world, playerData->worldX, newWorldY, playerData->worldZ);
    if ((!isTransparent(block) && !isTranslucent(block))){
        block = getBlockAtWorldCor(gameData->world, playerData->worldX, newWorldY, playerData->worldZ + 1);
        if ((!isTransparent(block) && !isTranslucent(block))){
            playerData->velY = 0;
        }
        else {
            playerData->worldZ++;
        }
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

    if (playerData->worldZ < - 100){
        reportTikBug("relocating player that fell off the world\n");
        playerData->worldZ = 100;
        playerData->worldX = 0;
        playerData->worldY = 0;
    }

    playerData->velZ -= playerData->gravity;
}

void handlePlayerControls(struct GameData* gameData){
    //Camera Movement Controls
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);
    struct CameraData* cameraData = gameData->cameraData;
    // Check each key of interest and update accordingly
    bool w = false;
    bool a = false;
    bool s = false;
    bool d = false;
    bool shift = false;
    gameData->playerData->sprinting = false;
    if (keystate[SDL_SCANCODE_UP]) {
        w = true;
    }
    if (keystate[SDL_SCANCODE_DOWN]) {
        s = true;
    }
    if (keystate[SDL_SCANCODE_LEFT]) {
        a = true;
    }
    if (keystate[SDL_SCANCODE_RIGHT]) {
        d = true;
    }
    if (keystate[SDL_SCANCODE_SPACE]) {
        gameData->playerData->velZ = 0.5f;
    }
    if (keystate[SDL_SCANCODE_LSHIFT]){
        shift = true;
        gameData->playerData->sprinting = true;
    }

    float shiftMod = 0;
    float halfWalk = gameData->playerData->walkingSpeed;
    if (shift){
        shiftMod = gameData->playerData->sprintMod;
    }
    if (!w && !a && s && !d){
        gameData->playerData->playerDirection = EntityNorth;
        gameData->playerData->velX = +(halfWalk+ shiftMod) * cameraData->xDirection;
        gameData->playerData->velY = +(halfWalk+ shiftMod) * cameraData->yDirection;
    }
    else if (!w && a && s && !d){
        gameData->playerData->playerDirection = EntityNorthEast;
        gameData->playerData->velY = +(gameData->playerData->walkingSpeed + shiftMod) * cameraData->yDirection;;
    }
    else if (!w && a && !s && !d){
        gameData->playerData->playerDirection = EntityEast;
        gameData->playerData->velY = +(halfWalk + shiftMod) * cameraData->yDirection;
        gameData->playerData->velX = -(halfWalk + shiftMod) * cameraData->xDirection;
    }
    else if (w && a && !s && !d){
        gameData->playerData->playerDirection = EntitySouthEast;
        gameData->playerData->velX = -(gameData->playerData->walkingSpeed + shiftMod) * cameraData->xDirection;;
    }
    else if (w && !a && !s && !d){
        gameData->playerData->playerDirection = EntitySouth;
        gameData->playerData->velX = -(halfWalk + shiftMod) * cameraData->xDirection;
        gameData->playerData->velY = -(halfWalk + shiftMod) * cameraData->yDirection;
    }
    else if (w && !a && !s && d){
        gameData->playerData->playerDirection = EntitySouthWest;
        gameData->playerData->velY = -(gameData->playerData->walkingSpeed + shiftMod) * cameraData->yDirection;
    }
    else if (!w && !a && !s && d){
        gameData->playerData->playerDirection = EntityWest;
        gameData->playerData->velY = -(halfWalk + shiftMod) * cameraData->yDirection;
        gameData->playerData->velX = +(halfWalk + shiftMod) * cameraData->xDirection;
    }
    else if (!w && !a && s && d){
        gameData->playerData->playerDirection = EntityNorthWest;
        gameData->playerData->velX = +(gameData->playerData->walkingSpeed + shiftMod) * cameraData->xDirection;
    }
}