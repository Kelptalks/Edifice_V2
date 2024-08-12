//
// Created by Spencer on 6/8/2024.
//

#include <stdbool.h>
#include "../../GameData.h"
#include "InMenuWindow.h"
#include "../../Debuging/Test_Main.h"
#include "SDL.h"
#include "../../Blocks/Blocks.h"
#include "../../Visuals/Camera/Rendering/TextureManager/IsoTextureManager.h"
#include "../../PlayerData/PlayerData.h"
#include "../Menu/MenuManager/ UIManager/Button/Button.h"

struct InMenuWindow* createInMenuWindow(int xCor, int yCor, int xRez, int yRez){
    struct InMenuWindow* inMenuWindow = malloc(sizeof (struct InMenuWindow));
    if (inMenuWindow == NULL){
        reportBug("Failed to malloc inMenu window \n");
        return NULL;
    }

    inMenuWindow->xCor = xCor;
    inMenuWindow->yCor = yCor;
    inMenuWindow->xRez = xRez;
    inMenuWindow->yRez = yRez;
    inMenuWindow->visible = false;


    //Setup Buttons for block menu
    inMenuWindow->buttonCount = 50;
    inMenuWindow->menuButtons = malloc(sizeof (struct MenuButton) * inMenuWindow->buttonCount);
    int spacing = 64;
    int scale = 50;
    int color[3] = {100, 200, 100};

    int xButtonCor = xCor + (spacing - scale);
    int yButtonCor = yCor + (spacing - scale) + 50;
    for (int x = 0; x < inMenuWindow->buttonCount; x++){
        xButtonCor += spacing;
        if (xButtonCor > inMenuWindow->xRez - spacing) {
            yButtonCor += spacing;
            xButtonCor = xCor + (spacing - scale);
        }

        //Create the button
        inMenuWindow->menuButtons[x] = createMenuButton(scale, scale, xButtonCor, yButtonCor);
        //Set button color
        inMenuWindow->menuButtons[x]->color[0] = color[0];
        inMenuWindow->menuButtons[x]->color[1] = color[1];
        inMenuWindow->menuButtons[x]->color[2] = color[2];
    }

    return inMenuWindow;
}

bool InMenuWindowControls(struct GameData* gameData, struct InMenuWindow* inMenuWindow, SDL_Event event){
    //Check if in bounds of window
    int xCor, yCor;
    SDL_GetMouseState(&xCor, &yCor);
    if (xCor > inMenuWindow->xCor && yCor > inMenuWindow->yCor && xCor < (inMenuWindow->xCor + inMenuWindow->xRez) && yCor < (inMenuWindow->yCor + inMenuWindow->yRez)){
        for (int x = 0; x < inMenuWindow->buttonCount; x++) {
            buttonMouseInput(inMenuWindow->menuButtons[x], event);
            if (inMenuWindow->menuButtons[x]->pressed){
                gameData->playerData->block = x;
            }
        }
        return true;
    }
    return false;
}

void DrawBlockTexture(struct GameData* gameData, enum Block block, int xCor, int yCor){
    int xScale = 49;
    int yScale = 49;

    SDL_Texture* TopLeft = gameData->textures->BlockTextures[block].textures[TopLeftFace];
    SDL_Rect TopLeftRect = {xCor, yCor, xScale, yScale};
    SDL_RenderCopy(gameData->screen->renderer, TopLeft, NULL, &TopLeftRect);

    SDL_Texture* TopRight = gameData->textures->BlockTextures[block].textures[TopRightFace];
    SDL_Rect TopRightRect = {xCor + (xScale/2), yCor, xScale, yScale};
    SDL_RenderCopy(gameData->screen->renderer, TopRight, NULL, &TopRightRect);

    SDL_Texture* LeftTop = gameData->textures->BlockTextures[block].textures[LeftTopFace];
    SDL_Rect LeftTopRect = {xCor, yCor + (xScale/4), xScale, yScale};
    SDL_RenderCopy(gameData->screen->renderer, LeftTop, NULL, &LeftTopRect);

    SDL_Texture* LeftBot = gameData->textures->BlockTextures[block].textures[LeftBotFace];
    SDL_Rect LeftBotRect = {xCor, yCor + (xScale/2), xScale, yScale};
    SDL_RenderCopy(gameData->screen->renderer, LeftBot, NULL, &LeftBotRect);

    SDL_Texture* RightTop = gameData->textures->BlockTextures[block].textures[RightTopFace];
    SDL_Rect RightTopRect = {xCor + (xScale/2), yCor + (xScale/4), xScale, yScale};
    SDL_RenderCopy(gameData->screen->renderer, RightTop, NULL, &RightTopRect);

    SDL_Texture* RightBot = gameData->textures->BlockTextures[block].textures[RightBotFace];
    SDL_Rect RightBotRect = {xCor + (xScale/2), yCor + (xScale/2), xScale, yScale};
    SDL_RenderCopy(gameData->screen->renderer, RightBot, NULL, &RightBotRect);

}

void renderInMenuWindow(struct GameData* gameData, struct InMenuWindow* inMenuWindow){
    int topBarYRez = inMenuWindow->xRez/30;
    //Draw Main Box
    SDL_SetRenderDrawColor(gameData->screen->renderer, 255, 255, 255, 200);
    SDL_Rect mainBox = {inMenuWindow->xCor, inMenuWindow->yCor, inMenuWindow->xRez, inMenuWindow->yRez};
    SDL_RenderFillRect(gameData->screen->renderer, &mainBox);

    //Draw Top Bar
    SDL_SetRenderDrawColor(gameData->screen->renderer, 200, 200, 255, 255);
    SDL_Rect topBar = {inMenuWindow->xCor, inMenuWindow->yCor, inMenuWindow->xRez, topBarYRez};
    SDL_RenderFillRect(gameData->screen->renderer, &topBar);

    //Draw X box
    SDL_SetRenderDrawColor(gameData->screen->renderer, 255, 100, 100, 255);
    SDL_Rect xBox = {inMenuWindow->xCor + (inMenuWindow->xRez - topBarYRez), inMenuWindow->yCor, topBarYRez, topBarYRez};
    SDL_RenderFillRect(gameData->screen->renderer, &xBox);

    //Draw Main Box outline
    SDL_SetRenderDrawColor(gameData->screen->renderer, 100, 100, 100, 255);
    SDL_Rect outLine = {inMenuWindow->xCor, inMenuWindow->yCor, inMenuWindow->xRez, inMenuWindow->yRez};
    SDL_RenderDrawRect(gameData->screen->renderer, &outLine);

    //Draw Buttons
    for (int x = 0; x < inMenuWindow->buttonCount; x++) {
        renderButton(gameData, inMenuWindow->menuButtons[x]);
        DrawBlockTexture(gameData, x, inMenuWindow->menuButtons[x]->xCor, inMenuWindow->menuButtons[x]->yCor);
    }

};
