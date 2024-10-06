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
    float worldX;
    float worldY;
    float worldZ;

    //Dimensions
    float baseBlockScale;
    float blockPixelScale;
    float viewDistance;
    float maxViewDistance;
    float mouseUpdateDistance;
    int chunksScale;
    float chunkPixelScale;
    float renderScale;
    float fractionalScale;

    //Chunk management
    struct CastedPool* castedPool;
    float xIsoCamCenter;
    float yIsoCamCenter;

    float xIsoChunkCamCenter;
    float yIsoChunkCamCenter;

    float xChunkScaledTextureRez;
    float yChunkScaledTextureRez;

    //Ray casting
    int castingDistance;
    struct RayCastingData* rayCastingData;
    struct RayCastingThreadPool* rayCastingThreadPool;
    enum Direction direction;
    int xDirection;
    int yDirection;
    int zDirection;

    //sorted relative cords for center based rendering
    int totalDistanceCords;
    struct DistanceCord* distanceSortedRelativeCords;

    //Movement
    float camVelX;
    float camVelY;
    float camVelResist;

    struct World* world;
};

struct CameraData* createCameraData(SDL_Renderer* renderer, struct World* world);

char* getDirectionString(enum Direction direction);

void worldCordsToCameraCords(struct CameraData* cameraData, float worldX, float worldY, float worldZ, float* camX, float* camY);

void worldCordsToScreenCords(struct CameraData* cameraData, float worldX, float worldY, float worldZ, float* camX, float* camY);

#endif //EDIFICE_CAMERADATA_H
