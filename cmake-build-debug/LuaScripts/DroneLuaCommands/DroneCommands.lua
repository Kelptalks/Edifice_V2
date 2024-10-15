--Wrapper functions

-- Lua wrapper for moving a drone
function moveDrone(droneId, x, y, z)
    -- Optional arguments or defaults can be handled here
    z = z or 0
    return luaMoveDrone(droneId or 0, x, y, z)
end

-- Lua wrapper for getting the block relative to a drone
function getDroneBlock(droneId, offsetX, offsetY, offsetZ)
    return luaGetRelativeBlock(droneId  or 0, offsetX or 0, offsetY or 0, offsetZ or 0) + 1
end

-- Lua wrapper for mining a block relative to a drone
function mineDroneBlock(droneId, offsetX, offsetY, offsetZ)
    local result = luaMineRelativeBlock(droneId or 0, offsetX or 0, offsetY or 0, offsetZ or 0)
    return result
end

-- Lua wrapper for getting the drone count
function getDroneCount()
    return luaGetDroneCount()
end

-- Lua wrapper for getting the drones cords
function getDroneCords(droneID)
    return luaGetDroneCords(droneID or 0)
end

function droneCraftTool(droneID, tool)
    return luaCraftDroneTool(droneID, tool)
end

function getDroneToolSlot(droneID, slot)
    local result = luaGetDroneToolSlot(droneID, slot)
    if result == -1 then
        return 0;
    end
    return result
end

function getDroneInventoryItemCount(droneID, item)
    local result = luaGetDroneInventoryItemCount(droneID, item)
    if result == -1 then
        return 0;
    end
    return result
end

function getDroneViewRange()
    return 4
end

function DroneUseItemForFuel(droneId, item, quantity)
    luaDroneUseItemForFuel(droneId, item, quantity)
end

function PlaceRelativeBlock(droneId, offsetX, offsetY, offsetZ, block)
    return luaPlaceRelativeBlock(droneId or 0, offsetX, offsetY, offsetZ, block - 1)
end

function GetFuelCount(droneId)
    return luaGetDroneFuelCount(droneId)
end

function ReportDroneBug(string)
    luaReportDroneBug(string)
end

function GetDroneBusyTime(droneId)
    return luaGetDroneBusyTime(droneId)
end