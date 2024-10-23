//
// Created by Spencer on 10/3/2024.
//

#include "SDL.h"
#include "DroneToolManager.h"

#include <bemapiset.h>

#include "../DroneData.h"
#include "../../../Debuging/Test_Main.h"
#include "../DroneItemManager/DroneItemManager.h"



void setUpDroneToolDataArrays(struct DroneToolData* droneToolData) {
    droneToolData->toolLevel = malloc(getTotalItemCount() * sizeof(int));
    if (droneToolData->toolLevel == NULL) {
        reportBug("Failed to create droneToolData tool level array\n");
    }

    droneToolData->mineSpeed = malloc(getTotalItemCount() * sizeof(float));
    if (droneToolData->mineSpeed == NULL) {
        reportBug("Failed to create droneToolData mine Speed array\n");
    }
}

void setToolProperty (struct DroneToolData* droneToolData, enum DroneItem tool, int toolLevel, float mineSpeed) {
    droneToolData->toolLevel[tool] = toolLevel;
    droneToolData->mineSpeed[tool] = mineSpeed;
}

void setUpToolProperties(struct DroneToolData* droneToolData) {
    setToolProperty(droneToolData, ItemNull, 0, 1.0f);

    setToolProperty(droneToolData, ToolStoneDrill, 1, 0.5f);
    setToolProperty(droneToolData, ToolStoneSaw, -1, 0.5f);
    setToolProperty(droneToolData, ToolIronDrill, 2, 0.25f);
    setToolProperty(droneToolData, ToolIronSaw, -2, 0.25f);
    setToolProperty(droneToolData, ToolIronBattery, 0, 1.0f);
    setToolProperty(droneToolData, ToolIronReceptacle, 0, 1.0f);
    setToolProperty(droneToolData, ToolIronCamera, 0, 1.0f);
    setToolProperty(droneToolData, ToolTitaniumDrill, 0, 1.0f);
    setToolProperty(droneToolData, ToolTitaniumSaw, 0, 1.0f);
    setToolProperty(droneToolData, ToolTitaniumBattery, 0, 1.0f);
    setToolProperty(droneToolData, ToolTitaniumReceptacle, 0, 1.0f);
    setToolProperty(droneToolData, ToolTitaniumCamera, 0, 1.0f);
    setToolProperty(droneToolData, ToolExplosive, 0, 1.0f);
}

struct DroneToolData* createDroneToolData(){
    struct DroneToolData* droneToolData = malloc((sizeof (struct DroneToolData)));
    if (droneToolData == NULL) {
        reportBug("Failed to create drone tool data struct\n");
        return NULL;
    }

    setUpDroneToolDataArrays(droneToolData);

    setUpToolProperties(droneToolData);

    return droneToolData;
}

float getToolMineSpeed(struct DroneToolData* droneToolData, enum DroneItem tool) {
    if (tool < getTotalToolCount()) {
        return droneToolData->mineSpeed[tool];
    }
    return -1;
}

int getToolLevel(struct DroneToolData* droneToolData, enum DroneItem tool) {
    if (tool < getTotalToolCount()) {
        return droneToolData->toolLevel[tool];
    }
    return -99;
}

enum DroneItem getDroneEquipmentAtSlot(struct Drone* drone, int slot) {
    return drone->equipment[slot];
}

int addToolToDone(struct Drone* drone, enum DroneItem tool) {
    if (tool < getTotalToolCount()) {
        for (int i = 0; i < 3; i++) {
            if (getDroneEquipmentAtSlot(drone, 0) == ItemNull) {
                drone->equipment[i] = tool;
                return 1;
            }
        }
    }
    else {
        return -2;
    }
    return -1;
}

int removeEquipmentFromDrone(struct DroneData* droneData, struct Drone* drone, int index) {
    enum DroneItem equipmentToRemove = drone->equipment[index];
    addItemToInventory(droneData, drone, equipmentToRemove, 1);
    drone->equipment[index] == ItemNull;
    return 1;
}

bool ifToolCanMineBlock(struct DroneData* droneData, enum DroneItem tool, enum Block block) {
    if (tool < getTotalToolCount()) {
        int blockRequiredToolType = getBlockToolLevelToMine(droneData->droneBlockProperties, block);

        //Posatives for drills
        if (blockRequiredToolType >= 0) {
            return droneData->droneToolData->toolLevel[tool] >= getBlockToolLevelToMine(droneData->droneBlockProperties, block);
        }
        //Negative for saws
        else {
            return droneData->droneToolData->toolLevel[tool] <= getBlockToolLevelToMine(droneData->droneBlockProperties, block);
        }
    }
    return false;
}

int getBlockToolMineTime(struct DroneData* droneData, enum Block block, enum DroneItem tool) {
    return (int) (droneData->droneToolData->mineSpeed[tool] * getBlockMineTime(droneData->droneBlockProperties, block));
}

enum DroneItem getDronesBestToolForBlock(struct DroneData* droneData, struct Drone* drone, enum Block block) {
    int blockRequiredToolType = getBlockToolLevelToMine(droneData->droneBlockProperties, block);

    //Get the best tool if block is +Tool
    int highestToolLevel = 0;
    int highestLevelToolSlot = 0;
    if (blockRequiredToolType >= 0) {
        for (int i = 0; i < 3; i++) {
            if (getToolLevel(droneData->droneToolData, drone->equipment[i]) > highestToolLevel) {
                highestLevelToolSlot = i;
                highestToolLevel = getToolLevel(droneData->droneToolData, drone->equipment[i]);
            }
        }
    }
    //Get the best tool if block is -Tool
    else {
        for (int i = 0; i < 3; i++) {
            if (getToolLevel(droneData->droneToolData, drone->equipment[i]) < highestToolLevel) {
                highestLevelToolSlot = i;
                highestToolLevel = getToolLevel(droneData->droneToolData, drone->equipment[i]);
            }
        }
    }

    return drone->equipment[highestLevelToolSlot];
}