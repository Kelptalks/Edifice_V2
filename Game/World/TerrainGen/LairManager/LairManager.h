//
// Created by Spencer on 4/28/2024.
//

#ifndef ENGINE_LAIRMANAGER_H
#define ENGINE_LAIRMANAGER_H

#include "../../World.h"
#include "../../../Blocks/Blocks.h"

struct LairRule{
    int z1;
    int z2;
    enum Block blockType;
};

struct ShiftRule{
    int xMin;
    int xMax;
    int yMin;
    int yMax;
    int scale;
};

struct ArrayList* getShiftRulesInArea(struct ArrayList* shiftRules, int xMin, int xMax, int yMin, int yMax);

struct ArrayList* getLairRulesInArea(struct ArrayList* lairRules, int zStart, int zEnd);

void addShiftRule(struct ArrayList* arrayList, int xMin, int xMax, int yMin, int yMax, int scale);

void addLairRule(struct ArrayList* lairRules, int z1, int z2, enum Block blockType);

bool zInRuleBounds(struct LairRule* lairRule, int z);

bool inShiftRuleBounds(struct ShiftRule* shiftRule, int x, int y);

#endif //ENGINE_LAIRMANAGER_H
