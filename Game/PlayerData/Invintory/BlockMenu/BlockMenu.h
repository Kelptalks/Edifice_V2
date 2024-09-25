//
// Created by Spencer on 9/25/2024.
//

#ifndef EDIFICE_BLOCKMENU_H
#define EDIFICE_BLOCKMENU_H

#include "../../../Blocks/Blocks.h"

struct BlockSelectionMenu{
    int rowLength;
    int columnLength;

    int blockCount;

    enum Block** blocks;
};

struct BlockSelectionMenu* createBlockSelectionMenu(int blockCount, int rowLength);

enum Block getBlockOnMenu(struct BlockSelectionMenu* blockSelectionMenu, int x, int y);

#endif //EDIFICE_BLOCKMENU_H
