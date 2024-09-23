//
// Created by Spencer on 9/23/2024.
//
#include "SDL.h"
#include "../../IsoCordTool/IsoCordManager.h"
#include "../../CameraData.h.."

void renderChunkOutLine(struct GameData* gameData, int isoX, int isoY, int color[3]){
    struct CameraData* cameraData = gameData->cameraData;

    //Debug Menu rendering
    int xScreenCor;
    int yScreenCor;
    isoToScreen(cameraData->xChunkScaledTextureRez, isoX, isoY, &xScreenCor, &yScreenCor);

    //Get chunk location on screen,
    int xChunkRenderCords = (xScreenCor) + cameraData->xRenderingOffset - (cameraData->yChunkScaledTextureRez);
    int yChunkRenderCords = (yScreenCor) + cameraData->yRenderingOffset;

    //Draw Chunk Boarder if toggled on
    SDL_SetRenderDrawColor(gameData->screen->renderer, color[0], color[1], color[2], 255);
    SDL_RenderDrawLine(gameData->screen->renderer, xChunkRenderCords + (cameraData->xChunkScaledTextureRez / 2),
                       yChunkRenderCords, xChunkRenderCords + (cameraData->xChunkScaledTextureRez),
                       yChunkRenderCords + (cameraData->yChunkScaledTextureRez / 2));
    SDL_RenderDrawLine(gameData->screen->renderer, xChunkRenderCords + (cameraData->xChunkScaledTextureRez),
                       yChunkRenderCords + (cameraData->yChunkScaledTextureRez / 2),
                       xChunkRenderCords + (cameraData->xChunkScaledTextureRez / 2),
                       yChunkRenderCords + cameraData->yChunkScaledTextureRez);
}

void renderCastedBlock(struct GameData* gameData, struct CastedBlock* castedBlock, int x, int y, int side){
    struct CameraData* cameraData = gameData->cameraData;

    //get the cords the chunk should be draw to the screen
    int chunkScreenX;
    int chunkScreenY;
    isoToScreen(cameraData->xChunkScaledTextureRez, x / 8, y / 8, &chunkScreenX, &chunkScreenY);

    //Get chunk location on screen,
    int xChunkRenderCords = chunkScreenX + cameraData->xRenderingOffset;
    int yChunkRenderCords = chunkScreenY + cameraData->yRenderingOffset;
    int color = {0, 20, 255};

    renderChunkOutLine(gameData, xChunkRenderCords, yChunkRenderCords, &color);
    //Drawing location
    int blockScreenX;
    int blockScreenY;
    floatIsoToScreen(cameraData->renderScale, (x % cameraData->chunksScale), (y % cameraData->chunksScale), &blockScreenX, &blockScreenY);
    blockScreenX = xChunkRenderCords + blockScreenX;
    blockScreenY = yChunkRenderCords + blockScreenY;
    blockScreenX -= cameraData->renderScale/2;

    //Center on texture
    float pixelFill =  3/cameraData->renderScale;
    SDL_Rect rightBLock = {(blockScreenX + (cameraData->renderScale/2)), blockScreenY, cameraData->renderScale + pixelFill, cameraData->renderScale + pixelFill};
    SDL_Rect leftBlock = {blockScreenX, blockScreenY, cameraData->renderScale + pixelFill,cameraData->renderScale + pixelFill};

    //Texture rendering
    if (side == 1 || side == 2) {
        for (int t = castedBlock->rightTextureList->length - 1; t >= 0; t--) {
            struct TextureNode *currentTextureNode = &castedBlock->rightTextureList->nodes[t];
            SDL_Texture *rightFace = gameData->textures->BlockTextures[currentTextureNode->block].textures[currentTextureNode->texture];
            SDL_RenderCopy(gameData->screen->renderer, rightFace, NULL, &rightBLock);
        }
        //Temp Textures
        for (int t = castedBlock->rightTemptTextureList->length - 1; t >= 0; t--) {
            struct TextureNode *currentTextureNode = &castedBlock->rightTemptTextureList->nodes[t];
            SDL_Texture *rightFace = gameData->textures->BlockTextures[currentTextureNode->block].textures[currentTextureNode->texture];
            SDL_RenderCopy(gameData->screen->renderer, rightFace, NULL, &rightBLock);
        }
        //Shader rendering
        if (castedBlock->rightShader != Empty) {
            SDL_Texture *rightFace = gameData->textures->blockShaders->textures[castedBlock->rightShader];
            SDL_RenderCopy(gameData->screen->renderer, rightFace, NULL, &rightBLock);
        }
    }
    if (side == 0 || side == 2) {
        for (int t = castedBlock->leftTempTextureList->length - 1; t >= 0; t--) {
            struct TextureNode *currentTextureNode = &castedBlock->leftTempTextureList->nodes[t];
            SDL_Texture *leftFace = gameData->textures->BlockTextures[currentTextureNode->block].textures[currentTextureNode->texture];
            SDL_RenderCopy(gameData->screen->renderer, leftFace, NULL, &leftBlock);
        }
        for (int t = castedBlock->leftTextureList->length - 1; t >= 0; t--) {
            struct TextureNode *currentTextureNode = &castedBlock->leftTextureList->nodes[t];
            SDL_Texture *leftFace = gameData->textures->BlockTextures[currentTextureNode->block].textures[currentTextureNode->texture];
            SDL_RenderCopy(gameData->screen->renderer, leftFace, NULL, &leftBlock);
        }
        if (castedBlock->leftShader != Empty) {
            SDL_Texture *leftFace = gameData->textures->blockShaders->textures[castedBlock->leftShader];
            SDL_RenderCopy(gameData->screen->renderer, leftFace, NULL, &leftBlock);
        }
    }
}

//Render a chunks texture
void renderChunkTexture(struct GameData* gameData, struct CastedChunk* castedChunk){
    struct CameraData* cameraData = gameData->cameraData;
    SDL_SetRenderDrawColor(gameData->screen->renderer, 0, 255, 0, 255);
    //Set renderer to target chunk texture
    SDL_SetRenderTarget(gameData->screen->renderer, castedChunk->chunkTexture);
    SDL_SetRenderDrawColor(gameData->screen->renderer, 0, 0, 0, 0);  // RGBA for transparent
    SDL_RenderClear(gameData->screen->renderer);

    for (int x = 0; x < gameData->cameraData->chunksScale; x++){
        for (int y = 0; y < gameData->cameraData->chunksScale; y++){
            struct CastedBlock* castedBlock = &castedChunk->castedBlocks[x + (y * gameData->cameraData->chunksScale)];
            //Drawing location
            int isoX;
            int isoY;
            isoToScreen(cameraData->baseBlockScale, x, y, &isoX, &isoY);

            //Center on texture
            isoX += (gameData->cameraData->chunkPixelScale - gameData->cameraData->baseBlockScale)/2;

            SDL_Rect rightBLock = {isoX + (cameraData->baseBlockScale/2), isoY, cameraData->baseBlockScale, cameraData->baseBlockScale};
            SDL_Rect leftBlock = {isoX, isoY, cameraData->baseBlockScale,cameraData->baseBlockScale};
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
        }
    }
    //Set render target back to main window
    SDL_SetRenderTarget(gameData->screen->renderer, NULL);
    castedChunk->textured = true;
}

void clearChunkTexture(struct GameData* gameData, struct CastedChunk* castedChunk){
    SDL_SetRenderDrawColor(gameData->screen->renderer, 0, 255, 0, 255);
    //Set renderer to target chunk texture
    SDL_SetRenderTarget(gameData->screen->renderer, castedChunk->chunkTexture);
    SDL_SetRenderDrawColor(gameData->screen->renderer, 0, 0, 0, 0);  // RGBA for transparent
    SDL_RenderClear(gameData->screen->renderer);
    SDL_SetRenderTarget(gameData->screen->renderer, NULL);
}

//Draw a chunk in the correct location
void DrawChunk(struct GameData* gameData, struct CastedChunk* castedChunk){
    struct CameraData* cameraData = gameData->cameraData;
    //get the cords the chunk should be draw to the screen

    int isoX;
    int isoY;
    isoToScreen(cameraData->xChunkScaledTextureRez, castedChunk->isoX, castedChunk->isoY, &isoX, &isoY);

    //Get chunk location on screen,
    int xChunkRenderCords = (isoX) + cameraData->xRenderingOffset;
    int yChunkRenderCords = (isoY) + cameraData->yRenderingOffset;

    //Draw the chunk with propper scale
    SDL_Rect chunkRect = {(xChunkRenderCords - cameraData->yChunkScaledTextureRez),
                          (yChunkRenderCords),
                          cameraData->xChunkScaledTextureRez + 2,
                          cameraData->yChunkScaledTextureRez + 2};
    SDL_RenderCopy(gameData->screen->renderer, castedChunk->chunkTexture, NULL, &chunkRect);
}
