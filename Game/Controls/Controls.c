//
// Created by Spencer on 5/6/2024.
//

#include "../GameData.h"
#include "../Visuals/Screen.h"
#include <stdbool.h>
#include "Controls.h"
#include "SDL.h"
#include "../Visuals/Camera/CameraData.h"
#include "../Visuals/Camera/Controls/CameraControls.h"
#include "../Visuals/InMenuWindow/InMenuWindow.h"

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
                break;
        }
    }
}