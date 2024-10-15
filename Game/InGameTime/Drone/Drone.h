//
// Created by Spencer on 10/1/2024.
//

#include <lua.h>           // Lua's main API
#include <lauxlib.h>        // Auxiliary library
#include <lualib.h>         // Standard Lua libraries

#include "../../World/World.h"
#include "../../Blocks/Blocks.h"

#ifndef EDIFICE_DRONE_H
#define EDIFICE_DRONE_H

enum DroneTool{
    ToolNull,
    ToolStoneDrill,
    ToolStoneSaw,
    ToolIronDrill,
    ToolIronSaw,
    ToolIronBattery,
    ToolIronReceptacle,
    ToolIronCamera,
    ToolTitaniumDrill,
    ToolTitaniumSaw,
    ToolTitaniumBattery,
    ToolTitaniumReceptacle,
    ToolTitaniumCamera,
    ToolExplosiveCamera
};

enum DroneItem{
    ItemNull,
    ItemDirt,
    ItemPlantMatter,
    ItemLog,
    ItemStone,
    ItemStoneBrick,
    ItemBrick,
    ItemIronOar,
    ItemIronBar,
    ItemCopperOar,
    ItemCopperBar,
    ItemSand,
    ItemGlass,
    ItemTitaniumOre,
    ItemTitaniumBar,
    ItemPurpleLens,
    ItemCharcoal,
    ItemSulfur,
    ItemScaffolding,
    ItemDroneParts,
};

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
    enum DroneTool tools[3];

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

int droneCraftTool(struct World* world, struct Drone* drone, enum DroneTool tool) ;

int getDroneToolSlot(struct Drone* drone, int slot);

int getDroneInventoryItemCount(struct Drone* drone, enum DroneItem item);

void tickDrone(struct World* world, struct Drone* drone);




#endif //EDIFICE_DRONE_H
