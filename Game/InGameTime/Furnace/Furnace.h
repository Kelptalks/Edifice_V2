//
// Created by Spencer on 10/15/2024.
//

#ifndef FURNACE_H
#define FURNACE_H

#include "../Drone/Drone.h"
#include "../Furnace/FurnaceData.h"


struct Furnace {

    int fuel;
    int busyTime;

    int xCor;
    int yCor;
    int zCor;

    enum DroneItem itemBeingSmelted;
};

struct Furnace* createFurnace(struct World* world, int x, int y, int z);

void tickFurnace(struct World* world, struct Furnace* furnace);

int droneAddSmeltingFuelToFurnace(struct Drone* drone, struct Furnace* furnace, enum DroneItem item, int quantity);

int droneAddSmeltingItemToFurnace(struct Drone* drone, struct Furnace* furnace, enum DroneItem item);

int removeSmeltingItemFromFurnace(struct DroneData* droneData, struct Drone* drone, struct Furnace* furnace);

#endif //FURNACE_H
