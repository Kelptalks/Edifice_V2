//
// Created by Spencer on 4/17/2024.
//

#ifndef ISOCORDMANAGER_H
#define ISOCORDMANAGER_H

void isoToScreen(float scale, int x, int y, int* isoX, int* isoY);

void floatIsoToScreen(float scale, float x, float y, int* screenX, int* screenY);

void screenToIso(float scale, int x, int y, int* isoX, int* isoY);

#endif
