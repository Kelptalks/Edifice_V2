//
// Created by Spencer on 8/7/2024.
//

#include "../../../../../GameData.h"
#include "../../ UIManager/UIRenderer/UIRenderer.h"
#include "../../ UIManager/UIManger.h"

void renderMainMenu(struct GameData* gameData){

    struct ScrollWheel* scrollWheel = createScrollWheel(50, 50, 400, 10, 20);
    renderScrollWheel(scrollWheel, gameData);
    free(scrollWheel);
}