//
// Created by Spencer on 5/6/2024.
//

#ifndef EDIFICE_CAMERA_H
#define EDIFICE_CAMERA_H

#include "CameraData.h"

void setDirection(struct CameraData* cameraData, enum Direction direction);

void rotateCamLeft(struct CameraData* cameraData);
void rotateCamRight(struct CameraData* cameraData);

void updateCameraCords(struct GameData* gameData);

void renderCastedBlock(struct GameData* gameData, struct CastedBlock* castedBlock, int x, int y, int side);
void clearChunkTexture(struct GameData* gameData, struct CastedChunk* castedChunk);

void renderView(struct GameData* gameData);
void clearCameraRendering(struct GameData* gameData);

#endif //EDIFICE_CAMERA_H
