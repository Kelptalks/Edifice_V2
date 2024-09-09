//
// Created by Spencer on 8/27/2024.
//

#include "../WorldChunk/WorldChunk.h"

#ifndef EDIFICE_WORLDCHUNKHASHMAP_H
#define EDIFICE_WORLDCHUNKHASHMAP_H

struct WorldChunkHashMapNode{
    struct WorldChunk* worldChunk;
    struct WorldChunkHashMapNode* nextNode;
};

struct WorldChunkHashMapNode* createWorldChunkHashMapNode();

struct WorldChunkHashMapNodePool{
    struct WorldChunkHashMapNode** freeNodes;

    int maxNodes;
    int freeNodesCount;
};

struct WorldChunkHashMapNodePool* createWorldChunkHashMapNodePool(int maxSize);

struct WorldChunkHashMap{
    struct WorldChunkHashMapNodePool* worldChunkHashMapNodePool;

    int hashArraySize;
    struct WorldChunkHashMapNode** worldChunkHashArray;
};

void addWorldChunkToMap();

struct WorldChunk* getWorldChunkFromMap();

void testWorldChunkHashMap();
#endif //EDIFICE_WORLDCHUNKHASHMAP_H
