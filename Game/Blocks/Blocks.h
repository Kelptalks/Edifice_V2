//
// Created by Spencer on 4/17/2024.
//

#ifndef BLOCKS_H
#define BLOCKS_H

#include <stdbool.h>

#define numOfBlocks = 18;

enum Block {
    Air,

    //Basic
    Dirt,
    CrackedEarth,
    Hive,
    Cobble,
    Core,
    Sand,
    Debug,

    //Stones
    Granite,
    Stone,
    Magma,

    //Grasses
    GreenGrass,
    BlueGrass,

    //Trees
    Leave,
    PurpleWood,
    PurpleWoodPlanks,

    BrownWood,
    BrownWoodPlanks,

    //LargeDandi
    Dandi,
    DandiStem,

    //LargeMushrooms
    MushroomStem,
    BlueMushroomBlock,
    PinkMushroomBlock,

    //Large Fungi
    Fungi,

    //Transparent Plants
    Water,
    YellowFlowers,
    WhiteFlowers,
    Mushroom,
    Flour,
    Glass,
    Bulb,

    //Metals
    Iron,
    Copper,

    MudBrick,
    ClayBrick,
    Coral,
    StoneBrick,
    FloweringStoneBrick,

    //Factory
    LBM,
    Factory,
    Crate,
    Metal,

    //Transparent Factory
    ConveyorBelt,
    Furnace,

    //Shaders
    GreyShader,
    RedShader,
    WhiteShader,
    GreenShader,

    //Test
    HalfBlockTest,

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
