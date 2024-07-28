//
// Created by Spencer on 5/14/2024.
//

#include "../TextureManager/IsoTextureManager.h"
#include "../../../../Blocks/Blocks.h"
#include "../../../../World/Octree/OctreeNode.h"
#include "../../../../World/Octree/KeyMod.h"
#include "../../CameraData.h"
#include "../../../../World/Octree/Octree.h"
#include "../../../../Debuging/Test_Main.h"
#include "RayCastingManager.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Casting blocks
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

void castLeftTriangle(struct CameraData* cameraData, struct CastedBlock* castedBlock, struct Octree* octree) {
    int drawDistance = 300;
    short block = 0;
    unsigned long key = castedBlock->camKey;

    while (drawDistance > 0){
        drawDistance--;

        //-x
        key = modAxis(key, -1 * cameraData->xDirection, 0, 0);
        block = getOctreeKeyVal(octree->root, key, octree->RootDepth);

        if (!isTransparent(block)){
            if (isTranslucent(block)){
                addTexture(castedBlock->leftTextureList, block, RightTopFace);
            }
            else {
                addTexture(castedBlock->leftTextureList, block, RightTopFace);
                if (cameraData->direction == North || cameraData->direction == West) {
                    castedBlock->leftShader = RightTopFace;
                }
                break;
            }
        }

        //-y
        key = modAxis(key, -1 * cameraData->yDirection, 1, 0);
        block = getOctreeKeyVal(octree->root, key, octree->RootDepth);

        if (!isTransparent(block)){
            if (isTranslucent(block)){
                addTexture(castedBlock->leftTextureList, block, LeftBotFace);
            }
            else {
                addTexture(castedBlock->leftTextureList, block, LeftBotFace);
                if (cameraData->direction == South || cameraData->direction == West) {
                    castedBlock->leftShader = LeftBotFace;
                }
                break;
            }
        }

        //-z
        key = modAxis(key, -1, 2, 0);
        block = getOctreeKeyVal(octree->root, key, octree->RootDepth);

        if (!isTransparent(block)){
            if (isTranslucent(block)){
                addTexture(castedBlock->leftTextureList, block, TopLeftFace);
            }
            else {
                addTexture(castedBlock->leftTextureList, block, TopLeftFace);
                break;
            }
        }
    }
    castedBlock->leftBlockKey = key;
}

void castRightTriangle(struct CameraData* cameraData, struct CastedBlock* castedBlock, struct Octree* octree){
    unsigned long key = castedBlock->camKey;
    int drawDistance = 300;
    short block = 0;

    while (drawDistance > 0){
        drawDistance--;
        //-y
        key = modAxis(key, -1 * cameraData->yDirection, 1, 0);
        block = getOctreeKeyVal(octree->root, key, octree->RootDepth);
        if (!isTransparent(block)){
            if (isTranslucent(block)){
                addTexture(castedBlock->rightTextureList, block, LeftTopFace);
            }
            else {
                addTexture(castedBlock->rightTextureList, block, LeftTopFace);
                if (cameraData->direction == South || cameraData->direction == West) {
                    castedBlock->rightShader = LeftTopFace;
                }
                break;
            }
        }

        //-x
        key = modAxis(key, -1 * cameraData->xDirection, 0, 0);
        block = getOctreeKeyVal(octree->root, key, octree->RootDepth);
        if (!isTransparent(block)){
            if (isTranslucent(block)){
                addTexture(castedBlock->rightTextureList, block, RightBotFace);
            }
            else {
                addTexture(castedBlock->rightTextureList, block, RightBotFace);
                if (cameraData->direction == North || cameraData->direction == West) {
                    castedBlock->rightShader = RightBotFace;
                }
                break;
            }
        }

        //-z
        key = modAxis(key, -1, 2, 0);
        block = getOctreeKeyVal(octree->root, key, octree->RootDepth);
        if (!isTransparent(block)){
            if (isTranslucent(block)){
                addTexture(castedBlock->rightTextureList, block, TopRightFace);
            }
            else {
                addTexture(castedBlock->rightTextureList, block, TopRightFace);
                break;
            }
        }
    }
    castedBlock->rightBlockKey = key;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Shadow casting
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

void castRightShadow(struct CameraData* cameraData, struct CastedBlock* castedBlock, struct Octree* octree) {
    unsigned long key = castedBlock->rightBlockKey;
    short block = 0;
    int drawDistance = 300;
    int* castingOrder = cameraData->rayCastingData->rightOrder;

    if ((castedBlock->rightTextureList->nodes[castedBlock->rightTextureList->length - 1].texture) == TopRightFace){
        while (drawDistance > 0){
            drawDistance--;
            //z++
            key = modAxis(key, 1, 2, 0);
            block = getOctreeKeyVal(octree->root, key, octree->RootDepth);
            if (!(isTransparent(block) || isTranslucent(block))){
                castedBlock->rightShader = TopRightFace;
                break;
            }

            //y++ side
            unsigned long keyY = modAxis(key, 1, 1, 0);
            block = getOctreeKeyVal(octree->root, keyY, octree->RootDepth);
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
            key = modAxis(key, -1, 0, 0);
            block = getOctreeKeyVal(octree->root, key, octree->RootDepth);
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
            key = modAxis(key, 1, 1, 0);
            block = getOctreeKeyVal(octree->root, key, octree->RootDepth);
            if (!(isTransparent(block) || isTranslucent(block))){
                castedBlock->rightShader = TopRightFace;
                break;
            }
        }
    }

    if ((castedBlock->rightTextureList->nodes[castedBlock->rightTextureList->length - 1].texture) == LeftTopFace){
        while (drawDistance > 0){
            drawDistance--;

            key = modKey(key, -1, 1, 0, 0);
            block = getOctreeKeyVal(octree->root, key, octree->RootDepth);

            if (!(isTransparent(block) || isTranslucent(block))){
                castedBlock->rightShader = LeftWest;
                key = modAxis(key, 1, 2, 0);
                block = getOctreeKeyVal(octree->root, key, octree->RootDepth);
                if (!(isTransparent(block) || isTranslucent(block))){
                    castedBlock->rightShader = LeftTopFace;
                    break;
                }
            }
            key = modAxis(key, 1, 2, 0);
        }
    }
}

void castLeftShadow(struct CameraData* cameraData, struct CastedBlock* castedBlock, struct Octree* octree) {
    unsigned long key = castedBlock->leftBlockKey;
    short block = 0;
    int drawDistance = 300;
    int* castingOrder = cameraData->rayCastingData->leftOrder;

    if ((castedBlock->leftTextureList->nodes[castedBlock->leftTextureList->length - 1].texture) == TopLeftFace){
        while (drawDistance > 0){
            drawDistance--;
            //z++
            key = modAxis(key, 1, castingOrder[0], 0);
            block = getOctreeKeyVal(octree->root, key, octree->RootDepth);
            if (!(isTransparent(block) || isTranslucent(block))){
                castedBlock->leftShader = TopLeftFace;
                break;
            }

            //y++ side
            unsigned long keyY = modAxis(key, 1, castingOrder[1], 0);
            block = getOctreeKeyVal(octree->root, keyY, octree->RootDepth);
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
            key = modAxis(key, -1, castingOrder[2], 0);
            block = getOctreeKeyVal(octree->root, key, octree->RootDepth);
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
            key = modAxis(key, 1, castingOrder[1], 0);
            block = getOctreeKeyVal(octree->root, key, octree->RootDepth);
            if (!(isTransparent(block) || isTranslucent(block))){
                castedBlock->leftShader = TopLeftFace;
                break;
            }
        }
    }

    if ((castedBlock->leftTextureList->nodes[castedBlock->leftTextureList->length - 1].texture) == LeftBotFace){
        while (drawDistance > 0){
            drawDistance--;

            key = modKey(key, -1, 1, 0, 0);
            block = getOctreeKeyVal(octree->root, key, octree->RootDepth);

            if (!(isTransparent(block) || isTranslucent(block))){
                castedBlock->leftShader = LeftSouth;
                key = modAxis(key, 1, 2, 0);
                block = getOctreeKeyVal(octree->root, key, octree->RootDepth);
                if (!(isTransparent(block) || isTranslucent(block))){
                    castedBlock->leftShader = LeftBotFace;
                    break;
                }
            }
            key = modAxis(key, 1, 2, 0);
        }
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Octree RayCasting
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

void castBlock(struct CameraData* cameraData, struct CastedBlock* castedBlock) {
    int octreeDepth = cameraData->octree->RootDepth;
    unsigned long currentKey = castedBlock->camKey;

    struct Octree* octree = cameraData->octree;
    struct OctreeNode* octreeNode = cameraData->octree->root;
    short currentBlock = 0;

    unsigned long leftModdedKey = 0;
    bool leftFaceStruck = false;

    unsigned long rightModdedKey = 0;
    bool rightFaceStruck = false;

    for (int d = 0; d < cameraData->castingDistance; d++) {
        //RightModdedKey to check if leftFace was struck
        //x--
        leftModdedKey = modAxis(currentKey, -1 * cameraData->xDirection, 0, 0);
        currentBlock = getOctreeKeyVal(octreeNode, leftModdedKey, octreeDepth);
        //Check if face has already been struck
        if (!isTransparent(currentBlock) && !leftFaceStruck) {
            if (isTranslucent(currentBlock)){
                addTexture(castedBlock->leftTextureList, currentBlock, RightTopFace);
            }
            else {
                addTexture(castedBlock->leftTextureList, currentBlock, RightTopFace);
                if (cameraData->direction == North || cameraData->direction == West) {
                    castedBlock->leftShader = RightTopFace;
                    castedBlock->leftBlockKey = leftModdedKey;
                    leftFaceStruck = true;
                }
            }
        }

        //LeftModded key to check if rightFace was struck
        //y--
        //Check if face has already been struck
        rightModdedKey = modAxis(currentKey, -1 * cameraData->yDirection, 1, 0);
        currentBlock = getOctreeKeyVal(octreeNode, rightModdedKey, octreeDepth);
        if (!isTransparent(currentBlock) && !rightFaceStruck) {
            if (isTranslucent(currentBlock)){
                addTexture(castedBlock->rightTextureList, currentBlock, LeftTopFace);
            }
            else {
                addTexture(castedBlock->rightTextureList, currentBlock, LeftTopFace);
                if (cameraData->direction == South || cameraData->direction == West) {
                    castedBlock->rightShader = LeftTopFace;
                }
                castedBlock->rightBlockKey = rightModdedKey;
                rightFaceStruck = true;
            }
        }



        //x-- & y--
        //Check block behind diagonaly shaired by both left and right triangles of the casted block
        currentKey = modAxis(leftModdedKey, -1 * cameraData->yDirection, 1, 0);
        currentBlock = getOctreeKeyVal(octreeNode, currentKey, octreeDepth);
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
                    castedBlock->leftBlockKey = currentKey;
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
                    castedBlock->rightBlockKey = currentKey;
                    rightFaceStruck = true;
                }
            }
        }



        //z--
        //Check if top face has been struck
        currentKey = modAxis(currentKey, -1, 2, 0);
        currentBlock = getOctreeKeyVal(octreeNode, currentKey, octreeDepth);
        if (!isTransparent(currentBlock)) {
            if (!leftFaceStruck) {
                if (isTranslucent(currentBlock)){
                    addTexture(castedBlock->leftTextureList, currentBlock, TopLeftFace);
                }
                else {
                    addTexture(castedBlock->leftTextureList, currentBlock, TopLeftFace);
                    castedBlock->leftBlockKey = currentKey;
                    leftFaceStruck = true;
                }
            }

            if (!rightFaceStruck) {
                if (isTranslucent(currentBlock)){
                    addTexture(castedBlock->rightTextureList, currentBlock, TopRightFace);
                }
                else {
                    addTexture(castedBlock->rightTextureList, currentBlock, TopRightFace);
                    castedBlock->rightBlockKey = currentKey;
                    rightFaceStruck = true;
                }
            }
        }


        //If both faces have been struck end loop
        if (leftFaceStruck && rightFaceStruck) {
            //reportBug("test\n");
            break;
        }
    }
}