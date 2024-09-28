//
// Created by Spencer on 8/7/2024.
//

#include <SDL_events.h>
#include "UIManger.h"
#include "../../../../Debuging/Test_Main.h"
#include "UIRenderer/UIRenderer.h"


struct Button* createButton(enum ButtonTexture buttonTexture, int xCor, int yCor, int xScale, int yScale){
    struct Button* button = malloc(sizeof (struct Button));
    if (button == NULL){
        reportBug("Failed to malloc scroll wheel\n");
        return NULL;
    };

    button->xCor = xCor;
    button->yCor = yCor;

    button->xScale = xScale;
    button->yScale = yScale;

    button->pressed = false;
    button->mouseOn = false;

    button->buttonTexture = buttonTexture;
    return button;
}

void handleButtonInputs(struct Button* button, struct GameData* gameData, SDL_Event event){

    //Mouse input Controls
    int xCor, yCor;
    SDL_GetMouseState(&xCor, &yCor);

    //if mouse is on button
    bool inXrange = (xCor < (button->xCor + button->xScale) && xCor > button->xCor);
    bool inYrange = (yCor < (button->yCor + button->yScale) && yCor > button->yCor);

    if (inXrange && inYrange){
        button->mouseOn = true;
        if (event.type == SDL_MOUSEBUTTONDOWN){
            button->pressed = true;
        }
    }
    else{
        button->mouseOn = false;
    }
}

void renderUIButton(struct Button* button, struct GameData* gameData){
    if (button->buttonTexture == ExitButton){
        renderXBox(gameData, button->mouseOn, button->xCor, button->yCor, button->xScale, button->yScale);
    }
    else if (button->buttonTexture == CheckButton){
        renderCheckBox(gameData, button->mouseOn, button->xCor, button->yCor, button->xScale, button->yScale);
    }
    else if (button->buttonTexture == BackButton){
        renderBackBox(gameData, button->mouseOn, button->xCor, button->yCor, button->xScale, button->yScale);
    }
    else if (button->buttonTexture == ForwardButton){
        renderForwardBox(gameData, button->mouseOn, button->xCor, button->yCor, button->xScale, button->yScale);
    }
    else if (button->buttonTexture == MainButton){
        renderScrollBar(gameData, button->mouseOn, button->xCor, button->yCor, button->xScale, button->yScale);
    }
}





struct ScrollWheel* createScrollWheel(int xCor, int yCor, int xScale, int yScale, int maxVal){
    struct ScrollWheel* scrollWheel = malloc(sizeof (struct ScrollWheel));
    if (scrollWheel == NULL){
        reportBug("Failed to malloc scroll wheel\n");
        return NULL;
    };
    scrollWheel->xCor = xCor;
    scrollWheel->yCor = yCor;

    scrollWheel->xScale = xScale;
    scrollWheel->yScale = yScale;

    scrollWheel->maxVal = maxVal;

    int pixelsPerValChange = (scrollWheel->xScale/scrollWheel->maxVal);
    scrollWheel->currentVal = (xScale/pixelsPerValChange) / 2;
    scrollWheel->lastX = 0;

    scrollWheel->currentX = xScale/2;

    scrollWheel->pressed = false;

    return scrollWheel;
}

void handleScrollWheelInputs(struct ScrollWheel* scrollWheel, struct GameData* gameData, SDL_Event event){
    bool mouseClickedPressed = event.button.button == SDL_BUTTON_LEFT;

    //Mouse input Controls
    int xCor, yCor;
    SDL_GetMouseState(&xCor, &yCor);

    //Get bounds of nob
    bool inXrange = (xCor < ((scrollWheel->xCor + scrollWheel->currentX) + scrollWheel->yScale) && xCor > scrollWheel->xCor + scrollWheel->currentX);
    bool inYrange = (yCor < (scrollWheel->yCor + scrollWheel->yScale) && yCor > scrollWheel->yCor);

    //If in range and mouse was clicked
    if (inXrange && inYrange && mouseClickedPressed){
        //base location off current value
        if (xCor < scrollWheel->xCor + scrollWheel->xScale && xCor > scrollWheel->xCor - scrollWheel->xScale) {
            scrollWheel->pressed = true;
            if (scrollWheel->lastX != 0) {
                if (xCor < scrollWheel->xCor + scrollWheel->xScale && xCor > scrollWheel->xCor) {
                    scrollWheel->currentX += (xCor - scrollWheel->lastX);
                }
            }
            scrollWheel->lastX = xCor;
            //Update scroll wheel value
            scrollWheel->currentVal = (scrollWheel->lastX - scrollWheel->xCor) / (scrollWheel->xScale/scrollWheel->maxVal);
        }
    }
    else{
        scrollWheel->pressed = false;
    }


}

void renderScrollWheel(struct ScrollWheel* scrollWheel, struct GameData* gameData){
    //Render the bar
    renderScrollBar(gameData, false, scrollWheel->xCor, scrollWheel->yCor, scrollWheel->xScale, scrollWheel->yScale);

    //Pointer Offset
    renderScrollPointer(gameData, scrollWheel->pressed, scrollWheel->xCor + scrollWheel->currentX, scrollWheel->yCor, scrollWheel->yScale, scrollWheel->yScale);
}