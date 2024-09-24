//
// Created by Spencer on 9/24/2024.
//

#ifndef EDIFICE_ONSCREENUI_H
#define EDIFICE_ONSCREENUI_H

#include "../../../GameData.h"
#include "../MenuManager/MenuManger.h"

struct OnScreenUI{
    struct Button* areaSelectButton;
    struct Button* blockEditingButton;
    struct Button* openBluePrintsButton;

};

void renderOnScreenUI(struct GameData* gameData);

void handleOnScreenUIInput(SDL_Event* event);

#endif //EDIFICE_ONSCREENUI_H
