//
// Created by Spencer on 3/27/2024.
//

#include <stdio.h>
#include "OctreeNode.h"
#include "stdlib.h"
#include "Octree.h"
#include "math.h"

//Create an octree struct with root node and depth vars
struct Octree* createOctree(int scale){

    //Create octree struct
    struct Octree* octree = malloc(sizeof (struct Octree));
    if (octree == NULL){
        FILE * debug;
        debug = fopen("debug", "a");
        fprintf(debug, "Octree | failed to malloc memory for octree \n");
        fclose(debug);

        return NULL;
    }

    //Create node
    struct OctreeNode* octreeNode = createOctreeNode();
    if (octreeNode == NULL){
        FILE * debug;
        debug = fopen("debug", "a");
        fprintf(debug, "Octree | failed to malloc memory for octreeNode \n");
        fclose(debug);
        return NULL;
    }


    octree->RootDepth = scale;
    octree->root = octreeNode;

    return octree;
}

//get a block in the octree
int getBlock(struct Octree* octree, long key){
    return getOctreeKeyVal(octree->root, key, octree->RootDepth);
}

//set a value in the octree
int setBlock(struct Octree* octree, long key, short value){
    setOctreeKeyValue(octree->root, key, octree->RootDepth, value);
}

//free the octree from memory
int freeOctree(struct Octree* octree){
    //Free all nodes in octree
    freeNode(octree->root);
    //Free the octree struct
    free(octree);
}

long getSize(int depth){
    return pow(8,depth);
}

long getCenter(int depth){
    return getSize(depth)/2;
}