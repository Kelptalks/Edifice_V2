//
// Created by Spencer on 6/12/2024.
//

#ifndef EDIFICE_CHUNKLINKLIST_H
#define EDIFICE_CHUNKLINKLIST_H
#include "../../Rendering/CastedBlockManager/CastedBlockManager.h"

struct ChunkLinkListNode{
    struct CastedChunk* castedChunk;
    int x, y;
    unsigned long key;
    struct ChunkLinkListNode* nextNode;
};

struct ChunkLinkListNode* createChunkLinkListNode(int x, int y, unsigned int key);


#endif //EDIFICE_CHUNKLINKLIST_H
