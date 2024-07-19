//
// Created by Spencer on 4/17/2024.
//

#ifndef BLOCKS_H
#define BLOCKS_H

#include <stdbool.h>

#define numOfBlocks = 18;

enum Block {
    Air,

    //Blocks
    Dirt,
    Stone,
    Wood,
    Leave,
    Dandi,
    DandiStem,
    Hive,
    Cobble,
    Grass,
    MushroomStem,
    BlueMushroomBlock,
    Magma,
    Core,
    LBM,
    Metal,
    Granite,
    Sand,
    Debug,
    Iron,
    Fungi,
    BlueGrass,
    Cloud,
    CrackedEarth,
    MudBrick,
    StoneBrick,

    //Transparent Blocks
    Water1,
    Water2,
    YellowFlowers,
    WhiteFlowers,
    Mushroom,
    Flour,
    Glass,

    //Shaders
    GreyShader,
    RedShader,
    WhiteShader,
    GreenShader,

    //Masking blocks
    MaskingBlock,
    ShadowMaskingBlock
};

bool isTransparent(enum Block);

bool isTranslucent(enum Block block);

bool isPlantable(enum Block block);

char* getBlockName(enum Block block);

void getBlockSpriteSheetCords(enum Block block, int* x, int* y);

#endif
