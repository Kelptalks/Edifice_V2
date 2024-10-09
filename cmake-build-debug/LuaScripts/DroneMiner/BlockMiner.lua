package.path = package.path .. ";./LuaScripts/?.lua"
require("DroneLuaCommands.DroneCommands")
require("DroneLuaCommands.BlockData")
require("DroneNavigator.DroneNavigator")

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

function HarvestRocksAndPlantMatter(droneId)
    mineBlockAroundDrone(droneId, Block.Rock)
    mineBlockAroundDrone(droneId, Block.Flour)
    mineBlockAroundDrone(droneId, Block.WhiteFlowers)
    mineBlockAroundDrone(droneId, Block.YellowFlowers)
    mineBlockAroundDrone(droneId, Block.Mushroom)

    local x, y, z = getCordsOfBlock(i, Block.Rock);
    if x == nil and y == nil and z == nil then
        BasicWalkInDirection(droneId, 100, 100, 0)
    end

    BasicWalkInDirection(droneId or 0, x or 0, y or 0, z or 0)
end