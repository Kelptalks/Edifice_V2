//
// Created by Spencer on 8/7/2024.
//

#include "MainMenu.h"

void upDateMainMenuCords(struct GameData* gameData){
    struct MainMenu* mainMenu = gameData->menuManger->mainMenu;

    int buttonScale = gameData->screen->xRez / 24;

    int xButtonScale = buttonScale * 8;
    int yButtonScale = buttonScale;
    int buttonSpacing = buttonScale + (buttonScale/2);


    mainMenu->startButton->xScale = xButtonScale;
    mainMenu->startButton->yScale = yButtonScale;
    mainMenu->startButton->xCor = (gameData->screen->xRez/2) - (xButtonScale/2);
    mainMenu->startButton->yCor = (gameData->screen->yRez/2) - (yButtonScale/2) - buttonSpacing;

    mainMenu->settingsButton->xScale = xButtonScale;
    mainMenu->settingsButton->yScale = yButtonScale;
    mainMenu->settingsButton->xCor = (gameData->screen->xRez/2) - (xButtonScale/2);
    mainMenu->settingsButton->yCor = (gameData->screen->yRez/2) - (yButtonScale/2);

    mainMenu->exitButton->xScale = xButtonScale;
    mainMenu->exitButton->yScale = yButtonScale;
    mainMenu->exitButton->xCor = (gameData->screen->xRez/2) - (xButtonScale/2);
    mainMenu->exitButton->yCor = (gameData->screen->yRez/2) - (yButtonScale/2) + buttonSpacing;
}

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
    mainMenu->animationFrame = 0;

    return mainMenu;
}

void renderMainMenu(struct GameData* gameData){
    struct MainMenu* mainMenu = gameData->menuManger->mainMenu;
    upDateMainMenuCords(gameData);

    //Render background
    SDL_Rect srcRect = {960, 0, 320, 175};
    SDL_Rect desRect = {0, 0, gameData->screen->xRez, gameData->screen->yRez};
    SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet, &srcRect, &desRect);

    //Render all the buttons with text
    struct Button* startButton = mainMenu->startButton;
    renderUIButton(startButton, gameData);
    renderStringCentered(gameData, "Start", startButton->xCor + startButton->xScale/2, startButton->yCor + (startButton->yScale/2), startButton->yScale/3);

    struct Button* settingsButton = mainMenu->settingsButton;
    renderUIButton(settingsButton, gameData);
    renderStringCentered(gameData, "Settings", settingsButton->xCor + settingsButton->xScale/2, settingsButton->yCor + (settingsButton->yScale/2), settingsButton->yScale/3);

    struct Button* exitButton = mainMenu->exitButton;
    renderUIButton(exitButton, gameData);
    renderStringCentered(gameData, "exit", exitButton->xCor + exitButton->xScale/2, exitButton->yCor + exitButton->yScale/2, exitButton->yScale/3);
}

void handleInputMainMenu(struct GameData* gameData, SDL_Event event){
    struct MainMenu* mainMenu = gameData->menuManger->mainMenu;

    //Handle button inputs
    struct Button* startButton = mainMenu->startButton;
    handleButtonInputs(startButton, gameData, event);
    if (startButton->pressed){
        playSound(gameData->soundManager, SoundMenuButtonClick);
        startButton->pressed = false;
        gameData->menuManger->currentMenuType = CameraMenu;
    }

    struct Button* settingsButton = mainMenu->settingsButton;
    handleButtonInputs(settingsButton, gameData, event);
    if (settingsButton->pressed){
        playSound(gameData->soundManager, SoundMenuButtonClick);
        settingsButton->pressed = false;
        gameData->menuManger->currentMenuType = SettingsMenu;
    }

    struct Button* exitButton = mainMenu->exitButton;
    handleButtonInputs(exitButton, gameData, event);
    if (exitButton->pressed){
        playSound(gameData->soundManager, SoundMenuButtonClick);
        exitButton->pressed = false;
        gameData->screen->run = false;
    }
}