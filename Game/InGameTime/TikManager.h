//
// Created by Spencer on 7/7/2024.
//

#ifndef EDIFICE_TIKMANAGER_H
#define EDIFICE_TIKMANAGER_H

#include "../GameData.h"

struct TikManager{
    int tik; // Unit of in game time
    int tikTime; // in ms
    Uint32 sdlTime;
};

struct TikManager* createTikManager();

void updateTikTime(struct GameData* gameData);

#endif //EDIFICE_TIKMANAGER_H
