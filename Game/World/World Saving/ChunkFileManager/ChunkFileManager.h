//
// Created by Spencer on 10/2/2024.
//

#ifndef EDIFICE_CHUNKFILEMANAGER_H
#define EDIFICE_CHUNKFILEMANAGER_H

#include <stdio.h>
#include "../../World.h"

unsigned int getSizeOfWorldChunk(int depth);

void writeChunkToFile(FILE *file, struct WorldChunk* worldChunk, unsigned int indexInFile);

struct WorldChunk* readChunkFromFile(FILE* file, unsigned int indexInFile);


#endif //EDIFICE_CHUNKFILEMANAGER_H
