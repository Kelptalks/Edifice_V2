-- init.lua
-- Setup
package.path = package.path .. ";./LuaScripts/?.lua"
require("DroneLuaCommands.DroneCommands")
require("DroneLuaCommands.DroneFurnaceCommands")
require("DroneLuaCommands.BlockData")
require("DroneMiner.BlockMiner")
require("DroneNavigator.DroneNavigator")
require("DronePlanner.DronePlanner")
require("BlockLocator.BlockLocator")
require("DronePlanner.BasicPlans.BasicDronePlans")
require("DronePlanner.ResourceGatheringPlans.ResourceGatheringPlans")
require("DronePlanner.CraftingPlans.CraftingPlans")


DroneManagers = {}


function ON_TICK()

    local droneCount = getDroneCount()
    
    -- Loop through all created drones
    if #DroneManagers < droneCount then
        table.insert(DroneManagers, CreateDroneManager(droneCount - 1))
        
        PlanUseFurnaceToSmeltItems(DroneManagers[droneCount], DroneItem.ItemIronOar, 3)


        --PlanDroneHarvestWood(DroneManagers[droneCount], 100)
        --PlanDigTunnel(DroneManagers[droneCount], -50, 0, 25, 1, 0, 50)
        --PlanScavangeForFuel(DroneManagers[droneCount], 5000)
        --PlanSpiralStairsOfHeight(DroneManagers[droneCount], 500)
        --PlanDroneNavigateToCords(DroneManagers[droneCount], 0, 0, 25)
    end


    for droneId = 1, #DroneManagers, 1 do
        TickDroneManager(DroneManagers[droneId])
    end

end