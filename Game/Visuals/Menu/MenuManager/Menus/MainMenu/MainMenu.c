//
// Created by Spencer on 8/7/2024.
//

#include "MainMenu.h"

struct MainMenu* createMainMenu(){
    struct MainMenu* mainMenu = malloc(sizeof (struct MainMenu));
    if (mainMenu == NULL){
        reportBug("Failed to create Main menu\n");
        return NULL;
    }


    int xButtonScale = 64 * 8;
    int yButtonScale = 64;

    int xOffset = 64;
    int yOffset = 64;


    //Center the buttons and scale based on resolution
    mainMenu->startButton = createButton(MainButton, xOffset, yOffset, xButtonScale, yButtonScale);

    mainMenu->settingsButton = createButton(MainButton, xOffset, yOffset + 100, xButtonScale, yButtonScale);

    mainMenu->exitButton = createButton(MainButton, xOffset, yOffset + 200, xButtonScale, yButtonScale);

    return mainMenu;
}


void renderMainMenu(struct GameData* gameData){
    struct MainMenu* mainMenu = gameData->menuManger->mainMenu;

    //Render background
    SDL_Rect srcRect = {960, 0, 320, 175};
    SDL_Rect desRect = {0, 0, gameData->screen->xRez, gameData->screen->yRez};


    //Render all the buttons with text
    struct Button* startButton = mainMenu->startButton;
    renderUIButton(startButton, gameData);
    drawString(gameData, "Start", 5, startButton->xCor + startButton->xScale/4, startButton->yCor + (startButton->yScale/4), startButton->yScale/2);


    struct Button* settingsButton = mainMenu->settingsButton;
    renderUIButton(settingsButton, gameData);
    drawString(gameData, "Settings", 8, settingsButton->xCor + settingsButton->xScale/4, settingsButton->yCor + (settingsButton->yScale/4), settingsButton->yScale/2);


    struct Button* exitButton = mainMenu->exitButton;
    renderUIButton(exitButton, gameData);
    drawString(gameData, "exit", 4, exitButton->xCor + exitButton->xScale/4, exitButton->yCor + (exitButton->yScale/4), exitButton->yScale/2);


}

void handleInputMainMenu(struct GameData* gameData, SDL_Event event){
    struct MainMenu* mainMenu = gameData->menuManger->mainMenu;

    //Handle button inputs
    struct Button* startButton = mainMenu->startButton;
    handleButtonInputs(startButton, gameData, event);
    if (startButton->pressed){
        startButton->pressed = false;
        gameData->menuManger->currentMenuType = CameraMenu;
    }

    struct Button* settingsButton = mainMenu->settingsButton;
    handleButtonInputs(settingsButton, gameData, event);
    if (settingsButton->pressed){
        settingsButton->pressed = false;
        gameData->menuManger->currentMenuType = SettingsMenu;
    }

    struct Button* exitButton = mainMenu->exitButton;
    handleButtonInputs(exitButton, gameData, event);
    if (exitButton->pressed){
        exitButton->pressed = false;
        gameData->screen->run = false;
    }
}