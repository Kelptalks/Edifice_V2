//
// Created by Spencer on 10/3/2024.
//

#ifndef EDIFICE_DRONETOOLMANAGER_H
#define EDIFICE_DRONETOOLMANAGER_H
#include "../Drone.h"

struct DroneToolData{
    int* blockMineTimes;
};

int addToolToDone(struct Drone* drone, enum DroneTool tool);

void removeToolToDone(struct Drone* drone, int index);

struct DroneToolData* createDroneToolData();

SDL_Rect getToolSrcRect(enum DroneTool droneTool);

#endif //EDIFICE_DRONETOOLMANAGER_H
