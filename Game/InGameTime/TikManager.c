//
// Created by Spencer on 7/7/2024.
//


#include <malloc.h>
#include "TikManager.h"
#include "../GameData.h"
#include "../Debuging/Test_Main.h"
#include "../PlayerData/PlayerData.h"
#include "../World/World.h"
#include "TikEvent/EntityManager/EntityManager.h"

struct TikManager* createTikManager(){
    struct TikManager* tikManager = malloc(sizeof (struct TikManager));
    tikManager->tik = 0;
    tikManager->tikTime = 10;
    return tikManager;
}

void tickAllEntityInWorld(struct GameData* gameData){
    for (int x = 0; x < gameData->world->entityCount; x++){
        if (gameData->world->tempEntityArray[x] != NULL){
            tikEntity(gameData, gameData->world->tempEntityArray[x]);
        }
    }
}

void updateTikTime(struct GameData* gameData){
    struct TikManager* tikManager = gameData->tikManager;

    tikManager->sdlTime = SDL_GetTicks();
    if (tikManager->sdlTime > (tikManager->tik * tikManager->tikTime)){
        reportTikBug("current tik %i \n", tikManager->tik);
        tikManager->tik++;
        tikPlayer(gameData);
        tickAllEntityInWorld(gameData);
    }

}
