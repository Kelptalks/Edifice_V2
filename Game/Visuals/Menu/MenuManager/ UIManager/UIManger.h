//
// Created by Spencer on 8/7/2024.
//

#ifndef EDIFICE_UIMANGER_H
#define EDIFICE_UIMANGER_H

#include "../../../../GameData.h"

struct ScrollWheel{
    //Value
    int maxVal;
    int currentVal;

    //location and scale
    int xCor;
    int yCor;

    int xScale;
    int yScale;
};

struct ScrollWheel* createScrollWheel(int xCor, int yCor, int xScale, int yScale, int maxVal);

void handleScrollWheelInputs(struct GameData* gameData, SDL_Event event);

void renderScrollWheel(struct ScrollWheel* scrollWheel, struct GameData* gameData);

#endif //EDIFICE_UIMANGER_H
