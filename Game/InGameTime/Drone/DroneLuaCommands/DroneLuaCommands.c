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
#include "DroneFurnaceLuaCommands/DroneFurnaceLuaCommands.h"

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

int luaPlaceRelativeBlock(lua_State *L){
    int droneId = luaL_checkinteger(L, 1);  // 1nd argument: droneId (assuming it's an int for this example)
    int offsetX = luaL_checkinteger(L, 2);  // 2rd argument: x movement
    int offsetY = luaL_checkinteger(L, 3);  // 3th argument: y movement
    int offsetZ = luaL_checkinteger(L, 4);  // 4th argument: z movement
    enum Block block = luaL_checkinteger(L, 5);

    lua_getglobal(L, "world");  // Get the global 'world'
    struct World* world = lua_touserdata(L, -1);
    if (world == NULL){
        return -1;
    }

    struct Drone* drone = world->droneData->drones[droneId];
    int result = placeBlockRelativeToDrone(world, drone, offsetX, offsetY, offsetZ, block);

    lua_pushinteger(L, result);

    return 1;
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

int luaCraftDroneTool(lua_State *L) {
    int droneId = luaL_checkinteger(L, 1);  // 1nd argument: droneId (assuming it's an int for this example)
    enum DroneItem tool = luaL_checkinteger(L, 2);  // 2rd argument: x movement

    lua_getglobal(L, "world");  // Get the global 'world'
    struct World* world = lua_touserdata(L, -1);
    if (world == NULL){
        return -1;
    }

    struct Drone* drone = world->droneData->drones[droneId];
    int result = droneCraftItem(world, drone, tool);

    lua_pushinteger(L, result);

    return 1;
}

int luaGetDroneToolSlot(lua_State *L) {
    int droneId = luaL_checkinteger(L, 1);  // 1nd argument: droneId (assuming it's an int for this example)
    int slot = luaL_checkinteger(L, 2);  // 2rd argument: x movement


    lua_getglobal(L, "world");  // Get the global 'world'
    struct World* world = lua_touserdata(L, -1);
    if (world == NULL){
        return -1;
    }

    struct Drone* drone = world->droneData->drones[droneId];
    int result = getDroneToolSlot(drone, slot);

    if (result <= 0) {
        lua_pushinteger(L, -1);
    }
    else {
        lua_pushinteger(L, result);
    }

    return 1;
}

int luaGetDroneFuelCount(lua_State *L) {
    int droneId = luaL_checkinteger(L, 1);  // 1nd argument: droneId (assuming it's an int for this example)


    lua_getglobal(L, "world");  // Get the global 'world'
    struct World* world = lua_touserdata(L, -1);
    if (world == NULL){
        return -1;
    }

    struct Drone* drone = world->droneData->drones[droneId];
    int result = drone->fuel;

    lua_pushinteger(L, result);

    return 1;
}

int luaGetDroneInventoryItemCount(lua_State *L) {

    int droneId = luaL_checkinteger(L, 1);  // 1nd argument: droneId (assuming it's an int for this example)
    enum DroneItem item = luaL_checkinteger(L, 2);  // 2rd argument: x movement


    lua_getglobal(L, "world");  // Get the global 'world'
    struct World* world = lua_touserdata(L, -1);
    if (world == NULL){
        return -1;
    }

    struct Drone* drone = world->droneData->drones[droneId];
    int result = getDroneInventoryItemCount(drone, item);

    if (result <= 0) {
        lua_pushinteger(L, -1);
    }
    else {
        lua_pushinteger(L, result);
    }

    return 1;
}

int luaDroneUseItemForFuel(lua_State *L) {

    int droneId = luaL_checkinteger(L, 1);  // 1nd argument: droneId (assuming it's an int for this example)
    enum DroneItem item = luaL_checkinteger(L, 2);  // 2rd argument: x movement
    int quantity = luaL_checkinteger(L, 3);


    lua_getglobal(L, "world");  // Get the global 'world'
    struct World* world = lua_touserdata(L, -1);
    if (world == NULL){
        return -1;
    }

    struct Drone* drone = world->droneData->drones[droneId];
    int result = useItemForFuel(drone, item, quantity);

    if (result <= 0) {
        lua_pushinteger(L, -1);
    }
    else {
        lua_pushinteger(L, result);
    }

    return 1;
}

int luaReportDroneBug(lua_State *L) {
    const char* myString = luaL_checkstring(L, 1);
    reportBug("%s\n", myString);
    return 1;
}

int luaGetDroneBusyTime(lua_State *L) {
    int droneId = luaL_checkinteger(L, 1);  // 1nd argument: droneId (assuming it's an int for this example)

    lua_getglobal(L, "world");  // Get the global 'world'
    struct World* world = lua_touserdata(L, -1);
    if (world == NULL){
        return -1;
    }

    struct Drone* drone = world->droneData->drones[droneId];
    int result = drone->busyTime;


    lua_pushinteger(L, result);
    return 1;
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
    lua_register(luaCommandsData->luaState, "luaCraftDroneTool", luaCraftDroneTool);
    lua_register(luaCommandsData->luaState, "luaGetDroneToolSlot", luaGetDroneToolSlot);
    lua_register(luaCommandsData->luaState, "luaGetDroneInventoryItemCount", luaGetDroneInventoryItemCount);
    lua_register(luaCommandsData->luaState, "luaDroneUseItemForFuel", luaDroneUseItemForFuel);
    lua_register(luaCommandsData->luaState, "luaPlaceRelativeBlock", luaPlaceRelativeBlock);
    lua_register(luaCommandsData->luaState, "luaGetDroneFuelCount", luaGetDroneFuelCount);
    lua_register(luaCommandsData->luaState, "luaReportDroneBug", luaReportDroneBug);
    lua_register(luaCommandsData->luaState, "luaGetDroneBusyTime", luaGetDroneBusyTime);

    lua_register(luaCommandsData->luaState, "luaDroneAddSmeltingFuelToFurnace", luaDroneAddSmeltingFuelToFurnace);
    lua_register(luaCommandsData->luaState, "luaDroneAddSmeltingItemToFurnace", luaDroneAddSmeltingItemToFurnace);
    lua_register(luaCommandsData->luaState, "luaRemoveSmeltingItemFromFurnace", luaRemoveSmeltingItemFromFurnace);
    lua_register(luaCommandsData->luaState, "luaGetRelativeFurnaceBusyTime", luaGetRelativeFurnaceBusyTime);


    //open Drone file
    if (luaL_dofile(luaCommandsData->luaState, "LuaScripts/Main.lua") != LUA_OK) {
        printf("Error loading script: %s\n", lua_tostring(luaCommandsData->luaState, -1));
    }

    return luaCommandsData;

}