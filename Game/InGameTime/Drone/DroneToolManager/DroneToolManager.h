//
// Created by Spencer on 10/3/2024.
//

#ifndef EDIFICE_DRONETOOLMANAGER_H
#define EDIFICE_DRONETOOLMANAGER_H
#include "../Drone.h"



struct DroneToolData{
    int* toolLevel;

    float* mineSpeed;

};

struct DroneToolData* createDroneToolData();

enum DroneItem getDroneEquipmentAtSlot(struct Drone* drone, int slot);

float getToolMineSpeed(struct DroneToolData* droneToolData, enum DroneItem tool);

int getToolLevel(struct DroneToolData* droneToolData, enum DroneItem tool) ;

int addToolToDone(struct Drone* drone, enum DroneItem tool);

int removeEquipmentFromDrone(struct DroneData* droneData, struct Drone* drone, int index);
bool ifToolCanMineBlock(struct DroneData* droneData, enum DroneItem tool, enum Block block);

int getBlockToolMineTime(struct DroneData* droneData, enum Block block, enum DroneItem tool);

enum DroneItem getDronesBestToolForBlock(struct DroneData* droneData, struct Drone* drone, enum Block block);

#endif //EDIFICE_DRONETOOLMANAGER_H
