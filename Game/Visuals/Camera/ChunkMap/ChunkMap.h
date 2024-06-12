//
// Created by Spencer on 6/12/2024.
//

#ifndef EDIFICE_CHUNKMAP_H
#define EDIFICE_CHUNKMAP_H

#include "ChunkLinkList/ChunkLinkList.h"

struct ChunkMap{
    struct ChunkLinkListNode** nodes;
    int size;
};

struct ChunkMap* createChunkMap(int size);

struct CastedChunk* getChunkFromMap(struct ChunkMap* chunkMap, int x, int y);

void addChunkToMap(struct ChunkMap* chunkMap, struct CastedChunk* castedChunk);

void removeChunkFromMap(struct ChunkMap* chunkMap, int x, int y);

#endif //EDIFICE_CHUNKMAP_H
