//
// Created by Spencer on 5/14/2024.
//

#ifndef EDIFICE_RAYCASTER_H
#define EDIFICE_RAYCASTER_H

void castRightShadow(struct CameraData* cameraData, struct CastedBlock* castedBlock);

void castLeftShadow(struct CameraData* cameraData, struct CastedBlock* castedBlock);

void castBlock(struct CameraData* cameraData, struct CastedBlock* castedBlock);

#endif //EDIFICE_RAYCASTER_H
