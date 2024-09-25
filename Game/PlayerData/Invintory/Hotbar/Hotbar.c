//
// Created by Spencer on 9/25/2024.
//



#include <malloc.h>
#include "Hotbar.h"
#include "../../../Debuging/Test_Main.h"

struct HotBar* createHotBar(int length){
    struct HotBar* hotBar = malloc(sizeof (struct HotBar));
    if (hotBar == NULL){
        reportBug("failed to malloc HotBar struct\n");
        return NULL;
    }
    hotBar->length = length;
    hotBar->selectedSlot = 0;

    hotBar->slots = calloc(sizeof (enum Block), length);
    if (hotBar->slots == NULL){
        reportBug("failed to malloc HotBar slots\n");
        free(hotBar);
        return NULL;
    }

    return hotBar;
}

enum Block getHotBarSlotBlockType(struct HotBar* hotBar, int slot){
    if (slot < hotBar->length){
        return hotBar->slots[slot];
    }
    return Debug;
}

void setHotBarSlotBlockType(struct HotBar* hotBar, int slot, enum Block block){
    if (slot < hotBar->length){
        hotBar->slots[slot] = block;
    }
}
