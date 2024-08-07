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
    if (block == Water){
        return true;
    }
    if (block == Glass){
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
        case Water:
            return "Water";
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
        case GreyShader:
            return "GreyShader";
        case GreenShader:
            return "GreenShader";
        case RedShader :
            return "redShader";
        case WhiteShader :
            return "WhiteShader";
    }
    return "unNamed";
}

void getBlockSpriteSheetCords(enum Block block, int* x, int* y) {
    switch (block) {
        case Dirt:
            *x = 0;
            *y = 0;
            break;
        case Stone:
            *x = 64;
            *y = 0;
            break;
        case Wood:
            *x = 128;
            *y = 0;
            break;
        case Leave:
            *x = 192;
            *y = 0;
            break;
        case Dandi:
            *x = 0;
            *y = 64;
            break;
        case DandiStem:
            *x = 64;
            *y = 64;
            break;
        case Hive:
            *x = 128;
            *y = 64;
            break;
        case Cobble:
            *x = 192;
            *y = 64;
            break;
        case Grass:
            *x = 0;
            *y = 128;
            break;
        case Magma:
            *x = 64;
            *y = 128;
            break;
        case Core:
            *x = 128;
            *y = 128;
            break;
        case LBM:
            *x = 192;
            *y = 128;
            break;
        case Metal:
            *x = 0;
            *y = 192;
            break;
        case Granite:
            *x = 64;
            *y = 192;
            break;
        case Sand:
            *x = 128;
            *y = 192;
            break;
        case Iron:
            *x = 192;
            *y = 192;
            break;
        case Fungi:
            *x = 0;
            *y = 256;
            break;
        case BlueGrass:
            *x = 64;
            *y = 256;
            break;
        case MushroomStem:
            *x = 128;
            *y = 256;
            break;
        case BlueMushroomBlock:
            *x = 192;
            *y = 256;
            break;
        case Debug:
            *x = 1216;
            *y = 1088;
            break;
        case Water:
            *x = 128;
            *y = 320;
            break;
        case Flour:
            *x = 192;
            *y = 960;
            break;
        case WhiteFlowers:
            *x = 64;
            *y = 960;
            break;
        case YellowFlowers:
            *x = 0;
            *y = 960;
            break;
        case Mushroom:
            *x = 128;
            *y = 960;
            break;
        case CrackedEarth:
            *x = 0;
            *y = 320;
            break;
        case MaskingBlock:
            *x = 1216;
            *y = 1152;
            break;
        case GreyShader:
            *x = 0;
            *y = 1152;
            break;
        case WhiteShader:
            *x = 64;
            *y = 1152;
            break;
        case GreenShader:
            *x = 128;
            *y = 1152;
            break;
        case RedShader:
            *x = 192;
            *y = 1152;
            break;
        case ShadowMaskingBlock:
            *x = 1216;
            *y = 1216;
            break;
        case Glass :
            *x = 192;
            *y = 320;
            break;
        case MudBrick :
            *x = 0;
            *y = 384;
            break;
        case Coral:
            *x = 64;
            *y = 384;
            break;
        case StoneBrick:
            *x = 128;
            *y = 384;
            break;
        case FloweringStoneBrick:
            *x = 192;
            *y = 384;
            break;
        default:
            *x = 64;
            *y = 320;
            break;
    }
}
