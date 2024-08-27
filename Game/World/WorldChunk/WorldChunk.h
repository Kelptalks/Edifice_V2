//
// Created by Spencer on 8/27/2024.
//

#ifndef EDIFICE_WORLDCHUNK_H
#define EDIFICE_WORLDCHUNK_H

struct WorldChunk{
    struct Octree* octree;

};

enum Block getBlockInWorldChunk(struct WorldChunk* worldChunk, int x, int y, int z);


#endif //EDIFICE_WORLDCHUNK_H
