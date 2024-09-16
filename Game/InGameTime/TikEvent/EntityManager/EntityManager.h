//
// Created by Spencer on 9/16/2024.
//

#ifndef EDIFICE_ENTITYMANAGER_H
#define EDIFICE_ENTITYMANAGER_H

enum EntityDirection{
    EntityNorth,
    EntityNorthEast,
    EntityEast,
    EntitySouthEast,
    EntitySouth,
    EntitySouthWest,
    EntityWest,
    EntityNorthWest
};

enum Entity{
    EntityMan,
};

void getEntitySpriteSheetLocation(enum Entity entity, int* xCor, int* yCor, int* width, int* height);

#endif //EDIFICE_ENTITYMANAGER_H
