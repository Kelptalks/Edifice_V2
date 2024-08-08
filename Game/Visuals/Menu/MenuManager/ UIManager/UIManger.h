//
// Created by Spencer on 8/7/2024.
//

#ifndef EDIFICE_UIMANGER_H
#define EDIFICE_UIMANGER_H

#include "../../../../GameData.h"

enum ButtonTexture{
    ExitButton,
    CheckButton,
    BackButton,
    ForwardButton
};

struct Button{
    //location and scale
    int xCor;
    int yCor;

    int xScale;
    int yScale;

    //Rendering
    enum ButtonTexture buttonTexture;

    //Events
    bool mouseOn;
    bool pressed;
};

struct Button* createButton(enum ButtonTexture buttonTexture, int xCor, int yCor, int xScale, int yScale);

void handleButtonInputs(struct Button* button, struct GameData* gameData, SDL_Event event);

void renderUIButton(struct Button* button, struct GameData* gameData);


struct ScrollWheel{
    //Value
    int maxVal;
    int currentVal;

    //location and scale
    int xCor;
    int yCor;

    int xScale;
    int yScale;

    bool pressed;
    int lastX;
    int currentX;

};

struct ScrollWheel* createScrollWheel(int xCor, int yCor, int xScale, int yScale, int maxVal);

void handleScrollWheelInputs(struct ScrollWheel* scrollWheel, struct GameData* gameData, SDL_Event event);

void renderScrollWheel(struct ScrollWheel* scrollWheel, struct GameData* gameData);

#endif //EDIFICE_UIMANGER_H
