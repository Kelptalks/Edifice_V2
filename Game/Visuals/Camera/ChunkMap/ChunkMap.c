//
// Created by Spencer on 6/12/2024.
//

#include <malloc.h>
#include "ChunkMap.h"
#include "../../../Debuging/Test_Main.h"
#include "../Rendering/CastedBlockManager/CastedBlockManager.h"
#include <stdint.h>

struct ChunkLinkListNode* createChunkLinkListNode(int64_t key, struct CastedChunk* castedChunk){
    struct ChunkLinkListNode* chunkLinkListNode = malloc(sizeof (struct ChunkLinkListNode));

    chunkLinkListNode->key = key;
    chunkLinkListNode->castedChunk = castedChunk;
    chunkLinkListNode->nextNode = NULL;

    return chunkLinkListNode;
}

struct ChunkMap* createChunkMap(int size){
    //Allocate the struct
    struct ChunkMap* chunkMap = malloc(sizeof(struct ChunkMap));
    if (chunkMap == NULL){
        reportBug("Failed to malloc chunkmap\n");
        return NULL;
    }

    //Set basic vars
    chunkMap->offset = 536870912;
    chunkMap->size = size;

    //Allocate array for chunks
    chunkMap->nodes = calloc(size, sizeof(struct ChunkLinkListNode));
    if (chunkMap->nodes == NULL){
        reportBug("failed to malloc chunkMap node array of size %i\n", size);
        return NULL;
    }

    return chunkMap;
}


int64_t encodeKey(int offset,int x, int y){
    int64_t key = ((int64_t)(x + offset) << 32) | (int64_t)(y + offset);
    return key;
}

void decodeKey(int64_t key, int offset, int* x, int* y){
    *x = (int)((key >> 32) - offset);
    *y = (int)((key & 0xFFFFFFFF) - offset);
}

void addChunkToMap(struct ChunkMap* chunkMap,struct CastedChunk* castedChunk){
    int64_t encodedKey = encodeKey(chunkMap->offset, castedChunk->isoX, castedChunk->isoY);
    int mapIndex = encodedKey % chunkMap->size;

    struct ChunkLinkListNode* chunkLinkListNode = chunkMap->nodes[mapIndex];

    // Check if list is empty and create if needed
    if (chunkLinkListNode == NULL){
        chunkMap->nodes[mapIndex] = createChunkLinkListNode(encodedKey, castedChunk);
    }
    //Find the end of the list and add to that
    else {
        while (chunkLinkListNode->nextNode != NULL) {
            chunkLinkListNode = chunkLinkListNode->nextNode;
        }
        chunkLinkListNode->nextNode = createChunkLinkListNode(encodedKey, castedChunk);
    }
}

struct CastedChunk* getChunkFromMap(struct ChunkMap* chunkMap, int xCor, int yCor){
    int64_t encodedKey = encodeKey(chunkMap->offset, xCor, yCor);

    //Index the correct link list from the hashtable
    int mapIndex = encodedKey % chunkMap->size;
    struct ChunkLinkListNode* chunkLinkListNode = chunkMap->nodes[mapIndex];

    while (chunkLinkListNode != NULL){
        if (encodedKey == chunkLinkListNode->key){
            return chunkLinkListNode->castedChunk;
        }
        chunkLinkListNode = chunkLinkListNode->nextNode;
    }

    return NULL;
}

void removeFromMap(struct ChunkMap* chunkMap, int xCor, int yCor){
    int64_t encodedKey = encodeKey(chunkMap->offset, xCor, yCor);

    //Index the correct link list from the hashtable
    int mapIndex = encodedKey % chunkMap->size;
    struct ChunkLinkListNode* CurrentChunkLinkListNode = chunkMap->nodes[mapIndex];
    struct ChunkLinkListNode* lastChunkLinkListNode = NULL;

    while (CurrentChunkLinkListNode != NULL){
        if (encodedKey == CurrentChunkLinkListNode->key){
            //If at start of list with no next following node
            if (lastChunkLinkListNode == NULL){
                free(chunkMap->nodes[mapIndex]);
                chunkMap->nodes[mapIndex] = NULL;
                return;
            }
            else {
                if (CurrentChunkLinkListNode->nextNode != NULL) {
                    //If at the end of a list
                    lastChunkLinkListNode->nextNode = CurrentChunkLinkListNode->nextNode;
                    free(CurrentChunkLinkListNode);
                    return;
                }
                    //at end
                else {
                    lastChunkLinkListNode->nextNode = NULL;
                    free(CurrentChunkLinkListNode);
                    return;
                }
            }
        }
        lastChunkLinkListNode = CurrentChunkLinkListNode;
        CurrentChunkLinkListNode = CurrentChunkLinkListNode->nextNode;
    }
}

void updateChunkMapLocation(struct ChunkMap* chunkMap, struct CastedChunk* castedChunk, int oldX, int oldY){
    removeFromMap(chunkMap, oldX, oldY);
    addChunkToMap(chunkMap, castedChunk);
}

void testChunkMap(struct GameData* gameData) {
    //Display test
    reportBug(
            "\n##################\n"
            "Testing Chunk Map \n"
            "##################\n");

    //Test key encoding
    struct ChunkMap *chunkMap = createChunkMap(1000);
    int xCor = -9;
    int yCor = -4;
    int64_t encodedKey = encodeKey(chunkMap->offset, xCor, yCor);
    int xDecode;
    int yDecode;
    decodeKey(encodedKey, chunkMap->offset, &xDecode, &yDecode);
    reportBug("\nTest key encoding : \n"
              "|Inputted %i, %i\n"
              "|Decoded %i, %i\n", xCor, yCor, xDecode, yDecode
    );

    //Test map adding and retrieval
    //Create casted chunk and add to map
    struct CastedChunk *castedChunk = createCastedChunk(gameData->cameraData, gameData->screen->renderer, 9, -4);
    addChunkToMap(chunkMap, castedChunk);

    //Testing returning function
    struct CastedChunk *returnedChunk = getChunkFromMap(chunkMap, 9, -4);
    reportBug("\nTest Chunk encoding:\n");
    if (castedChunk != NULL) {
        reportBug("|added chunk cords\n", returnedChunk->isoX, returnedChunk->isoY);
        reportBug("|Returned chunk cords\n", returnedChunk->isoX, returnedChunk->isoY);
    }
    else{
        reportBug("|Chunk not found \n");
    }


    reportBug("\nTest Removal from map:\n");
    //Verify chunk is there
    if (getChunkFromMap(chunkMap, 9, -4) != NULL){
        reportBug("|Chunk(%i, %i) exists"
                  , xCor, yCor);
    }
    //Remove and check if null
    removeFromMap(chunkMap, 9, -4);
    if (getChunkFromMap(chunkMap, 9, -4) == NULL){
        reportBug("|Chunk was remove successfully");
    }





    reportBug("\n##################\n");
}