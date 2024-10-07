//
// Created by Spencer on 10/3/2024.
//

#ifndef EDIFICE_DRONETOOLMANAGER_H
#define EDIFICE_DRONETOOLMANAGER_H
#include "../Drone.h"
#include "SDL.h"


struct DroneItemRecipe {
    int totalItemTypes;

    int* itemCounts;
    enum DroneItem* itemsNeeded;
};

struct DroneItemRecipe* createItemRecipe(int totalItemTypes);
void addItemToRecipe(struct DroneItemRecipe* item_recipe, enum DroneItem item, int itemCount);

struct DroneToolData{
    int* blockMineTimes;
    int* toolMineTimeMods;
    struct DroneItemRecipe** itemRecipes;
};

int addToolToDone(struct Drone* drone, enum DroneTool tool);

void removeToolToDone(struct Drone* drone, int index);

int getBlockMineTime(struct DroneToolData* droneToolData, struct Drone* drone, enum Block block);

struct DroneToolData* createDroneToolData();

SDL_Rect getToolSrcRect(enum DroneTool droneTool);

#endif //EDIFICE_DRONETOOLMANAGER_H
