//
// Created by Spencer on 10/15/2024.
//

#include "FurnaceData.h"

#include <stdlib.h>


struct FurnaceData* createFurnaceData(struct World* world, int maxFurnaceCount){
    struct FurnaceData* furnaceData = malloc(sizeof(struct FurnaceData));



    //Setup furnace array
    furnaceData->furnaces = calloc(maxFurnaceCount, sizeof(struct Furnace*));
    furnaceData->maxFurnaceCount = maxFurnaceCount;
    furnaceData->currentFurnaceCount = 0;


    //Setup item to smelted item conversion array
    furnaceData->itemToSmeltedItem = malloc(sizeof(enum DroneItem) * getTotalItemCount());
    furnaceData->itemToSmeltedItem[ItemNull] = ItemNull;
    furnaceData->itemToSmeltedItem[ItemDirt] = ItemDirt;
    furnaceData->itemToSmeltedItem[ItemPlantMatter] = ItemCharcoal;
    furnaceData->itemToSmeltedItem[ItemLog] = ItemCharcoal;
    furnaceData->itemToSmeltedItem[ItemStone] = ItemStoneBrick;
    furnaceData->itemToSmeltedItem[ItemStoneBrick] = ItemStoneBrick;
    furnaceData->itemToSmeltedItem[ItemBrick] = ItemBrick;

    furnaceData->itemToSmeltedItem[ItemIronOar] = ItemIronBar;
    furnaceData->itemToSmeltedItem[ItemIronBar] = ItemIronBar;
    furnaceData->itemToSmeltedItem[ItemCopperOar] = ItemCopperBar;
    furnaceData->itemToSmeltedItem[ItemCopperBar] = ItemCopperBar;

    furnaceData->itemToSmeltedItem[ItemSand] = ItemGlass;
    furnaceData->itemToSmeltedItem[ItemGlass] = ItemGlass;
    furnaceData->itemToSmeltedItem[ItemTitaniumOre] = ItemTitaniumBar;
    furnaceData->itemToSmeltedItem[ItemTitaniumBar] = ItemTitaniumBar;

    furnaceData->itemToSmeltedItem[ItemPurpleLens] = ItemPurpleLens;
    furnaceData->itemToSmeltedItem[ItemCharcoal] = ItemCharcoal;
    furnaceData->itemToSmeltedItem[ItemSulfur] = ItemNull;
    furnaceData->itemToSmeltedItem[ItemScaffolding] = ItemCharcoal;

    furnaceData->itemToSmeltedItem[ItemDroneParts] = ItemIronBar;



    return furnaceData;
}

struct Furnace* getFurnaceAtWorldCords(struct FurnaceData* furnaceData, int x, int y, int z) {
    for (int i = 0; i < furnaceData->currentFurnaceCount; i++) {
        struct Furnace* furnace = furnaceData->furnaces[i];
        if (furnace->xCor == x && furnace->yCor == y && furnace->zCor == z) {
            return furnace;
        }
    }

    return NULL;
}

void createFurnaceInFurnaceData(struct World* world, int x, int y, int z){
    struct FurnaceData* furnaceData = world->furnaceData;
    furnaceData->furnaces[furnaceData->currentFurnaceCount] = createFurnace(world, x, y, z);
    furnaceData->currentFurnaceCount++;
}

enum DroneItem getSmeltedItem(struct FurnaceData* furnaceData, enum DroneItem droneItem) {
    return furnaceData->itemToSmeltedItem[droneItem];
}
