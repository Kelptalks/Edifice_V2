//
// Created by Spencer on 3/27/2024.
//

#ifndef OCTREE_H
#define OCTREE_H

#include <stdbool.h>

struct Octree{
    int depth;

    unsigned int nextFreeIndex;

    int nodeDataArrayLength;
    unsigned int* branchData;

    int octreeDataArrayLength;
    unsigned int* octreeData;

    int volume;
    bool debug;
};

struct Octree* createOctree(int scale);

//Get the Dimension Of the octree
int getOctreeDimensions(int depth);

//Get the volume Of the octree
long getOctreeVolume(int depth);

int getOctreeDataArrayLength(int depth);

void setOctreeValue(struct Octree* octree, unsigned int indexOfCurrentBranch, int currentDepth, int key, unsigned int value);

unsigned int getOctreeValue(struct Octree* octree, unsigned int rootBranchIndex, int currentDepth, int key);
#endif

void freeOctree(struct Octree* octree);

void testOctree();