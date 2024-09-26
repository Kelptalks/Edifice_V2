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

// Sets or clears the 'has child' flag for a branch at a specific child index
unsigned int  markBranchHasChild(unsigned int branch, int child, bool hasChildren) {
    if (hasChildren) {
        return branch | (1 << child);
    } else {
        return branch & ~(1 << child);
    }
}

// Checks if the branch has a child at the given child index
bool ifBranchHasChild(unsigned int branch, int child) {
    return (branch >> child) & 1;
}

unsigned int  markBranchAsInUse(unsigned int branch){
    return branch | (1 << 8);
};

bool ifBranchInUse(unsigned int branch){
    return (branch >> 8) & 1;
}

unsigned int markBranchDepth(unsigned int branch, int depth){
    return branch | ((depth & 7) << 11);
}

unsigned int getBranchDepth(unsigned int branch){
    return (branch >> 11) & 7;
}

// Creates a new child node for the specified branch and sets the child index to point to it
void createOctreeNodeOnBranch(struct Octree* octree, int branchIndex, int childIndex, int depth) {
    // Mark branch as having a child
    octree->branchData[branchIndex] = markBranchHasChild(octree->branchData[branchIndex], childIndex, true);

    // Allocate a new branch in octreeData
    unsigned int  newBranchIndex = octree->nextFreeIndex++;

    if (ifBranchInUse(octree->branchData[newBranchIndex])){
        reportBug("branch was utilized while still in use\n");
    }


    if (octree->debug) {
        reportBug("Creating new branch from branch index(%i) to new branch index (%i)\n", branchIndex, newBranchIndex);
    }

    unsigned int  rootOctreeDataIndex = (branchIndex << 3) + childIndex;

    // Store the new branch index at the octree data location
    octree->octreeData[rootOctreeDataIndex] = newBranchIndex;
    octree->branchData[newBranchIndex] = markBranchDepth(octree->branchData[newBranchIndex], depth - 1);
    octree->branchData[newBranchIndex] = markBranchAsInUse(octree->branchData[newBranchIndex]);

    //octree->branchData[newBranchIndex] = markBranchAsInUse(octree->branchData[newBranchIndex]);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Branch Management
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

// Sets the value in the octree at the given depth and key
void setOctreeValue(struct Octree* octree, unsigned int  rootBranchIndex, int currentDepth, int key, unsigned int value) {

    unsigned int  indexOfChild = (key >> (currentDepth * 3)) & 7;
    unsigned int  octreeDataIndexAtRootBranch = (rootBranchIndex << 3) + indexOfChild;
    unsigned int  octreeDataValue = octree->octreeData[octreeDataIndexAtRootBranch];

    if (octree->debug) {
        reportBug("Depth: %d | Key: %d | IndexOfChild: %d | octreeDataIndexAtRootBranch: %d\n", currentDepth, key,
               indexOfChild, octreeDataIndexAtRootBranch);

        reportBug("RootBranchIndexDepth : %i\n", getBranchDepth(octree->branchData[rootBranchIndex]));
    }

    if (currentDepth > 0) {
        // Check if branch has a child
        if (ifBranchHasChild(octree->branchData[rootBranchIndex], indexOfChild)) {
            unsigned int indexNextBranch = octreeDataValue;
            // Traverse further down the tree
            setOctreeValue(octree, indexNextBranch, currentDepth - 1, key, value);
        } else {
            // Create a child and continue setting the value
            createOctreeNodeOnBranch(octree, rootBranchIndex, indexOfChild, currentDepth);
            unsigned int  newBranchIndex = octree->octreeData[octreeDataIndexAtRootBranch];
            setOctreeValue(octree, newBranchIndex, currentDepth - 1, key, value);
        }
    }
    else {
        // Set the value at the leaf node
        octree->octreeData[octreeDataIndexAtRootBranch] = value;
    }
}

// Retrieves the value from the octree at the given depth and key
unsigned int getOctreeValue(struct Octree* octree, unsigned int rootBranchIndex, int currentDepth, int key) {
    int indexOfChild = (key >> (currentDepth * 3)) & 7;
    int octreeDataIndexAtRootBranch = (rootBranchIndex << 3) + indexOfChild;
    int octreeDataValue = octree->octreeData[octreeDataIndexAtRootBranch];

    if (currentDepth > 0) {
        // If the branch has a child, traverse further down
        if (ifBranchHasChild(octree->branchData[rootBranchIndex], indexOfChild)) {
            return getOctreeValue(octree, octreeDataValue, currentDepth - 1, key);
        }
        else{
            return 0;
        }
    }

    // Return the value if it's a leaf or no children exist
    if (currentDepth == 0) {
        return octreeDataValue;
    }

    return 0;
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
    octree->branchData = calloc(octree->nodeDataArrayLength, sizeof (unsigned int));
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

    for (int i = 0; i < 8; i++) {
        //createOctreeNodeOnBranch(octree, 0, i);
    }
    return octree;
}

void printKeyIndexes(int key, int depth){
    printf("%i, ", (key >> (depth * 3)) & 7);
    if (depth >= 0) {
        printKeyIndexes(key, depth - 1);
    }
    else{
        printf("\n");
    }
}


void testOctree(){
    struct Octree* octree = createOctree(6);

    clearBugReports();

    octree->debug = true;

    octree->branchData[0];
    octree->branchData[0] = markBranchAsInUse(octree->branchData[0]);
    if (ifBranchInUse( octree->branchData[0])){
        reportBug("pass1\n");
    }

    octree->branchData[0] = markBranchDepth(octree->branchData[0], 6);
    if (getBranchDepth(octree->branchData[0]) == 4){
        reportBug("pass2\n");
    }
    else{
        reportBug("Expected %i, but was %i", 4, getBranchDepth(octree->branchData[0]));
    }


    for (int x = 0; x < octree->volume; x++){
        //setOctreeValue(octree, 0, octree->depth, x, rand() % 70);
    }


    free(octree);
}