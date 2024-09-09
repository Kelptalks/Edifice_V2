//
// Created by Spencer on 8/27/2024.
//

#ifndef EDIFICE_WORLDCHUNK_H
#define EDIFICE_WORLDCHUNK_H

#include "../Octree/OctreeNode.h"

struct WorldChunk{
    struct OctreeNode* octreeNode;

    int xCor;
    int yCor;
    int zCor;
};

struct WorldChunk* createWorldChunk(int xCor, int yCor, int zCor);

enum Block getBlockInWorldChunk(struct WorldChunk* worldChunk, int x, int y, int z);

void setBlockInWorldChunk(struct WorldChunk* worldChunk, int x, int y, int z, enum Block block);

void testWorldChunk();

#endif //EDIFICE_WORLDCHUNK_H
