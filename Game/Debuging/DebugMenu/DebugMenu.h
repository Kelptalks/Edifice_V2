//
// Created by Spencer on 6/7/2024.
//

#ifndef EDIFICE_DEBUGMENU_H
#define EDIFICE_DEBUGMENU_H

#include <stdbool.h>
#include "../../GameData.h"

struct DebugMenu{
    bool visible;
    int xBlockSelectedCor;
    int yBlockSelectedCor;
};

struct DebugMenu* createDebugMenu();

void renderDebugMenu(struct GameData* gameData);

#endif //EDIFICE_DEBUGMENU_H
