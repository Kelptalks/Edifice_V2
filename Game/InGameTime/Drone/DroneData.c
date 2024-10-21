//
// Created by Spencer on 10/4/2024.
//

#include <malloc.h>
#include "DroneData.h"
#include "../../Debuging/Test_Main.h"
#include "DroneCraftingManager/DroneCraftingManager.h"


struct DroneData* createDroneData(struct World* world,int maxDrones){
    reportBug("Creating Drone Data : \n");
    struct DroneData* droneData = malloc(sizeof (struct DroneData));
    if (droneData == NULL){
        reportBug("Failed To malloc drone Data\n");
        return NULL;
    }

    droneData->maxDrones = maxDrones;
    droneData->droneCount = 0;
    droneData->drones = calloc(maxDrones, sizeof (struct Drone*));
    if (droneData->drones  == NULL){
        reportBug("Failed To malloc drone array\n");
        free(droneData);
        return NULL;
    }

    reportBug(" - Creating Drone Item Data \n");
    droneData->droneItemData = createDroneItemData();

    reportBug(" - Creating Drone Block Properties \n");
    droneData->droneBlockProperties = createDroneBlockProperties();

    reportBug(" - Creating Drone Tool Data \n");
    droneData->droneToolData = createDroneToolData();

    reportBug(" - Creating Drone Crafting Data \n");
    droneData->droneCraftingData = createDroneCraftingData();

    reportBug(" - Creating Drone Lua Commands \n");
    droneData->droneLuaCommandsData = setUpLuaFunctions(world);

    return droneData;
}

struct Drone* getDroneFromId(struct DroneData* droneData, int id){
    return droneData->drones[id];
}