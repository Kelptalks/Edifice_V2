//
// Created by Spencer on 5/6/2024.
//

#include <malloc.h>
#include "GameData.h"
#include "Visuals/Screen.h"
#include "Visuals/Camera/CameraData.h"
#include "Visuals/Camera/Rendering/TextureManager/IsoTextureManager.h"
#include "World/World.h"z
#include "Debuging/Test_Main.h"

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
    gameData->textures = createTextures(gameData->screen->renderer, 40);

    //Build the octree world
    reportBug("Building world\n");
    gameData->world = createWorld(12);

    //Create menu struct
    reportBug("Creating Main menu\n");
    gameData->menu = createMenu();

    //Create camera Data
    reportBug("Creating cameraData \n");
    gameData->cameraData = createCameraData();
    gameData->cameraData->octree = gameData->world->octree;



    return gameData;
}