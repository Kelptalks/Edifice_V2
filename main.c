#include "SDL.h"
#include "Game/GameData.h"
#include "Game/Controls/Controls.h"
#include "Game/Visuals/Camera/Camera.h"
#include "Game/Visuals/Camera/Rendering/TextureManager/IsoTextureManager.h"
#include "Game/World/World.h"
#include "Game/Visuals/InMenuWindow/InMenuWindow.h"
#include "Game/World/World Saving/WorldFileManager.h"
#include "Game/InGameTime/TikManager.h"
#include "Game/World/WorldChunkHashMap/WorldChunkHashMap.h"
#include "Game/Visuals/Camera/Rendering/RayCasting/RayCastingManager.h"

int main(int argc, char* argv[]) {


    if (true) {
        struct GameData *gameData = createGameData();

        //Play start music
        playSound(gameData->soundManager, MusicSunn);

        while (gameData->screen->run) {
            //Get start time
            Uint32 time1 = SDL_GetTicks();

            //Control what the game is rendering
            renderCurrentMenu(gameData);

            SDL_SetRenderDrawColor(gameData->screen->renderer, 150, 255, 248, 255);
            SDL_RenderPresent(gameData->screen->renderer);
            SDL_RenderClear(gameData->screen->renderer);

            //Handle game inputs
            handleInput(gameData);
            updateTikTime(gameData);

            //end frame render time tracker
            Uint32 time2 = SDL_GetTicks();
            gameData->screen->frameRenderTime = time2 - time1;
            //Update current frame
            gameData->screen->currentFrame++;

        }
        openWorldFile(gameData->world);
    }
    return 0;
}
