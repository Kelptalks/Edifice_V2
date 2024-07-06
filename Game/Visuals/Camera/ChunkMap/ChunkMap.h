//
// Created by Spencer on 6/12/2024.
//

#ifndef EDIFICE_CHUNKMAP_H
#define EDIFICE_CHUNKMAP_H
#include "../../../GameData.h"

struct ChunkMap{
    struct ChunkLinkListNode** nodes;
    int size;
    int offset;
};

struct ChunkLinkListNode{
    struct CastedChunk* castedChunk;
    int64_t key;
    struct ChunkLinkListNode* nextNode;
};

struct ChunkMap* createChunkMap(int size);

void addChunkToMap(struct ChunkMap* chunkMap,struct CastedChunk* castedChunk);

struct CastedChunk* getChunkFromMap(struct ChunkMap* chunkMap, int xCor, int yCor);

void updateChunkMapLocation(struct ChunkMap* chunkMap, struct CastedChunk* castedChunk, int oldX, int oldY);

void testChunkMap(struct GameData* gameData);

#endif //EDIFICE_CHUNKMAP_H
