//
// Created by Spencer on 10/15/2024.
//

#include "DroneFurnaceLuaCommands.h"

#include <lauxlib.h>
#include <lua.h>
#include "../../../Furnace/Furnace.h"
#include "../../../../World/World.h"
#include "../../DroneData.h"
#include "../../../../Debuging/Test_Main.h"


int luaDroneAddSmeltingFuelToFurnace(lua_State *L) {
    int droneId = luaL_checkinteger(L, 1);  // 1nd argument: droneId (assuming it's an int for this example)
    int offsetX = luaL_checkinteger(L, 2);  // 2rd argument: x movement
    int offsetY = luaL_checkinteger(L, 3);  // 3th argument: y movement
    int offsetZ = luaL_checkinteger(L, 4);  // 4th argument: z movement
    enum DroneItem item = luaL_checkinteger(L, 5);
    int quantity = luaL_checkinteger(L, 6);  // 4th argument: z movement


    lua_getglobal(L, "world");  // Get the global 'world'
    struct World* world = lua_touserdata(L, -1);
    if (world == NULL){
        reportBug("World Null\n");
        return -1;
    }


    struct Drone* drone = world->droneData->drones[droneId];



    struct Furnace* furnace = getFurnaceAtWorldCords(world->furnaceData, drone->worldX + offsetX, drone->worldY + offsetY, drone->worldZ + offsetZ);
    if (furnace == NULL) {
        lua_pushinteger(L, -1);
        return -1;
    }



    int result = droneAddSmeltingFuelToFurnace(drone, furnace, item, quantity);

    lua_pushinteger(L, result);
    return 1;
}

int luaDroneAddSmeltingItemToFurnace(lua_State *L) {
    int droneId = luaL_checkinteger(L, 1);  // 1nd argument: droneId (assuming it's an int for this example)
    int offsetX = luaL_checkinteger(L, 2);  // 2rd argument: x movement
    int offsetY = luaL_checkinteger(L, 3);  // 3th argument: y movement
    int offsetZ = luaL_checkinteger(L, 4);  // 4th argument: z movement
    enum DroneItem item = luaL_checkinteger(L, 5);

    lua_getglobal(L, "world");  // Get the global 'world'
    struct World* world = lua_touserdata(L, -1);
    if (world == NULL){
        reportBug("World Null\n");
        return -1;
    }
    struct Drone* drone = world->droneData->drones[droneId];


    struct Furnace* furnace = getFurnaceAtWorldCords(world->furnaceData, drone->worldX + offsetX, drone->worldY + offsetY, drone->worldZ + offsetZ);
    if (furnace == NULL) {
        lua_pushinteger(L, -1);
        return -1;
    }


    int result = droneAddSmeltingItemToFurnace(drone, furnace, item);

    lua_pushinteger(L, result);
    return 1;
}

int luaRemoveSmeltingItemFromFurnace(lua_State *L) {
    int droneId = luaL_checkinteger(L, 1);  // 1nd argument: droneId (assuming it's an int for this example)
    int offsetX = luaL_checkinteger(L, 2);  // 2rd argument: x movement
    int offsetY = luaL_checkinteger(L, 3);  // 3th argument: y movement
    int offsetZ = luaL_checkinteger(L, 4);  // 4th argument: z movement

    lua_getglobal(L, "world");  // Get the global 'world'
    struct World* world = lua_touserdata(L, -1);
    if (world == NULL){
        reportBug("World Null\n");
        return -1;
    }
    struct Drone* drone = world->droneData->drones[droneId];


    struct Furnace* furnace = getFurnaceAtWorldCords(world->furnaceData, drone->worldX + offsetX, drone->worldY + offsetY, drone->worldZ + offsetZ);
    if (furnace == NULL) {
        lua_pushinteger(L, -1);
        return -1;
    }

    lua_pushinteger(L, removeSmeltingItemFromFurnace(world->droneData, drone, furnace));
    return 1;
}

int luaGetRelativeFurnaceBusyTime(lua_State *L) {
    int droneId = luaL_checkinteger(L, 1);  // 1nd argument: droneId (assuming it's an int for this example)
    int offsetX = luaL_checkinteger(L, 2);  // 2rd argument: x movement
    int offsetY = luaL_checkinteger(L, 3);  // 3th argument: y movement
    int offsetZ = luaL_checkinteger(L, 4);  // 4th argument: z movement

    lua_getglobal(L, "world");  // Get the global 'world'
    struct World* world = lua_touserdata(L, -1);
    if (world == NULL){
        reportBug("World Null\n");
        return -1;
    }
    struct Drone* drone = world->droneData->drones[droneId];


    struct Furnace* furnace = getFurnaceAtWorldCords(world->furnaceData, drone->worldX + offsetX, drone->worldY + offsetY, drone->worldZ + offsetZ);

    int result = furnace->busyTime;
    lua_pushinteger(L, result);

    return 1;
}
