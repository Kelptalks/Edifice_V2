//
// Created by Spencer on 10/4/2024.
//

#include <malloc.h>
#include "DroneData.h"
#include "../../Debuging/Test_Main.h"


struct DroneData* createDroneData(struct World* world,int maxDrones){
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

    droneData->droneToolData = createDroneToolData();
    droneData->droneLuaCommandsData = setUpLuaFunctions(world);

    return droneData;
}

struct Drone* getDroneFromId(struct DroneData* droneData, int id){
    return droneData->drones[id];
}