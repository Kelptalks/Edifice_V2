//
// Created by Spencer on 5/7/2024.
//

#include "CastedBlockManager.h"
#include "../../../../World/Octree/KeyMod.h"
#include "../../../../Debuging/Test_Main.h"

struct CastedBlock* createCastedBlock(){
    struct CastedBlock* castedBlock = malloc(sizeof (struct CastedBlock));
    castedBlock->leftTextureList = createTextureList();
    castedBlock->rightTextureList = createTextureList();
    castedBlock->leftShader = Empty;
    castedBlock->rightShader = Empty;
    return castedBlock;
}

struct CastedChunk* createCastedChunk(struct CameraData* cameraData, struct SDL_Renderer* renderer, int isoX, int isoY){
    struct CastedChunk* castedChunk = malloc(sizeof (struct CastedChunk));
    castedChunk->worldKey = modKey(cameraData->key, isoX * cameraData->chunksScale, isoY * cameraData->chunksScale, 0, 0);
    castedChunk->castedBlocks = malloc(sizeof (struct CastedBlock*) * cameraData->chunksScale);
    castedChunk->isoX = isoX;
    castedChunk->isoY = isoY;
    castedChunk->busy = false;
    castedChunk->rayCast = false;
    castedChunk->textured = false;
    castedChunk->scale = cameraData->chunksScale;

    //SetupCasted blocks
    for (int x = 0; x < cameraData->chunksScale; x++){
        castedChunk->castedBlocks[x] = malloc(sizeof (struct CastedBlock) * cameraData->chunksScale);
        for (int y = 0; y < cameraData->chunksScale; y++){
            castedChunk->castedBlocks[x][y] = *createCastedBlock();
            //Set the world key for the casted block
            castedChunk->castedBlocks[x][y].camKey = modKey(castedChunk->worldKey, x, y, 0, 0);
        }
    }

    //Create casted Chunk texture
    int xChunkTextureRez = cameraData->chunksScale * cameraData->baseBlockScale;
    int yChunkTextureRez = cameraData->chunksScale * (cameraData->baseBlockScale/2);
    castedChunk->chunkTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, xChunkTextureRez, yChunkTextureRez);

    SDL_SetTextureBlendMode(castedChunk->chunkTexture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(renderer, castedChunk->chunkTexture);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);  // RGBA for transparent
    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer, NULL);

    return castedChunk;
}

struct CastedPool* createCastedPool(struct CameraData* cameraData, struct SDL_Renderer* renderer){
    struct CastedPool* castedPool = malloc(sizeof (struct CastedPool));
    castedPool->castedChunks = malloc(sizeof (struct CastedChunk*) * cameraData->viewDistance);
    for (int x = 0; x < cameraData->viewDistance; x++){
        castedPool->castedChunks[x] = malloc(sizeof (struct CastedChunk) * cameraData->viewDistance);
        for (int y = 0; y < cameraData->viewDistance; y++){
            castedPool->castedChunks[x][y] = *createCastedChunk(cameraData, renderer, x, y);
        }
    }
    return castedPool;
}