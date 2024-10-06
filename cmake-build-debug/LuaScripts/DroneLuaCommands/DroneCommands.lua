--Wrapper functions

-- Lua wrapper for moving a drone
function moveDrone(droneId, x, y, z)
    -- Optional arguments or defaults can be handled here
    z = z or 0
    return luaMoveDrone(droneId, x, y, z)
end

-- Lua wrapper for getting the block relative to a drone
function getDroneBlock(droneId, offsetX, offsetY, offsetZ)
    return luaGetRelativeBlock(droneId, offsetX, offsetY, offsetZ) + 1
end

-- Lua wrapper for mining a block relative to a drone
function mineDroneBlock(droneId, offsetX, offsetY, offsetZ)
    local result = luaMineRelativeBlock(droneId, offsetX, offsetY, offsetZ)
    if result == -1 then
        error("Failed to mine block. Invalid drone ID or position.")
    end
    return result
end

-- Lua wrapper for getting the drone count
function getDroneCount()
    return luaGetDroneCount()
end

-- Lua wrapper for getting the drones cords
function getDroneCords(droneID)
    return luaGetDroneCords(droneID)
end