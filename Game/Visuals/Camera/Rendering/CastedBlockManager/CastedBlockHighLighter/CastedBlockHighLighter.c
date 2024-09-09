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
    for (int x = -16; x < 16; x++){
        for (int y = -16; y < 16; y++){
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
        int worldX;
        int worldY;
        int worldZ;


        if (leftSided) {
            worldX = castedBlock->worldLeftBlockX;
            worldY = castedBlock->worldLeftBlockY;
            worldZ = castedBlock->worldLeftBlockZ;
        }
        else{
            worldX = castedBlock->worldRightBlockX;
            worldY = castedBlock->worldRightBlockY;
            worldZ = castedBlock->worldRightBlockZ;
        }

        for (int x = -4; x < 4; x++) {
            for (int y = -4; y < 4; y++) {
                tempCastedBlock = getCastedBlockAtCords(gameData->cameraData, xIso + x, yIso + y);
                if (tempCastedBlock != NULL) {
                    if (worldX == tempCastedBlock->worldLeftBlockX && worldY == tempCastedBlock->worldLeftBlockY && worldZ == tempCastedBlock->worldLeftBlockZ) {
                        addTexture(tempCastedBlock->leftTempTextureList, WhiteShader, tempCastedBlock->leftTextureList->nodes[0].texture);
                    }
                    if (worldX == tempCastedBlock->worldRightBlockX && worldY == tempCastedBlock->worldRightBlockY && worldZ == tempCastedBlock->worldRightBlockZ) {
                        addTexture(tempCastedBlock->rightTemptTextureList, WhiteShader,  tempCastedBlock->rightTextureList->nodes[0].texture);
                    }
                }
            }
        }
    }
}