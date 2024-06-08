//
// Created by Spencer on 5/6/2024.
//


#include "CameraData.h"
#include "Rendering/CastedBlockManager/CastedBlockManager.h"
#include "../../Debuging/Test_Main.h"
#include "../../World/Octree/KeyMod.h"
#include "../InMenuWindow/InMenuWindow.h"

struct CameraData* createCameraData(SDL_Renderer* renderer){
    struct CameraData* cameraData = malloc(sizeof(struct CameraData));
    if (cameraData == NULL){
        return NULL;
    }

    cameraData->xRenderingOffset = 0;
    cameraData->yRenderingOffset = 0;

    //The scale the camera should render
    cameraData->baseBlockScale = 64;
    cameraData->renderScale = 64;

    //How many chunks will generate
    cameraData->viewDistance = 16;

    //Max 512
    cameraData->chunksScale = 16;
    cameraData->chunkPixelScale = cameraData->baseBlockScale * cameraData->chunksScale;

    //Key the camera renderers from
    cameraData->key = modKey(0, 300, 300, 300, 0);

    //Create viewport
    reportBug(" - Creating CastedPool\n");
    cameraData->castedPool = createCastedPool(cameraData, renderer);

    //Create inMenuWindow
    cameraData->inMenuWindow = createInMenuWindow(50, 50, 1280, 720);

    return cameraData;
}