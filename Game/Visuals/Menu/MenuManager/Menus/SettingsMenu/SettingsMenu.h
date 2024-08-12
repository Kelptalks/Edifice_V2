//
// Created by Spencer on 8/12/2024.
//

#ifndef EDIFICE_SETTINGSMENU_H
#define EDIFICE_SETTINGSMENU_H

#include "../../MenuManger.h"

struct SettingsMenu* createSettingsMenu();

struct SettingsMenu{
    struct ScrollWheel* viewDistanceScrollWheel;
    struct Button* backButton;
};

void renderSettingsMenu(struct GameData* gameData);

void handleInputSettingsMenu(struct GameData* gameData, SDL_Event event);

#endif //EDIFICE_SETTINGSMENU_H
