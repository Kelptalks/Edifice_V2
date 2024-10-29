//
// Created by Spencer on 10/29/2024.
//

#include "GPUWorldData.h"

#include <stdlib.h>

#include "../../../../../../../Debuging/Test_Main.h"
#include "../../../../../../../World/Octree/Octree.h"


struct ChunkGPUHashTable* createChunkGPUHashTable(int maxChunks) {
    struct ChunkGPUHashTable* chunkGpuHashTable = malloc(sizeof(struct ChunkGPUHashTable));
    if (chunkGpuHashTable == NULL) {
        reportBug("Failed to malloc chunk GPU hash Table\n");
        return NULL;
    }

    chunkGpuHashTable->chainLength = maxChunks * 4;
    chunkGpuHashTable->chainDepth0 = calloc(chunkGpuHashTable->chainLength, sizeof(int));
    chunkGpuHashTable->chainDepth1 = calloc(chunkGpuHashTable->chainLength, sizeof(int));
    chunkGpuHashTable->chainDepth2 = calloc(chunkGpuHashTable->chainLength, sizeof(int));
    chunkGpuHashTable->chainDepth3 = calloc(chunkGpuHashTable->chainLength, sizeof(int));
    chunkGpuHashTable->chainDepth4 = calloc(chunkGpuHashTable->chainLength, sizeof(int));

    return chunkGpuHashTable;
}


struct WorldDataToSend* createWorldDataToSend(const int maxChunks) {
    struct WorldDataToSend* worldDataToSend = malloc(sizeof(struct WorldDataToSend));
    if (worldDataToSend == NULL) {
        reportBug("Failed to malloc worldDataToSend\n");
        return NULL;
    }


    worldDataToSend->maxChunk = maxChunks;
    worldDataToSend->octreeLinearArraySize = getOctreeDataArrayLength(6);

    //Alocate octree Data;
    worldDataToSend->branchData = calloc(maxChunks * worldDataToSend->octreeLinearArraySize, sizeof(unsigned int));
    worldDataToSend->nodeData = calloc(maxChunks * worldDataToSend->octreeLinearArraySize, sizeof(unsigned int));

    worldDataToSend->chunkXCords = calloc(maxChunks, sizeof(int));
    worldDataToSend->chunkYCords = calloc(maxChunks, sizeof(int));
    worldDataToSend->chunkZCords = calloc(maxChunks, sizeof(int));

    return worldDataToSend;
}

void addChunkToGPUHashTable(struct ChunkGPUHashTable* chunkGpuHashTable, struct WorldDataToSend* worldDataToSend, struct CastedChunk* castedChunk) {
    

}
