//
// Created by Spencer on 7/1/2024.
//

#include <mbstring.h>
#include <stdio.h>
#include <malloc.h>
#include <windows.h>
#include <sys/stat.h>

#include "../World.h"
#include "../../Debuging/Test_Main.h"
#include "../../Blocks/Blocks.h"
#include "../../InGameTime/TikEvent/EntityManager/Puff/PuffLogic.h"
#include "ChunkFileManager/ChunkFileManager.h"
#include "../../InGameTime/Drone/Drone.h"
#include "../../InGameTime/Drone/DroneData.h"


FILE* openWorldFile(char *filePath){
    // Try to open the file in read+write mode to check if it exists
    FILE *file = fopen(filePath, "rb+");

    if (file == NULL) {
        // File does not exist, create it
        reportBug("File does not exist. Creating it now...\n");

        // Open the file in write mode to create it
        file = fopen(filePath, "w");
        if (file == NULL) {
            reportBug("Error creating file.\n");
            return NULL; // Return NULL to signal failure
        }

        reportBug("World File Created\n");

        // Close the file after creation and reopen in r+ mode
        fclose(file);
        file = fopen(filePath, "rb+");
        if (file == NULL) {
            reportBug("Error reopening file in r+ mode.\n");
            return NULL; // Return NULL to signal failure
        }
    } else {
        // File exists
        //reportBug("File exists.\n");
    }

    return file;
}

void deleteWorldFile(char *fileName){
    if (remove(fileName) == 0) {
        reportBug("File deleted successfully.\n");
    } else {
        reportBug("Error: unable to delete the file.\n");
    }
}

bool ifFileExists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return true;
    }
    return false;
}

void clearWorldFile(){
    const char *filePath = "Saves/WorldSave.bin";
    FILE *file = fopen(filePath, "w");
    fclose(file);
}

void saveWorldToFile(struct World* world){

    for (int i = 0; i < world->droneData->droneCount; i++) {
        struct Drone* drone = world->droneData->drones[i];
        if (world->droneData->drones[i] != NULL) {
            setBlockAtWorldCor(world, drone->worldX, drone->worldY, drone->worldZ, DroneDead);
        }
    }

    FILE* file = openWorldFile(world->name);
    clearWorldFile();
    fseek(file, 0, SEEK_SET);

    //WriteWorldData;
    unsigned int worldDataLength = 3;
    fwrite(&world->maxWorldChunks, sizeof(int), 1, file);
    fwrite(&world->chunkOctreeScale, sizeof(int), 1, file);
    fwrite(&world->totalChunksCreated, sizeof(int), 1, file);

    unsigned int indexSpacingPerChunk = getSizeOfWorldChunk(6);
    for (int i = 0; i < world->totalChunksCreated; i++){
        struct WorldChunk* currentChunk = world->allCreatedWorldChunks[i];
        unsigned int currentIndex = worldDataLength + (indexSpacingPerChunk * i);

        writeChunkToFile(file, currentChunk, currentIndex);
    }

    fclose(file);
}

struct World* readWorldData(char* fileName){
    reportBug("reading world %s\n", fileName);
    FILE* file = openWorldFile(fileName);
    fseek(file, 0, SEEK_SET);

    //Read world Data
    struct World* world = malloc(sizeof (struct World));

    unsigned int worldDataLength = 3;
    fread(&world->maxWorldChunks, sizeof(int), 1, file);
    fread(&world->chunkOctreeScale, sizeof(int), 1, file);
    fread(&world->totalChunksCreated, sizeof(int), 1, file);

    world->chunkOctreeDimension = getOctreeDimensions(world->chunkOctreeScale);
    world->worldChunkHashMap = createWorldChunkHashMap(world->maxWorldChunks);
    world->allCreatedWorldChunks = malloc(sizeof (struct WorldChunk*) * world->maxWorldChunks);

    unsigned int indexSpacingPerChunk = getSizeOfWorldChunk(6);
    for (int i = 0; i < world->totalChunksCreated; i++){
        //Read the chunk
        unsigned int currentIndex = worldDataLength + (indexSpacingPerChunk * i);
        struct WorldChunk* currentChunk = readChunkFromFile(file, currentIndex);

        //Set the chunk in the world map
        addWorldChunkToHashMap(world->worldChunkHashMap, currentChunk);
        world->allCreatedWorldChunks[i] = currentChunk;
    }

    //Set up basic variables
    world->terrainGenRules = NULL;
    world->debug = false;

    //Set up world name
    world->name = malloc(strlen(fileName) + 1);
    strcpy(world->name, fileName);

    //Set up entity array
    world->entityCount = 150;
    world->tempEntityArray = calloc(sizeof (struct Entity*), world->entityCount);
    for (int i = 0; i < 100; i++) {
        world->tempEntityArray[i] = createPuffEntity();
        world->tempEntityArray[i]->worldX = rand()%150;
        world->tempEntityArray[i]->worldY = rand()%150;
        world->tempEntityArray[i]->worldZ = 100;
    }


    //Set up drone array
    world->droneData = createDroneData(world, 100);

    fclose(file);
    return world;
}

void testWorldSaving(){
    /*
    clearBugReports();
    clearWorldFile();

    struct WorldChunk* worldChunk = malloc(sizeof (struct WorldChunk));
    worldChunk->xCor = 0;
    worldChunk->yCor = 0;
    worldChunk->zCor = 0;
    worldChunk->octree = createOctree(6);

    //reportBug("%i\n",worldChunk->octree->octreeDataArrayLength);

    worldChunk->octree->debug = false;

    worldChunk->xCor = 0;
    worldChunk->yCor = 0;

    for (int x = 0; x < 64; x++){
        for (int y = 0; y < 64; y++){
            for (int z = 0; z < 64; z++){
                setBlockInWorldChunk(worldChunk, x, y, z, x %50);
            }
        }
    }

    FILE* file = openWorldFile("Saves/WorldTest.bin");
    reportBug("#############\n");
    reportBug("## Writing ##\n");
    reportBug("#############\n");
    writeChunkToFile(file, worldChunk, 0);
    fclose(file);


    file = openWorldFile("Saves/WorldTest.bin");
    reportBug("#############\n");
    reportBug("## Reading ##\n");
    reportBug("#############\n");
    struct WorldChunk* readChunk = readChunkFromFile(file, 0);
    fclose(file);


    struct Octree* octreeWritten = worldChunk->octree;
    struct Octree* octreeRead = readChunk->octree;
    int octreeFailCount = 0;
    int firstOctreeFailIndex = -1;
    for (int x = 0; x < octreeRead->octreeDataArrayLength; x++){
        if (octreeWritten->octreeData[x] != octreeRead->octreeData[x]){
            //reportBug("expected %i was %i\n",octree1->octreeData[x], octree2->octreeData[x]);
            octreeFailCount++;
            if (firstOctreeFailIndex == -1){
                firstOctreeFailIndex = x;
            }

        }
    }
    reportBug("\n############################\n");
    reportBug("Octree Fail count = %i\n", octreeFailCount);
    reportBug("First Octree Fail index = %i\n", firstOctreeFailIndex);



    //Test world
    struct World* world = createWorld("Saves/WorldTest.bin", 150, 150);
    for (int x = 0; x < 200; x++){
        for (int y = 0; y < 200; y++){
            for (int z = 0; z < 50; z++){
                setBlockAtWorldCor(world, x, y, z, x%60);
            }
        }
    }
    saveWorldToFile(world);


    struct World* world1;
    if (ifFileExists(world->name)){
        world1 = readWorldData(world->name);
    }

    int totalFails = 0;
    for (int x = 0; x < 200; x++){
        for (int y = 0; y < 200; y++){
            for (int z = 0; z < 50; z++){
                int value = getBlockAtWorldCor(world1, x, y, z);
                if (value != x%60){
                    totalFails++;
                }
            }
        }
    }
    reportBug("Total errors : %i\n", totalFails);

    // Found the error Here
    int octreeFails = 0;
    for (int i = 0; i < world->totalChunksCreated; i++){

        struct Octree* octree1 = world->allCreatedWorldChunks[i]->octree;
        //reportBug("cords of OG chunk = %i, %i, %i\n", world->allCreatedWorldChunks[i]->xCor, world->allCreatedWorldChunks[i]->yCor, world->allCreatedWorldChunks[i]->zCor);

        struct Octree* octree2 = world1->allCreatedWorldChunks[i]->octree;
        //reportBug("cords of returned chunk = %i, %i, %i\n", world1->allCreatedWorldChunks[i]->xCor, world1->allCreatedWorldChunks[i]->yCor, world1->allCreatedWorldChunks[i]->zCor);

        for (int x = 0; x < 1000; x++){
            if (octree1->octreeData[x] != octree2->octreeData[x]){
                //reportBug("expected %i was %i\n",octree1->octreeData[x], octree2->octreeData[x]);
                octreeFails++;
            }

        }
    }

    reportBug("total octree copy fails = %i\n", octreeFails);


    int returnedBlock = getBlockAtWorldCor(world1, 304, 439, 29);
    reportBug("%i\n", returnedBlock);
     */
}