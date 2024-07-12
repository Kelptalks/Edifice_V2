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
#include "../../../PlayerData/PlayerData.h"
#include "../Camera.h"
#include "../Rendering/CastedBlockManager/CastedBlockHighLighter/CastedBlockHighLighter.h"

void mouseBreakBlock(struct GameData* gameData, int xMouseCor, int yMouseCor, SDL_Event event){
    //Cords calculations
    int *cords = screenToIso(gameData->cameraData->renderScale/2, xMouseCor - gameData->cameraData->xRenderingOffset, yMouseCor - gameData->cameraData->yRenderingOffset);
    int xIso = cords[0];
    int yIso = cords[1];
    free(cords);

    //Get casted block from cords
    struct CastedBlock* castedBlock = getCastedBlockAtCords(gameData->cameraData, xIso, yIso);
    if (castedBlock == NULL){
        return;
    }
    //Unpack the casted block data.
    unsigned long CastedBlockCamkey = castedBlock->camKey;
    struct Octree *octree = gameData->world->octree;
    short block = 0;

    //Use blocks cam CastedBlockCamkey to rayCast and break block
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


    highLightMouseCord(gameData, xIso, yIso, leftSide);

    //If button was pressed
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        //Left click to break block
        if (event.button.button == SDL_BUTTON_LEFT) {
            //Cast ray from camera to block
            for (int drawDistance = 300; drawDistance > 0; drawDistance--) {
                for (int axis = 0; axis < 3; axis++) {
                    int axisMod = 1;
                    if (keyModOrder[axis] == 0){
                        axisMod *= gameData->cameraData->xDirection;
                    }
                    if (keyModOrder[axis] == 1){
                        axisMod *= gameData->cameraData->yDirection;
                    }
                    CastedBlockCamkey = modAxis(CastedBlockCamkey, -1 * axisMod, keyModOrder[axis], 0);
                    block = getOctreeKeyVal(octree->root, CastedBlockCamkey, octree->RootDepth);
                    if (!isTransparent(block)) {
                        setOctreeKeyValue(octree->root, CastedBlockCamkey, octree->RootDepth, 0);
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
            //Cast ray from camera to block
            for (int drawDistance = 300; drawDistance > 0; drawDistance--) {
                for (int axis = 0; axis < 3; axis++) {
                    CastedBlockCamkey = modAxis(CastedBlockCamkey, -1, keyModOrder[axis], 0);
                    block = getOctreeKeyVal(octree->root, CastedBlockCamkey, octree->RootDepth);
                    if (!isTransparent(block)) {
                        //Mod CastedBlockCamkey based off axis of intercept
                        CastedBlockCamkey = modAxis(CastedBlockCamkey, 1, keyModOrder[axis], 0);

                        setOctreeKeyValue(octree->root, CastedBlockCamkey, octree->RootDepth,
                                          gameData->playerData->block);
                        drawDistance = 0;
                        break;
                    }
                }
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
        mouseBreakBlock(gameData, xCor, yCor, event);


    }

    float camSpeed = 10;
    float timeAdjustedCamChange = camSpeed * gameData->screen->frameRenderTime;

    //Camera Movement Controls
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);
    // Check each key of interest and update accordingly
    if (keystate[SDL_SCANCODE_W]) {
        gameData->cameraData->yRenderingOffset +=  camSpeed;  // Move camera up
    }
    if (keystate[SDL_SCANCODE_S]) {
        gameData->cameraData->yRenderingOffset -=  camSpeed;  // Move camera down
    }
    if (keystate[SDL_SCANCODE_A]) {
        gameData->cameraData->xRenderingOffset +=  camSpeed;  // Move camera left
    }
    if (keystate[SDL_SCANCODE_D]) {
        gameData->cameraData->xRenderingOffset -=  camSpeed;  // Move camera right
    }

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_TAB :
                gameData->cameraData->inMenuWindow->visible = !gameData->cameraData->inMenuWindow->visible;
                break;
            case SDLK_ESCAPE :
                gameData->screen->menuType = MainMenu;
                break;
            case SDLK_q :
                if (gameData->cameraData->direction < 3) {
                    int newDirection = gameData->cameraData->direction + 1;
                    setDirection(gameData->cameraData, newDirection);
                }
                else {
                    setDirection(gameData->cameraData, 0);
                }
                break;
            case SDLK_e :
                if (gameData->cameraData->direction > 0) {
                    int newDirection = gameData->cameraData->direction - 1;
                    setDirection(gameData->cameraData, newDirection);
                }
                else {
                    setDirection(gameData->cameraData, 3);
                }
                break;
            case SDLK_F3 :
                gameData->debugMenu->visible = !gameData->debugMenu->visible;
                break;
            case SDLK_F4 :
                gameData->debugMenu->chunkBoarders = !gameData->debugMenu->chunkBoarders;
                break;
        }
    }
    if (event.type == SDL_MOUSEWHEEL) {
        float scale2;
        int xCamIsoChange = gameData->cameraData->xIsoCamCenter;
        int yCamIsoChange = gameData->cameraData->yIsoCamCenter;

        if (event.wheel.y > 0) {
            //Zoom in
            scale2 = gameData->cameraData->renderScale / 0.95;
            gameData->cameraData->renderScale = scale2;
        }
        if (event.wheel.y < 0) {
            //Zoom out
            scale2 = gameData->cameraData->renderScale * 0.95;
            gameData->cameraData->renderScale = scale2;
        }

        updateCameraCords(gameData);

        xCamIsoChange = xCamIsoChange - gameData->cameraData->xIsoCamCenter;
        yCamIsoChange = yCamIsoChange - gameData->cameraData->yIsoCamCenter;

        int* cords = isoToScreen(scale2, xCamIsoChange, yCamIsoChange);
        gameData->cameraData->xRenderingOffset -= cords[0];
        gameData->cameraData->yRenderingOffset -= cords[1];
        free(cords);

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