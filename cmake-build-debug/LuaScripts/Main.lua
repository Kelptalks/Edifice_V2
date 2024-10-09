-- init.lua
-- Setup
package.path = package.path .. ";./LuaScripts/?.lua"
require("DroneLuaCommands.DroneCommands")
require("DroneLuaCommands.BlockData")
require("DroneMiner.BlockMiner")
require("DroneNavigator.DroneNavigator")
require("DronePlanner.DronePlanner")

io.stdout:setvbuf("no")
print("Starting Lua");
io.flush() 


DroneManagers = {}


function ON_TICK()

    local droneCount = getDroneCount()
    
    -- Loop through all created drones
    if #DroneManagers < droneCount then
        table.insert(DroneManagers, CreateDroneManager(droneCount - 1))
        PlanScavangeForFuel(DroneManagers[droneCount], 1000)
    end


    for droneId = 1, #DroneManagers, 1 do
        TickDroneManager(DroneManagers[droneId])
    end

end