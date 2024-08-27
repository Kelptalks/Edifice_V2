//
// Created by Spencer on 4/18/2024.
//

#include "Octree/OctreeBranchPool/OctreeNodePool.h"

#ifndef ENGINE_WORLD_H
#define ENGINE_WORLD_H

struct World{
    char* name;

    int chunkOctreeScale;
    int chunkOctreeDimension;

    struct Octree* octree;
    struct TerrainGenRules* terrainGenRules;

    //
    struct OctreeNodePool* octreeNodePool;
};

//Create a world
struct World* createWorld(int scale);


#endif //ENGINE_WORLD_H
