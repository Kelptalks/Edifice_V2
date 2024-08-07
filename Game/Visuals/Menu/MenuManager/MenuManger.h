//
// Created by Spencer on 8/7/2024.
//

#ifndef EDIFICE_MENUMANGER_H
#define EDIFICE_MENUMANGER_H

#include "../../../GameData.h"

enum MenuType{
    MainMenu,
    CameraMenu
};

struct MenuManager{
    enum MenuType currentMenuType;
};

struct MenuManager* createMenuManager();

void renderCurrentMenu(struct GameData* gameData);

#endif //EDIFICE_MENUMANGER_H
