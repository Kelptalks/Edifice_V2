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



    return frameRenderingData;
}

void renderFrameRenderingData(struct GameData* gameData){
    struct FrameRenderingData* frameRenderingData = gameData->debugMenu->frameRenderingData;

    char chunkManagement[40] = {0};
    sprintf(chunkManagement, "Chunk Management Time : %i", frameRenderingData->chunkUpdatingTime);
    renderString(gameData, chunkManagement, 5, gameData->screen->yRez - 25, 20);

    char chunkRayCasting[40] = {0};
    sprintf(chunkRayCasting, "RayCasting time : %i", frameRenderingData->rayCastingTime);
    renderString(gameData, chunkRayCasting, 5, gameData->screen->yRez - 50, 20);

    char entityRendering[40] = {0};
    sprintf(entityRendering, "Entity Rendering Time : %i", frameRenderingData->entityRenderingTime);
    renderString(gameData, entityRendering, 5, gameData->screen->yRez - 75, 20);
}