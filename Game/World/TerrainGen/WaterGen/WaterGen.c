//
// Created by Spencer on 7/5/2024.
//

#include "../../../Blocks/Blocks.h"
#include "../../Octree/OctreeNode.h"
#include "../../World.h"
#include "../../Octree/Octree.h"
#include "../../Octree/OctreeNode.h"

void generateWater(struct World* world, unsigned long key, enum Block block){
    if (block == Air){
        setOctreeKeyValue(world->octree->root, key, world->octree->RootDepth, Water1);
    }
}