//
// Created by Spencer on 4/18/2024.
//

#include "Octree/OctreeBranchPool/OctreeNodePool.h"
#include "WorldChunkHashMap/WorldChunkHashMap.h"

#ifndef ENGINE_WORLD_H
#define ENGINE_WORLD_H

struct World{
    char* name;

    int chunkOctreeScale;
    int chunkOctreeDimension;

    struct TerrainGenRules* terrainGenRules;

    //
    struct OctreeNodePool* octreeNodePool;
    struct WorldChunkHashMap* worldChunkHashMap;

    //
    struct Entity** tempEntityArray;

};

//Create a world
struct World* createWorld(int scale);

enum Block getBlockAtWorldCor(struct World* world, int x, int y, int z);
void setBlockAtWorldCor(struct World* world, int x, int y, int z, enum Block block);

void testWorld();

#endif //ENGINE_WORLD_H
