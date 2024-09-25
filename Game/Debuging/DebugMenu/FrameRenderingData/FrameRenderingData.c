//
// Created by Spencer on 9/24/2024.
//

#include <malloc.h>
#include "FrameRenderingData.h"
#include "../../Test_Main.h"

struct FrameRenderingData* createFrameRenderingData(){
    struct FrameRenderingData* frameRenderingData = malloc(sizeof (struct FrameRenderingData));
    if (frameRenderingData == NULL){
        reportBug("Failed to create frame Rendering Data");
        return NULL;
    }

    frameRenderingData->chunkUpdatingTime = 0;
    frameRenderingData->rayCastingTime = 0;
    frameRenderingData->entityRenderingTime = 0;
    frameRenderingData->onScreenUIRenderingTime = 0;


    return frameRenderingData;
}

void renderFrameRenderingData(struct GameData* gameData){
    struct FrameRenderingData* frameRenderingData = gameData->debugMenu->frameRenderingData;

    char chunkManagement[40] = {0};
    sprintf(chunkManagement, "Chunk Management Time : %i ms", frameRenderingData->chunkUpdatingTime);
    renderString(gameData, chunkManagement, 5, gameData->screen->yRez - 25, 20);

    char chunkRayCasting[40] = {0};
    sprintf(chunkRayCasting, "RayCasting time : %i ms", frameRenderingData->rayCastingTime);
    renderString(gameData, chunkRayCasting, 5, gameData->screen->yRez - 50, 20);

    char entityRendering[40] = {0};
    sprintf(entityRendering, "Entity Rendering Time : %i ms", frameRenderingData->entityRenderingTime);
    renderString(gameData, entityRendering, 5, gameData->screen->yRez - 75, 20);

    char totalFrameTime[40] = {0};
    sprintf(totalFrameTime, "Total Frame Time : %i ms", frameRenderingData->totalFrameTime);
    renderString(gameData, totalFrameTime, 5, gameData->screen->yRez - 100, 20);

    char onScreenUIRenderingTime[40] = {0};
    sprintf(onScreenUIRenderingTime, "On screen UI rendering Time : %i ms", frameRenderingData->onScreenUIRenderingTime);
    renderString(gameData, onScreenUIRenderingTime, 5, gameData->screen->yRez - 125, 20);
}