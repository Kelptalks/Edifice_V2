//
// Created by Spencer on 10/4/2024.
//

#ifndef EDIFICE_DRONEDATA_H
#define EDIFICE_DRONEDATA_H

#include "Drone.h"
#include "DroneToolManager/DroneToolManager.h"
#include "DroneInventoryManager/DroneInventoryManager.h"
#include "DroneLuaCommands/DroneLuaCommands.h"
#include "DroneBlockProperties/DroneBlockProperties.h"
#include "DroneItemManager/DroneItemManager.h"

struct DroneData{
    int droneCount;
    int maxDrones;
    struct Drone** drones;

    struct DroneToolData* droneToolData;
    struct DroneLuaCommandsData* droneLuaCommandsData;

    struct DroneItemData* droneItemData;
    struct DroneBlockProperties* droneBlockProperties;
    struct DroneCraftingData* droneCraftingData;
};

struct Drone* getDroneFromId(struct DroneData* droneData, int id);

struct DroneData* createDroneData(struct World* world,int maxDrones);

#endif //EDIFICE_DRONEDATA_H
