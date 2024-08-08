//
// Created by Spencer on 8/7/2024.
//

#include "../../../../../GameData.h"
#include "../../ UIManager/UIRenderer/UIRenderer.h"
#include "../../ UIManager/UIManger.h"
#include "../../../../../Debuging/Test_Main.h"
#include "MainMenu.h"

struct MainMenu* createMainMenu(){
    struct MainMenu* mainMenu = malloc(sizeof (struct MainMenu));
    if (mainMenu == NULL){
        reportBug("Failed to create Main menu\n");
        return NULL;
    }

    mainMenu->scrollWheel = createScrollWheel(50, 50, 128, 16, 30);
    mainMenu->button = createButton(CheckButton, 300, 300, 64, 64);

    return mainMenu;
}


void renderMainMenu(struct GameData* gameData){
    struct MainMenu* mainMenu = gameData->menuManger->mainMenu;
    renderUIButton(mainMenu->button, gameData);

    renderScrollWheel(mainMenu->scrollWheel, gameData);

}

void handleInputMainMenu(struct GameData* gameData, SDL_Event event){
    struct MainMenu* mainMenu = gameData->menuManger->mainMenu;
    handleButtonInputs(mainMenu->button, gameData, event);
    handleScrollWheelInputs(mainMenu->scrollWheel, gameData, event);
}