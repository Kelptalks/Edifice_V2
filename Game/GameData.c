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
    drawString(gameData, "Creating Debug Menu...", 22, 0, 0, 50);
    updateScreen(gameData->screen);
    reportBug("Creating DebugMenu\n");
    gameData->debugMenu = createDebugMenu();


    //create textures
    drawString(gameData, "Creating textures...", 20, 0, 0, 50);
    updateScreen(gameData->screen);

    reportBug("Splicing textures \n");
    gameData->textures = createTextures(gameData->screen->renderer, 70);


    //Build the octree world
    drawString(gameData, "Building world...", 17, 0, 0, 50);
    updateScreen(gameData->screen);

    reportBug("Building world\n");
    gameData->world = createWorld(12);


    //CreateMenuManager
    drawString(gameData, "Creating Menu Manager...", 24, 0, 0, 50);
    updateScreen(gameData->screen);

    reportBug("Creating Menu Manager\n");
    gameData->menuManger = createMenuManager();


    //Create camera Data
    drawString(gameData, "Creating Camera...", 18, 0, 0, 50);
    updateScreen(gameData->screen);

    reportBug("Creating cameraData \n");
    gameData->cameraData = createCameraData(gameData->screen->renderer, gameData->world);

    //Create playerDaya
    drawString(gameData, "Creating PlayerData...", 22, 0, 0, 50);
    updateScreen(gameData->screen);

    reportBug("Creating PlayerData\n");
    gameData->playerData = createPlayerData();


    //CreateTikManager
    drawString(gameData, "Creating Tick Manager...", 26, 0, 0, 50);
    updateScreen(gameData->screen);

    reportBug("Creating Tik Manager \n");
    gameData->tikManager = createTikManager();

    //Create sound manager
    drawString(gameData, "Creating Sound Manager...", 25, 0, 0, 50);
    updateScreen(gameData->screen);

    reportBug("Creating Sound Manager\n");
    gameData->soundManager = createSoundManager(12);


    //Create Sounds
    //reportBug("Creating Sounds \n");
    //gameData->sounds = createSounds();

    return gameData;
}