//
// Created by Spencer on 8/27/2024.
//

#include "../OctreeNode.h"

#ifndef EDIFICE_OCTREENODEPOOL_H
#define EDIFICE_OCTREENODEPOOL_H

struct OctreeNodePool{
    int maxNodes;

    int totalFreeNodes;

    //Array of pointers to free nodes
    struct OctreeNode** freeNodes;
};

struct OctreeNodePool* CreateOctreeBranchPool(int maxNodes);

#endif //EDIFICE_OCTREENODEPOOL_H
