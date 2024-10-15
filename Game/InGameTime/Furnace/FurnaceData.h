//
// Created by Spencer on 10/15/2024.
//

#ifndef FURNACEDATA_H
#define FURNACEDATA_H

#include "../Drone/Drone.h"
#include "../Furnace/Furnace.h"

struct FurnaceData {
    enum DroneItem* itemToSmeltedItem;


    struct Furnace** furnaces;
    int maxFurnaceCount;
    int currentFurnaceCount;
};

struct FurnaceData* createFurnaceData(struct World* world, int maxFurnaceCount);

struct Furnace* getFurnaceAtWorldCords(struct FurnaceData* furnaceData, int x, int y, int z);

void createFurnaceInFurnaceData(struct World* world, int x, int y, int z);

enum DroneItem getSmeltedItem(struct FurnaceData* furnaceData, enum DroneItem droneItem);

#endif //FURNACEDATA_H
