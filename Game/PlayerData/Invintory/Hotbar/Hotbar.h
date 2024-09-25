//
// Created by Spencer on 9/25/2024.
//

#ifndef EDIFICE_HOTBAR_H
#define EDIFICE_HOTBAR_H

#include "../../../Blocks/Blocks.h"

struct HotBar{
    int length;
    enum Block* slots;

    int selectedSlot;
};

struct HotBar* createHotBar(int length);

enum Block  getHotBarSlotBlockType(struct HotBar* hotBar, int slot);

void setHotBarSlotBlockType(struct HotBar* hotBar, int slot, enum Block block);


#endif //EDIFICE_HOTBAR_H
