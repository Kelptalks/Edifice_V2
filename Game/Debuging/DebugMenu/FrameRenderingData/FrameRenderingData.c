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
    frameRenderingData->currentCalcAverageIndex = 0;

    return frameRenderingData;
}

Uint32 addToAndGetAverageFrameRenderTime(struct FrameRenderingData* frameRenderingData, Uint32 renderTime){
    if (frameRenderingData->currentCalcAverageIndex == 30){
        frameRenderingData->currentCalcAverageIndex = 0;
    }
    frameRenderingData->averageRenderTimeArray[frameRenderingData->currentCalcAverageIndex] = renderTime;
    frameRenderingData->currentCalcAverageIndex++;

    Uint32 combinedValues = 0;
    for (int i = 0; i < 30; i++) {
        combinedValues += frameRenderingData->averageRenderTimeArray[i];
    }

    return combinedValues / 30;
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

    char averageFrameTimeString[40] = {0};
    int averageFrameRenderTime = addToAndGetAverageFrameRenderTime(frameRenderingData, frameRenderingData->totalFrameTime);
    sprintf(averageFrameTimeString, "Average Frame Time : %i ms", averageFrameRenderTime);
    renderString(gameData, averageFrameTimeString, 5, gameData->screen->yRez - 100, 20);

    char onScreenUIRenderingTime[40] = {0};
    sprintf(onScreenUIRenderingTime, "On screen UI rendering Time : %i ms", frameRenderingData->onScreenUIRenderingTime);
    renderString(gameData, onScreenUIRenderingTime, 5, gameData->screen->yRez - 125, 20);

}