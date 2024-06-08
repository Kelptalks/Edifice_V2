//
// Created by Spencer on 3/27/2024.
//

#ifndef KEYMOD_H
#define KEYMOD_H
#define MASK 7;

//add a bit to axis
unsigned long addBitToAxis(unsigned long key, int axis, int depth);

//Subtract bit from axis
unsigned long subBitFromAxis(unsigned long key, int axis, int depth);

//Add/Subtract bits from a specific axis
unsigned long modAxis(unsigned long key, int value, int axis, int depth);

int getAxis(unsigned long key, int axis, int depth);

//Add/Subtract bits from all axis
unsigned long modKey(unsigned long key, int xMod, int yMod, int zMod, int depth);

void printKeyAxis(unsigned long key, int depth);

void printKeyIndex(unsigned long key, int depth);

#endif
