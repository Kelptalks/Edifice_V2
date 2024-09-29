//
// Created by Spencer on 9/29/2024.
//
#include "WorldSelectMenu.h"
#include "../../../../../World/World Saving/WorldFileManager.h"
#include <stdio.h>

struct WorldSelectMenu* createWorldSelectMenu(){
    struct WorldSelectMenu* worldSelectMenu = malloc(sizeof (struct WorldSelectMenu));

    worldSelectMenu->worldCount = 3;
    worldSelectMenu->worldButtons = malloc(sizeof (struct Button*) * worldSelectMenu->worldCount);
    worldSelectMenu->worldDeleteButtons = malloc(sizeof (struct Button*) * worldSelectMenu->worldCount);
    for (int i = 0; i < 3; i++){
        worldSelectMenu->worldButtons[i] = createButton(MainButton, 0, 0, 0, 0);
        worldSelectMenu->worldDeleteButtons[i] = createButton(ExitButton, 0, 0, 0, 0);
    }

    worldSelectMenu->backButton = createButton(BackButton, 0, 0, 0, 0);

    return worldSelectMenu;
}

void updateWorldSelectionMenuDrawCords(struct GameData* gameData){
    struct WorldSelectMenu* worldSelectMenu = gameData->menuManger->worldSelectMenu;

    int xButtonRez = gameData->screen->xRez/24;
    int yButtonRez = gameData->screen->xRez/24;;
    int xLongButtonRez = xButtonRez * 8;

    int buttonSpacing = (yButtonRez / 2) + yButtonRez;

    int xButtonCor = gameData->screen->xRez/2 - (xLongButtonRez/2);
    int yButtonCor = gameData->screen->yRez/2 - ((buttonSpacing * worldSelectMenu->worldCount) / 2);


    for (int i = 0; i < worldSelectMenu->worldCount; i++){
        struct Button* button = worldSelectMenu->worldButtons[i];
        button->xCor = xButtonCor;
        button->yCor = yButtonCor + (buttonSpacing * i);
        button->xScale = xLongButtonRez;
        button->yScale = yButtonRez;

        struct Button* deleteButton = worldSelectMenu->worldDeleteButtons[i];
        deleteButton->xCor = xButtonCor - xButtonRez - (buttonSpacing/3);
        deleteButton->yCor = yButtonCor + (buttonSpacing * i);
        deleteButton->xScale = xButtonRez;
        deleteButton->yScale = yButtonRez;
    }

    struct Button* backButton = worldSelectMenu->backButton;
    backButton->xScale = xButtonRez;
    backButton->yScale = yButtonRez;
    backButton->xCor = buttonSpacing / 3;
    backButton->yCor = gameData->screen->yRez - buttonSpacing;



}

void renderWorldSelectMenu(struct GameData* gameData){
    struct WorldSelectMenu* worldSelectMenu = gameData->menuManger->worldSelectMenu;
    updateWorldSelectionMenuDrawCords(gameData);

    for (int i = 0; i < worldSelectMenu->worldCount; i++){
        //Render world button
        struct Button* worldButton = worldSelectMenu->worldButtons[i];
        renderUIButton(worldButton, gameData);

        //Render World name if it exists
        char worldName[20] = {0};
        sprintf(worldName, "Saves/World%i.bin", i);

        if (ifFileExists(worldName)) {
            renderStringCentered(gameData, worldName,
                                 worldButton->xCor + (worldButton->xScale/2),
                                 worldButton->yCor + worldButton->yScale/2,
                                 worldButton->yScale/2);
        }
        else{
            renderStringCentered(gameData, "Empty Slot",
                                 worldButton->xCor + (worldButton->xScale/2),
                                 worldButton->yCor + worldButton->yScale/2,
                                 worldButton->yScale/2);
        }


        //Render world delete buttons
        struct Button* worldDeleteButton = worldSelectMenu->worldDeleteButtons[i];
        renderUIButton(worldDeleteButton, gameData);
        if (worldDeleteButton->mouseOn){
            renderString(gameData, "DELETE WORLD",
                         worldDeleteButton->xCor - (worldDeleteButton->xScale * 3),
                         worldDeleteButton->yCor + worldDeleteButton->yScale/3,
                         worldDeleteButton->xScale/4);
        }
    }

    renderUIButton(worldSelectMenu->backButton, gameData);


}

void handleWorldSelectMenuInputs(struct GameData* gameData, SDL_Event event){
    struct WorldSelectMenu* worldSelectMenu = gameData->menuManger->worldSelectMenu;
    for (int i = 0; i < worldSelectMenu->worldCount; i++){
        struct Button *worldButton = worldSelectMenu->worldButtons[i];
        handleButtonInputs(worldButton, gameData, event);
        if (worldButton->pressed){
            worldButton->pressed = false;
            if (i == 0) {

            }
            if (i == 1) {

            }
            if (i == 2) {

            }
            gameData->menuManger->currentMenuType = CameraMenu;
        }

        struct Button* deleteWorldButton = worldSelectMenu->worldDeleteButtons[i];
        handleButtonInputs(deleteWorldButton, gameData, event);
        if (deleteWorldButton->pressed){

        }

    }


    handleButtonInputs(worldSelectMenu->backButton, gameData, event);
    if (worldSelectMenu->backButton->pressed){
        worldSelectMenu->backButton->pressed = false;
        gameData->menuManger->currentMenuType = MainMenu;
    }
}

#include "WorldSelectMenu.h"
