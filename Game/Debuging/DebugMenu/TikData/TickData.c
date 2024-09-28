//
// Created by Spencer on 9/27/2024.
//

#include "TickData.h"
#include "../../../InGameTime/TikManager.h"

void renderTickData(struct GameData* gameData){

    struct TikManager* tikManager = gameData->tikManager;

    char totalFrameTime[40] = {0};
    sprintf(totalFrameTime, "Current Tick : %i", tikManager->tik);
    renderString(gameData, totalFrameTime, 5, gameData->screen->yRez - 150, 20);

}