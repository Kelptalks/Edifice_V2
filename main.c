#include "SDL.h"
#include "Game/GameData.h"
#include "Game/Controls/Controls.h"
#include "Game/Visuals/Camera/Camera.h"
#include "Game/Visuals/Camera/Rendering/TextureManager/IsoTextureManager.h"
#include "Game/World/World.h"
#include "Game/Visuals/Menu/Menu.h"
#include "Game/Visuals/InMenuWindow/InMenuWindow.h"
#include "Game/World/World Saving/WorldFileManager.h"
#include "Game/InGameTime/TikManager.h"

int main(int argc, char* argv[]) {
    struct GameData* gameData = createGameData();

    enum Direction direction;
    
    if (SDL_Init(SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    while (gameData->screen->run){
        //Control what the game is rendering
        if (gameData->screen->menuType == MainMenu){
            renderMainMenu(gameData, 0, 0);
        }
        else if (gameData->screen->menuType == SettingsMenu){
            renderSettingsMenu(gameData, 0, 0);
        }
        else if (gameData->screen->menuType == WorldCamera){
            //Render game world
            renderView(gameData);
            //Render window if visible
            if (gameData->cameraData->inMenuWindow->visible){
                renderInMenuWindow(gameData, gameData->cameraData->inMenuWindow);
            }
            //render debug menu if visible
            if (gameData->debugMenu->visible) {
                renderDebugMenu(gameData);
            }
        }

        SDL_SetRenderDrawColor(gameData->screen->renderer, 150, 255, 248, 255);
        SDL_RenderPresent(gameData->screen->renderer);
        SDL_RenderClear(gameData->screen->renderer);

        //Delay to limit frame rate
        SDL_Delay(gameData->screen->frameDelay);


        //Handle game inputs
        handleInput(gameData);

        updateTikTime(gameData);
    }

    openWorldFile(gameData->world);
    return 0;
}
