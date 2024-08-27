//
// Created by Spencer on 3/27/2024.
//

#ifndef OCTREE_H
#define OCTREE_H

struct Octree{
    struct OctreeNode* root;
    int RootDepth;

};


long getSize(int scale);

long getCenter(int scale);

struct Octree* createOctree(int maxDepth);

int getBlock(struct Octree* octree, long key);

int setBlock(struct Octree* octree, long key, short value);

int getOctreeDimensions(int maxDepth);

#endif
