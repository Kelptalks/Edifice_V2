//
// Created by Spencer on 6/7/2024.
//

#include "SDL.h"
#include "../../../GameData.h"
#include "../CameraData.h"
#include "../../../World/World.h"
#include "../../../World/Octree/Tools/KeyMod.h"
#include "../IsoCordTool/IsoCordManager.h"
#include "../../../World/Octree/Octree.h"
#include "../../../World/Octree/OctreeNode.h"
#include "../../../Debuging/Test_Main.h"
#include "../../../Visuals/InMenuWindow/InMenuWindow.h"
#include "../../../PlayerData/PlayerData.h"
#include "../Camera.h"
#include "../Rendering/CastedBlockManager/CastedBlockHighLighter/CastedBlockHighLighter.h"
#include "../../../Sound/SoundManager.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Getters
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

struct CastedBlock* getCastedBlockAtMouseCords(struct CameraData* cameraData, int xMouseCor, int yMouseCor){
    //Cords calculations
    int xIso; int yIso;
    screenToIso(cameraData->renderScale/2, xMouseCor - cameraData->xRenderingOffset, yMouseCor - cameraData->yRenderingOffset,&xIso, &yIso);

    //Get casted block from cords
    return getCastedBlockAtCords(cameraData, xIso, yIso);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Mouse inputs
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

void mouseHighlight(struct GameData* gameData, int xMouseCor, int yMouseCor){
    struct CameraData* cameraData = gameData->cameraData;

    int xIso;
    int yIso;
    screenToIso(cameraData->renderScale/2, xMouseCor - cameraData->xRenderingOffset, yMouseCor - cameraData->yRenderingOffset,  &xIso, &yIso);

    int detailedXIso; int detailedYIso;
    screenToIso(cameraData->renderScale/4, xMouseCor - cameraData->xRenderingOffset, yMouseCor - cameraData->yRenderingOffset, &detailedXIso, &detailedYIso);

    int keyModOrder[3] = {0, 1, 2};
    bool leftSide = true;
    if (detailedYIso % 2 == 0){
        leftSide = false;
    }
    highLightMouseCord(gameData, xIso, yIso, leftSide);
}

void mousePlaceBlock(struct GameData* gameData, int xMouseCor, int yMouseCor){

    //Get casted block from cords
    struct CastedBlock* castedBlock = getCastedBlockAtMouseCords(gameData->cameraData, xMouseCor, yMouseCor);
    if (castedBlock == NULL){
        return;
    }
    //Unpack the casted block data.
    unsigned long CastedBlockCamkey = castedBlock->camKey;
    struct Octree *octree = gameData->world->octree;
    short block = 0;

    //Use blocks cam CastedBlockCamkey to rayCast and break block
    //Determine the side of the cast block

    int detailedXIso; int detailedYIso;
    screenToIso(gameData->cameraData->renderScale/4, xMouseCor - gameData->cameraData->xRenderingOffset, yMouseCor - gameData->cameraData->yRenderingOffset, &detailedXIso, &detailedYIso);

    int keyModOrder[3] = {0, 1, 2};
    if (detailedYIso % 2 == 0){
        keyModOrder[0] = 1;
        keyModOrder[1] = 0;
        keyModOrder[2] = 2;
    }
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
                //Mod CastedBlockCamkey based off axis of intercept
                CastedBlockCamkey = modAxis(CastedBlockCamkey, 1 * axisMod, keyModOrder[axis], 0);


                //play the sound of the current block in hand
                playSound(gameData->soundManager, getBlockPlaceSound(gameData->playerData->block));

                //Set the block
                setOctreeKeyValue(octree->root, CastedBlockCamkey, octree->RootDepth,
                                  gameData->playerData->block);
                drawDistance = 0;
                break;
            }
        }
    }
}

void mouseBreakBlock(struct GameData* gameData, int xMouseCor, int yMouseCor, SDL_Event event){

    //Get casted block from cords
    struct CastedBlock* castedBlock = getCastedBlockAtMouseCords(gameData->cameraData, xMouseCor, yMouseCor);
    if (castedBlock == NULL){
        return;
    }
    //Unpack the casted block data.
    unsigned long CastedBlockCamkey = castedBlock->camKey;
    struct Octree *octree = gameData->world->octree;
    short block = 0;

    //Use blocks cam CastedBlockCamkey to rayCast and break block
    //Determine the side of the cast block
    int detailedXIso; int detailedYIso;
    screenToIso(gameData->cameraData->renderScale/4, xMouseCor - gameData->cameraData->xRenderingOffset, yMouseCor - gameData->cameraData->yRenderingOffset, &detailedXIso, &detailedYIso);

    int keyModOrder[3] = {0, 1, 2};
    if (detailedYIso % 2 == 0){
        keyModOrder[0] = 1;
        keyModOrder[1] = 0;
        keyModOrder[2] = 2;
    }
    //If button was pressed
    //Left click to break block
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

                //Get the block to play the correct sound
                enum Block blockType = getOctreeKeyVal(octree->root, CastedBlockCamkey, octree->RootDepth);
                playSound(gameData->soundManager, getBlockRemoveSound(blockType));

                setOctreeKeyValue(octree->root, CastedBlockCamkey, octree->RootDepth, 0);
                drawDistance = 0;
                break;
            }
        }
    }

    int xAxis = 0; int yAxis = 0; int zAxis = 0;
    getCords(CastedBlockCamkey, octree->RootDepth - 1, &xAxis, &yAxis, &zAxis);
    reportBug("block broken at(%i, %i, %i)\n", xAxis, yAxis, zAxis);

}

void mouseCamMovement(struct GameData* gameData, int currentMouseXCor, int currentMouseYCor){
    int lastMouseXcor = gameData->playerData->lastMouseXCor;
    int lastMouseYcor = gameData->playerData->lastMouseYCor;

    int xMouseCordChange = lastMouseXcor - currentMouseXCor;
    int yMouseCordChange = lastMouseYcor - currentMouseYCor;

    gameData->cameraData->xRenderingOffset -= xMouseCordChange;
    gameData->cameraData->yRenderingOffset -= yMouseCordChange;

}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Keyboard inputs
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

void updateZoomScale(struct GameData* gameData, SDL_Event event){
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

    //Recenter camera after zoom
    updateCameraCords(gameData);
    xCamIsoChange = xCamIsoChange - gameData->cameraData->xIsoCamCenter;
    yCamIsoChange = yCamIsoChange - gameData->cameraData->yIsoCamCenter;

    int isoX; int isoY;
    isoToScreen(scale2, xCamIsoChange, yCamIsoChange,&isoX, &isoY);


    gameData->cameraData->xRenderingOffset -= isoX;
    gameData->cameraData->yRenderingOffset -= isoY;



}

void keyboardCamMovement(struct CameraData* cameraData){
    //Camera Movement Controls
    float camSpeed = 10;
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);
    // Check each key of interest and update accordingly
    if (keystate[SDL_SCANCODE_W]) {
        cameraData->yRenderingOffset +=  camSpeed;  // Move camera up
    }
    if (keystate[SDL_SCANCODE_S]) {
        cameraData->yRenderingOffset -=  camSpeed;  // Move camera down
    }
    if (keystate[SDL_SCANCODE_A]) {
        cameraData->xRenderingOffset +=  camSpeed;  // Move camera left
    }
    if (keystate[SDL_SCANCODE_D]) {
        cameraData->xRenderingOffset -=  camSpeed;  // Move camera right
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Other
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

void updateDebugMenu(struct GameData* gameData, int xCor, int yCor){
    gameData->debugMenu->xMouseCor = xCor;
    gameData->debugMenu->yMouseCor = yCor;

    int isoX; int isoY;
    screenToIso(gameData->cameraData->renderScale/2, xCor - gameData->cameraData->xRenderingOffset, yCor - gameData->cameraData->yRenderingOffset, &isoX, &isoY);
    gameData->debugMenu->xBlockSelectedCor = isoX;
    gameData->debugMenu->yBlockSelectedCor = isoY;

    int detailedXIso; int detailedYIso;
    screenToIso(gameData->cameraData->renderScale/4, xCor - gameData->cameraData->xRenderingOffset, yCor - gameData->cameraData->yRenderingOffset, &detailedXIso, &detailedYIso);
    if (detailedYIso % 2 == 0){
        gameData->debugMenu->LeftSide = false;
    }
    else{
        gameData->debugMenu->LeftSide = true;
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Main input Manager
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

void cameraControlInput(struct GameData* gameData, SDL_Event event){
    //InMenuWindow Controls
    bool mouseOnInMenuWindow = false;
    if (gameData->cameraData->inMenuWindow->visible){
        mouseOnInMenuWindow = InMenuWindowControls(gameData, gameData->cameraData->inMenuWindow, event);
    }
    //Mouse input Controls
    int xCor, yCor;
    SDL_GetMouseState(&xCor, &yCor);

    mouseHighlight(gameData, xCor, yCor);
    if (!mouseOnInMenuWindow) {
        //Convert to iso cords
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            //If left break block
            if (event.button.button == SDL_BUTTON_LEFT){
                mouseBreakBlock(gameData, xCor, yCor, event);
            }
            //If right place block
            else if(event.button.button == SDL_BUTTON_RIGHT){
                mousePlaceBlock(gameData, xCor, yCor);
            }
        }
    }

    //If right place block
    if(event.button.button == SDL_BUTTON_MIDDLE){
        mouseCamMovement(gameData, xCor, yCor);
    }

    keyboardCamMovement(gameData->cameraData);

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_TAB :
                gameData->cameraData->inMenuWindow->visible = !gameData->cameraData->inMenuWindow->visible;
                break;
            case SDLK_ESCAPE :
                gameData->menuManger->currentMenuType = MainMenu;
                break;
            case SDLK_q :
                rotateCamLeft(gameData->cameraData);
                break;
            case SDLK_e :
                rotateCamRight(gameData->cameraData);
                break;
            case SDLK_F3 :
                toggleDebugMenu(gameData->debugMenu);
                break;
            case SDLK_F4 :
                toggleChunkBoarders(gameData->debugMenu);
                break;
        }
    }


    //If scroll wheel is used
    if (event.type == SDL_MOUSEWHEEL) {
        updateZoomScale(gameData, event);
    }

    //Update debug menu
    updateDebugMenu(gameData, xCor, yCor);
    gameData->playerData->lastMouseXCor = xCor;
    gameData->playerData->lastMouseYCor = yCor;


}