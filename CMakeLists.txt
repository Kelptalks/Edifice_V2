cmake_minimum_required(VERSION 3.27)
project(edifice C)

#SDL2
set(SDL2_DIR "C:/SDL2-2.30.2/x86_64-w64-mingw32")
find_package(SDL2 REQUIRED HINTS ${SDL2_DIR})
include_directories(${SDL2_INCLUDE_DIRS})

set(CMAKE_C_STANDARD 11)

add_executable(edifice main.c
        Game/Visuals/Camera/CameraData.h
        Game/Visuals/Camera/CameraData.c
        Game/GameData.h
        Game/GameData.c
        Game/Visuals/Camera/Camera.c
        Game/Visuals/Camera/Camera.h
        Game/Visuals/Screen.h
        Game/Visuals/Screen.c
        Game/Visuals/Camera/IsoCordTool/IsoCordManager.c
        Game/Controls/Controls.c
        Game/Controls/Controls.h
        Game/Visuals/Camera/Rendering/TextureManager/IsoTextureManager.c
        Game/Debuging/Test_Main.c
        Game/World/Octree/KeyMod.c
        Game/World/World.c
        Game/World/TerrainGen/LairManager/LairManager.c
        "Game/World/TerrainGen/Perlin Noise/PerlinNoise.c"
        Game/World/TerrainGen/PlantManager/PlantManager.c
        Game/Blocks/Blocks.c
        ArrayList/arrayList.c
        Game/World/Octree/Octree.c
        Game/World/Octree/OctreeNode.c
        Game/World/TerrainGen/PlantManager/PlantManger.h
        Game/World/TerrainGen/TerrainGen.c
        Game/Visuals/Camera/Rendering/CastedBlockManager/CastedBlockManager.h
        Game/Visuals/Camera/Rendering/CastedBlockManager/CastedBlockManager.c
        Game/Visuals/Camera/Rendering/CastedBlockManager/TextureList/TextureList.h
        Game/Visuals/Camera/Rendering/CastedBlockManager/TextureList/TextureList.c
        Game/Visuals/Camera/Rendering/CastedBlockManager/TextureList/TextureList.c
        Game/Visuals/Camera/Rendering/RayCasting/RayCaster.c
        Game/Visuals/Camera/Rendering/RayCasting/RayCaster.h
        Game/Visuals/Camera/Rendering/RayCasting/RayCastingManager.h
        Game/Visuals/Camera/Rendering/RayCasting/RayCastingManager.c
        Game/Visuals/Camera/Rendering/RayCasting/CastingThread/castingThread.c
        Game/Visuals/Menu/Menu.h
        Game/Visuals/Menu/Menu.c
        Game/Visuals/Menu/TextManager/TextManager.c
        Game/Visuals/Menu/TextManager/TextManager.h
        Game/Visuals/Menu/Button/Button.h
        Game/Visuals/Menu/Button/Button.c
        Game/Visuals/Camera/Controls/CameraControls.h
        Game/Visuals/Camera/Controls/CameraControls.c
        Game/Debuging/DebugMenu/DebugMenu.h
        Game/Debuging/DebugMenu/DebugMenu.c
        Game/Visuals/InMenuWindow/InMenuWindow.h
        Game/Visuals/InMenuWindow/InMenuWindow.c
        Assets/AssetManager.c
        Assets/AssetManager.h
        Game/Visuals/Camera/ChunkMap/ChunkMap.h
        Game/Visuals/Camera/ChunkMap/ChunkMap.c
        Game/Visuals/Camera/ChunkMap/ChunkLinkList/ChunkLinkList.c
        Game/Visuals/Camera/ChunkMap/ChunkLinkList/ChunkLinkList.h
        Game/PlayerData/PlayerData.h
        Game/PlayerData/PlayerData.c
        "Game/World/World Saving/WorldFileManager.c"
        "Game/World/World Saving/WorldFileManager.h"
)

target_link_libraries(edifice ${SDL2_LIBRARIES})