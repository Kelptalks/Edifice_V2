//
// Created by Spencer on 4/18/2024.
//



#include <stdbool.h>
#include "Blocks.h"

bool isPlantable(enum Block block){
    if (block == Grass){
        return true;
    }
    if (block == BlueGrass){
        return true;
    }
    return false;
}

bool isTransparent(enum Block block){
    if (block == 0){
        return true;
    }
    else{
        return false;
    }
}

bool isTranslucent(enum Block block){
    //if (block > 29 & block < 36){
    if (block == YellowFlowers){
        return true;
    }
    if (block == WhiteFlowers){
        return true;
    }
    if (block == Flour){
        return true;
    }
    if (block == Mushroom){
        return true;
    }
    if (block == Water1){
        return true;
    }
    if (block == Water2){
        return true;
    }
    else{
        return false;
    }
}

char* getBlockName(enum Block block){
    switch (block) {
        case Dirt:
            return "Dirt";
        case Stone:
            return "Stone";
        case Wood:
            return "Wood";
        case Leave:
            return "Leave";
        case Cloud:
            return "Cloud";
        case Dandi:
            return "Dandi";
        case DandiStem:
            return "DandiStem";
        case Hive:
            return "Hive";
        case Cobble:
            return "Cobble";
        case Grass:
            return "Grass";
        case Magma:
            return "Magma";
        case Core:
            return "Core";
        case LBM:
            return "LBM";
        case Metal:
            return "Metal";
        case Granite:
            return "Granite";
        case Sand:
            return "Sand";
        case Iron:
            return "Iron";
        case Fungi:
            return "Fungi";
        case BlueGrass:
            return "BlueGrass";
        case MushroomStem:
            return "MushroomStem";
        case BlueMushroomBlock:
            return "BlueMushroomBlock";
        case Debug:
            return "Debug";
        case Water1:
            return "Water1";
        case Flour:
            return "Flour";
        case WhiteFlowers:
            return "WhiteFlowers";
        case YellowFlowers:
            return "YellowFlowers";
        case Mushroom:
            return "Mushroom";
        case CrackedEarth:
            return "CrackedEarth";
    }
    return "unNamed";
}

int getSpriteSheetYCor(enum Block block){
    switch (block) {
        case Dirt:
            return 0;
        case Stone:
            return 0;
        case Wood:
            return 0;
        case Leave:
            return 0;
        case Dandi:
            return 64;
        case DandiStem:
            return 64;
        case Hive:
            return 64;
        case Cobble:
            return 64;
        case Grass:
            return 128;
        case Magma:
            return 128;
        case Core:
            return 128;
        case LBM:
            return 128;
        case Metal:
            return 192;
        case Granite:
            return 192;
        case Sand:
            return 192;
        case Iron:
            return 192;
        case Fungi:
            return 256;
        case BlueGrass:
            return 256;
        case MushroomStem:
            return 256;
        case BlueMushroomBlock:
            return 256;
        case Debug:
            return 320;
        case Water1:
            return 320;
        case Flour:
            return 960;
        case WhiteFlowers:
            return 960;
        case YellowFlowers:
            return 960;
        case Mushroom:
            return 960;
        case CrackedEarth:
            return 320;
        case MaskingBlock :
            return 1152;
        case GreyShader:
            return 1152;
        case ShadowMaskingBlock:
            return 1216;
    }
    return 0;
}

int getSpriteSheetXCor(enum Block block){
    switch (block) {
        case Dirt:
            return 0;
        case Stone:
            return 64;
        case Wood:
            return 128;
        case Leave:
            return 192;
        case Dandi:
            return 0;
        case DandiStem:
            return 64;
        case Hive:
            return 128;
        case Cobble:
            return 192;
        case Grass:
            return 0;
        case Magma:
            return 64;
        case Core:
            return 128;
        case LBM:
            return 192;
        case Metal:
            return 0;
        case Granite:
            return 64;
        case Sand:
            return 128;
        case Iron:
            return 192;
        case Fungi:
            return 0;
        case BlueGrass:
            return 64;
        case MushroomStem:
            return 128;
        case BlueMushroomBlock:
            return 192;
        case Debug:
            return 64;
        case Water1:
            return 128;
        case Flour:
            return 256;
        case WhiteFlowers:
            return 64;
        case YellowFlowers:
            return 0;
        case Mushroom:
            return 192;
        case CrackedEarth:
            return 0;
        case MaskingBlock :
            return 1216;
        case GreyShader:
            return 0;
        case ShadowMaskingBlock:
            return 1216;

    }
    return 0;
}