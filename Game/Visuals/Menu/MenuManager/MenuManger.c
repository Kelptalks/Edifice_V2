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
#include "Menus/WorldSelectMenu/WorldSelectMenu.h"
#include "../../../InGameTime/TikManager.h"
#include "Menus/WorldCreateMenu/WorldCreateMenu.h"
#include "../../../PlayerData/PlayerData.h"

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
    menuManager->worldSelectMenu = createWorldSelectMenu();
    menuManager->worldCreateMenu = createWorldCreateMenu();
    menuManager->onScreenUi = createOnScreenUI();
    menuManager->droneOnScreenUi = createDroneOnScreenUI();
    menuManager->console = CreateConsole();

    return menuManager;
}

void renderCurrentMenu(struct GameData* gameData){
    //Get the current Menu Type
    enum MenuType currentMenuType = gameData->menuManger->currentMenuType;

    if (currentMenuType == MainMenu){
        renderMainMenu(gameData);
    }
    else if (currentMenuType == CameraMenu) {
        Uint32 time1;
        Uint32 time2;
        //Render game world
        time1 = SDL_GetTicks();
        renderView(gameData);

        Uint32 UiRenderTime1 = SDL_GetTicks();
        //Render the Player UI
        if (gameData->menuManger->onScreenUi->visible) {
            renderOnScreenUI(gameData);
        }
        if(gameData->menuManger->droneOnScreenUi->visible){
            renderDroneOnScreenUI(gameData);
        }

        //render debug menu if visible
        if (gameData->debugMenu->visible) {
            renderDebugMenu(gameData);
        }

        if (gameData->menuManger->console->visible) {
            renderConsole(gameData);
        }

        Uint32 UiRenderTime2 = SDL_GetTicks();
        gameData->debugMenu->frameRenderingData->onScreenUIRenderingTime = UiRenderTime1 - UiRenderTime2;

        time2 = SDL_GetTicks();
        gameData->debugMenu->frameRenderingData->totalFrameTime = time2 - time1;

        updateTikTime(gameData);
    }
    else if (currentMenuType == SettingsMenu){
        renderSettingsMenu(gameData);
    }
    else if (currentMenuType == WorldSelectMenu){
        renderWorldSelectMenu(gameData);
    }
    else if (currentMenuType == WorldCreateMenu){
        renderWorldCreateMenu(gameData);
    }
}

void handleCurrentMenuInputs(struct GameData* gameData, SDL_Event event){
    switch (event.key.keysym.sym) {
        case SDLK_SLASH :
            gameData->menuManger->console->clickedOn = true;
        break;
    }


    enum MenuType currentMenuType = gameData->menuManger->currentMenuType;
    if (currentMenuType == MainMenu){
        handleInputMainMenu(gameData, event);
    }
    else if (currentMenuType == CameraMenu) {
        //Take on screen UI input
        bool onScreenUIMouseOn = false;
        if (gameData->menuManger->onScreenUi->visible){
            onScreenUIMouseOn = handleOnScreenUIInput(gameData, event);
        }
        if (!onScreenUIMouseOn && gameData->menuManger->droneOnScreenUi->visible){
            onScreenUIMouseOn = handleDroneOnScreenUI(gameData, event);
        }
        if (!onScreenUIMouseOn && gameData->menuManger->console->visible) {
            onScreenUIMouseOn = handleConsoleInputs(gameData, event);
        }
        if (!onScreenUIMouseOn) {
            // if on screen UI is not hit then take camera control inputs.
            cameraControlInput(gameData, event);
        }
        handlePlayerControls(gameData);
    }
    else if (currentMenuType == SettingsMenu){
        handleInputSettingsMenu(gameData, event);
    }
    else if (currentMenuType == WorldSelectMenu){
        handleWorldSelectMenuInputs(gameData, event);
    }
    else if (currentMenuType == WorldCreateMenu){
        handleWorldCreateMenuInputs(gameData, event);
    }

}