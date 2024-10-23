//
// Created by Spencer on 10/23/2024.
//

#include "GameSpeedControls.h"
#include "../../../../InGameTime/TikManager.h"

#include <stdlib.h>
#include <windows.h>


struct GameSpeedControls* createGameSpeedControls() {
    struct GameSpeedControls* gameSpeedControls = malloc(sizeof(struct GameSpeedControls));
    if (gameSpeedControls == NULL) {
        reportBug("failed to malloc game speed controls\n");
        return NULL;
    }

    gameSpeedControls->currentSpeed = 0;
    gameSpeedControls->totalSpeeds = 5;


    gameSpeedControls->speeds = malloc(sizeof(int) * gameSpeedControls->totalSpeeds);
    if (gameSpeedControls->speeds == NULL) {
        reportBug("failed to malloc gameSpeedControls speeds\n");
        free(gameSpeedControls);
        return NULL;
    }
    gameSpeedControls->speeds[0] = 1;
    gameSpeedControls->speeds[1] = 5;
    gameSpeedControls->speeds[2] = 10;
    gameSpeedControls->speeds[3] = 50;
    gameSpeedControls->speeds[4] = 100;


    return gameSpeedControls;
}

void renderGameSpeedControls(struct GameData* gameData) {
    struct GameSpeedControls* gameSpeedControls = gameData->menuManger->droneOnScreenUi->gameSpeedControls;
    SDL_Rect srcSpeedRect = {1136, 368, 16, 16};
    SDL_Rect srcSelectedSpeedRect = {1136, 352, 16, 16};

    int renderScale = gameData->screen->xRez / 32;
    int xOffset = gameData->screen->xRez - (renderScale * gameSpeedControls->totalSpeeds);
    for (int i = 0; i < gameSpeedControls->totalSpeeds; i++) {
        SDL_Rect destRect = {(i * renderScale + xOffset), 0, renderScale, renderScale};
        if (i <= gameSpeedControls->currentSpeed) {
            SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet, &srcSelectedSpeedRect, &destRect);
        }
        else {
            SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet, &srcSpeedRect, &destRect);
        }
    }

    char currentSpeed[20] = {};
    sprintf(currentSpeed, "%i", gameSpeedControls->speeds[gameSpeedControls->currentSpeed]);
    renderStringCentered(gameData, currentSpeed, gameData->screen->xRez - (renderScale * gameSpeedControls->totalSpeeds/2), renderScale, renderScale/2);
}

void handleGameSpeedInputs(struct GameData* gameData, SDL_Event event) {
    struct GameSpeedControls* gameSpeedControls = gameData->menuManger->droneOnScreenUi->gameSpeedControls;
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_MINUS :
                if (gameSpeedControls->currentSpeed > 0) {
                    gameSpeedControls->currentSpeed--;
                }
            break;
            case SDLK_EQUALS :
                if (gameSpeedControls->currentSpeed < gameSpeedControls->totalSpeeds - 1) {
                    gameSpeedControls->currentSpeed++;
                }
            break;
        }
    }
    gameData->tikManager->ticksPerInterVal = gameSpeedControls->speeds[gameSpeedControls->currentSpeed];
}