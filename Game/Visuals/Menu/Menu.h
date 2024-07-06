//
// Created by Spencer on 6/6/2024.
//

#ifndef EDIFICE_MENU_H
#define EDIFICE_MENU_H
#include "../../GameData.h"
#include "Button/Button.h"

struct Menu{
    struct MenuButton** menuButtons;
    int buttonCount;

    //Sub menus
    struct Menu* settingsMenu;
};

struct Menu* createMainMenu();

void MainMenuControlInput(struct GameData* gameData, SDL_Event event);

void renderMainMenu(struct GameData* gameData, int xCor, int yCor);

void settingsMenuControlInput(struct GameData* gameData, SDL_Event event);

void renderSettingsMenu(struct GameData* gameData, int xCor, int yCor);

#endif //EDIFICE_MENU_H
