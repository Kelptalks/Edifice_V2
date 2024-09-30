//
// Created by Spencer on 9/30/2024.
//

#ifndef EDIFICE_WORLDCREATEMENU_H
#define EDIFICE_WORLDCREATEMENU_H

#include "../../MenuManger.h"

struct WorldCreateMenu{
    int worldScale;
    struct Button* increaseWorldScale;
    struct Button* decreaseWorldScale;

    int roughness;
    struct Button* increaseRoughnessScale;
    struct Button* decreaseRoughnessScale;

    struct Button* createWorld;

    struct Button* backToMenuButton;
};

struct WorldCreateMenu* createWorldCreateMenu();

void renderWorldCreateMenu(struct GameData* gameData);

void handleWorldCreateMenuInputs(struct GameData* gameData, SDL_Event event);

#endif //EDIFICE_WORLDCREATEMENU_H
