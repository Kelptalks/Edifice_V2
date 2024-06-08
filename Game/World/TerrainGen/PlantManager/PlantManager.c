//
// Created by Spencer on 4/29/2024.
//

#include <stdlib.h>
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
            //1% tree
            else if (randomVal <= 75){
                buildTree(world, key);
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
            else{
                setOctreeKeyValue(world->octree->root, key, world->octree->RootDepth, Flour);
            }


        }


    }
}