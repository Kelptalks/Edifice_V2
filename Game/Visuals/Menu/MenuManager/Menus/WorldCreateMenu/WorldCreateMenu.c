//
// Created by Spencer on 9/30/2024.
//

#include "WorldCreateMenu.h"
#include "../../../../../World/World.h"
#include "../../../../../Visuals/Camera/CameraData.h"

struct WorldCreateMenu* createWorldCreateMenu(){
    struct WorldCreateMenu* worldCreateMenu = malloc(sizeof (struct WorldCreateMenu));
    worldCreateMenu->roughness = 5;
    worldCreateMenu->increaseRoughnessScale = createButton(ForwardButton, 0, 0, 0, 0);
    worldCreateMenu->decreaseRoughnessScale = createButton(BackButton, 0, 0, 0, 0);

    worldCreateMenu->worldScale = 200;
    worldCreateMenu->increaseWorldScale = createButton(ForwardButton, 0, 0, 0, 0);
    worldCreateMenu->decreaseWorldScale = createButton(BackButton, 0, 0, 0, 0);


    worldCreateMenu->createWorld = createButton(MainButton, 0, 0, 0, 0);

    worldCreateMenu->backToMenuButton = createButton(ExitButton, 0, 0, 0, 0);
    return worldCreateMenu;
}

void updateButtonCords(struct GameData* gameData){
    struct WorldCreateMenu* worldCreateMenu = gameData->menuManger->worldCreateMenu;

    int xButtonScale = gameData->screen->xRez/32;
    int yButtonScale = gameData->screen->xRez/32;
    int buttonSpacing = (yButtonScale/2) + yButtonScale;
    int buttonXGap = xButtonScale * 6;
    struct Button* button;

    button = worldCreateMenu->decreaseWorldScale;
    button->xScale = xButtonScale;
    button->yScale = yButtonScale;
    button->xCor = buttonSpacing;
    button->yCor = buttonSpacing;

    button = worldCreateMenu->increaseWorldScale;
    button->xScale = xButtonScale;
    button->yScale = yButtonScale;
    button->xCor = buttonSpacing + buttonXGap;
    button->yCor = buttonSpacing;


    button = worldCreateMenu->decreaseRoughnessScale;
    button->xScale = xButtonScale;
    button->yScale = yButtonScale;
    button->xCor = buttonSpacing;
    button->yCor = buttonSpacing * 3;

    button = worldCreateMenu->increaseRoughnessScale;
    button->xScale = xButtonScale;
    button->yScale = yButtonScale;
    button->xCor = buttonSpacing + buttonXGap;
    button->yCor = buttonSpacing * 3;

    button = worldCreateMenu->createWorld;
    button->xScale = xButtonScale * 8;
    button->yScale = yButtonScale;
    button->xCor = buttonSpacing;
    button->yCor = gameData->screen->yRez - (yButtonScale + buttonSpacing);

}

void renderWorldCreateMenu(struct GameData* gameData){
    //Render background
    SDL_Rect srcRect = {656, 0, 240, 128};
    SDL_Rect desRect = {0, 0, gameData->screen->xRez, gameData->screen->yRez};
    SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet, &srcRect, &desRect);
    updateButtonCords(gameData);

    struct WorldCreateMenu* worldCreateMenu = gameData->menuManger->worldCreateMenu;

    struct Button* button;

    button = worldCreateMenu->decreaseWorldScale;
    renderUIButton(button, gameData);

    char worldScale[20] = {0};
    sprintf(worldScale, "%i", worldCreateMenu->worldScale);
    renderStringCentered(gameData, worldScale, button->xCor + (button->xScale * 3.5), button->yCor + (button->yScale/4), button->xScale/2);
    renderStringCentered(gameData, "worldScale", button->xCor + (button->xScale * 3.5), button->yCor - button->xScale/2, button->xScale/2);


    button = worldCreateMenu->increaseWorldScale;
    renderUIButton(button, gameData);
    if (worldCreateMenu->worldScale >= 400 && worldCreateMenu->worldScale < 1000){
        renderString(gameData, "WARNING : Large worlds take a long time to Generate",
                             button->xCor + (button->xScale * 1.5),
                             button->yCor + (button->yScale/4),
                             button->xScale/3);
    }
    if (worldCreateMenu->worldScale >= 1000){
        renderString(gameData, "!DANGER! : Extreme world size could blue screen your computer!",
                     button->xCor + (button->xScale * 1.5),
                     button->yCor + (button->yScale/4),
                     button->xScale/3);
    }


    button = worldCreateMenu->decreaseRoughnessScale;
    renderUIButton(button, gameData);

    char roughness[20] = {0};
    sprintf(roughness, "%i", worldCreateMenu->roughness);
    renderStringCentered(gameData, roughness, button->xCor + (button->xScale * 3.5), button->yCor + (button->yScale/4), button->xScale/2);
    renderStringCentered(gameData, "roughness", button->xCor + (button->xScale * 3.5), button->yCor - button->xScale/2, button->xScale/2);

    button = worldCreateMenu->increaseRoughnessScale;
    renderUIButton(button, gameData);
    if (worldCreateMenu->roughness > 10){
        renderString(gameData, "WARNING : Very rough world",
                     button->xCor + (button->xScale * 1.5),
                     button->yCor + (button->yScale/4),
                     button->xScale/3);
    }

    button = worldCreateMenu->createWorld;
    renderUIButton(button, gameData);
    renderStringCentered(gameData, "Create World",
            button->xCor + (button->xScale/2),
            button->yCor + (button->yScale/3),
            button->yScale/3);
}

void handleWorldCreateMenuInputs(struct GameData* gameData, SDL_Event event){

    struct WorldCreateMenu* worldCreateMenu = gameData->menuManger->worldCreateMenu;
    struct Button* button;

    button = worldCreateMenu->decreaseWorldScale;
    handleButtonInputs(button, gameData, event);
    if (button->pressed){
        button->pressed = false;
        worldCreateMenu->worldScale -= 10;
        playSound(gameData->soundManager, SoundMenuButtonClick);
    }

    button = worldCreateMenu->increaseWorldScale;
    handleButtonInputs(button, gameData, event);
    if (button->pressed){
        button->pressed = false;
        worldCreateMenu->worldScale += 10;
        playSound(gameData->soundManager, SoundMenuButtonClick);
    }

    button = worldCreateMenu->decreaseRoughnessScale;
    handleButtonInputs(button, gameData, event);
    if (button->pressed){
        button->pressed = false;
        worldCreateMenu->roughness -= 1;
        playSound(gameData->soundManager, SoundMenuButtonClick);
    }

    button = worldCreateMenu->increaseRoughnessScale;
    handleButtonInputs(button, gameData, event);
    if (button->pressed){
        button->pressed = false;
        worldCreateMenu->roughness += 1;
        playSound(gameData->soundManager, SoundMenuButtonClick);
    }

    button = worldCreateMenu->createWorld;
    handleButtonInputs(button, gameData, event);
    if (button->pressed){
        playSound(gameData->soundManager, SoundMenuButtonClick);
        button->pressed = false;

        //Loading screen
        SDL_Rect srcRect = {896, 64, 64, 64};
        SDL_Rect desRect = {0, 0, gameData->screen->xRez, gameData->screen->yRez};
        SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet, &srcRect, &desRect);
        renderStringCentered(gameData, "Generating World...", gameData->screen->xRez/2, gameData->screen->yRez/2, gameData->screen->xRez/32);
        updateScreen(gameData->screen);


        generateWorldTerrain(gameData->world, worldCreateMenu->worldScale, worldCreateMenu->worldScale, worldCreateMenu->roughness);
        gameData->cameraData->world = gameData->world;
        gameData->menuManger->currentMenuType = CameraMenu;
    }
}

#include "WorldCreateMenu.h"
