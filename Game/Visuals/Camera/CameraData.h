//
// Created by Spencer on 5/6/2024.
//

#ifndef EDIFICE_CAMERADATA_H
#define EDIFICE_CAMERADATA_H

#include "SDL.h"
#include "Rendering/CastedBlockManager/CastedBlockManager.h"

struct CameraData{
    //Drawing location
    float xRenderingOffset;
    float yRenderingOffset;

    //Camera world location
    unsigned long key;

    //Dimensions
    int baseBlockScale;
    int viewDistance;
    int chunksScale;
    int chunkPixelScale;
    float renderScale;

    //Chunk management
    struct CastedPool* castedPool;
    int xIsoCamCenter;
    int yIsoCamCenter;

    //World
    struct Octree* octree;

    //In MenuWindow
    struct InMenuWindow* inMenuWindow;
    enum Block blockSelected;
};

struct CameraData* createCameraData(SDL_Renderer* renderer);


#endif //EDIFICE_CAMERADATA_H
