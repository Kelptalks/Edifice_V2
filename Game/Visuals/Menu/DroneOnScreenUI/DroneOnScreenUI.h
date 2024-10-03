//
// Created by Spencer on 10/2/2024.
//

#ifndef EDIFICE_DRONEONSCREENUI_H
#define EDIFICE_DRONEONSCREENUI_H

#include <stdbool.h>
#include "SDL.h"
#include "../../../GameData.h"
#include "DronePopOutWindow/DronePopOutWindow.h"

struct DroneOnScreenUI{
    bool visible;

    int maxDroneWindows;
    int currentDroneWindowCount;
    struct DronePopOutWindow** dronePopOutWindow;
};

void updateDroneOnScreenUI(struct GameData* gameData);

struct DroneOnScreenUI* createDroneOnScreenUI();

void renderDroneOnScreenUI(struct GameData* gameData);

bool handleDroneOnScreenUI(struct GameData* gameData, SDL_Event event);

#endif //EDIFICE_DRONEONSCREENUI_H
