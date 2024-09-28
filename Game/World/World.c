//
// Created by Spencer on 4/18/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include "Octree/Octree.h"
#include "World.h"
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
    char name[] = "First_World";
    world->name = malloc(sizeof (name));
    world->name = name;


    world->chunkOctreeScale = 6;
    world->chunkOctreeDimension = getOctreeDimensions(world->chunkOctreeScale);
    //reportBug("octree Dimentions %i\n", world->chunkOctreeDimension);

    //Calculate ground height
    world->worldChunkHashMap = createWorldChunkHashMap(20000);


    world->debug = false;
    createTerrainGenRules(world);
    world->entityCount = 500;
    world->tempEntityArray = calloc(sizeof (struct Entity**), world->entityCount);
    int worldXScale = 150;
    int worldYScale = 150;
    reportBug("  - Generating Terrain : \n");
    genArea(world, 0, -worldXScale, -worldYScale, worldXScale, worldYScale, 100);
    reportBug(" - Creating Entity's : %i \n");
    for (int i = 0; i < world->entityCount; i++){
        int x = (rand() % (worldXScale * 2)) - worldXScale;
        int y = (rand() % (worldYScale * 2)) - worldYScale;
        world->tempEntityArray[i] = createPuffEntity();
        world->tempEntityArray[i]->worldZ = 50;
        world->tempEntityArray[i]->worldX = x;
        world->tempEntityArray[i]->worldY = y;
    }


    /*
    for (int x = 0; x < 500; x++){
        for (int y = 0; y < 500; y++){
            for (int z = -50; z < 50; z++){
                setBlockAtWorldCor(world, x, y, z, BlueGrass);
            }
        }

    }
     */

    world->debug = false;
    return world;
}

struct WorldChunk* getWorldChunk(struct World* world, int x, int y, int z){
    struct WorldChunk* worldChunk = getWordChunkFromMap(world->worldChunkHashMap, x, y, z);

    if (worldChunk == NULL){
        return NULL;
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
    if (worldChunk == NULL){
        return Air;
    }

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
    //Create world chunk if null
    if (worldChunk == NULL){
        worldChunk = createWorldChunk(chunkXCor, chunkYCor, chunkZCor);
        addWorldChunkToHashMap(world->worldChunkHashMap, worldChunk);
    }

    worldChunk->octree->debug = world->debug;

    //Mod the cords by getting the remainder using the bitwise operations
    int chunkSubXCor = x & (world->chunkOctreeDimension - 1);
    int chunkSubYCor = y & (world->chunkOctreeDimension - 1);
    int chunkSubZCor = z & (world->chunkOctreeDimension - 1);

    setBlockInWorldChunk(worldChunk, chunkSubXCor, chunkSubYCor, chunkSubZCor, block);
}

void testWorld(){

}