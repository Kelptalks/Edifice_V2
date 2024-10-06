package.path = package.path .. ";./LuaScripts/?.lua"
require("DroneLuaCommands.DroneCommands")
require("DroneLuaCommands.BlockData")

function mineBlockAroundDrone(droneId, block) 
    for z = -1, 1, 1 do
        for y = -1, 1, 1 do
            for x = -1, 1, 1 do
                if getDroneBlock(droneId, x, y, z) == (block) then
                    mineDroneBlock(droneId, x, y, z)
                end
            end
        end
    end
end