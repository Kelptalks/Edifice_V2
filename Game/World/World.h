//
// Created by Spencer on 4/18/2024.
//

#ifndef ENGINE_WORLD_H
#define ENGINE_WORLD_H

struct World{
    int totalBlocks;
    struct Octree* octree;
    struct TerrainGenRules* terrainGenRules;
};

//Create a world
struct World* createWorld(int scale);

#endif //ENGINE_WORLD_H
