//
// Created by Spencer on 8/7/2024.
//

#include "../../../../../GameData.h"
#include "../../../../Camera/Rendering/TextureManager/IsoTextureManager.h"

//Basic Boxes
void renderXBox(struct GameData* gameData, bool pressed, int xCor, int yCor, int xScale, int yScale){
    //Get X sprite from sprite sheet
    SDL_Rect srcRect = {1152, 192, 16 ,16};
    if (pressed){
        srcRect.y -= 16;
    }
    //Get location and scale to draw
    SDL_Rect destRect = {xCor, yCor, xScale ,yScale};
    //Render the sprite
    SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet, &srcRect, &destRect);
}

void renderCheckBox(struct GameData* gameData, bool pressed, int xCor, int yCor, int xScale, int yScale){
    //Get X sprite from sprite sheet
    SDL_Rect srcRect = {1184, 192, 16 ,16};
    if (pressed){
        srcRect.y -= 16;
    }
    //Get location and scale to draw
    SDL_Rect destRect = {xCor, yCor, xScale ,yScale};
    //Render the sprite
    SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet, &srcRect, &destRect);
}

void renderForwardBox(struct GameData* gameData, bool pressed, int xCor, int yCor, int xScale, int yScale){
    //Get X sprite from sprite sheet
    SDL_Rect srcRect = {1168, 192, 16 ,16};
    if (pressed){
        srcRect.y -= 16;
    }
    //Get location and scale to draw
    SDL_Rect destRect = {xCor, yCor, xScale ,yScale};
    //Render the sprite
    SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet, &srcRect, &destRect);
}

void renderBackBox(struct GameData* gameData, bool pressed, int xCor, int yCor, int xScale, int yScale){
    //Get X sprite from sprite sheet
    SDL_Rect srcRect = {1136, 192, 16 ,16};
    if (pressed){
        srcRect.y -= 16;
    }
    //Get location and scale to draw
    SDL_Rect destRect = {xCor, yCor, xScale ,yScale};
    //Render the sprite
    SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet, &srcRect, &destRect);
}

void renderScrollBar(struct GameData* gameData, int xCor, int yCor, int xScale, int yScale){
    //Get X sprite from sprite sheet
    SDL_Rect srcRect = {1137, 208, 128 ,16};

    //Get location and scale to draw
    SDL_Rect destRect = {xCor, yCor, xScale ,yScale};
    //Render the sprite
    SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet, &srcRect, &destRect);
}

void renderScrollPointer(struct GameData* gameData, bool pressed, int xCor, int yCor, int xScale, int yScale){
    //Get X sprite from sprite sheet
    SDL_Rect srcRect = {1200, 192, 16 ,16};
    if (pressed){
        srcRect.y -= 16;
    }
    //Get location and scale to draw
    SDL_Rect destRect = {xCor, yCor, xScale ,yScale};
    //Render the sprite
    SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet, &srcRect, &destRect);
}