//
// Created by Spencer on 4/17/2024.
//

#include <malloc.h>
#include "IsoCordManager.h";
#include "stdio.h";


void isoToScreen(float scale, int x, int y, int* isoX, int* isoY){
    scale = scale/2;
    *isoX = (int) ((x - y) * scale);
    *isoY = (int) ((x + y) * (scale / 2));
}

void screenToIso(float scale, int x, int y, int* isoX, int* isoY){
    float tempIsoX = (float) (x + 2 * y) / (2 * scale);
    float tempIsoY = (float) (2 * y - x) / (2 * scale);

    //Cord correction due to 0
    if (tempIsoX < 0){
        tempIsoX--;
    }
    if (tempIsoY < 0){
        tempIsoY--;
    }

    *isoX = tempIsoX;
    *isoY = tempIsoY;

}