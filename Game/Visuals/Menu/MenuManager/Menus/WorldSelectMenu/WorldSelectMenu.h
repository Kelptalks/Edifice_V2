//
// Created by Spencer on 9/29/2024.
//

#ifndef EDIFICE_WORLDSELECTMENU_H
#define EDIFICE_WORLDSELECTMENU_H

#include "../../MenuManger.h"

struct WorldSelectMenu{
    int worldCount;
    struct Button** worldButtons;
    struct Button** worldDeleteButtons;

    struct Button* backButton;

};

struct WorldSelectMenu* createWorldSelectMenu();

void renderWorldSelectMenu(struct GameData* gameData);

void handleWorldSelectMenuInputs(struct GameData* gameData, SDL_Event event);


#endif //EDIFICE_WORLDSELECTMENU_H
