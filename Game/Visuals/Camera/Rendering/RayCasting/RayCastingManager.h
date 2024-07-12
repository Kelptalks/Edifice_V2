//
// Created by Spencer on 5/14/2024.
//

#ifndef EDIFICE_RAYCASTINGMANAGER_H
#define EDIFICE_RAYCASTINGMANAGER_H

struct RayCastingData{
    int leftOrder[3];
    int rightOrder[3];
};

struct RayCastingData* createRayCastingData(struct CameraData* cameraData);

void updateCastingDirectionOrder(struct CameraData* cameraData);

void rayCastBlock(struct CameraData* cameraData, struct CastedBlock* castedBlock, struct Octree* octree);

void rayCastChunk(struct CameraData* cameraData, struct CastedChunk* castedChunk, struct Octree* octree);

void threadCastChunk(struct CameraData* cameraData, struct CastedChunk* castedChunk, struct Octree* octree);

#endif //EDIFICE_RAYCASTINGMANAGER_H
