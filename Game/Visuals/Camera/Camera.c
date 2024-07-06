//
// Created by Spencer on 5/6/2024.
//

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


void drawChunk(struct GameData* gameData, struct CastedChunk* castedChunk){

}

void setDirection(struct GameData* gameData, enum Direction direction){
    struct CameraData* cameraData = gameData->cameraData;
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

void renderView(struct GameData* gameData, int xCor, int yCor){
    struct CameraData* cameraData = gameData->cameraData;
    SDL_SetRenderDrawBlendMode(gameData->screen->renderer, SDL_BLENDMODE_BLEND);

    updateCameraCords(gameData);

    //Get texture dimensions
    float chunkRenderScale = (gameData->cameraData->renderScale / gameData->cameraData->baseBlockScale);
    int xChunkTextureRez = cameraData->chunkPixelScale * chunkRenderScale;
    int yChunkTextureRez = (cameraData->chunkPixelScale/2) * chunkRenderScale;

    //Center to Coordinate plane
    xCor -= yChunkTextureRez;

    for (int x = gameData->cameraData->xIsoChunkCamCenter - cameraData->viewDistance; x < gameData->cameraData->xIsoChunkCamCenter + cameraData->viewDistance; x++){
        for (int y = gameData->cameraData->yIsoChunkCamCenter - cameraData->viewDistance; y < gameData->cameraData->yIsoChunkCamCenter + cameraData->viewDistance; y++){
            struct CastedChunk* castedChunk = getChunkFromMap(cameraData->castedPool->chunkMap, x, y);
            if (castedChunk == NULL){
                struct CastedChunk* newCastedChunk = createCastedChunk(cameraData, gameData->screen->renderer, x, y);
                addChunkToMap(gameData->cameraData->castedPool->chunkMap, newCastedChunk);
            }
            else {
                //Render the chunk texture if needed
                if (!castedChunk->busy) {
                    if (!castedChunk->rayCast) {
                        castedChunk->busy = true;
                        threadCastChunk(gameData->cameraData, castedChunk, gameData->world->octree);

                    } else if (!castedChunk->textured) {
                        castedChunk->busy = true;
                        renderChunkTexture(gameData, castedChunk);
                    }
                }

                //Render the chunk
                SDL_SetRenderDrawColor(gameData->screen->renderer, 255, 255, 255, 255);
                int *cords = isoToScreen(cameraData->renderScale * cameraData->chunksScale, castedChunk->isoX,
                                         castedChunk->isoY);

                int xChunkRenderCords = cords[0] + xCor + cameraData->xRenderingOffset;
                int yChunkRenderCords = cords[1] + yCor + cameraData->yRenderingOffset;

                SDL_Rect chunkRect = {(xChunkRenderCords),
                                      (yChunkRenderCords),
                                      xChunkTextureRez + 3,
                                      yChunkTextureRez + 3};
                SDL_RenderCopy(gameData->screen->renderer, castedChunk->chunkTexture, NULL, &chunkRect);


                SDL_SetRenderDrawColor(gameData->screen->renderer, 0, 50, 255, 255);



                if (gameData->debugMenu->chunkBoarders) {
                    SDL_RenderDrawLine(gameData->screen->renderer, xChunkRenderCords + (xChunkTextureRez / 2),
                                       yChunkRenderCords, xChunkRenderCords + (xChunkTextureRez),
                                       yChunkRenderCords + (yChunkTextureRez / 2));
                    SDL_RenderDrawLine(gameData->screen->renderer, xChunkRenderCords + (xChunkTextureRez),
                                       yChunkRenderCords + (yChunkTextureRez / 2),
                                       xChunkRenderCords + (xChunkTextureRez / 2),
                                       yChunkRenderCords + yChunkTextureRez);
                }
                free(cords);
            }
        }
    }

    renderMouseArea(gameData);
}