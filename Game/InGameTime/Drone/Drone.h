//
// Created by Spencer on 10/1/2024.
//

#include <lua.h>           // Lua's main API
#include <lauxlib.h>        // Auxiliary library
#include <lualib.h>         // Standard Lua libraries

#include "../../World/World.h"

#ifndef EDIFICE_DRONE_H
#define EDIFICE_DRONE_H

enum DroneItem{
    ItemDirt,
    ItemLog,
    ItemStone,
    ItemStoneBrick,
    ItemBrick,
    ItemIron,
    ItemGlass,
};

enum DroneTools{
    //Tools
    StoneDrill,
    IronDrill,
    StoneSaw,
    IronSaw
};

struct Drone{
    int id;

    int reachRange;
    int speed;
    int health;

    int worldX;
    int worldY;
    int worldZ;
    int fuel;

    //Inventory
    enum DroneItem items[9];
    int itemCounts[9];
    enum DroneTools tools[3];
};

struct Drone* createDrone(struct World* world, int x, int y, int z);

int getBlockRelativeToDrone(struct World* world, struct Drone* drone, int x, int y, int z);
int moveDrone(struct World* world, struct Drone* drone, int x, int y, int z);

int mineBlockRelativeToDrone();
int placeBlockRelativeToDrone();

int useItemForFuel();

void tickDrone(struct World* world, struct Drone* drone);


#endif //EDIFICE_DRONE_H
