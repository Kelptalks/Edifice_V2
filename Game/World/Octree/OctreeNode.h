//
// Created by Spencer on 3/19/2024.
//

#ifndef OCTREENODE_H
#define OCTREENODE_H

#include <stdbool.h>

#define NUM_CHILDREN 8

struct OctreeNode{
    // Union to hold either children or data
    union {
        struct OctreeNode* children[NUM_CHILDREN];
        short data[NUM_CHILDREN];
    };

    //If this is a node at the lowest depth
    bool isLeaf;
};


struct OctreeNode* createOctreeNode();

void createChildren(struct OctreeNode* octreeNode, int depth);

void getOctreeNode(struct OctreeNode* octreeNode, unsigned long key, int depth);

short getOctreeKeyVal(struct OctreeNode* octreeNode, unsigned long key, int depth);

void setOctreeKeyValue(struct OctreeNode* octreeNode, unsigned long key, int depth, short value);

void freeNode(struct OctreeNode* octreeNode);

void fillNode(struct OctreeNode* octreeNode, int depth, short value);

#endif
