//
// Created by Spencer on 10/1/2024.
//

#include <malloc.h>
#include "Drone.h"
#include "../../Blocks/Blocks.h"
#include "../../Debuging/Test_Main.h"
#include "DroneInventoryManager/DroneInventoryManager.h"
#include "DroneToolManager/DroneToolManager.h"
#include "../Drone/DroneData.h"


struct Drone* createDrone(struct World* world, int x, int y, int z){
    struct Drone* drone = malloc(sizeof (struct Drone));

    reportBug("Creating Drone at (%i, %i, %i)\n", x, y, z);

    drone->reachRange = 1;
    drone->viewRange = 4;
    drone->health = 50;
    drone->speed = 1;
    drone->busyTime = 0;
    drone->inventorySize = 9;

    drone->fuel = 10;
    drone->worldX = x;
    drone->worldY = y;
    drone->worldZ = z;

    setBlockAtWorldCor(world, x, y, z, DroneLeftForward);

    for (int i = 0; i < 3; i++){
        drone->tools[i] = 0;
    }

    for (int i = 0; i < 9; i++){
        drone->items[i] = ItemNull;
        drone->itemCounts[i] = 0;
    }

    return drone;
}

int getBlockRelativeToDrone(struct World* world, struct Drone* drone, int x, int y, int z){
    bool inPositiveRange = x <= drone->viewRange && y <= drone->viewRange && z <= drone->viewRange;
    bool inNegativeRange = x >= -drone->viewRange && y >= -drone->viewRange && z >= -drone->viewRange;
    if (inPositiveRange && inNegativeRange) {
        return getBlockAtWorldCor(world, drone->worldX + x, drone->worldY + y, drone->worldZ + z);
    }
    else{
        return -1;
    }
}


int moveDrone(struct World* world, struct Drone* drone, int x, int y, int z){
    if (drone->busyTime > 0){
        return -3;
    }
    if (drone->fuel < 0){
        return -4;
    }

    bool inPositiveRange = x <= drone->speed && y <= drone->speed && z <= drone->speed;
    bool inNegativeRange = x >= -drone->speed && y >= -drone->speed && z >= -drone->speed;
    if (inPositiveRange && inNegativeRange) {
        int newDroneX = drone->worldX + x;
        int newDroneY = drone->worldY + y;
        int newDroneZ = drone->worldZ + z;

        if (getBlockAtWorldCor(world, newDroneX, newDroneY, newDroneZ) == Air) {
            if (x > 0) {
                setBlockAtWorldCor(world, newDroneX, newDroneY, newDroneZ, DroneLeftForward);
            }
            else if (y > 0){
                setBlockAtWorldCor(world, newDroneX, newDroneY, newDroneZ, DroneRightForward);
            }
            else if (x < 0){
                setBlockAtWorldCor(world, newDroneX, newDroneY, newDroneZ, DroneRightBack);
            }
            else if (y < 0){
                setBlockAtWorldCor(world, newDroneX, newDroneY, newDroneZ, DroneLeftBack);
            }
            else{
                enum Block currentDroneTexture = getBlockAtWorldCor(world, drone->worldX, drone->worldY, drone->worldZ);
                setBlockAtWorldCor(world, newDroneX, newDroneY, newDroneZ, currentDroneTexture);
            }
            setBlockAtWorldCor(world, drone->worldX, drone->worldY, drone->worldZ, Air);
            drone->worldX = newDroneX;
            drone->worldY = newDroneY;
            drone->worldZ = newDroneZ;
            drone->busyTime = 5;
            drone->fuel-=1;
            return 0;
        }
        else{
            return -2;
        }
    }
    else{
        return -1;
    }
}

int mineBlockRelativeToDrone(struct World* world, struct Drone* drone, int x, int y, int z){
    if (drone->busyTime > 0){
        return -3;
    }
    if (drone->fuel < 0){
        return -4;
    }

    bool inPositiveRange = x <= drone->reachRange && y <= drone->reachRange && z <= drone->reachRange;
    bool inNegativeRange = x >= -drone->reachRange && y >= -drone->reachRange && z >= -drone->reachRange;

    if (inPositiveRange && inNegativeRange) {
        int blockToMineX = drone->worldX + x;
        int blockToMineY = drone->worldY + y;
        int blockToMineZ = drone->worldZ + z;

        enum Block blockToMine = getBlockAtWorldCor(world, blockToMineX, blockToMineY, blockToMineZ);

        if (blockToMine != Air) {
            drone->busyTime = getBlockMineTime(world->droneData->droneToolData, drone, blockToMine);
            drone->mining = true;
            drone->blockCurrentlyMining = blockToMine;
            drone->blockToMineX = blockToMineX;
            drone->blockToMineY = blockToMineY;
            drone->blockToMineZ = blockToMineZ;
        }
        else {
            return -2;
        }
    }
    return -1;
}

int placeBlockRelativeToDrone(struct World* world, struct Drone* drone, int x, int y, int z, enum Block block){
    if (drone->busyTime > 0){
        return -3;
    }
    if (drone->fuel < 0){
        return -4;
    }
    bool inPositiveRange = x <= drone->reachRange && y <= drone->reachRange && z <= drone->reachRange;
    bool inNegativeRange = x >= -drone->reachRange && y >= -drone->reachRange && z >= -drone->reachRange;

    if (inPositiveRange && inNegativeRange) {
        struct DroneToolData* droneToolData = world->droneData->droneToolData;
        int blockToMineX = drone->worldX + x;
        int blockToMineY = drone->worldY + y;
        int blockToMineZ = drone->worldZ + z;

        enum Block placeLocationBlock = getBlockAtWorldCor(world, blockToMineX, blockToMineY, blockToMineZ);
        if (placeLocationBlock == Air){
            if (removeItemFromInventory(drone, droneToolData->blockPlacementCostItems[block], droneToolData->blockPlacementCostQuantities[block]) == 1) {
                setBlockAtWorldCor(world, blockToMineX, blockToMineY, blockToMineZ, block);
                drone->busyTime = 30;
                drone->fuel-=5;
                return 1;
            }
            else {
                return -5;
            }
        }
        else{
            return -2;
        }
    }
    return -1;
}

int useItemForFuel(struct Drone* drone, enum DroneItem item, int quantity) {

    if (removeItemFromInventory(drone, item, quantity) == 1) {
        if (item == ItemPlantMatter) {
            drone->fuel+=25;
            return 1;
        }
        else if (item == ItemLog) {
            drone->fuel += 200;
            return 1;
        }
    }
    return -1;


}

int droneCraftTool(struct World* world, struct Drone* drone, enum DroneTool tool) {
    struct DroneItemRecipe* droneItemRecipe = world->droneData->droneToolData->itemRecipes[tool];

    int hasIngredient = 0;
    //Loop through all needed ingredients
    for (int i = 0; i < droneItemRecipe->totalItemTypes; i++) {
        enum DroneItem itemTypeNeeded = droneItemRecipe->itemsNeeded[i];
        int itemCountNeeded = droneItemRecipe->itemCounts[i];

        //Loop through drone inventory and check for ingredient
        for (int t = 0; t < drone->inventorySize; t++) {
            if (drone->items[t] == itemTypeNeeded) {
                if (drone->itemCounts[t] >= itemCountNeeded) {
                    hasIngredient++;
                }
            }
        }
    }

    if (hasIngredient >= droneItemRecipe->totalItemTypes) {
        for (int i = 0; i < droneItemRecipe->totalItemTypes; i++) {
            enum DroneItem itemTypeNeeded = droneItemRecipe->itemsNeeded[i];
            int itemCountNeeded = droneItemRecipe->itemCounts[i];
            removeItemFromInventory(drone, itemTypeNeeded, itemCountNeeded);
        }
        addToolToDone(drone, tool);
        drone->busyTime += 50;
        return 1;
    }
    else {
        return -1;
    }
}

int getDroneToolSlot(struct Drone* drone, int slot){
    if (slot < 3) {
        if (drone->tools[slot] == ToolNull) {
            return -1;
        }
        else {
            return drone->tools[slot];
        }
    }
    return -1;
}

int getDroneInventoryItemCount(struct Drone* drone, enum DroneItem item){
    for (int t = 0; t < drone->inventorySize; t++) {
        if (drone->items[t] == item) {
            return drone->itemCounts[t];
        }
    }
    return -1;
}

void tickDrone(struct World* world, struct Drone* drone){
    //Make drone fall if possible
    enum Block blockUnderDrone = getBlockAtWorldCor(world, drone->worldX, drone->worldY, drone->worldZ - 1);
    if (drone->health == 0){
        drone->speed = 0;
        drone->reachRange = 0;
    }
    if (blockUnderDrone == Air){
        drone->busyTime = 0;
        moveDrone(world, drone, 0, 0, -1);
        drone->busyTime++;
    }

    if (drone->busyTime > 0) {
        drone->busyTime--;
    }
    if (drone->mining && drone->busyTime == 0){
        setBlockAtWorldCor(world, drone->blockToMineX, drone->blockToMineY, drone->blockToMineZ, Air);
        addItemToInventory(drone, getBlockTypeToItem(drone->blockCurrentlyMining));
        drone->mining = false;
    }

    //reportBug("drone %i\n", drone->mining);
}