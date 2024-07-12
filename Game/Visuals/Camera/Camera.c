//
// Created by Spencer on 5/6/2024.
//

#include <math.h>
#include "../../GameData.h"
#include "SDL.h"
#include "IsoCordTool/IsoCordManager.h"
#include "CameraData.h"
#include "Rendering/TextureManager/IsoTextureManager.h"
#include "Rendering/CastedBlockManager/CastedBlockManager.h"
#include "../../Debuging/Test_Main.h"
#include "../../../Game/Blocks/Blocks.h"
#include "Rendering/RayCasting/RayCastingManager.h"
#include "../../World/World.h"

//Render a chunks texture
void renderChunkTexture(struct GameData* gameData, struct CastedChunk* castedChunk){
    struct CameraData* cameraData = gameData->cameraData;
    SDL_SetRenderDrawColor(gameData->screen->renderer, 0, 255, 0, 255);
    //Set renderer to target chunk texture
    SDL_SetRenderTarget(gameData->screen->renderer, castedChunk->chunkTexture);


    for (int x = 0; x < gameData->cameraData->chunksScale; x++){
        for (int y = 0; y < gameData->cameraData->chunksScale; y++){
            struct CastedBlock* castedBlock = &castedChunk->castedBlocks[x + (y * gameData->cameraData->chunksScale)];

            //Drawing location
            int* cords = isoToScreen(cameraData->baseBlockScale, x, y);
            //Center on texture
            cords[0] += (gameData->cameraData->chunkPixelScale - gameData->cameraData->baseBlockScale)/2;

            SDL_Rect rightBLock = {cords[0] + (cameraData->baseBlockScale/2), cords[1], cameraData->baseBlockScale, cameraData->baseBlockScale};
            SDL_Rect leftBlock = {cords[0], cords[1], cameraData->baseBlockScale,cameraData->baseBlockScale};

            //Texture rendering
            for (int t = castedBlock->rightTextureList->length - 1; t >= 0; t--){
                struct TextureNode* currentTextureNode = &castedBlock->rightTextureList->nodes[t];
                SDL_Texture* rightFace = gameData->textures->BlockTextures[currentTextureNode->block].textures[currentTextureNode->texture];
                SDL_RenderCopy(gameData->screen->renderer, rightFace, NULL, &rightBLock);
            }
            for (int t = castedBlock->leftTextureList->length - 1; t >= 0; t--) {
                struct TextureNode* currentTextureNode = &castedBlock->leftTextureList->nodes[t];
                SDL_Texture *leftFace = gameData->textures->BlockTextures[currentTextureNode->block].textures[currentTextureNode->texture];
                SDL_RenderCopy(gameData->screen->renderer, leftFace, NULL, &leftBlock);
            }

            //Temp Textures
            for (int t = castedBlock->rightTemptTextureList->length - 1; t >= 0; t--){
                struct TextureNode* currentTextureNode = &castedBlock->rightTemptTextureList->nodes[t];
                SDL_Texture* rightFace = gameData->textures->BlockTextures[currentTextureNode->block].textures[currentTextureNode->texture];
                SDL_RenderCopy(gameData->screen->renderer, rightFace, NULL, &rightBLock);
            }
            for (int t = castedBlock->leftTempTextureList->length - 1; t >= 0; t--) {
                struct TextureNode* currentTextureNode = &castedBlock->leftTempTextureList->nodes[t];
                SDL_Texture *leftFace = gameData->textures->BlockTextures[currentTextureNode->block].textures[currentTextureNode->texture];
                SDL_RenderCopy(gameData->screen->renderer, leftFace, NULL, &leftBlock);
            }

            //Shader rendering
            if (castedBlock->rightShader != Empty) {
                SDL_Texture *rightFace = gameData->textures->blockShaders->textures[castedBlock->rightShader];
                SDL_RenderCopy(gameData->screen->renderer, rightFace, NULL, &rightBLock);
            }
            if (castedBlock->leftShader != Empty) {
                SDL_Texture *leftFace = gameData->textures->blockShaders->textures[castedBlock->leftShader];
                SDL_RenderCopy(gameData->screen->renderer, leftFace, NULL, &leftBlock);
            }

            free(cords);
        }
    }
    //Set render target back to main window
    SDL_SetRenderTarget(gameData->screen->renderer, NULL);
    castedChunk->busy = false;
    castedChunk->textured = true;
}

//Render the area around the mouse
void renderMouseArea(struct GameData* gameData){
    struct CameraData* cameraData = gameData->cameraData;
    int xChunkCor = gameData->debugMenu->xBlockSelectedCor / gameData->cameraData->chunksScale;
    int yChunkCor = gameData->debugMenu->yBlockSelectedCor / gameData->cameraData->chunksScale;

    //Check what chunk the Mouse is over
    for (int x = xChunkCor - cameraData->mouseUpdateDistance; x < xChunkCor + cameraData->mouseUpdateDistance; x++){
        for (int y = yChunkCor - cameraData->mouseUpdateDistance; y < yChunkCor + cameraData->mouseUpdateDistance; y++){
            struct CastedChunk* castedChunk = getChunkFromMap(cameraData->castedPool->chunkMap, x, y);
            if (castedChunk != NULL) {
                if (!castedChunk->busy && castedChunk->rayCast && castedChunk->textured) {
                    castedChunk->rayCast = false;
                    castedChunk->textured = false;
                }
            }
        }
    }
}


void setDirection(struct CameraData* cameraData, enum Direction direction){
    cameraData->direction = direction;
    if (direction == North){
        cameraData->xDirection = 1;
        cameraData->yDirection = 1;
        cameraData->zDirection = 1;
    }
    else if (direction == South){
        cameraData->xDirection = -1;
        cameraData->yDirection = -1;
        cameraData->zDirection = 1;
    }
    else if (direction == East){
        cameraData->xDirection = -1;
        cameraData->yDirection = 1;
        cameraData->zDirection = 1;
    }
    else if (direction == West){
        cameraData->xDirection = 1;
        cameraData->yDirection = -1;
        cameraData->zDirection = 1;
    }
    updateCastingDirectionOrder(cameraData);
}

//Update the coordinates of the camera based off the offset produced by control functions
void updateCameraCords(struct GameData* gameData){
    //Setup
    struct CameraData* cameraData = gameData->cameraData;

    //Cords of camera in world calculations
    int *cords = screenToIso(gameData->cameraData->renderScale/2,  (gameData->screen->xRez/2) - gameData->cameraData->xRenderingOffset, (gameData->screen->yRez/2) - gameData->cameraData->yRenderingOffset);

    cameraData->xIsoCamCenter = cords[0];
    cameraData->yIsoCamCenter = cords[1];

    cameraData->xIsoChunkCamCenter = cords[0] / cameraData->chunksScale;
    cameraData->yIsoChunkCamCenter = cords[1] / cameraData->chunksScale;

    free(cords);
}

void DrawChunk(struct GameData* gameData, struct CastedChunk* castedChunk){
    struct CameraData* cameraData = gameData->cameraData;
    //Draw the chunk to the screen
    SDL_SetRenderDrawColor(gameData->screen->renderer, 255, 255, 255, 255);

    //get the cords the chunk should be draw to the screen
    int isoChunkXRenderingCor = castedChunk->isoX;
    int isoChunkYRenderingCor = castedChunk->isoY;

    int *cords = isoToScreen(cameraData->xChunkScaledTextureRez, isoChunkXRenderingCor,
                             isoChunkYRenderingCor);

    //Get chunk location on screen,
    float xRenderingOffset = cameraData->xRenderingOffset;
    float yRenderingOffset = cameraData->yRenderingOffset;

    int xChunkRenderCords = (cords[0]) + xRenderingOffset;
    int yChunkRenderCords = (cords[1]) + yRenderingOffset;

    //Draw the chunk with propper scale
    SDL_Rect chunkRect = {(xChunkRenderCords - cameraData->yChunkScaledTextureRez),
                          (yChunkRenderCords),
                          cameraData->xChunkScaledTextureRez + 2,
                          cameraData->yChunkScaledTextureRez + 2};
    SDL_RenderCopy(gameData->screen->renderer, castedChunk->chunkTexture, NULL, &chunkRect);

    //Draw Chunk Boarder if is on
    if (gameData->debugMenu->chunkBoarders) {
        SDL_RenderDrawLine(gameData->screen->renderer, xChunkRenderCords + (cameraData->xChunkScaledTextureRez / 2),
                           yChunkRenderCords, xChunkRenderCords + (cameraData->xChunkScaledTextureRez),
                           yChunkRenderCords + (cameraData->yChunkScaledTextureRez / 2));
        SDL_RenderDrawLine(gameData->screen->renderer, xChunkRenderCords + (cameraData->xChunkScaledTextureRez),
                           yChunkRenderCords + (cameraData->yChunkScaledTextureRez / 2),
                           xChunkRenderCords + (cameraData->xChunkScaledTextureRez / 2),
                           yChunkRenderCords + cameraData->yChunkScaledTextureRez);
    }
    free(cords);
}

void renderView(struct GameData* gameData, int xCor, int yCor){
    //Report Bugs
    reportFrameBug(" \n");
    reportFrameBug("Rendered Frame %i# \n", gameData->screen->currentFrame);

    Uint32 time1 = SDL_GetTicks(); //Start time to render tracker


    struct CameraData* cameraData = gameData->cameraData;
    SDL_SetRenderDrawBlendMode(gameData->screen->renderer, SDL_BLENDMODE_BLEND);

    updateCameraCords(gameData);

    //Get texture dimensions
    float chunkRenderScale = (gameData->cameraData->renderScale / gameData->cameraData->baseBlockScale);
    cameraData->xChunkScaledTextureRez = cameraData->chunkPixelScale * chunkRenderScale;
    cameraData->yChunkScaledTextureRez = (cameraData->chunkPixelScale/2) * chunkRenderScale;

    int maxTexturingPerFrame = 7;
    int maxNewChunksPerFrame = 7;
    for (int x = -cameraData->viewDistance; x < cameraData->viewDistance; x++){
        for (int y = -cameraData->viewDistance; y < cameraData->viewDistance; y++){
            int xChunkWorldCords = (x) + cameraData->xIsoChunkCamCenter;
            int yChunkWorldCords = (y) + cameraData->yIsoChunkCamCenter;

            struct CastedChunk *castedChunk = getChunkFromMap(cameraData->castedPool->chunkMap, xChunkWorldCords,
                                                              yChunkWorldCords);
            //if in view distance radius
            double distanceFromCenter = sqrt((x * x) + (y * y));
            if (distanceFromCenter < cameraData->viewDistance) {
                //Manage chunks
                if (castedChunk == NULL && maxNewChunksPerFrame > 0) {
                    struct CastedChunk *newCastedChunk = createCastedChunk(cameraData, gameData->screen->renderer,
                                                                           xChunkWorldCords, yChunkWorldCords);
                    addChunkToMap(gameData->cameraData->castedPool->chunkMap, newCastedChunk);
                    maxNewChunksPerFrame--;

                } else if (castedChunk != NULL){
                    //If chunk is rendered in wrong direction set for reRendering
                    if (castedChunk->direction != cameraData->direction){
                        castedChunk->textured = false;
                        castedChunk->rayCast = false;
                        castedChunk->direction = cameraData->direction;
                    }

                    //Render the chunk texture if needed
                    if (!castedChunk->busy) {
                        if (!castedChunk->rayCast) {
                            castedChunk->busy = true;
                            threadCastChunk(gameData->cameraData, castedChunk, gameData->world->octree);

                        } else if (!castedChunk->textured && maxTexturingPerFrame > 0) {
                            maxTexturingPerFrame--;
                            castedChunk->busy = true;
                            renderChunkTexture(gameData, castedChunk);
                        }
                    }

                    //Draw the Casted Chunk
                    DrawChunk(gameData, castedChunk);
                }
            }

            //Make lazy chunk and lower texture rez
            else if (distanceFromCenter > cameraData->viewDistance){
                if (castedChunk != NULL) {
                    //reportBug("Distance :%f | Cords : (%i, %i)\n", distanceFromCenter, xChunkWorldCords, yChunkWorldCords);
                    //removeFromChunkMap(cameraData->castedPool->chunkMap, xChunkWorldCords, yChunkWorldCords);
                    //freeCastedChunk(castedChunk);
                }
            }
        }
    }

    //re raycast and texture the area around the mouse
    renderMouseArea(gameData);

    //end frame render time tracker
    Uint32 time2 = SDL_GetTicks();
    gameData->screen->frameRenderTime = time2 - time1;
    //Update current frame
    gameData->screen->currentFrame++;

    reportFrameBug(" | Frame Render Time : %i ms \n", gameData->screen->frameRenderTime);
    reportFrameBug(" | Total Chunks Created : %i Chunks \n", gameData->cameraData->castedPool->totalChunksCreated);

    if (gameData->screen->currentFrame == 200){

    }
}