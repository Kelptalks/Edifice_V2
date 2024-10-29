//
// Created by Spencer on 10/29/2024.
//

#ifndef GPUCASTINGDATA_H
#define GPUCASTINGDATA_H

#include "../../../../CastedBlockManager/CastedBlockManager.h"

struct CastedBlocksSendData {
    int maxCastedBlocks;
    int totalCastedBlocks;

    int* chunkXCor;
    int* chunkYCor;
    int* chunkArrayPosition;

    int* castedBlockXCords;
    int* castedBlockYCords;
    int* castedBlockZCords;
};

struct CastedBlocksSendData* createCastedBlocksSendData(int maxCastedBlocks);

void clearCastedBlockSendData(struct CastedBlocksSendData* castedBlocksSendData);

void addCastedChunkToSendData(struct CastedBlocksSendData* castedBlocksSendData, const struct CastedChunk* castedChunk);

struct CastedBlockReturnData {
    int totalCastedBlocks;
    int totalTransparentTextures;

    int* triangleTypes;
    int* blockTypes;
};

#endif //GPUCASTINGDATA_H
