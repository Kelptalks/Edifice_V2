//
// Created by Spencer on 4/28/2024.
//

#include <malloc.h>
#include "TerrainGen.h"
#include "Perlin Noise/PerlinNoise.h"
#include "../Octree/Tools/KeyMod.h"
#include "../Octree/Octree.h"
#include "LairManager/LairManager.h"
#include "PlantManager/PlantManger.h"
#include "../../../ArrayList/ArrayList.h"
#include "Perlin Noise/PerlinGenerator.h"
#include "StoneManager/StoneManager.h"

void createTerrainGenRules(struct World* world){
    struct TerrainGenRules* terrainGenRules = malloc(sizeof (struct TerrainGenRules));
    if (terrainGenRules == NULL){
        reportBug("Terrain Gen | failed to malloc terrainGenRules struct");
        return;
    }
    terrainGenRules->lairRules = createList();
    terrainGenRules->shiftRules = createList();

    //add all lair rules
    addLairRule(terrainGenRules->lairRules, -60, 15, Stone);
    addLairRule(terrainGenRules->lairRules, 16, 20, Dirt);
    addLairRule(terrainGenRules->lairRules, 21, 21, GreenGrass);


    world->terrainGenRules = terrainGenRules;


    //Create testing hill

}

void genChunk(struct World world, int worldX, int worldY, int worldZ){
    struct WorldChunk* WorldChunk = getWordChunkFromMap(world.worldChunkHashMap, worldX, worldY, worldZ);







}

void genArea(struct World* world, int xStart, int yStart, int xEnd, int yEnd, int roughNess){
    int zStart = -30;
    int zEnd = 100;


    //Get an array of only rules applicable to area
    struct ArrayList* lairRulesInArea = getLairRulesInArea(world->terrainGenRules->lairRules, zStart, zEnd);

    float RoughNess = 0.005f * ((float)roughNess / 5.0f);

    //Loop through keys in the area
    for (int x = xStart; x < xEnd; x++){
        for (int y = yStart; y < yEnd; y++){
            for (int z = zStart; z < zEnd; z++) {
                //Set Lair Shifting rule

                //Set lair rules
                for (int rule = 0; rule < lairRulesInArea->length; rule++) {
                    //Lair building
                    struct LairRule *lairRule = (struct LairRule *) indexList(lairRulesInArea, rule);
                    if (zInRuleBounds(lairRule, zStart + z)) {

                        int heightMod = perlinAt(x * RoughNess, y * RoughNess) * (100);


                        int oceanLevel = 90;
                        if (heightMod > oceanLevel && z > 0){
                            int currentHeightMod = heightMod;
                            while (currentHeightMod > oceanLevel) {
                                currentHeightMod--;
                                setBlockAtWorldCor(world, x, y, z - currentHeightMod, Water);
                            }
                            setBlockAtWorldCor(world, x, y, z - heightMod, Sand);
                        }
                        else{
                            setBlockAtWorldCor(world, x, y, z - heightMod,lairRule->blockType);

                            generatePlant(world, x, y, z - heightMod, lairRule->blockType);
                            generateStone(world, x, y, z - heightMod, lairRule->blockType);
                        }
                    }
                }
            }
        }

    }
}