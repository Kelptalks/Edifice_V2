//
// Created by Spencer on 4/18/2024.
//



#include <stdbool.h>
#include "Blocks.h"
#include "../Sound/SoundManager.h"

bool isPlantable(enum Block block){
    if (block == GreenGrass){
        return true;
    }
    if (block == BlueGrass){
        return true;
    }
    return false;
}

bool isTransparent(enum Block block){
    if (block == 0){
        return true;
    }
    else{
        return false;
    }
}

bool isTranslucent(enum Block block) {
    switch (block) {
        case YellowFlowers :
        case WhiteFlowers :
        case Flour :
        case Mushroom :
        case Water :
        case Glass :
        case HalfBlockTest :
        case ConveyorBelt :
        case Bulb :
        case Rock :
        case Furnace :
            return true;
        default:
            return false; // Non-translucent blocks
    }
}

int getTotalBlockCount(){
    return 65;
}

SDL_Rect getBlockSpriteSheetSrcRect(enum Block block){
    int xSpriteSheetCor; int ySpriteSheetCor;
    getBlockSpriteSheetCords(block, &xSpriteSheetCor, &ySpriteSheetCor);
    SDL_Rect blockSrcRect = {xSpriteSheetCor, ySpriteSheetCor, 64, 64};
    return blockSrcRect;
};

char* getBlockName(enum Block block) {
    switch (block) {
        case Dirt:
            return "Dirt";
        case CrackedEarth:
            return "Cracked Earth";
        case Hive:
            return "Hive";
        case Cobble:
            return "Cobble";
        case Core:
            return "Core";
        case Sand:
            return "Sand";
        case Debug:
            return "Debug";
        case Granite:
            return "Granite";
        case Stone:
            return "Stone";
        case Magma:
            return "Magma";
        case GreenGrass:
            return "Green Grass";
        case BlueGrass:
            return "Blue Grass";
        case Leave:
            return "Leave";
        case PurpleWood:
            return "Purple Wood";
        case PurpleWoodPlanks:
            return "Purple Wood Planks";
        case BrownWood:
            return "Brown Wood";
        case BrownWoodPlanks:
            return "Brown Wood Planks";
        case Dandi:
            return "Dandi";
        case DandiStem:
            return "Dandi Stem";
        case MushroomStem:
            return "Mushroom Stem";
        case BlueMushroomBlock:
            return "Blue Mushroom Block";
        case PinkMushroomBlock:
            return "Pink Mushroom Block";
        case Fungi:
            return "Fungi";
        case Water:
            return "Water";
        case YellowFlowers:
            return "Yellow Flowers";
        case WhiteFlowers:
            return "White Flowers";
        case Mushroom:
            return "Mushroom";
        case Flour:
            return "Flour";
        case Glass:
            return "Glass";
        case Bulb:
            return "Bulb";
        case Rock:
            return "Rock";
        case Iron:
            return "Iron";
        case Copper:
            return "Copper";
        case MudBrick:
            return "Mud Brick";
        case ClayBrick:
            return "Clay Brick";
        case Coral:
            return "Coral";
        case StoneBrick:
            return "Stone Brick";
        case FloweringStoneBrick:
            return "Flowering Stone Brick";
        case LBM:
            return "LBM";
        case Factory:
            return "Factory";
        case Crate:
            return "Crate";
        case Metal:
            return "Metal";
        case ConveyorBelt:
            return "Conveyor Belt";
        case Furnace:
            return "Furnace";
        case WormBody:
            return "Worm Body";
        case WormEyesLevel:
            return "Worm Eyes Level";
        case WormEyesUp:
            return "Worm Eyes Up";
        case WormMouth:
            return "Worm Mouth";
        case GreyShader:
            return "Grey Shader";
        case RedShader:
            return "Red Shader";
        case WhiteShader:
            return "White Shader";
        case GreenShader:
            return "Green Shader";
        case HalfBlockTest:
            return "Half Block Test";
        case MaskingBlock:
            return "Masking Block";
        case ShadowMaskingBlock:
            return "Shadow Masking Block";
        default:
            return "unNamed";
    }
}

void getBlockSpriteSheetCords(enum Block block, int* x, int* y) {
    switch (block) {
        case Air:
            *x = 256;
            *y = 0;
            break;
        case Dirt:
            *x = 0;
            *y = 0;
            break;
        case Stone:
            *x = 64;
            *y = 0;
            break;
        case PurpleWood:
            *x = 128;
            *y = 0;
            break;
        case BrownWood:
            *x = 128;
            *y = 512;
            break;
        case BrownWoodPlanks:
            *x = 64;
            *y = 512;
            break;
        case PurpleWoodPlanks:
            *x = 0;
            *y = 576;
        case Leave:
            *x = 192;
            *y = 0;
            break;
        case Dandi:
            *x = 0;
            *y = 64;
            break;
        case DandiStem:
            *x = 64;
            *y = 64;
            break;
        case Hive:
            *x = 128;
            *y = 64;
            break;
        case Cobble:
            *x = 192;
            *y = 64;
            break;
        case GreenGrass:
            *x = 0;
            *y = 128;
            break;
        case Magma:
            *x = 64;
            *y = 128;
            break;
        case Core:
            *x = 128;
            *y = 128;
            break;
        case LBM:
            *x = 192;
            *y = 128;
            break;
        case Factory:
            *x = 0;
            *y = 1024;
            break;
        case Crate:
            *x = 0;
            *y = 1088;
            break;
        case Furnace:
            *x = 0;
            *y = 512;
            break;
        case ConveyorBelt:
            *x = 256;
            *y = 1088;
            break;
        case Metal:
            *x = 0;
            *y = 192;
            break;
        case Granite:
            *x = 64;
            *y = 192;
            break;
        case Sand:
            *x = 128;
            *y = 192;
            break;
        case Copper:
            *x = 192;
            *y = 192;
            break;
        case Iron:
            *x = 128;
            *y = 448;
            break;
        case Fungi:
            *x = 0;
            *y = 256;
            break;
        case BlueGrass:
            *x = 64;
            *y = 256;
            break;
        case MushroomStem:
            *x = 128;
            *y = 256;
            break;
        case BlueMushroomBlock:
            *x = 192;
            *y = 448;
            break;
        case PinkMushroomBlock:
            *x = 192;
            *y = 256;
            break;
        case Debug:
            *x = 64;
            *y = 320;
            break;
        case Water:
            *x = 128;
            *y = 320;
            break;
        case Flour:
            *x = 192;
            *y = 960;
            break;
        case Bulb:
            *x = 256;
            *y = 960;
            break;
        case Rock:
            *x = 320;
            *y = 960;
            break;
        case WhiteFlowers:
            *x = 64;
            *y = 960;
            break;
        case YellowFlowers:
            *x = 0;
            *y = 960;
            break;
        case Mushroom:
            *x = 128;
            *y = 960;
            break;
        case CrackedEarth:
            *x = 0;
            *y = 320;
            break;
        case MaskingBlock:
            *x = 256;
            *y = 1152;
            break;
        case WormBody :
            *y = 640;
            *x = 0;
            break;
        case WormEyesLevel :
            *y = 640;
            *x = 64;
            break;
        case WormEyesUp :
            *y = 640;
            *x = 128;
            break;
        case WormMouth :
            *y = 640;
            *x = 192;
            break;
        case GreyShader:
            *x = 0;
            *y = 1152;
            break;
        case WhiteShader:
            *x = 64;
            *y = 1152;
            break;
        case GreenShader:
            *x = 128;
            *y = 1152;
            break;
        case RedShader:
            *x = 192;
            *y = 1152;
            break;
        case ShadowMaskingBlock:
            *x = 320;
            *y = 1152;
            break;
        case Glass :
            *x = 192;
            *y = 320;
            break;
        case MudBrick :
            *x = 0;
            *y = 384;
            break;
        case ClayBrick :
            *x = 0;
            *y = 448;
            break;
        case Coral:
            *x = 64;
            *y = 384;
            break;
        case StoneBrick:
            *x = 128;
            *y = 384;
            break;
        case FloweringStoneBrick:
            *x = 192;
            *y = 384;
            break;
        case HalfBlockTest:
            *x = 0;
            *y = 576;
            break;
        case DroneRightForward:
            *x = 0;
            *y = 704;
            break;
        case DroneLeftForward:
            *x = 64;
            *y = 704;
            break;
        case DroneRightBack:
            *x = 128;
            *y = 704;
            break;
        case DroneLeftBack:
            *x = 192;
            *y = 704;
            break;
        default:
            *x = 64;
            *y = 320;
            break;
    }
}

int getBlockRemoveSound(enum Block block){
    switch (block) {
        //Plant Sound
        case GreenGrass:
        case BlueGrass:
        case DandiStem:
        case Dandi:
        case Mushroom:
        case Flour:
        case Fungi:
        case WhiteFlowers:
        case YellowFlowers:
        case MushroomStem:
        case Bulb :
        case BlueMushroomBlock:
            return BlockRemoveSoundPlant;
        case LBM :
        case Factory :
        case Crate :
        case ConveyorBelt :
        case Metal :
            return BlockRemoveSoundFactory;
    }
    return BlockRemoveSoundDefault;
}

int getBlockPlaceSound(enum Block block){
    switch (block) {
        //Plant Sound
        case DandiStem:
        case Dandi:
        case Mushroom:
        case Flour:
        case Fungi:
        case WhiteFlowers:
        case YellowFlowers:
        case MushroomStem:
        case Bulb :
        case BlueMushroomBlock:
            return BlockPlaceSoundPlant;
        case LBM :
        case Factory :
        case Crate :
        case ConveyorBelt :
        case Metal :
            return BlockPlaceSoundFactory;
        case GreenGrass :
        case BlueGrass :
        case Dirt :
        case CrackedEarth :
            return BlockPlaceSoundDirt;
        case ClayBrick :
        case StoneBrick :
        case MudBrick :
            return BlockPlaceSoundBrick;
    }
    return BlockPlaceSoundDefault;
}