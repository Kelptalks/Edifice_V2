//
// Created by Spencer on 4/28/2024.
//

#ifndef ENGINE_TERRAINGEN_H
#define ENGINE_TERRAINGEN_H
#include "../World.h"
#include "LairManager/LairManager.h"


enum Feature{
    Hills,
    Trees,
};

struct TerrainGenRules{
    struct ArrayList* lairRules;
    struct ArrayList* shiftRules;
    struct HeightMapPool* heightMapPool;
};

void createTerrainGenRules(struct World* world);

void genArea(struct World* world, int xStart, int yStart, int xEnd, int yEnd, int roughNess);

void genTree(struct World* world);

void genHill();

void buildGround();


#endif //ENGINE_TERRAINGEN_H
