//
// Created by Spencer on 10/1/2024.
//

#include <malloc.h>
#include "Drone.h"
#include "../../Blocks/Blocks.h"
#include "../../Debuging/Test_Main.h"
#include "DroneInventoryManager/DroneInventoryManager.h"
#include "DroneToolManager/DroneToolManager.h"


struct Drone* createDrone(struct World* world, int x, int y, int z){
    struct Drone* drone = malloc(sizeof (struct Drone));

    reportBug("Creating Drone at (%i, %i, %i)\n", x, y, z);

    drone->reachRange = 1;
    drone->health = 50;
    drone->speed = 1;

    drone->fuel = 5000;
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

    addItemToInventory(drone, ItemGlass);
    addItemToInventory(drone, ItemGlass);
    addItemToInventory(drone, ItemGlass);

    addItemToInventory(drone, ItemDirt);
    addItemToInventory(drone, ItemDirt);
    addItemToInventory(drone, ItemDirt);
    addItemToInventory(drone, ItemDirt);
    addItemToInventory(drone, ItemDirt);
    addItemToInventory(drone, ItemDirt);
    addItemToInventory(drone, ItemDirt);
    addItemToInventory(drone, ItemDirt);

    addItemToInventory(drone, ItemBrick);
    addItemToInventory(drone, ItemPlantMatter);
    addItemToInventory(drone, ItemPlantMatter);
    addItemToInventory(drone, ItemPlantMatter);

    addToolToDone(drone, ToolStoneDrill);

    return drone;
}

int getBlockRelativeToDrone(struct World* world, struct Drone* drone, int x, int y, int z){
    bool inPositiveRange = x <= drone->reachRange && y <= drone->reachRange && z <= drone->reachRange;
    bool inNegativeRange = x >= -drone->reachRange && y >= -drone->reachRange && z >= -drone->reachRange;
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

    bool inPositiveRange = x <= drone->speed && y <= drone->speed && z <= drone->speed;
    bool inNegativeRange = x >= -drone->speed && y >= -drone->speed && z >= -drone->speed;

    if (inPositiveRange && inNegativeRange) {
        int blockToMineX = drone->worldX + x;
        int blockToMineY = drone->worldY + y;
        int blockToMineZ = drone->worldZ + z;

        enum Block mined = getBlockAtWorldCor(world, blockToMineX, blockToMineY, blockToMineZ);
        setBlockAtWorldCor(world, blockToMineX, blockToMineY, blockToMineZ, Air);
        addItemToInventory(drone, getBlockTypeToItem(mined));

        drone->busyTime = 20;
        drone->fuel-=5;
    }
}

int placeBlockRelativeToDrone(struct World* world, struct Drone* drone, int x, int y, int z, enum Block block){
    if (drone->busyTime > 0){
        return -3;
    }
    if (drone->fuel < 0){
        return -4;
    }
    bool inPositiveRange = x <= drone->speed && y <= drone->speed && z <= drone->speed;
    bool inNegativeRange = x >= -drone->speed && y >= -drone->speed && z >= -drone->speed;

    if (inPositiveRange && inNegativeRange) {
        int blockToMineX = drone->worldX + x;
        int blockToMineY = drone->worldY + y;
        int blockToMineZ = drone->worldZ + z;

        enum Block placeLocationBlock = getBlockAtWorldCor(world, blockToMineX, blockToMineY, blockToMineZ);
        if (placeLocationBlock == Air){
            setBlockAtWorldCor(world, blockToMineX, blockToMineY, blockToMineZ, block);
            drone->busyTime = 20;
            drone->fuel-=5;
        }
        else{
            return -2;
        }
    }
    return -1;
}

int useItemForFuel();

void tickDrone(struct World* world, struct Drone* drone){
    if (drone->busyTime > 0) {
        drone->busyTime--;
    }

    //Make drone fall if possible
    enum Block blockUnderDrone = getBlockAtWorldCor(world, drone->worldX, drone->worldY, drone->worldZ - 1);
    if (drone->health == 0){
        drone->speed = 0;
        drone->reachRange = 0;
    }

    if (blockUnderDrone == Air){
        moveDrone(world, drone, 0, 0, -1);
    }
}