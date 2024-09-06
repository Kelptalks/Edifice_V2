//
// Created by Spencer on 4/24/2024.
//

#include <pthread.h>
#include "castingThread.h"
#include "../RayCastingManager.h"
#include "../../CastedBlockManager/CastedBlockManager.h"
#include "../../../../../Debuging/Test_Main.h"
#include "../../../../../World/Octree/Octree.h"
#include "castingThread.h"

//Were the threads code will run
void* castChunk(void* arg) {
    struct args* data = (struct args*) arg;
    rayCastChunk(data->cameraData, data->castedChunk, data->octree);
    data->castedChunk->rayCast = true;
    pthread_mutex_unlock(&data->castedChunk->lock);
    pthread_exit(NULL);
}

void *rayCastingThreadWorker(void* arg){
    struct RayCastingThreadPool* threadPool = (struct RayCastingThreadPool*) arg;
    while (1){
        //Lock the pool
        pthread_mutex_lock(&threadPool->mutex);

        //Wait until tasks are available
        while (threadPool->currentTask == 0 && !threadPool->shutDown){
            pthread_cond_wait(&threadPool->tasksAvailable, &threadPool->mutex);
        }

        //exit properly if shutting down
        if (threadPool->shutDown) {
            pthread_mutex_unlock(&threadPool->mutex);
            break;  // Exit the loop and terminate the thread
        }

        if (threadPool->currentTask > 0) {
            //get The task from the pool
            threadPool->currentTask--;
            struct Task task = threadPool->tasks[threadPool->currentTask];

            //unlock the Thread pool to allow other threads to assign themselves tasks
            pthread_mutex_unlock(&threadPool->mutex);

            //Ray cast the chunk
            pthread_mutex_lock(&task.castedChunk->lock);
            rayCastChunk(threadPool->cameraData, task.castedChunk, threadPool->octree);
            task.castedChunk->rayCast = true;

            pthread_mutex_unlock(&task.castedChunk->lock);

            //Mark task as complete when Thread pool becomes available
            pthread_mutex_lock(&threadPool->mutex);
            threadPool->totalTasksComplete++;
            if (threadPool->totalTasks == threadPool->totalTasksComplete) {
                pthread_cond_signal(&threadPool->allTasksComplete);
            }
            pthread_mutex_unlock(&threadPool->mutex);
        }
    }
    return NULL;
}

struct RayCastingThreadPool* createRayCastingThreadPool(int maxTasks, struct CameraData* cameraData, struct Octree* octree){
    struct RayCastingThreadPool* threadPool = malloc(sizeof (struct RayCastingThreadPool));
    if (threadPool == NULL){
        reportBug("failed to malloc threadPool\n");
        return NULL;
    }
    threadPool->cameraData = cameraData;
    threadPool->octree = octree;

    threadPool->shutDown = false;

    //Create task Q
    threadPool->totalTasks = 0;
    threadPool->currentTask = 0;
    threadPool->totalTasksComplete = 0;
    threadPool->threadCount = MAX_THREADS;

    threadPool->maxTasks = maxTasks;
    threadPool->tasks = malloc(sizeof (struct Task) * maxTasks);
    if (threadPool->tasks == NULL){
        reportBug("failed to malloc tasks for raycasting thread pool\n");
        return NULL;
    }

    //Initialize mutex
    pthread_mutex_init(&threadPool->mutex, NULL);

    //Initialize thread conditions
    pthread_cond_init(&threadPool->tasksAvailable, NULL);
    pthread_cond_init(&threadPool->allTasksComplete, NULL);

    //Initialize threads
    for (int i = 0; i < threadPool->threadCount; i++){
        pthread_create(&threadPool->threads[i], NULL, rayCastingThreadWorker, threadPool);
    }

    return threadPool;
}

void executeAllTasks(struct RayCastingThreadPool* rayCastingThreadPool){
    pthread_mutex_lock(&rayCastingThreadPool->mutex);

    rayCastingThreadPool->totalTasksComplete = 0;
    rayCastingThreadPool->currentTask = rayCastingThreadPool->totalTasks;

    //Alert the worker threads that tasks are available
    pthread_cond_broadcast(&rayCastingThreadPool->tasksAvailable);

    //Wait for all tasks to be completed
    while (rayCastingThreadPool->totalTasksComplete < rayCastingThreadPool->totalTasks){
        pthread_cond_wait(&rayCastingThreadPool->allTasksComplete, &rayCastingThreadPool->mutex);
    }

    rayCastingThreadPool->totalTasks = 0;
    pthread_mutex_unlock(&rayCastingThreadPool->mutex);
}

void addRayCastingTaskToThreadPool(struct RayCastingThreadPool* rayCastingThreadPool, struct CastedChunk* castedChunk){
    pthread_mutex_lock(&rayCastingThreadPool->mutex);
    if (rayCastingThreadPool->totalTasks < rayCastingThreadPool->maxTasks) {
        rayCastingThreadPool->tasks[rayCastingThreadPool->totalTasks].castedChunk = castedChunk;
        rayCastingThreadPool->totalTasks++;
    }
    pthread_mutex_unlock(&rayCastingThreadPool->mutex);
}

void shutdownRayCastingThreadPool(struct RayCastingThreadPool* threadPool) {
    pthread_mutex_lock(&threadPool->mutex);
    threadPool->shutDown = true;
    pthread_cond_broadcast(&threadPool->tasksAvailable);
    pthread_mutex_unlock(&threadPool->mutex);

    for (int i = 0; i < threadPool->threadCount; i++) {
        pthread_join(threadPool->threads[i], NULL);
    }

    pthread_mutex_destroy(&threadPool->mutex);
    pthread_cond_destroy(&threadPool->tasksAvailable);
    pthread_cond_destroy(&threadPool->allTasksComplete);
    free(threadPool->tasks);
    free(threadPool);
}