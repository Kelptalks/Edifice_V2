//
// Created by Spencer on 10/3/2024.
//

#include "SDL.h"
#include "DroneToolManager.h"
#include "../../../Blocks/Blocks.h"
#include "../../../Debuging/Test_Main.h"

struct DroneItemRecipe* createItemRecipe(int totalItemTypes) {
    struct DroneItemRecipe* itemRecipe = malloc(sizeof(struct DroneItemRecipe));

    itemRecipe->totalItemTypes = totalItemTypes;
    itemRecipe->itemsNeeded = calloc(totalItemTypes, sizeof(enum DroneItem*));
    for (int i = 0; i < itemRecipe->totalItemTypes; i++) {
        itemRecipe->itemsNeeded[i] = ItemNull;
    }
    itemRecipe->itemCounts = calloc(totalItemTypes, sizeof(int));

    return itemRecipe;
}

void addItemToRecipe(struct DroneItemRecipe* itemRecipe, enum DroneItem item, int itemCount) {
    for (int x = 0; x < itemRecipe->totalItemTypes; x++) {
        if (itemRecipe->itemCounts[x] == 0) {
            itemRecipe->itemsNeeded[x] = item;
            itemRecipe->itemCounts[x] = itemCount;
            return;
        }
    }
    reportBug("Failed to add item to recipe\n");
}


int getTotalToolCount(){
    return 14;
}

SDL_Rect getToolSrcRect(enum DroneTool droneTool){
    SDL_Rect srcRect = {droneTool * 16, 1232, 16, 16};
    return srcRect;
}

int addToolToDone(struct Drone* drone, enum DroneTool tool){
    for (int i = 0; i < 3; i++){
        if (drone->tools[i] == ToolNull){
            drone->tools[i] = tool;
            return 1;
        }
    }
    return -1;
}

void removeToolToDone(struct Drone* drone, int index){
    drone->tools[index] = ToolNull;
}



int getBlockMineTime(struct DroneToolData* droneToolData, struct Drone* drone, enum Block block){
    int mineMod = 1;

    if (block == BrownWood || block == PurpleWood || block == BrownWoodPlanks || block == PurpleWoodPlanks) {
        for (int i = 0; i < 3; i++) {
            enum DroneTool droneTool = drone->tools[i];
            if (droneTool == ToolStoneSaw || droneTool == ToolIronSaw || droneTool == ToolTitaniumSaw) {
                mineMod += droneToolData->toolMineTimeMods[drone->tools[i]];
            }
        }
    }
    else {
        for (int i = 0; i < 3; i++){
            enum DroneTool droneTool = drone->tools[i];
            if (droneTool == ToolStoneDrill || droneTool == ToolIronDrill || droneTool == ToolTitaniumDrill) {
                mineMod += droneToolData->toolMineTimeMods[drone->tools[i]];
            }
        }
    }

    return droneToolData->blockMineTimes[block] / mineMod;
}

struct DroneToolData* createDroneToolData(){
    struct DroneToolData* droneToolData = malloc((sizeof (struct DroneToolData)));
    //Set up block mine times
    droneToolData->blockMineTimes = calloc(getTotalBlockCount(), sizeof (int));

    //Set Up drone mine times
    droneToolData->blockMineTimes[Dirt] = 20;
    droneToolData->blockMineTimes[CrackedEarth] = 30;
    droneToolData->blockMineTimes[Hive] = 30;
    droneToolData->blockMineTimes[Cobble] = 100;
    droneToolData->blockMineTimes[Core] = 9999;
    droneToolData->blockMineTimes[Sand] = 30;
    droneToolData->blockMineTimes[Granite] = 200;
    droneToolData->blockMineTimes[Stone] = 100;
    droneToolData->blockMineTimes[Magma] = 500;
    droneToolData->blockMineTimes[GreenGrass] = 30;
    droneToolData->blockMineTimes[BlueGrass] = 30;
    droneToolData->blockMineTimes[Leave] = 10;
    droneToolData->blockMineTimes[PurpleWood] = 500;
    droneToolData->blockMineTimes[BrownWood] = 50;
    droneToolData->blockMineTimes[PurpleWoodPlanks] = 500;
    droneToolData->blockMineTimes[BrownWoodPlanks] = 60;
    droneToolData->blockMineTimes[Dandi] = 10;
    droneToolData->blockMineTimes[DandiStem] = 20;
    droneToolData->blockMineTimes[MushroomStem] = 10;
    droneToolData->blockMineTimes[BlueMushroomBlock] = 10;
    droneToolData->blockMineTimes[PinkMushroomBlock] = 10;
    droneToolData->blockMineTimes[Fungi] = 10;
    droneToolData->blockMineTimes[Water] = 10;
    droneToolData->blockMineTimes[YellowFlowers] = 5;
    droneToolData->blockMineTimes[WhiteFlowers] = 5;
    droneToolData->blockMineTimes[Mushroom] = 5;
    droneToolData->blockMineTimes[Flour] = 5;
    droneToolData->blockMineTimes[Glass] = 20;
    droneToolData->blockMineTimes[Bulb] = 5;
    droneToolData->blockMineTimes[Rock] = 5;
    droneToolData->blockMineTimes[Iron] = 200;
    droneToolData->blockMineTimes[Copper] = 250;
    droneToolData->blockMineTimes[MudBrick] = 35;
    droneToolData->blockMineTimes[ClayBrick] = 75;
    droneToolData->blockMineTimes[Coral] = 20;
    droneToolData->blockMineTimes[StoneBrick] = 250;
    droneToolData->blockMineTimes[FloweringStoneBrick] = 250;
    droneToolData->blockMineTimes[LBM] = 20;
    droneToolData->blockMineTimes[Factory] = 20;
    droneToolData->blockMineTimes[Crate] = 20;
    droneToolData->blockMineTimes[Metal] = 1000;
    droneToolData->blockMineTimes[ConveyorBelt] = 100;
    droneToolData->blockMineTimes[Furnace] = 100;


    //Set up block Tool mine mods
    droneToolData->toolMineTimeMods = calloc(getTotalToolCount(), sizeof (int));
    droneToolData->toolMineTimeMods[ToolNull] = 0;
    droneToolData->toolMineTimeMods[ToolStoneDrill] = 4;
    droneToolData->toolMineTimeMods[ToolStoneSaw] = 4;
    droneToolData->toolMineTimeMods[ToolIronDrill] = 6;
    droneToolData->toolMineTimeMods[ToolIronSaw] = 6;
    droneToolData->toolMineTimeMods[ToolIronBattery] = 0;
    droneToolData->toolMineTimeMods[ToolIronReceptacle] = 0;
    droneToolData->toolMineTimeMods[ToolIronCamera] = 0;
    droneToolData->toolMineTimeMods[ToolTitaniumDrill] = 8;
    droneToolData->toolMineTimeMods[ToolTitaniumSaw] = 8;
    droneToolData->toolMineTimeMods[ToolTitaniumBattery] = 0;
    droneToolData->toolMineTimeMods[ToolTitaniumReceptacle] = 0;
    droneToolData->toolMineTimeMods[ToolTitaniumCamera] = 0;
    droneToolData->toolMineTimeMods[ToolExplosiveCamera] = 0;



    //Set up block placement Costs
    droneToolData->blockPlacementCostQuantities = calloc(getTotalBlockCount(), sizeof (int));
    droneToolData->blockPlacementCostItems = calloc(getTotalBlockCount(), sizeof (enum DroneItem));

    droneToolData->blockPlacementCostQuantities[Dirt] = 1;
    droneToolData->blockPlacementCostItems[Dirt] = ItemDirt;

    droneToolData->blockPlacementCostQuantities[CrackedEarth] = 1;
    droneToolData->blockPlacementCostItems[CrackedEarth] = ItemDirt;

    droneToolData->blockPlacementCostQuantities[Hive] = 1;
    droneToolData->blockPlacementCostItems[Hive] = ItemPlantMatter;

    droneToolData->blockPlacementCostQuantities[Cobble] = 1;
    droneToolData->blockPlacementCostItems[Cobble] = ItemStone;

    droneToolData->blockPlacementCostQuantities[Core] = 9999;
    droneToolData->blockPlacementCostItems[Core] = ItemTitaniumBar;

    droneToolData->blockPlacementCostQuantities[Sand] = 1;
    droneToolData->blockPlacementCostItems[Sand] = ItemSand;

    droneToolData->blockPlacementCostQuantities[Granite] = 5;
    droneToolData->blockPlacementCostItems[Granite] = ItemStone;

    droneToolData->blockPlacementCostQuantities[Stone] = 2;
    droneToolData->blockPlacementCostItems[Stone] = ItemStone;

    droneToolData->blockPlacementCostQuantities[Magma] = 10;
    droneToolData->blockPlacementCostItems[Magma] = ItemStone;

    droneToolData->blockPlacementCostQuantities[GreenGrass] = 2;
    droneToolData->blockPlacementCostItems[GreenGrass] = ItemPlantMatter;

    droneToolData->blockPlacementCostQuantities[BlueGrass] = 5;
    droneToolData->blockPlacementCostItems[BlueGrass] = ItemPlantMatter;

    droneToolData->blockPlacementCostQuantities[Leave] = 1;
    droneToolData->blockPlacementCostItems[Leave] = ItemPlantMatter;

    droneToolData->blockPlacementCostQuantities[PurpleWood] = 1;
    droneToolData->blockPlacementCostItems[PurpleWood] = ItemLog;

    droneToolData->blockPlacementCostQuantities[BrownWood] = 1;
    droneToolData->blockPlacementCostItems[BrownWood] = ItemLog;

    droneToolData->blockPlacementCostQuantities[PurpleWoodPlanks] = 1;
    droneToolData->blockPlacementCostItems[PurpleWoodPlanks] = ItemLog;

    droneToolData->blockPlacementCostQuantities[BrownWoodPlanks] = 1;
    droneToolData->blockPlacementCostItems[BrownWoodPlanks] = ItemLog;

    droneToolData->blockPlacementCostQuantities[Dandi] = 2;
    droneToolData->blockPlacementCostItems[Dandi] = ItemPlantMatter;

    droneToolData->blockPlacementCostQuantities[DandiStem] = 1;
    droneToolData->blockPlacementCostItems[DandiStem] = ItemPlantMatter;

    droneToolData->blockPlacementCostQuantities[MushroomStem] = 1;
    droneToolData->blockPlacementCostItems[MushroomStem] = ItemPlantMatter;

    droneToolData->blockPlacementCostQuantities[BlueMushroomBlock] = 2;
    droneToolData->blockPlacementCostItems[BlueMushroomBlock] = ItemPlantMatter;

    droneToolData->blockPlacementCostQuantities[PinkMushroomBlock] = 2;
    droneToolData->blockPlacementCostItems[PinkMushroomBlock] = ItemPlantMatter;

    droneToolData->blockPlacementCostQuantities[Fungi] = 3;
    droneToolData->blockPlacementCostItems[Fungi] = ItemPlantMatter;

    droneToolData->blockPlacementCostQuantities[Water] = 999;
    droneToolData->blockPlacementCostItems[Water] = ItemPlantMatter;

    droneToolData->blockPlacementCostQuantities[YellowFlowers] = 1;
    droneToolData->blockPlacementCostItems[YellowFlowers] = ItemPlantMatter;

    droneToolData->blockPlacementCostQuantities[WhiteFlowers] = 1;
    droneToolData->blockPlacementCostItems[WhiteFlowers] = ItemPlantMatter;

    droneToolData->blockPlacementCostQuantities[Mushroom] = 1;
    droneToolData->blockPlacementCostItems[Mushroom] = ItemPlantMatter;

    droneToolData->blockPlacementCostQuantities[Flour] = 1;
    droneToolData->blockPlacementCostItems[Flour] = ItemPlantMatter;

    droneToolData->blockPlacementCostQuantities[Glass] = 2;
    droneToolData->blockPlacementCostItems[Glass] = ItemGlass;

    droneToolData->blockPlacementCostQuantities[Bulb] = 1;
    droneToolData->blockPlacementCostItems[Bulb] = ItemGlass;

    droneToolData->blockPlacementCostQuantities[Rock] = 1;
    droneToolData->blockPlacementCostItems[Rock] = ItemStone;

    droneToolData->blockPlacementCostQuantities[Iron] = 1;
    droneToolData->blockPlacementCostItems[Iron] = ItemIronOar;

    droneToolData->blockPlacementCostQuantities[Copper] = 1;
    droneToolData->blockPlacementCostItems[Copper] = ItemCopperOar;

    droneToolData->blockPlacementCostQuantities[MudBrick] = 2;
    droneToolData->blockPlacementCostItems[MudBrick] = ItemDirt;

    droneToolData->blockPlacementCostQuantities[ClayBrick] = 2;
    droneToolData->blockPlacementCostItems[ClayBrick] = ItemBrick;

    droneToolData->blockPlacementCostQuantities[Coral] = 20;
    droneToolData->blockPlacementCostItems[Coral] = ItemPlantMatter;

    droneToolData->blockPlacementCostQuantities[StoneBrick] = 2;
    droneToolData->blockPlacementCostItems[StoneBrick] = ItemStoneBrick;

    droneToolData->blockPlacementCostQuantities[FloweringStoneBrick] = 3;
    droneToolData->blockPlacementCostItems[FloweringStoneBrick] = ItemStoneBrick;

    droneToolData->blockPlacementCostQuantities[LBM] = 50;
    droneToolData->blockPlacementCostItems[LBM] = ItemTitaniumBar;

    droneToolData->blockPlacementCostQuantities[Factory] = 20;
    droneToolData->blockPlacementCostItems[Factory] = ItemIronBar;

    droneToolData->blockPlacementCostQuantities[Crate] = 10;
    droneToolData->blockPlacementCostItems[Crate] = ItemIronBar;

    droneToolData->blockPlacementCostQuantities[Metal] = 5;
    droneToolData->blockPlacementCostItems[Metal] = ItemIronBar;

    droneToolData->blockPlacementCostQuantities[ConveyorBelt] = 100;
    droneToolData->blockPlacementCostItems[ConveyorBelt] = ItemIronBar;

    droneToolData->blockPlacementCostQuantities[Furnace] = 10;
    droneToolData->blockPlacementCostItems[Furnace] = ItemStoneBrick;

    droneToolData->blockPlacementCostQuantities[DroneLeftForward] = 3;
    droneToolData->blockPlacementCostItems[DroneLeftForward] = ItemDroneParts;


    //Item Crafting
    droneToolData->itemRecipes = malloc(sizeof(struct DroneItemRecipe*) * getTotalToolCount());

    droneToolData->itemRecipes[ToolNull] = createItemRecipe(1);

    droneToolData->itemRecipes[ToolStoneDrill] = createItemRecipe(1);
    addItemToRecipe(droneToolData->itemRecipes[ToolStoneDrill], ItemStone, 3);

    droneToolData->itemRecipes[ToolStoneSaw] = createItemRecipe(1);
    addItemToRecipe(droneToolData->itemRecipes[ToolStoneSaw], ItemStone, 3);

    droneToolData->itemRecipes[ToolIronDrill] = createItemRecipe(1);
    addItemToRecipe(droneToolData->itemRecipes[ToolIronDrill], ItemIronBar, 3);

    droneToolData->itemRecipes[ToolIronSaw] = createItemRecipe(1);
    addItemToRecipe(droneToolData->itemRecipes[ToolIronSaw], ItemIronBar, 3);

    droneToolData->itemRecipes[ToolIronBattery] = createItemRecipe(1);

    droneToolData->itemRecipes[ToolIronReceptacle] = createItemRecipe(1);

    droneToolData->itemRecipes[ToolIronCamera] = createItemRecipe(1);

    droneToolData->itemRecipes[ToolTitaniumDrill] = createItemRecipe(1);

    droneToolData->itemRecipes[ToolTitaniumSaw] = createItemRecipe(1);

    droneToolData->itemRecipes[ToolTitaniumBattery] = createItemRecipe(1);

    droneToolData->itemRecipes[ToolTitaniumReceptacle] = createItemRecipe(1);

    droneToolData->itemRecipes[ToolTitaniumCamera] = createItemRecipe(1);

    droneToolData->itemRecipes[ToolExplosiveCamera] = createItemRecipe(1);

    return droneToolData;
}