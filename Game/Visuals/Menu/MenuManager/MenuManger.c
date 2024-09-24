//
// Created by Spencer on 8/7/2024.
//

#include <malloc.h>
#include "MenuManger.h"
#include "../../Camera/Controls/CameraControls.h"
#include "../../Camera/Camera.h"
#include "Menus/MainMenu/MainMenu.h"
#include "Menus/SettingsMenu/SettingsMenu.h"



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


    return menuManager;
}

void setCurrentMenu(){

}

void renderCurrentMenu(struct GameData* gameData){
    //Get the current Menu Type
    enum MenuType currentMenuType = gameData->menuManger->currentMenuType;

    if (currentMenuType == MainMenu){
        renderMainMenu(gameData);
    }
    else if (currentMenuType == CameraMenu) {
        //Render game world
        renderView(gameData);
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
        cameraControlInput(gameData, event);
    }
    else if (currentMenuType == SettingsMenu){
        handleInputSettingsMenu(gameData, event);
    }

}