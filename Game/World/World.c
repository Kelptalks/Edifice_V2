//
// Created by Spencer on 4/18/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Octree/Octree.h"
#include "World.h"
#include "TerrainGen/TerrainGen.h"
#include "WorldChunk/WorldChunk.h"
#include "../Debuging/Test_Main.h"
#include "../InGameTime/TikEvent/EntityManager/Puff/PuffLogic.h"
#include "../InGameTime/Drone/Drone.h"
#include "../InGameTime/Drone/DroneLuaCommands/DroneLuaCommands.h"
#include "../InGameTime/Drone/DroneData.h"

struct World* createWorld(char *worldName){
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
    world->name = malloc(strlen(worldName) + 1);
    strcpy(world->name, worldName);

    world->chunkOctreeScale = 6;
    world->chunkOctreeDimension = getOctreeDimensions(world->chunkOctreeScale);

    //Create world chunk storage
    world->maxWorldChunks = 20000;
    world->worldChunkHashMap = createWorldChunkHashMap(world->maxWorldChunks);
    world->totalChunksCreated = 0;
    world->allCreatedWorldChunks = malloc(sizeof (struct WorldChunk*) * world->maxWorldChunks);

    world->entityCount = 0;
    world->tempEntityArray = NULL;

    world->droneData = createDroneData(world, 100);

    world->debug = false;

    return world;
}

void generateWorldTerrain(struct World* world, int xScale, int yScale, int roughness){
    //Build world terrain
    world->debug = false;
    createTerrainGenRules(world);
    int worldXScale = xScale;
    int worldYScale = yScale;
    reportBug("  - Generating Terrain : \n");
    genArea(world, -worldXScale, -worldYScale, worldXScale, worldYScale, roughness);
}

struct WorldChunk* createWorldChunkInWorld(struct World* world, int x, int y, int z){
    if (world->totalChunksCreated < world->maxWorldChunks) {
        //Create the world chunk
        struct WorldChunk *worldChunk = createWorldChunk(x, y, z);
        //Add the world chunk to hashmap
        addWorldChunkToHashMap(world->worldChunkHashMap, worldChunk);
        //Add world chunk to all chunk array
        world->allCreatedWorldChunks[world->totalChunksCreated] = worldChunk;
        world->totalChunksCreated++;
        return worldChunk;
    }
    reportBug("ERROR : max world chunks created\n");
    return NULL;
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
        worldChunk = createWorldChunkInWorld(world, chunkXCor, chunkYCor, chunkZCor);
        addWorldChunkToHashMap(world->worldChunkHashMap, worldChunk);
    }

    worldChunk->octree->debug = world->debug;

    //Mod the cords by getting the remainder using the bitwise operations
    int chunkSubXCor = x & (world->chunkOctreeDimension - 1);
    int chunkSubYCor = y & (world->chunkOctreeDimension - 1);
    int chunkSubZCor = z & (world->chunkOctreeDimension - 1);

    setBlockInWorldChunk(worldChunk, chunkSubXCor, chunkSubYCor, chunkSubZCor, block);
}

void freeWorld(struct World* world){
    for (int i = 1; i < world->totalChunksCreated; i++){
        if (world->allCreatedWorldChunks[i] != NULL) {
            freeWorldChunk(world->allCreatedWorldChunks[i]);
        }
    }
    free(world->allCreatedWorldChunks);

    for (int i = 1; i < world->entityCount; i++){
        if (world->tempEntityArray[i] != NULL) {
            free(world->tempEntityArray[i]);
        }
    }
    if (world->tempEntityArray != NULL) {
        free(world->tempEntityArray);
    }

    free(world->name);
    freeWorldHashMap(world->worldChunkHashMap);
    free(world);

}