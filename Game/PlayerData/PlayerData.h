//
// Created by Spencer on 6/30/2024.
//

#ifndef EDIFICE_PLAYERDATA_H
#define EDIFICE_PLAYERDATA_H

#include "../Blocks/Blocks.h"
#include "../InGameTime/TikEvent/EntityManager/EntityManager.h"

struct PlayerData{
    enum Block block;
    int lastMouseXCor;
    int lastMouseYCor;

    enum EntityDirection playerDirection;
    float worldX;
    float worldY;
    float worldZ;
};

struct PlayerData* createPlayerData();

#endif //EDIFICE_PLAYERDATA_H
