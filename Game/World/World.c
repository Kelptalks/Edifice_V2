//
// Created by Spencer on 4/18/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include "Octree/Octree.h"
#include "Octree/OctreeNode.h"
#include "World.h"
#include "Octree/Tools/KeyMod.h"
#include "TerrainGen/TerrainGen.h"
#include "WorldChunk/WorldChunk.h"

struct World* createWorld(int scale){
    //Create world struct
    struct World* world = malloc(sizeof (struct World));
    if (world == NULL){
        //append debug file
        FILE * debug;
        debug = fopen("debug", "a");
        fprintf(debug, "World | failed to malloc memory for world struct \n");
        fclose(debug);

        return NULL;
    }

    //Name the world
    char name[] = "World";
    world->name = malloc(sizeof (name));
    world->name = name;

    //Create octree for world data
    struct Octree* octree = createOctree(scale);
    if (octree == NULL){
        //append debug file
        FILE * debug;
        debug = fopen("debug", "a");
        fprintf(debug, "World | failed to malloc memory for octree struct \n");
        fclose(debug);
        return NULL;
    }


    world->chunkOctreeScale = 6;
    world->chunkOctreeDimension = getOctreeDimensions(world->chunkOctreeScale);

    //Calculate ground height
    world->octree = octree;
    createTerrainGenRules(world);


    unsigned long key = modKey(0, 0, 0, 0, octree->RootDepth);

    genArea(world, key, 500, 500, 50);

    return world;
}

struct WorldChunk* getWorldChunk(int x, int y, int z){

}

enum Block getBlockAtCor(struct World* world, int x, int y, int z){
    //Shift the cords based on the scale of the octree
    int chunkXCor = x >> world->chunkOctreeScale;
    int chunkYCor = y >> world->chunkOctreeScale;
    int chunkZCor = z >> world->chunkOctreeScale;

    struct WorldChunk* worldChunk = getWorldChunk(chunkXCor, chunkYCor, chunkZCor);

    //Mod the cords by getting the remainder using the bitwise operations
    int chunkSubXCor = x & (world->chunkOctreeDimension - 1);
    int chunkSubYCor = y & (world->chunkOctreeDimension - 1);
    int chunkSubZCor = z & (world->chunkOctreeDimension - 1);

    return getBlockInWorldChunk(worldChunk, chunkSubXCor, chunkSubYCor, chunkSubZCor);
};

void setBlockAtCor(struct World* world, int x, int y, int z, enum Block block){
    //Shift the cords based on the scale of the octree
    int chunkXCor = x >> world->chunkOctreeScale;
    int chunkYCor = y >> world->chunkOctreeScale;
    int chunkZCor = z >> world->chunkOctreeScale;

    struct WorldChunk* worldChunk = getWorldChunk(chunkXCor, chunkYCor, chunkZCor);

    //Mod the cords by getting the remainder using the bitwise operations
    int chunkSubXCor = x & (world->chunkOctreeDimension - 1);
    int chunkSubYCor = y & (world->chunkOctreeDimension - 1);
    int chunkSubZCor = z & (world->chunkOctreeDimension - 1);

    setBlockInWorldChunk(worldChunk, chunkSubXCor, chunkSubYCor, chunkSubZCor, block);
};