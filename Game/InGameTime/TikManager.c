//
// Created by Spencer on 7/7/2024.
//


#include <malloc.h>
#include "TikManager.h"
#include "../GameData.h"
#include "../Debuging/Test_Main.h"
#include "../PlayerData/PlayerData.h"
#include "../World/World.h"
#include "TikEvent/EntityManager/EntityManager.h"
#include "../Visuals/Camera/Controls/CameraControls.h"
#include "Drone/Drone.h"
#include "Drone/DroneLuaCommands/DroneLuaCommands.h"
#include "Drone/DroneData.h"
#include "Furnace/FurnaceData.h"

struct TikManager* createTikManager(){
    struct TikManager* tikManager = malloc(sizeof (struct TikManager));
    tikManager->tik = 0;
    tikManager->tikTime = 25;
    tikManager->droneTickInterval = 5;
    return tikManager;
}

void tickAllEntityInWorld(struct GameData* gameData){
    for (int x = 0; x < gameData->world->entityCount; x++){
        if (gameData->world->tempEntityArray[x] != NULL){
            tikEntity(gameData, gameData->world->tempEntityArray[x]);
        }
    }
}

void updateTikTime(struct GameData* gameData){
    Uint32 time1 = SDL_GetTicks();
    struct TikManager* tikManager = gameData->tikManager;
    tikManager->sdlTime = SDL_GetTicks();
    if (tikManager->sdlTime > (tikManager->tik * tikManager->tikTime)){
        tikManager->tik++;
        tikPlayer(gameData);
        tickAllEntityInWorld(gameData);

        struct World* world = gameData->world;
        struct DroneLuaCommandsData* commandsData = world->droneData->droneLuaCommandsData;

        //Run lua tick function
        if (tikManager->tik % tikManager->droneTickInterval == 0) {
            lua_getglobal(commandsData->luaState, "ON_TICK");  // Get the onTick function from Lua
            if (!lua_isfunction(commandsData->luaState, -1)) {  // Check if onTick is a valid function
                reportBug("Error: ON_TICK is not a function\n");
                return;
            }

            if (lua_pcall(commandsData->luaState, 0, 0, 0) != LUA_OK) {  // Call it with no arguments, no return values
                reportBug("Error running onTick: %s\n", lua_tostring(commandsData->luaState, -1));
            }

            for (int i = 0; i < world->droneData->droneCount; i++) {
                tickDrone(world, world->droneData->drones[i]);
            }

            for (int i = 0; i < world->furnaceData->currentFurnaceCount; i++) {
                tickFurnace(world, world->furnaceData->furnaces[i]);
            }
        }

    }
    Uint32 time2 = SDL_GetTicks();
    gameData->debugMenu->tickTime = time2 - time1;

    tickCamera(gameData);
}
