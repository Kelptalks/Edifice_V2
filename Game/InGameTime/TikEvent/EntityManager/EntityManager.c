//
// Created by Spencer on 9/16/2024.
//

#include "EntityManager.h"

void getEntitySpriteSheetLocation(enum Entity entity, int* xCor, int* yCor, int* width, int* height){
    if (entity == EntityMan){
         *xCor = 768;
         *yCor = 832;
         *width = 64;
         *height = 128;
    }
}