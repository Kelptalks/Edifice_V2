//
// Created by Spencer on 7/1/2024.
//

#include <stdio.h>
#include "../World.h"
#include "../../Debuging/Test_Main.h"

void openWorldFile(struct World* world){
    reportBug("Saving world\n");

    FILE *file = fopen("Saves/Test.bin", "rb+");
    if (file == NULL){
        file = fopen("Saves/Test.bin", "ab+");
        if (file == NULL){
            reportBug("failed to open world save file \n");
            return;
        }
    }

    unsigned char byte = 1;
    size_t result = fread(&byte, sizeof(byte), 1, file);
    if (result == 0) {
        reportBug("Failed to read byte\n");
        fclose(file);
        return;
    }

    byte--;
    reportBug("file read : %i\n", byte);

    fseek(file, -1, SEEK_CUR);  // Move back one byte
    result = fwrite(&byte, sizeof(byte), 1, file);
    if (result == 0) {
        reportBug("Failed to write byte\n");
        fclose(file);
        return;
    }

    fclose(file);
}