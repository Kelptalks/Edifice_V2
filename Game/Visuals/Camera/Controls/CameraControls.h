//
// Created by Spencer on 6/7/2024.
//

#ifndef EDIFICE_CAMERACONTROLS_H
#define EDIFICE_CAMERACONTROLS_H

#include "SDL.h"
#include "../../../GameData.h"

void tickCamera(struct GameData* gameData);

void cameraControlInput(struct GameData* gameData, SDL_Event event);

#endif //EDIFICE_CAMERACONTROLS_H
