//
// Created by Spencer on 5/6/2024.
//


#include "CameraData.h"
#include "Rendering/CastedBlockManager/CastedBlockManager.h"
#include "../../Debuging/Test_Main.h"
#include "../../World/Octree/KeyMod.h"
#include "../InMenuWindow/InMenuWindow.h"
#include "Camera.h"
#include "Rendering/RayCasting/RayCastingManager.h"

struct CameraData* createCameraData(SDL_Renderer* renderer){
    struct CameraData* cameraData = calloc(1, sizeof(struct CameraData));
    if (cameraData == NULL){
        return NULL;
    }

    //cameraOrientation
    cameraData->direction = North;
    cameraData->xDirection = 1;
    cameraData->yDirection = 1;
    cameraData->rayCastingData = createRayCastingData(cameraData);
    setDirection(cameraData, North);

    //The scale the camera should render
    cameraData->baseBlockScale = 64;
    cameraData->renderScale = 64;
    cameraData->xChunkScaledTextureRez = 0;
    cameraData->yChunkScaledTextureRez = 0;

    //How many chunks will generate
    cameraData->viewDistance = 16;
    cameraData->mouseUpdateDistance = 2;

    //Max 512
    cameraData->chunksScale = 8;
    cameraData->chunkPixelScale = cameraData->baseBlockScale * cameraData->chunksScale;

    //Offset for drawing the screen and shifting
    cameraData->xIsoCamCenter = 0;
    cameraData->yIsoCamCenter = 0;
    cameraData->xIsoChunkCamCenter = 0;
    cameraData->yIsoChunkCamCenter = 0;


    //Key the camera renderers from
    cameraData->key = modKey(0, 300, 300, 300, 0);

    //Create viewport
    reportBug(" - Creating CastedPool\n");
    cameraData->castedPool = createCastedPool(cameraData, renderer);

    //Create inMenuWindow
    cameraData->inMenuWindow = createInMenuWindow(0, 0, 1280, 720);

    return cameraData;
}

char* getDirectionString(enum Direction direction){
    if(direction == North){
        return "North";
    }
    if(direction == East){
        return "East";
    }
    if(direction == South){
        return "South";
    }
    if(direction == West){
        return "West";
    }
}