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

char* getName(enum Block block){
    if (block == Grass){
        return "grass";
    }
    return "unNamed";
}
