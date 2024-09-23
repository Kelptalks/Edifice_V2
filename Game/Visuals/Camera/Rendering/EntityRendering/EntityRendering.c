//
// Created by Spencer on 9/23/2024.
//
#include "../../../../World/World.h"
#include "../../../../GameData.h"
#include "../../Camera.h"
#include "../../IsoCordTool/IsoCordManager.h"
#include "../../../../PlayerData/PlayerData.h"

void renderPuffEntity(struct GameData* gameData, struct Entity* entity){
    struct CameraData* cameraData = gameData->cameraData;

    //Get Sprite Cords
    float chunkRenderScale = (cameraData->renderScale / cameraData->baseBlockScale);
    float xEntityCamCor; float yEntityCamCor;
    worldCordsToCameraCords(cameraData, entity->worldX, entity->worldY, entity->worldZ, &xEntityCamCor, &yEntityCamCor);
    int xPlayerScreenCor; int yPlayerScreenCor;
    floatIsoToScreen(cameraData->renderScale, xEntityCamCor, yEntityCamCor, &xPlayerScreenCor, &yPlayerScreenCor);
    int xSpriteScreenCords = xPlayerScreenCor + cameraData->xRenderingOffset - (cameraData->renderScale / 2);
    int ySpriteScreenCords = yPlayerScreenCor + cameraData->yRenderingOffset - (cameraData->renderScale - (cameraData->renderScale/4));

    int null; int spriteWidth; int spriteHeight;
    getEntitySpriteSheetLocation(entity->entityType, &null, &null, &spriteWidth, &spriteHeight, &null);

    //RenderPuffShadow

    //Render By calculating the first solid block below entity
    int startX = entity->worldX; int startY = entity->worldY; float startZ = entity->worldZ;

    float shadowDrawDistance;
    float increment = 0.1f;
    for (int i = 0; i < 100; i++){
        startZ -= increment;
        enum Block block = getBlockAtWorldCor(gameData->world, startX, startY, startZ);
        if (!isTranslucent(block) && !isTransparent(block)){
            shadowDrawDistance = i * increment;
            SDL_Rect sourceRect = {704, 1120, 64, 32};
            SDL_Rect destRect2 = {xSpriteScreenCords, ySpriteScreenCords + ((shadowDrawDistance) * (cameraData->renderScale/2)) + (chunkRenderScale *  spriteHeight), chunkRenderScale * spriteWidth, chunkRenderScale * 16};
            SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet,
                           &sourceRect, &destRect2);
            break;
        }
    }

    //Render the puff entity
    SDL_Texture* spriteSheet = gameData->textures->spriteSheet;
    SDL_Rect destRect = {xSpriteScreenCords, ySpriteScreenCords, chunkRenderScale * spriteWidth, chunkRenderScale * spriteHeight};
    SDL_Rect srcRect = getEntitySpriteSheetSourceRect(entity->entityType, entity->direction, entity->frame);
    SDL_RenderCopy(gameData->screen->renderer, spriteSheet,
                   &srcRect, &destRect);

    //ReDraw Blocks in front of sprite
    for (int x = -3; x < 1; x++){
        for (int y = -3; y < 1; y++){
            float relXCor = y + xEntityCamCor + 1;
            float relYCor = x + yEntityCamCor + 1;
            struct CastedBlock* castedBlock = getCastedBlockAtCords(cameraData, relXCor, relYCor);
            if (castedBlock != NULL) {
                //Check if block is in front of sprite
                //Left
                if ((castedBlock->worldLeftBlockX >= entity->worldX || castedBlock->worldLeftBlockY >= entity->worldY) && castedBlock->worldLeftBlockZ >= entity->worldZ) {
                    renderCastedBlock(gameData, castedBlock, relXCor, relYCor, 0);
                }
                if ((castedBlock->worldRightBlockX >= entity->worldX || castedBlock->worldRightBlockY >= entity->worldY) && castedBlock->worldRightBlockZ >= entity->worldZ) {
                    renderCastedBlock(gameData, castedBlock, relXCor, relYCor, 1);
                }
            }
        }
    }
    //ReDraw Blocks in front of Shadow
    for (int x = -2; x < 2; x++){
        for (int y = -2; y < 2; y++){
            float relXCor = x + xEntityCamCor + (shadowDrawDistance) + 1;
            float relYCor = y + yEntityCamCor + (shadowDrawDistance) + 1;
            struct CastedBlock* castedBlock = getCastedBlockAtCords(cameraData, relXCor, relYCor);
            if (castedBlock != NULL) {
                //Check if block is in front of sprite
                //Left
                if ((castedBlock->worldLeftBlockX >= entity->worldX || castedBlock->worldLeftBlockY >= entity->worldY) && castedBlock->worldLeftBlockZ >= entity->worldZ) {
                    renderCastedBlock(gameData, castedBlock, relXCor, relYCor, 0);
                }
                if ((castedBlock->worldRightBlockX >= entity->worldX || castedBlock->worldRightBlockY >= entity->worldY) && castedBlock->worldRightBlockZ >= entity->worldZ) {
                    renderCastedBlock(gameData, castedBlock, relXCor, relYCor, 1);
                }
            }
        }
    }
}

void renderEntity(struct GameData* gameData){
    struct CameraData* cameraData = gameData->cameraData;
    struct PlayerData* playerData = gameData->playerData;

    float chunkRenderScale = (cameraData->renderScale / cameraData->baseBlockScale);
    float xPlayerCamCor; float yPlayerCamCor;
    worldCordsToCameraCords(cameraData, gameData->playerData->worldX, gameData->playerData->worldY, gameData->playerData->worldZ, &xPlayerCamCor, &yPlayerCamCor);
    int xPlayerScreenCor; int yPlayerScreenCor;
    floatIsoToScreen(cameraData->renderScale, xPlayerCamCor, yPlayerCamCor, &xPlayerScreenCor, &yPlayerScreenCor);


    //reportBug("Player World cords (%f)\n", cameraData->renderScale);
    int xSpriteScreenCords = xPlayerScreenCor + cameraData->xRenderingOffset - (cameraData->renderScale / 2);
    int ySpriteScreenCords = yPlayerScreenCor + cameraData->yRenderingOffset - (cameraData->renderScale - (cameraData->renderScale/4));

    //Render By calculating the first solid block below entity
    int startX = playerData->worldX; int startY = playerData->worldY; float startZ = playerData->worldZ;


    int shadowDrawDistance = 100;
    float increment = 0.1f;
    for (int i = 0; i < shadowDrawDistance; i++){
        startZ -= increment;
        enum Block block = getBlockAtWorldCor(gameData->world, startX, startY, startZ);
        if (!isTranslucent(block) && !isTransparent(block)){

            SDL_Rect sourceRect = {704, 1120, 64, 32};
            SDL_Rect destRect2 = {xSpriteScreenCords, ySpriteScreenCords + ((i * increment) * (cameraData->renderScale/2)) + (chunkRenderScale *  100), chunkRenderScale * 64, chunkRenderScale * 32};
            SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet,
                           &sourceRect, &destRect2);
            break;
        }
    }

    //Draw the entity texture
    SDL_Rect destRect = {xSpriteScreenCords, ySpriteScreenCords, chunkRenderScale * 64, chunkRenderScale *  128};
    SDL_RenderCopy(gameData->screen->renderer, gameData->textures->entityTextures->entityTextures[0].textures[playerData->walkingTexture][playerData->playerDirection],
                   NULL, &destRect);


    //ReDraw Blocks infront of sprite
    for (int x = -3; x < 3; x++){
        for (int y = -3; y < 3; y++){
            float relXCor = x + xPlayerCamCor + 1;
            float relYCor = y + yPlayerCamCor + 1;
            struct CastedBlock* castedBlock = getCastedBlockAtCords(cameraData, relXCor, relYCor);
            if (castedBlock != NULL) {
                //Check if block is in front of sprite
                //Left
                if ((castedBlock->worldLeftBlockX >= playerData->worldX || castedBlock->worldLeftBlockY >= playerData->worldY) && castedBlock->worldLeftBlockZ >= playerData->worldZ) {
                    renderCastedBlock(gameData, castedBlock, relXCor, relYCor, 0);
                }
                if ((castedBlock->worldRightBlockX >= playerData->worldX || castedBlock->worldRightBlockY >= playerData->worldY) && castedBlock->worldRightBlockZ >= playerData->worldZ) {
                    renderCastedBlock(gameData, castedBlock, relXCor, relYCor, 1);
                }
            }
        }
    }


    //Render HitBoxTexture
    if (gameData->debugMenu->visible) {
        SDL_Rect sourceRect = {704, 1152, 64, 128};
        SDL_Rect destRect2 = {xSpriteScreenCords, ySpriteScreenCords, chunkRenderScale * 64, chunkRenderScale * 128};
        SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet,
                       &sourceRect, &destRect2);
    }

}