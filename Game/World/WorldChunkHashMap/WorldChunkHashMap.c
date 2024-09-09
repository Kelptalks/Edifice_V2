//
// Created by Spencer on 8/27/2024.
//

#include <stdint.h>
#include <malloc.h>
#include "WorldChunkHashMap.h"
#include "../../Debuging/Test_Main.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * node pool management
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

struct WorldChunkHashMapNodePool* createWorldChunkHashMapNodePool(int maxSize){
    struct WorldChunkHashMapNodePool* nodePool = malloc(sizeof (struct WorldChunkHashMapNodePool));

    nodePool->maxNodes = maxSize;
    nodePool->freeNodesCount = 0;

    nodePool->freeNodes = malloc(sizeof (struct WorldChunkHashMapNode*) * maxSize);

    //Create nodes for the pool
    for (int i = 0; i < maxSize; i++){
        nodePool->freeNodes[i] = malloc(sizeof (struct WorldChunkHashMapNode));
        nodePool->freeNodes[i]->nextNode = NULL;
        nodePool->freeNodesCount++;
        if (nodePool->freeNodes[i] == NULL){
            reportBug("Failed to malloc free node for WorldChunkHashMap");
            return NULL;
        }
    }

    return nodePool;
}

struct WorldChunkHashMapNode* getNodeFromWorldChunkHashMapNodePool(struct WorldChunkHashMapNodePool* nodePool){
    nodePool->freeNodesCount--;
    return nodePool->freeNodes[nodePool->freeNodesCount];
}

void freeNodeToWorldChunkHashMapNodePool(struct WorldChunkHashMapNodePool* nodePool, struct WorldChunkHashMapNode* node){
    nodePool->freeNodes[nodePool->freeNodesCount] = node;
    nodePool->freeNodesCount++;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * key management
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

uint64_t hashCords(int x, int y, int z) {
    const int64_t shift = 1 << 30; // Shift by 2^30 to ensure positive values
    const uint64_t prime1 = 73856093;
    const uint64_t prime2 = 19349663;
    const uint64_t prime3 = 83492791;
    return (uint64_t)((x + shift) * prime1) ^ (uint64_t)((y + shift) * prime2) ^ (uint64_t)((z + shift) * prime3);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * HashMap management
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

struct WorldChunkHashMap* createWorldChunkHashMap(int maxChunks){
    struct WorldChunkHashMap* worldChunkHashMap = malloc(sizeof (struct WorldChunkHashMap));
    if (worldChunkHashMap == NULL){
        reportBug("failed to malloc worldChunkHashMap\n");
        return NULL;
    }

    worldChunkHashMap->hashArraySize = maxChunks;

    //Create worldChunkHashMapNodePool
    worldChunkHashMap->worldChunkHashMapNodePool = createWorldChunkHashMapNodePool(maxChunks);
    if (worldChunkHashMap->worldChunkHashMapNodePool == NULL){
        reportBug("failed to create worldChunkHashMapNodePool\n");
        return NULL;
    }

    worldChunkHashMap->worldChunkHashArray = calloc(sizeof (struct WorldChunkHashMapNode*), maxChunks);
    if (worldChunkHashMap->worldChunkHashArray == NULL){
        reportBug("failed to malloc worldChunkHashArray \n");
        return NULL;
    }

    return worldChunkHashMap;
}

void addWorldChunkToHashMap(struct WorldChunkHashMap* worldChunkHashMap, struct WorldChunk* worldChunk){
    //Setup New node
    struct WorldChunkHashMapNode* node = getNodeFromWorldChunkHashMapNodePool(worldChunkHashMap->worldChunkHashMapNodePool);
    node->worldChunk = worldChunk;

    //get key
    uint64_t key = hashCords(worldChunk->xCor, worldChunk->yCor, worldChunk->zCor);
    int index = key % worldChunkHashMap->hashArraySize;

    //If the hashmapArray is empty
    struct WorldChunkHashMapNode* currentNode = worldChunkHashMap->worldChunkHashArray[index];
    if (currentNode == NULL){
        worldChunkHashMap->worldChunkHashArray[index] = node;
    }

    //If the hashMapArray has node already add to the end of link list
    else{
        int x = 0;
        while (currentNode->nextNode != NULL){
            currentNode = currentNode->nextNode;
        }
        if (currentNode->nextNode == NULL){
            currentNode->nextNode = node;
        }
    }
}

struct WorldChunk* getWordChunkFromMap(struct WorldChunkHashMap* hashMap, int xCor, int yCor, int zCor){

    uint64_t key = hashCords(xCor, yCor, zCor);
    int index = key % hashMap->hashArraySize;

    struct WorldChunkHashMapNode* currentNode = hashMap->worldChunkHashArray[index];

    if (currentNode == NULL){
        return NULL;
    }
    else{
        while(currentNode != NULL){
            if (currentNode->worldChunk->xCor == xCor && currentNode->worldChunk->yCor == yCor && currentNode->worldChunk->zCor == zCor){
                return currentNode->worldChunk;
            }
            else{
                currentNode = currentNode->nextNode;
            }
        }
    }
    return NULL;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Testing
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

void testWorldChunkHashMap(){
    clearBugReports();

    struct WorldChunkHashMap* worldChunkHashMap = createWorldChunkHashMap(10000);


    for (int x = 0; x < 16; x++){
        for (int y = 0; y < 16; y++){
            for (int z = 0; z < 16; z++){
                int xCor = x * 15;
                int yCor = y * 12;
                int zCor = z * 3;
                struct WorldChunk* worldChunk = createWorldChunk(xCor, yCor, zCor);
                addWorldChunkToHashMap(worldChunkHashMap, worldChunk);
            }
        }
    }


    for (int x = 0; x < 16; x++){
        for (int y = 0; y < 16; y++){
            for (int z = 0; z < 16; z++){
                int xCor = x * 15;
                int yCor = y * 12;
                int zCor = z * 3;
                struct WorldChunk* worldChunk = getWordChunkFromMap(worldChunkHashMap, xCor, yCor, zCor);
                if (worldChunk == NULL){
                    reportBug("Failed test\n");
                }
            }
        }
    }
}