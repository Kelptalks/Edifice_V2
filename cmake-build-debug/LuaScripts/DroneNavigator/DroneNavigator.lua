package.path = package.path .. ";./LuaScripts/?.lua"
require("DroneLuaCommands.DroneCommands")
require("DroneLuaCommands.BlockData")

function navigateToCords(droneID, xCor, yCor, zCor)
    local x, y, z = getDroneCords(droneID)

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