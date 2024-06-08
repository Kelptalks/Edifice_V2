//
// Created by Spencer on 6/7/2024.
//

#ifndef EDIFICE_BUTTON_H
#define EDIFICE_BUTTON_H

#include <stdbool.h>
#include "SDL.h"
#include "../../../GameData.h"

struct MenuButton{
    //Positioning
    int width;
    int height;
    int xCor;
    int yCor;

    //Input
    bool mouseOn;
    bool pressed;

    //Rendering
    int color[3];
};

struct MenuButton* createMenuButton(int width, int height, int xCor, int yCor);

void renderButton(struct GameData* gameData, struct MenuButton* menuButton);

void buttonMouseInput(struct MenuButton* menuButton, SDL_Event event);

#endif //EDIFICE_BUTTON_H
