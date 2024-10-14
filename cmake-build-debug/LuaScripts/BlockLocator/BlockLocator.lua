
package.path = package.path .. ";./LuaScripts/?.lua"
require("DroneLuaCommands.DroneCommands")
require("DroneLuaCommands.BlockData")
require("DroneMiner.BlockMiner")
require("DroneNavigator.DroneNavigator")
require("DronePlanner.DronePlanner")


function GetCordsOfHighestBlockOfType(droneId, Block)
    for z = getDroneViewRange(), -getDroneViewRange(), -1 do
        for y = getDroneViewRange(), -getDroneViewRange(), -1 do
            for x = getDroneViewRange(), -getDroneViewRange(), -1 do
                
                if getDroneBlock(droneId, x, y, z) == Block then
                    local xCor, yCor, zCor = getDroneCords(droneId)
                    
                    return x + xCor, y + yCor, z + zCor
                end
            end
        end
    end
    return "NoBlock";
end
