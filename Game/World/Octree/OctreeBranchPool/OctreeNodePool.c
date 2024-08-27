//
// Created by Spencer on 8/27/2024.
//

#include <malloc.h>
#include "OctreeNodePool.h"
#include "../../../Debuging/Test_Main.h"

struct OctreeNodePool* CreateOctreeNodePool(int maxNodes){
    struct OctreeNodePool* octreeNodePool = malloc(sizeof (struct OctreeNodePool));
    if (octreeNodePool == NULL){
        reportBug("Failed to create branchPool\n");
        return NULL;
    }

    octreeNodePool->maxNodes = maxNodes;
    octreeNodePool->freeNodes = malloc(sizeof(struct OctreeNode*) * octreeNodePool->maxNodes);
    if (octreeNodePool->freeNodes == NULL){
        reportBug("Failed to create free branch pool array\n");
        return NULL;
    }

    octreeNodePool->totalFreeNodes = 0;

    return octreeNodePool;
}
