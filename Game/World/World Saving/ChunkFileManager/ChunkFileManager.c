//
// Created by Spencer on 10/2/2024.
//

#include "ChunkFileManager.h"
#include <mbstring.h>
#include <stdio.h>
#include <malloc.h>
#include "../../../Debuging/Test_Main.h"
#include "../../../Blocks/Blocks.h"
#include "ChunkFileManager.h"


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
