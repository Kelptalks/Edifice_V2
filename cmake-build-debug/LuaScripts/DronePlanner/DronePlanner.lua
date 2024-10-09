-- Plan Types
DronePlanType = {
    navigateToCords = 1,
    scavangeForFuel = 2,
}

-- Drone Plan structure
DronePlan = {
    planType = nil,
    goal = 0,
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

-- Function to execute scavenging for fuel
local function executeScavangeForFuel(droneManager)
    local dronePlan = droneManager.dronePlans[1] -- Access first plan (Lua is 1-indexed)
    if GetFuelCount(droneManager.droneId) < dronePlan.goal then
        HarvestRocksAndPlantMatter()
        if getDroneInventoryItemCount(droneManager.droneId, DroneItem.ItemPlantMatter) > 0 then
            DroneUseItemForFuel(droneManager.droneId, DroneItem.ItemPlantMatter, 1)
        end
    else
        -- Goal complete, remove the first plan
        table.remove(droneManager.dronePlans, 1)
    end
end

-- Function map
local functionMap = {
    [DronePlanType.navigateToCords] = function() end, -- Placeholder function for navigation
    [DronePlanType.scavangeForFuel] = executeScavangeForFuel,
}

-- Function to process drone plans on each tick
function TickDroneManager(droneManager)
    if droneManager.dronePlans[1] ~= nil then
        local currentPlanType = droneManager.dronePlans[1].planType
        local func = functionMap[currentPlanType]
        if func then
            func(droneManager)
        end
    end
end

-- Function to add a scavenging plan to the drone manager
function PlanScavangeForFuel(droneManager, fuelGoal)
    local dronePlan = {
        planType = DronePlanType.scavangeForFuel,
        goal = fuelGoal
    }
    table.insert(droneManager.dronePlans, dronePlan)
end