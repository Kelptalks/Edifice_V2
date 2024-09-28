//
// Created by Spencer on 5/7/2024.
//

#include <math.h>
#include "CastedBlockManager.h"

#include <windows.h>

#include "../../../../World/Octree/Tools/KeyMod.h"
#include "../../../../Debuging/Test_Main.h"
#include "../../CameraData.h"
#include "../../Camera.h"

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

    castedChunk->worldX = cameraData->worldX + ((castedChunk->isoX * cameraData->xDirection) * cameraData->chunksScale);
    castedChunk->worldY = cameraData->worldY + ((castedChunk->isoY * cameraData->yDirection) * cameraData->chunksScale);
    castedChunk->worldZ = cameraData->worldZ;


    for (int x = 0; x < castedChunk->scale; x++){
        for (int y = 0; y < castedChunk->scale; y++){
            //Set the world key for the casted block
            struct CastedBlock* castedBlock = &castedChunk->castedBlocks[x + (y * castedChunk->scale)];
            castedBlock->worldX = castedChunk->worldX + (x * cameraData->xDirection);
            castedBlock->worldY = castedChunk->worldY + (y * cameraData->yDirection);
            castedBlock->worldZ = castedChunk->worldZ;
        }
    }
}

//Create a casted chunk object
struct CastedChunk* createCastedChunk(struct CameraData* cameraData, struct SDL_Renderer* renderer, int isoX, int isoY){
    struct CastedChunk* castedChunk = malloc(sizeof (struct CastedChunk));

    //set world rendering key
    castedChunk->worldX = cameraData->worldX + (isoX * cameraData->chunksScale);
    castedChunk->worldY = cameraData->worldY + (isoY * cameraData->chunksScale);
    castedChunk->worldZ = cameraData->worldZ;

    //set rendering cords / basics
    castedChunk->isoX = isoX;
    castedChunk->isoY = isoY;

    castedChunk->direction = cameraData->direction;

    castedChunk->scale = cameraData->chunksScale;
    castedChunk->castedBlockCount = cameraData->chunksScale * cameraData->chunksScale;;

    //set rendering variables
    castedChunk->rayCast = false;
    castedChunk->textured = false;

    //Initilize
    pthread_mutex_init(&castedChunk->lock, NULL);

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

    cameraData->castedPool->allChunks[cameraData->castedPool->totalChunksCreated] = castedChunk;
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
    castedPool->chunkMap = createChunkMap(9000);
    castedPool->maxChunks = (cameraData->maxViewDistance * 2) * (cameraData->maxViewDistance * 2);

    castedPool->freeChunks = malloc(sizeof (struct CastedChunk*) * castedPool->maxChunks);
    castedPool->allChunks = malloc(sizeof (struct CastedChunk*) * castedPool->maxChunks);
    castedPool->chunksInUse = malloc(sizeof (struct CastedChunk*) * castedPool->maxChunks);

    castedPool->totalChunksCreated = 0;
    castedPool->freeChunkCount = 0;
    castedPool->totalChunksInUse = 0;


    return castedPool;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Pool Management
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

void unloadChunk(struct GameData* gameData, struct CastedChunk* castedChunk){
    struct CastedPool* castedPool = gameData->cameraData->castedPool;
    //Remove the chunk from the hashmap
    removeFromChunkMap(castedPool->chunkMap, castedChunk->isoX, castedChunk->isoY);

    //Reset values
    castedChunk->isoY = 0;
    castedChunk->isoX = 0;
    clearChunkTexture(gameData, castedChunk);

    //Add the chunk to the top of the free chunk array stack
    castedPool->freeChunks[castedPool->freeChunkCount] = castedChunk;
    castedPool->freeChunkCount++;
}

struct CastedChunk* loadChunk(struct GameData* gameData, int isoX, int isoY){
    struct CastedPool* castedPool = gameData->cameraData->castedPool;
    //If there are no free chunks in pool create new one

    if (castedPool->freeChunkCount > 0){
        //Rebuild free struct
        castedPool->freeChunkCount--;
        struct CastedChunk *freeCastedChunk = castedPool->freeChunks[castedPool->freeChunkCount];
        castedPool->freeChunks[castedPool->freeChunkCount] = NULL;

        //Rebuild the chunk
        //Basic vars
        freeCastedChunk->isoX = isoX;
        freeCastedChunk->isoY = isoY;
        freeCastedChunk->direction = gameData->cameraData->direction;
        freeCastedChunk->rayCast = false;
        freeCastedChunk->textured = false;

        //World Camera location update
        updateChunkCamCords(gameData->cameraData, freeCastedChunk);

        //Add to chunk map
        addChunkToMap(castedPool->chunkMap, freeCastedChunk);
        return freeCastedChunk;
    }

    //If not the max chunks created has not been reached create another
    if (castedPool->maxChunks < castedPool->totalChunksCreated){
        return NULL;
    }
    else {
        //Malloc new struct
        struct CastedChunk *newCastedChunk = createCastedChunk(gameData->cameraData, gameData->screen->renderer, isoX, isoY);
        addChunkToMap(castedPool->chunkMap, newCastedChunk);

        return newCastedChunk;
    }
}

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