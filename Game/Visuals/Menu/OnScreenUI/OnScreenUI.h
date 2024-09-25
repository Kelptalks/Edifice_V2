//
// Created by Spencer on 9/24/2024.
//

#ifndef EDIFICE_ONSCREENUI_H
#define EDIFICE_ONSCREENUI_H

#include "../../../GameData.h"
#include "../MenuManager/MenuManger.h"

struct OnScreenUI{
    bool visible;

    struct Button* areaSelectButton;
    struct Button* blockEditingButton;
    struct Button* openBluePrintsButton;


    //Location and scaling vars
    int scale;

    int slotSpacedScale;
    int blockScale;
    int blockCenteringOffset;

    int hotBarCorX;
    int hotBarCorY;

    int blockMenuCorX;
    int blockMenuCorY;
};

void updateOnScreenUICords(struct GameData* gameData);

struct OnScreenUI* createOnScreenUI();

void renderOnScreenUI(struct GameData* gameData);

bool handleOnScreenUIInput(struct GameData* gameData, SDL_Event event);

#endif //EDIFICE_ONSCREENUI_H
