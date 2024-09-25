//
// Created by Spencer on 6/30/2024.
//

#ifndef EDIFICE_PLAYERDATA_H
#define EDIFICE_PLAYERDATA_H

#include "../Blocks/Blocks.h"
#include "../InGameTime/TikEvent/EntityManager/EntityManager.h"
#include "../GameData.h"
#include "Invintory/Hotbar/Hotbar.h"
#include "Invintory/BlockMenu/BlockMenu.h"

struct PlayerData{
    enum Block block;
    struct HotBar* hotBar;
    struct BlockSelectionMenu* blockSelectionMenu;


    int lastMouseXCor;
    int lastMouseYCor;

    enum EntityDirection playerDirection;

    int walkingFrame;
    int walkingTexture;

    float worldX;
    float worldY;
    float worldZ;

    float sizeX;
    float sizeY;

    float velResistance;
    float sprintMod;
    float walkingSpeed;
    bool sprinting;
    float velX;
    float velY;

    float gravity;
    float velZ;
};

struct PlayerData* createPlayerData();

void tikPlayer(struct GameData* gameData);
#endif //EDIFICE_PLAYERDATA_H
