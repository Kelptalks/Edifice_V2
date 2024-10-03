//
// Created by Spencer on 10/2/2024.
//

#include "DroneOnScreenUI.h"
#include "../../../World/World.h"
#include "../../../InGameTime/Drone/Drone.h"
#include "../../Camera/IsoCordTool/IsoCordManager.h"
#include "../../Camera/CameraData.h"
#include "../../../InGameTime/Drone/DroneInventoryManager/DroneInventoryManager.h"
#include "../../../InGameTime/Drone/DroneToolManager/DroneToolManager.h"

void renderDroneSelectIcon(struct GameData* gameData, struct Drone* drone, int xCor, int yCor, float scale){
    SDL_Rect srcRect = {1162, 420, 120, 28};
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
        SDL_Rect srcRect = getToolSrcRect(drone->tools[i]);
        SDL_Rect destRect = {xDrawCor + (i * itemSpacing), yDrawCor, itemScale, itemScale};
        SDL_RenderCopy(gameData->screen->renderer, texture, &srcRect, &destRect);
    }

}

bool handleDroneSelectionIconsInputs(struct GameData* gameData, struct Drone* drone, int xCor, int yCor, float scale, SDL_Event event){
    int xScale = 120 * scale;
    int yScale = 28 * scale;

    struct DroneOnScreenUI* droneOnScreenUi = gameData->menuManger->droneOnScreenUi;

    int mouseCorX; int mouseCorY;
    SDL_GetMouseState(&mouseCorX, &mouseCorY);

    bool inMouseBoundsX = mouseCorX < (xCor + xScale) && mouseCorX > xCor;
    bool inMouseBoundsY = mouseCorY < (yCor + yScale) && mouseCorY > yCor;
    if (inMouseBoundsX && inMouseBoundsY) {
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (droneOnScreenUi->dronePopOutWindow[drone->id] == NULL){
                droneOnScreenUi->dronePopOutWindow[droneOnScreenUi->currentDroneWindowCount] = createDronePopOutWindow(
                        drone, xCor + xScale, yCor, scale);
                droneOnScreenUi->currentDroneWindowCount++;
            }
            else{
                droneOnScreenUi->dronePopOutWindow[drone->id]->visible = true;
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

    if (world->droneCount > 0){
        for (int i = 0; i < world->droneCount; i++){
            struct Drone* drone = world->drones[i];
            renderDroneSelectIcon(gameData, drone, 0, i * (28 * 2), 2);
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
    for (int i = 0; i < world->droneCount; i++){
        struct Drone* drone = world->drones[i];
        handleDroneSelectionIconsInputs(gameData, drone, 0, i * (28 * 2), 2, event);
    }

    struct DroneOnScreenUI* droneOnScreenUi = gameData->menuManger->droneOnScreenUi;
    for (int i = 0; i < droneOnScreenUi->currentDroneWindowCount; i++) {
        onDroneScreenUIMouseOn = HandleDronePopOutMenuInputs(gameData, droneOnScreenUi->dronePopOutWindow[i], event);
    }

    return onDroneScreenUIMouseOn;
}