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
#include "../Debuging/Test_Main.h"
#include "../InGameTime/TikEvent/EntityManager/Puff/PuffLogic.h"

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
    world->worldChunkHashMap = createWorldChunkHashMap(10000);

    createTerrainGenRules(world);

    genArea(world, 0, 150, 150, 100);

    world->tempEntityArray = calloc(sizeof (struct Entity**), 20);

    for (int i = 0; i < 20; i++){
        world->tempEntityArray[i] = createPuffEntity();
        world->tempEntityArray[i]->worldX += i * 5;
    }


    return world;
}

struct WorldChunk* getWorldChunk(struct World* world, int x, int y, int z){
    struct WorldChunk* worldChunk = getWordChunkFromMap(world->worldChunkHashMap, x, y, z);

    if (worldChunk == NULL){
        worldChunk = createWorldChunk(x, y, z);
        addWorldChunkToHashMap(world->worldChunkHashMap, worldChunk);
        return worldChunk;
    }
    else{
        return worldChunk;
    }
}

enum Block getBlockAtWorldCor(struct World* world, int x, int y, int z){
    //Shift the cords based on the scale of the octree
    int chunkXCor = x >> world->chunkOctreeScale;
    int chunkYCor = y >> world->chunkOctreeScale;
    int chunkZCor = z >> world->chunkOctreeScale;

    struct WorldChunk* worldChunk = getWorldChunk(world, chunkXCor, chunkYCor, chunkZCor);

    //Mod the cords by getting the remainder using the bitwise operations
    int chunkSubXCor = x & (world->chunkOctreeDimension - 1);
    int chunkSubYCor = y & (world->chunkOctreeDimension - 1);
    int chunkSubZCor = z & (world->chunkOctreeDimension - 1);

    return getBlockInWorldChunk(worldChunk, chunkSubXCor, chunkSubYCor, chunkSubZCor);
};

void setBlockAtWorldCor(struct World* world, int x, int y, int z, enum Block block){
    //Shift the cords based on the scale of the octree
    int chunkXCor = x >> world->chunkOctreeScale;
    int chunkYCor = y >> world->chunkOctreeScale;
    int chunkZCor = z >> world->chunkOctreeScale;

    struct WorldChunk* worldChunk = getWorldChunk(world, chunkXCor, chunkYCor, chunkZCor);

    //Mod the cords by getting the remainder using the bitwise operations
    int chunkSubXCor = x & (world->chunkOctreeDimension - 1);
    int chunkSubYCor = y & (world->chunkOctreeDimension - 1);
    int chunkSubZCor = z & (world->chunkOctreeDimension - 1);

    setBlockInWorldChunk(worldChunk, chunkSubXCor, chunkSubYCor, chunkSubZCor, block);
};

void testWorld(){
    clearBugReports();
    struct World* world = createWorld(12);

    for (int x = -100; x < 100; x++){
        for (int y = -100; y < 100; y++){
            for (int z = -100; z < 100; z++){
                setBlockAtWorldCor(world, x, y, z, Stone);
            }
        }
    }

    for (int x = -100; x < 100; x++){
        for (int y = -100; y < 100; y++){
            for (int z = -100; z < 100; z++){
                enum Block block = getBlockAtWorldCor(world, x, y, z);
                if (block != Stone){
                    reportBug("failed to return correct value");
                }
            }
        }
    }
}