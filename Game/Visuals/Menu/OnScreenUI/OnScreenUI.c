//
// Created by Spencer on 9/24/2024.
//


#include "OnScreenUI.h"
#include "../../../PlayerData/PlayerData.h"
#include "../../Camera/CameraData.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Management
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

struct OnScreenUI* createOnScreenUI(){
    struct OnScreenUI* onScreenUi = malloc(sizeof (struct OnScreenUI));
    if (onScreenUi == NULL){
        reportBug("failed to create onscreen UI\n");
        return NULL;
    }

    onScreenUi->visible = true;
    onScreenUi->blockSelectionMenuVisible = false;
    onScreenUi->blockSelected = Air;

    return onScreenUi;
}

void updateOnScreenUICords(struct GameData* gameData){
    struct OnScreenUI* onScreenUi = gameData->menuManger->onScreenUi;

    onScreenUi->scale = gameData->screen->xRez / 32;

    onScreenUi->slotSpacedScale = onScreenUi->scale/8 + onScreenUi->scale;
    onScreenUi->blockScale = (int) (onScreenUi->scale * 0.88);
    onScreenUi->blockCenteringOffset = (onScreenUi->blockScale - onScreenUi->scale)/2;

    //Hot Bar
    onScreenUi->hotBarRezX = (gameData->playerData->hotBar->length) * onScreenUi->slotSpacedScale;
    onScreenUi->hotBarRezY = onScreenUi->slotSpacedScale;
    onScreenUi->hotBarCorX = (gameData->screen->xRez/2) - (onScreenUi->hotBarRezX/2);
    onScreenUi->hotBarCorY = (gameData->screen->yRez - (int) (onScreenUi->scale * 1.25));

    //Block Menu
    onScreenUi->blockMenuRezX = gameData->playerData->blockSelectionMenu->rowLength * onScreenUi->slotSpacedScale;
    onScreenUi->blockMenuRezY = gameData->playerData->blockSelectionMenu->columnLength * onScreenUi->slotSpacedScale;
    onScreenUi->blockMenuCorX = (gameData->screen->xRez/2) - (onScreenUi->blockMenuRezX/2);
    onScreenUi->blockMenuCorY = (gameData->screen->yRez/2) - (onScreenUi->blockMenuRezY/2);

    //Text
    onScreenUi->textScale = onScreenUi->scale/4;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Rendering
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

void renderHotBar(struct GameData* gameData){
    struct HotBar* hotBar = gameData->playerData->hotBar;

    struct OnScreenUI* onScreenUi = gameData->menuManger->onScreenUi;

    for (int i = 0; i < hotBar->length; i++){
        enum Block block = hotBar->slots[i];

        //Get the sprite of the block
        int renderingCorX = (i * onScreenUi->slotSpacedScale) + onScreenUi->hotBarCorX;
        int renderingCorY = onScreenUi->hotBarCorY;

        //Calculate the drawing location
        if (i == hotBar->selectedSlot){
            renderStringCentered(gameData, getBlockName(block), (gameData->screen->xRez/2), renderingCorY - (onScreenUi->textScale), onScreenUi->textScale);
            renderHotBarSlot(gameData, renderingCorX, renderingCorY, block, true);
        }
        else {
            renderHotBarSlot(gameData, renderingCorX, renderingCorY, block, false);
        }
    }
}

void renderBlockSelectionMenu(struct GameData* gameData){

    struct BlockSelectionMenu* blockSelectionMenu = gameData->playerData->blockSelectionMenu;

    //Cord Spacing
    struct OnScreenUI* onScreenUi = gameData->menuManger->onScreenUi;

    //Render the main Box
    SDL_Rect srcRect = {1136, 240, 144, 80};
    SDL_Rect destRect = {onScreenUi->blockMenuCorX, onScreenUi->blockMenuCorY, onScreenUi->blockMenuRezX, onScreenUi->blockMenuRezY};
    SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet, &srcRect, &destRect);


    //Get mouse cords on window
    int relativeXMouseCor = gameData->debugMenu->xMouseCor - onScreenUi->blockMenuCorX;
    int relativeYMouseCor = gameData->debugMenu->yMouseCor - onScreenUi->blockMenuCorY;

    //Get the cords of the selected box if in bounds of window
    int selectedSlotX = 999;
    int selectedSlotY = 999;
    if (relativeXMouseCor >= 0 && relativeXMouseCor < onScreenUi->blockMenuRezX && relativeYMouseCor >= 0 && relativeYMouseCor < onScreenUi->blockMenuRezY){
        selectedSlotX = relativeXMouseCor / onScreenUi->slotSpacedScale;
        selectedSlotY = relativeYMouseCor / onScreenUi->slotSpacedScale;
    }


    //Render the grid of blocks
    for (int x = 0; x < blockSelectionMenu->rowLength; x++){
        for (int y = 0; y < blockSelectionMenu->columnLength; y++) {
            enum Block block = blockSelectionMenu->blocks[x][y];
            int renderingCorX = x * onScreenUi->slotSpacedScale + onScreenUi->blockMenuCorX;
            int renderingCorY = y * onScreenUi->slotSpacedScale + onScreenUi->blockMenuCorY;

            if (x == selectedSlotX && y == selectedSlotY) {
                renderHotBarSlot(gameData, renderingCorX, renderingCorY, block, true);
            }
            else {
                renderHotBarSlot(gameData, renderingCorX, renderingCorY, block, false);
            }
        }
    }

    //Render the name of the block the mouse is on

    if (selectedSlotX < blockSelectionMenu->rowLength && selectedSlotY < blockSelectionMenu->columnLength) {
        int renderingCorX = gameData->debugMenu->xMouseCor;
        int renderingCorY = gameData->debugMenu->yMouseCor;
        enum Block block = blockSelectionMenu->blocks[selectedSlotX][selectedSlotY];
        renderStringCentered(gameData, getBlockName(block), renderingCorX, renderingCorY + onScreenUi->blockScale/3, onScreenUi->textScale);
    }



}

void renderSelectedBlock(struct GameData* gameData){
    struct OnScreenUI* onScreenUi = gameData->menuManger->onScreenUi;
    //Render block on the mouse if one is selected
    if (onScreenUi->blockSelected != Air) {

        int xMouseCor = gameData->debugMenu->xMouseCor - (onScreenUi->blockScale/2);
        int yMouseCor = gameData->debugMenu->yMouseCor - (onScreenUi->blockScale/2);

        SDL_Rect destRect = {xMouseCor, yMouseCor, onScreenUi->blockScale, onScreenUi->blockScale};
        SDL_Rect blockSrcRect = getBlockSpriteSheetSrcRect(onScreenUi->blockSelected);
        SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet, &blockSrcRect, &destRect);
    }
}

//Render UI
void renderOnScreenUI(struct GameData* gameData){
    updateOnScreenUICords(gameData);

    //Calculate the scale of the hot bar base on screen resolution
    struct OnScreenUI* onScreenUi = gameData->menuManger->onScreenUi;
    if (onScreenUi->visible) {
        renderHotBar(gameData);

        //Render block selection menu if on
        if (onScreenUi->blockSelectionMenuVisible) {
            renderBlockSelectionMenu(gameData);
            renderSelectedBlock(gameData);
        }
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Controls
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */


void handleOnScreenUIKeyInputs(struct GameData* gameData, SDL_Event event){
    struct OnScreenUI* onScreenUi = gameData->menuManger->onScreenUi;
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
            case SDLK_TAB:
                onScreenUi->blockSelectionMenuVisible = !onScreenUi->blockSelectionMenuVisible;
                break;
        }
        gameData->playerData->block = getHotBarSlotBlockType(gameData->playerData->hotBar, gameData->playerData->hotBar->selectedSlot);
    }
}

bool handleOnScreenUIMouseInputs(struct GameData* gameData, SDL_Event event){
    struct OnScreenUI* onScreenUi = gameData->menuManger->onScreenUi;

    int mouseCorX; int mouseCorY;
    SDL_GetMouseState(&mouseCorX, &mouseCorY);

    //If Left Mouse Button Is clicked
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        //If there is currently no block selected
        if (onScreenUi->blockSelected == Air) {
            //If mouse is on In Menu Window
            int relativeMouseX = mouseCorX - onScreenUi->blockMenuCorX;
            int relativeMouseY = mouseCorY - onScreenUi->blockMenuCorY;

            bool inMenusXBounds = (relativeMouseX >= 0 && relativeMouseX <= onScreenUi->blockMenuRezX);
            bool inMenusYBounds = (relativeMouseY >= 0 && relativeMouseY <= onScreenUi->blockMenuRezY);
            if (inMenusXBounds && inMenusYBounds) {
                struct BlockSelectionMenu *blockSelectionMenu = gameData->playerData->blockSelectionMenu;
                int blockRow = relativeMouseX / onScreenUi->slotSpacedScale;
                int blockColumn = relativeMouseY / onScreenUi->slotSpacedScale;
                //If in bounds of the block selection menu
                if (blockRow < blockSelectionMenu->rowLength && blockColumn < blockSelectionMenu->columnLength) {
                    onScreenUi->blockSelected = blockSelectionMenu->blocks[blockRow][blockColumn];
                    playSound(gameData->soundManager, SoundMenuButtonClick);
                }
            }
            return true;
        }
        //If there is a block selected
        else{
            //check if on Hot bar Slot
            int relativeMouseX = mouseCorX - onScreenUi->hotBarCorX;
            int relativeMouseY = mouseCorY - onScreenUi->hotBarCorY;

            bool inHotBarXBounds = relativeMouseX >= 0 && relativeMouseX <= onScreenUi->hotBarRezX;
            bool inHotBarYBounds = relativeMouseY >= 0 && relativeMouseY <= onScreenUi->hotBarRezY;
            if (inHotBarXBounds && inHotBarYBounds){
                int hotBarSlot = relativeMouseX / onScreenUi->slotSpacedScale;
                setHotBarSlotBlockType(gameData->playerData->hotBar, hotBarSlot, onScreenUi->blockSelected);
                playSound(gameData->soundManager, SoundMenuButtonClick);
            }

            //Clear to air
            onScreenUi->blockSelected = Air;
            return true;
        }

    }


}

//return if the onScreen UI was used
bool handleOnScreenUIInput(struct GameData* gameData, SDL_Event event){
    struct OnScreenUI* onScreenUi = gameData->menuManger->onScreenUi;
    bool UIElementClicked = false;
    //Handle Key inputs
    handleOnScreenUIKeyInputs(gameData, event);

    //HandleMouse Inputs
    if (onScreenUi->blockSelectionMenuVisible){
        UIElementClicked = handleOnScreenUIMouseInputs(gameData, event);
    }
    else if (onScreenUi->blockSelected != Air){
        onScreenUi->blockSelected = Air;
    }
    return UIElementClicked;
}