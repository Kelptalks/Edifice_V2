//
// Created by Spencer on 5/6/2024.
//

#include "CameraData.h"
#include "Rendering/RayCasting/RayCastingManager.h"
#include "IsoCordTool/IsoCordManager.h"
#include "Rendering/EntityRendering/EntityRendering.h"
#include "Rendering/CastedBlockRendering/CastedBlockRendering.h"
#include "Rendering/RayCasting/CastingThread/castingThread.h"
#include "../../World/World.h"

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
    struct World* world = cameraData->world;

    //Get Casted block at the center of the screen
    struct CastedBlock* castedBlock = getCastedBlockAtCords(cameraData,cameraData->xIsoCamCenter, cameraData->yIsoCamCenter);
    //Unpack cords
    int worldX = castedBlock->worldX;
    int worldY = castedBlock->worldY;
    int worldZ = castedBlock->worldZ;

    //Cast a ray to the block it hits
    enum Block block = Air;
    int distance = 0;
    for (int drawDistance = 300; drawDistance > 0; drawDistance--){
        worldX -= cameraData->xDirection;
        block = getBlockAtWorldCor(world, worldX, worldY, worldZ);
        if (!isTransparent(block)){
            drawDistance = 0;
        }
        worldY -= cameraData->yDirection;
        block = getBlockAtWorldCor(world, worldX, worldY, worldZ);
        if (!isTransparent(block)){
            drawDistance = 0;
        }
        block = getBlockAtWorldCor(world, worldX, worldY, worldZ);
        worldZ -= 1;
        if (!isTransparent(block)){
            drawDistance = 0;
        }
        distance++;
    }

    //Update the casting directions
    updateDirectionCastingMods(cameraData, direction);

    //
    int newCamWorldX = worldX + (cameraData->xDirection * distance);
    int newCamWorldY = worldY + (cameraData->yDirection * distance);
    int newCamWorldZ = distance;

    cameraData->xRenderingOffset = 1920/2;
    cameraData->yRenderingOffset = 1080/2;

    cameraData->worldX = newCamWorldX;
    cameraData->worldY = newCamWorldY;
    cameraData->worldZ = 300;

    //reportBug("Distance to block : %i\n", distance);
    //reportBug("new cam cords (%i, %i, %i)\n", newCamWorldX, newCamWorldY, newCamWorldZ);
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
    cameraData->fractionalScale = (gameData->cameraData->renderScale / gameData->cameraData->baseBlockScale);

    //Get texture dimensions
    cameraData->xChunkScaledTextureRez = cameraData->chunkPixelScale * cameraData->fractionalScale;
    cameraData->yChunkScaledTextureRez = (cameraData->chunkPixelScale/2) * cameraData->fractionalScale;

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
        }
    }

}

void renderView(struct GameData* gameData){
    struct CameraData* cameraData = gameData->cameraData;
    SDL_SetRenderDrawBlendMode(gameData->screen->renderer, SDL_BLENDMODE_BLEND);

    updateCameraCords(gameData);

    int maxTexturingPerFrame = 15;
    int maxNewChunksPerFrame = 15;
    //Loop through a circular area of chunks
    for (int i = 0; i < cameraData->totalDistanceCords; i++)
    {
        int x = cameraData->distanceSortedRelativeCords[i].x;
        int y = cameraData->distanceSortedRelativeCords[i].y;

        int xChunkWorldCords = (x) + cameraData->xIsoChunkCamCenter;
        int yChunkWorldCords = (y) + cameraData->yIsoChunkCamCenter;

        //Attempt to retrieve the chunk at the chunks world cords
        struct CastedChunk *castedChunk = getChunkFromMap(cameraData->castedPool->chunkMap, xChunkWorldCords,
                                                          yChunkWorldCords);

        //If IN view distance : Update required fields
        if (cameraData->distanceSortedRelativeCords[i].distance <= cameraData->viewDistance){
            //Manage chunks
            //If the chunk does not exist load one from Casted pool.
            if (castedChunk == NULL && maxNewChunksPerFrame > 0) {
                loadChunk(gameData, xChunkWorldCords,yChunkWorldCords);
                maxNewChunksPerFrame--;
            }
            // If chunk is not null manage its fields
            else if (castedChunk != NULL){
                //Reset the direction the chunk should be rendered
                if (castedChunk->direction != cameraData->direction) {
                    castedChunk->direction = cameraData->direction;
                    castedChunk->rayCast = false;
                    castedChunk->textured = false;
                    clearChunkTexture(gameData, castedChunk);
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

        //If NOT in Distance : Free The chunk
        if (cameraData->distanceSortedRelativeCords[i].distance > cameraData->viewDistance){
            if (castedChunk != NULL) {
                unloadChunk(gameData, castedChunk);
            }
        }
    }


    executeAllTasks(cameraData->rayCastingThreadPool);


    renderEntity(gameData);
    for (int i = 0; i < gameData->world->entityCount; i ++){
        if (gameData->world->tempEntityArray[i] != NULL){
            renderPuffEntity(gameData, gameData->world->tempEntityArray[i]);
        }
    }

    //re raycast and texture the area around the mouse
    renderMouseArea(gameData);
}