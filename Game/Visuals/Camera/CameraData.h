//
// Created by Spencer on 5/6/2024.
//

#ifndef EDIFICE_CAMERADATA_H
#define EDIFICE_CAMERADATA_H

enum Direction{
    North,
    East,
    South,
    West
};

#include "SDL.h"
#include "Rendering/CastedBlockManager/CastedBlockManager.h"

struct DistanceCord
{
    int x;
    int y;
    double distance;
};

struct CameraData{

    //Drawing location
    float xRenderingOffset;
    float yRenderingOffset;

    //Camera world location
    int worldX;
    int worldY;
    int worldZ;

    //Dimensions
    int baseBlockScale;
    int blockPixelScale;
    int viewDistance;
    int maxViewDistance;
    int mouseUpdateDistance;
    int chunksScale;
    int chunkPixelScale;
    float renderScale;
    float fractionalScale;

    //Chunk management
    struct CastedPool* castedPool;
    int xIsoCamCenter;
    int yIsoCamCenter;

    int xIsoChunkCamCenter;
    int yIsoChunkCamCenter;

    int xChunkScaledTextureRez;
    int yChunkScaledTextureRez;

    //Raycasting
    int castingDistance;
    struct RayCastingData* rayCastingData;
    struct RayCastingThreadPool* rayCastingThreadPool;
    enum Direction direction;
    int xDirection;
    int yDirection;
    int zDirection;

    //sorted reltive cords for center based rendering
    int totalDistanceCords;
    struct DistanceCord* distanceSortedRelativeCords;

    struct World* world;
};

struct CameraData* createCameraData(SDL_Renderer* renderer, struct World* world);

char* getDirectionString(enum Direction direction);

void worldCordsToCameraCords(struct CameraData* cameraData, float worldX, float worldY, float worldZ, float* camX, float* camY);

#endif //EDIFICE_CAMERADATA_H
