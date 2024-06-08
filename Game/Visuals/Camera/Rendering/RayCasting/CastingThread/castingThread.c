//
// Created by Spencer on 4/24/2024.
//

#include <pthread.h>
#include "castingThread.h"
#include "../RayCastingManager.h"
#include "../../CastedBlockManager/CastedBlockManager.h"
#include "../../../../../Debuging/Test_Main.h"
#include "../../../../../World/Octree/Octree.h"

//Were the threads code will run
void* castChunk(void* arg) {
    struct args* data = (struct args*) arg;

    rayCastChunk(data->castedChunk, data->octree);
    data->castedChunk->rayCast = true;
    data->castedChunk->busy = false;
    free(data);
    pthread_exit(NULL);
}
