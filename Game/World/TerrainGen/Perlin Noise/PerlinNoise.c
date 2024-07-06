//
// Created by Spencer on 5/2/2024.
//


#include <malloc.h>
#include "PerlinNoise.h"
#include <math.h>
#include "SDL.h"
#include "../../../Debuging/Test_Main.h"
#include "../../../GameData.h"

#define PI 3.14159265

int cordsToSeed(int x, int y){
    int maskedX = (x & 0xFFFF);
    int maskedY = (y & 0xFFFF) << 16;

    return maskedX | maskedY;
}


struct NoiseData* createNoiseData(int octave, int lacunarity, float persistence){
    struct NoiseData* noiseData = malloc(sizeof(struct NoiseData));
    if (noiseData == NULL){
        reportBug("PerlinNoise | Failed to malloc NoiseData struct \n");
        return NULL;
    }

    //Calculate possible influence possible vectors
    int possibleAngles = 16;
    noiseData->possibleAngles = possibleAngles;
    double influenceVectorAngles[possibleAngles];
    for (int corner = 0; corner < possibleAngles; corner++){
        //Create a set of evenly spaced angles based off num of possible angles
        double angle = 2 * PI * ((double) corner / possibleAngles);
        influenceVectorAngles[corner] = angle;
    }

    //Allocate float vector array
    noiseData->influenceVectors = malloc(sizeof(float*) * possibleAngles);
    for (int x = 0; x < possibleAngles; x++){
        noiseData->influenceVectors[x] = malloc(sizeof(float) * 2);
    }

    //Calculate and set float vectors
    for (int x = 0; x < possibleAngles; x++){
        noiseData->influenceVectors[x][0] = cos(influenceVectorAngles[x]);
        noiseData->influenceVectors[x][1] = sin(influenceVectorAngles[x]);
    }

    noiseData->seed = 1;
    noiseData->chunkScale = 128;
    noiseData->octave = octave;
    noiseData->lacunarity = lacunarity;
    noiseData->persistence = persistence;



    return noiseData;
}

short* getChunkHeightsCor(struct NoiseData* noiseData, int x, int y){
    //Create an array of length 4 of pointers to short arrays
    short** dotProductMaps = malloc(sizeof(short*) * 4);

    if (dotProductMaps == NULL){
        reportBug("PerlinNoise | Failed to malloc height array");
        return NULL;
    }

    //Gradients
    //Create dot product map for each corner
    for (int corner = 0; corner < 4; corner++) {
        short *cornerDotProductMap = calloc(noiseData->chunkScale * noiseData->chunkScale, sizeof(short));
        int randInfluenceVector = rand() % noiseData->possibleAngles;
        //Loop through pixels in map
        for (int x = 0; x < noiseData->chunkScale; x++) {
            for (int y = 0; y < noiseData->chunkScale; y++) {
                //Get the vector for each point
                int offSetVector[2] = {x, y};
                //get influence vector based off cords of point
                int dotProduct = (offSetVector[0] * noiseData->influenceVectors[randInfluenceVector][0]) + (offSetVector[1] * noiseData->influenceVectors[randInfluenceVector][1]);
                cornerDotProductMap[x + (y * noiseData->chunkScale)] = dotProduct;
            }
        }
        //Save to heights array
        dotProductMaps[corner] = cornerDotProductMap;
    }

    //Lerping
    //Combine Top
    short *combinedTopMap = calloc(noiseData->chunkScale * noiseData->chunkScale, sizeof(short));
    for (int y = 0; y < noiseData->chunkScale; y++) {
        short startVal = dotProductMaps[0][(y * noiseData->chunkScale)];
        for (int x = 0; x < noiseData->chunkScale; x++) {
            short lineDiff = ((dotProductMaps[0][x + (y * noiseData->chunkScale)]) - (dotProductMaps[1][x + (y * noiseData->chunkScale)])) * (x / (float) noiseData->chunkScale);
            short lerpDiff = lineDiff * (x / (float) noiseData->chunkScale);
            combinedTopMap[x + (y * noiseData->chunkScale)] = lerpDiff + startVal;
        }
    }

    //Combine Bottom
    short *combinedBopMap = calloc(noiseData->chunkScale * noiseData->chunkScale, sizeof(short));
    for (int y = 0; y < noiseData->chunkScale; y++) {
        short startVal = dotProductMaps[2][(y * noiseData->chunkScale)];
        for (int x = 0; x < noiseData->chunkScale; x++) {
            short lineDiff = ((dotProductMaps[2][x + (y * noiseData->chunkScale)]) - (dotProductMaps[3][x + (y * noiseData->chunkScale)])) * (x / (float) noiseData->chunkScale);
            short lerpDiff = lineDiff * (x / (float) noiseData->chunkScale);
            combinedBopMap[x + (y * noiseData->chunkScale)] = lerpDiff + startVal;
        }
    }

    for (int corner = 0; corner < 4; corner++) {
        free(dotProductMaps[corner]);
    }
    free(dotProductMaps);

    //Combine Top and bottom
    short *heightMap = calloc(noiseData->chunkScale * noiseData->chunkScale, sizeof(short));
    for (int x = 0; x < noiseData->chunkScale; x++){
        short startVal = combinedBopMap[(x * noiseData->chunkScale)];
        for (int y = 0; y < noiseData->chunkScale; y++){
            short lineDiff = ((combinedTopMap[x + (y * noiseData->chunkScale)]) - (combinedBopMap[x + (y * noiseData->chunkScale)])) * (y / (float) noiseData->chunkScale);
            short lerpDiff = lineDiff * (y / (float) noiseData->chunkScale);
            heightMap[x + (y * noiseData->chunkScale)] = lerpDiff + startVal;
        }
    }
    free(combinedBopMap);
    free(combinedTopMap);
    return heightMap;
}


//Debug
void drawHeightArray(struct GameData* gameData, short* heightArray, int scale){
    for (int x = 0; x < scale; x++) {
        for (int y = 0; y < scale; y++) {
            int color = abs(heightArray[x + (y * scale)]);
            SDL_SetRenderDrawColor(gameData->screen->renderer, 0, 0, 0, 255);
            if (color > 765){
                reportBug("HUH %i \n", color);
            }
            else if (color > 510){
                SDL_SetRenderDrawColor(gameData->screen->renderer, 255, 255, color, 255);
            }
            else if (color > 255){
                SDL_SetRenderDrawColor(gameData->screen->renderer, 255, color, 0, 255);
            }
            else{
                SDL_SetRenderDrawColor(gameData->screen->renderer, color, 0, 0, 255);
            }

            SDL_RenderDrawPoint(gameData->screen->renderer, x, y);
        }
    }
}