//
// Created by Spencer on 6/30/2024.
//


#include <malloc.h>
#include "PlayerData.h"

struct PlayerData* createPlayerData(){
    struct PlayerData* playerData = malloc(sizeof (struct PlayerData));
    playerData->block = 1;
    return playerData;
}