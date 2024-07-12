//
// Created by Spencer on 4/17/2024.
//

#ifndef BLOCKS_H
#define BLOCKS_H

#include <stdbool.h>

#define numOfBlocks = 18;

enum Block {
    Air,
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
    Water1,
    Water2,
    YellowFlowers,
    WhiteFlowers,
    Mushroom,
    Flour,
    CrackedEarth,
    GreyShader,
    RedShader,
    WhiteShader,
    GreenShader,
    MaskingBlock,
    ShadowMaskingBlock,
};

bool isTransparent(enum Block);

bool isTranslucent(enum Block block);

bool isPlantable(enum Block block);

char* getBlockName(enum Block block);

int getSpriteSheetYCor(enum Block block);
int getSpriteSheetXCor(enum Block block);

#endif
