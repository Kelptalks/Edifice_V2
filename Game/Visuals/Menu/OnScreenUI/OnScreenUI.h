//
// Created by Spencer on 9/24/2024.
//

#ifndef EDIFICE_ONSCREENUI_H
#define EDIFICE_ONSCREENUI_H

#include "../../../GameData.h"
#include "../MenuManager/MenuManger.h"

struct OnScreenUI{
    bool visible;
    bool blockSelectionMenuVisible;
    bool escapeMenuVisible;

    enum Block blockSelected;

    //Location and scaling vars
    int scale;

    //Slot drawing
    int slotSpacedScale;
    int blockScale;
    int blockCenteringOffset;

    //HotBar
    int hotBarCorX;
    int hotBarCorY;
    int hotBarRezX;
    int hotBarRezY;

    //Block menu
    int blockMenuRezX;
    int blockMenuRezY;
    int blockMenuCorX;
    int blockMenuCorY;

    struct Button* inventoryButton;

    //Text
    int textScale;

    //Escape Menu
    struct Button** escapeMenuButtons;
};

void updateOnScreenUICords(struct GameData* gameData);

struct OnScreenUI* createOnScreenUI();

void renderOnScreenUI(struct GameData* gameData);

bool handleOnScreenUIInput(struct GameData* gameData, SDL_Event event);

#endif //EDIFICE_ONSCREENUI_H
