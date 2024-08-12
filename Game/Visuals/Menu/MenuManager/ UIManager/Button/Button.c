//
// Created by Spencer on 6/7/2024.
//


#include <malloc.h>
#include "Button.h"
#include "../../../../../Debuging/Test_Main.h"
#include "SDL.h"
#include "../../../../../GameData.h"

//Create a menu button struct
struct MenuButton* createMenuButton(int width, int height, int xCor, int yCor){
    struct MenuButton* menuButton = malloc(sizeof (struct MenuButton));
    if (menuButton == NULL){
        reportBug("failed to malloc menuButton");
        return NULL;
    }
    menuButton->width = width;
    menuButton->height = height;
    menuButton->xCor = xCor;
    menuButton->yCor = yCor;
    menuButton->mouseOn = true;
    menuButton->pressed = false;

    for (int x = 0; x < 3; x++){
        menuButton->color[x] = 100;
    }

    return menuButton;
}

void renderButton(struct GameData* gameData, struct MenuButton* menuButton){
    int colorMod = 0;
    if (menuButton->pressed){
        colorMod = 50;
    }
    else if (menuButton->mouseOn) {
        colorMod = 20;
    }
    SDL_SetRenderDrawColor(gameData->screen->renderer, menuButton->color[0] + colorMod, menuButton->color[1] + colorMod, menuButton->color[2] + colorMod, 255);
    SDL_Rect rect = {menuButton->xCor, menuButton->yCor, menuButton->width, menuButton->height};
    SDL_RenderFillRect(gameData->screen->renderer, &rect);
}

//Record input for menu Button
void buttonMouseInput(struct MenuButton* menuButton, SDL_Event event){
    //Get the location of the mouse
    int xCor, yCor;
    SDL_GetMouseState(&xCor, &yCor);

    //Check if in bounds of mouse
    if (xCor > menuButton->xCor && yCor > menuButton->yCor && xCor < menuButton->xCor + menuButton->width && yCor < menuButton->yCor + menuButton->height){
        menuButton->mouseOn = true;
        if (event.type == SDL_MOUSEBUTTONDOWN){
            menuButton->pressed = true;
        }
        else{
            menuButton->pressed = false;
        }
    }
    else{
        menuButton->mouseOn = false;
    }
}