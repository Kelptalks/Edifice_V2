package.path = package.path .. ";./LuaScripts/?.lua"
require("DronePlanner.BasicPlans.BasicDronePlans")
require("DronePlanner.ResourceGatheringPlans.ResourceGatheringPlans")
require("DronePlanner.CraftingPlans.CraftingPlans")

-- Plan Types
DronePlanType = {
    navigateToCords = 1,
    scavangeForFuel = 2,
    droneHarvestWood = 3,
    spiralStairsOfHeight = 4,
    digTunnel = 5,
    useFurnaceToSmeltItems = 6
}

-- Drone Plan structure
DronePlan = {
    planType = nil,
    goal = 0,
    goalXCor = 0,
    goalYCor = 0,
    goalZCor = 0,

    targetGoal = 0,
    xDirection = 0,
    yDirection = 0,

    goalItemCount = 0,
    goalItemType = 0,
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
    [DronePlanType.navigateToCords] = ExecuteNavigateToCords,
    [DronePlanType.scavangeForFuel] = ExecuteScavangeForFuel,
    [DronePlanType.droneHarvestWood] = ExecuteDroneHarvestWood,
    [DronePlanType.spiralStairsOfHeight] = ExecuteBuildSpiralStairsOfHeight,
    [DronePlanType.digTunnel] = ExecuteBuildDigTunnel,
    [DronePlanType.useFurnaceToSmeltItems] = ExecuteUseFurnaceToSmeltItems
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