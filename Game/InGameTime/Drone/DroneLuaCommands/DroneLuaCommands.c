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
#include "../DroneData.h"

int luaGetDroneCount(lua_State *L){
    lua_getglobal(L, "world");  // Get the global 'world'
    struct World* world = lua_touserdata(L, -1);
    if (world == NULL){
        lua_pushinteger(L, -1);
    }
    else {
        lua_pushinteger(L, world->droneData->droneCount);
    }
    return 1;
}

int luaMoveDrone(lua_State *L){
    int droneId = luaL_checkinteger(L, 1);  // 1nd argument: droneId (assuming it's an int for this example)
    int offsetX = luaL_checkinteger(L, 2);  // 2rd argument: x movement
    int offsetY = luaL_checkinteger(L, 3);  // 3th argument: y movement
    int offsetZ = luaL_checkinteger(L, 4);  // 4th argument: z movement

    lua_getglobal(L, "world");  // Get the global 'world'
    struct World* world = lua_touserdata(L, -1);
    if (world == NULL){
        return -1;
    }
    struct Drone* drone = world->droneData->drones[droneId];

    int result = moveDrone(world, drone, offsetX, offsetY, offsetZ);

    lua_pushinteger(L, result);

    return 1;
}

int luaGetRelativeBlock(lua_State *L){
    int droneId = luaL_checkinteger(L, 1);  // 1nd argument: droneId (assuming it's an int for this example)
    int offsetX = luaL_checkinteger(L, 2);  // 2rd argument: x movement
    int offsetY = luaL_checkinteger(L, 3);  // 3th argument: y movement
    int offsetZ = luaL_checkinteger(L, 4);  // 4th argument: z movement

    lua_getglobal(L, "world");  // Get the global 'world'
    struct World* world = lua_touserdata(L, -1);
    if (world == NULL){
        return -1;
    }

    struct Drone* drone = world->droneData->drones[droneId];
    int result = getBlockRelativeToDrone(world, drone, offsetX, offsetY, offsetZ);

    lua_pushinteger(L, result);

    return 1;
}

int luaMineRelativeBlock(lua_State *L){
    int droneId = luaL_checkinteger(L, 1);  // 1nd argument: droneId (assuming it's an int for this example)
    int offsetX = luaL_checkinteger(L, 2);  // 2rd argument: x movement
    int offsetY = luaL_checkinteger(L, 3);  // 3th argument: y movement
    int offsetZ = luaL_checkinteger(L, 4);  // 4th argument: z movement

    lua_getglobal(L, "world");  // Get the global 'world'
    struct World* world = lua_touserdata(L, -1);
    if (world == NULL){
        return -1;
    }

    struct Drone* drone = world->droneData->drones[droneId];
    int result = mineBlockRelativeToDrone(world, drone, offsetX, offsetY, offsetZ);

    lua_pushinteger(L, result);

    return 1;
}

int luaGetItemInInventorySlot(lua_State *L){

}

int luaGetDroneCords(lua_State *L) {
    int droneId = luaL_checkinteger(L, 1);  // 1nd argument: droneId (assuming it's an int for this example)

    lua_getglobal(L, "world");  // Get the global 'world'
    struct World* world = lua_touserdata(L, -1);
    if (world == NULL){
        return -1;
    }

    struct Drone* drone = world->droneData->drones[droneId];

    lua_pushinteger(L, drone->worldX);
    lua_pushinteger(L, drone->worldY);
    lua_pushinteger(L, drone->worldZ);

    return 3;
}


struct DroneLuaCommandsData* setUpLuaFunctions(struct World* world){
    reportBug("creating lua\n");

    struct DroneLuaCommandsData* luaCommandsData = malloc(sizeof (struct DroneLuaCommandsData));
    if (luaCommandsData == NULL){
        reportBug("failed to create lua command data\n");
        return NULL;
    }

    luaCommandsData->luaState = luaL_newstate();
    luaL_openlibs(luaCommandsData->luaState);

    lua_pushlightuserdata(luaCommandsData->luaState, world);
    lua_setglobal(luaCommandsData->luaState, "world");

    lua_register(luaCommandsData->luaState, "luaMoveDrone", luaMoveDrone);
    lua_register(luaCommandsData->luaState, "luaGetRelativeBlock", luaGetRelativeBlock);
    lua_register(luaCommandsData->luaState, "luaGetDroneCount", luaGetDroneCount);
    lua_register(luaCommandsData->luaState, "luaMineRelativeBlock", luaMineRelativeBlock);
    lua_register(luaCommandsData->luaState, "luaGetDroneCords", luaGetDroneCords);

    //open Drone file
    if (luaL_dofile(luaCommandsData->luaState, "LuaScripts/Main.lua") != LUA_OK) {
        printf("Error loading script: %s\n", lua_tostring(luaCommandsData->luaState, -1));
    }

    return luaCommandsData;

}