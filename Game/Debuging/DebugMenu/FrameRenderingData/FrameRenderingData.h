//
// Created by Spencer on 9/24/2024.
//

#ifndef EDIFICE_FRAMERENDERINGDATA_H
#define EDIFICE_FRAMERENDERINGDATA_H

#include <SDL_stdinc.h>
#include "../../../GameData.h"

struct FrameRenderingData{
    Uint32 totalFrameTime;

    int currentCalcAverageIndex;
    Uint32 averageRenderTimeArray[30];
    Uint32 averageRenderTime;

    Uint32 chunkUpdatingTime;
    Uint32 rayCastingTime;
    Uint32 entityRenderingTime;
    Uint32 onScreenUIRenderingTime;
};

struct FrameRenderingData* createFrameRenderingData();

Uint32 addToAndGetAverageFrameRenderTime(struct FrameRenderingData* frameRenderingData, Uint32 renderTime);

void renderFrameRenderingData(struct GameData* gameData);

#endif //EDIFICE_FRAMERENDERINGDATA_H
