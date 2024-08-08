//
// Created by Spencer on 4/18/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include "Octree/Octree.h"
#include "Octree/OctreeNode.h"
#include "World.h"
#include "Octree/KeyMod.h"
#include "TerrainGen/TerrainGen.h"

struct World* createWorld(int scale){
    //Create world struct
    struct World* world = malloc(sizeof (struct World));
    if (world == NULL){
        //append debug file
        FILE * debug;
        debug = fopen("debug", "a");
        fprintf(debug, "World | failed to malloc memory for world struct \n");
        fclose(debug);

        return NULL;
    }

    //Name the world
    char name[] = "World";
    world->name = malloc(sizeof (name));
    world->name = name;

    //Create octree for world data
    struct Octree* octree = createOctree(scale);
    if (octree == NULL){
        //append debug file
        FILE * debug;
        debug = fopen("debug", "a");
        fprintf(debug, "World | failed to malloc memory for octree struct \n");
        fclose(debug);
        return NULL;
    }

    world->totalBlocks = 35;


    //Calculate ground height
    world->octree = octree;
    createTerrainGenRules(world);


    unsigned long key = modKey(0, 0, 0, 0, octree->RootDepth);

    genArea(world, key, 200, 200, 50);

    return world;
}
