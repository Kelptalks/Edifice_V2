cmake_minimum_required(VERSION 3.27)
project(edifice C)

set(CMAKE_C_STANDARD 11)

set(OpenCL_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/OCL_SDK_Light/include")
set(OpenCL_LIBRARY "${CMAKE_SOURCE_DIR}/OCL_SDK_Light/lib/x86_64/OpenCL.lib")
include_directories(${OpenCL_INCLUDE_DIR})
find_package(OpenCL REQUIRED)

#SDL2
set(SDL2_DIR "C:/SDL2-2.30.2/x86_64-w64-mingw32")
find_package(SDL2 REQUIRED HINTS ${SDL2_DIR})
include_directories(${SDL2_INCLUDE_DIRS})

# Lua include directory (headers)
set(LUA_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/Lua542/include")
include_directories(${LUA_INCLUDE_DIR})

# Lua library directory
set(LUA_LIBRARY_DIR "${PROJECT_SOURCE_DIR}/Lua542")
set(LUA_LIBRARIES "${LUA_LIBRARY_DIR}/lua54.lib")  # Use the import library (lua54.lib)

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
        Game/World/Octree/Tools/KeyMod.c
        Game/World/World.c
        Game/World/TerrainGen/LairManager/LairManager.c
        "Game/World/TerrainGen/Perlin Noise/PerlinNoise.c"
        Game/World/TerrainGen/PlantManager/PlantManager.c
        Game/Blocks/Blocks.c
        ArrayList/arrayList.c
        Game/World/Octree/Octree.c
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
        Game/Visuals/Menu/TextManager/TextManager.c
        Game/Visuals/Menu/TextManager/TextManager.h
        Game/Visuals/Camera/Controls/CameraControls.h
        Game/Visuals/Camera/Controls/CameraControls.c
        Game/Debuging/DebugMenu/DebugMenu.h
        Game/Debuging/DebugMenu/DebugMenu.c
        Assets/AssetManager.c
        Assets/AssetManager.h
        Game/Visuals/Camera/Rendering/CastedBlockManager/ChunkMap/ChunkMap.h
        Game/Visuals/Camera/Rendering/CastedBlockManager/ChunkMap/ChunkMap.c
        Game/PlayerData/PlayerData.h
        Game/PlayerData/PlayerData.c
        Game/InGameTime/TikManager.c
        Game/InGameTime/TikManager.h
        Game/Visuals/Camera/Rendering/CastedBlockManager/CastedBlockHighLighter/CastedBlockHighLighter.h
        Game/Visuals/Camera/Rendering/CastedBlockManager/CastedBlockHighLighter/CastedBlockHighLighter.c
        Game/InGameTime/TikEvent/TerpManager/TerpManager.c
        Game/InGameTime/TikEvent/TerpManager/TerpManager.h
        Game/World/Octree/Tools/AdvancedKeyMod.c
        Game/World/Octree/Tools/AdvancedKeyMod.h
        Game/Sound/SoundManager.c
        Game/Sound/SoundManager.h
        "Game/Visuals/Menu/MenuManager/ UIManager/UIManger.h"
        "Game/Visuals/Menu/MenuManager/ UIManager/UIManger.c"
        Game/Visuals/Menu/MenuManager/MenuManger.c
        Game/Visuals/Menu/MenuManager/MenuManger.h
        Game/Visuals/Menu/MenuManager/Menus/MainMenu/MainMenu.c
        Game/Visuals/Menu/MenuManager/Menus/MainMenu/MainMenu.h
        "Game/Visuals/Menu/MenuManager/ UIManager/UIRenderer/UIRenderer.c"
        "Game/Visuals/Menu/MenuManager/ UIManager/UIRenderer/UIRenderer.h"
        Game/Visuals/Menu/MenuManager/Menus/SettingsMenu/SettingsMenu.c
        Game/Visuals/Menu/MenuManager/Menus/SettingsMenu/SettingsMenu.h
        Game/World/WorldChunk/WorldChunk.c
        Game/World/WorldChunk/WorldChunk.h
        Game/World/WorldChunkHashMap/WorldChunkHashMap.c
        Game/World/WorldChunkHashMap/WorldChunkHashMap.h
        Game/InGameTime/TikEvent/EntityManager/Puff/PuffLogic.c
        Game/InGameTime/TikEvent/EntityManager/Puff/PuffLogic.h
        Game/Visuals/Camera/Rendering/TextureManager/EntityTextures.h
        Game/Visuals/Camera/Rendering/TextureManager/EntityTextures.c
        Game/InGameTime/TikEvent/EntityManager/EntityManager.c
        Game/InGameTime/TikEvent/EntityManager/EntityManager.h
        Game/Visuals/Camera/Rendering/EntityRendering/EntityRendering.c
        Game/Visuals/Camera/Rendering/EntityRendering/EntityRendering.h
        Game/Visuals/Camera/Rendering/CastedBlockRendering/CastedBlockRendering.h
        Game/Visuals/Camera/Rendering/CastedBlockRendering/CastedBlockRendering.c
        "Game/World/TerrainGen/Perlin Noise/PerlinGenerator.c"
        "Game/World/TerrainGen/Perlin Noise/PerlinGenerator.h"
        Game/Visuals/Menu/OnScreenUI/OnScreenUI.h
        Game/Visuals/Menu/OnScreenUI/OnScreenUI.c
        Game/Debuging/DebugMenu/FrameRenderingData/FrameRenderingData.h
        Game/Debuging/DebugMenu/FrameRenderingData/FrameRenderingData.c
        Game/PlayerData/Invintory/Hotbar/Hotbar.c
        Game/PlayerData/Invintory/Hotbar/Hotbar.h
        Game/PlayerData/Invintory/BlockMenu/BlockMenu.c
        Game/PlayerData/Invintory/BlockMenu/BlockMenu.h
        "Game/World/World Saving/WorldFileManager.c"
        Game/Debuging/DebugMenu/TikData/TickData.c
        Game/Debuging/DebugMenu/TikData/TickData.h
        Game/Visuals/Menu/MenuManager/Menus/WorldSelectMenu/WorldSelectMenu.c
        Game/Visuals/Menu/MenuManager/Menus/WorldSelectMenu/WorldSelectMenu.h
        Game/Visuals/Menu/MenuManager/Menus/WorldCreateMenu/WorldCreateMenu.c
        Game/Visuals/Menu/MenuManager/Menus/WorldCreateMenu/WorldCreateMenu.h
        Game/InGameTime/Drone/Drone.c
        Game/InGameTime/Drone/Drone.h
        Game/InGameTime/Drone/DroneLuaCommands/DroneLuaCommands.c
        Game/InGameTime/Drone/DroneLuaCommands/DroneLuaCommands.h
        "Game/World/World Saving/ChunkFileManager/ChunkFileManager.c"
        "Game/World/World Saving/ChunkFileManager/ChunkFileManager.h"
        Game/Visuals/Menu/DroneOnScreenUI/DroneOnScreenUI.c
        Game/Visuals/Menu/DroneOnScreenUI/DroneOnScreenUI.h
        Game/InGameTime/Drone/DroneInventoryManager/DroneInventoryManager.c
        Game/InGameTime/Drone/DroneInventoryManager/DroneInventoryManager.h
        Game/InGameTime/Drone/DroneToolManager/DroneToolManager.c
        Game/InGameTime/Drone/DroneToolManager/DroneToolManager.h
        Game/Visuals/Menu/DroneOnScreenUI/DronePopOutWindow/DronePopOutWindow.c
        Game/Visuals/Menu/DroneOnScreenUI/DronePopOutWindow/DronePopOutWindow.h
        Game/InGameTime/Drone/DroneData.c
        Game/InGameTime/Drone/DroneData.h
        Game/World/TerrainGen/StoneManager/StoneManager.c
        Game/World/TerrainGen/StoneManager/StoneManager.h
        Game/InGameTime/Furnace/FurnaceData.c
        Game/InGameTime/Furnace/FurnaceData.h
        Game/InGameTime/Furnace/furnace.c
        Game/InGameTime/Furnace/furnace.h
        Game/World/WorldChunk/WorldChunkEntityHashMap/WorldChunkEntityHashMap.c
        Game/World/WorldChunk/WorldChunkEntityHashMap/WorldChunkEntityHashMap.h
        Game/InGameTime/Drone/DroneLuaCommands/DroneFurnaceLuaCommands/DroneFurnaceLuaCommands.c
        Game/InGameTime/Drone/DroneLuaCommands/DroneFurnaceLuaCommands/DroneFurnaceLuaCommands.h
        Game/InGameTime/Drone/DroneItemManager/DroneItemManager.c
        Game/InGameTime/Drone/DroneItemManager/DroneItemManager.h
        Game/InGameTime/Drone/DroneBlockProperties/DroneBlockProperties.c
        Game/InGameTime/Drone/DroneBlockProperties/DroneBlockProperties.h
        Game/InGameTime/Drone/DroneCraftingManager/DroneCraftingManager.c
        Game/InGameTime/Drone/DroneCraftingManager/DroneCraftingManager.h
        Game/Debuging/DebugMenu/Consol/DebugConsole.c
        Game/Debuging/DebugMenu/Consol/DebugConsole.h
        Game/Visuals/Menu/DroneOnScreenUI/GameSpeedControls/GameSpeedControls.c
        Game/Visuals/Menu/DroneOnScreenUI/GameSpeedControls/GameSpeedControls.h
        Game/Visuals/Consol/Consol.c
        Game/Visuals/Consol/Consol.h
)

target_link_libraries(edifice  ${LUA_LIBRARIES}  ${SDL2_LIBRARIES} ${OpenCL_LIBRARY})

set(CMAKE_VERBOSE_MAKEFILE ON)