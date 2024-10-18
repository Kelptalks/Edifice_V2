//
// Created by Spencer on 10/2/2024.
//

#include "DroneOnScreenUI.h"

#include "../../../InGameTime/TikManager.h"
#include "../../../World/World.h"
#include "../../../InGameTime/Drone/Drone.h"
#include "../../Camera/CameraData.h"
#include "../../../InGameTime/Drone/DroneInventoryManager/DroneInventoryManager.h"
#include "../../../InGameTime/Drone/DroneToolManager/DroneToolManager.h"
#include "../../../InGameTime/Drone/DroneData.h"
#include "../OnScreenUI/OnScreenUI.h"
#include "DronePopOutWindow/DronePopOutWindow.h"

void renderDroneSelectIcon(struct GameData* gameData, struct Drone* drone){

    float scale = 2;
    float xCor;
    float yCor;

    worldCordsToScreenCords(gameData->cameraData, drone->worldX, drone->worldY, drone->worldZ, &xCor, &yCor);

    int xScale = 120 * scale;
    int yScale = 28 * scale;
    xCor += xScale/4;
    yCor += yScale/2;



    SDL_Rect srcRect = {1160, 420, 120, 28};
    SDL_Rect desRect = {xCor, yCor, 120 * scale, 28 * scale};
    SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet, &srcRect, &desRect);


    char healthString[10] = {0};
    sprintf(healthString, "%i", drone->health);
    int healthTextCorX = xCor + (17 * scale);
    int healthTextCorY = yCor + (11 * scale);
    renderString(gameData, healthString, healthTextCorX, healthTextCorY, scale * 5);

    int fuelTextCorX = xCor + (27 * scale);
    int fuelTextCorY = yCor + (19 * scale);
    char fuelString[10] = {0};
    sprintf(fuelString, "%i", drone->fuel);
    renderString(gameData, fuelString, fuelTextCorX, fuelTextCorY, scale * 5);

    int idTextCorX = xCor + (18 * scale);
    int idTextCorY = yCor + (3 * scale);
    char idString[10] = {0};
    sprintf(idString, "%i", drone->id);
    renderString(gameData, idString, idTextCorX, idTextCorY, scale * 5);


    int xDrawCor = xCor + (53 * scale);
    int yDrawCor = yCor + (6 * scale);
    int itemSpacing = 19 * scale;
    int itemScale = 16 * scale;

    SDL_Texture* texture = gameData->textures->spriteSheet;
    for (int i = 0; i < 3; i++){
        SDL_Rect srcRect = getDroneItemSrcRect(drone->equipment[i]);
        SDL_Rect destRect = {xDrawCor + (i * itemSpacing), yDrawCor, itemScale, itemScale};
        SDL_RenderCopy(gameData->screen->renderer, texture, &srcRect, &destRect);
    }

}

bool handleDroneSelectionIconsInputs(struct GameData* gameData, struct Drone* drone, SDL_Event event){
    float scale = 2;
    float xCor;
    float yCor;

    worldCordsToScreenCords(gameData->cameraData, drone->worldX, drone->worldY, drone->worldZ, &xCor, &yCor);

    int xScale = 120 * scale;
    int yScale = 28 * scale;
    xCor += xScale/4;
    yCor += yScale/2;

    struct DroneOnScreenUI* droneOnScreenUi = gameData->menuManger->droneOnScreenUi;

    int mouseCorX; int mouseCorY;
    SDL_GetMouseState(&mouseCorX, &mouseCorY);

    bool inMouseBoundsX = mouseCorX < (xCor + xScale) && mouseCorX > xCor;
    bool inMouseBoundsY = mouseCorY < (yCor + yScale) && mouseCorY > yCor;
    if (inMouseBoundsX && inMouseBoundsY) {
        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
            if (droneOnScreenUi->dronePopOutWindow[drone->id] == NULL){
                droneOnScreenUi->dronePopOutWindow[droneOnScreenUi->currentDroneWindowCount] = createDronePopOutWindow(
                        drone, xCor + xScale, yCor, 2);
                droneOnScreenUi->currentDroneWindowCount++;
            }
            else{
                droneOnScreenUi->dronePopOutWindow[drone->id]->visible = !droneOnScreenUi->dronePopOutWindow[drone->id]->visible;
                droneOnScreenUi->dronePopOutWindow[drone->id]->xCor = xCor + xScale;
                droneOnScreenUi->dronePopOutWindow[drone->id]->yCor = yCor;
            }
        }
        return true;
    }
    return false;

}

struct DroneOnScreenUI* createDroneOnScreenUI(){
    struct DroneOnScreenUI* droneOnScreenUi = malloc(sizeof(struct DroneOnScreenUI));
    if (droneOnScreenUi == NULL){
        reportBug("failed to create Drone onscreen UI\n");
        return NULL;
    }

    droneOnScreenUi->visible = true;
    droneOnScreenUi->maxDroneWindows = 100;
    droneOnScreenUi->currentDroneWindowCount = 0;

    droneOnScreenUi->dronePopOutWindow = malloc(sizeof (struct DroneOnScreenUI*) * droneOnScreenUi->maxDroneWindows);
    if (droneOnScreenUi->dronePopOutWindow == NULL){
        free(droneOnScreenUi);
        reportBug("failed to create Drone onscreen UI\n");
        return NULL;
    }
    for (int i = 0; i < droneOnScreenUi->maxDroneWindows; i++){
        droneOnScreenUi->dronePopOutWindow[i] = NULL;
    }


    return droneOnScreenUi;
}

void renderDroneOnScreenUI(struct GameData* gameData){
    struct World* world = gameData->world;
    struct DroneOnScreenUI* droneOnScreenUi = gameData->menuManger->droneOnScreenUi;

    if (world->droneData->droneCount > 0){
        for (int i = 0; i < world->droneData->droneCount; i++){
            struct Drone* drone = world->droneData->drones[i];
            renderDroneSelectIcon(gameData, drone);
        }

        for (int i = 0; i < droneOnScreenUi->currentDroneWindowCount; i++) {
            struct DronePopOutWindow* dronePopOutWindow = droneOnScreenUi->dronePopOutWindow[i];
            if (dronePopOutWindow->visible) {
                renderDronePopOutWindow(gameData, dronePopOutWindow);
            }
        }
    }

}

bool handleDroneOnScreenUI(struct GameData* gameData, SDL_Event event){
    bool onDroneScreenUIMouseOn = false;

    struct World* world = gameData->world;
    for (int i = 0; i < world->droneData->droneCount; i++){
        struct Drone* drone = world->droneData->drones[i];
        onDroneScreenUIMouseOn = onDroneScreenUIMouseOn || handleDroneSelectionIconsInputs(gameData, drone, event);
    }

    struct DroneOnScreenUI* droneOnScreenUi = gameData->menuManger->droneOnScreenUi;
    for (int i = 0; i < droneOnScreenUi->currentDroneWindowCount; i++) {
        if (droneOnScreenUi->dronePopOutWindow[i]->visible) {
            onDroneScreenUIMouseOn = onDroneScreenUIMouseOn || HandleDronePopOutMenuInputs(gameData, droneOnScreenUi->dronePopOutWindow[i], event);
        }
    }

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_F1 :
                droneOnScreenUi->visible = false;
                gameData->menuManger->onScreenUi->visible = true;
                break;
            case SDLK_MINUS :
                if (gameData->tikManager->droneTickInterval > 1) {
                    gameData->tikManager->tikTime -= 5;
                    gameData->tikManager->droneTickInterval -= 1;
                }
                break;
            case SDLK_PLUS :
                if (gameData->tikManager->droneTickInterval < 5) {
                    gameData->tikManager->droneTickInterval += 1;
                    gameData->tikManager->tikTime += 5;
                }
            break;
        }
    }

    return onDroneScreenUIMouseOn;
}