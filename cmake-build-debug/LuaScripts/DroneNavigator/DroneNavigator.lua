package.path = package.path .. ";./LuaScripts/?.lua"
require("DroneLuaCommands.DroneCommands")
require("DroneLuaCommands.BlockData")

function GetCordsOfBlock(droneID, block)
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
    return "NoBlocks"
end

function BlockUp(droneID, block)
    if (getDroneBlock(droneID, 0, 0, 1)) ~= Block.Air then
        mineDroneBlock(droneID, 0, 0, 1)
    else 
        PlaceRelativeBlock(droneID, 0, 0, 0, block)
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

function GetClosestBuildUpLocation(droneID, xCor, yCor, zCor)
    xCor = xCor or 0
    yCor = yCor or 0
    zCor = zCor or 0
    
    
    local x, y, z = getDroneCords(droneID)
    local xDistance = x - xCor
    local yDistance = y - yCor
    local zDistance = z - zCor
    
    -- Check for division by zero when calculating direction
    local xDirection = xDistance ~= 0 and -(xDistance / math.abs(xDistance)) or 0
    local yDirection = yDistance ~= 0 and -(yDistance / math.abs(yDistance)) or 0
    
    local absXDistance = math.abs(xDistance)
    local absYDistance = math.abs(yDistance)
    local absZDistance = math.abs(zDistance)



    --Based on the quadrent of the drone return build up location

    local xGoal = xCor;
    local yGoal = yCor - zDistance

    return xGoal, yGoal
end

function BuildStairInDirection(droneID, xDirection, yDirection)
    if getDroneBlock(droneID, xDirection, yDirection, 0) == Block.Air then
        PlaceRelativeBlock(droneID, xDirection, yDirection, 0, Block.Dirt)
        return "Unfinished";

    else if (getDroneBlock(droneID, xDirection, yDirection, 1)) ~= Block.Air then
        mineDroneBlock(droneID, xDirection, yDirection, 1)
        return "Unfinished";
    else
        moveDrone(droneID, xDirection, yDirection, 1);
        return "Finished";
    end
    end
end

function BuildStairsInDirectionToZCor(droneID, xGoal, yGoal, zGoal)
    xGoal = xGoal or 0
    yGoal = yGoal or 0
    zGoal = zGoal or 0
    
    local x, y, z = getDroneCords(droneID)

    local xDistance = x - xGoal
    local yDistance = y - yGoal
    local zDistance = z - zGoal

    -- Check for division by zero when calculating direction
    local xDirection = xDistance ~= 0 and -(xDistance / math.abs(xDistance)) or 0
    local yDirection = yDistance ~= 0 and -(yDistance / math.abs(yDistance)) or 0
    if zGoal > z then
        if getDroneBlock(droneID, xDirection, yDirection, 0) == Block.Air then
            PlaceRelativeBlock(droneID, xDirection, yDirection, 0, Block.Dirt)

        else if (getDroneBlock(droneID, xDirection, yDirection, 1)) ~= Block.Air then
            mineDroneBlock(droneID, xDirection, yDirection, 1)

        else
            moveDrone(droneID, xDirection, yDirection, 1);

        end
        end
        return 1;
    else if zGoal < z then
        if getDroneBlock(droneID, 1, 0, 0) == Block.Air then
            moveDrone(droneID, 1, 0, 0)
        else
            if getDroneBlock(droneID, -1, 0, 0) == Block.Air then
                mineDroneBlock(droneID, 0, 0, -1)
            else
                mineDroneBlock(droneID, 1, 0, 0)
            end
        end
    else 
        return -1;
    end
    end
    
    
end

function BasicWalkInDirection(droneID, xCor, yCor, zCor)

    xCor = xCor or 0
    yCor = yCor or 0
    zCor = zCor or 0
    

    local x, y, z = getDroneCords(droneID)

    local xDistance = x - xCor
    local yDistance = y - yCor
    
    -- Check for division by zero when calculating direction
    local xDirection = xDistance ~= 0 and -(xDistance / math.abs(xDistance)) or 0
    local yDirection = yDistance ~= 0 and -(yDistance / math.abs(yDistance)) or 0
    
    local absXDistance = math.abs(xDistance)
    local absYDistance = math.abs(yDistance)

    --Basic walk in direction
    if absXDistance ~= 0 then
        if getDroneBlock(droneID, xDirection, 0, 0) == Block.Air then
            moveDrone(droneID, xDirection, 0, 0)
            return 1;
        end
        if getDroneBlock(droneID, xDirection, 0, 1) == Block.Air then
            moveDrone(droneID, xDirection, 0, 1)
            return 1;
        end 
        if getDroneBlock(droneID, xDirection, 0, 1) ~= Block.Air then
            moveDrone(droneID, 0, 1, 1)
            return 1;
        end 
        moveDrone(droneID, 1, -1, 1)
        return 1;
    end
    if absYDistance ~= 0 then
        if getDroneBlock(droneID, 0, yDirection, 0) == Block.Air then
            moveDrone(droneID, 0, yDirection, 0)
            return 1;
        end
        if getDroneBlock(droneID, 0, yDirection, 1) == Block.Air then
            moveDrone(droneID, 0, yDirection, 1)
            return 1;
        end
        if getDroneBlock(droneID, 0, yDirection, 1) ~= Block.Air then
            moveDrone(droneID, 1, 0, 1)
            return 1;
        end 
        moveDrone(droneID, -1, 0, 1)
        return 1;
    end

    return -1;
end

function navigateToCords(droneID, xCor, yCor, zCor)
    local x, y, z = getDroneCords(droneID)
    
    local x, y, z = getDroneCords(droneID)
    local xDistance = x - xCor
    local yDistance = y - yCor
    local zDistance = z - zCor
    
    -- Check for division by zero when calculating direction
    local xDirection = xDistance ~= 0 and -(xDistance / math.abs(xDistance)) or 0
    local yDirection = yDistance ~= 0 and -(yDistance / math.abs(yDistance)) or 0
    local zDirection = zDistance ~= 0 and -(zDistance / math.abs(zDistance)) or 0


    if zDirection < 0 then
        DigStairsDown(droneID, zCor)

    elseif zDirection > 0 then
        if getDroneBlock(droneID, xDirection, 0, 1) ~= Block.Air then
            mineDroneBlock(droneID, xDirection, yDirection, 1)
        else 
            PlaceRelativeBlock(droneID, xDirection, yDirection, 0, Block.Dirt)
        end
    end

    --Basic walk in direction
    BasicWalkInDirection(droneID or 0, xCor or 0, yCor or 0, zCor or 0)
end