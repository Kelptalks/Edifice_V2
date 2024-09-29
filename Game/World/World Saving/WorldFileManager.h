//
// Created by Spencer on 7/1/2024.
//
#include "../World.h"

#ifndef EDIFICE_WORLDFILEMANAGER_H
#define EDIFICE_WORLDFILEMANAGER_H

struct WorldFile{
    unsigned int chunkDataArray;
};

void saveWorldToFile(struct World* world);

struct World* readWorldData(char* fileName);

//Delete the world file
void deleteWorldFile(char *fileName);

//Check if the world file exists
bool ifFileExists(const char *filename);

void testWorldSaving();

#endif //EDIFICE_WORLDFILEMANAGER_H
