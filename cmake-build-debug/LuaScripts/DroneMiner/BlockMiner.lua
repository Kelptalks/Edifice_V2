package.path = package.path .. ";./LuaScripts/?.lua"
require("DroneLuaCommands.DroneCommands")
require("DroneLuaCommands.BlockData")

function mineBlockAroundDrone(droneId, block) 
    for x = -1, 1, 1 do
        for y = -1, 1, 1 do
            if getDroneBlock(droneId, x, y, 0) == (block - 1) then
                mineDroneBlock(droneId, x, y, 0)
            end
        end
    end
end