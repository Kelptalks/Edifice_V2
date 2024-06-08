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
    Shadow,
    Battery,
    Battery1,
    Battery2,
    Battery3,
    Factory,
    Factory1,
    Factory2,
    BlueGrass,
    Cloud,
    Water1,
    Water2,
    YellowFlowers,
    WhiteFlowers,
    Mushroom,
    Flour,
};

bool isTransparent(enum Block);

bool isTranslucent(enum Block block);

bool isPlantable(enum Block block);

char* getName(enum Block block);

#endif
