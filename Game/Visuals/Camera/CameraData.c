//
// Created by Spencer on 5/6/2024.
//


#include "CameraData.h"
#include "Rendering/CastedBlockManager/CastedBlockManager.h"
#include "../../Debuging/Test_Main.h"
#include "../../World/Octree/Tools/KeyMod.h"
#include "../InMenuWindow/InMenuWindow.h"
#include "Camera.h"
#include "Rendering/RayCasting/RayCastingManager.h"
#include "math.h"

struct DistanceCord* createDistanceSortedRelativeCords(struct CameraData* cameraData)
{
    //Create an array of cordnate structs with distances
    int radius = cameraData->viewDistance * 5;
    int totalCords = radius * 2 * radius * 2;

    cameraData->totalDistanceCords = totalCords;

    struct DistanceCord distanceCords[totalCords];

    //Calculate the distances for all the cords
    for (int x = -radius; x < radius; x++)
    {
        for (int y = -radius; y < radius; y++)
        {
            //if in view distance radius
            double distanceFromCenter = sqrt((x * x) + (y * y));
            int arrayIndex = (x + radius + ((y + radius) * radius * 2));

            distanceCords[arrayIndex].x = x;
            distanceCords[arrayIndex].y = y;
            distanceCords[arrayIndex].distance = distanceFromCenter;
        }
    }

    //Sort the cords in order | using selection sort
    for (int i = 0; i < totalCords - 1; i++) {
        int minValueIndex = i;
        for (int j = i + 1; j < totalCords; j++) {
            if (distanceCords[j].distance < distanceCords[minValueIndex].distance) {
                minValueIndex = j;
            }
        }

        // Swap the values
        struct DistanceCord tempDistanceCord = distanceCords[i];
        distanceCords[i] = distanceCords[minValueIndex];
        distanceCords[minValueIndex] = tempDistanceCord;
    }

    //Create the array based off distance
    struct DistanceCord* distanceSortedRelativeCords = malloc(totalCords * sizeof(struct DistanceCord));
    for (int x = 0; x < totalCords; x++)
    {
        distanceSortedRelativeCords[x] = distanceCords[x];
    }

    return distanceSortedRelativeCords;
}


struct CameraData* createCameraData(SDL_Renderer* renderer){
    struct CameraData* cameraData = calloc(1, sizeof(struct CameraData));
    if (cameraData == NULL){
        return NULL;
    }

    //cameraOrientation
    cameraData->direction = North;
    cameraData->xDirection = 1;
    cameraData->yDirection = 1;
    cameraData->rayCastingData = createRayCastingData(cameraData);
    setDirection(cameraData, North);

    //The scale the camera should render
    cameraData->baseBlockScale = 64;
    cameraData->renderScale = 64;
    cameraData->xChunkScaledTextureRez = 0;
    cameraData->yChunkScaledTextureRez = 0;

    //How many chunks will generate
    cameraData->viewDistance = 16;
    cameraData->mouseUpdateDistance = 2;

    //Max 512
    cameraData->chunksScale = 8;
    cameraData->chunkPixelScale = cameraData->baseBlockScale * cameraData->chunksScale;

    //Offset for drawing the screen and shifting
    cameraData->xIsoCamCenter = 0;
    cameraData->yIsoCamCenter = 0;
    cameraData->xIsoChunkCamCenter = 0;
    cameraData->yIsoChunkCamCenter = 0;
    cameraData->castingDistance = 300;


    //Key the camera renderers from
    cameraData->key = modKey(0, 300, 300, 300, 0);

    //Create viewport
    reportBug(" - Creating CastedPool\n");
    cameraData->castedPool = createCastedPool(cameraData, renderer);

    //Create inMenuWindow
    cameraData->inMenuWindow = createInMenuWindow(0, 0, 1280, 720);

    cameraData->distanceSortedRelativeCords = createDistanceSortedRelativeCords(cameraData);

    return cameraData;
}

char* getDirectionString(enum Direction direction){
    if(direction == North){
        return "North";
    }
    if(direction == East){
        return "East";
    }
    if(direction == South){
        return "South";
    }
    if(direction == West){
        return "West";
    }
}