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
};

struct Menu* createMenu();

void menuControlInput(struct GameData* gameData, SDL_Event event);

void renderMenu(struct GameData* gameData, int x, int y);

#endif //EDIFICE_MENU_H
