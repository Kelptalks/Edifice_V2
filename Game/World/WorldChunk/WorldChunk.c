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

    worldChunk->octreeNode = createOctreeNode();

    worldChunk->xCor = xCor;
    worldChunk->yCor = yCor;
    worldChunk->zCor = zCor;

    return worldChunk;
}

enum Block getBlockInWorldChunk(struct WorldChunk* worldChunk, int x, int y, int z){
    unsigned long key = cordsToKey(6, x, y, z);
    return getOctreeKeyVal(worldChunk->octreeNode, key, 6);
}

void setBlockInWorldChunk(struct WorldChunk* worldChunk, int x, int y, int z, enum Block block){
    unsigned long key = cordsToKey(6, x, y, z);
    setOctreeKeyValue(worldChunk->octreeNode, key, 6, block);
}

void testWorldChunk(){
    clearBugReports();

    struct WorldChunk* worldChunk = createWorldChunk(15, 23, 12);

    setBlockInWorldChunk(worldChunk, 2, 12, 3, BlueMushroomBlock);

    reportBug("Octree Key Val %i\n", getBlockInWorldChunk(worldChunk, 2, 12, 3));
}
