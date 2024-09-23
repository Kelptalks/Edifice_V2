//
// Created by Spencer on 4/28/2024.
//
#include <malloc.h>
#include "LairManager.h"
#include "../../../../ArrayList/ArrayList.h"



bool inShiftRuleBounds(struct ShiftRule* shiftRule, int x, int y){
    if ((x >= shiftRule->xMin) && (x <= shiftRule->xMax) && (y >= shiftRule->yMin) && (y <= shiftRule->yMax)){
        return true;
    }
    return false;
}

void addLairRule(struct ArrayList* lairRules, int z1, int z2, enum Block blockType){
    struct LairRule* lairRule = malloc(sizeof (struct LairRule));

    lairRule->z1 = z1;
    lairRule->z2 = z2;
    lairRule->blockType = blockType;

    addList(lairRules, lairRule);
}

struct ArrayList* getLairRulesInArea(struct ArrayList* lairRules, int zStart, int zEnd){
    struct ArrayList* lairRulesInArea = createList();
    for (int x = 0; x < lairRules->length; x++){
        struct LairRule* lairRule = lairRules->ptrs[x];
        //If the rule is in bounds of area
        if (lairRule->z1 > zStart || lairRule->z2 < zEnd){
            addList(lairRulesInArea, lairRule);
        }
    }
    return lairRulesInArea;
}

bool zInRuleBounds(struct LairRule* lairRule, int z){
    if (z >= lairRule->z1 && z <= lairRule->z2){
        return true;
    }
    return false;
}
