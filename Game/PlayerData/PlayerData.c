//
// Created by Spencer on 6/30/2024.
//


#include <malloc.h>
#include "PlayerData.h"

struct PlayerData* createPlayerData(){
    struct PlayerData* playerData = malloc(sizeof (struct PlayerData));
    playerData->block = 1;
    int lastMouseXCor = 0;
    int lastMouseYCor = 0;


    playerData->playerDirection = EntityNorth;

    playerData->worldX = -98;
    playerData->worldY = -96;
    playerData->worldZ = 52;

    return playerData;
}