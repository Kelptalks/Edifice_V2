//
// Created by Spencer on 9/11/2024.
//

#ifndef EDIFICE_PUFFLOGIC_H
#define EDIFICE_PUFFLOGIC_H

#include "../EntityManager.h"


struct EntityPuffSpecificData{
    enum EntityDirection entityDirection;


    float resistance;
    float velX;
    float velY;
    float velZ;
    float speed;
};

struct Entity* createPuffEntity();

void tickPuffEntity(struct GameData* gameData, struct Entity* entity);

#endif //EDIFICE_PUFFLOGIC_H
