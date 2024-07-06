//
// Created by Spencer on 4/29/2024.
//

#include <stdlib.h>
#include <math.h>
#include "../../Octree/KeyMod.h"
#include "../../Octree/OctreeNode.h"
#include "../../Octree/Octree.h"
#include "../../World.h"
#include "../../../Blocks/Blocks.h"


//Build leave pattern
void buildLeaves(struct World* world, unsigned long key){
    setOctreeKeyValue(world->octree->root, modKey(key, 0, 0, 0, 0), world->octree->RootDepth, Leave);
    setOctreeKeyValue(world->octree->root, modKey(key, 1, 0, 0, 0), world->octree->RootDepth, Leave);
    setOctreeKeyValue(world->octree->root, modKey(key, -1, 0, 0, 0), world->octree->RootDepth, Leave);
    setOctreeKeyValue(world->octree->root, modKey(key, 0, -1, 0, 0), world->octree->RootDepth, Leave);
    setOctreeKeyValue(world->octree->root, modKey(key, 0, 1, 0, 0), world->octree->RootDepth, Leave);
    setOctreeKeyValue(world->octree->root, modKey(key, 0, 0, 1, 0), world->octree->RootDepth, Leave);
}

//Build the branch of a tree
void buildBranch(struct World* world, unsigned long key){
    int rand = rand % 4;
    //select random direction
    int yMod = 0;
    int xMod = 0;
    if (rand == 0){
        xMod = 1;
    }
    else if (rand == 1){
        xMod = -1;
    }
    else if (rand == 2){
        yMod = 1;
    }
    else if (rand == 3){
        yMod = -1;
    }
    for (int x = 1; x < 3; x++){
        setOctreeKeyValue(world->octree->root, modKey(key, xMod * x, yMod * x, 0, 0), world->octree->RootDepth, Wood);
    }
    buildLeaves(world, modKey(key, xMod * 3, yMod * 3, 1, 0));
}

//Build a purple tree
void buildTree(struct World* world, unsigned long key){
    int height = rand() % 10 + 5;
    int branchHeight = -1;
    if (height > 10){
        branchHeight = rand()%4 + 5;
    }

    //Build the trunk and branches
    for (int z = 0; z < height; z++){
        setOctreeKeyValue(world->octree->root, modKey(key, 0, 0, z, 0), world->octree->RootDepth, Wood);
        if (branchHeight == z){
            buildBranch(world, modKey(key, 0, 0, z, 0));
        }
    }
    //Top tree with leaves
    buildLeaves(world, modKey(key, 0, 0, height, 0));

}



void buildMushroom(struct World* world, unsigned long key){
    int height = rand() % 30 + 10;
    int stemRadius = (height / ((rand()%20) + 5)) + 3;

    //Build the stem
    for (int z = 0; z < height; z++){
        for (int x = -stemRadius; x < stemRadius; x++){
            for (int y = -stemRadius; y < stemRadius; y++){
                if (sqrt(x*x + y*y) < stemRadius){
                    setOctreeKeyValue(world->octree->root, modKey(key, x, y, z, 0), world->octree->RootDepth, MushroomStem);
                }
            }
        }
    }

    int topRadius = stemRadius + 8 + (rand() % 5);

    unsigned long mushroomTopKey = modKey(key, 0, 0, height, 0);
    int zMod = 0;
    while (topRadius > 2) {
        for (int x = -topRadius; x < topRadius; x++) {
            for (int y = -topRadius; y < topRadius; y++) {
                if (sqrt(x * x + y * y) < topRadius) {
                    setOctreeKeyValue(world->octree->root, modKey(mushroomTopKey, x, y, zMod, 0), world->octree->RootDepth,
                                      BlueMushroomBlock);
                }
            }
        }
        zMod++;
        topRadius -= (rand() % 2);
    }
}

void buildDandi(struct World* world, unsigned long key){
    int height = rand() % 25 + 12;

    int stemRadius = height / 15;
    //Build the stem
    for (int z = 0; z < height; z++){
        for (int x = -stemRadius; x < stemRadius; x++){
            for (int y = -stemRadius; y < stemRadius; y++){
                if (sqrt(x*x + y*y) < stemRadius){
                    setOctreeKeyValue(world->octree->root, modKey(key, x, y, z, 0), world->octree->RootDepth, DandiStem);
                }
            }
        }
    }

    //Build the ball
    unsigned long puffTopKey = modKey(key, 0, 0, height--, 0);

    int puffRadius = stemRadius * 3.2;
    //Make sure number is odd
    if (puffRadius % 2 == 0){
        puffRadius++;
    }
    for (int x = -puffRadius; x < puffRadius; x++) {
        for (int y = -puffRadius; y < puffRadius; y++) {
            for (int z = -puffRadius; z < puffRadius; z++) {
                // Calculate the distance from the center
                int dx = x;
                int dy = y;
                int dz = z;
                if ((dx * dx + dy * dy + dz * dz) <= (puffRadius * puffRadius)) {
                    if (rand() % 5 != 0) {
                        setOctreeKeyValue(world->octree->root, modKey(puffTopKey, x, y, z, 0), world->octree->RootDepth,
                                          Dandi);
                    }
                }
            }
        }
    }
}


void generatePlant(struct World* world, unsigned long key, enum Block block){
    if (isPlantable(block)){
        int randomVal = rand() % 100;
        key = modKey(key, 0, 0, 1, 0);

        //Generate if grass
        if (block == Grass){
            //reportBug("%i \n", randomVal);
            //60% chance to grow empty
            if (randomVal <= 74){
                return;
            }
            //20% flower
            else if (randomVal <= 95){
                //50% chance to be white or yellow
                if (randomVal <= 80) {
                    setOctreeKeyValue(world->octree->root, key, world->octree->RootDepth, WhiteFlowers);
                }
                else{
                    setOctreeKeyValue(world->octree->root, key, world->octree->RootDepth, YellowFlowers);
                }
            }
            //10% flour
            else if (randomVal <= 97){
                setOctreeKeyValue(world->octree->root, key, world->octree->RootDepth, Flour);
            }
            else if (randomVal <= 98){
                setOctreeKeyValue(world->octree->root, key, world->octree->RootDepth, Mushroom);
            }
            //1% tree
            else {
                if (rand() % 2 == 0) {
                    int randomTree = rand() % 200;
                    if (randomTree < 190) {
                        buildTree(world, key);
                    } else if (randomTree < 199) {
                        buildDandi(world, key);
                    } else {
                        buildMushroom(world, key);
                    }
                }
            }


        }


    }
}