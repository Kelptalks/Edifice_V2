//
// Created by Spencer on 10/3/2024.
//

#include "DronePopOutWindow.h"
#include "../../../../InGameTime/Drone/DroneInventoryManager/DroneInventoryManager.h"
#include "../../../Camera/IsoCordTool/IsoCordManager.h"
#include "../../../../InGameTime/Drone/DroneToolManager/DroneToolManager.h"
#include "../../../Camera/CameraData.h"

struct DronePopOutWindow* createDronePopOutWindow(struct Drone* drone, int xCor, int yCor, float scale){
    struct DronePopOutWindow* dronePopOutWindow = malloc(sizeof (struct DronePopOutWindow));

    dronePopOutWindow->drone = drone;
    dronePopOutWindow->xCor = xCor;
    dronePopOutWindow->yCor = yCor;
    dronePopOutWindow->scale = scale;
    dronePopOutWindow->xDirection = 1;
    dronePopOutWindow->yDirection = 1;
    dronePopOutWindow->xRez = scale * 263;
    dronePopOutWindow->yRez = scale * 196;
    dronePopOutWindow->visible = true;
    dronePopOutWindow->mouseOnExitButton = false;
    dronePopOutWindow->grabbed = false;
    dronePopOutWindow->direction = 0;

    return dronePopOutWindow;
}

void renderDroneWindow(struct GameData* gameData, struct DronePopOutWindow* droneWindow){
    int windowCorX = droneWindow->xCor;
    int windowCorY = droneWindow->yCor;
    float scale = droneWindow->scale;
    struct Drone* drone = droneWindow->drone;

    //Render Window
    SDL_Rect srcRect = {1017, 448, 263, 196};
    SDL_Rect destRect = {windowCorX, windowCorY, droneWindow->xRez, droneWindow->yRez};
    SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet, &srcRect, &destRect);

    char healthString[10] = {0};
    sprintf(healthString, "%i", drone->health);
    int healthTextCorX = windowCorX + (236 * scale);
    int healthTextCorY = windowCorY + (119 * scale);
    renderString(gameData, healthString, healthTextCorX, healthTextCorY, scale * 5);

    int fuelTextCorX = windowCorX + (228 * scale);
    int fuelTextCorY = windowCorY + (133 * scale);
    char fuelString[10] = {0};
    sprintf(fuelString, "%i", drone->fuel);
    renderString(gameData, fuelString, fuelTextCorX, fuelTextCorY, scale * 5);

    int idTextCorX = windowCorX + (216 * scale);
    int idTextCorY = windowCorY + (147 * scale);
    char idString[10] = {0};
    sprintf(idString, "%i", drone->id);
    renderString(gameData, idString, idTextCorX, idTextCorY, scale * 5);

    int busyTextCorX = windowCorX + (226 * scale);
    int busyTextCorY = windowCorY + (162 * scale);
    char busyString[10] = {0};
    sprintf(busyString, "%i +", drone->busyTime);
    renderString(gameData, busyString, busyTextCorX, busyTextCorY, scale * 5);

    int exitButtonRezX = 9 * droneWindow->scale;
    int exitButtonRezY = 9 * droneWindow->scale;
    int exitButtonCorX = droneWindow->xCor + (droneWindow->xRez - (exitButtonRezX));
    int exitButtonCorY = droneWindow->yCor;

    if (droneWindow->mouseOnExitButton) {
        SDL_Rect exitRect = {exitButtonCorX, exitButtonCorY, exitButtonRezX, exitButtonRezY};
        SDL_SetRenderDrawColor(gameData->screen->renderer, 255, 0, 0, 75);
        SDL_RenderFillRect(gameData->screen->renderer, &exitRect);
    }

}

void renderDronesInventory(struct GameData* gameData, struct DronePopOutWindow* droneWindow){
    float scale = droneWindow->scale;
    int xDrawCor = droneWindow->xCor + (200 * scale);
    int yDrawCor = droneWindow->yCor + (57 * scale);

    int itemSpacing = 19 * scale;
    int itemScale = 16 * scale;

    struct Drone* drone = droneWindow->drone;

    int xMouseCor = gameData->debugMenu->xMouseCor;
    int yMouseCor = gameData->debugMenu->yMouseCor;

    SDL_Texture* texture = gameData->textures->spriteSheet;
    for (int y = 0; y < 3; y++){
        for (int x = 0; x < 3; x++){
            int itemIndex = x + (3 * y);
            SDL_Rect srcRect = getDroneItemSrcRect(getItemInSlot(drone, itemIndex));

            int xSlotCor = xDrawCor + (x * itemSpacing);
            int ySlotCor = yDrawCor + (y * itemSpacing);

            SDL_Rect destRect = {xSlotCor, ySlotCor, itemScale, itemScale};
            SDL_RenderCopy(gameData->screen->renderer, texture, &srcRect, &destRect);

            //Render string if mouse is on cord
            int itemCountInSlot = getItemCountInSlot(drone, itemIndex);
            if (itemCountInSlot > 0) {
                char itemCount[10] = {0};
                sprintf(itemCount, "%i", itemCountInSlot);
                renderStringCentered(gameData, itemCount, xSlotCor + (itemScale/2), ySlotCor + (itemScale/2), scale * 5);
            }

        }
    }


}

void renderDroneTools(struct GameData* gameData, struct DronePopOutWindow* droneWindow){
    float scale = droneWindow->scale;
    int xDrawCor = droneWindow->xCor + (199 * scale);
    int yDrawCor = droneWindow->yCor + (22 * scale);
    int itemSpacing = 19 * scale;
    int itemScale = 16 * scale;


    SDL_Texture* texture = gameData->textures->spriteSheet;
    for (int i = 0; i < 3; i++){
        SDL_Rect srcRect = getDroneItemSrcRect(droneWindow->drone->equipment[i]);
        SDL_Rect destRect = {xDrawCor + (i * itemSpacing), yDrawCor, itemScale, itemScale};
        SDL_RenderCopy(gameData->screen->renderer, texture, &srcRect, &destRect);
    }
}

void renderDronesBlocksInArea(struct GameData* gameData, struct DronePopOutWindow* droneWindow){
    int windowCorX = droneWindow->xCor;
    int windowCorY = droneWindow->yCor;
    float scale = droneWindow->scale;
    struct Drone* drone = droneWindow->drone;

    int baseBlockScale = gameData->cameraData->baseBlockScale * 2;
    SDL_Texture* spriteSheet = gameData->textures->spriteSheet;

    //Offset to center rendering
    windowCorX += (baseBlockScale) * (scale/2) + scale;
    windowCorY += (baseBlockScale) * (scale/2) + scale;

    int xDirection = droneWindow->xDirection;
    int yDirection = droneWindow->yDirection;

    int blockScale = (baseBlockScale * scale) / 2;

    for (int z = 0; z < 3; z++){
        for (int y = 0; y < 3; y++){
            for (int x = 0; x < 3; x++){
                int screenX; int screenY;
                isoToScreen(blockScale, x - z, y - z, &screenX, &screenY);
                enum Block block = getBlockAtWorldCor(gameData->world,
                                                      drone->worldX + (xDirection * (x - 1)),
                                                      drone->worldY + (yDirection * (y - 1)),
                                                      drone->worldZ + (z - 1));
                SDL_Rect srcRect = getBlockSpriteSheetSrcRect(block);
                SDL_Rect destRect = {screenX + windowCorX, screenY + windowCorY, blockScale, blockScale};

                SDL_RenderCopy(gameData->screen->renderer, spriteSheet, &srcRect, &destRect);

            }
        }
    }

}

void renderDronePopOutWindow(struct GameData* gameData, struct DronePopOutWindow* dronePopOutWindow){
    renderDroneWindow(gameData, dronePopOutWindow);
    renderDronesInventory(gameData, dronePopOutWindow);
    renderDronesBlocksInArea(gameData, dronePopOutWindow);
    renderDroneTools(gameData, dronePopOutWindow);
}

void updatePopOutWindowDirection(struct DronePopOutWindow* dronePopOutWindow){
    if (dronePopOutWindow->direction > 3){
        dronePopOutWindow->direction = 0;
    }
    if (dronePopOutWindow->direction < 0){
        dronePopOutWindow->direction = 3;
    }
    if (dronePopOutWindow->direction == North){
        dronePopOutWindow->xDirection = 1;
        dronePopOutWindow->yDirection = 1;
    }
    else if (dronePopOutWindow->direction == South){
        dronePopOutWindow->xDirection = -1;
        dronePopOutWindow->yDirection = -1;
    }
    else if (dronePopOutWindow->direction == East){
        dronePopOutWindow->xDirection= -1;
        dronePopOutWindow->yDirection = 1;
    }
    else if (dronePopOutWindow->direction == West){
        dronePopOutWindow->xDirection = 1;
        dronePopOutWindow->yDirection = -1;
    }
}

bool handleDroneArrowInput(struct DronePopOutWindow* dronePopOutWindow, int mouseCorX, int mouseCorY, SDL_Event event){
    int xArrowScale = 24 * dronePopOutWindow->scale;
    int yArrowScale = 24 * dronePopOutWindow->scale;

    int yArrowCor = dronePopOutWindow->yCor + (dronePopOutWindow->yRez - yArrowScale);
    int xArrowRightCor = (170 * dronePopOutWindow->scale) + dronePopOutWindow->xCor;
    int xArrowLeftCor = dronePopOutWindow->xCor;

    bool inYRotateBounds = (mouseCorY < (yArrowCor + yArrowScale)) && (mouseCorY > yArrowCor);
    bool inRightRotateBoundsX = (mouseCorX < (xArrowRightCor + xArrowScale)) && (mouseCorX > xArrowRightCor);
    bool inLeftRotateBoundsX = (mouseCorX < (xArrowLeftCor + xArrowScale)) && (mouseCorX > xArrowLeftCor);


    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (inYRotateBounds) {
            if (inLeftRotateBoundsX) {
                dronePopOutWindow->direction++;
                updatePopOutWindowDirection(dronePopOutWindow);
                return true;
            } else if (inRightRotateBoundsX) {
                dronePopOutWindow->direction--;
                updatePopOutWindowDirection(dronePopOutWindow);
                return true;
            }
        }
    }
    return false;
}

bool HandleDronePopOutMenuInputs(struct GameData* gameData, struct DronePopOutWindow* dronePopOutWindow, SDL_Event event){
    int mouseCorX; int mouseCorY;
    SDL_GetMouseState(&mouseCorX, &mouseCorY);


    if (event.type == SDL_MOUSEBUTTONUP){
        dronePopOutWindow->grabbed = false;
    }
    if (dronePopOutWindow->grabbed){
        dronePopOutWindow->xCor = mouseCorX - dronePopOutWindow->xGrabCor;
        dronePopOutWindow->yCor = mouseCorY - dronePopOutWindow->yGrabCor;
    }

    bool inWindowXBounds = (dronePopOutWindow->xCor < mouseCorX) && (mouseCorX < dronePopOutWindow->xCor + dronePopOutWindow->xRez);
    bool inWindowYBounds = (dronePopOutWindow->yCor < mouseCorY) && (mouseCorY < dronePopOutWindow->yCor + dronePopOutWindow->yRez);
    if (inWindowXBounds && inWindowYBounds) {
        handleDroneArrowInput(dronePopOutWindow, mouseCorX, mouseCorY, event);

        int exitButtonRezX = 9 * dronePopOutWindow->scale;
        int exitButtonRezY = 9 * dronePopOutWindow->scale;
        int exitButtonCorX = dronePopOutWindow->xCor + (dronePopOutWindow->xRez - (exitButtonRezX));
        int exitButtonCorY = dronePopOutWindow->yCor;

        bool exitButtonInXBounds = (mouseCorX < (exitButtonCorX + exitButtonRezX)) && (mouseCorX > exitButtonCorX);
        bool exitButtonInYBounds = (mouseCorY < (exitButtonCorY + exitButtonRezY)) && (mouseCorY > exitButtonCorY);

        if (exitButtonInXBounds && exitButtonInYBounds){
            dronePopOutWindow->mouseOnExitButton = true;
        }
        else{
            dronePopOutWindow->mouseOnExitButton = false;
        }

        int xBarCor = dronePopOutWindow->xCor + (193 * dronePopOutWindow->scale);
        int xBarRez = 61 * dronePopOutWindow->scale;
        bool inBarXBounds = (mouseCorX < (xBarCor + xBarRez)) && (mouseCorX > xBarCor);

        if (event.type == SDL_MOUSEBUTTONDOWN){
            if (inBarXBounds && exitButtonInYBounds){
                dronePopOutWindow->grabbed = true;
                dronePopOutWindow->xGrabCor = (mouseCorX - dronePopOutWindow->xCor);
                dronePopOutWindow->yGrabCor = (mouseCorY - dronePopOutWindow->yCor);
            }
            if (dronePopOutWindow->mouseOnExitButton){
                dronePopOutWindow->visible = false;
            }
        }
        return true;
    }

    return false;
}