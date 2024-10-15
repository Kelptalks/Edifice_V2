//
// Created by Spencer on 10/2/2024.
//

#include "DroneInventoryManager.h"

SDL_Rect getSrcRectOfItemSprite(enum DroneItem item){
    SDL_Rect srcRect = {item * 16, 1216, 16, 16};
    return srcRect;
}

enum DroneItem getBlockTypeToItem(enum Block block){
    switch (block) {

        //Dirt
        case Dirt:
        case MudBrick:
        case BlueGrass:
        case GreenGrass:
        case CrackedEarth:
            return ItemDirt;


        //Stone
        case Stone:
        case Granite:
        case Cobble:
        case Rock:
            return ItemStone;
        case Sand:
            ItemSand;

        //Plant Matter
        case Leave:
        case Dandi:
        case DandiStem:
        case MushroomStem:
        case BlueMushroomBlock:
        case PinkMushroomBlock:
        case Fungi:
        case YellowFlowers:
        case WhiteFlowers:
        case Mushroom:
        case Flour:
            return ItemPlantMatter;

        //Log
        case PurpleWood:
        case PurpleWoodPlanks:
        case BrownWood:
        case BrownWoodPlanks:
        case Log:
            return ItemLog;

        //Glass
        case Glass:
            return ItemGlass;


        //IronOar
        case Iron:
            return ItemIronOar;

        //CopperOar
        case Copper:
            return ItemCopperOar;

        //Brick
        case ClayBrick:
            return ItemBrick;

        //Stone Brick
        case StoneBrick:
        case Furnace:
        case FloweringStoneBrick:
            return ItemStoneBrick;

        //IronBar
        case LBM:
        case Factory:
        case Crate:
        case Metal:
        case DroneLeftForward:
        case DroneRightForward:
        case DroneRightBack:
        case DroneLeftBack:
        case DroneDead:
            return ItemIronBar;

        default:
            return ItemNull;
    }
}

void addItemToInventory(struct Drone* drone, enum DroneItem item, int quantity){
    if (item == ItemNull) {
        return;
    }
    //Look for item to stack to
    for (int i = 0; i < 9; i++){
        if (drone->items[i] == item){
            drone->itemCounts[i] += quantity;
            return;
        }
    }


    //Then if no stack look to add item to first free slot
    for (int i = 0; i < 9; i++){
        if (drone->items[i] == ItemNull){
            drone->items[i] = item;
            drone->itemCounts[i]+=quantity;
            return;
        }
    }
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
}

int getItemCountInSlot(struct Drone* drone, int slot){
    if (slot < 9) {
        return drone->itemCounts[slot];
    }
}