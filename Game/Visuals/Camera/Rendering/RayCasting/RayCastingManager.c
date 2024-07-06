//
// Created by Spencer on 5/14/2024.
//

#include <pthread.h>
#include "stdlib.h"
#include "CastingThread/castingThread.h"
#include "../CastedBlockManager/CastedBlockManager.h"
#include "RayCaster.h"
#include "../../../../Debuging/Test_Main.h"


void rayCastBlock(struct CameraData* cameraData, struct CastedBlock* castedBlock, struct Octree* octree){
    clearTextureList(castedBlock->leftTextureList);
    clearTextureList(castedBlock->rightTextureList);

    castedBlock->leftShader = Empty;
    castedBlock->rightShader = Empty;

    castLeftTriangle(cameraData, castedBlock, octree);
    castRightTriangle(cameraData, castedBlock, octree);
    castLeftShadow(cameraData, castedBlock, octree);
    castRightShadow(cameraData, castedBlock, octree);
}

void rayCastChunk(struct CameraData* cameraData, struct CastedChunk* castedChunk, struct Octree* octree){
    for (int x = 0; x < castedChunk->castedBlockCount; x++){
        rayCastBlock(cameraData, &castedChunk->castedBlocks[x], octree);
    }
}

void threadCastChunk(struct CameraData* cameraData, struct CastedChunk* castedChunk, struct Octree* octree){
    struct args* args = malloc(sizeof(struct args));
    args->cameraData = cameraData;
    args->castedChunk = castedChunk;
    args->octree = octree;
    pthread_create(NULL, NULL, castChunk, (void*)args);
}