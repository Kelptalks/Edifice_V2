//
// Created by Spencer on 7/7/2024.
//


#include <malloc.h>
#include "TikManager.h"
#include "../GameData.h"
#include "../Debuging/Test_Main.h"

struct TikManager* createTikManager(){
    struct TikManager* tikManager = malloc(sizeof (struct TikManager));
    tikManager->tik = 0;
    tikManager->tikTime = 50;
    return tikManager;
}

void updateTikTime(struct GameData* gameData){
    struct TikManager* tikManager = gameData->tikManager;

    tikManager->sdlTime = SDL_GetTicks();
    if (tikManager->sdlTime > (tikManager->tik * tikManager->tikTime)){
        tikManager->tik++;
    }

    reportTikBug("Current tik : %i \n", tikManager->tik);
    if (tikManager->tik % 200 == 0){
        clearTikBugReports();
    }
}