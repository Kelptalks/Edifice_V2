//
// Created by Spencer on 4/17/2024.
//

#include <malloc.h>
#include "IsoCordManager.h";
#include "stdio.h";


int* isoToScreen(float scale, int x, int y){
    int* cordArray = malloc(sizeof(int) * 2);

    if (cordArray == NULL){
        printf("IsoCordManager | Failed to initialize cord array");
        return NULL;
    }

    scale = scale/2;

    cordArray[0] = (x - y) * scale;
    cordArray[1] = (x + y) * (scale/2);

    return cordArray;
}

float* accurateIsoToScreen(float scale, float x, float y){
    float* cordArray = malloc(sizeof(int) * 2);

    if (cordArray == NULL){
        printf("IsoCordManager | Failed to initialize cord array");
        return NULL;
    }

    scale = scale/2;

    cordArray[0] = (x - y) * scale;
    cordArray[1] = (x + y) * (scale/2);

    return cordArray;
}


int* screenToIso(float scale, int x, int y){
    int* cordArray = malloc(sizeof(int) * 2);
    if (cordArray == NULL){
        printf("IsoCordManager | Failed to initialize cord array");
        return NULL;
    }

    float isoX = (float) (x + 2 * y) / (2 * scale);
    float isoY = (float) (2 * y - x) / (2 * scale);

    if (isoY < 0){
        isoY++;
    }

    cordArray[0] = isoX;
    cordArray[1] = isoY;

    return cordArray;
}