//
// Created by Spencer on 10/1/2024.
//

#ifndef EDIFICE_DRONELUACOMMANDS_H
#define EDIFICE_DRONELUACOMMANDS_H

#include <lua.h>

struct DroneLuaCommandsData{
    lua_State *luaState;
    struct World* world;
};

struct DroneLuaCommandsData* setUpLuaFunctions(struct World* world);

#endif //EDIFICE_DRONELUACOMMANDS_H
