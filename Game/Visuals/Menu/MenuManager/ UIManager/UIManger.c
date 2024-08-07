//
// Created by Spencer on 8/7/2024.
//

#include <SDL_events.h>
#include "../../../../GameData.h"
#include "UIManger.h"
#include "../../../../Debuging/Test_Main.h"
#include "UIRenderer/UIRenderer.h"

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
    scrollWheel->currentVal = 0;

}

void handleScrollWheelInputs(struct GameData* gameData, SDL_Event event){

}

void renderScrollWheel(struct ScrollWheel* scrollWheel, struct GameData* gameData){
    //Render the bar
    renderScrollBar(gameData, scrollWheel->xCor, scrollWheel->yCor, scrollWheel->xScale, scrollWheel->yScale);

    //Pointer Offset
    int xPointerOffset = 0;
    int yPointerOffset = scrollWheel->yScale/2;
    renderScrollPointer(gameData, scrollWheel->xCor, scrollWheel->yCor - yPointerOffset, scrollWheel->yScale, (scrollWheel->yScale * 2));
}