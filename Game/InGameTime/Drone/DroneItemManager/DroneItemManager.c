//
// Created by Spencer on 10/18/2024.
//

#include "DroneItemManager.h"

#include <stdlib.h>

#include "../../../Debuging/Test_Main.h"


//Get the total items that exist
int getTotalToolCount() {
    return 14;
}

int getTotalItemCount() {
    return 33;
}

//Set the poperties of an item
void setItemProperties(struct DroneItemData* droneItemData, enum DroneItem item, int stackSize, bool isCraftable, bool isTool) {
    droneItemData->itemMaxStackSize[item] = stackSize;
    droneItemData->craftable[item] = isCraftable;
    droneItemData->tool[item] = isTool;
}

//Allocate arrays for the drone item array struct
int allocateDroneItemDataArrays(struct DroneItemData* droneItemData) {
    //setup item max stack size array
    droneItemData->itemMaxStackSize = malloc(getTotalItemCount() * sizeof(bool));
    if (droneItemData->itemMaxStackSize == NULL) {
        reportBug("failed to malloc item max size array\n");
        return -1;
    }

    //Setup if craftable array
    droneItemData->craftable = malloc(getTotalItemCount() * sizeof(bool));
    if (droneItemData->craftable == NULL) {
        reportBug("failed to malloc item craftable array\n");
        return -1;
    }

    //Setup if tool array
    droneItemData->tool = malloc(getTotalItemCount() * sizeof(bool));
    if (droneItemData->tool == NULL) {
        reportBug("failed to malloc item craftable array\n");
        return -1;
    }
    return 1;
}

void setUpAllItemsData(struct DroneItemData* droneItemData){

    // Tools - Stack size 1
    setItemProperties(droneItemData, ItemNull, 1, false, false);
    setItemProperties(droneItemData, ToolStoneDrill, 1, true, true);
    setItemProperties(droneItemData, ToolStoneSaw, 1, true, true);
    setItemProperties(droneItemData, ToolIronDrill, 1, true, true);
    setItemProperties(droneItemData, ToolIronSaw, 1, true, true);
    setItemProperties(droneItemData, ToolIronBattery, 1, true, true);
    setItemProperties(droneItemData, ToolIronReceptacle, 1, true, true);
    setItemProperties(droneItemData, ToolIronCamera, 1, true, true);
    setItemProperties(droneItemData, ToolTitaniumDrill, 1, true, true);
    setItemProperties(droneItemData, ToolTitaniumSaw, 1, true, true);
    setItemProperties(droneItemData, ToolTitaniumBattery, 1, true, true);
    setItemProperties(droneItemData, ToolTitaniumReceptacle, 1, true, true);
    setItemProperties(droneItemData, ToolTitaniumCamera, 1, true, true);
    setItemProperties(droneItemData, ToolExplosive, 5, true, true);

    // Items - Stack size 64
    setItemProperties(droneItemData, ItemDirt, 512, false, false);
    setItemProperties(droneItemData, ItemPlantMatter, 1024, false, false);
    setItemProperties(droneItemData, ItemLog, 256, false, false);
    setItemProperties(droneItemData, ItemStone, 256, false, false);
    setItemProperties(droneItemData, ItemStoneBrick, 512, false, false);
    setItemProperties(droneItemData, ItemBrick, 512, false, false);
    setItemProperties(droneItemData, ItemIronOar, 64, false, false);
    setItemProperties(droneItemData, ItemIronBar, 128, false, false);
    setItemProperties(droneItemData, ItemCopperOar, 64, false, false);
    setItemProperties(droneItemData, ItemCopperBar, 128, false, false);
    setItemProperties(droneItemData, ItemSand, 256, false, false);
    setItemProperties(droneItemData, ItemGlass, 512, false, false);
    setItemProperties(droneItemData, ItemTitaniumOre, 256, false, false);
    setItemProperties(droneItemData, ItemTitaniumBar, 512, false, false);
    setItemProperties(droneItemData, ItemPurpleLens, 256, false, false);
    setItemProperties(droneItemData, ItemCharcoal, 1024, false, false);
    setItemProperties(droneItemData, ItemSulfur, 256, false, false);
    setItemProperties(droneItemData, ItemScaffolding, 256, true, false);
    setItemProperties(droneItemData, ItemDroneParts, 1, true, false);
}

struct DroneItemData* createDroneItemData() {
    struct DroneItemData* droneItemData = malloc(sizeof(struct DroneItemData));

    //Setup Drone Item data struct
    if (droneItemData == NULL) {
        reportBug("Failed to create drone item data struct\n");
        return NULL;
    }

    //Setup Drone Item data arrays
    if (allocateDroneItemDataArrays(droneItemData) == -1) {
        reportBug("Failed to allocate drones Item Arrays\n");
        return NULL;
    }

    setUpAllItemsData(droneItemData);

    //SetUp each blocks values

    return droneItemData;
}


bool isTool(struct DroneItemData* droneItemData, enum DroneItem item) {
    return droneItemData->tool[item];
}

bool isCraftable(struct DroneItemData* droneItemData, enum DroneItem item) {
    return droneItemData->craftable[item];
}

int getItemMaxStackSize(struct DroneItemData* droneItemData, enum DroneItem item) {
    return droneItemData->itemMaxStackSize[item];
}

SDL_Rect getDroneItemSrcRect(enum DroneItem item){
    SDL_Rect srcRect = {item * 16, 1216, 16, 16};
    return srcRect;
}
