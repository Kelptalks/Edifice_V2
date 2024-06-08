//
// Created by Spencer on 5/6/2024.
//

#ifndef EDIFICE_CAMERADATA_H
#define EDIFICE_CAMERADATA_H

#include "SDL.h"
#include "Rendering/CastedBlockManager/CastedBlockManager.h"

struct CameraData{
    //Drawing location
    int xRenderingOffset;
    int yRenderingOffset;

    //Camera world location
    unsigned long key;

    //Dimensions
    int viewDistance;
    int chunksScale;
    float renderScale;

    //Viewport
    struct CastedPool* castedPool;

    //World
    struct Octree* octree;

    //In MenuWindow
    struct InMenuWindow* inMenuWindow;
};

struct CameraData* createCameraData();


#endif //EDIFICE_CAMERADATA_H
