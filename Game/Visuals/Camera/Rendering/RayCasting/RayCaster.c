//
// Created by Spencer on 5/14/2024.
//

#include "../TextureManager/IsoTextureManager.h"
#include "../../../../Blocks/Blocks.h"
#include "../../../../World/Octree/OctreeNode.h"
#include "../../../../World/Octree/Tools/KeyMod.h"
#include "../../CameraData.h"
#include "../../../../World/Octree/Octree.h"
#include "../../../../Debuging/Test_Main.h"
#include "RayCastingManager.h"
#include "../../../../World/World.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * RayCasting
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

void castBlock(struct CameraData* cameraData, struct CastedBlock* castedBlock) {
    int currentX = castedBlock->worldX;
    int currentY = castedBlock->worldY;
    int currentZ = castedBlock->worldZ;

    struct World* world = cameraData->world;

    short currentBlock = 0;

    int leftX = currentX;
    int leftY = currentY;
    int leftZ = currentZ;
    bool leftFaceStruck = false;

    int rightX = currentX;
    int rightY = currentY;
    int rightZ = currentZ;
    bool rightFaceStruck = false;

    for (int d = 0; d < cameraData->castingDistance; d++) {
        //RightModdedKey to check if leftFace was struck
        //x--
        leftX = currentX - cameraData->xDirection;
        currentBlock = getBlockAtWorldCor(world, leftX, leftY, leftZ);

        //Check if face has already been struck
        if (!isTransparent(currentBlock) && !leftFaceStruck) {
            if (isTranslucent(currentBlock)){
                addTexture(castedBlock->leftTextureList, currentBlock, RightTopFace);
            }
            else {
                addTexture(castedBlock->leftTextureList, currentBlock, RightTopFace);
                if (cameraData->direction == North || cameraData->direction == West) {
                    castedBlock->leftShader = RightTopFace;
                    castedBlock->worldLeftBlockX = leftX;
                    castedBlock->worldLeftBlockY = leftY;
                    castedBlock->worldLeftBlockZ = leftZ;
                    leftFaceStruck = true;
                }
            }
        }

        //LeftModded key to check if rightFace was struck
        //y--
        //Check if face has already been struck
        rightY = currentY - cameraData->yDirection;
        currentBlock = getBlockAtWorldCor(world, rightX, rightY, rightZ);

        if (!isTransparent(currentBlock) && !rightFaceStruck) {
            if (isTranslucent(currentBlock)){
                addTexture(castedBlock->rightTextureList, currentBlock, LeftTopFace);
            }
            else {
                addTexture(castedBlock->rightTextureList, currentBlock, LeftTopFace);
                if (cameraData->direction == South || cameraData->direction == West) {
                    castedBlock->rightShader = LeftTopFace;
                }
                castedBlock->worldRightBlockX = rightX;
                castedBlock->worldRightBlockY = rightY;
                castedBlock->worldRightBlockZ = rightZ;
                rightFaceStruck = true;
            }
        }



        //x-- & y--
        //Check block behind diagonaly shaired by both left and right triangles of the casted block
        currentX -= cameraData->xDirection;
        currentY -= cameraData->yDirection;

        currentBlock = getBlockAtWorldCor(world, currentX, currentY, currentZ);
        if (!isTransparent(currentBlock)) {
            //If left face has not been struck update texture
            if (!leftFaceStruck) {
                if (isTranslucent(currentBlock)){
                    addTexture(castedBlock->leftTextureList, currentBlock, LeftBotFace);
                }
                else {
                    addTexture(castedBlock->leftTextureList, currentBlock, LeftBotFace);
                    if (cameraData->direction == South || cameraData->direction == West) {
                        castedBlock->leftShader = LeftBotFace;
                    }
                    castedBlock->worldLeftBlockX = currentX;
                    castedBlock->worldLeftBlockY = currentY;
                    castedBlock->worldLeftBlockZ = currentZ;
                    leftFaceStruck = true;
                }
            }

            //If right face has not been struck update texture
            if (!rightFaceStruck) {
                if (isTranslucent(currentBlock)){
                    addTexture(castedBlock->rightTextureList, currentBlock, RightBotFace);
                }
                else {
                    addTexture(castedBlock->rightTextureList, currentBlock, RightBotFace);
                    if (cameraData->direction == North || cameraData->direction == West) {
                        castedBlock->rightShader = RightBotFace;
                    }
                    castedBlock->worldRightBlockX = currentX;
                    castedBlock->worldRightBlockY = currentY;
                    castedBlock->worldRightBlockZ = currentZ;
                    rightFaceStruck = true;
                }
            }
        }



        //z--
        //Check if top face has been struck
        currentZ -= 1;

        currentBlock = getBlockAtWorldCor(world, currentX, currentY, currentZ);
        if (!isTransparent(currentBlock)) {
            if (!leftFaceStruck) {
                if (isTranslucent(currentBlock)){
                    addTexture(castedBlock->leftTextureList, currentBlock, TopLeftFace);
                }
                else {
                    addTexture(castedBlock->leftTextureList, currentBlock, TopLeftFace);
                    castedBlock->worldLeftBlockX = currentX;
                    castedBlock->worldLeftBlockY = currentY;
                    castedBlock->worldLeftBlockZ = currentZ;
                    leftFaceStruck = true;
                }
            }

            if (!rightFaceStruck) {
                if (isTranslucent(currentBlock)){
                    addTexture(castedBlock->rightTextureList, currentBlock, TopRightFace);
                }
                else {
                    addTexture(castedBlock->rightTextureList, currentBlock, TopRightFace);
                    castedBlock->worldRightBlockX = currentX;
                    castedBlock->worldRightBlockY = currentY;
                    castedBlock->worldRightBlockZ = currentZ;
                    rightFaceStruck = true;
                }
            }
        }


        leftX = currentX;
        leftY = currentY;
        leftZ = currentZ;

        rightX = currentX;
        rightY = currentY;
        rightZ = currentZ;


        //If both faces have been struck end loop
        if (leftFaceStruck && rightFaceStruck) {
            //reportBug("test\n");
            break;
        }
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Shadow casting
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */


void castRightShadow(struct CameraData* cameraData, struct CastedBlock* castedBlock) {
    int currentX = castedBlock->worldRightBlockX;
    int currentY = castedBlock->worldRightBlockY;
    int currentZ = castedBlock->worldRightBlockZ;

    struct World* world = cameraData->world;

    short block = 0;
    int drawDistance = 300;

    if ((castedBlock->rightTextureList->nodes[castedBlock->rightTextureList->length - 1].texture) == TopRightFace){
        while (drawDistance > 0){
            drawDistance--;
            //z++
            currentZ++;

            block = getBlockAtWorldCor(world, currentX, currentY, currentZ);
            if (!(isTransparent(block) || isTranslucent(block))){
                castedBlock->rightShader = TopRightFace;
                break;
            }

            //y++ side
            int tempY = currentY + 1;
            block = getBlockAtWorldCor(world, currentX, tempY, currentZ);
            if (!(isTransparent(block) || isTranslucent(block))){
                //South
                if (cameraData->direction == South){
                    if (castedBlock->rightShader == TopBotRight) {
                        castedBlock->rightShader = TopRightFace;
                    }
                    else {
                        castedBlock->rightShader = TopTopRight;
                    }
                }
                //West
                else if (cameraData->direction == West){
                    castedBlock->rightShader = TopRightFace;
                }
                //North
                else {
                    if (castedBlock->rightShader == TopTopRight) {
                        castedBlock->rightShader = TopRightFace;
                    } else {
                        castedBlock->rightShader = TopBotRight;
                    }
                }
            }

            //x-- side
            currentX--;
            block = getBlockAtWorldCor(world, currentX, currentY, currentZ);
            if (!(isTransparent(block) || isTranslucent(block))){
                if (castedBlock->rightShader == TopBotRight){
                    castedBlock->rightShader = TopRightFace;
                    break;
                }
                else {
                    if (cameraData->direction == South){
                        castedBlock->rightShader = TopBotRight;
                    }
                    else if (cameraData->direction == West){
                        //castedBlock->leftShader = TopTopLeft;
                    }
                    else {
                        castedBlock->rightShader = TopTopRight;
                    }
                }
            }

            //diagonal side
            currentY++;
            block = getBlockAtWorldCor(world, currentX, currentY, currentZ);
            if (!(isTransparent(block) || isTranslucent(block))){
                castedBlock->rightShader = TopRightFace;
                break;
            }
        }
    }

    if ((castedBlock->rightTextureList->nodes[castedBlock->rightTextureList->length - 1].texture) == LeftTopFace){
        while (drawDistance > 0){
            drawDistance--;

            currentX--;
            currentY++;

            block = getBlockAtWorldCor(world, currentX, currentY, currentZ);

            if (!(isTransparent(block) || isTranslucent(block))){
                castedBlock->rightShader = LeftWest;
                currentZ++;
                block = getBlockAtWorldCor(world, currentX, currentY, currentZ);
                if (!(isTransparent(block) || isTranslucent(block))){
                    castedBlock->rightShader = LeftTopFace;
                    break;
                }
                currentZ--;
            }
            currentZ++;
        }
    }
}


void castLeftShadow(struct CameraData* cameraData, struct CastedBlock* castedBlock) {
    int currentX = castedBlock->worldLeftBlockX;
    int currentY = castedBlock->worldLeftBlockY;
    int currentZ = castedBlock->worldLeftBlockZ;

    struct World* world = cameraData->world;

    short block = 0;
    int drawDistance = 300;

    if ((castedBlock->leftTextureList->nodes[castedBlock->leftTextureList->length - 1].texture) == TopLeftFace){
        while (drawDistance > 0){
            drawDistance--;
            //z++
            currentZ++;
            block = getBlockAtWorldCor(world, currentX, currentY, currentZ);
            if (!(isTransparent(block) || isTranslucent(block))){
                castedBlock->leftShader = TopLeftFace;
                break;
            }

            //y++ side
            int tempY = currentY + 1;
            block = getBlockAtWorldCor(world, currentX, tempY, currentZ);
            if (!(isTransparent(block) || isTranslucent(block))){
                if (cameraData->direction == South){
                    if (castedBlock->leftShader == TopBotLeft) {
                        castedBlock->leftShader = TopLeftFace;
                    }
                    else {
                        castedBlock->leftShader = TopTopLeft;
                    }
                }
                else if (cameraData->direction == West){
                    //castedBlock->rightShader = ;
                }
                else {
                    if (castedBlock->leftShader == TopTopLeft) {
                        castedBlock->leftShader = TopLeftFace;
                    } else {
                        castedBlock->leftShader = TopBotLeft;
                    }
                }
            }

            //x-- side
            currentX--;
            block = getBlockAtWorldCor(world, currentX, currentY, currentZ);
            if (!(isTransparent(block) || isTranslucent(block))){
                if (castedBlock->leftShader == TopBotLeft){
                    castedBlock->leftShader = TopLeftFace;
                    break;
                }
                else {
                    if (cameraData->xDirection == - 1 && cameraData->yDirection == -1){
                        castedBlock->leftShader = TopBotLeft;
                    }
                    else if (cameraData->direction == West){
                        castedBlock->leftShader = TopLeftFace;
                    }
                    else {

                        castedBlock->leftShader = TopTopLeft;
                    }
                }
            }

            //diagonal side
            currentY++;
            block = getBlockAtWorldCor(world, currentX, currentY, currentZ);
            if (!(isTransparent(block) || isTranslucent(block))){
                castedBlock->leftShader = TopLeftFace;
                break;
            }
        }
    }

    if ((castedBlock->leftTextureList->nodes[castedBlock->leftTextureList->length - 1].texture) == LeftBotFace){
        while (drawDistance > 0){
            drawDistance--;
            currentX--;
            currentY++;

            block = getBlockAtWorldCor(world, currentX, currentY, currentZ);

            if (!(isTransparent(block) || isTranslucent(block))){
                castedBlock->leftShader = LeftSouth;
                currentZ++;
                block = getBlockAtWorldCor(world, currentX, currentY, currentZ);
                if (!(isTransparent(block) || isTranslucent(block))){
                    castedBlock->leftShader = LeftBotFace;
                    break;
                }
                currentZ--;
            }
            currentZ++;
        }
    }
}