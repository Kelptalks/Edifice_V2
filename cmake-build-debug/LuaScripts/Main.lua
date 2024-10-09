-- init.lua
-- Setup
package.path = package.path .. ";./LuaScripts/?.lua"
require("DroneLuaCommands.DroneCommands")
require("DroneLuaCommands.BlockData")
require("DroneMiner.BlockMiner")
require("DroneNavigator.DroneNavigator")

print("Starting Lua");
local test = 0;

function ON_TICK()

    local droneCount = getDroneCount()
    
    for i = 0, droneCount - 1, 1
    do
        navigateToCords(i, 0, 0, 100)
    end
end