//
// Created by Spencer on 10/18/2024.
//

#ifndef DRONEBLOCKPROPERTIES_H
#define DRONEBLOCKPROPERTIES_H
#include <stdbool.h>
#include "../DroneItemManager/DroneItemManager.h"
#include "../../../Blocks/Blocks.h"

struct DroneBlockProperties {
    //Mining
    int* mineTime;
    int* toolLevelToMine;

    //Item
    enum DroneItem* itemOfBlock;
    int* itemCountPerBlock;

    //
    int* walkSpeedOnBlock;
    bool* solid;
};

struct DroneBlockProperties* createDroneBlockProperties();

//Mining
int getBlockMineTime(struct DroneBlockProperties* blockPropertiesData, enum Block block);
int getBlockToolLevelToMine(struct DroneBlockProperties* blockPropertiesData, enum Block block);

//Item
enum DroneItem getBlockItemType(struct DroneBlockProperties* blockPropertiesData, enum Block block);
int getBlockItemCount(struct DroneBlockProperties* blockPropertiesData, enum Block block);

bool ifBlockIsSolid(struct DroneBlockProperties* blockPropertiesData, enum Block block);

int getBlockDroneWalkSpeed(struct DroneBlockProperties* blockPropertiesData, enum Block block);

#endif //DRONEBLOCKPROPERTIES_H
