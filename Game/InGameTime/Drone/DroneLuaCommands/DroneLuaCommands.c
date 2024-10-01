//
// Created by Spencer on 10/1/2024.
//

#include <malloc.h>
#include "DroneLuaCommands.h"
#include "../../../Debuging/Test_Main.h"
#include "../Drone.h"
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

int lua_moveDrone(lua_State *L){
    /*
    int worldId = luaL_checkinteger(L, 1);  // 1st argument: worldId
    int droneId = luaL_checkinteger(L, 2);  // 2nd argument: droneId (assuming it's an int for this example)
    int offsetX = luaL_checkinteger(L, 3);  // 3rd argument: x movement
    int offsetY = luaL_checkinteger(L, 4);  // 4th argument: y movement
    int offsetZ = luaL_checkinteger(L, 5);  // 5th argument: z movement

    lua_getglobal(L, "world");  // Get the global 'world'
    struct World* world = lua_touserdata(L, -1);
    struct Drone* drone = world->drones[droneId];

    int result = moveDrone(world, drone, offsetX, offsetY, offsetZ);

    lua_pushinteger(L, result);

    return 1;
     */
}

struct DroneLuaCommandsData* setUpLuaFunctions(struct World* world){
    /*
    struct DroneLuaCommandsData* luaCommandsData = malloc(sizeof (struct DroneLuaCommandsData));
    if (luaCommandsData == NULL){
        reportBug("failed to create lua command data\n");
        return NULL;
    }

    luaCommandsData->luaState = luaL_newstate();
    luaL_openlibs(luaCommandsData->luaState);

    lua_pushlightuserdata(luaCommandsData->luaState, world);
    lua_setglobal(luaCommandsData->luaState, "worlds");

    lua_register(luaCommandsData->luaState, "moveDrone", lua_moveDrone);
    return luaCommandsData;
     */
}