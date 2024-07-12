//
// Created by Spencer on 5/6/2024.
//

#ifndef EDIFICE_GAMEDATA_H
#define EDIFICE_GAMEDATA_H
#include "Visuals/Screen.h"
#include "Visuals/Menu/Menu.h"
#include "Visuals/Menu/TextManager/TextManager.h"
#include "Debuging/DebugMenu/DebugMenu.h"

struct GameData{
    struct Screen* screen;
    struct CameraData* cameraData;
    struct World* world;
    struct Textures* textures;
    struct TextTextures* textTextures;
    struct Menu* menu;
    struct DebugMenu* debugMenu;
    struct PlayerData* playerData;
    struct TikManager* tikManager;
};

struct GameData* createGameData();

#endif //EDIFICE_GAMEDATA_H
