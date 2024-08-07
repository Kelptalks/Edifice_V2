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
    noiseData->chunkScale = 32;
    noiseData->octave = octave;
    noiseData->lacunarity = lacunarity;
    noiseData->persistence = persistence;



    return noiseData;
}

short* getChunkHeightsCor(int chunkSize, float** influenceVectors){
    //Create an array of length 4 of pointers to short arrays
    short** dotProductMaps = malloc(sizeof(short*) * 4);

    if (dotProductMaps == NULL){
        reportBug("PerlinNoise | Failed to malloc height array");
        return NULL;
    }

    //Gradients
    //Create dot product map for each corner
    for (int corner = 0; corner < 4; corner++) {
        short *cornerDotProductMap = calloc(chunkSize * chunkSize, sizeof(short));
        int randInfluenceVector = rand() % 16;

        float xInfluence =  influenceVectors[randInfluenceVector][0];
        float yInfluence =  influenceVectors[randInfluenceVector][1];


        //Loop through pixels in map
        for (int x = 0; x < chunkSize; x++) {
            for (int y = 0; y < chunkSize; y++) {
                //Get the vector for each point
                int offSetVector[2] = {x, y};
                //get influence vector based off cords of point

                short dotProduct = (offSetVector[0] * xInfluence) + (offSetVector[1] * yInfluence);
                cornerDotProductMap[x + (y * chunkSize)] = dotProduct;
            }
        }
        //Save to heights array
        dotProductMaps[corner] = cornerDotProductMap;
    }

    //Lerping
    //Combine Top
    short *combinedTopMap = calloc(chunkSize * chunkSize, sizeof(short));
    for (int y = 0; y < chunkSize; y++) {
        short startVal = dotProductMaps[0][(y * chunkSize)];
        for (int x = 0; x < chunkSize; x++) {
            short lineDiff = ((dotProductMaps[0][x + (y * chunkSize)]) - (dotProductMaps[1][x + (y * chunkSize)])) * (x / (float) chunkSize);
            short lerpDiff = lineDiff * (x / (float) chunkSize);
            combinedTopMap[x + (y * chunkSize)] = lerpDiff + startVal;
        }
    }

    //Combine Bottom
    short *combinedBopMap = calloc(chunkSize * chunkSize, sizeof(short));
    for (int y = 0; y < chunkSize; y++) {
        short startVal = dotProductMaps[2][(y * chunkSize)];
        for (int x = 0; x < chunkSize; x++) {
            short lineDiff = ((dotProductMaps[2][x + (y * chunkSize)]) - (dotProductMaps[3][x + (y * chunkSize)])) * (x / (float) chunkSize);
            short lerpDiff = lineDiff * (x / (float) chunkSize);
            combinedBopMap[x + (y * chunkSize)] = lerpDiff + startVal;
        }
    }

    for (int corner = 0; corner < 4; corner++) {
        free(dotProductMaps[corner]);
    }
    free(dotProductMaps);

    //Combine Top and bottom
    short *heightMap = calloc(chunkSize * chunkSize, sizeof(short));
    for (int x = 0; x < chunkSize; x++){
        short startVal = combinedBopMap[(x * chunkSize)];
        for (int y = 0; y < chunkSize; y++){
            short lineDiff = ((combinedTopMap[x + (y * chunkSize)]) - (combinedBopMap[x + (y * chunkSize)])) * (y / (float) chunkSize);
            short lerpDiff = lineDiff * (y / (float) chunkSize);
            heightMap[x + (y * chunkSize)] = lerpDiff + startVal;
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