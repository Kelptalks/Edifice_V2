//
// Created by Spencer on 6/7/2024.
//

#ifndef EDIFICE_DEBUGMENU_H
#define EDIFICE_DEBUGMENU_H

#include <stdbool.h>
#include "../../GameData.h"

struct DebugMenu{
    bool visible;

    int xMouseCor;
    int yMouseCor;

    bool LeftSide;
    bool chunkBoarders;

    int xBlockSelectedCor;
    int yBlockSelectedCor;
};

struct DebugMenu* createDebugMenu();

void renderDebugMenu(struct GameData* gameData);

//Controls
void toggleChunkBoarders(struct DebugMenu* debugMenu);
void toggleDebugMenu(struct DebugMenu* debugMenu);
#endif //EDIFICE_DEBUGMENU_H
