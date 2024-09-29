//
// Created by Spencer on 8/27/2024.
//

#include <malloc.h>
#include "WorldChunk.h"
#include "../World.h"
#include "../../Blocks/Blocks.h"
#include "../../Debuging/Test_Main.h"
#include "../Octree/Tools/KeyMod.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * WorldChunk management
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

struct WorldChunk* createWorldChunk(int xCor, int yCor, int zCor){
    struct WorldChunk* worldChunk = malloc(sizeof (struct WorldChunk));
    if (worldChunk == NULL){
        reportBug("failed to malloc world chunk \n");
        return NULL;
    }

    worldChunk->octree = createOctree(6);
    worldChunk->octree->debug = false;

    worldChunk->xCor = xCor;
    worldChunk->yCor = yCor;
    worldChunk->zCor = zCor;

    return worldChunk;
}

enum Block getBlockInWorldChunk(struct WorldChunk* worldChunk, int x, int y, int z){
    int key = cordsToKey(6, x, y, z);;
    enum Block block = getOctreeValue(worldChunk->octree, 0, worldChunk->octree->depth, key);
    if (block > getTotalBlockCount()){
        return Air;
    }
    return block;
}

void setBlockInWorldChunk(struct WorldChunk* worldChunk, int x, int y, int z, enum Block block){
    int key = cordsToKey(6, x, y, z);
    if (worldChunk->octree->debug){
        reportBug("\n\nsetting block at (%i,%i,%i)\n",x,y,z);
        printKeyIndex(key, 6);
    }

    setOctreeValue(worldChunk->octree,0, worldChunk->octree->depth, key, block);
}

void testWorldChunk(){
    clearBugReports();

    struct WorldChunk* worldChunk = createWorldChunk(15, 23, 12);

    setBlockInWorldChunk(worldChunk, 2, 12, 3, BlueMushroomBlock);

    reportBug("Octree Key Val %i\n", getBlockInWorldChunk(worldChunk, 2, 12, 3));
    free(worldChunk);
}
