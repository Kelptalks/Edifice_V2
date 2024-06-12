//
// Created by Spencer on 6/12/2024.
//
#include "ChunkLinkList.h"

struct ChunkLinkListNode* createChunkLinkListNode(int x, int y, unsigned int key){
    struct ChunkLinkListNode* chunkLinkListNode = malloc(sizeof (struct ChunkLinkListNode));

    chunkLinkListNode->x = x;
    chunkLinkListNode->y = y;
    chunkLinkListNode->key = key;
    chunkLinkListNode->nextNode = NULL;

    return  chunkLinkListNode;

}