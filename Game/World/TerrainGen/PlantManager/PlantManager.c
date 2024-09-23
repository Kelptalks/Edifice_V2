//
// Created by Spencer on 4/29/2024.
//

#include <stdlib.h>
#include <math.h>
#include "../../Octree/Tools/KeyMod.h"
#include "../../Octree/OctreeNode.h"
#include "../../Octree/Octree.h"
#include "../../World.h"
#include "../../../Blocks/Blocks.h"


//Build leave pattern
void buildLeaves(struct World* world, int worldX, int worldY, int worldZ){
    setBlockAtWorldCor(world, worldX, worldY, worldZ, Leave);
    setBlockAtWorldCor(world, worldX + 1, worldY, worldZ, Leave);
    setBlockAtWorldCor(world, worldX - 1, worldY, worldZ, Leave);
    setBlockAtWorldCor(world, worldX, worldY + 1, worldZ, Leave);
    setBlockAtWorldCor(world, worldX, worldY - 1, worldZ, Leave);
    setBlockAtWorldCor(world, worldX, worldY, worldZ + 1, Leave);
}

//Build the branch of a tree
void buildBranch(struct World* world, int worldX, int worldY, int worldZ, enum Block blockType){
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
        setBlockAtWorldCor(world, worldX + (xMod * x), worldY + (yMod * x), worldZ, Leave);
    }
    buildLeaves(world, worldX + (xMod * 3), worldY + (yMod * 3), worldZ);
}

//Build a purple tree
void buildTree(struct World* world, int worldX, int worldY, int worldZ){

    enum Block blockType = BrownWood;
    if (rand() % 10 == 0){
        blockType = PurpleWood;
    };

    int height = rand() % 10 + 5;
    int branchHeight = -1;
    if (height > 10){
        branchHeight = rand()%4 + 5;
    }

    //Build the trunk and branches
    for (int z = 0; z < height; z++){

        setBlockAtWorldCor(world, worldX, worldY, worldZ + z, blockType);
        if (branchHeight == z){
            buildBranch(world, worldX, worldY, worldZ + z, blockType);
        }
    }
    //Top tree with leaves
    buildLeaves(world, worldX, worldY, worldZ + height);
}



void buildMushroom(struct World* world, int worldX, int worldY, int worldZ){
    int height = rand() % 30 + 10;
    int stemRadius = (height / ((rand()%20) + 5)) + 3;

    //Build the stem
    for (int z = 0; z < height; z++){
        for (int x = -stemRadius; x < stemRadius; x++){
            for (int y = -stemRadius; y < stemRadius; y++){
                if (sqrt(x*x + y*y) < stemRadius){
                    setBlockAtWorldCor(world, worldX + x, worldY + y, worldZ + z, MushroomStem);
                }
            }
        }
    }

    enum Block blockType = BlueMushroomBlock;
    if (rand() % 2 == 0){
        blockType = PinkMushroomBlock;
    };

    int topRadius = stemRadius + 8 + (rand() % 5);

    int zMod = 0;
    while (topRadius > 2) {
        for (int x = -topRadius; x < topRadius; x++) {
            for (int y = -topRadius; y < topRadius; y++) {
                if (sqrt(x * x + y * y) < topRadius) {
                    setBlockAtWorldCor(world, worldX + x, worldY + y, worldZ + zMod + height, blockType);
                }
            }
        }
        zMod++;
        topRadius -= (rand() % 2);
    }
}

void buildDandi(struct World* world, int worldX, int worldY, int worldZ){
    int height = rand() % 25 + 12;

    int stemRadius = height / 15;
    //Build the stem
    for (int z = 0; z < height; z++){
        for (int x = -stemRadius; x < stemRadius; x++){
            for (int y = -stemRadius; y < stemRadius; y++){
                if (sqrt(x*x + y*y) < stemRadius){
                    setBlockAtWorldCor(world, worldX + x, worldY + y, worldZ + z, DandiStem);
                }
            }
        }
    }

    //Build the ball
    int puffTop = height--;

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
                        setBlockAtWorldCor(world, worldX + x, worldY + y, worldZ + z + puffTop, Dandi);
                    }
                }
            }
        }
    }
}


void generatePlant(struct World* world, int worldX, int worldY, int worldZ, enum Block block){
    if (isPlantable(block)){
        int randomVal = rand() % 100;
        worldZ++;

        //Generate if grass
        if (block == GreenGrass){
            //reportBug("%i \n", randomVal);
            //60% chance to grow empty
            if (randomVal <= 74){
                return;
            }
            //20% flower
            else if (randomVal <= 95){
                //50% chance to be white or yellow
                if (randomVal <= 80) {
                    setBlockAtWorldCor(world, worldX, worldY, worldZ, WhiteFlowers);
                }
                else if (randomVal < 95){
                    setBlockAtWorldCor(world, worldX, worldY, worldZ, YellowFlowers);
                }
                else {
                    setBlockAtWorldCor(world, worldX, worldY, worldZ, Rock);
                }
            }
            //10% flour / Mushroom
            else if (randomVal <= 97){
                setBlockAtWorldCor(world, worldX, worldY, worldZ, Flour);
            }
            else if (randomVal <= 98){
                setBlockAtWorldCor(world, worldX, worldY, worldZ, Mushroom);
            }
            //1% tree
            else {
                if (rand() % 2 == 0) {
                    int randomTree = rand() % 200;
                    if (randomTree < 190) {
                        buildTree(world, worldX, worldY, worldZ);
                    } else if (randomTree < 199) {
                        buildDandi(world, worldX, worldY, worldZ);
                    } else {
                        buildMushroom(world, worldX, worldY, worldZ);
                    }
                }
            }


        }


    }
}