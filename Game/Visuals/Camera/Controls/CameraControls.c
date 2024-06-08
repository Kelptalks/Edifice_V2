//
// Created by Spencer on 6/7/2024.
//

#include "SDL.h"
#include "../../../GameData.h"
#include "../CameraData.h"
#include "../../../World/World.h"
#include "../../../World/Octree/KeyMod.h"
#include "../IsoCordTool/IsoCordManager.h"
#include "../../../World/Octree/Octree.h"
#include "../../../World/Octree/OctreeNode.h"
#include "../../../Debuging/Test_Main.h"
#include "../../../Visuals/InMenuWindow/InMenuWindow.h"

void mouseBreakBlock(struct GameData* gameData, int xMouseCor, int yMouseCor, SDL_Event event){
    //Cords calculations
    int *cords = screenToIso(gameData->cameraData->renderScale/2, xMouseCor - gameData->cameraData->xRenderingOffset, yMouseCor - gameData->cameraData->yRenderingOffset);
    int xIso = cords[0];
    int yIso = cords[1];
    free(cords);

    //Identifie block from collection
    struct CastedChunk* castedChunk = &gameData->cameraData->castedPool->castedChunks[xIso / gameData->cameraData->chunksScale][yIso / gameData->cameraData->chunksScale];
    struct CastedBlock* castedBlock = &castedChunk->castedBlocks[xIso % gameData->cameraData->chunksScale][yIso % gameData->cameraData->chunksScale];
    
    //Use blocks cam key to rayCast and break block
    if (xIso > 0 && yIso > 0) {
        unsigned long key = castedBlock->camKey;
        struct Octree* octree = gameData->world->octree;
        short block = 0;
        //Cast ray from camera to block
        int keyModOrder[3] = {0, 1, 2}; //Order x--, y-- ,z--
        for (int drawDistance = 300; drawDistance > 0; drawDistance--){
            for (int axis = 0; axis < 3; axis++) {
                key = modAxis(key, -1, keyModOrder[axis], 0);
                block = getOctreeKeyVal(octree->root, key, octree->RootDepth);
                if (!isTransparent(block)){
                    setOctreeKeyValue(octree->root, key, octree->RootDepth, 0);
                    drawDistance = 0;
                }
            }
        }
    }
    //ReRender modified chunk;
    castedChunk->rayCast = false;
    castedChunk->textured = false;

}

void cameraControlInput(struct GameData* gameData, SDL_Event event){
    //InMenuWindow Controls
    bool mouseOnInMenuWindow = false;
    if (gameData->cameraData->inMenuWindow->visible){
        mouseOnInMenuWindow = InMenuWindowControls(gameData, gameData->cameraData->inMenuWindow, event);
    }

    //Mouse input Controls
    int xCor, yCor;
    SDL_GetMouseState(&xCor, &yCor);

    if (!mouseOnInMenuWindow) {
        //Convert to iso cords
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            mouseBreakBlock(gameData, xCor, yCor, event);
        }
    }

    float camSpeed = 1;
    float timeAdjustedCamChange = camSpeed * gameData->screen->frameRenderTime;

    //Camera Movement Controls
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);
    // Check each key of interest and update accordingly
    if (keystate[SDL_SCANCODE_W]) {
        gameData->cameraData->yRenderingOffset += timeAdjustedCamChange;  // Move camera up
    }
    if (keystate[SDL_SCANCODE_S]) {
        gameData->cameraData->yRenderingOffset -= timeAdjustedCamChange;  // Move camera down
    }
    if (keystate[SDL_SCANCODE_A]) {
        gameData->cameraData->xRenderingOffset += timeAdjustedCamChange;  // Move camera left
    }
    if (keystate[SDL_SCANCODE_D]) {
        gameData->cameraData->xRenderingOffset -= timeAdjustedCamChange;  // Move camera right
    }

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_TAB :
                gameData->cameraData->inMenuWindow->visible = !gameData->cameraData->inMenuWindow->visible;
                break;
        }
    }

    //Mouse location Debug menu update
    int *cords = screenToIso(gameData->cameraData->renderScale/2, xCor - gameData->cameraData->xRenderingOffset, yCor - gameData->cameraData->yRenderingOffset);
    gameData->debugMenu->xBlockSelectedCor = cords[0];
    gameData->debugMenu->yBlockSelectedCor = cords[1];
    free(cords);


}