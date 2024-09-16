//
// Created by Spencer on 5/2/2024.
//

#ifndef ENGINE_PERLINNOISE_H
#define ENGINE_PERLINNOISE_H

#include <malloc.h>
#include "PerlinNoise.h"
#include <math.h>
#include "SDL.h"
#include "../../../Debuging/Test_Main.h"
#include "../../../GameData.h"

struct NoiseData{
    int seed;
    int chunkScale;
    int octave;
    int lacunarity;
    float persistence;

    int possibleAngles;

    //Array pointing to array of float vectors
    float** influenceVectors;
};


struct NoiseData* createNoiseData(int octave, int lacunarity, float persistence);

short* getChunkHeightsCor(int chunkSize, float** influenceVectors);

void drawHeightArray(struct GameData* gameData, short* heightArray, int scale);


#endif //ENGINE_PERLINNOISE_H
