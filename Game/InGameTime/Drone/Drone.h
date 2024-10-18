//
// Created by Spencer on 10/1/2024.
//

#include <lua.h>           // Lua's main API
#include <lauxlib.h>        // Auxiliary library
#include <lualib.h>         // Standard Lua libraries

#include "../../World/World.h"
#include "../../Blocks/Blocks.h"
#include "../../Visuals/Camera/CameraData.h"
#include "DroneItemManager/DroneItemManager.h"

#ifndef EDIFICE_DRONE_H
#define EDIFICE_DRONE_H

int getTotalItemCount();

struct Drone{
    int id;
    int busyTime;

    int reachRange;
    int viewRange;
    int speed;
    int health;
    int inventorySize;

    int worldX;
    int worldY;
    int worldZ;
    int fuel;

    //Inventory
    enum DroneItem items[9];
    int itemCounts[9];
    enum DroneItem equipment[3];

    enum Direction direction;

    //BlockToMine
    bool mining;
    enum Block blockCurrentlyMining;
    int blockToMineX;
    int blockToMineY;
    int blockToMineZ;
};

struct Drone* createDrone(struct World* world, int x, int y, int z);

int getBlockRelativeToDrone(struct World* world, struct Drone* drone, int x, int y, int z);
int moveDrone(struct World* world, struct Drone* drone, int x, int y, int z);

int mineBlockRelativeToDrone(struct World* world, struct Drone* drone, int x, int y, int z);

int placeBlockRelativeToDrone(struct World* world, struct Drone* drone, int x, int y, int z, enum Block block);

int useItemForFuel(struct Drone* drone, enum DroneItem item, int quantity);

int droneCraftItem(struct World* world, struct Drone* drone, enum DroneItem item) ;

int getDroneToolSlot(struct Drone* drone, int slot);

int getDroneInventoryItemCount(struct Drone* drone, enum DroneItem item);

void tickDrone(struct World* world, struct Drone* drone);




#endif //EDIFICE_DRONE_H
