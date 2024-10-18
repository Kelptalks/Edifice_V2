//
// Created by Spencer on 10/18/2024.
//


#include "DroneBlockProperties.h"

#include <stdlib.h>

#include "../../../Debuging/Test_Main.h"

int setUpDroneBlockPropertiesArrays(struct DroneBlockProperties* droneBlockProperties) {
    const int blocksCount = getTotalBlockCount();

    droneBlockProperties->solid = malloc( blocksCount * sizeof(bool));
    if (droneBlockProperties->solid == NULL) {
        reportBug("Failed to create solid Array");
        return -1;
    }

    droneBlockProperties->mineTime = malloc( blocksCount * sizeof(bool));
    if (droneBlockProperties->mineTime == NULL) {
        reportBug("Failed to create mineTime Array");
        return -1;
    }

    droneBlockProperties->toolLevelToMine = malloc( blocksCount * sizeof(int));
    if (droneBlockProperties->toolLevelToMine == NULL) {
        reportBug("Failed to create toolLevelToMine Array");
        return -1;
    }

    droneBlockProperties->itemOfBlock = malloc( blocksCount * sizeof(enum DroneItem));
    if (droneBlockProperties->itemOfBlock == NULL) {
        reportBug("Failed to create itemOfBlock Array");
        return -1;
    }

    droneBlockProperties->itemCountPerBlock = malloc( blocksCount * sizeof(int));
    if (droneBlockProperties->itemCountPerBlock == NULL) {
        reportBug("Failed to create itemCountPerBlock Array");
        return -1;
    }

    droneBlockProperties->walkSpeedOnBlock = malloc( blocksCount * sizeof(int));
    if (droneBlockProperties->walkSpeedOnBlock == NULL) {
        reportBug("Failed to create walkSpeedOnBlock Array");
        return -1;
    }
    return 1;
}

void setDroneBlockProperty(struct DroneBlockProperties* blockProperties, enum Block block, bool solid, int mineTime, int toolLevelToMine, enum DroneItem itemOfBlock, int itemCountPerBlock, int blockWalkSpeed) {
    blockProperties->solid[block] = solid;
    blockProperties->mineTime[block] = mineTime;
    blockProperties->toolLevelToMine[block] = toolLevelToMine;
    blockProperties->itemOfBlock[block] = itemOfBlock;
    blockProperties->itemCountPerBlock[block] = itemCountPerBlock;
    blockProperties->walkSpeedOnBlock[block] = blockWalkSpeed;
}

void setUpDroneBlockProperties(struct DroneBlockProperties* blockProperties) {
    // Basic blocks
    setDroneBlockProperty(blockProperties, Air, false, 0, 0, ItemNull, 0, 3);
    setDroneBlockProperty(blockProperties, Dirt, true, 50, 1, ItemDirt, 1, 20);
    setDroneBlockProperty(blockProperties, CrackedEarth, true, 50, 1, ItemDirt, 1, 15);
    setDroneBlockProperty(blockProperties, Hive, true, 75, 1, ItemPlantMatter, 1, 30);
    setDroneBlockProperty(blockProperties, Cobble, true, 125, 1, ItemStone, 2, 10);
    setDroneBlockProperty(blockProperties, Core, true, 9999, 3, ItemNull, 1, 999);
    setDroneBlockProperty(blockProperties, Sand, true, 30, 1, ItemSand, 1, 30);
    setDroneBlockProperty(blockProperties, Debug, false, 0, 0, ItemNull, 0, 999);

    // Stones
    setDroneBlockProperty(blockProperties, Granite, true, 150, 2, ItemStone, 1, 8);
    setDroneBlockProperty(blockProperties, Stone, true, 100, 1, ItemStone, 1, 12);
    setDroneBlockProperty(blockProperties, Magma, true, 75, 3, ItemStoneBrick, 1, 500);

    // Grasses
    setDroneBlockProperty(blockProperties, GreenGrass, true, 65, 1, ItemDirt, 1, 25);
    setDroneBlockProperty(blockProperties, BlueGrass, true, 65, 1, ItemDirt, 1, 25);

    // Trees
    setDroneBlockProperty(blockProperties, Leave, true, 20, 0, ItemPlantMatter, 1, 50);
    setDroneBlockProperty(blockProperties, PurpleWood, true, 500, -2, ItemLog, 2, 6);
    setDroneBlockProperty(blockProperties, PurpleWoodPlanks, true, 500, -2, ItemLog, 1, 6);
    setDroneBlockProperty(blockProperties, BrownWood, true, 100, -1, ItemLog, 2, 8);
    setDroneBlockProperty(blockProperties, BrownWoodPlanks, true, 100, -1, ItemLog, 1, 8);

    // Large Dandi
    setDroneBlockProperty(blockProperties, Dandi, true, 10, 1, ItemPlantMatter, 1, 100);
    setDroneBlockProperty(blockProperties, DandiStem, true, 15, 1, ItemPlantMatter, 1, 30);

    // Large Mushrooms
    setDroneBlockProperty(blockProperties, MushroomStem, true, 20, 1, ItemPlantMatter, 1, 20);
    setDroneBlockProperty(blockProperties, BlueMushroomBlock, true, 25, 1, ItemPlantMatter, 1, 20);
    setDroneBlockProperty(blockProperties, PinkMushroomBlock, true, 25, 1, ItemPlantMatter, 1, 20);

    // Large Fungi
    setDroneBlockProperty(blockProperties, Fungi, true, 15, 1, ItemPlantMatter, 1, 20);

    // Transparent Plants
    setDroneBlockProperty(blockProperties, Water, false, 5, 0, ItemNull, 0, 100);
    setDroneBlockProperty(blockProperties, YellowFlowers, false, 5, 0, ItemPlantMatter, 1, 50);
    setDroneBlockProperty(blockProperties, WhiteFlowers, false, 5, 0, ItemPlantMatter, 1, 50);
    setDroneBlockProperty(blockProperties, Mushroom, false, 5, 0, ItemPlantMatter, 1, 50);
    setDroneBlockProperty(blockProperties, Flour, true, 10, 0, ItemPlantMatter, 1, 50);
    setDroneBlockProperty(blockProperties, Glass, true, 25, 1, ItemGlass, 1, 50);
    setDroneBlockProperty(blockProperties, Bulb, true, 30, 0, ItemGlass, 1, 50);
    setDroneBlockProperty(blockProperties, Rock, true, 10, 0, ItemStone, 1, 50);

    // Metals
    setDroneBlockProperty(blockProperties, Iron, true, 200, 3, ItemIronBar, 1, 10);
    setDroneBlockProperty(blockProperties, Copper, true, 200, 2, ItemCopperBar, 1, 10);

    // Miscellaneous blocks
    setDroneBlockProperty(blockProperties, MudBrick, true, 150, 1, ItemBrick, 1, 8);
    setDroneBlockProperty(blockProperties, ClayBrick, true, 200, 2, ItemBrick, 2, 8);
    setDroneBlockProperty(blockProperties, Coral, true, 50, 1, ItemPlantMatter, 1, 20);
    setDroneBlockProperty(blockProperties, StoneBrick, true, 250, 2, ItemStoneBrick, 1, 4);
    setDroneBlockProperty(blockProperties, FloweringStoneBrick, true, 275, 2, ItemStoneBrick, 2, 6);

    // Factory blocks
    setDroneBlockProperty(blockProperties, LBM, true, 200, 3, ItemIronBar, 1, 10);
    setDroneBlockProperty(blockProperties, Factory, true, 200, 4, ItemIronBar, 1, 10);
    setDroneBlockProperty(blockProperties, Crate, true, 1000, 1, ItemIronBar, 1, 10);
    setDroneBlockProperty(blockProperties, Metal, true, 1000, 3, ItemIronBar, 1, 10);

    // Transparent Factory
    setDroneBlockProperty(blockProperties, ConveyorBelt, false, 50, 2, ItemIronBar, 1, 10);
    setDroneBlockProperty(blockProperties, Furnace, true, 50, 3, ItemIronBar, 1, 10);
    setDroneBlockProperty(blockProperties, StoneFurnaceOn, true, 100, 3, ItemIronBar, 1, 10);
    setDroneBlockProperty(blockProperties, StoneFurnaceOff, true, 100, 3, ItemIronBar, 1, 10);

    // Creature parts (Worm)
    setDroneBlockProperty(blockProperties, WormBody, true, 10, 1, ItemPlantMatter, 1, 20);
    setDroneBlockProperty(blockProperties, WormEyesLevel, true, 10, 1, ItemPlantMatter, 1, 20);
    setDroneBlockProperty(blockProperties, WormEyesUp, true, 10, 1, ItemPlantMatter, 1, 20);
    setDroneBlockProperty(blockProperties, WormMouth, true, 10, 1, ItemPlantMatter, 1, 20);

    // Miscellaneous
    setDroneBlockProperty(blockProperties, Scaffolding, true, 5, 1, ItemScaffolding, 1, 20);
    setDroneBlockProperty(blockProperties, Log, true, 15, 0, ItemLog, 1, 30);

    // Drone parts
    setDroneBlockProperty(blockProperties, DroneLeftForward, true, 1000, 3, ItemDroneParts, 1, 100);
    setDroneBlockProperty(blockProperties, DroneRightForward, true, 1000, 3, ItemDroneParts, 1, 100);
    setDroneBlockProperty(blockProperties, DroneRightBack, true, 1000, 3, ItemDroneParts, 1, 100);
    setDroneBlockProperty(blockProperties, DroneLeftBack, true, 1000, 3, ItemDroneParts, 1, 100);
    setDroneBlockProperty(blockProperties, DroneDead, true, 1000, 3, ItemDroneParts, 1, 100);

}

struct DroneBlockProperties* createDroneBlockProperties() {
    //setup droneBlockProperties struct
    struct DroneBlockProperties* droneBlockProperties = malloc(sizeof(struct DroneBlockProperties));
    if  (droneBlockProperties == NULL) {
        reportBug("Failed to create drones block properties\n");
        return NULL;
    }

    //Setup Block properties arrays
    if (setUpDroneBlockPropertiesArrays(droneBlockProperties) == -1) {
        reportBug("Failed to malloc Drone block properties Data arrays\n");
        return NULL;
    }

    setUpDroneBlockProperties(droneBlockProperties);

    return droneBlockProperties;
}


//Mining
int getBlockMineTime(struct DroneBlockProperties* blockPropertiesData, enum Block block) {
    return blockPropertiesData->mineTime[block];
}
int getBlockToolLevelToMine(struct DroneBlockProperties* blockPropertiesData, enum Block block) {
    return blockPropertiesData->toolLevelToMine[block];
}

//Item
enum DroneItem getBlockItemType(struct DroneBlockProperties* blockPropertiesData, enum Block block) {
    return blockPropertiesData->itemOfBlock[block];
}
int getBlockItemCount(struct DroneBlockProperties* blockPropertiesData, enum Block block) {
    return blockPropertiesData->itemCountPerBlock[block];
}

bool ifBlockIsSolid(struct DroneBlockProperties* blockPropertiesData, enum Block block) {
    return blockPropertiesData->solid[block];
}

int getBlockDroneWalkSpeed(struct DroneBlockProperties* blockPropertiesData, enum Block block) {
    return blockPropertiesData->walkSpeedOnBlock[block];
}