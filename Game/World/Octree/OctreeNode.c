//
// Created by Spencer on 3/27/2024.
//

#include "OctreeNode.h"
#include "Tools/KeyMod.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct OctreeNode* createOctreeNode(){

    struct OctreeNode* newOctreeNode = calloc(1, sizeof(struct OctreeNode));

    if (newOctreeNode == NULL){
        FILE * debug;
        debug = fopen("debug", "a");
        fprintf(debug, "OctreeNode | failed to malloc memory for octreeNode struct \n");
        fclose(debug);
        return NULL;
    }

    return newOctreeNode;
}

void createChildren(struct OctreeNode* octreeNode, int depth){
    //Check that octreeNode is valid
    if (octreeNode == NULL){
        printf("OctreeNode | Failed to create children as octreeNode is null\n");
        return;
    }

    //If node is a branch
    if (depth > 0){
        octreeNode->isLeaf = false;
        for (int x = 0; x < NUM_CHILDREN; x++){
            octreeNode->children[x] = createOctreeNode();
        }
    }

    //if node is a leaf
    else {
        octreeNode->isLeaf = true;
        for (int x = 0; x < NUM_CHILDREN; x++){
            octreeNode->data[x] = 0;
        }
    }
}

void getOctreeNode(struct OctreeNode* octreeNode, unsigned long key, int depth){
    int mask = (7 << 3 * depth);
    int index = (key & mask) >> (3 * depth);

}

//Get a value from the octree with a key
short getOctreeKeyVal(struct OctreeNode* octreeNode, unsigned long key, int depth){
    int mask = (7 << (3 * depth));
    int index = (key & mask) >> (3 * depth);
    if (depth > 0){
        if (octreeNode->children[index] == NULL){
            return 0;
        } else{
            return(getOctreeKeyVal(octreeNode->children[index], key, depth - 1));
        }
    } else{
        return (octreeNode->data[index]);
    }
}

//set the value of a node in octree, and generate necessary children to set that value
void setOctreeKeyValue(struct OctreeNode* octreeNode, unsigned long key, int depth, short value){
    int mask = (7 << (3 * depth));
    int index = (key & mask) >> (3 * depth);

    if (depth > 0){
        if (octreeNode->children[index] == NULL){
            //Create node and assign children.
            octreeNode->isLeaf = false;
            octreeNode->children[index] = createOctreeNode();
            setOctreeKeyValue(octreeNode->children[index], key, depth - 1, value);

        } else{
            setOctreeKeyValue(octreeNode->children[index], key, depth - 1, value);
        }
    } else{

        if (octreeNode->isLeaf == false){
            octreeNode->isLeaf = true;
            for (int x = 0; x < 8; x++){
                octreeNode->children[x] = 0;
            }
        }
        octreeNode->data[index] = value;

    }
}

void fillNode(struct OctreeNode* octreeNode, int depth, short value){
    //Loop through all children nodes and fill

    if (depth > 0){
        for (int index = 0; index < 8; index++) {
            //Create if lower nodes do not exist
            if (octreeNode->children[index] == NULL) {
                octreeNode->children[index] = createOctreeNode();
            }

            //fill lower nodes
            fillNode(octreeNode->children[index], depth - 1, value);
        }
    }
    //If at max depth
    else {
        //set values of lowest node
        for (int index = 0; index < 8; index++) {
            octreeNode->data[index] = value;
        }
    }
}

void freeNode(struct OctreeNode* octreeNode){
    //free itself and data if leaf
    if (octreeNode->isLeaf){
        free(octreeNode->data);
        free(octreeNode);
    }
    else {
        //free children
        for (int x = 0; x < NUM_CHILDREN; x++) {
            freeNode(octreeNode);
        }
        //free itself
        free(octreeNode);
    }
}