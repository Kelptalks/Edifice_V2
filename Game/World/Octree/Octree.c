//
// Created by Spencer on 3/27/2024.
//

#include <stdio.h>
#include "stdlib.h"
#include "Octree.h"
#include "../../Debuging/Test_Main.h"
#include <stdbool.h>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Get data
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

//getOctreeDimensions
int getOctreeDimensions(int depth){
    return (2 << (depth - 1));
}

//Get the volume Of the octree
long getOctreeVolume(int depth){
    int dimension = getOctreeDimensions(depth);
    return dimension * dimension * dimension;
}

//Get the volume Of the octree
int getOctreeDataArrayLength(int depth){
    int nodeCount = 0;
    for (int i = 0; i <= depth; i++){
        nodeCount += getOctreeVolume(i);
    }
    return nodeCount;
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Branch Management
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
//====================================================================== Branch In use
// Mark the branch as in use
void markBranchAsInUse(unsigned int *branch){
    *branch = *branch | (1 << 8);
};
// Check if branch is in use
bool ifBranchInUse(unsigned int branch){
    return (branch >> 8) & 1;
}

//====================================================================== Branch Depth
//Setting the Depth of a branch
void markBranchDepth(unsigned int *branch, int depth){
    *branch = *branch | ((depth & 7) << 11);
}
//Get the depth of a branch
unsigned int getBranchDepth(int branch){
    return (branch >> 11) & 7;
}

//====================================================================== Branch child
// Sets or clears the 'has child' flag for a branch at a specific child index
void markBranchHasChild(unsigned int *branch, int child, bool hasChildren) {
    if (hasChildren) {
        *branch = *branch | (1 << child);
    } else {
        *branch = *branch & ~(1 << child);
    }
}
// Checks if the branch has a child at the given child index
bool ifBranchHasChild(unsigned int branch, int child) {
    return (branch >> child) & 1;
}

//Create a branch at the location of the child and set the proper variables
void createBranchChild(struct Octree* octree, unsigned int branchIndex, int child, int childDepth){
    unsigned int *branch = &octree->branchData[branchIndex];
    if (!ifBranchHasChild(*branch, child)) {
        //Set up the roots branch connections
        unsigned int octreeDataIndex = (branchIndex << 3) + child;

        //Create the new branch at the location
        unsigned int newBranchIndex = octree->nextFreeIndex;
        unsigned int *newBranch = &octree->branchData[newBranchIndex];
        markBranchDepth(newBranch, childDepth);
        octree->octreeData[octreeDataIndex] = newBranchIndex;
        octree->nextFreeIndex = octree->nextFreeIndex + 1;

        markBranchHasChild(branch, child, true);
    }
    else{
        reportBug("!!!!!!!!!!\n");
        reportBug("!!ERROR!!! \nAttempted to add child to branch that already has one\n");
        reportBug("!!!!!!!!!!\n");
    }
}

unsigned int getBranchChildIndex(struct Octree* octree, unsigned int branchIndex, int indexOfChild){
    return octree->octreeData[(branchIndex << 3) + indexOfChild];
}

// Creates a new child node for the specified branch and sets the child index to point to it
void createOctreeNodeOnBranch(struct Octree* octree, int branchIndex, int childIndex, int depth) {

}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Debug
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

void printKeyIndexes(int key, int depth){
    reportBug("%i, ", (key >> (depth * 3)) & 7);
    if (depth >= 0) {
        printKeyIndexes(key, depth - 1);
    }
    else{
        reportBug("\n");
    }
}

void printBranchDepth(struct Octree* octree, unsigned int branchIndex){
    unsigned int branch = octree->branchData[branchIndex];
    unsigned int depth = getBranchDepth(branch);
    reportBug("Branch saved depth : %i\n", depth);
}


void printIfBranchHasChildren(struct Octree* octree, unsigned int branchIndex){
    unsigned int *branch = &octree->branchData[branchIndex];
    for (int x = 0; x < 8; x++){
        if(ifBranchHasChild(*branch, x)){
            reportBug("True, ");
        }
        else{
            reportBug("False, ");
        }
    }
    reportBug("\n");
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Octree Management
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

// Sets the value in the octree at the given depth and key
void setOctreeValue(struct Octree* octree, unsigned int  indexOfCurrentBranch, int currentDepth, int key, unsigned int value) {
    unsigned int *currentBranch = &octree->branchData[indexOfCurrentBranch];
    int indexOfCurrentBranchChild = (key >> (currentDepth * 3)) & 7;


    if (currentDepth > 0) {
        if (ifBranchHasChild(*currentBranch, indexOfCurrentBranchChild)) {
            unsigned int newBranchIndex = getBranchChildIndex(octree, indexOfCurrentBranch, indexOfCurrentBranchChild);
            setOctreeValue(octree, newBranchIndex, currentDepth - 1, key, value);
        } else
        {
            createBranchChild(octree, indexOfCurrentBranch, indexOfCurrentBranchChild, currentDepth - 1);
            unsigned int newBranchIndex = getBranchChildIndex(octree, indexOfCurrentBranch, indexOfCurrentBranchChild);
            setOctreeValue(octree, newBranchIndex, currentDepth - 1, key, value);
        }
    }
    else{
        octree->octreeData[(indexOfCurrentBranch << 3) + indexOfCurrentBranchChild] = value;
    }
}

// Retrieves the value from the octree at the given depth and key
unsigned int getOctreeValue(struct Octree* octree, unsigned int  indexOfCurrentBranch, int currentDepth, int key) {
    unsigned int *currentBranch = &octree->branchData[indexOfCurrentBranch];
    int indexOfCurrentBranchChild = (key >> (currentDepth * 3)) & 7;

    if (currentDepth > 0) {
        if (ifBranchHasChild(*currentBranch, indexOfCurrentBranchChild)) {
            unsigned int newBranchIndex = getBranchChildIndex(octree, indexOfCurrentBranch, indexOfCurrentBranchChild);
            return getOctreeValue(octree, newBranchIndex, currentDepth - 1, key);
        } else
        {
            return octree->octreeData[(indexOfCurrentBranch << 3) + indexOfCurrentBranchChild];
        }
    }
    else{
        return octree->octreeData[(indexOfCurrentBranch << 3) + indexOfCurrentBranchChild];
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Creation
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

struct Octree* createOctree(int depth){
    struct Octree* octree = malloc(sizeof (struct Octree));
    if (octree == NULL){
        printf("Failed to malloc octree struct\n");
        return NULL;
    }

    //Create octreeDataArray : using the volume of octree of the depth
    octree->octreeDataArrayLength = getOctreeDataArrayLength(depth);
    octree->octreeData = calloc(octree->octreeDataArrayLength, sizeof(unsigned int ));
    if (octree->octreeData == NULL){
        printf("failed to calloc octree Data array of length : %i\n", octree->octreeDataArrayLength);
        free(octree);
        return NULL;
    }


    //Create Octree Node Data
    octree->nodeDataArrayLength = octree->octreeDataArrayLength;
    octree->branchData = calloc(octree->nodeDataArrayLength << 3, sizeof (unsigned int));
    if (octree->branchData == NULL){
        printf("failed to create Octree node Data of length : %i\n", octree->nodeDataArrayLength);
        free(octree->octreeData);
        free(octree);
        return NULL;
    }

    bool debug = false;

    octree->nextFreeIndex = 0;
    octree->volume =  octree->octreeDataArrayLength;
    octree->depth = depth;

    //Create root node
    unsigned int *rootBranch = &octree->branchData[0];
    markBranchDepth(rootBranch, depth);
    markBranchAsInUse(rootBranch);

    octree->nextFreeIndex++;

    return octree;
}

void testOctree(){
    int depth = 6;
    struct Octree* octree = createOctree(depth);

    clearBugReports();

    octree->debug = true;


    // Tests branch in use marking
    unsigned int branch = 0;
    markBranchAsInUse(&branch);
    if (ifBranchInUse(branch)){
        reportBug("pass : in use marking\n");
    }


    // Test depth reading
    int fails = 0;
    for (int x = 0; x < 6; x++) {
        int depth = x;
        branch = 0;
        markBranchDepth(&branch, depth);
        if (getBranchDepth(branch) != depth) {
            reportBug("fail : Depth marking\n");
            fails++;
        }
    }
    if (fails == 0){
        reportBug("Pass : depth Reading\n");
    }


    for (int x = 0; x < 8; x++) {
        createBranchChild(octree, 0, x, octree->depth - 1);
    }

    octree->debug = false;
    for (int x = 0; x < octree->volume; x++){
        setOctreeValue(octree, 0, depth, 6, x);
    }

    int key = 39424;
    printKeyIndexes(key, depth);


    setOctreeValue(octree, 0, depth, key, 5);
    reportBug("\n##############################################################################################################\n");
    unsigned int value = getOctreeValue(octree, 0, depth, key);

    reportBug("Value : %i", value);
    free(octree);
}