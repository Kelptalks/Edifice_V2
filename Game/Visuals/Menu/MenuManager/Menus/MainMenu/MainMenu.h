//
// Created by Spencer on 8/7/2024.
//

#ifndef EDIFICE_MAINMENU_H
#define EDIFICE_MAINMENU_H

#include "../../../../../GameData.h"
#include "../../ UIManager/UIRenderer/UIRenderer.h"
#include "../../ UIManager/UIManger.h"

struct MainMenu{
    struct Button* button;
    struct ScrollWheel* scrollWheel;

};

struct MainMenu* createMainMenu();

void renderMainMenu(struct GameData* gameData);

void handleInputMainMenu(struct GameData* gameData, SDL_Event event);

#endif //EDIFICE_MAINMENU_H
