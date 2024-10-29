//
// Created by Spencer on 10/29/2024.
//

#ifndef GPUCASTINGMANAGER_H
#define GPUCASTINGMANAGER_H
#include <CL/cl.h>
#include <CL/cl_platform.h>

struct GPUCastingManager {
    cl_platform_id platform;
    cl_device_id device;
    cl_uint numPlatforms, numDevices;

    cl_context context;
    cl_command_queue queue;
};

struct GPUCastingManager* createGPUCastingManager();


#endif //GPUCASTINGMANAGER_H
