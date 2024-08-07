//
// Created by Spencer on 7/30/2024.
//

#ifndef EDIFICE_HILLMANAGER_H
#define EDIFICE_HILLMANAGER_H

struct HeightMapChunk{

    // The size that the chunk will be smoothed too
    int scale;
    short * heightMap;
};


struct HeightMapPool{
    //Tool for creating noiseData
    struct NoiseData* noiseData;

    struct HeightMapChunk** heightChunkPool;

    int chunkScale;

    int scale;
};

struct HeightMapPool* createHeightMapPool();

void applyHeightPool(struct TerrainGenRules* terrainGenRules, struct HeightMapPool* heightMapPool);

#endif //EDIFICE_HILLMANAGER_H
