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
#include "../../World/Octree/Tools/KeyMod.h"
#include "../../World/Octree/Octree.h"
#include "../../World/Octree/OctreeNode.h"
#include "Rendering/RayCasting/CastingThread/castingThread.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Texture rendering
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * render chunk textures to avoid drawing all casted blocks every frame
 */


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

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Rendering direction management
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void updateDirectionCastingMods(struct CameraData* cameraData, enum Direction direction){
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

void offSetCamWorldKeyBasedOnRotation(struct CameraData* cameraData, enum Direction direction){

    reportBug("Starting camera cords (%i, %i, %i)\n", cameraData->worldX, cameraData->worldY, cameraData->worldZ);
    struct World* world = cameraData->world;


    //Get Casted block at the center of the screen
    struct CastedBlock* castedBlock = getCastedBlockAtCords(cameraData,cameraData->xIsoCamCenter, cameraData->yIsoCamCenter);
    //Unpack cords
    int worldX = castedBlock->worldX; int worldY = castedBlock->worldY; int worldZ = castedBlock->worldZ;

    //Cast a ray to the block it hits
    enum Block block = Air;
    int distance = 0;
    for (int drawDistance = 300; drawDistance > 0; drawDistance--){
        worldX - cameraData->xDirection;
        block = getBlockAtWorldCor(world, worldX, worldY, worldZ);
        if (!isTransparent(block)){
            break;
        }
        block = getBlockAtWorldCor(world, worldX, worldY, worldZ);
        worldY - cameraData->yDirection;
        if (!isTransparent(block)){
            break;
        }
        block = getBlockAtWorldCor(world, worldX, worldY, worldZ);
        worldZ - 1;
        if (!isTransparent(block)){
            break;
        }
        distance++;
    }

    //Update the casting directions
    updateDirectionCastingMods(cameraData, direction);

    int newCamWorldX = worldX + (cameraData->xDirection * distance);
    int newCamWorldY = worldY + (cameraData->yDirection * distance);
    int newCamWorldZ = distance;

    cameraData->worldX = newCamWorldX;
    cameraData->worldY = newCamWorldY;
    cameraData->worldZ = newCamWorldZ;

    reportBug("new cam cords (%i, %i, %i)\n", newCamWorldX, newCamWorldY, newCamWorldZ);

    //Calculate a new Casted block key by casting from the struck block

}

void setDirection(struct CameraData* cameraData, enum Direction direction){
    if (cameraData->world != NULL) {
        offSetCamWorldKeyBasedOnRotation(cameraData, direction);
    }

    cameraData->direction = direction;

    //Update order for shadow casting
    updateCastingDirectionOrder(cameraData);
}

void rotateCamLeft(struct CameraData* cameraData){
    if (cameraData->direction < 3) {
        int newDirection = cameraData->direction + 1;
        setDirection(cameraData, newDirection);
    }
    else {
        setDirection(cameraData, 0);
    }
}

void rotateCamRight(struct CameraData* cameraData){
    if (cameraData->direction > 0) {
        int newDirection = cameraData->direction - 1;
        setDirection(cameraData, newDirection);
    }
    else {
        setDirection(cameraData, 3);
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Rendering management
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

//Update the coordinates of the camera based off the offset produced by control functions
void updateCameraCords(struct GameData* gameData){
    //Setup
    struct CameraData* cameraData = gameData->cameraData;

    //Cords of camera in world calculations
    int isoX; int isoY;
    screenToIso(gameData->cameraData->renderScale/2,  (gameData->screen->xRez/2) - gameData->cameraData->xRenderingOffset, (gameData->screen->yRez/2) - gameData->cameraData->yRenderingOffset, &isoX, &isoY);

    cameraData->xIsoCamCenter = isoX;
    cameraData->yIsoCamCenter = isoY;

    cameraData->xIsoChunkCamCenter = isoX / cameraData->chunksScale;
    cameraData->yIsoChunkCamCenter = isoY / cameraData->chunksScale;
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
                if (castedChunk->rayCast && castedChunk->textured) {
                    castedChunk->rayCast = false;
                    castedChunk->textured = false;
                }
            }
            else{

            }
        }
    }
}

void renderView(struct GameData* gameData){

    struct CameraData* cameraData = gameData->cameraData;
    SDL_SetRenderDrawBlendMode(gameData->screen->renderer, SDL_BLENDMODE_BLEND);

    updateCameraCords(gameData);

    //Get texture dimensions
    float chunkRenderScale = (gameData->cameraData->renderScale / gameData->cameraData->baseBlockScale);
    cameraData->xChunkScaledTextureRez = cameraData->chunkPixelScale * chunkRenderScale;
    cameraData->yChunkScaledTextureRez = (cameraData->chunkPixelScale/2) * chunkRenderScale;


    int maxTexturingPerFrame = 15;
    int maxNewChunksPerFrame = 15;
    for (int i = 0; i < cameraData->totalDistanceCords / 2; i++)
    {
        int x = cameraData->distanceSortedRelativeCords[i].x;
        int y = cameraData->distanceSortedRelativeCords[i].y;

        int xChunkWorldCords = (x) + cameraData->xIsoChunkCamCenter;
        int yChunkWorldCords = (y) + cameraData->yIsoChunkCamCenter;

        struct CastedChunk *castedChunk = getChunkFromMap(cameraData->castedPool->chunkMap, xChunkWorldCords,
                                                          yChunkWorldCords);
        //if in view distance radius
        if (cameraData->distanceSortedRelativeCords[i].distance < cameraData->viewDistance){
            //Manage chunks
            if (castedChunk == NULL && maxNewChunksPerFrame > 0) {
                loadChunk(gameData, xChunkWorldCords,yChunkWorldCords);
                maxNewChunksPerFrame--;
            //If the chunk does exist
            } else if (castedChunk != NULL){

                //Reset the direction the chunk should be rendered
                if (castedChunk->direction != cameraData->direction) {
                    castedChunk->direction = cameraData->direction;
                    updateChunkCamCords(cameraData, castedChunk);
                    castedChunk->rayCast = false;
                    castedChunk->textured = false;
                }

                //Render the chunk texture if needed
                if (!castedChunk->rayCast) {
                    addRayCastingTaskToThreadPool(cameraData->rayCastingThreadPool, castedChunk);
                } else if (!castedChunk->textured && maxTexturingPerFrame > 0) {
                    maxTexturingPerFrame--;
                    renderChunkTexture(gameData, castedChunk);
                }

                //Draw the Casted Chunk
                DrawChunk(gameData, castedChunk);
            }
        }
    }

    //Ray cast all chunks added to the thread pool task q
    executeAllTasks(cameraData->rayCastingThreadPool);

    for (int i = cameraData->totalDistanceCords/10; i < cameraData->totalDistanceCords; i++){
        //Get the chunk
        int x = cameraData->distanceSortedRelativeCords[i].x;
        int y = cameraData->distanceSortedRelativeCords[i].y;
        int xChunkWorldCords = (x) + cameraData->xIsoChunkCamCenter;
        int yChunkWorldCords = (y) + cameraData->yIsoChunkCamCenter;
        struct CastedChunk *castedChunk = getChunkFromMap(cameraData->castedPool->chunkMap, xChunkWorldCords,
                                                          yChunkWorldCords);


        if (castedChunk != NULL) {
            unloadChunk(cameraData->castedPool, castedChunk);
        }
    }

    //re raycast and texture the area around the mouse
    renderMouseArea(gameData);
}