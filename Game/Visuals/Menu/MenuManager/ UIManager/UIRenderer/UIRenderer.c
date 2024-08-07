//
// Created by Spencer on 8/7/2024.
//

#include "../../../../../GameData.h"
#include "../../../../Camera/Rendering/TextureManager/IsoTextureManager.h"

//Basic Boxes
void renderXBox(struct GameData* gameData, int xCor, int yCor, int xScale, int yScale){
    //Get X sprite from sprite sheet
    SDL_Rect srcRect = {1168, 192, 16 ,16};
    //Get location and scale to draw
    SDL_Rect destRect = {xCor, yCor, xScale ,yScale};
    //Render the sprite
    SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet, &srcRect, &destRect);
}

void renderCheckBox(struct GameData* gameData, int xCor, int yCor, int xScale, int yScale){
    //Get X sprite from sprite sheet
    SDL_Rect srcRect = {1200, 192, 16 ,16};
    //Get location and scale to draw
    SDL_Rect destRect = {xCor, yCor, xScale ,yScale};
    //Render the sprite
    SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet, &srcRect, &destRect);
}

void renderForwardBox(struct GameData* gameData, int xCor, int yCor, int xScale, int yScale){
    //Get X sprite from sprite sheet
    SDL_Rect srcRect = {1232, 192, 16 ,16};
    //Get location and scale to draw
    SDL_Rect destRect = {xCor, yCor, xScale ,yScale};
    //Render the sprite
    SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet, &srcRect, &destRect);
}

void renderBackBox(struct GameData* gameData, int xCor, int yCor, int xScale, int yScale){
    //Get X sprite from sprite sheet
    SDL_Rect srcRect = {1264, 192, 16 ,16};
    //Get location and scale to draw
    SDL_Rect destRect = {xCor, yCor, xScale ,yScale};
    //Render the sprite
    SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet, &srcRect, &destRect);
}

void renderScrollBar(struct GameData* gameData, int xCor, int yCor, int xScale, int yScale){
    //Get X sprite from sprite sheet
    SDL_Rect srcRect = {960, 192, 128 ,16};
    //Get location and scale to draw
    SDL_Rect destRect = {xCor, yCor, xScale ,yScale};
    //Render the sprite
    SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet, &srcRect, &destRect);
}

void renderScrollPointer(struct GameData* gameData, int xCor, int yCor, int xScale, int yScale){
    //Get X sprite from sprite sheet
    SDL_Rect srcRect = {1088, 192, 16 ,32};
    //Get location and scale to draw
    SDL_Rect destRect = {xCor, yCor, xScale ,yScale};
    //Render the sprite
    SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet, &srcRect, &destRect);
}