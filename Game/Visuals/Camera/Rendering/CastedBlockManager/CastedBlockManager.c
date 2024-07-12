//
// Created by Spencer on 5/7/2024.
//

#include <math.h>
#include "CastedBlockManager.h"
#include "../../../../World/Octree/KeyMod.h"
#include "../../../../Debuging/Test_Main.h"
#include "../../CameraData.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Creation and freeing functions
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

struct CastedBlock* createCastedBlock(){
    struct CastedBlock* castedBlock = malloc(sizeof (struct CastedBlock));
    castedBlock->leftTextureList = createTextureList();
    castedBlock->rightTextureList = createTextureList();

    castedBlock->leftTempTextureList = createTextureList();
    castedBlock->rightTemptTextureList = createTextureList();

    castedBlock->leftShader = Empty;
    castedBlock->rightShader = Empty;
    return castedBlock;
}

void updateChunkCamCords(struct CameraData* cameraData, struct CastedChunk* castedChunk){
    castedChunk->worldKey = modKey(cameraData->key, (castedChunk->isoX * cameraData->xDirection) * cameraData->chunksScale, (castedChunk->isoY * cameraData->yDirection) * cameraData->chunksScale, 0, 0);
    for (int x = 0; x < castedChunk->scale; x++){
        for (int y = 0; y < castedChunk->scale; y++){
            //Set the world key for the casted block
            castedChunk->castedBlocks[x + (y * castedChunk->scale)].camKey = modKey(castedChunk->worldKey, x * cameraData->xDirection, y * cameraData->yDirection, 0, 0);
        }
    }
}

//Create a casted chunk object
struct CastedChunk* createCastedChunk(struct CameraData* cameraData, struct SDL_Renderer* renderer, int isoX, int isoY){
    struct CastedChunk* castedChunk = malloc(sizeof (struct CastedChunk));

    //set world rendering key
    castedChunk->worldKey = modKey(cameraData->key, isoX * cameraData->chunksScale, isoY * cameraData->chunksScale, 0, 0);

    //set rendering cords / basics
    castedChunk->isoX = isoX;
    castedChunk->isoY = isoY;

    castedChunk->direction = cameraData->direction;

    castedChunk->scale = cameraData->chunksScale;
    castedChunk->castedBlockCount = cameraData->chunksScale * cameraData->chunksScale;;

    //set rendering variables
    castedChunk->busy = false;
    castedChunk->rayCast = false;
    castedChunk->textured = false;
    //castedChunk->direction = cameraData->direction;

    //SetupCasted blocks utilizing the casted chunks camWorldKey
    castedChunk->castedBlocks = calloc(castedChunk->castedBlockCount, sizeof(struct CastedBlock));

    for (int x = 0; x < castedChunk->castedBlockCount; x++){
        castedChunk->castedBlocks[x] = *createCastedBlock();
    }

    updateChunkCamCords(cameraData, castedChunk);

    //Create casted Chunk texture based on it's scale
    int xChunkTextureRez = cameraData->chunksScale * cameraData->baseBlockScale;
    int yChunkTextureRez = cameraData->chunksScale * (cameraData->baseBlockScale/2);
    castedChunk->chunkTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, xChunkTextureRez, yChunkTextureRez);

    //Clear the chunk texture
    SDL_SetTextureBlendMode(castedChunk->chunkTexture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(renderer, castedChunk->chunkTexture);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);  // RGBA for transparent
    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer, NULL);

    cameraData->castedPool->totalChunksCreated++;
    return castedChunk;
}

void freeCastedChunk(struct CastedChunk* castedChunk){
    //Free the casted blocks array's data
    for (int x = 0; x < castedChunk->castedBlockCount; x++) {
        struct CastedBlock castedBlock = castedChunk->castedBlocks[x];
        freeTextureList(castedBlock.leftTextureList);
        freeTextureList(castedBlock.rightTextureList);
    }
    //free castedBlockArray
    free(castedChunk->castedBlocks);
    //Free struct itself
    castedChunk = NULL;
}

struct CastedPool* createCastedPool(struct CameraData* cameraData, struct SDL_Renderer* renderer){
    struct CastedPool* castedPool = malloc(sizeof (struct CastedPool));
    //Create the Casted Pool array based on the square of the view distance
    castedPool->totalChunksCreated = 0;
    castedPool->chunkMap = createChunkMap(256);


    return castedPool;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Pool Management
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

struct CastedChunk* getCastedChunkAtCords(struct CameraData* cameraData, int isoX, int isoY){
    //Loop through chunks in array and identify on that has correct cords
    int chunkIsoX = isoX/cameraData->chunksScale;
    int chunkIsoY = isoY/cameraData->chunksScale;

    //Index chunk map at cords
    struct CastedChunk* castedChunk = getChunkFromMap(cameraData->castedPool->chunkMap, chunkIsoX, chunkIsoY);
    return castedChunk;
}

struct CastedBlock* getCastedBlockAtCords(struct CameraData* cameraData, int isoX, int isoY){
    //Get chunk chunk cords
    int chunkIsoX = isoX / cameraData->chunksScale;
    int chunkIsoY = isoY / cameraData->chunksScale;

    int xBlockCor = isoX % cameraData->chunksScale;
    int yBlockCor = isoY % cameraData->chunksScale;

    if (xBlockCor < 0){
        xBlockCor += cameraData->chunksScale;
        chunkIsoX--;
    }
    if (yBlockCor < 0){
        yBlockCor += cameraData->chunksScale;
        chunkIsoY--;
    }

    //Mod cords based off chunk scale to determine where in the chunk the cords are located
    struct CastedChunk* castedChunk = getChunkFromMap(cameraData->castedPool->chunkMap, chunkIsoX, chunkIsoY);

    if (castedChunk != NULL) {
        return &castedChunk->castedBlocks[xBlockCor + (yBlockCor * cameraData->chunksScale)];
    }
    return NULL;
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Getters / Setters
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */