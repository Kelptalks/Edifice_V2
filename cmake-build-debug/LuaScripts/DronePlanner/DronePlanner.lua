package.path = package.path .. ";./LuaScripts/?.lua"
require("DronePlanner.DroneNavigator.DroneNavigator")
require("DronePlanner.DroneGatherer.DroneGatherer")
require("DronePlanner.DroneCrafter.DroneCrafter")
require("DronePlanner.DroneGatherer.DroneMiner")

-- Plan Types
DronePlanType = {
    navigateToCords = 1,
    scavengeSurface = 2;
    craftStoneTools = 3;
    craftScaffolding = 4;

    mineOar = 5;
    digMineStairs = 6;
    digTunnel = 7;
}

-- Drone Plan structure
DronePlan = {
    planType = nil,
}

-- Drone Manager structure
DroneManager = {
    droneId = 0,
    dronePlans = {},
}

-- Function to create a new drone manager
function CreateDroneManager(id)
    local newDroneManager = {
        droneId = id,
        dronePlans = {},
    }
    return newDroneManager
end

-- ##########################################################
-- Plan Managegment
-- ##########################################################

-- Function map
local functionMap = {
    [DronePlanType.navigateToCords] = ExecuteNavigateToCords;
    [DronePlanType.scavengeSurface] = ExecuteScavengeSurface;
    [DronePlanType.craftStoneTools] = ExecuteCraftStoneTools;
    [DronePlanType.craftScaffolding] = ExecuteCraftScaffolding;

    [DronePlanType.mineOar] = ExecuteMineOar;
    [DronePlanType.digMineStairs] = ExecuteDigMineStairs;
    [DronePlanType.digTunnel] = ExecuteDigTunnel;
}

-- Function to process drone plans on each tick
function TickDroneManager(droneManager)
    if (GetDroneBusyTime(droneManager.droneId) < 1) then

        if droneManager.dronePlans[1] ~= nil then
            local currentPlanType = droneManager.dronePlans[1].planType
            local func = functionMap[currentPlanType]
            if func then
                func(droneManager)
            end
        end
    end
end