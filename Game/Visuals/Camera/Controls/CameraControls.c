//
// Created by Spencer on 6/7/2024.
//

#include "SDL.h"
#include "../../../GameData.h"
#include "../CameraData.h"
#include "../../../World/World.h"
#include "../IsoCordTool/IsoCordManager.h"
#include "../../../PlayerData/PlayerData.h"
#include "../Camera.h"
#include "../Rendering/CastedBlockManager/CastedBlockHighLighter/CastedBlockHighLighter.h"
#include <math.h>

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
    struct CameraData* cameraData = gameData->cameraData;
    struct CastedBlock* castedBlock = getCastedBlockAtMouseCords(cameraData, xMouseCor, yMouseCor);


    //Unpack the casted block data.
    int castedBlockCamWorldX = castedBlock->worldX;
    int castedBlockCamWorldY = castedBlock->worldY;
    int castedBlockCamWorldZ = castedBlock->worldZ;

    struct World *world = cameraData->world;
    short block = 0;

    int detailedXIso; int detailedYIso;
    screenToIso(cameraData->renderScale/4, xMouseCor - cameraData->xRenderingOffset, yMouseCor - cameraData->yRenderingOffset, &detailedXIso, &detailedYIso);
    int keyModOrder[3] = {0, 1, 2};
    bool leftSide = true;
    if (detailedYIso % 2 == 0){
        leftSide = false;
    }

    if (leftSide) {
        for (int drawDistance = 300; drawDistance > 0; drawDistance--) {
            castedBlockCamWorldX = castedBlockCamWorldX - cameraData->xDirection;
            block = getBlockAtWorldCor(world, castedBlockCamWorldX, castedBlockCamWorldY, castedBlockCamWorldZ);
            if (!isTransparent(block)) {
                setBlockAtWorldCor(world, castedBlockCamWorldX + cameraData->xDirection, castedBlockCamWorldY, castedBlockCamWorldZ, gameData->playerData->block);
                break;
            }

            castedBlockCamWorldY = castedBlockCamWorldY - cameraData->yDirection;
            block = getBlockAtWorldCor(world, castedBlockCamWorldX, castedBlockCamWorldY, castedBlockCamWorldZ);
            if (!isTransparent(block)) {
                setBlockAtWorldCor(world, castedBlockCamWorldX, castedBlockCamWorldY + cameraData->yDirection, castedBlockCamWorldZ, gameData->playerData->block);
                break;
            }

            castedBlockCamWorldZ = castedBlockCamWorldZ - 1;
            block = getBlockAtWorldCor(world, castedBlockCamWorldX, castedBlockCamWorldY, castedBlockCamWorldZ);
            if (!isTransparent(block)) {
                setBlockAtWorldCor(world, castedBlockCamWorldX, castedBlockCamWorldY, castedBlockCamWorldZ + 1, gameData->playerData->block);
                break;
            }
        }
    }
    else{
        for (int drawDistance = 300; drawDistance > 0; drawDistance--) {
            castedBlockCamWorldY = castedBlockCamWorldY - cameraData->yDirection;
            block = getBlockAtWorldCor(world, castedBlockCamWorldX, castedBlockCamWorldY, castedBlockCamWorldZ);
            if (!isTransparent(block)) {
                setBlockAtWorldCor(world, castedBlockCamWorldX, castedBlockCamWorldY + cameraData->yDirection, castedBlockCamWorldZ, gameData->playerData->block);
                break;
            }

            castedBlockCamWorldX = castedBlockCamWorldX - cameraData->xDirection;
            block = getBlockAtWorldCor(world, castedBlockCamWorldX, castedBlockCamWorldY, castedBlockCamWorldZ);
            if (!isTransparent(block)) {
                setBlockAtWorldCor(world, castedBlockCamWorldX + cameraData->xDirection, castedBlockCamWorldY, castedBlockCamWorldZ, gameData->playerData->block);
                break;
            }

            castedBlockCamWorldZ = castedBlockCamWorldZ - 1;
            block = getBlockAtWorldCor(world, castedBlockCamWorldX, castedBlockCamWorldY, castedBlockCamWorldZ);
            if (!isTransparent(block)) {
                setBlockAtWorldCor(world, castedBlockCamWorldX, castedBlockCamWorldY, castedBlockCamWorldZ + 1, gameData->playerData->block);
                break;
            }
        }
    }
    playSound(gameData->soundManager, getBlockPlaceSound(gameData->playerData->block));
}

void mouseBreakBlock(struct GameData* gameData, int xMouseCor, int yMouseCor, SDL_Event event){
    struct CameraData* cameraData = gameData->cameraData;
    struct CastedBlock* castedBlock = getCastedBlockAtMouseCords(cameraData, xMouseCor, yMouseCor);

    if (castedBlock == NULL){
        return;
    }

    struct World *world = cameraData->world;
    short block = 0;

    int detailedXIso; int detailedYIso;
    screenToIso(cameraData->renderScale/4, xMouseCor - cameraData->xRenderingOffset, yMouseCor - cameraData->yRenderingOffset, &detailedXIso, &detailedYIso);
    int keyModOrder[3] = {0, 1, 2};
    bool leftSide = true;
    if (detailedYIso % 2 == 0){
        leftSide = false;
    }

    if (leftSide) {
        if (castedBlock->struckLeftTranslucent){
            setBlockAtWorldCor(world, castedBlock->worldLeftTranslucentX, castedBlock->worldLeftTranslucentY, castedBlock->worldLeftTranslucentZ, Air);
        }
        else{
            setBlockAtWorldCor(world, castedBlock->worldLeftBlockX, castedBlock->worldLeftBlockY, castedBlock->worldLeftBlockZ, Air);
        }
    }
    else{
        if (castedBlock->struckRightTranslucent){
            setBlockAtWorldCor(world, castedBlock->worldRightTranslucentX, castedBlock->worldRightTranslucentY, castedBlock->worldRightTranslucentZ, Air);
        }
        else{
            setBlockAtWorldCor(world, castedBlock->worldRightBlockX, castedBlock->worldRightBlockY, castedBlock->worldRightBlockZ, Air);
        }
    }
    playSound(gameData->soundManager, getBlockRemoveSound(gameData->playerData->block));
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
    float xCamIsoChange = gameData->cameraData->xIsoCamCenter;
    float yCamIsoChange = gameData->cameraData->yIsoCamCenter;

    if (event.wheel.y > 0) {
        //Zoom in
        //scale2 = round(gameData->cameraData->renderScale / 0.90 / 8) * 8;
        scale2 = gameData->cameraData->renderScale / 0.95;
        gameData->cameraData->renderScale = scale2;
    }
    if (event.wheel.y < 0) {
        //Zoom out
        //scale2 = round(gameData->cameraData->renderScale * 0.90 / 8) * 8;
        scale2 = gameData->cameraData->renderScale * 0.95;
        gameData->cameraData->renderScale = scale2;
    }

    //Recenter camera after zoom
    updateCameraCords(gameData);
    xCamIsoChange = xCamIsoChange - gameData->cameraData->xIsoCamCenter;
    yCamIsoChange = yCamIsoChange - gameData->cameraData->yIsoCamCenter;

    int isoX; int isoY;
    floatIsoToScreen(scale2, xCamIsoChange, yCamIsoChange,&isoX, &isoY);


    gameData->cameraData->xRenderingOffset -= isoX;
    gameData->cameraData->yRenderingOffset -= isoY;



}

void tickCamera(struct GameData* gameData){
    struct CameraData* cameraData = gameData->cameraData;

    cameraData->xRenderingOffset += cameraData->camVelX;
    cameraData->yRenderingOffset += cameraData->camVelY;

    cameraData->camVelX = cameraData->camVelX/cameraData->camVelResist;
    cameraData->camVelY = cameraData->camVelY/cameraData->camVelResist;

}

void keyboardCamMovement(struct GameData* gameData, SDL_Event event){
    //Camera Movement Controls
    float camSpeed = 10;
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);
    struct CameraData* cameraData = gameData->cameraData;
    // Check each key of interest and update accordingly
    gameData->playerData->sprinting = false;


    if (keystate[SDL_SCANCODE_W]) {
        cameraData->camVelY += 5.0;
    }
    if (keystate[SDL_SCANCODE_S]) {
        cameraData->camVelY -= 5.0;
    }
    if (keystate[SDL_SCANCODE_A]) {
        cameraData->camVelX += 5.0;
    }
    if (keystate[SDL_SCANCODE_D]) {
        cameraData->camVelX -= 5.0;
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

    //Mouse input Controls
    int xCor, yCor;
    SDL_GetMouseState(&xCor, &yCor);

    mouseHighlight(gameData, xCor, yCor);
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

    //If right place block
    if(event.button.button == SDL_BUTTON_MIDDLE){
        mouseCamMovement(gameData, xCor, yCor);
    }

    keyboardCamMovement(gameData, event);

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_TAB :
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
                gameData->debugMenu->tikDataVisible = !gameData->debugMenu->tikDataVisible;
                break;
            case SDLK_F5 :
                gameData->debugMenu->frameDataVisible = !gameData->debugMenu->frameDataVisible;
                break;
            case SDLK_F6 :
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