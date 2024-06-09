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


void renderChunkTexture(struct GameData* gameData, struct CastedChunk* castedChunk){
    struct CameraData* cameraData = gameData->cameraData;
    SDL_SetRenderDrawColor(gameData->screen->renderer, 0, 255, 0, 255);
    //Set renderer to target chunk texture
    SDL_SetRenderTarget(gameData->screen->renderer, castedChunk->chunkTexture);

    for (int x = 0; x < gameData->cameraData->chunksScale; x++){
        for (int y = 0; y < gameData->cameraData->chunksScale; y++){
            struct CastedBlock* castedBlock = &castedChunk->castedBlocks[x][y];

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
}

void renderView(struct GameData* gameData, int xCor, int yCor){
    struct CameraData* cameraData = gameData->cameraData;
    SDL_SetRenderDrawBlendMode(gameData->screen->renderer, SDL_BLENDMODE_BLEND);

    //Get texture dimensions
    float chunkRenderScale = (gameData->cameraData->renderScale / gameData->cameraData->baseBlockScale);
    int xChunkTextureRez = cameraData->chunkPixelScale * chunkRenderScale;
    int yChunkTextureRez = (cameraData->chunkPixelScale/2) * chunkRenderScale;

    //Center to Coordinate plane
    xCor -= yChunkTextureRez;

    for (int x = 0; x < cameraData->viewDistance; x++){
        for (int y = 0; y < cameraData->viewDistance; y++){
            struct CastedChunk* castedChunk = &gameData->cameraData->castedPool->castedChunks[x][y];

            if (!castedChunk->busy){
                if (!castedChunk->rayCast){
                    threadCastChunk(castedChunk, gameData->world->octree);
                    castedChunk->busy = true;
                }
                else if(!castedChunk->textured){
                    renderChunkTexture(gameData, castedChunk);
                    castedChunk->textured = true;
                }
            }

            //Render the chunk
            SDL_SetRenderDrawColor(gameData->screen->renderer, 255, 255, 255, 255);
            int* cords = isoToScreen(cameraData->renderScale * cameraData->chunksScale, x, y);

            SDL_Rect chunkRect = {cords[0] + xCor + cameraData->xRenderingOffset, cords[1] + yCor + cameraData->yRenderingOffset, xChunkTextureRez + 3, yChunkTextureRez + 3};
            SDL_RenderCopy(gameData->screen->renderer, castedChunk->chunkTexture, NULL, &chunkRect);

            //renderChunk(gameData, castedChunk, cords[0] + xCor, cords[1] + yCor);
            free(cords);
        }
    }
}