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

        //Determine the side of the cast block
        int *detailedCords = screenToIso(gameData->cameraData->renderScale/4, xMouseCor - gameData->cameraData->xRenderingOffset, yMouseCor - gameData->cameraData->yRenderingOffset);

        int keyModOrder[3] = {0, 1, 2};
        bool leftSide;
        if (detailedCords[1]%2 == 0){
            leftSide = false;
            keyModOrder[0] = 1;
            keyModOrder[1] = 0;
            keyModOrder[2] = 2;
        }
        else{
            leftSide = true;
        }
        free(detailedCords);


        //Left click to break block
        if (event.button.button == SDL_BUTTON_LEFT) {
            //Remove block
            unsigned long key = castedBlock->camKey;
            struct Octree *octree = gameData->world->octree;
            short block = 0;
            //Cast ray from camera to block
            for (int drawDistance = 300; drawDistance > 0; drawDistance--) {
                for (int axis = 0; axis < 3; axis++) {
                    key = modAxis(key, -1, keyModOrder[axis], 0);
                    block = getOctreeKeyVal(octree->root, key, octree->RootDepth);
                    if (!isTransparent(block)) {
                        setOctreeKeyValue(octree->root, key, octree->RootDepth, 0);
                        drawDistance = 0;
                        break;
                    }
                }
            }

        }

        //Right click to place block
        else if (event.button.button == SDL_BUTTON_RIGHT) {
            //Play sound
            //playPlaceSound(gameData->screen->audio);

            unsigned long key = castedBlock->camKey;
            struct Octree *octree = gameData->world->octree;
            short block = 0;
            //Cast ray from camera to block
            for (int drawDistance = 300; drawDistance > 0; drawDistance--) {
                for (int axis = 0; axis < 3; axis++) {
                    key = modAxis(key, -1, keyModOrder[axis], 0);
                    block = getOctreeKeyVal(octree->root, key, octree->RootDepth);
                    if (!isTransparent(block)) {
                        //Mod key based off axis of intercept
                        key = modAxis(key, 1, keyModOrder[axis], 0);

                        setOctreeKeyValue(octree->root, key, octree->RootDepth, gameData->cameraData->blockSelected);
                        drawDistance = 0;
                        break;
                    }
                }
            }
        }
    }
    //ReRender modified chunk and the sounding ones;
    castedChunk->rayCast = false;
    castedChunk->textured = false;

    int xStart = (xIso / gameData->cameraData->chunksScale) - 1;
    int yStart = (xIso / gameData->cameraData->chunksScale) - 1;
    for (int x = 0; x < 3; x++){
        for (int y = 0; y < 3; y++) {
            if (&gameData->cameraData->castedPool->castedChunks[xStart + x][yStart + y] != NULL) {
                gameData->cameraData->castedPool->castedChunks[xStart + x][yStart + y].rayCast = false;
                gameData->cameraData->castedPool->castedChunks[xStart + x][yStart + y].textured = false;
            }
        }
    }

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
            case SDLK_e :
                gameData->cameraData->blockSelected++;
                if (gameData->cameraData->blockSelected > 35){
                    gameData->cameraData->blockSelected = 1;
                }
                break;
            case SDLK_q :
                gameData->cameraData->renderScale--;
                break;

        }
    }
    if (event.type == SDL_MOUSEWHEEL) {
        if (event.wheel.y > 0) {
            //Zoom in
            float scale2 = gameData->cameraData->renderScale / 0.95;
            gameData->cameraData->renderScale = scale2;
        }
        if (event.wheel.y < 0) {
            //Zoom out
            float scale2 = gameData->cameraData->renderScale * 0.95;
            gameData->cameraData->renderScale = scale2;
        }
    }

    //Mouse location Debug menu update
    gameData->debugMenu->xMouseCor = xCor;
    gameData->debugMenu->yMouseCor = yCor;

    int *cords = screenToIso(gameData->cameraData->renderScale/2, xCor - gameData->cameraData->xRenderingOffset, yCor - gameData->cameraData->yRenderingOffset);
    gameData->debugMenu->xBlockSelectedCor = cords[0];
    gameData->debugMenu->yBlockSelectedCor = cords[1];
    free(cords);

    int *detailedCords = screenToIso(gameData->cameraData->renderScale/4, xCor - gameData->cameraData->xRenderingOffset, yCor - gameData->cameraData->yRenderingOffset);
    if (detailedCords[1]%2 == 0){
        gameData->debugMenu->LeftSide = false;
    }
    else{
        gameData->debugMenu->LeftSide = true;
    }
    free(detailedCords);





}