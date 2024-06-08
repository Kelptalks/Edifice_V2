//
// Created by Spencer on 4/17/2024.
//
#include <SDL2/SDL.h>
#include <stdio.h>
#include "stdlib.h"

#ifndef ISOTEXTUREMANAGER_H
#define ISOTEXTUREMANAGER_H

enum Texture{
    //Blocks
    TopLeftFace,
    TopRightFace,
    LeftTopFace,
    LeftBotFace,
    RightTopFace,
    RightBotFace,

    //Shading
    TopTopLeft,
    TopTopRight,
    TopBotLeft,
    TopBotRight,
    LeftNorth,
    LeftEast,
    LeftSouth,
    LeftWest,

    //Other
    Empty
};

struct SplicedBlockSurfaces{
    //Array for each block face
    SDL_Surface* surfaces[6];
};

struct BlockTextures{
    // Array of spliced textures for a block
    SDL_Texture* textures[6];
};

struct BlockShaders{
    // Array of spliced shaders for a block
    SDL_Texture* textures[14];
};

struct Textures{
    //Array for every array of block's spliced textures
    struct BlockTextures* BlockTextures;
    int blockCount;

    struct BlockShaders* blockShaders;
    int shaderCount;
};

SDL_Surface* loadSpriteSheet();

SDL_Surface* cropBlockFromSpriteSheet(SDL_Surface* spriteSheet, int xCor, int yCor);

struct SplicedBlockSurfaces* spliceBlockSurfaces(SDL_Surface* spriteSheet, int xCor, int yCor);

struct Textures* createTextures(SDL_Renderer* renderer, int blockCount);

#endif
