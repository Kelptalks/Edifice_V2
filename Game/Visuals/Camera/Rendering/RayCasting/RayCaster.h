//
// Created by Spencer on 5/14/2024.
//

#ifndef EDIFICE_RAYCASTER_H
#define EDIFICE_RAYCASTER_H

void castLeftTriangle(struct CastedBlock* castedBlock, struct Octree* octree);

void castRightTriangle(struct CastedBlock* castedBlock, struct Octree* octree);

void castRightShadow(struct CastedBlock* castedBlock, struct Octree* octree);

void castLeftShadow(struct CastedBlock* castedBlock, struct Octree* octree);

#endif //EDIFICE_RAYCASTER_H
