//
// Created by Spencer on 9/29/2024.
//
#include "WorldSelectMenu.h"
#include "../../../../../World/World Saving/WorldFileManager.h"
#include "../../../../../Visuals/Camera/CameraData.h"
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
    worldSelectMenu->confirmDeleteButton = createButton(CheckButton, 0, 0 ,0 ,0);
    worldSelectMenu->cancelDeleteButton = createButton(ExitButton, 0, 0, 0, 0);

    worldSelectMenu->worldToDelete = 0;
    worldSelectMenu->confirmDeleteVisible = false;

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

    struct Button* confirmDeleteButton = worldSelectMenu->confirmDeleteButton;
    confirmDeleteButton->xScale = xButtonRez;
    confirmDeleteButton->yScale = yButtonRez;
    confirmDeleteButton->xCor = ((gameData->screen->xRez / 2) - (xButtonRez/2)) - buttonSpacing;
    confirmDeleteButton->yCor = (gameData->screen->yRez / 5);

    struct Button* cancelDeleteButton = worldSelectMenu->cancelDeleteButton;
    cancelDeleteButton->xScale = xButtonRez;
    cancelDeleteButton->yScale = yButtonRez;
    cancelDeleteButton->xCor = ((gameData->screen->xRez / 2) - (xButtonRez/2)) + buttonSpacing;
    cancelDeleteButton->yCor = (gameData->screen->yRez / 5);

}

void renderWorldSelectMenu(struct GameData* gameData){
    struct WorldSelectMenu* worldSelectMenu = gameData->menuManger->worldSelectMenu;
    updateWorldSelectionMenuDrawCords(gameData);

    //Render background
    SDL_Rect srcRect = {656, 0, 240, 128};
    SDL_Rect desRect = {0, 0, gameData->screen->xRez, gameData->screen->yRez};
    SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet, &srcRect, &desRect);

    renderStringCentered(gameData, "Select a world",
                         gameData->screen->xRez/2,
                         gameData->screen->xRez/24,
                         gameData->screen->xRez/24);

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
        if(ifFileExists(worldName)){
            renderUIButton(worldDeleteButton, gameData);
        }

        if (worldDeleteButton->mouseOn){
            renderString(gameData, "DELETE WORLD",
                         worldDeleteButton->xCor - (worldDeleteButton->xScale * 3),
                         worldDeleteButton->yCor + worldDeleteButton->yScale/3,
                         worldDeleteButton->xScale/4);
        }
    }

    //Render Confirm delete world if visible
    if (worldSelectMenu->confirmDeleteVisible){
        renderStringCentered(gameData, "Are you Sure you want to delete your world?", gameData->screen->xRez/2,
                             gameData->screen->yRez/6,
                             worldSelectMenu->confirmDeleteButton->xScale/4);


        //Render Confirm button
        struct Button* confirm = worldSelectMenu->confirmDeleteButton;
        renderUIButton(confirm, gameData);
        if (confirm->mouseOn){
            renderStringCentered(gameData, "CONFIRM",
                                 confirm->xCor + confirm->yScale/2,
                                 confirm->yCor + confirm->yScale,
                                 confirm->xScale/3);
        }

        //Render cancel button
        struct Button* cancel = worldSelectMenu->cancelDeleteButton;
        renderUIButton(cancel, gameData);
        if (cancel->mouseOn){
            renderStringCentered(gameData, "CANCEL",
                                 cancel->xCor + cancel->xScale/2,
                                 cancel->yCor + cancel->yScale,
                                 cancel->xScale/3);
        }
    }

    renderUIButton(worldSelectMenu->backButton, gameData);

}

void handleWorldSelectMenuInputs(struct GameData* gameData, SDL_Event event){
    struct WorldSelectMenu* worldSelectMenu = gameData->menuManger->worldSelectMenu;

    handleButtonInputs(worldSelectMenu->confirmDeleteButton, gameData, event);
    if (worldSelectMenu->confirmDeleteButton->pressed) {
        playSound(gameData->soundManager, SoundMenuButtonClick);
        worldSelectMenu->confirmDeleteButton->pressed = false;
        worldSelectMenu->confirmDeleteVisible = false;
        //Get world name of index
        char worldName[20] = {0};
        sprintf(worldName, "Saves/World%i.bin", worldSelectMenu->worldToDelete);
        if (ifFileExists(worldName)) {
            deleteWorldFile(worldName);
        }
        return;
    }

    handleButtonInputs(worldSelectMenu->cancelDeleteButton, gameData, event);
    if (worldSelectMenu->cancelDeleteButton->pressed) {
        playSound(gameData->soundManager, SoundMenuButtonClick);
        worldSelectMenu->cancelDeleteButton->pressed = false;
        worldSelectMenu->confirmDeleteVisible = false;
        return;
    }

    for (int i = 0; i < worldSelectMenu->worldCount; i++){
        struct Button *worldButton = worldSelectMenu->worldButtons[i];
        handleButtonInputs(worldButton, gameData, event);


        if (worldButton->pressed){
            playSound(gameData->soundManager, SoundMenuButtonClick);
            worldButton->pressed = false;
            //Get world name of index
            char worldName[20] = {0};
            sprintf(worldName, "Saves/World%i.bin", i);

            //If the file exists loads
            if (ifFileExists(worldName)){
                gameData->world = readWorldData(worldName);
                gameData->cameraData->world = gameData->world;
                gameData->menuManger->currentMenuType = CameraMenu;
            }
            //If the file does not go to world create menu
            else{
                gameData->world = createWorld(worldName);
                gameData->menuManger->currentMenuType = WorldCreateMenu;
            }

        }

        struct Button* deleteWorldButton = worldSelectMenu->worldDeleteButtons[i];
        handleButtonInputs(deleteWorldButton, gameData, event);
        if (deleteWorldButton->pressed){
            playSound(gameData->soundManager, SoundMenuButtonClick);
            deleteWorldButton->pressed = false;
            worldSelectMenu->confirmDeleteVisible = true;
            worldSelectMenu->worldToDelete = i;
        }

    }


    handleButtonInputs(worldSelectMenu->backButton, gameData, event);
    if (worldSelectMenu->backButton->pressed){
        playSound(gameData->soundManager, SoundMenuButtonClick);
        worldSelectMenu->backButton->pressed = false;
        gameData->menuManger->currentMenuType = MainMenu;
    }
}

#include "WorldSelectMenu.h"
