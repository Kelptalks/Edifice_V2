//
// Created by Spencer on 5/6/2024.
//

#include "../GameData.h"
#include <stdbool.h>
#include "Controls.h"
#include "SDL.h"
#include "../Visuals/Camera/CameraData.h"
#include "../World/World Saving/WorldFileManager.h"

void handleInput(struct GameData* gameData){
    //Handling close event
    SDL_Event event;
    while (SDL_PollEvent(&event)) {

        handleCurrentMenuInputs(gameData, event);


        const Uint8 *keystate = SDL_GetKeyboardState(NULL);

        switch (event.type) {
            //Exit the game when the x is pressed
            case SDL_QUIT:
                gameData->screen->run = false;
                if (gameData->world != NULL) {
                    //Loading screen
                    SDL_Rect srcRect = {896, 64, 64, 64};
                    SDL_Rect desRect = {0, 0, gameData->screen->xRez, gameData->screen->yRez};
                    SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet, &srcRect, &desRect);
                    renderStringCentered(gameData, "SavingWorld...", gameData->screen->xRez/2, gameData->screen->yRez/2, gameData->screen->xRez/32);
                    updateScreen(gameData->screen);
                    saveWorldToFile(gameData->world);
                }
                break;
        }
    }
}