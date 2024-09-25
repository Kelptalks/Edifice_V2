//
// Created by Spencer on 8/7/2024.
//

#include <malloc.h>
#include "MenuManger.h"
#include "../../Camera/Controls/CameraControls.h"
#include "../../Camera/Camera.h"
#include "Menus/MainMenu/MainMenu.h"
#include "Menus/SettingsMenu/SettingsMenu.h"
#include "../OnScreenUI/OnScreenUI.h"


struct MenuManager* createMenuManager(){
    struct MenuManager* menuManager = malloc(sizeof (struct MenuManager));
    if (menuManager == NULL){
        reportBug("failed to create menuManager\n");
        return NULL;
    }
    //Set the default menu to main
    menuManager->currentMenuType = MainMenu;
    menuManager->mainMenu = createMainMenu();
    menuManager->settingsMenu = createSettingsMenu();
    menuManager->onScreenUi = createOnScreenUI();


    return menuManager;
}

void setCurrentMenu(){

}

void renderCurrentMenu(struct GameData* gameData){
    //Get the current Menu Type
    enum MenuType currentMenuType = gameData->menuManger->currentMenuType;

    Uint32 time1;
    Uint32 time2;
    if (currentMenuType == MainMenu){
        renderMainMenu(gameData);
    }
    else if (currentMenuType == CameraMenu) {
        //Render game world
        time1 = SDL_GetTicks();
        renderView(gameData);
        time2 = SDL_GetTicks();
        gameData->debugMenu->frameRenderingData->totalFrameTime = time2 - time1;

        //Render the Player UI
        time1 = SDL_GetTicks();
        renderOnScreenUI(gameData);
        time2 = SDL_GetTicks();
        gameData->debugMenu->frameRenderingData->onScreenUIRenderingTime = time2 - time1;

        //render debug menu if visible
        if (gameData->debugMenu->visible) {
            renderDebugMenu(gameData);
        }

    }
    else if (currentMenuType == SettingsMenu){
        renderSettingsMenu(gameData);
    }
}

void handleCurrentMenuInputs(struct GameData* gameData, SDL_Event event){
    enum MenuType currentMenuType = gameData->menuManger->currentMenuType;
    if (currentMenuType == MainMenu){
        handleInputMainMenu(gameData, event);
    }
    else if (currentMenuType == CameraMenu) {
        //Take on screen UI input
        if (!handleOnScreenUIInput(gameData, event)) {
            // if on screen UI is not hit then take camera control inputs.
            cameraControlInput(gameData, event);
        }
    }
    else if (currentMenuType == SettingsMenu){
        handleInputSettingsMenu(gameData, event);
    }

}