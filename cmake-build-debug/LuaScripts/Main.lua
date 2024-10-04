-- init.lua
-- Setup
package.path = package.path .. ";./LuaScripts/?.lua"
require("DroneLuaCommands.DroneCommands")
require("DroneLuaCommands.BlockData")
require("DroneMiner.BlockMiner")

print("Starting Lua");
local test = 0;


function ON_TICK()

    local droneCount = getDroneCount()
    
    for i = 0, droneCount - 1, 1
    do
        mineRocksAroundDrone(i, Block.Rock)
        local xMod = 1;
        local yMod = 0;
        local zMod = 0;

        if luaGetRelativeBlock(i, xMod, yMod, zMod) ~= 0
        then
            xMod = 0;
            yMod = 1;
            if luaGetRelativeBlock(i, xMod, yMod, zMod) ~= 0
            then
                xMod = 0;
                yMod = -1;
            end
        end
        
        luaMoveDrone(i, xMod, yMod, zMod)
    end
end