//
// Created by Spencer on 9/23/2024.
//
#include "../../../../World/World.h"
#include "../../../../GameData.h"
#include "../../Camera.h"
#include "../../IsoCordTool/IsoCordManager.h"
#include "../../../../PlayerData/PlayerData.h"


void renderEntity(struct GameData* gameData){
    struct CameraData* cameraData = gameData->cameraData;
    struct PlayerData* playerData = gameData->playerData;

    float chunkRenderScale = (cameraData->renderScale / cameraData->baseBlockScale);

    float xPlayerCamCor; float yPlayerCamCor;
    worldCordsToCameraCords(cameraData, gameData->playerData->worldX, gameData->playerData->worldY, gameData->playerData->worldZ, &xPlayerCamCor, &yPlayerCamCor);
    int xPlayerScreenCor; int yPlayerScreenCor;
    floatIsoToScreen(cameraData->renderScale, xPlayerCamCor, yPlayerCamCor, &xPlayerScreenCor, &yPlayerScreenCor);

    //Draw the entity texture
    //reportBug("Player World cords (%f)\n", cameraData->renderScale);
    int xSpriteScreenCords = xPlayerScreenCor + cameraData->xRenderingOffset - (cameraData->renderScale / 2);
    int ySpriteScreenCords = yPlayerScreenCor + cameraData->yRenderingOffset - (cameraData->renderScale - (cameraData->renderScale/4));

    SDL_Rect destRect = {xSpriteScreenCords, ySpriteScreenCords, chunkRenderScale * 64, chunkRenderScale *  128};
    SDL_RenderCopy(gameData->screen->renderer, gameData->textures->entityTextures->entityTextures[0].textures[playerData->walkingTexture][playerData->playerDirection],
                   NULL, &destRect);


    //ReDraw Blocks infront of sprite
    for (int x = -3; x < 3; x++){
        for (int y = -3; y < 3; y++){
            float relXCor = y + xPlayerCamCor;
            float relYCor = x + yPlayerCamCor;
            struct CastedBlock* castedBlock = getCastedBlockAtCords(cameraData, relXCor, relYCor);
            if (castedBlock != NULL) {
                //Check if block is in front of sprite
                //Left
                if ((castedBlock->worldLeftBlockX >= playerData->worldX || castedBlock->worldLeftBlockY >= playerData->worldY) && castedBlock->worldLeftBlockZ > playerData->worldZ) {
                    renderCastedBlock(gameData, castedBlock, relXCor, relYCor, 0);
                }
                if ((castedBlock->worldRightBlockX >= playerData->worldX || castedBlock->worldRightBlockY >= playerData->worldY) && castedBlock->worldRightBlockZ > playerData->worldZ) {
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