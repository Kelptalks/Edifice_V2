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
                castedBlock->leftShader = RightTopFace;
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
                castedBlock->rightShader = RightBotFace;
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
                castedBlock->rightShader = TopBotRight;
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
                    castedBlock->rightShader = TopTopRight;
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

    if ((castedBlock->leftTextureList->nodes[castedBlock->leftTextureList->length - 1].texture) == TopLeftFace){
        while (drawDistance > 0){
            drawDistance--;
            //z++
            key = modAxis(key, 1, 2, 0);
            block = getOctreeKeyVal(octree->root, key, octree->RootDepth);
            if (!(isTransparent(block) || isTranslucent(block))){
                castedBlock->leftShader = TopLeftFace;
                break;
            }

            //y++ side
            unsigned long keyY = modAxis(key, 1, 1, 0);
            block = getOctreeKeyVal(octree->root, keyY, octree->RootDepth);
            if (!(isTransparent(block) || isTranslucent(block))){
                castedBlock->leftShader = TopBotLeft;
            }

            //x-- side
            key = modAxis(key, -1, 0, 0);
            block = getOctreeKeyVal(octree->root, key, octree->RootDepth);
            if (!(isTransparent(block) || isTranslucent(block))){
                if (castedBlock->leftShader == TopBotLeft){
                    castedBlock->leftShader = TopLeftFace;
                    break;
                }
                else {
                    castedBlock->leftShader = TopTopLeft;
                }
            }

            //diagonal side
            key = modAxis(key, 1, 1, 0);
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