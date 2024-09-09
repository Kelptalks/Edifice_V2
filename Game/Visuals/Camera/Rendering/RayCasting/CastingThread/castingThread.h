//
// Created by Spencer on 4/24/2024.
//
#include <pthread.h>
#include <stdbool.h>

#ifndef ENGINE_CASTINGTHREAD_H
#define ENGINE_CASTINGTHREAD_H

#define MAX_THREADS 15

struct args{
    struct Octree* octree;
    struct CastedChunk* castedChunk;
    struct CameraData* cameraData;
};

struct Task{
    struct CastedChunk* castedChunk;
};

struct RayCastingThreadPool{

    //Tasks array management
    struct Task* tasks;
    int maxTasks;
    int totalTasks;
    int totalTasksComplete;
    int currentTask;


    //Threads
    int threadCount;
    pthread_t threads[MAX_THREADS];

    //ThreadManagement
    pthread_mutex_t mutex;
    pthread_cond_t tasksAvailable;
    pthread_cond_t allTasksComplete;
    bool shutDown;

    //Read only data needed
    struct CameraData* cameraData;
};


void* castChunk(void* arg);

struct RayCastingThreadPool* createRayCastingThreadPool(int maxTasks, struct CameraData* cameraData);

void executeAllTasks(struct RayCastingThreadPool* rayCastingThreadPool);

void addRayCastingTaskToThreadPool(struct RayCastingThreadPool* rayCastingThreadPool, struct CastedChunk* castedChunk);

void shutdownRayCastingThreadPool(struct RayCastingThreadPool* threadPool);

#endif //ENGINE_CASTINGTHREAD_H
