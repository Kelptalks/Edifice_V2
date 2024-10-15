//
// Created by Spencer on 4/17/2024.
//

#ifndef BLOCKS_H
#define BLOCKS_H

#include <stdbool.h>
#include <SDL_rect.h>

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
    Rock,

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
    StoneFurnaceOn,
    StoneFurnaceOff,

    //Creature
    WormBody,
    WormEyesLevel,
    WormEyesUp,
    WormMouth,

    Scaffolding,
    Log,

    //Drone
    DroneLeftForward,
    DroneRightForward,
    DroneRightBack,
    DroneLeftBack,
    DroneDead,

    //Shaders
    GreyShader,
    RedShader,
    WhiteShader,
    GreenShader,

    //Test
    HalfBlockTest,

    //Masking blocks
    MaskingBlock,
    ShadowMaskingBlock,

};

int getTotalBlockCount();

SDL_Rect getBlockSpriteSheetSrcRect(enum Block block);

bool isTransparent(enum Block);

bool isTranslucent(enum Block block);

bool isPlantable(enum Block block);

char* getBlockName(enum Block block);

void getBlockSpriteSheetCords(enum Block block, int* x, int* y);

int getBlockPlaceSound(enum Block block);

int getBlockRemoveSound(enum Block block);

#endif
