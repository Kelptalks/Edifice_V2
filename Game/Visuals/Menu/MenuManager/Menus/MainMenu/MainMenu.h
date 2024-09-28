//
// Created by Spencer on 8/7/2024.
//

#ifndef EDIFICE_MAINMENU_H
#define EDIFICE_MAINMENU_H

#include <SDL_events.h>
#include "../../../../../GameData.h"

struct MainMenu{
    struct Button* startButton;
    struct Button* settingsButton;
    struct Button* exitButton;

    int animationFrame;
};

struct MainMenu* createMainMenu();

void renderMainMenu(struct GameData* gameData);

void handleInputMainMenu(struct GameData* gameData, SDL_Event event);

#endif //EDIFICE_MAINMENU_H
