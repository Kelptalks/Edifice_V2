local function locateBlocksOfTypes(droneId, blocks)
    local droneX, droneY, droneZ = getDroneCords(droneId);

    local droneViewRange = getDroneViewRange();
    for z = -droneViewRange, droneViewRange, 1 do
        for y = -droneViewRange, droneViewRange, 1 do
            for x = -droneViewRange, droneViewRange, 1 do
                for i = 1, #blocks, 1 do
                    if (getDroneBlock(droneId, x, y, z) == blocks[i]) then
                        return x + droneX, y + droneY, z + droneZ;
                    end
                end
            end
        end
    end
    return "NoBlocksOfType"
end

local function mineSurroundingBlockOfTypes(droneId, blocks)
    for z = -1, 1, 1 do
        for y = -1, 1, 1 do
            for x = -1, 1, 1 do
                
                -- Loop through block list
                for i = 1, #blocks, 1 do
                    if getDroneBlock(droneId, x, y, z) == blocks[i] then
                        mineDroneBlock(droneId, x, y, z)
                        return true;
                    end 
                end
            end
        end
    end
    return false;
end

function ExecuteScavengeSurface(droneManager)
    local droneId = droneManager.droneId;
    local dronePlan = droneManager.dronePlans[1];

    if (dronePlan.goal == 2) then
        -- Check fuel and plant matter goals
        local compltedPlantMatterGoal = false;
        local plantMatterCount = getDroneInventoryItemCount(droneId, DroneItem.ItemPlantMatter)

        if dronePlan.goalFuel > GetFuelCount(droneId) then
            if plantMatterCount > 0 then
                DroneUseItemForFuel(droneId, DroneItem.ItemPlantMatter, plantMatterCount)
            end
        else if dronePlan.goalPlantMatter <= plantMatterCount then
            compltedPlantMatterGoal = true
        end
        end

        --Check log goal
        local logCount = getDroneInventoryItemCount(droneId, DroneItem.ItemLog)
        local compltedLogGoal = false;
        if (dronePlan.goalLog <= logCount) then
            compltedLogGoal = true
        end

        local stoneCount = getDroneInventoryItemCount(droneId, DroneItem.ItemStone)
        local compltedStoneGoal = false;
        if (dronePlan.goalStone <= stoneCount) then
            compltedStoneGoal = true
        end

        if (compltedPlantMatterGoal and compltedLogGoal and compltedStoneGoal) then
            dronePlan.goal = 0
        end


        local blocksToAttemptToMine = {};
        if not compltedLogGoal then
            table.insert(blocksToAttemptToMine, Block.Log)
        end

        if not compltedStoneGoal then
            table.insert(blocksToAttemptToMine, Block.Rock)
        end
        
        if not compltedPlantMatterGoal then
            table.insert(blocksToAttemptToMine, Block.WhiteFlowers)
            table.insert(blocksToAttemptToMine, Block.YellowFlowers)
            table.insert(blocksToAttemptToMine, Block.Flour)
            table.insert(blocksToAttemptToMine, Block.Mushroom)
        end

        -- If there are no blocks around to mine path to closest one
        local minedABlock = mineSurroundingBlockOfTypes(droneId, blocksToAttemptToMine)
        if not minedABlock then
            local xCor, yCor, zCor = locateBlocksOfTypes(droneId, blocksToAttemptToMine)
            if (xCor ~= "NoBlocksOfType") then
                PlanNavigateToCords(droneManager, xCor, yCor, zCor)
            else
                local droneXCor, droneYCor, DroneZCor = getDroneCords(droneId)
                PlanNavigateToCords(droneManager, droneXCor - 1, droneYCor, DroneZCor)
            end
        end

    else if (dronePlan.goal == 1) then
        
    
    else if (dronePlan.goal == 0) then
        table.remove(droneManager.dronePlans, 1);
    end
    end
    end
end

function PlanScavengeSurface(droneManager, goalFuel, goalPlantMatter, goalLog, goalStone)
    local dronePlan = {
        planType = DronePlanType.scavengeSurface;
        
        goal = 2;

        goalFuel = goalFuel;
        goalPlantMatter = goalPlantMatter;
        goalLog = goalLog;
        goalStone = goalStone;
    }
    table.insert(droneManager.dronePlans, 1, dronePlan)
end