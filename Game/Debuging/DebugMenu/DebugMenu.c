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
    debugMenu->xBlockSelectedCor = 0;
    debugMenu->yBlockSelectedCor = 0;
    debugMenu->xMouseCor = 0;
    debugMenu->yMouseCor = 0;

    debugMenu->visible = true;
    return debugMenu;
}

void renderDebugMenu(struct GameData* gameData){
    //Frame rate
    char FrameRate[40] = {0};
    Uint32 fps = 1000 / gameData->screen->frameRenderTime;
    sprintf(FrameRate, "FPS : %u  CAP : %i ", fps, gameData->screen->targetFPS);
    drawString(gameData, FrameRate, 40, 5, 5, 20);

    //Mouse cords
    char MouseCords[40] = {0};
    sprintf(MouseCords, "Mouse cords : %d, %d", gameData->debugMenu->xMouseCor, gameData->debugMenu->yMouseCor);
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
    drawString(gameData, mouseIsoCords, 40, 5, 55, 20);
}