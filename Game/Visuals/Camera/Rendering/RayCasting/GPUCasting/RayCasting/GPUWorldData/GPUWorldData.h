//
// Created by Spencer on 10/29/2024.
//

#ifndef GPUWORLDDATA_H
#define GPUWORLDDATA_H

#include "../../../../CastedBlockManager/CastedBlockManager.h"

//Manage the chunk hash table
struct ChunkGPUHashTable {
    int chainLength;
    int* chainDepth0;
    int* chainDepth1;
    int* chainDepth2;
    int* chainDepth3;
    int* chainDepth4;
};

struct ChunkGPUHashTable* createChunkGPUHashTable(int maxChunks);

struct WorldDataToSend {
    int maxChunk;
    int octreeLinearArraySize;

    int* chunkXCords;
    int* chunkYCords;
    int* chunkZCords;

    int* branchData;
    int* nodeData;
};



#endif //GPUWORLDDATA_H
