//
// Created by Spencer on 4/18/2024.
//

#include "WorldChunkHashMap/WorldChunkHashMap.h"

#ifndef ENGINE_WORLD_H
#define ENGINE_WORLD_H

struct World{
    char *name;

    int chunkOctreeScale;
    int chunkOctreeDimension;

    struct TerrainGenRules* terrainGenRules;

    int maxWorldChunks;
    struct WorldChunkHashMap* worldChunkHashMap;
    int totalChunksCreated;
    struct WorldChunk** allCreatedWorldChunks;

    //
    int entityCount;
    struct Entity** tempEntityArray;

    bool debug;
};

//Create a world
struct World* createWorld(char *worldName);

enum Block getBlockAtWorldCor(struct World* world, int x, int y, int z);
void setBlockAtWorldCor(struct World* world, int x, int y, int z, enum Block block);

void testWorld();

#endif //ENGINE_WORLD_H
