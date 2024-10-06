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
        mineBlockAroundDrone(i, Block.Rock)
        mineBlockAroundDrone(i, Block.Flour)
        mineBlockAroundDrone(i, Block.WhiteFlowers)
        mineBlockAroundDrone(i, Block.YellowFlowers)
        mineBlockAroundDrone(i, Block.Mushroom)

        navigateToCords(i, 0, 0, 0);
    end
end