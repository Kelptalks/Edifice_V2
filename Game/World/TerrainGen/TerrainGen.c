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
#include "Perlin Noise/PerlinGenerator.h"

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


    world->terrainGenRules = terrainGenRules;


    //Create testing hill

}

void genChunk(struct World world, int worldX, int worldY, int worldZ){
    struct WorldChunk* WorldChunk = getWordChunkFromMap(world.worldChunkHashMap, worldX, worldY, worldZ);







}

void genArea(struct World* world, unsigned long key, int xStart, int yStart, int xArea, int yArea, int zArea){
    int zStart = -30;

    int xEnd = xStart + xArea;
    int yEnd = yStart + yArea;
    int zEnd = zStart + zArea;


    //Get an array of only rules applicable to area
    struct ArrayList* lairRulesInArea = getLairRulesInArea(world->terrainGenRules->lairRules, zStart, zEnd);

    //Loop through keys in the area
    for (int x = xStart; x < xArea; x++){
        for (int y = yStart; y < yArea; y++){
            for (int z = zStart; z < zArea; z++) {
                //Set Lair Shifting rule

                //Set lair rules
                for (int rule = 0; rule < lairRulesInArea->length; rule++) {
                    //Lair building
                    struct LairRule *lairRule = (struct LairRule *) indexList(lairRulesInArea, rule);
                    if (zInRuleBounds(lairRule, zStart + z)) {

                        int heightMod = perlinAt(x * 0.03, y * 0.03) * 25;


                        int oceanLevel = 15;
                        if (heightMod > oceanLevel){
                            int currentHeightMod = heightMod;
                            while (currentHeightMod > oceanLevel) {
                                currentHeightMod--;
                                setBlockAtWorldCor(world, x, y, z - currentHeightMod, Water);
                            }
                            setBlockAtWorldCor(world, x, y, z - heightMod, Sand);
                        }
                        else{
                            setBlockAtWorldCor(world, x, y, z - heightMod,lairRule->blockType);\
                            if (lairRule->blockType == GreenGrass){
                                generatePlant(world, x, y, z - heightMod, GreenGrass);
                            }
                        }
                    }
                }
            }
        }

    }
}