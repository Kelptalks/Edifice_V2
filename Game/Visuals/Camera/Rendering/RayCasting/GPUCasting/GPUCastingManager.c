//
// Created by Spencer on 10/29/2024.
//

#include "GPUCastingManager.h"

#include "../../../../../Debuging/Test_Main.h"


struct GPUCastingManager* createGPUCastingManager() {
    struct GPUCastingManager* gpuCastingManager = malloc(sizeof(struct GPUCastingManager));

    gpuCastingManager->platform;

    // Get the number of platforms
    clGetPlatformIDs(1, &gpuCastingManager->platform, &gpuCastingManager->numPlatforms);

    // Get the first available platform
    clGetPlatformIDs(gpuCastingManager->numPlatforms, &gpuCastingManager->platform, NULL);

    // Get devices on the platform
    clGetDeviceIDs(gpuCastingManager->platform, CL_DEVICE_TYPE_GPU, 1, &gpuCastingManager->device, &gpuCastingManager->numDevices);


    int err;
    gpuCastingManager->context = clCreateContext(NULL, 1, &gpuCastingManager->device, NULL, NULL, &err);
    if (err != CL_SUCCESS) {
        reportBug("Error during context creation: %d\n", err);
        return NULL;
    }


    cl_command_queue_properties properties[] = { CL_QUEUE_PROPERTIES, CL_QUEUE_PROFILING_ENABLE, 0 };
    gpuCastingManager->queue = clCreateCommandQueueWithProperties(gpuCastingManager->context, gpuCastingManager->device, properties, &err);


    //Kernel setup
    const char *kernelSource = "__kernel void simpleKernel(__global float* data) { int id = get_global_id(0); data[id] += 1.0f; }";
    cl_program program = clCreateProgramWithSource(gpuCastingManager->context, 1, &kernelSource, NULL, &err);

    err = clBuildProgram(program, 1, &gpuCastingManager->device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        size_t logSize;
        clGetProgramBuildInfo(program, gpuCastingManager->device, CL_PROGRAM_BUILD_LOG, 0, NULL, &logSize);
        char *log = (char *)malloc(logSize);
        clGetProgramBuildInfo(program, gpuCastingManager->device, CL_PROGRAM_BUILD_LOG, logSize, log, NULL);
        reportBug("Build log:\n%s\n", log);
        free(log);
        return NULL;
    }

    cl_kernel kernel = clCreateKernel(program, "simpleKernel", &err);

    int dataSize = 1000;
    cl_mem dataBuffer = clCreateBuffer(gpuCastingManager->context, CL_MEM_READ_WRITE, sizeof(float) * dataSize, NULL, &err);


    return gpuCastingManager;

}
