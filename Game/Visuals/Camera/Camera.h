//
// Created by Spencer on 5/6/2024.
//

#ifndef EDIFICE_CAMERA_H
#define EDIFICE_CAMERA_H

#include "CameraData.h"

void setDirection(struct CameraData* cameraData, enum Direction direction);

void updateCameraCords(struct GameData* gameData);

void renderView(struct GameData* gameData, int x, int y);

#endif //EDIFICE_CAMERA_H
