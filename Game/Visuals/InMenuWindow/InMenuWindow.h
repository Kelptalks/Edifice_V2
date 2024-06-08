//
// Created by Spencer on 6/8/2024.
//

#ifndef EDIFICE_INMENUWINDOW_H
#define EDIFICE_INMENUWINDOW_H


#include <malloc.h>
#include <stdbool.h>
#include "../Menu/Button/Button.h"

struct InMenuWindow{
    int xCor;
    int yCor;
    int xRez;
    int yRez;
    bool visible;

    int buttonCount;
    struct MenuButton** menuButtons;
};

struct InMenuWindow* createInMenuWindow(int xCor, int yCor, int xRez, int yRez);

bool InMenuWindowControls(struct GameData* gameData, struct InMenuWindow* inMenuWindow, SDL_Event event);

void renderInMenuWindow(struct GameData* gameData, struct InMenuWindow* inMenuWindow);

#endif //EDIFICE_INMENUWINDOW_H
