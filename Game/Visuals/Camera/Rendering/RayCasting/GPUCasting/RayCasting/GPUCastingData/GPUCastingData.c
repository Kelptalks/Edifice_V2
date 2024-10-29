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