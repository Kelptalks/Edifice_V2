//
// Created by Spencer on 10/15/2024.
//

#include "Furnace.h"

#include <stdlib.h>

#include "../../Debuging/Test_Main.h"
#include "../Drone/DroneInventoryManager/DroneInventoryManager.h"

struct Furnace* createFurnace(struct World* world, int x, int y, int z) {
    struct Furnace* furnace = malloc(sizeof(struct Furnace));

    furnace->fuel = 1;
    furnace->busyTime = 0;
    furnace->itemBeingSmelted = ItemNull;

    furnace->xCor = x;
    furnace->yCor = y;
    furnace->zCor = z;

    setBlockAtWorldCor(world, x, y, z, StoneFurnaceOff);
    return furnace;
}

void tickFurnace(struct World* world, struct Furnace* furnace) {
    if (furnace->fuel > 0) {
        furnace->fuel--;
        furnace->busyTime--;
        setBlockAtWorldCor(world, furnace->xCor, furnace->yCor, furnace->zCor, StoneFurnaceOn);
        if (furnace->busyTime <= 0) {
            furnace->itemBeingSmelted = getSmeltedItem(world->furnaceData, furnace->itemBeingSmelted);
        }
    }
    else {
        setBlockAtWorldCor(world, furnace->xCor, furnace->yCor, furnace->zCor, StoneFurnaceOff);
    }
}

int droneAddSmeltingFuelToFurnace(struct Drone* drone, struct Furnace* furnace, enum DroneItem item, int quantity){
    if (drone->busyTime > 0){
        return -3;
    }
    if (drone->fuel < 0){
        return -4;
    }
    if (removeItemFromInventory(drone, item, quantity) == 1) {
        if (item == ItemPlantMatter) {
            furnace->fuel+=50;
            drone->busyTime = 5 * quantity;
            return 1;
        }
        if (item == ItemLog) {
            furnace->fuel += 300;
            drone->busyTime = 5 * quantity;
            return 1;
        }
        return -7;
    }
    return -1;
}

int droneAddSmeltingItemToFurnace(struct Drone* drone, struct Furnace* furnace, enum DroneItem item){
    if (drone->busyTime > 0){
        return -3;
    }
    if (drone->fuel < 0){
        return -4;
    }
    if (furnace->itemBeingSmelted != ItemNull) {
        return -2;
    }
    //If removing the item from the drones inventory is successful
    if (removeItemFromInventory(drone, item, 1) == 1){
        furnace->itemBeingSmelted = item;
        furnace->busyTime = 50;
        return 1;
    }
    return -1;
}


int removeSmeltingItemFromFurnace(struct DroneData* droneData, struct Drone* drone, struct Furnace* furnace){
    if (drone->busyTime > 0){
        return -3;
    }
    if (drone->fuel < 0){
        return -4;
    }
    addItemToInventory(droneData, drone, furnace->itemBeingSmelted, 1);
    furnace->itemBeingSmelted = ItemNull;

    return 1;
}