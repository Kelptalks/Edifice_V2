//
// Created by Spencer on 3/27/2024.
//

#include <stdio.h>
#include "KeyMod.h"
#include "../../../Debuging/Test_Main.h"

// Add a bit to axis
unsigned long addBitToAxis(unsigned long key, int axis, int depth) {
    // Create mask for targeted bit
    int mask = 1 << (depth * 3 + axis);
    unsigned long newKey;

    // Check if bit has value
    if ((key & mask) != 0) {
        // Clear bit to 0 and call recursively to update bits on axes of higher depths
        newKey = addBitToAxis((key & ~mask), axis, depth + 1);
    } else {
        // Change bit to 1
        newKey = key | mask;
    }
    return newKey;
}

// Subtract bit from axis
unsigned long subBitFromAxis(unsigned long key, int axis, int depth) {
    // Create mask for targeted bit
    int mask = 1 << (depth * 3 + axis);
    unsigned long newKey;

    // Check if bit has value
    if ((key & mask) != 0) {
        // Change bit to 0
        newKey = key & ~mask;
    } else {
        // Set bit to 1 and call recursively to borrow bits from axes of higher depths
        newKey = subBitFromAxis(key | mask, axis, depth + 1);
    }

    return newKey;
}

unsigned long modAxis(unsigned long key, int value, int axis, int depth){
    unsigned long newKey = key;
    //If adding
    if (value > 0){
        while (value > 0){
            value--;
            newKey = addBitToAxis(newKey, axis, depth);
        }
    }

    //If subtracting
    if (value < 0){
        while (value < 0){
            value++;
            newKey = subBitFromAxis(newKey, axis, depth);
        }
    }

    return newKey;
}

unsigned long modKey(unsigned long key, int xMod, int yMod, int zMod, int depth){
    unsigned long newKey = key;
    newKey = modAxis(newKey, xMod, 0, depth);
    newKey = modAxis(newKey, yMod, 1, depth);
    newKey = modAxis(newKey, zMod, 2, depth);
    return newKey;
}

int getAxis(unsigned long key, int axis, int depth){
    int axisCor = 0;
    for (int x = 0; x < depth; x++){
        int mask = 1 << ((x * 3) + axis);
        axisCor = ((key & mask) >> (3 * x + axis) << x) | axisCor;
    }
    return axisCor;
}

void getCords(unsigned long key, int depth, int* x, int* y, int* z){
    for (int currentDepth = 0; depth > currentDepth; currentDepth++){
        int mask = (7 << 3 * currentDepth);
        int maskedDepth = (key & mask) >> (3 * currentDepth);
        //x
        if ((1 & maskedDepth) > 0){
            *x += (1 << currentDepth);
        }
        //y
        if ((2 & maskedDepth) > 0){
            *y += (1 << (currentDepth));
        }
        //z
        if ((4 & maskedDepth) > 0){
            *z += (1 << (currentDepth));
        }

    }
}

void printKeyAxis(unsigned long key, int depth){
    FILE * debug;
    debug = fopen("debug", "a");
    fprintf(debug, "%i, %i, %i \n", getAxis(key, 0, depth), getAxis(key, 1, depth), getAxis(key, 2, depth));
    fclose(debug);
}

void printKeyIndex(unsigned long key, int depth){
    //Open debug file to write too
    FILE * debug;
    debug = fopen("debug", "a");
    fprintf(debug, "Index : ");
    for (int d = 0; d < depth; d++){
        int mask = (7 << (3 * d));
        int index = (key & mask) >> (3 * d);
        fprintf(debug, "%i, ", index);
    }
    fprintf(debug, "\n");
    fclose(debug);
}