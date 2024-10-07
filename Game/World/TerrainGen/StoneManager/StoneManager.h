//
// Created by Spencer on 10/7/2024.
//

#ifndef STONEMANAGER_H
#define STONEMANAGER_H

#include <stdlib.h>
#include <math.h>
#include "../../Octree/Octree.h"
#include "../../World.h"
#include "../../../Blocks/Blocks.h"

void generateStone(struct World* world, int worldX, int worldY, int worldZ, enum Block block);

#endif //STONEMANAGER_H
