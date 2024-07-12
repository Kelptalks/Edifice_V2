//
// Created by Spencer on 7/10/2024.
//


#include "../../../../../GameData.h"
#include "../CastedBlockManager.h"
#include "../../../IsoCordTool/IsoCordManager.h"
#include "../../../CameraData.h"

void highLightMouseCord(struct GameData* gameData, int xIso, int yIso, bool leftSided){

    //clear all temp texture lists in vicinity
    struct CastedBlock* tempCastedBlock;
    for (int x = -4; x < 4; x++){
        for (int y = -4; y < 4; y++){
            tempCastedBlock = getCastedBlockAtCords(gameData->cameraData, xIso + x, yIso + y);
            if (tempCastedBlock != NULL) {
                clearTextureList(tempCastedBlock->leftTempTextureList);
                clearTextureList(tempCastedBlock->rightTemptTextureList);
            }
        }
    }


    //Set textures
    struct CastedBlock* castedBlock = getCastedBlockAtCords(gameData->cameraData, xIso, yIso);
    if (castedBlock != NULL) {
        if (leftSided) {
            addTexture(castedBlock->leftTempTextureList, WhiteShader, TopLeftFace);
        } else {
            addTexture(castedBlock->rightTemptTextureList, WhiteShader, TopRightFace);
        }
    }

}