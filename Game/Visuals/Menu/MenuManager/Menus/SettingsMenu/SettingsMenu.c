//
// Created by Spencer on 8/12/2024.
//
#include "../../MenuManger.h"
#include "../../../../Camera/CameraData.h"

struct SettingsMenu* createSettingsMenu(){
    struct SettingsMenu* settingsMenu = malloc(sizeof (struct SettingsMenu));
    if (settingsMenu == NULL){
        reportBug("Failed to malloc settings menu\n");
        return NULL;
    }

    int xButtonScale = 64 * 8;
    int yButtonScale = 64;

    int xOffset = 64;
    int yOffset = 64;

    settingsMenu->viewDistanceScrollWheel = createScrollWheel(xOffset, yOffset, xButtonScale, yButtonScale, 64);
    settingsMenu->backButton = createButton(ExitButton, 1920 - 64, 1080 - 64, 64, 64);


    return settingsMenu;
}

void renderSettingsMenu(struct GameData* gameData){
    struct SettingsMenu* settingsMenu = gameData->menuManger->settingsMenu;


    struct ScrollWheel* viewDistanceScrollWheel = settingsMenu->viewDistanceScrollWheel;
    renderScrollWheel(viewDistanceScrollWheel, gameData);

    int number = viewDistanceScrollWheel->currentVal;
    char str[12];
    // Convert integer to string
    sprintf(str, "%d", number);
    drawString(gameData, str, 12, viewDistanceScrollWheel->xCor, viewDistanceScrollWheel->yCor + viewDistanceScrollWheel->yScale, viewDistanceScrollWheel->yScale/2);
    drawString(gameData, "View Distance", 13, viewDistanceScrollWheel->xCor, viewDistanceScrollWheel->yCor - viewDistanceScrollWheel->yScale, viewDistanceScrollWheel->yScale/2);

    struct Button* backButton = settingsMenu->backButton;
    renderUIButton(backButton, gameData);

}

void handleInputSettingsMenu(struct GameData* gameData, SDL_Event event){

    struct SettingsMenu* settingsMenu = gameData->menuManger->settingsMenu;

    struct ScrollWheel* viewDistanceScrollWheel = settingsMenu->viewDistanceScrollWheel;
    handleScrollWheelInputs(viewDistanceScrollWheel, gameData, event);
    gameData->cameraData->viewDistance = settingsMenu->viewDistanceScrollWheel->currentVal;

    struct Button* backButton = settingsMenu->backButton;
    handleButtonInputs(backButton, gameData, event);
    if (backButton->pressed){
        backButton->pressed = false;
        gameData->menuManger->currentMenuType = MainMenu;
    }
}
