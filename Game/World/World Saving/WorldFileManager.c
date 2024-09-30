//
// Created by Spencer on 7/1/2024.
//

#include <mbstring.h>
#include <stdio.h>
#include <malloc.h>
#include <sys/stat.h>

#include "../World.h"
#include "../../Debuging/Test_Main.h"
#include "../../Blocks/Blocks.h"
#include "../../InGameTime/TikEvent/EntityManager/Puff/PuffLogic.h"

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

unsigned int getSizeOfWorldChunk(int depth){
    int totalLength = 0;

    //3 for each world cor
    totalLength += 3;

    //5 for octrees | depth, volume, nextFreeIndex, octreeDataArrayLength, nodeDataArrayLength
    totalLength +=5;

    //+ size of each world chunks data arrays
    totalLength += getOctreeDataArrayLength(depth);
    totalLength += getOctreeDataArrayLength(depth);

    //Safety buffer
    totalLength += 500;

    return totalLength;
}

void writeChunkToFile(FILE *file, struct WorldChunk* worldChunk, unsigned int indexInFile){
    //Get the location of the chunk
    fseek(file, sizeof(int) * indexInFile, SEEK_SET);

    //Write world coordinates
    fwrite(&worldChunk->xCor, sizeof(int), 1, file);
    fwrite(&worldChunk->yCor, sizeof(int), 1, file);
    fwrite(&worldChunk->zCor, sizeof(int), 1, file);

    //Write Octree Data
    struct Octree* octree = worldChunk->octree;
    fwrite(&octree->depth, sizeof(int), 1, file);
    fwrite(&octree->volume, sizeof(int), 1, file);
    fwrite(&octree->nextFreeIndex, sizeof(unsigned int), 1, file);
    fwrite(&octree->octreeDataArrayLength, sizeof(int), 1, file);
    fwrite(&octree->nodeDataArrayLength, sizeof(int), 1, file);

    //Write the octree data arrays
    size_t items_written = fwrite(octree->branchData, sizeof(unsigned int), octree->nodeDataArrayLength, file);
    if (octree->nodeDataArrayLength > 300000){
        reportBug("Node Data array length : %i\n", octree->nodeDataArrayLength);
    }

    if (items_written != octree->nodeDataArrayLength){
        reportBug("Failed to write all branchData items : %zu\n", items_written);
        return;
    }

    items_written = fwrite(octree->octreeData, sizeof(unsigned int), octree->octreeDataArrayLength, file);

    if (octree->octreeDataArrayLength > 300000){
        reportBug("Node Octree array length : %i\n", octree->octreeDataArrayLength);
    }
    if (items_written != octree->octreeDataArrayLength){
        reportBug("Failed to write all octree data items : %zu\n", items_written);
        return;
    }



    //reportBug("\nFinal File index after writing : %i\n", ftell(file));
}

struct WorldChunk* readChunkFromFile(FILE* file, unsigned int indexInFile){
    //reportBug("File size to read %ld\n", fileSize);

    //Create struct for world chunk
    struct WorldChunk* worldChunk = malloc(sizeof (struct WorldChunk));
    if (worldChunk == NULL){
        reportBug("Failed to allocate memory for world chunk\n");
        return NULL;
    }

    //Get the location of the chunk
    fseek(file, sizeof(int) * indexInFile, SEEK_SET);

    //Read world coordinates
    fread(&worldChunk->xCor, sizeof(int), 1, file);
    fread(&worldChunk->yCor, sizeof(int), 1, file);
    fread(&worldChunk->zCor, sizeof(int), 1, file);

    //Read octree values
    struct Octree* octree = malloc(sizeof(struct Octree));
    if (octree == NULL){
        reportBug("Failed to allocate memory for octree\n");
        free(worldChunk);
        return NULL;
    }
    fread(&octree->depth, sizeof(int), 1, file);
    fread(&octree->volume, sizeof(int), 1, file);
    fread(&octree->nextFreeIndex, sizeof(unsigned int), 1, file);
    fread(&octree->octreeDataArrayLength, sizeof(int), 1, file);
    fread(&octree->nodeDataArrayLength, sizeof(int), 1, file);

    //Malloc the required octree arrays;
    octree->branchData = calloc(octree->nodeDataArrayLength, sizeof (unsigned int));
    if (octree->branchData == NULL){
        reportBug("Failed to allocate branchData array for loading file\n");
        free(octree);
        free(worldChunk);
    }
    octree->octreeData = calloc(octree->octreeDataArrayLength, sizeof(unsigned int));
    if (octree->octreeData == NULL){
        reportBug("Failed to allocate octreeData array for loading file\n");
        free(octree->branchData);
        free(octree);
        free(worldChunk);
        return NULL;
    }


    //Read the octree data
    size_t items_read = fread(octree->branchData, sizeof(unsigned int), octree->nodeDataArrayLength, file);
    //reportBug("Node array length : %i\n", octree->octreeDataArrayLength);
    if (octree->nodeDataArrayLength > 300000){
        reportBug("Node Data array length : %i\n", octree->nodeDataArrayLength);
    }
    if (items_read != octree->nodeDataArrayLength){\
        reportBug("Failed to read all branchData items : %zu\n", items_read);
        reportBug("current file index %i\n", ftell(file));
        reportBug("Expected Node Data size %i bytes\n", sizeof(unsigned int) * octree->nodeDataArrayLength);
    }



    items_read = fread(octree->octreeData, sizeof(unsigned int), octree->octreeDataArrayLength, file);
    if (octree->octreeDataArrayLength > 300000){
        reportBug("Node Octree array length : %i\n", octree->octreeDataArrayLength);
    }
    if (items_read != octree->octreeDataArrayLength){
        reportBug("Failed to read all octreeData items : %i\n", items_read);
        reportBug("current file index %i\n", ftell(file));
        reportBug("Expected OctreeData size %i bytes\n", sizeof(unsigned int) * octree->octreeDataArrayLength);
        reportBug("OctreeData array length : %i\n", octree->octreeDataArrayLength);
    }

    //reportBug("\nFinal File index after reading : %i\n", ftell(file));
    for (int i = 0; i < octree->octreeDataArrayLength; i++){
        if (octree->octreeData[i] >= octree->octreeDataArrayLength){
            octree->octreeData[i] = 0;
        }
    }

    worldChunk->octree = octree;
    worldChunk->octree->debug = false;
    return worldChunk;
}

void saveWorldToFile(struct World* world){
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

    world->terrainGenRules = NULL;
    world->debug = false;

    world->name = malloc(strlen(fileName) + 1);
    strcpy(world->name, fileName);

    world->entityCount = 0;
    world->entityCount = 150;
    world->tempEntityArray = calloc(sizeof (struct Entity**), world->entityCount);
    for (int i = 0; i < world->entityCount; i++){
        int x = (rand() % (150 * 2)) - 150;
        int y = (rand() % (150 * 2)) - 150;
        world->tempEntityArray[i] = createPuffEntity();
        world->tempEntityArray[i]->worldZ = 50;
        world->tempEntityArray[i]->worldX = x;
        world->tempEntityArray[i]->worldY = y;
    }


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