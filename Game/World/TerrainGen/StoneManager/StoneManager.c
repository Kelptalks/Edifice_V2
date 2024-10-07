//
// Created by Spencer on 10/7/2024.
//

#include "StoneManager.h"

#include <stdlib.h>


void generateStone(struct World* world, int worldX, int worldY, int worldZ, enum Block block) {
    if (block == Stone) {
        int randomVal = rand() % 100;

        if (randomVal >= 97) {
            setBlockAtWorldCor(world, worldX, worldY, worldZ, Iron);
        }
        else if (randomVal >= 96) {
            setBlockAtWorldCor(world, worldX, worldY, worldZ, Copper);
        }

    }
}
