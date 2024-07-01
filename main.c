#include "SDL.h"
#include "Game/GameData.h"
#include "Game/Controls/Controls.h"
#include "Game/Visuals/Camera/Camera.h"
#include "Game/Visuals/Camera/Rendering/TextureManager/IsoTextureManager.h"
#include "Game/World/World.h"
#include "Game/Visuals/Menu/Menu.h"
#include "Game/Visuals/InMenuWindow/InMenuWindow.h"
#include "Game/World/World Saving/WorldFileManager.h"

int main(int argc, char* argv[]) {
    struct GameData* gameData = createGameData();
    if (SDL_Init(SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }


    while (gameData->screen->run){
        Uint32 time1 = SDL_GetTicks();
        //Control what the game is rendering
        if (gameData->screen->menuType == MainMenu){
            renderMenu(gameData, 0, 0);
        }
        else if (gameData->screen->menuType == WorldCamera){
            //Render game world
            renderView(gameData, 0, 0);
            //Render window if visible
            if (gameData->cameraData->inMenuWindow->visible){
                renderInMenuWindow(gameData, gameData->cameraData->inMenuWindow);
            }
            //render debug menu if visible
            if (gameData->debugMenu->visible) {
                renderDebugMenu(gameData);
            }
        }
        //Handle game inputs
        handleInput(gameData);

        SDL_SetRenderDrawColor(gameData->screen->renderer, 255, 255, 255, 255);
        SDL_RenderPresent(gameData->screen->renderer);
        SDL_RenderClear(gameData->screen->renderer);

        //Delay to limit frame rate
        SDL_Delay(gameData->screen->frameDelay);

        Uint32 time2 = SDL_GetTicks();
        gameData->screen->frameRenderTime = time2 - time1;
    }

    openWorldFile(gameData->world);
    return 0;
}
