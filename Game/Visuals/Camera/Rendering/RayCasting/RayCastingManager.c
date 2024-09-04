//
// Created by Spencer on 5/14/2024.
//

#include <pthread.h>
#include "stdlib.h"
#include "CastingThread/castingThread.h"
#include "../CastedBlockManager/CastedBlockManager.h"
#include "RayCaster.h"
#include "../../../../Debuging/Test_Main.h"
#include "RayCastingManager.h"

struct RayCastingData* createRayCastingData(struct CameraData* cameraData){
    struct RayCastingData* rayCastingData = malloc(sizeof (struct RayCastingData));
    if (rayCastingData == NULL){
        reportBug("Failed to create rayCasting Data\n");
        return NULL;
    }

    rayCastingData->leftOrder[0] = 0;
    rayCastingData->leftOrder[1] = 1;
    rayCastingData->leftOrder[2] = 2;

    rayCastingData->rightOrder[1] = 0;
    rayCastingData->rightOrder[0] = 1;
    rayCastingData->rightOrder[2] = 2;

    return rayCastingData;
}

void updateCastingDirectionOrder(struct CameraData* cameraData){
    struct RayCastingData* rayCastingData = cameraData->rayCastingData;
    int* leftOrder = rayCastingData->leftOrder;
    int* rightOrder = rayCastingData->rightOrder;

    if (cameraData->direction == North){
        rayCastingData->leftOrder[0] = 2;
        rayCastingData->leftOrder[1] = 1;
        rayCastingData->leftOrder[2] = 0;

        rayCastingData->rightOrder[1] = 0;
        rayCastingData->rightOrder[0] = 1;
        rayCastingData->rightOrder[2] = 2;
    }
    else if (cameraData->direction == East){
        rayCastingData->leftOrder[0] = 2;
        rayCastingData->leftOrder[1] = 1;
        rayCastingData->leftOrder[2] = 0;

        rayCastingData->rightOrder[1] = 0;
        rayCastingData->rightOrder[0] = 1;
        rayCastingData->rightOrder[2] = 2;
    }
    else if (cameraData->direction == South){
        rayCastingData->leftOrder[0] = 2;
        rayCastingData->leftOrder[1] = 1;
        rayCastingData->leftOrder[2] = 0;

        rayCastingData->rightOrder[1] = 0;
        rayCastingData->rightOrder[0] = 1;
        rayCastingData->rightOrder[2] = 2;
    }
    else if (cameraData->direction == West){
        rayCastingData->leftOrder[0] = 2;
        rayCastingData->leftOrder[1] = 1;
        rayCastingData->leftOrder[2] = 0;

        rayCastingData->rightOrder[1] = 0;
        rayCastingData->rightOrder[0] = 1;
        rayCastingData->rightOrder[2] = 2;
    }
}

void rayCastBlock(struct CameraData* cameraData, struct CastedBlock* castedBlock, struct Octree* octree){
    clearTextureList(castedBlock->leftTextureList);
    clearTextureList(castedBlock->rightTextureList);

    castedBlock->leftShader = Empty;
    castedBlock->rightShader = Empty;

    //castLeftTriangle(cameraData, castedBlock, octree);
    //castRightTriangle(cameraData, castedBlock, octree);

    castBlock(cameraData, castedBlock);


    if (cameraData->direction != East) {
        castLeftShadow(cameraData, castedBlock, octree);
        castRightShadow(cameraData, castedBlock, octree);
    }
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