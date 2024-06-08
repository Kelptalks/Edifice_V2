//
// Created by Spencer on 4/28/2024.
//

#include <malloc.h>
#include "TerrainGen.h"
#include "Perlin Noise/PerlinNoise.h"
#include "../Octree/KeyMod.h"
#include "../Octree/OctreeNode.h"
#include "../Octree/Octree.h"
#include "LairManager/LairManager.h"
#include "PlantManager/PlantManger.h"
#include "../../../ArrayList/ArrayList.h"

void createTerrainGenRules(struct World* world){
    struct TerrainGenRules* terrainGenRules = malloc(sizeof (struct TerrainGenRules));
    if (terrainGenRules == NULL){
        reportBug("Terrain Gen | failed to malloc terrainGenRules struct");
        return;
    }
    terrainGenRules->lairRules = createList();
    terrainGenRules->shiftRules = createList();

    //add all lair rules
    addLairRule(terrainGenRules->lairRules, -20, 15, Stone);
    addLairRule(terrainGenRules->lairRules, 16, 20, Dirt);
    addLairRule(terrainGenRules->lairRules, 21, 21, Grass);

    world->terrainGenRules = terrainGenRules;
}

void genArea(struct World* world, unsigned long key, int xArea, int yArea, int zArea){
    int xStart = getAxis(key, 0, 0);
    int yStart = getAxis(key, 1, 0);
    int zStart = getAxis(key, 2, 0);

    int xEnd = xStart + xArea;
    int yEnd = yStart + yArea;
    int zEnd = zStart + zArea;

    //Get an array of only rules applicable to area
    struct ArrayList* lairRulesInArea = getLairRulesInArea(world->terrainGenRules->lairRules, zStart, zEnd);
    struct ArrayList* shiftRulesInArea = getShiftRulesInArea(world->terrainGenRules->shiftRules, xStart, xEnd, yStart, yEnd);


    //test
    struct NoiseData* noiseData = createNoiseData(0, 0, 0);
    short* heights = getChunkHeightsCor(noiseData, 0, 0);

    //Loop through keys in the area
    for (int x = 0; x < xArea; x++){
        unsigned long xKeyMod = modKey(key, x, 0, 0, 0);
        for (int y = 0; y < yArea; y++){
            unsigned long yKeyMod = modKey(xKeyMod, 0, y, 0, 0);
            for (int z = 0; z < zArea; z++){
                //Set Lair Shifting rule
                int lairShift = 0;
                for (int rule = 0; rule < shiftRulesInArea->length; rule++){
                    struct ShiftRule* shiftRule = indexList(shiftRulesInArea, rule);
                    if(inShiftRuleBounds(shiftRule, xStart + x, yStart + y)){
                        lairShift += shiftRule->scale;
                    }
                }

                if (y < noiseData->chunkScale && y > 0 && x > 0 && x < noiseData->chunkScale){
                    lairShift += heights[y + (x * noiseData->chunkScale)] / 3;
                }


                //Set lair rules
                unsigned long zKeyMod = modKey(yKeyMod, 0, 0, z, 0);
                for (int rule = 0; rule < lairRulesInArea->length; rule++){


                    //Lair building
                    struct LairRule* lairRule = (struct LairRule *) indexList(lairRulesInArea, rule);
                    if (zInRuleBounds(lairRule, zStart + z)){
                        unsigned long shiftedLairKey = modKey(zKeyMod, 0, 0, lairShift, 0);
                        //Build block of the lair
                        setOctreeKeyValue(world->octree->root, shiftedLairKey, world->octree->RootDepth, lairRule->blockType);
                        //Attempt to plant on that block
                        generatePlant(world, shiftedLairKey, lairRule->blockType);
                    }
                }
            }
        }
    }
}