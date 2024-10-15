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


    struct FurnaceData* furnaceData;
    struct DroneData* droneData;


    bool debug;
};

//Create a world
struct World* createWorld(char *worldName);

enum Block getBlockAtWorldCor(struct World* world, int x, int y, int z);
void setBlockAtWorldCor(struct World* world, int x, int y, int z, enum Block block);

void generateWorldTerrain(struct World* world, int xScale, int yScale, int roughness);

void freeWorld(struct World* world);

void testWorld();

#endif //ENGINE_WORLD_H
