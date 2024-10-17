//
// Created by Spencer on 6/7/2024.
//

#include <malloc.h>
#include "stdio.h"
#include "DebugMenu.h"
#include "../Test_Main.h"
#include "SDL.h"
#include "../../Visuals/Camera/CameraData.h"
#include "../../GameData.h"
#include "TikData/TickData.h"


struct DebugMenu* createDebugMenu(){
    struct DebugMenu* debugMenu = malloc(sizeof (struct DebugMenu));
    if (debugMenu == NULL){
        reportBug("failed to create debugMenu \n");
        return NULL;
    }
    debugMenu->frameRenderingData = createFrameRenderingData();

    debugMenu->xBlockSelectedCor = 0;
    debugMenu->yBlockSelectedCor = 0;
    debugMenu->xMouseCor = 0;
    debugMenu->yMouseCor = 0;

    debugMenu->visible = false;
    debugMenu->frameDataVisible = false;
    debugMenu->tikDataVisible = false;
    debugMenu->chunkBoarders = false;



    return debugMenu;
}

void renderDebugMenu(struct GameData* gameData){
    struct DebugMenu* debugMenu = gameData->debugMenu;

    //Mouse cords
    char MouseCords[40] = {0};
    sprintf(MouseCords, "Mouse cords : %f, %f", gameData->debugMenu->xMouseCor + gameData->cameraData->xRenderingOffset, gameData->debugMenu->yMouseCor + gameData->cameraData->yRenderingOffset);
    drawString(gameData, MouseCords, 40, 5, 30, 20);

    char side[6] = "right";
    if (gameData->debugMenu->LeftSide){
        side[0] = 'l';
        side[1] = 'e';
        side[2] = 'f';
        side[3] = 't';
        side[4] = ' ';
    }

    //Iso cords of mouse
    char mouseIsoCords[40] = {0};
    sprintf(mouseIsoCords, "Mouse Iso Cords : %d, %d Side : %s ", gameData->debugMenu->xBlockSelectedCor, gameData->debugMenu->yBlockSelectedCor, side);
    renderString(gameData, mouseIsoCords, 5, 55, 20);

    //Iso cords of camera
    char camIsoCords[40] = {0};
    sprintf(camIsoCords, "Camera Iso Cords : %d, %d", gameData->cameraData->xIsoCamCenter, gameData->cameraData->yIsoCamCenter);
    renderString(gameData, camIsoCords, 5, 80, 20);

    //Iso chunk cords of camera
    char camChunkIsoCords[40] = {0};
    sprintf(camChunkIsoCords, "Camera Chunk Cords : %d, %d", gameData->cameraData->xIsoChunkCamCenter, gameData->cameraData->yIsoChunkCamCenter);
    renderString(gameData, camChunkIsoCords, 5, 105, 20);

    //Iso chunk cords of camera
    char camRenderingDirection[40] = {0};
    sprintf(camRenderingDirection, getDirectionString(gameData->cameraData->direction));
    renderString(gameData, camRenderingDirection, 5, 130, 20);

    //ChunkInformation
    int totalChunks = gameData->cameraData->castedPool->totalChunksCreated;

    char TotalChunkCount[40] = {0};
    sprintf(TotalChunkCount, "Total Casted Chunks : %i", totalChunks);
    renderString(gameData, TotalChunkCount, 5, 155, 20);

    int freeChunks = gameData->cameraData->castedPool->freeChunkCount;
    char freeChunkCount[40] = {0};
    sprintf(freeChunkCount, "Total Free Chunks : %i", freeChunks);
    renderString(gameData, freeChunkCount, 5, 180, 20);

    if (debugMenu->frameDataVisible) {
        renderFrameRenderingData(gameData);
    }
    if (debugMenu->tikDataVisible) {
        renderTickData(gameData);
    }
}

void toggleChunkBoarders(struct DebugMenu* debugMenu){
    debugMenu->chunkBoarders = !debugMenu->chunkBoarders;
}

void toggleDebugMenu(struct DebugMenu* debugMenu){
    debugMenu->visible = !debugMenu->visible;
}