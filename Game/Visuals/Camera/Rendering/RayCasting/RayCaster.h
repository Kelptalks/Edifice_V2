//
// Created by Spencer on 5/14/2024.
//

#ifndef EDIFICE_RAYCASTER_H
#define EDIFICE_RAYCASTER_H

void castLeftTriangle(struct CameraData* cameraData, struct CastedBlock* castedBlock, struct Octree* octree);

void castRightTriangle(struct CameraData* cameraData, struct CastedBlock* castedBlock, struct Octree* octree);

void castRightShadow(struct CameraData* cameraData, struct CastedBlock* castedBlock, struct Octree* octree);

void castLeftShadow(struct CameraData* cameraData, struct CastedBlock* castedBlock, struct Octree* octree);

void castBlock(struct CameraData* cameraData, struct CastedBlock* castedBlock);

#endif //EDIFICE_RAYCASTER_H
