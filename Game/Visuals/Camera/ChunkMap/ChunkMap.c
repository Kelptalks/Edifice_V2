//
// Created by Spencer on 6/12/2024.
//

#include "ChunkMap.h"
#include "../../../Debuging/Test_Main.h"

//Key management
//return a long key of the bit packed cords;
unsigned long createKey(int x, int y) {
    return ((unsigned long)x << 32) | (unsigned long)(y & 0xFFFFFFFF);
}
//Create a hash of the key
unsigned int getHash(unsigned long key, int map_size) {
    const unsigned long prime = 0x9E3779B9;  // A large prime number
    unsigned long hash_value = key * prime;
    return (unsigned int)(hash_value % map_size);
}

unsigned int getKey(int x, int y, int mapSize){
    return getHash(createKey(x, y), mapSize);
}

struct ChunkMap* createChunkMap(int size){
    //Malloc the chunkMapStruct
    struct ChunkMap* chunkMap = malloc(sizeof(struct ChunkMap));
    if (chunkMap == NULL){
        reportBug("Failed to malloc chunk map \n");
        return NULL;
    }

    //Set size
    chunkMap->size = size;

    //Create chunk node array
    chunkMap->nodes = calloc(size,sizeof(struct ChunkLinkListNode*));
    if (chunkMap->nodes == NULL){
        reportBug("Failed to calloc chunkmap node array \n");
        return NULL;
    }

    return chunkMap;
}

struct CastedChunk* getChunkFromMap(struct ChunkMap* chunkMap, int x, int y){
    unsigned int key = getKey(x, y, chunkMap->size);
    struct ChunkLinkListNode* chunkLinkListNode = chunkMap->nodes[key];

    while (chunkLinkListNode != NULL){
        //Check if is chunk cords
        if (chunkLinkListNode->x == x && chunkLinkListNode->y == y){
            reportBug("Test1\n");
            return chunkLinkListNode->castedChunk;
        }
        else{
            chunkLinkListNode = chunkLinkListNode->nextNode;
        }
    }
    reportBug("Test2\n");
    return NULL;
}

void addChunkToMap(struct ChunkMap* chunkMap, struct CastedChunk* castedChunk){
    unsigned int key = getKey(castedChunk->isoX, castedChunk->isoY, chunkMap->size);
    struct ChunkLinkListNode* chunkLinkListNode = chunkMap->nodes[key];
    struct ChunkLinkListNode* NewChunkLinkListNode = createChunkLinkListNode(castedChunk->isoX, castedChunk->isoY, key);


    //If node list is empty
    if (chunkLinkListNode == NULL){
        chunkMap->nodes[key] = NewChunkLinkListNode;
    }
    //Append to the end of the other node/nodes
    else{
        while(chunkLinkListNode->nextNode != NULL){
            chunkLinkListNode = chunkLinkListNode->nextNode;
        }
        chunkLinkListNode->nextNode = NewChunkLinkListNode;
    }
}

void removeChunkFromMap(struct ChunkMap* chunkMap, int x, int y){
    unsigned int key = getKey(x, y, chunkMap->size);
    struct ChunkLinkListNode* chunkLinkListNode = chunkMap->nodes[key];


}