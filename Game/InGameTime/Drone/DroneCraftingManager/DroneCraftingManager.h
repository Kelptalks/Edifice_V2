//
// Created by Spencer on 10/18/2024.
//

#ifndef DRONECRAFTINGMANAGER_H
#define DRONECRAFTINGMANAGER_H

#include "../DroneItemManager/DroneItemManager.h"
#include "../DroneInventoryManager/DroneInventoryManager.h"
#include "../DroneData.h"

struct DroneItemRecipe  {
    int uniqueItems;

    enum DroneItem* items;
    int* itemQuantitys;

    int amountPerCraft;
};

struct DroneCraftingData {
    struct DroneItemRecipe* droneItemRecipes;
};

struct DroneCraftingData* createDroneCraftingData();

int droneAttemptCraftItem(struct DroneData* droneData, struct Drone* drone, enum DroneItem itemToCraft);

#endif //DRONECRAFTINGMANAGER_H
