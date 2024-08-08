//
// Created by Spencer on 8/7/2024.
//

#ifndef EDIFICE_MENUMANGER_H
#define EDIFICE_MENUMANGER_H

#include "../../../GameData.h"

enum MenuType{
    MainMenu,
    CameraMenu,
    TestMenu
};

struct MenuManager{
    enum MenuType currentMenuType;

    struct MainMenu* mainMenu;
};

struct MenuManager* createMenuManager();

void renderCurrentMenu(struct GameData* gameData);

void handleCurrentMenuInputs(struct GameData* gameData, SDL_Event event);

#endif //EDIFICE_MENUMANGER_H
