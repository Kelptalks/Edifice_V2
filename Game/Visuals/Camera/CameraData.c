//
// Created by Spencer on 5/6/2024.
//


#include "CameraData.h"
#include "Rendering/CastedBlockManager/CastedBlockManager.h"
#include "../../Debuging/Test_Main.h"
#include "../../World/Octree/KeyMod.h"
#include "../InMenuWindow/InMenuWindow.h"

struct CameraData* createCameraData(SDL_Renderer* renderer){
    struct CameraData* cameraData = calloc(1, sizeof(struct CameraData));
    if (cameraData == NULL){
        return NULL;
    }
    //The current block selected for building
    cameraData->blockSelected == Grass;

    //The scale the camera should render
    cameraData->baseBlockScale = 64;
    cameraData->renderScale = 64;

    //How many chunks will generate
    cameraData->viewDistance = 10;

    //Max 512
    cameraData->chunksScale = 16;
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
    cameraData->inMenuWindow = createInMenuWindow(200, 200, 1280, 720);

    return cameraData;
}