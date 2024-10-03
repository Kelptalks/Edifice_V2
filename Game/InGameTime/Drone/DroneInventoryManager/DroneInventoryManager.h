//
// Created by Spencer on 10/2/2024.
//

#ifndef EDIFICE_DRONEINVENTORYMANAGER_H
#define EDIFICE_DRONEINVENTORYMANAGER_H

#include "../Drone.h"
#include "../../../Blocks/Blocks.h"


SDL_Rect getSrcRectOfItemSprite(enum DroneItem item);

enum DroneItem getBlockTypeToItem(enum Block block);

void addItemToInventory(struct Drone* drone, enum DroneItem item);

enum DroneItem getItemInSlot(struct Drone* drone, int slot);

int getItemCountInSlot(struct Drone* drone, int slot);

#endif //EDIFICE_DRONEINVENTORYMANAGER_H
