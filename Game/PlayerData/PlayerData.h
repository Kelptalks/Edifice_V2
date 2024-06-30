//
// Created by Spencer on 6/30/2024.
//

#ifndef EDIFICE_PLAYERDATA_H
#define EDIFICE_PLAYERDATA_H

#include "../Blocks/Blocks.h"

struct PlayerData{
    enum Block block;
};

struct PlayerData* createPlayerData();

#endif //EDIFICE_PLAYERDATA_H
