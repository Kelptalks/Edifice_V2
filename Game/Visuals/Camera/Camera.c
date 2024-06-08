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

void renderChunk(struct GameData* gameData, struct CastedChunk* castedChunk, int xCor , int yCor){
    struct CameraData* cameraData = gameData->cameraData;

    SDL_SetRenderDrawColor(gameData->screen->renderer, 0, 255, 0, 255);
    for (int x = 0; x < gameData->cameraData->chunksScale; x++){
        for (int y = 0; y < gameData->cameraData->chunksScale; y++){
            struct CastedBlock* castedBlock = &castedChunk->castedBlocks[x][y];

            //Drawing location
            int* cords = isoToScreen(cameraData->renderScale, x, y);
            SDL_Rect rightBLock = {cords[0] + xCor + (cameraData->renderScale/2) + cameraData->xRenderingOffset, cords[1] + yCor + cameraData->yRenderingOffset, cameraData->renderScale, cameraData->renderScale};
            SDL_Rect leftBlock = {cords[0] + xCor + cameraData->xRenderingOffset, cords[1] + yCor + cameraData->yRenderingOffset, cameraData->renderScale,cameraData->renderScale};

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
}

void renderView(struct GameData* gameData, int xCor, int yCor){
    struct CameraData* cameraData = gameData->cameraData;
    SDL_SetRenderDrawBlendMode(gameData->screen->renderer, SDL_BLENDMODE_BLEND);
    for (int x = 0; x < cameraData->viewDistance; x++){
        for (int y = 0; y < cameraData->viewDistance; y++){
            struct CastedChunk* castedChunk = &gameData->cameraData->castedPool->castedChunks[x][y];

            if (!castedChunk->busy){
                if (!castedChunk->rayCast){
                    threadCastChunk(castedChunk, gameData->world->octree);
                    castedChunk->busy = true;
                }
            }

            //Render the chunk
            SDL_SetRenderDrawColor(gameData->screen->renderer, 255, 0, 0, 255);
            int* cords = isoToScreen(cameraData->renderScale * cameraData->chunksScale, x, y);
            SDL_RenderDrawPoint(gameData->screen->renderer, cords[0] + xCor, cords[1] + yCor);
            renderChunk(gameData, castedChunk, cords[0] + xCor, cords[1] + yCor);
            free(cords);
        }
    }
}