//
// Created by Spencer on 10/15/2024.
//

#ifndef DRONEFURNACELUACOMMANDS_H
#define DRONEFURNACELUACOMMANDS_H
#include <lua.h>

int luaDroneAddSmeltingFuelToFurnace(lua_State *L);

int luaDroneAddSmeltingItemToFurnace(lua_State *L);

int luaRemoveSmeltingItemFromFurnace(lua_State *L);

int luaGetRelativeFurnaceBusyTime(lua_State *L);

#endif //DRONEFURNACELUACOMMANDS_H
