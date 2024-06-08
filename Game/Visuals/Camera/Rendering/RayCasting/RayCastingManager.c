//
// Created by Spencer on 5/14/2024.
//

#include <pthread.h>
#include "stdlib.h"
#include "CastingThread/castingThread.h"
#include "../CastedBlockManager/CastedBlockManager.h"
#include "RayCaster.h"


void rayCastBlock(struct CastedBlock* castedBlock, struct Octree* octree){
    clearTextureList(castedBlock->leftTextureList);
    clearTextureList(castedBlock->rightTextureList);
    castedBlock->leftShader = Empty;
    castedBlock->rightShader = Empty;

    castLeftTriangle(castedBlock, octree);
    castRightTriangle(castedBlock, octree);
    castLeftShadow(castedBlock, octree);
    castRightShadow(castedBlock, octree);
}

void rayCastChunk(struct CastedChunk* castedChunk, struct Octree* octree){
    for (int x = 0; x < castedChunk->scale; x++){
        for (int y = 0; y < castedChunk->scale; y++){
            rayCastBlock(&castedChunk->castedBlocks[x][y], octree);
        }
    }
}

void threadCastChunk(struct CastedChunk* castedChunk, struct Octree* octree){
    struct args* args = malloc(sizeof(struct args));
    args->castedChunk = castedChunk;
    args->octree = octree;
    pthread_create(NULL, NULL, castChunk, (void*)args);
}