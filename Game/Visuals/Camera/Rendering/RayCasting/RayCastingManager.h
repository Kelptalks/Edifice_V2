//
// Created by Spencer on 5/14/2024.
//

#ifndef EDIFICE_RAYCASTINGMANAGER_H
#define EDIFICE_RAYCASTINGMANAGER_H

void rayCastBlock(struct CastedBlock* castedBlock, struct Octree* octree);

void rayCastChunk(struct CastedChunk* castedChunk, struct Octree* octree);

void threadCastChunk(struct CastedChunk* castedChunk, struct Octree* octree);

#endif //EDIFICE_RAYCASTINGMANAGER_H
