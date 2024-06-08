//
// Created by Spencer on 4/28/2024.
//

#ifndef ENGINE_ARRAYLIST_H
#define ENGINE_ARRAYLIST_H

struct ArrayList{
    int size;
    int length;
    int** ptrs;
};

void expandList(struct ArrayList* arrayList);

struct ArrayList* createList();

void addList(struct ArrayList* arrayList, int* ptr);

void setListIndex(struct ArrayList* arrayList, int* ptr, int index);

int* indexList(struct ArrayList* arrayList, int index);

void clearList(struct ArrayList* arrayList);

void freeList(struct ArrayList* arrayList);

#endif //ENGINE_ARRAYLIST_H
