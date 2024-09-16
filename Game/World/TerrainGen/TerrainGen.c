//
// Created by Spencer on 4/28/2024.
//

#include <malloc.h>
#include "TerrainGen.h"
#include "Perlin Noise/PerlinNoise.h"
#include "../Octree/Tools/KeyMod.h"
#include "../Octree/OctreeNode.h"
#include "../Octree/Octree.h"
#include "LairManager/LairManager.h"
#include "PlantManager/PlantManger.h"
#include "../../../ArrayList/ArrayList.h"
#include "WaterGen/WaterGen.h"
#include "HillManager/HillManager.h"

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
    addLairRule(terrainGenRules->lairRules, 21, 21, GreenGrass);


    terrainGenRules->heightMapPool = createHeightMapPool();

    world->terrainGenRules = terrainGenRules;


    //Create testing hill

}

void genArea(struct World* world, unsigned long key, int xArea, int yArea, int zArea){
    int xStart = -150;
    int yStart = -150;
    int zStart = -30;

    int xEnd = xStart + xArea;
    int yEnd = yStart + yArea;
    int zEnd = zStart + zArea;


    //Get an array of only rules applicable to area
    struct ArrayList* lairRulesInArea = getLairRulesInArea(world->terrainGenRules->lairRules, zStart, zEnd);
    struct ArrayList* shiftRulesInArea = getShiftRulesInArea(world->terrainGenRules->shiftRules, xStart, xEnd, yStart, yEnd);

    //Perlin terrain gen
    struct HeightMapPool* heightMapPool = world->terrainGenRules->heightMapPool;
    int chunkSizeCenterOffSet = (heightMapPool->chunkScale - heightMapPool->chunkScale) / 2;

    //Loop through keys in the area
    for (int x = xStart; x < xArea; x++){
        for (int y = yStart; y < yArea; y++){
            for (int z = zStart; z < zArea; z++) {
                //Set Lair Shifting rule
                int lairShift = 0;
                for (int rule = 0; rule < shiftRulesInArea->length; rule++) {
                    struct ShiftRule *shiftRule = indexList(shiftRulesInArea, rule);
                    if (inShiftRuleBounds(shiftRule, xStart + x, yStart + y)) {
                        lairShift += shiftRule->scale;
                    }
                }


                int chunkX = x / heightMapPool->chunkScale;
                int chunkY = y / heightMapPool->chunkScale;
                int xCor =  x % heightMapPool->chunkScale;
                int yCor = y % heightMapPool->chunkScale;

                if (chunkX > 0 && chunkX < heightMapPool->scale && chunkY > 0 && chunkY < heightMapPool->scale){
                    int height = heightMapPool->heightChunkPool[chunkX][chunkY].heightMap[xCor + chunkSizeCenterOffSet + ((yCor + chunkSizeCenterOffSet) * heightMapPool->chunkScale)];
                    height = height/4;
                    lairShift += height;
                }



                //Set lair rules
                for (int rule = 0; rule < lairRulesInArea->length; rule++) {
                    //Lair building
                    struct LairRule *lairRule = (struct LairRule *) indexList(lairRulesInArea, rule);
                    if (zInRuleBounds(lairRule, zStart + z)) {
                        //Build the location


                        //Build block of the lair
                        setBlockAtWorldCor(world, x, y, z + lairShift,lairRule->blockType);


                        //Attempt to plant on that block
                        if (lairRule->blockType == GreenGrass) {
                            generatePlant(world, x, y, z + lairShift, GreenGrass);
                        }
                    }
                }
            }
        }

    }
}