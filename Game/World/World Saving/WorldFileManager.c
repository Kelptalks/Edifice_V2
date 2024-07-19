//
// Created by Spencer on 7/1/2024.
//

#include <stdio.h>
#include "../World.h"
#include "../Octree/Octree.h"
#include "../Octree/OctreeNode.h"
#include "../Octree/KeyMod.h"
#include "../../Debuging/Test_Main.h"


unsigned long readLongAtIndex(FILE* file, int offset){
    // Move the file pointer to the correct position for reading
    fseek(file, offset * sizeof(short ), SEEK_SET);
    unsigned long test;
    fread(&test, sizeof(unsigned long), 1, file);
    return test;
}

void writeLongAtIndex(FILE* file, int offset, char value){
    // Move the file pointer to the correct position
    fseek(file, offset * sizeof(short ), SEEK_SET);
    // Write the value
    fwrite(&value, sizeof(unsigned long), 1, file);
    // Flush the file buffer to ensure the data is written to the file
    fflush(file);
}

short readShortAtIndex(FILE* file, int offset){
    // Move the file pointer to the correct position for reading
    fseek(file, offset * sizeof(short), SEEK_SET);
    char test;
    fread(&test, sizeof(short), 1, file);
    return test;
}

void writeShortAtIndex(FILE* file, int offset, short value){
    // Move the file pointer to the correct position
    fseek(file, offset * sizeof(short), SEEK_SET);
    // Write the value
    fwrite(&value, sizeof(short), 1, file);
    // Flush the file buffer to ensure the data is written to the file
    fflush(file);
}

void writeNodeToFile(FILE* file, int offset, struct OctreeNode* octreeNode){
    //Write the branch identifier
    writeShortAtIndex(file, offset, 'b');
    offset++;

    //If leaf node
    if (octreeNode->isLeaf) {
        writeShortAtIndex(file, offset, 'l');
        printf("offset : %i\n", offset);
        offset++;

        //Loop through leaf octreeNodes values
        for (int x = 0; x < 8; x++){
            writeShortAtIndex(file, offset + x, octreeNode->data[x]);
        }
    }
    else{
        writeShortAtIndex(file, offset, 'b');
    }



}

struct OctreeNode* readNodeFromFile(FILE* file, int offset){
    printf("offset : %i\n", offset);
    short ifBranch = readShortAtIndex(file, offset);
    printf("offset : %i\n", offset);
    if (ifBranch == 'b'){
        printf("branch\n");
    }

    offset++;
    short ifLeaf = readShortAtIndex(file, offset);
    printf("isLeaf %c\n", ifLeaf);

    if (ifLeaf == 'l'){
        printf("Leaf\n");
    }


    return NULL;
}

//e = end of branch
//b = start of branch
//l = if leaf node

void openWorldFile(struct World* world){
    FILE *file = fopen("Saves/Test.bin", "rb+");
    if (file == NULL) {
        perror("Unable to open file for reading and writing");
    }

    unsigned long value = 13;
    int offset = 0;

    struct OctreeNode* octreeNode = createOctreeNode();
    setOctreeKeyValue(octreeNode, 0, 0, 1);

    writeNodeToFile(file, 50, octreeNode);
    readNodeFromFile(file, 50);

    fclose(file);
}