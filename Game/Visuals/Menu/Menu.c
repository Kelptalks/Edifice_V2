//
// Created by Spencer on 6/6/2024.
//

#include <setjmp.h>
#include <stdio.h>
#include "SDL.h"
#include "Menu.h"
#include "../../Debuging/Test_Main.h"
#include "../Camera/Rendering/TextureManager/IsoTextureManager.h"
#include "../Camera/CameraData.h"


struct Menu* createSettingsMenu(){
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
    //Setup Buttons
    int xRez = 1920;
    int yRez = 1080;
    int color[3] = {255, 255, 255};
    for (int x = 0; x < menu->buttonCount; x++) {
        menu->menuButtons[x] = createMenuButton(25, 25, 25, 25);
        menu->menuButtons[x]->name = "NULL";
        menu->menuButtons[x]->nameLength = 4;
    }

    //Setup Button names

    int menuEdditing = 0;
    menu->menuButtons[menuEdditing]->name = "+ViewDistance";
    menu->menuButtons[menuEdditing]->nameLength = 13;

    menu->menuButtons[menuEdditing]->xCor = 50;
    menu->menuButtons[menuEdditing]->yCor = 160;
    menu->menuButtons[menuEdditing]->width = 50;
    menu->menuButtons[menuEdditing]->height = 50;
    //Color for +viewDistance (Green
    menu->menuButtons[menuEdditing]->color[0] = 0;
    menu->menuButtons[menuEdditing]->color[1] = 200;
    menu->menuButtons[menuEdditing]->color[2] = 0;

    //
    menuEdditing = 1;
    menu->menuButtons[menuEdditing]->name = "-ViewDistance";
    menu->menuButtons[menuEdditing]->nameLength = 13;

    menu->menuButtons[menuEdditing]->xCor = 50;
    menu->menuButtons[menuEdditing]->yCor = 50;
    menu->menuButtons[menuEdditing]->width = 50;
    menu->menuButtons[menuEdditing]->height = 50;

    //Color for -viewDistance (RED)
    menu->menuButtons[menuEdditing]->color[0] = 200;
    menu->menuButtons[menuEdditing]->color[1] = 0;
    menu->menuButtons[menuEdditing]->color[2] = 0;
    return menu;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Main menu
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

struct Menu* createMainMenu(){
    struct Menu* menu = malloc(sizeof (struct Menu));
    if (menu == NULL){
        reportBug("Failed to create main menu\n");
        return NULL;
    }

    menu->buttonCount = 3;
    menu->menuButtons = malloc(sizeof (struct MenuButton*) * menu->buttonCount);
    if (menu->menuButtons == NULL){
        reportBug("Failed to malloc menuButton Array\n");
        return NULL;
    }
    //Setup Buttons
    int xRez = 1920;
    int yRez = 1080;
    int color[3] = {200, 200, 200};
    for (int x = 0; x < menu->buttonCount; x++) {
        menu->menuButtons[x] = createMenuButton(500, 100, xRez/2 - 250, (yRez/2) - ((menu->buttonCount * 150)/2) + (x * 150));
        menu->menuButtons[x]->name = "NULL";
        menu->menuButtons[x]->nameLength = 4;
        menu->menuButtons[x]->color[0] = color[0];
        menu->menuButtons[x]->color[1] = color[1];
        menu->menuButtons[x]->color[2] = color[2];
    }

    //Setup Button names
    menu->menuButtons[0]->name = "Start";
    menu->menuButtons[0]->nameLength = 5;

    menu->menuButtons[1]->name = "Settings";
    menu->menuButtons[1]->nameLength = 8;

    menu->menuButtons[2]->name = "Testing";
    menu->menuButtons[2]->nameLength = 7;

    menu->settingsMenu = createSettingsMenu();
    return menu;
}

void MainMenuControlInput(struct GameData* gameData, SDL_Event event){
    struct Menu* menu = gameData->menu;
    for (int x = 0; x < menu->buttonCount; x++) {
        buttonMouseInput(menu->menuButtons[x], event);
    }
}

void renderMainMenu(struct GameData* gameData, int xCor, int yCor){
    struct Menu* menu = gameData->menu;
    SDL_Rect srcRect = {960, 0, 320, 180};
    SDL_Rect drawRect = {0, 0, gameData->screen->xRez, gameData->screen->yRez};
    SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet, &srcRect, &drawRect);

    for (int x = 0; x < gameData->menu->buttonCount; x++){
        struct MenuButton* menuButton = menu->menuButtons[x];

        renderButton(gameData, menuButton);
        drawString(gameData, menuButton->name, menuButton->nameLength, menuButton->xCor + menuButton->width/2 - ((30 / 2) * menuButton->nameLength), menuButton->yCor + menuButton->height/2 - (30/2), 30);
    }

    if (menu->menuButtons[0]->pressed){
        gameData->screen->menuType = WorldCamera;
        menu->menuButtons[0]->pressed = false;
    }
    if (menu->menuButtons[1]->pressed){
        gameData->screen->menuType = SettingsMenu;
        menu->menuButtons[1]->pressed = false;
    }


    SDL_Rect testRect = {50, 50, 64, 64};

    SDL_RenderCopy(gameData->screen->renderer, gameData->textures->blockShaders->textures[LeftTopFace], NULL, &testRect);

}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Settings menu
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

void settingsMenuControlInput(struct GameData* gameData, SDL_Event event){
    struct Menu* menu = gameData->menu->settingsMenu;
    for (int x = 0; x < menu->buttonCount; x++) {
        buttonMouseInput(menu->menuButtons[x], event);
    }
    if (menu->menuButtons[0]->pressed){
        gameData->cameraData->viewDistance++;
        menu->menuButtons[0]->pressed = false;
    }
    else if (menu->menuButtons[1]->pressed){
        gameData->cameraData->viewDistance--;
        menu->menuButtons[1]->pressed = false;
    }
}

void renderSettingsMenu(struct GameData* gameData, int xCor, int yCor){
    struct Menu* menu = gameData->menu->settingsMenu;

    SDL_Rect srcRect = {960, 0, 320, 180};
    SDL_Rect drawRect = {0, 0, gameData->screen->xRez, gameData->screen->yRez};
    SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet, &srcRect, &drawRect);

    for (int x = 0; x < menu->buttonCount; x++){
        struct MenuButton* menuButton = menu->menuButtons[x];
        renderButton(gameData, menuButton);
        drawString(gameData, menuButton->name, menuButton->nameLength, menuButton->xCor + menuButton->width/2 - ((15 / 2) * menuButton->nameLength), menuButton->yCor, 15);
    }
}