//
// Created by Spenjcer on 7/30/2024.
//


#include <stdlib.h>
#include "../../World.h"
#include "../../Octree/OctreeNode.h"
#include "../../Octree/Octree.h"
#include "../../Octree/Tools/KeyMod.h"
#include "../LairManager/LairManager.h"
#include "../TerrainGen.h"
#include "../../../../ArrayList/ArrayList.h"
#include "../../../Debuging/Test_Main.h"
#include "../Perlin Noise/PerlinNoise.h"
#include "HillManager.h"



struct HeightMapChunk* createHeightMapChunk(int scale){
    struct HeightMapChunk* heightMapChunk = malloc(sizeof (struct HeightMapChunk));
    if (heightMapChunk == NULL){
        reportBug("failed too malloc heightMapChunk");
        return NULL;
    }
    heightMapChunk->scale = scale;

    return heightMapChunk;
}

void smoothChunkMapPool(struct HeightMapPool* heightMapPool, int smoothingScale){
    //Loop through the chunks and identify boarders
    for (int x = 0; x < heightMapPool->scale; x++){
        for (int y = 0; y < heightMapPool->scale; y++){
            //Get index of current chunk to smooth
            int index = x + (y * heightMapPool->scale);
            struct HeightMapChunk* mainHeightMapChunk = &heightMapPool->heightChunkPool[x][y];
            if (mainHeightMapChunk == NULL){
                reportBug("Indexed out of range for HeighMapPool of size %i\n", heightMapPool->scale);
            }

            //Loop through neighboring chunks
            for (int side = 0; side < 1; side++){
                struct HeightMapChunk* neighboringHeightMapChunk;

                if (side == 0){
                    neighboringHeightMapChunk = &heightMapPool->heightChunkPool[x + 1][y];
                } else if(side == 1){
                    neighboringHeightMapChunk = &heightMapPool->heightChunkPool[x][y + 1];
                }
                else if(side == 2){
                    neighboringHeightMapChunk = &heightMapPool->heightChunkPool[x - 1][y];
                }
                else if(side == 3){
                    neighboringHeightMapChunk = &heightMapPool->heightChunkPool[x][y - 1];
                }

                //If the neighboring chunk exists smooth

            }
        }
    }
}

struct HeightMapPool* createHeightMapPool(){
    struct HeightMapPool* heightMapPool = malloc(sizeof (struct HeightMapPool));
    //Set basics
    heightMapPool->chunkScale = 64;
    heightMapPool->scale = 4;

    //Malloc the chunks

    heightMapPool->heightChunkPool = malloc(sizeof (struct HeightMapChunk*) * heightMapPool->scale);
    for (int x = 0; x < heightMapPool->scale; x++){
        heightMapPool->heightChunkPool[x] = malloc(sizeof (struct HeightMapChunk) * heightMapPool->scale);
    }

    //test
    struct NoiseData* noiseData = createNoiseData(0, 0, 0);

    //assign the chunks
    for (int y = 0; y < heightMapPool->scale; y++) {
        for (int x = 0; x < heightMapPool->scale; x++) {
            heightMapPool->heightChunkPool[x][y] = *createHeightMapChunk(heightMapPool->chunkScale);
            //reportBug("Chunk Cords (%i, %i) | Pointer = %p\n", x, y, heightMapPool->heightChunkPool[x][y]);
            heightMapPool->heightChunkPool[x][y].heightMap = getChunkHeightsCor(heightMapPool->chunkScale, noiseData->influenceVectors);
        }
    }

    smoothChunkMapPool(heightMapPool, 10);
    return heightMapPool;
}