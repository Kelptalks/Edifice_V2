//
// Created by Spencer on 7/1/2024.
//

#include <mbstring.h>
#include <stdio.h>
#include "../World.h"
#include "../../Debuging/Test_Main.h"

void setUpWorldFile(FILE *file){

}

void safeWorldToFile(struct World* world){
    const char *filePath = "Saves/WorldSave.bin";

    // Try to open the file in read mode to check if it exists
    FILE *file = fopen(filePath, "r");

    // File does not exist create
    if (file == NULL) {
        printf("File does not exist. Creating it now...\n");
        file = fopen(filePath, "w");

        if (file == NULL) {
            perror("Error creating file");
        }
        printf("World File Created\n");
        setUpWorldFile(file);

    } else {
        // File exists
        printf("File exists.\n");
        fclose(file); // Close the file if it exists
    }


    printf("closing file\n");
    fclose(file);
}