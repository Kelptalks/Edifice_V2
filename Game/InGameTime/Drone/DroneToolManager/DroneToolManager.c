//
// Created by Spencer on 10/3/2024.
//

#include "SDL.h"
#include "DroneToolManager.h"
#include "../../../Blocks/Blocks.h"

SDL_Rect getToolSrcRect(enum DroneTool droneTool){
    SDL_Rect srcRect = {droneTool * 16, 1232, 16, 16};
    return srcRect;
}

int addToolToDone(struct Drone* drone, enum DroneTool tool){
    for (int i = 0; i < 3; i++){
        if (drone->tools[i] == ToolNull){
            drone->tools[i] = tool;
            return 1;
        }
    }
    return -1;
}

void removeToolToDone(struct Drone* drone, int index){
    drone->tools[index] = ToolNull;
}



struct DroneToolData* createDroneToolData(){
    struct DroneToolData* droneToolData = malloc((sizeof (struct DroneToolData)));


    //Set up block mine times
    droneToolData->blockMineTimes = calloc(getTotalBlockCount(), sizeof (int));
}