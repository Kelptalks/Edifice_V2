//
// Created by Spencer on 6/6/2024.
//

#include <setjmp.h>
#include <stdio.h>
#include "SDL.h"
#include "Menu.h"
#include "../../Debuging/Test_Main.h"

struct Menu* createMenu(){
    struct Menu* menu = malloc(sizeof (struct Menu));
    if (menu == NULL){
        reportBug("Failed to create main menu\n");
        return NULL;
    }

    menu->buttonCount = 2;

    menu->menuButtons = malloc(sizeof (struct MenuButton*) * menu->buttonCount);
    if (menu->menuButtons == NULL){
        reportBug("Failed to malloc menuButton Array\n");
        return NULL;
    }

    for (int x = 0; x < menu->buttonCount; x++) {
        menu->menuButtons[x] = createMenuButton(200, 50, 50, 50 + (x * 75));
    }
    return menu;
}

void menuControlInput(struct GameData* gameData, SDL_Event event){
    struct Menu* menu = gameData->menu;
    for (int x = 0; x < menu->buttonCount; x++) {
        buttonMouseInput(menu->menuButtons[x], event);
    }
}

void renderMenu(struct GameData* gameData, int xCor, int yCor){
    struct Menu* menu = gameData->menu;

    for (int x = 0; x < gameData->menu->buttonCount; x++){
        renderButton(gameData, menu->menuButtons[x]);
    }

    if (menu->menuButtons[0]->pressed){
        gameData->screen->menuType = WorldCamera;
    }

}