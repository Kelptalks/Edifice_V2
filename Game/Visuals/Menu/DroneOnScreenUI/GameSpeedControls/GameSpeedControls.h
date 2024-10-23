//
// Created by Spencer on 10/23/2024.
//

#ifndef GAMESPEEDCONTROLS_H
#define GAMESPEEDCONTROLS_H
#include <SDL_events.h>
#include "../../../../Debuging/Test_Main.h"
#include "../../../../GameData.h"

struct GameSpeedControls {
    int currentSpeed;

    int totalSpeeds;
    int* speeds;

};

struct GameSpeedControls* createGameSpeedControls();

void renderGameSpeedControls(struct GameData* gameData);

void handleGameSpeedInputs(struct GameData* gameData, SDL_Event event);
#endif //GAMESPEEDCONTROLS_H
