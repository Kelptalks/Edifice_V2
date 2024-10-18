//
// Created by Spencer on 10/2/2024.
//

#include "DroneInventoryManager.h"

#include "../DroneData.h"
#include "../DroneItemManager/DroneItemManager.h"


void addItemToInventory(struct DroneData* droneData, struct Drone* drone, enum DroneItem item, int quantity){
    if (item == ItemNull) {
        return;
    }

    int maxStackSizeOfItem = getItemMaxStackSize(droneData->droneItemData, item);
    //Look for item to stack to
    for (int i = 0; i < 9; i++){

        // If there is a stack and it's not full
        if (drone->items[i] == item && drone->itemCounts[i] < maxStackSizeOfItem){
            //If the new stack will be larger call recursively to add the remainder
            int newStackSize = drone->itemCounts[i] + quantity;
            if (newStackSize > maxStackSizeOfItem){
                //Set the current stack to full
                drone->itemCounts[i] = maxStackSizeOfItem;

                //Call recursively to add the remainder.
                int stackOverFlow = newStackSize - maxStackSizeOfItem;
                addItemToInventory(droneData, drone, item, stackOverFlow);

                return;
            }
            //Add the item to the slot
            else {
                drone->itemCounts[i] += quantity;
                return;
            }
        }
    }

    //Then if no stack look to add item to first free slot
    for (int i = 0; i < 9; i++){
        if (drone->items[i] == ItemNull){
            //If the new stack will be larger call recursively to add the remainder
            int newStackSize = quantity;
            if (newStackSize > maxStackSizeOfItem){
                //Set the current stack to full
                drone->itemCounts[i] = maxStackSizeOfItem;

                //Call recursively to add the remainder.
                int stackOverFlow = newStackSize - maxStackSizeOfItem;
                addItemToInventory(droneData, drone, item, stackOverFlow);

                return;
            }
            //Add the item to the slot
            else {
                drone->items[i] = item;
                drone->itemCounts[i] += quantity;
                return;
            }
        }
    }
}

int getTotalItemCountInInventory(struct Drone* drone, enum DroneItem item) {
    int runningTotal = 0;
    for (int i = 0; i < 9; i++) {
       if (drone->items[i] == item) {
           runningTotal += drone->itemCounts[i];
       }
    }
    return runningTotal;
}

int removeItemFromInventory(struct Drone* drone, enum DroneItem item, int count) {
    //Loop through drone inventory and check for ingredient
    for (int i = 0; i < drone->inventorySize; i++) {
        if (drone->items[i] == item) {
            if (drone->itemCounts[i] >= count) {
                drone->itemCounts[i] -= count;
                if (drone->itemCounts[i] <= 0) {
                    drone->items[i] = ItemNull;
                }
                return 1;
            }

        }
    }
    return -1;
}

enum DroneItem getItemInSlot(struct Drone* drone, int slot){
    if (slot < 9) {
        return drone->items[slot];
    }
    return ItemNull;
}

int getItemCountInSlot(struct Drone* drone, int slot){
    if (slot < 9) {
        return drone->itemCounts[slot];
    }
}