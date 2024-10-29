//
// Created by Spencer on 10/29/2024.
//

#include "GPUCastingData.h"

#include <stdlib.h>

#include "../../../../../../../Debuging/Test_Main.h"

struct CastedBlocksSendData* createCastedBlocksSendData(int maxCastedBlocks) {
    //Setup struct
    struct CastedBlocksSendData* castedBlockSendData = malloc(sizeof(struct CastedBlocksSendData));
    if (castedBlockSendData == NULL) {
        reportBug("Failed to mall casted block send Data\n");
        return NULL;
    }

    castedBlockSendData->maxCastedBlocks = maxCastedBlocks;
    castedBlockSendData->totalCastedBlocks = 0;

    //Allocate arrays
    castedBlockSendData->chunkXCor = calloc(maxCastedBlocks, sizeof(int));
    castedBlockSendData->chunkYCor = calloc(maxCastedBlocks, sizeof(int));
    castedBlockSendData->chunkArrayPosition = calloc(maxCastedBlocks, sizeof(int));

    castedBlockSendData->castedBlockXCords = calloc(maxCastedBlocks, sizeof(int));
    castedBlockSendData->castedBlockYCords = calloc(maxCastedBlocks, sizeof(int));
    castedBlockSendData->castedBlockZCords = calloc(maxCastedBlocks, sizeof(int));


    return castedBlockSendData;
}

void clearCastedBlockSendData(struct CastedBlocksSendData* castedBlocksSendData) {
    castedBlocksSendData->totalCastedBlocks = 0;
}

void addCastedChunkToSendData(struct CastedBlocksSendData* castedBlocksSendData, const struct CastedChunk* castedChunk) {
    int castedBlocksPerChunk = castedChunk->scale * castedChunk->scale;

    // Don't add chunk if max cast Block reached
    if (castedBlocksSendData->totalCastedBlocks >= castedBlocksSendData->maxCastedBlocks) {
        reportBug("ERROR, To many casted blocks! \n");
        return;
    }

    //Copy data from each cast block into array
    for (int t = 0; t < castedBlocksPerChunk; t++) {
        //Copy chunk cords
        castedBlocksSendData->chunkXCor[castedBlocksSendData->totalCastedBlocks] = castedChunk->isoX;
        castedBlocksSendData->chunkYCor[castedBlocksSendData->totalCastedBlocks] = castedChunk->isoY;
        castedBlocksSendData->chunkArrayPosition[castedBlocksSendData->totalCastedBlocks] = t;

        //Copy CastedBlock data to new array
        castedBlocksSendData->castedBlockXCords[castedBlocksSendData->totalCastedBlocks] = castedChunk->castedBlocks[t].worldX;
        castedBlocksSendData->castedBlockYCords[castedBlocksSendData->totalCastedBlocks] = castedChunk->castedBlocks[t].worldY;
        castedBlocksSendData->castedBlockZCords[castedBlocksSendData->totalCastedBlocks] = castedChunk->castedBlocks[t].worldZ;

        //Update totalCastedBlocksToSend
        castedBlocksSendData->totalCastedBlocks++;
    }
}


struct CastedBlockReturnData* createCastedBlockReturnData(int maxCastedBlocks, int textureArrayLength) {
    struct CastedBlockReturnData* castedBlockReturnData = malloc(sizeof(struct CastedBlocksSendData));
    if (castedBlockReturnData == NULL) {
        reportBug("Failed to malloc casted block return Data\n");
        return NULL;
    }

    castedBlockReturnData->maxCastedBlocks = maxCastedBlocks;
    castedBlockReturnData->totalCastedBlocks = 0;

    //Textures
    castedBlockReturnData->textureArrayLength = textureArrayLength;
    castedBlockReturnData->leftBlockTypes = calloc(maxCastedBlocks * textureArrayLength, sizeof(int));
    castedBlockReturnData->leftTriangleTypes = calloc(maxCastedBlocks * textureArrayLength, sizeof(int));
    castedBlockReturnData->rightBlockTypes = calloc(maxCastedBlocks * textureArrayLength, sizeof(int));
    castedBlockReturnData->rightTriangleTypes = calloc(maxCastedBlocks * textureArrayLength, sizeof(int));


    return castedBlockReturnData;
}

void clearCastedBlockReturnData(struct CastedBlockReturnData* castedBlockReturnData) {

    for (int i = 0; i < castedBlockReturnData->totalCastedBlocks; i++) {
        castedBlockReturnData->leftBlockTypes[i] = 0;
        castedBlockReturnData->rightBlockTypes[i] = 0;
    }
    castedBlockReturnData->totalCastedBlocks = 0;

}

void unPackBlockReturnData(struct CastedBlockReturnData* castedBlockReturnData, struct CastedBlocksSendData* castedBlocksSendData, struct CastedPool* castedPool) {
    //Loop through all returned CastedBlocks;
    int currentChunkXCor = castedBlocksSendData->chunkXCor[0];
    int currentChunkYCor = castedBlocksSendData->chunkYCor[0];
    struct CastedChunk* currentCastedChunk = getChunkFromMap(castedPool->chunkMap, currentChunkXCor, currentChunkYCor);


    for (int i = 0; i < castedBlockReturnData->totalCastedBlocks; i++) {
        //Only getChunk from map when needed to reduce performance cost
        //If chunk location has changed update it
        const int chunkXCor = castedBlocksSendData->chunkXCor[i];
        const int chunkYCor = castedBlocksSendData->chunkYCor[i];
        if (currentChunkXCor != chunkXCor || currentChunkYCor != chunkYCor) {
            currentChunkXCor = chunkXCor;
            currentChunkYCor = chunkYCor;
            currentCastedChunk = getChunkFromMap(castedPool->chunkMap, currentChunkXCor, currentChunkYCor);
            currentCastedChunk->rayCast = true;
        }

        int castedBlockArrayPos = castedBlocksSendData->chunkArrayPosition[i];


        currentCastedChunk->rayCast = true;
        struct CastedBlock castedBlock = currentCastedChunk->castedBlocks[castedBlockArrayPos];
        //Clear Texture lists
        clearTextureList(castedBlock.leftTextureList);
        clearTextureList(castedBlock.rightTextureList);


        bool leftFinished = false;
        bool rightFinished = false;
        for (int t = 0; t < castedBlockReturnData->textureArrayLength; t++) {
            int returnTextureArrayIndex = i * castedBlockReturnData->textureArrayLength + t;
            int leftBlockTypeOfTexture = castedBlockReturnData->leftBlockTypes[returnTextureArrayIndex];
            int leftTriangleTypeOfTexture = castedBlockReturnData->leftTriangleTypes[returnTextureArrayIndex];

            int rightBlockTypeOfTexture = castedBlockReturnData->rightBlockTypes[returnTextureArrayIndex];
            int rightTriangleTypeOfTexture = castedBlockReturnData->rightTriangleTypes[returnTextureArrayIndex];

            //If no textures are in the texture array in the CastedBlock;
            if (leftBlockTypeOfTexture == 0) {
                leftFinished = true;
            }
            if (rightBlockTypeOfTexture == 0) {
                rightFinished = true;
            }

            if (leftFinished && rightFinished) {
                break;
            }
            else{
                if (!leftFinished) {
                    addTexture(castedBlock.leftTextureList, leftBlockTypeOfTexture, leftTriangleTypeOfTexture);
                }
                if (!rightFinished) {
                    addTexture(castedBlock.rightTextureList, rightBlockTypeOfTexture, rightTriangleTypeOfTexture);
                }
            }
        }
    }
}