//
// Created by Spencer on 6/7/2024.
//

#include <malloc.h>
#include "stdio.h"
#include "DebugMenu.h"
#include "../Test_Main.h"
#include "SDL.h"
#include "../../GameData.h"


struct DebugMenu* createDebugMenu(){
    struct DebugMenu* debugMenu = malloc(sizeof (struct DebugMenu));
    if (debugMenu == NULL){
        reportBug("failed to create debugMenu \n");
        return NULL;
    }
    debugMenu->yBlockSelectedCor = 0;
    debugMenu->yBlockSelectedCor = 0;
    debugMenu->visible = true;
    return debugMenu;
}

void renderDebugMenu(struct GameData* gameData){
    //Frame rate
    char FrameRate[40] = {0};
    Uint32 fps = 1000 / gameData->screen->frameRenderTime;
    sprintf(FrameRate, "FPS : %u  CAP : %i", fps, gameData->screen->targetFPS);
    drawString(gameData, FrameRate, 40, 5, 5, 20);

    //Mouse cords
    char MouseCords[30] = {0};
    sprintf(MouseCords, "MouseCords : %d, %d", gameData->debugMenu->xBlockSelectedCor, gameData->debugMenu->yBlockSelectedCor);
    drawString(gameData, MouseCords, 30, 5, 30, 20);
}