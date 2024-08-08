//
// Created by Spencer on 8/7/2024.
//

#ifndef EDIFICE_UIRENDERER_H
#define EDIFICE_UIRENDERER_H

#include "../../../../../GameData.h"
#include "../../../../Camera/Rendering/TextureManager/IsoTextureManager.h"

void renderXBox(struct GameData* gameData, bool pressed, int xCor, int yCor, int xScale, int yScale);

void renderCheckBox(struct GameData* gameData, bool pressed, int xCor, int yCor, int xScale, int yScale);

void renderForwardBox(struct GameData* gameData, bool pressed, int xCor, int yCor, int xScale, int yScale);

void renderBackBox(struct GameData* gameData, bool pressed, int xCor, int yCor, int xScale, int yScale);

void renderScrollBar(struct GameData* gameData, int xCor, int yCor, int xScale, int yScale);

void renderScrollPointer(struct GameData* gameData, bool pressed, int xCor, int yCor, int xScale, int yScale);

#endif //EDIFICE_UIRENDERER_H
