//
// Created by Spencer on 4/28/2024.
//

#include <malloc.h>
#include "ArrayList.h"
#include "../Game/Debuging/Test_Main.h"

void expandList(struct ArrayList* arrayList){
    //Save old vars for copying
    int** oldPtr = arrayList->ptrs;
    int oldSize = arrayList->size;

    //create a list of double the size
    arrayList->size = arrayList->size * 2;
    arrayList->ptrs = malloc(sizeof (void*) * arrayList->size);

    //Copy old data to new List
    for (int x = 0; x < oldSize; x++){
        arrayList->ptrs[x] = oldPtr[x];
    }
}

struct ArrayList* createList(){
    struct ArrayList* arrayList = malloc(sizeof(struct ArrayList));
    if (arrayList == NULL){
        reportBug("Array List : failed to malloc arraylist struct");
        return NULL;
    }
    arrayList->size = 1;
    arrayList->length = 0;
    arrayList->ptrs = malloc(sizeof (void*) * arrayList->size);
    expandList(arrayList);
    return arrayList;
}

void addList(struct ArrayList* arrayList, int* ptr){
    if (arrayList->length >= arrayList->size){
        expandList(arrayList);
    }
    arrayList->ptrs[arrayList->length] = ptr;
    arrayList->length++;
}

void setListIndex(struct ArrayList* arrayList, int* ptr, int index){
    if (index < arrayList->length){
        arrayList->ptrs[index] = ptr;
    }
    else{
        reportBug("Index %i Out of range of list length %i!", index, arrayList->length);
    }
}

int* indexList(struct ArrayList* arrayList, int index){
    if (index < arrayList->length){
        return arrayList->ptrs[index];
    }
    else{
        reportBug("Index %i Out of range of list length %i!", index, arrayList->length);
        return NULL;
    }
}

//Clear all items in the lists and reset length and size.
void clearList(struct ArrayList* arrayList){
    free(arrayList->ptrs);
    arrayList->length = 0;
    arrayList->size = 1;
    arrayList->ptrs = malloc(sizeof (void*));
}

//free the list struct but not the objects in the list itself
void freeList(struct ArrayList* arrayList){
    free(arrayList->ptrs);
    free(arrayList);
}