//
// Created by Spencer on 4/24/2024.
//

#ifndef ENGINE_CASTINGTHREAD_H
#define ENGINE_CASTINGTHREAD_H


struct args{
    struct Octree* octree;
    struct CastedChunk* castedChunk;
};

void* castChunk(void* arg);

#endif //ENGINE_CASTINGTHREAD_H
