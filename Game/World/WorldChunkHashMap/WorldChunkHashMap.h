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

struct WorldChunkHashMap* createWorldChunkHashMap(int maxChunks);

void addWorldChunkToHashMap(struct WorldChunkHashMap* worldChunkHashMap, struct WorldChunk* worldChunk);

struct WorldChunk* getWordChunkFromMap(struct WorldChunkHashMap* hashMap, int xCor, int yCor, int zCor);

void freeWorldHashMap(struct WorldChunkHashMap* worldChunkHashMap);

void testWorldChunkHashMap();
#endif //EDIFICE_WORLDCHUNKHASHMAP_H
