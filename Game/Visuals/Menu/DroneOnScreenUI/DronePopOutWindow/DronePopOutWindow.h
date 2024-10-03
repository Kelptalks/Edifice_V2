//
// Created by Spencer on 10/3/2024.
//

#ifndef EDIFICE_DRONEPOPOUTWINDOW_H
#define EDIFICE_DRONEPOPOUTWINDOW_H

#include "SDL.h"
#include "../DroneOnScreenUI.h"

struct DronePopOutWindow{
    struct Drone* drone;
    int xCor;
    int yCor;

    int xRez;
    int yRez;

    float scale;

    int xDirection;
    int yDirection;

    int xGrabCor;
    int yGrabCor;

    bool grabbed;
    bool mouseOnExitButton;
    bool visible;

    int direction;
};

struct DronePopOutWindow* createDronePopOutWindow(struct Drone* drone, int xCor, int yCor, float scale);

void renderDroneWindow(struct GameData* gameData, struct DronePopOutWindow* droneWindow);

void renderDronesInventory(struct GameData* gameData, struct DronePopOutWindow* droneWindow);

void renderDronesBlocksInArea(struct GameData* gameData, struct DronePopOutWindow* droneWindow);

void renderDronePopOutWindow(struct GameData* gameData, struct DronePopOutWindow* dronePopOutWindow);

bool HandleDronePopOutMenuInputs(struct GameData* gameData, struct DronePopOutWindow* dronePopOutWindow, SDL_Event event);

#endif //EDIFICE_DRONEPOPOUTWINDOW_H
