//
// Created by Spencer on 4/17/2024.
//

#include <stdio.h>
#include "IsoTextureManager.h"
#include "malloc.h"
#include "SDL.h"
#include "../../../../../Assets/AssetManager.h"
#include "../../../../Blocks/Blocks.h"
#include <windows.h>
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Basic
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *
 *
 */


//crop a 64 by 64 block from the sprite sheet
SDL_Surface* cropBlockFromSpriteSheet(SDL_Surface* spriteSheet, enum Block block){
    SDL_Rect srcRect = {getSpriteSheetXCor(block), getSpriteSheetYCor(block), 64, 64};
    SDL_Surface* croppedSurface = SDL_CreateRGBSurfaceWithFormat(0, 64, 64, 32, SDL_PIXELFORMAT_RGBA32);
    if (croppedSurface == NULL){
        printf("TextureManager | failed to create cropped surface");
        return NULL;
    }
    SDL_BlitSurface(spriteSheet, &srcRect, croppedSurface, NULL);
    return croppedSurface;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Texture Splicing
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *
 *
 */

//Splice a block from the sprite sheet into the 6 needed triangles
struct SplicedBlockSurfaces* spliceBlockSurfaces(SDL_Surface* spriteSheet, enum Block block){
    //The sprite sheet to crop from
    SDL_Surface* blockSurface = cropBlockFromSpriteSheet(spriteSheet, block);
    uint32_t *blockPixels = blockSurface->pixels;

    //get maskSprite
    SDL_Surface* mask = cropBlockFromSpriteSheet(spriteSheet, MaskingBlock);
    uint32_t *maskPixels = mask->pixels;

    //create surface for each splice
    struct SplicedBlockSurfaces* splicedBlock = malloc(sizeof(struct SplicedBlockSurfaces));
    if (splicedBlock->surfaces == NULL){
        printf("IsoTextureManger | failed to allocate for spliced texture array");
        return NULL;
    }

    //Create a surface array of 64 by 64
    for (int s = 0 ; s < 6; s++){
        splicedBlock->surfaces[s] = SDL_CreateRGBSurfaceWithFormat(0, 64, 64, 32, SDL_PIXELFORMAT_RGBA32);
    }

    //splice the textures using the color mask
    for (int x = 0; x < 64; x++){
        for (int y = 0; y < 64; y++){
            int index = x + (y * 64);

            //Left Top
            if (maskPixels[index + (64 * 16)] == -16776961 ){
                uint32_t *pixels = splicedBlock->surfaces[LeftTopFace]->pixels;
                pixels[index] = blockPixels[index + (64 * 16)];
            }
            //left bot C
            if (maskPixels[index  + (64 * 32)] == -1572611 ){
                uint32_t *pixels = splicedBlock->surfaces[LeftBotFace]->pixels;
                pixels[index] = blockPixels[index + (64 * 32)];
            }
            //top left C
            if (maskPixels[index] == -16711693){
                uint32_t *pixels = splicedBlock->surfaces[TopLeftFace]->pixels;
                pixels[index] = blockPixels[index];
            }

            //Right Bot C
            if (maskPixels[index + 32 + (64 * 32)] == -65426 ){
                uint32_t *pixels = splicedBlock->surfaces[RightBotFace]->pixels;
                pixels[index] = blockPixels[index + 32 + (64 * 32)];
            }
            //Top Right
            if (maskPixels[index + 32] == -16711929 ){
                uint32_t *pixels = splicedBlock->surfaces[TopRightFace]->pixels;
                pixels[index] = blockPixels[index + 32];
            }
            //Right Top C
            if (maskPixels[index + 32 + (64 * 16)] == -16128 ){
                uint32_t *pixels = splicedBlock->surfaces[RightTopFace]->pixels;
                pixels[index] = blockPixels[index + 32 + (64 * 16)];
            }
        }
    }
    return splicedBlock;
}

struct BlockShaders* createShaders(SDL_Renderer* renderer, SDL_Surface* spriteSheet){

    SDL_Surface* shader = cropBlockFromSpriteSheet(spriteSheet, GreyShader);
    uint32_t *shaderPixels = shader->pixels;

    //get maskSprite1
    SDL_Surface* aMask = cropBlockFromSpriteSheet(spriteSheet, MaskingBlock);
    uint32_t *aMaskPixels = aMask->pixels;

    //get maskSprite2
    SDL_Surface* bMask = cropBlockFromSpriteSheet(spriteSheet, ShadowMaskingBlock);
    uint32_t *bMaskPixels = bMask->pixels;

    //create surface for each splice
    SDL_Surface surfaces[14];
    for (int s = 0 ; s < 14; s++){
        surfaces[s] = *SDL_CreateRGBSurfaceWithFormat(0, 64, 64, 32, SDL_PIXELFORMAT_RGBA32);
    }

    //splice the textures using the color mask
    for (int x = 0; x < 64; x++){
        for (int y = 0; y < 64; y++){
            int index = x + (y * 64);

            //Left Top
            if (aMaskPixels[index + (64 * 16)] == -16776961 ){
                uint32_t *pixels = surfaces[LeftTopFace].pixels;
                pixels[index] = shaderPixels[index + (64 * 16)];
            }
            //left bot C
            if (aMaskPixels[index  + (64 * 32)] == -1572611 ){
                uint32_t *pixels = surfaces[LeftBotFace].pixels;
                pixels[index] = shaderPixels[index + (64 * 32)];
            }
            //top left C
            if (aMaskPixels[index] == -16711693){
                uint32_t *pixels = surfaces[TopLeftFace].pixels;
                pixels[index] = shaderPixels[index];
            }

            //Right Bot C
            if (aMaskPixels[index + 32 + (64 * 32)] == -65426 ){
                uint32_t *pixels = surfaces[RightBotFace].pixels;
                pixels[index] = shaderPixels[index + 32 + (64 * 32)];
            }
            //Top Right
            if (aMaskPixels[index + 32] == -16711929 ){
                uint32_t *pixels = surfaces[TopRightFace].pixels;
                pixels[index] = shaderPixels[index + 32];
            }
            //Right Top C
            if (aMaskPixels[index + 32 + (64 * 16)] == -16128 ){
                uint32_t *pixels = surfaces[RightTopFace].pixels;
                pixels[index] = shaderPixels[index + 32 + (64 * 16)];
            }

            if (bMaskPixels[index] == -16776961){
                uint32_t *pixels = surfaces[TopTopLeft].pixels;
                pixels[index] = shaderPixels[index];
            }

            if (bMaskPixels[index] == -16711739){
                uint32_t *pixels = surfaces[TopBotLeft].pixels;
                pixels[index] = shaderPixels[index];
            }

            if (bMaskPixels[index + 32] == -12452096){
                uint32_t *pixels = surfaces[TopBotRight].pixels;
                pixels[index] = shaderPixels[index + 32];
            }

            if (bMaskPixels[index + 32] == -31280){
                uint32_t *pixels = surfaces[TopTopRight].pixels;
                pixels[index] = shaderPixels[index + 32];
            }

            if (bMaskPixels[index + (64 * 16)] == -16711929 ){
                uint32_t *pixels = surfaces[LeftWest].pixels;
                pixels[index] = shaderPixels[index + (64 * 16)];
            }

            if (bMaskPixels[index + (64 * 32)] == -16128 ){
                uint32_t *pixels = surfaces[LeftSouth].pixels;
                pixels[index] = shaderPixels[index + (64 * 16)];
            }

            if (bMaskPixels[index + (64 * 16)] == -65406 ){
                uint32_t *pixels = surfaces[LeftNorth].pixels;
                pixels[index] = shaderPixels[index + (64 * 16)];
            }

            if (bMaskPixels[index + (64 * 32)] == -1572611){
                uint32_t *pixels = surfaces[LeftEast].pixels;
                pixels[index] = shaderPixels[index + (64 * 16)];
            }

        }
    }


    struct BlockShaders* blockShaders = malloc(sizeof(struct BlockShaders));
    if (blockShaders == NULL){
        FILE * debug;
        debug = fopen("debug", "a");
        fprintf(debug, "IsoTextureManager | failed to create blockShaders struct \n");
        fclose(debug);
        return NULL;
    }

    for (int x = 0; x < 14; x++){
        blockShaders->textures[x] = SDL_CreateTextureFromSurface(renderer, &surfaces[x]);
    }

    return blockShaders;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Creation
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

//Creates all the textures needed for the game and orginizes them
struct Textures* createTextures(SDL_Renderer* renderer, int blockCount){
    //load spriteSheet
    SDL_Surface* spriteSheet = loadSpriteSheet();


    //setup texture struct
    struct Textures* textures = malloc(sizeof(struct Textures));
    textures->blockCount = blockCount;

    // Allocate memory for the BlockTextures array
    textures->BlockTextures = malloc(sizeof(struct BlockTextures) * textures->blockCount);

    //Loop through array and create textures
    for (int b = 0; b < blockCount; b++){
        //Create spliced surfaces
        struct SplicedBlockSurfaces* splicedBlockSurfaces = spliceBlockSurfaces(spriteSheet, b);
        //turn those surfaces into textures

        if (splicedBlockSurfaces->surfaces == NULL){
            FILE * debug;
            debug = fopen("debug", "a");
            fprintf(debug, "Aids... \n");
            fclose(debug);
            return NULL;
        }

        for (int s = 0; s < 6; s++){
            textures->BlockTextures[b].textures[s] = SDL_CreateTextureFromSurface(renderer, splicedBlockSurfaces->surfaces[s]);
            SDL_FreeSurface(splicedBlockSurfaces->surfaces[s]); // Free the surface after creating the texture
        }
        free(splicedBlockSurfaces);

    }
    textures->shaderCount = 1;
    textures->blockShaders = malloc(sizeof(struct BlockTextures) * textures->shaderCount);
    textures->blockShaders = createShaders(renderer, spriteSheet);
    textures->spriteSheet = SDL_CreateTextureFromSurface(renderer, spriteSheet);
    SDL_FreeSurface(spriteSheet);

    return textures;
}