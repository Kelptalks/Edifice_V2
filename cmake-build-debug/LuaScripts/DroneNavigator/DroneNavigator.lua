package.path = package.path .. ";./LuaScripts/?.lua"
require("DroneLuaCommands.DroneCommands")
require("DroneLuaCommands.BlockData")

function getCordsOfBlock(droneID, block)
    local viewRange = getDroneViewRange();
    local worldX, worldY, worldZ = getDroneCords(droneID)

    for z = -viewRange, viewRange, 1 do
        for y = -viewRange, viewRange, 1 do
            for x = -viewRange, viewRange, 1 do
                
                if getDroneBlock(droneID, x, y, z) == block then
                    return worldX + x, worldY + y, worldZ + z
                end
            end
        end
    end
end

function DigStairsDown(droneID, depth)
    local x, y, z = getDroneCords(droneID)
    if z > depth then
        if getDroneBlock(droneID, 1, 0, 0) == Block.Air then
            moveDrone(droneID, 1, 0, 0)
        else
            if getDroneBlock(droneID, -1, 0, 0) == Block.Air then
                mineDroneBlock(droneID, 0, 0, -1)
            else
                mineDroneBlock(droneID, 1, 0, 0)
            end
        end
        return true;
    end
    return false;
end

function StripMine(droneID)
    if getDroneBlock(droneID, 1, 1, 1) == Block.Air then
        moveDrone(droneID, 1, 0, 0)
    else
        for z = 0, 1, 1 do
            for y = -1, 1, 1 do
                if getDroneBlock(droneID, 1, y, z) then
                    mineDroneBlock(droneID, 1, y, z)
                end
            end
        end
    end
end

function navigateToCords(droneID, xCor, yCor, zCor)
    local x, y, z = getDroneCords(droneID)


    local xCor = xCor or 0
    local yCor = yCor or 0
    local zCor = zCor or 0

    local xDistance = x - xCor
    local yDistance = y - yCor
    local zDistance = z - zCor
    
    -- Check for division by zero when calculating direction
    local xDirection = xDistance ~= 0 and -(xDistance / math.abs(xDistance)) or 0
    local yDirection = yDistance ~= 0 and -(yDistance / math.abs(yDistance)) or 0
    local zDirection = zDistance ~= 0 and -(zDistance / math.abs(zDistance)) or 0
    
    local absXDistance = math.abs(xDistance)
    local absYDistance = math.abs(yDistance)  -- Corrected typo from 'YDistance'
    local absZDistance = math.abs(zDistance)  -- Corrected typo from 'ZDistance'
    
    if xDirection ~= 0 then
        if getDroneBlock(droneID, xDirection, 0, 0) == Block.Air then
            moveDrone(droneID, xDirection, 0, 0)
            return
        end
        if getDroneBlock(droneID, xDirection, 0, 1) == Block.Air then
            moveDrone(droneID, xDirection, 0, 1)
            return
        end 
    end
    if absYDistance ~= 0 then
        if getDroneBlock(droneID, 0, yDirection, 0) == Block.Air then
            moveDrone(droneID, 0, yDirection, 0)
            return
        end
        if getDroneBlock(droneID, 0, yDirection, 1) == Block.Air then
            moveDrone(droneID, 0, yDirection, 1)
            return
        end 
    end
    
end