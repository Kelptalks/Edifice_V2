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
    settingsMenu->viewDistanceScrollWheel->currentVal = 16;
    settingsMenu->backButton = createButton(BackButton, 1920 - 64, 1080 - 64, 64, 64);

    settingsMenu->resolutionButtons = malloc(sizeof (struct Button*) * 3);
    for (int x = 0; x < 3; x++){
        settingsMenu->resolutionButtons[x] = createButton(MainButton, 0, 0, 0, 0);
    }

    return settingsMenu;
}

void updateButtonRenderCords(struct GameData* gameData){
    struct SettingsMenu* settingsMenu = gameData->menuManger->settingsMenu;

    int buttonScaleX = gameData->screen->xRez/24;
    int buttonScaleY = buttonScaleX;
    int buttonSpacing = (buttonScaleX / 3) + buttonScaleX;

    settingsMenu->backButton->xScale = buttonScaleX;
    settingsMenu->backButton->yScale = buttonScaleY;
    settingsMenu->backButton->xCor = buttonScaleX / 3;
    settingsMenu->backButton->yCor = gameData->screen->yRez - buttonSpacing;


    int buttonLongXScale = buttonScaleX * 8;
    settingsMenu->viewDistanceScrollWheel->xScale = buttonLongXScale;
    settingsMenu->viewDistanceScrollWheel->yScale = buttonScaleY;
    settingsMenu->viewDistanceScrollWheel->xCor = buttonScaleX;
    settingsMenu->viewDistanceScrollWheel->yCor = buttonScaleY;

    for (int x = 0; x < 3; x++){
        settingsMenu->resolutionButtons[x]->xScale = buttonLongXScale;
        settingsMenu->resolutionButtons[x]->yScale = buttonScaleY;
        settingsMenu->resolutionButtons[x]->xCor = buttonScaleX;
        settingsMenu->resolutionButtons[x]->yCor = settingsMenu->viewDistanceScrollWheel->yCor + buttonScaleY + (buttonSpacing * (x + 2));
    }

}

void renderSettingsMenu(struct GameData* gameData){
    updateButtonRenderCords(gameData);
    //Render background
    SDL_Rect srcRect = {656, 0, 240, 128};
    SDL_Rect desRect = {0, 0, gameData->screen->xRez, gameData->screen->yRez};
    SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet, &srcRect, &desRect);

    struct SettingsMenu* settingsMenu = gameData->menuManger->settingsMenu;
    settingsMenu->viewDistanceScrollWheel->maxVal = gameData->cameraData->maxViewDistance;

    struct Button* firstButton = settingsMenu->resolutionButtons[0];
    renderString(gameData, "Resolution", firstButton->xCor, firstButton->yCor - (firstButton->yScale/2), firstButton->yScale/2);

    for (int x = 0; x < 3; x++){
        struct Button* button = settingsMenu->resolutionButtons[x];
        renderUIButton(button, gameData);
        char *str;
        if (x == 0)str = "1280, 720";
        if (x == 1)str = "1920, 1080";
        if (x == 2)str = "2560, 1440";
        renderStringCentered(gameData, str, button->xCor + (button->xScale/2), button->yCor + (button->yScale/2), button->yScale/2);
    }


    //Scroll Wheel
    struct ScrollWheel* viewDistanceScrollWheel = settingsMenu->viewDistanceScrollWheel;
    renderScrollWheel(viewDistanceScrollWheel, gameData);
    //Scroll Wheel text
    int number = viewDistanceScrollWheel->currentVal;
    char str[12];
    sprintf(str, "%d", number); // Convert integer to string
    int buttonSpacing = (viewDistanceScrollWheel->xScale / 3) + viewDistanceScrollWheel->xScale;
    renderString(gameData, str, viewDistanceScrollWheel->xCor, viewDistanceScrollWheel->yCor + viewDistanceScrollWheel->yScale, viewDistanceScrollWheel->yScale/2);

    renderString(gameData, "View Distance", viewDistanceScrollWheel->xCor, viewDistanceScrollWheel->yCor - viewDistanceScrollWheel->yScale/2, viewDistanceScrollWheel->yScale/2);

    //Button
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
    if (backButton->pressed || event.key.keysym.sym == SDLK_ESCAPE){
        playSound(gameData->soundManager, SoundMenuButtonClick);
        backButton->pressed = false;
        if (gameData->world == NULL) {
            gameData->menuManger->currentMenuType = MainMenu;
        }
        else{
            gameData->menuManger->currentMenuType = CameraMenu;
        }
    }


    for (int x = 0; x < 3; x++){
        handleButtonInputs(settingsMenu->resolutionButtons[x], gameData, event);
    }
    struct Button* button = settingsMenu->resolutionButtons[0];
    if (button->pressed){
        button->pressed = false;
        setScreenResolution(gameData->screen, 1280, 720);
        playSound(gameData->soundManager, SoundMenuButtonClick);
    }
    button = settingsMenu->resolutionButtons[1];
    if (button->pressed){
        button->pressed = false;
        setScreenResolution(gameData->screen, 1920, 1080);
        playSound(gameData->soundManager, SoundMenuButtonClick);
    }
    button = settingsMenu->resolutionButtons[2];
    if (button->pressed){
        button->pressed = false;
        setScreenResolution(gameData->screen, 2560, 1440);
        playSound(gameData->soundManager, SoundMenuButtonClick);
    }
}
