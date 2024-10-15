

function DroneAddSmeltingFuelToFurnace(droneId, offsetX, offsetY, offsetZ, fuelItem, quantity)
    return luaDroneAddSmeltingFuelToFurnace(droneId, offsetX, offsetY, offsetZ, fuelItem, quantity);
end

function DroneAddSmeltingItemToFurnace(droneId, offsetX, offsetY, offsetZ, smeltingItem)
    return luaDroneAddSmeltingItemToFurnace(droneId, offsetX, offsetY, offsetZ, smeltingItem)
end

function RemoveSmeltingItemFromFurnace(droneId, offsetX, offsetY, offsetZ)
    return luaRemoveSmeltingItemFromFurnace(droneId, offsetX, offsetY, offsetZ)
end


function GetRelativeFurnaceBusyTime(droneId, offsetX, offsetY, offsetZ)
    return luaGetRelativeFurnaceBusyTime(droneId, offsetX, offsetY, offsetZ)
end