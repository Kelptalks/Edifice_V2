//
// Created by Spencer on 10/18/2024.
//

#ifndef DRONEITEMMANAGER_H
#define DRONEITEMMANAGER_H
#include <SDL_rect.h>
#include <stdbool.h>

enum DroneItem{
    ItemNull,

    //Tools
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
    ToolExplosive,

    //Items
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
    ItemGoldOar,
    ItemGoldBar,
};

struct DroneItemData {
    // Max size an item can stack to
    int* itemMaxStackSize;

    // If tool
    bool* tool;

    // If it is craftable
    bool* craftable;
    bool* smeltable;
};

int getTotalToolCount();

int getTotalItemCount();

struct DroneItemData* createDroneItemData();

bool isTool(struct DroneItemData* droneItemData, enum DroneItem item);

bool isCraftable(struct DroneItemData* droneItemData, enum DroneItem item);

int getItemMaxStackSize(struct DroneItemData* droneItemData, enum DroneItem item);

SDL_Rect getDroneItemSrcRect(enum DroneItem item);


#endif //DRONEITEMMANAGER_H
