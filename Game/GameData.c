//
// Created by Spencer on 5/6/2024.
//

#include <malloc.h>
#include "GameData.h"
#include "Visuals/Screen.h"
#include "Visuals/Camera/CameraData.h"
#include "Visuals/Camera/Rendering/TextureManager/IsoTextureManager.h"
#include "World/World.h"
#include "Debuging/Test_Main.h"
#include "PlayerData/PlayerData.h"
#include "InGameTime/TikManager.h"
#include "Sound/SoundManager.h"
#include "Visuals/Camera/Rendering/RayCasting/CastingThread/castingThread.h"


struct GameData* createGameData(){
    //Clear bug report file
    clearBugReports();

    reportBug("Building gameData \n");

    //Create gameData struct
    struct GameData* gameData = malloc(sizeof (struct GameData));
    if (gameData == NULL){
        return NULL;
    }

    //Create screen
    reportBug("Creating SDL Screen \n");
    gameData->screen = createScreen();

    //create textTextures
    reportBug("Creating textTextures\n");
    gameData->textTextures = createTextTextures(gameData->screen->renderer);

    //CreateDebugMenu
    reportBug("Creating DebugMenu\n");
    gameData->debugMenu = createDebugMenu();

    //create textures
    reportBug("Splicing textures \n");
    gameData->textures = createTextures(gameData->screen->renderer, 60);

    //Build the octree world
    reportBug("Building world\n");
    gameData->world = createWorld(12);

    //CreateMenuManager
    gameData->menuManger = createMenuManager();

    //Create camera Data
    reportBug("Creating cameraData \n");
    gameData->cameraData = createCameraData(gameData->screen->renderer, gameData->world->octree);

    //Create playerDaya
    reportBug("Creating playerData \n");
    gameData->playerData = createPlayerData();

    //CreateTikManager
    reportBug("Creating Tik Manager \n");
    gameData->tikManager = createTikManager();

    reportBug("Creating Sound Manager\n");
    gameData->soundManager = createSoundManager(12);


    //Create Sounds
    //reportBug("Creating Sounds \n");
    //gameData->sounds = createSounds();

    return gameData;
}