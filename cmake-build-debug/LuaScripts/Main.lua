-- init.lua
-- Setup
package.path = package.path .. ";./LuaScripts/?.lua"
require("DroneLuaCommands.DroneCommands")
require("DroneLuaCommands.BlockData")
require("DroneMiner.BlockMiner")
require("DroneNavigator.DroneNavigator")

print("Starting Lua");
local test = 0;
hasDrill = 0

function ON_TICK()

    local droneCount = getDroneCount()
    
    for i = 0, droneCount - 1, 1
    do
        if getDroneInventoryItemCount(i, DroneItem.ItemPlantMatter) >= 3 then
            DroneUseItemForFuel(i, DroneItem.ItemPlantMatter, 3)
        end

        -- Collect rocks for drill
        if getDroneToolSlot(i, 0) == 0 then
                mineBlockAroundDrone(i, Block.Rock)
                mineBlockAroundDrone(i, Block.Flour)
                mineBlockAroundDrone(i, Block.WhiteFlowers)
                mineBlockAroundDrone(i, Block.YellowFlowers)
                mineBlockAroundDrone(i, Block.Mushroom)

            if getDroneInventoryItemCount(i, DroneItem.ItemStone) == 3 then
                droneCraftTool(i, DroneTool.ToolStoneDrill) 
                hasDrill = 1;
            end
            
            local x, y, z = getCordsOfBlock(i, Block.Rock);
            navigateToCords(i, x, y, z);
        -- Mine down 
        else if getDroneInventoryItemCount(i, DroneItem.ItemIronOar) < 5 then
            -- Craft extra drill if possible
            if getDroneToolSlot(i, 2) == 0 then
                if getDroneInventoryItemCount(i, DroneItem.ItemStone) == 3 then
                    droneCraftTool(i, DroneTool.ToolStoneDrill) 
                end
            end

            -- Start mineing down
            if DigStairsDown(i, 20) == false then
                StripMine(i)
            end
            
        else

        end
    end
    end
end