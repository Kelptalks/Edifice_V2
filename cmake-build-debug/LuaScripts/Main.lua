-- init.lua
-- Setup
package.path = package.path .. ";./LuaScripts/?.lua"
require("DroneLuaCommands.DroneCommands")
require("DroneLuaCommands.DroneFurnaceCommands")
require("DroneLuaCommands.BlockData")

require("DronePlanner.DronePlanner")

require("DronePlanner.DroneNavigator.DroneNavigator")
require("DronePlanner.DroneGatherer.DroneGatherer")
require("DronePlanner.DroneGatherer.DroneMiner")
require("DronePlanner.DroneCrafter.DroneCrafter")


DroneManagers = {}
Mine = CreateMine(0, 0, 24)

function ON_TICK()

    local droneCount = getDroneCount()
    
    -- Loop through all created drones
    if #DroneManagers < droneCount then
        table.insert(DroneManagers, CreateDroneManager(droneCount - 1))
        local droneManager = DroneManagers[droneCount]
        
        PlanMineForOar(droneManager, Mine, 256, 4, 4)
        PlanCraftStoneTools(droneManager)
        PlanScavengeSurface(droneManager, 5000, 0, 0, 6)
    end


    for droneId = 1, #DroneManagers, 1 do
        TickDroneManager(DroneManagers[droneId])
    end

end