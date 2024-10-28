//
// Created by Spencer on 10/18/2024.
//

#include "DroneCraftingManager.h"

#include <stdlib.h>



struct DroneItemRecipe* setUpItemRecipe (struct DroneCraftingData* droneCraftingData, enum DroneItem item, int uniqueItems, int amountPerCraft) {
    struct DroneItemRecipe* recipe = &droneCraftingData->droneItemRecipes[item];
    recipe->items = malloc(sizeof(enum DroneItem) * uniqueItems);
    recipe->itemQuantitys = malloc(sizeof(int) * uniqueItems);
    recipe->uniqueItems = uniqueItems;
    recipe->amountPerCraft = amountPerCraft;
    return recipe;
}

void setItemRecipeIngredient(struct DroneItemRecipe* recipe, int ingredientIndex, enum DroneItem itemType, int quantity) {
    if (recipe->uniqueItems > ingredientIndex) {
        recipe->items[ingredientIndex] = itemType;
        recipe->itemQuantitys[ingredientIndex] = quantity;
    }
    else {
        reportBug("Error out of recipe range | Item (%i), IngredientIndex (%i), recipeUniqueItems(%i)\n", itemType, ingredientIndex, recipe->uniqueItems);
    }
}

void setUpItemRecipes(struct DroneCraftingData* droneCraftingData) {

    struct DroneItemRecipe* currentRecipe = setUpItemRecipe(droneCraftingData, ItemNull, 1, 0);

    currentRecipe = setUpItemRecipe(droneCraftingData, ToolStoneDrill, 1, 1);
    setItemRecipeIngredient(currentRecipe, 0, ItemStone, 2);

    //Tools
    currentRecipe = setUpItemRecipe(droneCraftingData, ToolStoneSaw, 1, 1);
    setItemRecipeIngredient(currentRecipe, 0, ItemStone, 2);

    currentRecipe = setUpItemRecipe(droneCraftingData, ToolIronDrill, 1, 1);
    setItemRecipeIngredient(currentRecipe, 0, ItemIronBar, 2);

    currentRecipe = setUpItemRecipe(droneCraftingData, ToolIronSaw, 1, 1);
    setItemRecipeIngredient(currentRecipe, 0, ItemIronBar, 2);

    currentRecipe = setUpItemRecipe(droneCraftingData, ToolIronBattery, 2, 1);
    setItemRecipeIngredient(currentRecipe, 0, ItemIronBar, 2);
    setItemRecipeIngredient(currentRecipe, 1, ItemCopperBar, 2);

    currentRecipe = setUpItemRecipe(droneCraftingData, ToolIronReceptacle, 1, 1);
    setItemRecipeIngredient(currentRecipe, 0, ItemIronBar, 4);

    currentRecipe = setUpItemRecipe(droneCraftingData, ToolIronCamera, 2, 1);
    setItemRecipeIngredient(currentRecipe, 0, ItemCopperBar, 2);
    setItemRecipeIngredient(currentRecipe, 1, ItemGlass, 1);

    currentRecipe = setUpItemRecipe(droneCraftingData, ToolTitaniumDrill, 1, 1);
    setItemRecipeIngredient(currentRecipe, 0, ItemTitaniumBar, 2);

    currentRecipe = setUpItemRecipe(droneCraftingData, ToolTitaniumSaw, 1, 1);
    setItemRecipeIngredient(currentRecipe, 0, ItemTitaniumBar, 2);

    currentRecipe = setUpItemRecipe(droneCraftingData, ToolTitaniumBattery, 3, 1);
    setItemRecipeIngredient(currentRecipe, 0, ItemTitaniumBar, 2);
    setItemRecipeIngredient(currentRecipe, 1, ItemCopperBar, 2);
    setItemRecipeIngredient(currentRecipe, 2, ItemGoldBar, 1);


    currentRecipe = setUpItemRecipe(droneCraftingData, ToolTitaniumReceptacle, 1, 1);
    setItemRecipeIngredient(currentRecipe, 0, ItemTitaniumBar, 4);


    currentRecipe = setUpItemRecipe(droneCraftingData, ToolTitaniumCamera, 2, 1);
    setItemRecipeIngredient(currentRecipe, 0, ItemTitaniumBar, 4);
    setItemRecipeIngredient(currentRecipe, 1, ItemPurpleLens, 1);


    currentRecipe = setUpItemRecipe(droneCraftingData, ToolExplosive, 2, 1);
    setItemRecipeIngredient(currentRecipe, 0, ItemSulfur, 2);
    setItemRecipeIngredient(currentRecipe, 1, ItemCharcoal, 3);

    //Items
    currentRecipe = setUpItemRecipe(droneCraftingData, ItemStoneBrick, 1, 2);
    setItemRecipeIngredient(currentRecipe, 0, ItemStone, 4);

    currentRecipe = setUpItemRecipe(droneCraftingData, ItemBrick, 1, 2);
    setItemRecipeIngredient(currentRecipe, 0, ItemDirt, 4);

    currentRecipe = setUpItemRecipe(droneCraftingData, ItemScaffolding, 2, 8);
    setItemRecipeIngredient(currentRecipe, 0, ItemLog, 1);
    setItemRecipeIngredient(currentRecipe, 1, ItemPlantMatter, 1);

    currentRecipe = setUpItemRecipe(droneCraftingData, ItemDroneParts, 1, 1);
    setItemRecipeIngredient(currentRecipe, 0, ItemDroneParts, 1);

}

struct DroneCraftingData* createDroneCraftingData() {
    struct DroneCraftingData* droneCraftingData = malloc(sizeof(struct DroneCraftingData));
    if (droneCraftingData == NULL) {
        reportBug("Failed to malloc drone crafting data\n");
        return NULL;
    }

    droneCraftingData->droneItemRecipes = malloc(getTotalItemCount() * sizeof(struct DroneItemRecipe));
    if (droneCraftingData->droneItemRecipes == NULL) {
        reportBug("Failed to malloc drone item recipie array\n");
    }

    setUpItemRecipes(droneCraftingData);

    return droneCraftingData;
}


int droneAttemptCraftItem(struct DroneData* droneData, struct Drone* drone, enum DroneItem itemToCraft) {

    struct DroneItemRecipe recipe = droneData->droneCraftingData->droneItemRecipes[itemToCraft];

    //Check if can afford recipe
    bool hasEnoughItemsToCraft = true;
    for (int i = 0; i < recipe.uniqueItems; i++) {
        int totalOfItemsOfCurrentTypeInInventory = getTotalItemCountInInventory(drone, recipe.items[i]);
        //If lacking current ingredient
        if (totalOfItemsOfCurrentTypeInInventory < recipe.itemQuantitys[i]) {
            hasEnoughItemsToCraft = false;
            break;
        }
    }

    if (hasEnoughItemsToCraft) {
        for (int i = 0; i < recipe.uniqueItems; i++) {
            int num = removeItemFromInventory(drone, recipe.items[i], recipe.itemQuantitys[i]);
        }
        addItemToInventory(droneData, drone, itemToCraft, recipe.amountPerCraft);
        return 1;
    }
    else {
        return -1;
    }
}
