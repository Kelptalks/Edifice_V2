//
// Created by Spencer on 9/25/2024.
//

#include <malloc.h>
#include "BlockMenu.h"
#include "../../../Debuging/Test_Main.h"

struct BlockSelectionMenu* createBlockSelectionMenu(int blockCount, int rowLength){

    struct BlockSelectionMenu* blockSelectionMenu = malloc(sizeof (struct BlockSelectionMenu));
    if (blockSelectionMenu == NULL){
        reportBug("Failed to malloc block selection menu\n");
        return NULL;
    }

    //create the blocks array
    blockSelectionMenu->blocks = malloc(sizeof (enum Block*) * rowLength);
    int columnLength = blockCount / rowLength;

    for (int i = 0; i < rowLength; i++){
        blockSelectionMenu->blocks[i] = malloc(sizeof (enum Block) * columnLength);


        for (int b = 0; b < columnLength; b++){
            enum Block block = (i * columnLength) + b;
            if (block < blockCount){
                blockSelectionMenu->blocks[i][b] = block;
            }
            else{
                blockSelectionMenu->blocks[i][b] = 0;
            }
        }
    }

    blockSelectionMenu->rowLength = rowLength;

    blockSelectionMenu->columnLength = columnLength;

    return blockSelectionMenu;
}

enum Block getBlockOnMenu(struct BlockSelectionMenu* blockSelectionMenu, int x, int y){
    if (x < blockSelectionMenu->rowLength && y < blockSelectionMenu->columnLength){
        return blockSelectionMenu->blocks[x][y];
    }
    return Debug;
}