#include "SDL.h"
#include "Game/GameData.h"
#include "Game/Controls/Controls.h"
#include "Game/Visuals/Camera/Camera.h"
#include "Game/Visuals/Camera/Rendering/TextureManager/IsoTextureManager.h"
#include "Game/World/World.h"
#include "Game/World/World Saving/WorldFileManager.h"
#include "Game/InGameTime/TikManager.h"
#include "Game/World/WorldChunkHashMap/WorldChunkHashMap.h"
#include "Game/Visuals/Camera/Rendering/RayCasting/RayCastingManager.h"
#include "Game/InGameTime/Drone/DroneLuaCommands/DroneLuaCommands.h"
#include "Game/InGameTime/Drone/Drone.h"

#include <stdio.h>

int main(int argc, char* argv[]) {
    //int temp = getOctreeVolume(6);
    //reportBug("Octree volume %i", temp);
    //testWorldSaving();
    if (true) {
        struct GameData *gameData = createGameData();

        //Play start music
        playSound(gameData->soundManager, MusicEdifice);

        while (gameData->screen->run) {
            //Get start time
            Uint32 time1 = SDL_GetTicks();

            //Control what the game is rendering
            renderCurrentMenu(gameData);

            SDL_SetRenderDrawColor(gameData->screen->renderer, 150, 255, 248, 255);
            SDL_RenderPresent(gameData->screen->renderer);

            SDL_Rect srcRect = {896, 64, 64, 64};
            SDL_Rect desRect = {0, 0, gameData->screen->xRez, gameData->screen->yRez};
            SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet, &srcRect, &desRect);



            //Handle game inputs
            handleInput(gameData);

            //end frame render time tracker
            Uint32 time2 = SDL_GetTicks();
            gameData->screen->frameRenderTime = time2 - time1;
            //Update current frame
            gameData->screen->currentFrame++;
        }


        if (gameData->world != NULL) {
            saveWorldToFile(gameData->world);
        }
    }
    return 0;
}
