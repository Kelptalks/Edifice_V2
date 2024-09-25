//
// Created by Spencer on 9/24/2024.
//


#include "OnScreenUI.h"
#include "../../../PlayerData/PlayerData.h"
#include "../../Camera/CameraData.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * HotBarRendering
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

SDL_Rect getHotBarSlotSrcRect(bool selected){
    int x = 1216;
    int y = 176;
    int w = 32;
    int h = 32;

    if (selected){
        x = 1216 + w;
    }

    SDL_Rect rect = {x, y, w, h};
    return rect;
}

void renderHotBarSlot(struct GameData* gameData, int xDrawCor, int yDrawCor, enum Block block, bool selected){
    struct OnScreenUI* onScreenUi = gameData->menuManger->onScreenUi;
    int spacedScale = onScreenUi->slotSpacedScale;
    int scale = onScreenUi->scale;
    int blockScale = onScreenUi->blockScale;
    int blockCenteringOffset = onScreenUi->blockCenteringOffset;

    //Get the hotBarSource rect
    SDL_Rect hotBarSlotSrcRect = {1216, 176, 32, 32};
    if (selected){
        hotBarSlotSrcRect.w + 32;
    }


    //Calculate the drawing location
    SDL_Rect destRect = {xDrawCor, yDrawCor, scale, scale};
    if (selected){
        SDL_Rect selectedHotBarSlotSrcRect = getHotBarSlotSrcRect(true);
        SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet, &selectedHotBarSlotSrcRect, &destRect);
    }
    else{
        SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet, &hotBarSlotSrcRect, &destRect);
    }

    //Draw the block slightly smaller
    destRect.h = blockScale;
    destRect.w = blockScale;

    //Offset to center the block in the slot
    destRect.x -= blockCenteringOffset;
    destRect.y -= blockCenteringOffset;

    //Get block and render
    SDL_Rect blockSrcRect = getBlockSpriteSheetSrcRect(block);
    SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet, &blockSrcRect, &destRect);
}


void updateOnScreenUICords(struct GameData* gameData){
    struct OnScreenUI* onScreenUi = gameData->menuManger->onScreenUi;

    onScreenUi->scale = gameData->screen->xRez / 24;
    onScreenUi->hotBarCorX = onScreenUi->scale / 4;
    onScreenUi->hotBarCorY = (gameData->screen->yRez - (int) (onScreenUi->scale * 1.25));

    onScreenUi->slotSpacedScale = onScreenUi->scale/8 + onScreenUi->scale;
    onScreenUi->blockScale = (int) (onScreenUi->scale * 0.88);
    onScreenUi->blockCenteringOffset = (onScreenUi->blockScale - onScreenUi->scale)/2;
}

struct OnScreenUI* createOnScreenUI(){
    struct OnScreenUI* onScreenUi = malloc(sizeof (struct OnScreenUI));
    if (onScreenUi == NULL){
        reportBug("failed to create onscreen UI\n");
        return NULL;
    }

    return onScreenUi;
}

void renderHotBar(struct GameData* gameData, struct HotBar* hotBar, int xDrawCor, int yDrawCor, int scale){

    SDL_Rect hotBarSlotSrcRect = getHotBarSlotSrcRect(false);
    int baseBlockScale = gameData->cameraData->baseBlockScale;

    struct OnScreenUI* onScreenUi = gameData->menuManger->onScreenUi;

    //Cord Spacing
    int SpacedScale = onScreenUi->slotSpacedScale;
    int blockScale = onScreenUi->blockScale;
    int blockCenteringOffset = onScreenUi->blockCenteringOffset;

    for (int i = 0; i < hotBar->length; i++){
        enum Block block = hotBar->slots[i];

        //Get the sprite of the block
        SDL_Rect blockSrcRect = getBlockSpriteSheetSrcRect(block);

        //Calculate the drawing location
        SDL_Rect destRect = {xDrawCor + (i * SpacedScale), yDrawCor, scale, scale};
        if (i != hotBar->selectedSlot){
            SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet, &hotBarSlotSrcRect, &destRect);
        }
        else{
            SDL_Rect selectedHotBarSlotSrcRect = getHotBarSlotSrcRect(true);
            SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet, &selectedHotBarSlotSrcRect, &destRect);
        }

        //Draw the block slightly smaller
        destRect.h = blockScale;
        destRect.w = blockScale;

        //Offset to center the block in the slot
        destRect.x -= blockCenteringOffset;
        destRect.y -= blockCenteringOffset;

        SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet, &blockSrcRect, &destRect);
    }
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * BlockSelection WindowRendering
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

void renderBlockSelectionMenu(struct GameData* gameData, int xDrawCor, int yDrawCor, int xMouseCor, int yMouseCor, int scale){

    struct BlockSelectionMenu* blockSelectionMenu = gameData->playerData->blockSelectionMenu;
    SDL_Rect hotBarSlotSrcRect = getHotBarSlotSrcRect(false);

    //Cord Spacing
    struct OnScreenUI* onScreenUi = gameData->menuManger->onScreenUi;

    //Render the main Box
    int xMainBoxRez = blockSelectionMenu->rowLength * onScreenUi->slotSpacedScale;
    int yMainBoxRez = blockSelectionMenu->columnLength * onScreenUi->slotSpacedScale;

    SDL_Rect srcRect = {1136, 240, 144, 80};
    SDL_Rect destRect = {xDrawCor, yDrawCor, xMainBoxRez, yMainBoxRez};
    SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet, &srcRect, &destRect);


    //Render the grid of blocks
    for (int x = 0; x < blockSelectionMenu->rowLength; x++){
        for (int y = 0; y < blockSelectionMenu->columnLength; y++){
            enum Block block = blockSelectionMenu->blocks[x][y];
            int renderingCorX = x * onScreenUi->slotSpacedScale;
            int renderingCorY = y * onScreenUi->slotSpacedScale;

            renderHotBarSlot(gameData, renderingCorX, renderingCorY, block, false);
        }
    }

    //Render the name of the block the mouse is on




}


void renderOnScreenUI(struct GameData* gameData){
    //Calculate the scale of the hot bar base on screen resolution

    struct OnScreenUI* onScreenUi = gameData->menuManger->onScreenUi;
    if (onScreenUi->visible) {
        renderHotBar(gameData, gameData->playerData->hotBar, onScreenUi->hotBarCorX, onScreenUi->hotBarCorY,
                     onScreenUi->scale);
        renderBlockSelectionMenu(gameData, 0, 0, gameData->debugMenu->xMouseCor, gameData->debugMenu->yMouseCor,
                                 onScreenUi->scale);
    }
}

//return if the onScreen UI was used
bool handleOnScreenUIInput(struct GameData* gameData, SDL_Event event){
    struct OnScreenUI* onScreenUi = gameData->menuManger->onScreenUi;

    //If mouse was on elements
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_1 :
                gameData->playerData->hotBar->selectedSlot = 0;
                break;
            case SDLK_2 :
                gameData->playerData->hotBar->selectedSlot = 1;
                break;
            case SDLK_3 :
                gameData->playerData->hotBar->selectedSlot = 2;
                break;
            case SDLK_4 :
                gameData->playerData->hotBar->selectedSlot = 3;
                break;
            case SDLK_5 :
                gameData->playerData->hotBar->selectedSlot = 4;
                break;
            case SDLK_6 :
                gameData->playerData->hotBar->selectedSlot = 5;
                break;
            case SDLK_7 :
                gameData->playerData->hotBar->selectedSlot = 6;
                break;
            case SDLK_8 :
                gameData->playerData->hotBar->selectedSlot = 7;
                break;
            case SDLK_9 :
                gameData->playerData->hotBar->selectedSlot = 8;
                break;
            case SDLK_0 :
                gameData->playerData->hotBar->selectedSlot = 9;
                break;
            case SDLK_F1 :
                onScreenUi->visible = !onScreenUi->visible;
                break;
        }
        gameData->playerData->block = getHotBarSlotBlockType(gameData->playerData->hotBar, gameData->playerData->hotBar->selectedSlot);
    }


    //If mouse was not on any elements
    return false;
}