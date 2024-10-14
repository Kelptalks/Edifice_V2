-- Function to execute scavenging for fuel

-- ##########################################################
-- Scavenge
-- ##########################################################

function ExecuteScavangeForFuel(droneManager)
    local dronePlan = droneManager.dronePlans[1] -- Access first plan (Lua is 1-indexed)
    if GetFuelCount(droneManager.droneId) < dronePlan.goal then
        HarvestRocksAndPlantMatter()
    
        local hasDrill = false
        -- Check for saw
        for i = 0, 2, 1 do
            if getDroneToolSlot(droneManager.droneId, 0) == DroneTool.ToolStoneDrill then
                hasDrill = true;
            end
        end
        -- Craft one if has recorces and does not currently have one
        if getDroneInventoryItemCount(droneManager.droneId, DroneItem.ItemStone) >= 3 then
            if (hasDrill == false) then
                droneCraftTool(droneManager.droneId, DroneTool.ToolStoneDrill)
            end
        end

        if BasicWalkInDirection(droneManager.droneId, dronePlan.goalXCor, dronePlan.goalYCor, dronePlan.goalZCor) == -1 then
            dronePlan.goalXCor = math.random(-100, 100)
            dronePlan.goalYCor = math.random(-100, 100)
            dronePlan.goalZCor = math.random(-100, 100)
        end

        if getDroneInventoryItemCount(droneManager.droneId, DroneItem.ItemPlantMatter) > 0 then
            DroneUseItemForFuel(droneManager.droneId, DroneItem.ItemPlantMatter, 1)
        end
    else
        -- Goal complete, remove the first plan
        table.remove(droneManager.dronePlans, 1)
    end
end

function PlanScavangeForFuel(droneManager, fuelGoal)
    local dronePlan = {
        planType = DronePlanType.scavangeForFuel,
        goal = fuelGoal
    }
    table.insert(droneManager.dronePlans, 1, dronePlan)
end

-- ##########################################################
-- Harvest Wood
-- ##########################################################

function ExecuteDroneHarvestWood(droneManager)
    local dronePlan = droneManager.dronePlans[1]
    local x, y, z = getDroneCords(droneManager.droneId)
    local xCorOfHighestBlock, yCorOfHighestBlock, zCorOfHighestBlock = GetCordsOfHighestBlockOfType(droneManager.droneId, Block.BrownWood);

    --Craft a tool if needed
    if (dronePlan.goal == 4) then
        local hasSaw = false
        -- Check for saw
        for i = 0, 2, 1 do
            if getDroneToolSlot(droneManager.droneId, 0) == DroneTool.ToolStoneSaw then
                hasSaw = true;
            end
        end
        -- Craft one if has recorces and does not currently have one
        if getDroneInventoryItemCount(droneManager.droneId, DroneItem.ItemStone) >= 3 then
            if (hasSaw == false) then
                droneCraftTool(droneManager.droneId, DroneTool.ToolStoneSaw)
            end
        end

        dronePlan.goal = 3;
    end

    --Find a log and build up to it's height
    if (dronePlan.goal == 3) then
        if (xCorOfHighestBlock == "NoBlock") then
            if BasicWalkInDirection(droneManager.droneId, dronePlan.goalXCor, dronePlan.goalYCor, 0) == -1 then
                dronePlan.goalXCor = math.random(-150, 150)
                dronePlan.goalYCor = math.random(-150, 150)
            end
        else
            if BasicWalkInDirection(droneManager.droneId, xCorOfHighestBlock + 1, yCorOfHighestBlock, zCorOfHighestBlock) == -1 then
                dronePlan.goal = 2;
            end
        end
    end

    -- Build up next to tree
    if (dronePlan.goal == 2) then
        if (zCorOfHighestBlock < z) then
            if (getDroneBlock(droneManager.droneId, -1, 0, 0) ~= Block.Air) then
                mineDroneBlock(droneManager.droneId, -1, 0, 0)
            else
                moveDrone(droneManager.droneId, -1, 0, 0)
                dronePlan.goal = 1
            end
        else
            BlockUp(droneManager.droneId)
        end
    end

    --Chop down tree
    if (dronePlan.goal == 1) then
        local blockBellowDrone = getDroneBlock(droneManager.droneId, 0, 0, -1);
        if (blockBellowDrone == Block.BrownWood or blockBellowDrone == Block.Air or blockBellowDrone == Block.Leave) then
            mineDroneBlock(droneManager.droneId, 0, 0, -1)
        else
            dronePlan.goal = 0;
        end
    end

    --Check if goal has been met if not look for more trees
    if (dronePlan.goal == 0) then
        if (dronePlan.goalItemCount <= getDroneInventoryItemCount(droneManager.droneId, DroneItem.ItemLog)) then
            table.remove(droneManager.dronePlans, 1)
        else
            dronePlan.goal = 3;
        end
    end
end

function PlanDroneHarvestWood(droneManager, goalAmount)
    --Check slots for saw
    local dronePlan = {
        planType = DronePlanType.droneHarvestWood,
        goal = 4;
        goalXCor = 0;
        goalYCor = 0;
        goalZCor = 0;
        goalItemCount = goalAmount
    }
    table.insert(droneManager.dronePlans, 1, dronePlan)
end

-- ##########################################################
-- Dig / build tunnel
-- ##########################################################

function ExecuteBuildDigTunnel(droneManager)
    local dronePlan = droneManager.dronePlans[1]
    local x, y, z = getDroneCords(droneManager.droneId)

    -- Plan Navigate to goal start cords
    if (dronePlan.goal == 4) then

        PlanDroneNavigateToCords(droneManager, dronePlan.goalXCor, dronePlan.goalYCor, dronePlan.goalZCor)
        dronePlan.goal = 3
    end

    -- Area In front exept block under 
    if (dronePlan.goal == 3) then
        local stillMining = false;


        for directionMineCor = -1, 1, 1 do
            for zMineCor = 0, 1, 1 do
                if (droneManager.dronePlans.xDirection ~= 0) then
                    if getDroneBlock(droneManager.droneId, dronePlan.xDirection, directionMineCor, zMineCor) ~= Block.Air then
                        mineDroneBlock(droneManager.droneId, dronePlan.xDirection, directionMineCor, zMineCor)
                        stillMining = true
                    end
                else if (droneManager.dronePlans.yDirection ~= 0) then
                    if getDroneBlock(droneManager.droneId, directionMineCor, dronePlan.yDirection, zMineCor) ~= Block.Air then
                        mineDroneBlock(droneManager.droneId, directionMineCor, dronePlan.yDirection, zMineCor)
                        stillMining = true
                    end
                end
                end
            end
        end
        if not stillMining then
            dronePlan.goal = 2
        end
    end

    -- Step foward
    if (dronePlan.goal == 2) then
        if (getDroneBlock(droneManager.droneId, dronePlan.xDirection, dronePlan.yDirection, -1)) ~= Block.Air then
            moveDrone(droneManager.droneId, dronePlan.xDirection, dronePlan.yDirection, 0)
            dronePlan.targetGoal = dronePlan.targetGoal - 1
            if (dronePlan.targetGoal <= 0) then
                dronePlan.goal = 0
            else
                dronePlan.goal = 3
            end

        else
            PlaceRelativeBlock(droneManager.droneId, dronePlan.xDirection, dronePlan.yDirection, -1, Block.Dirt)
        end
    end
    if (dronePlan.goal == 0) then
        table.remove(droneManager.dronePlans, 1)
    end
end

function PlanDigTunnel(droneManager, xStart, yStart, zStart, xDirection, yDirection, length)
    local dronePlan = {
        planType = DronePlanType.digTunnel,
        goal = 4;
        goalXCor = xStart;
        goalYCor = yStart;
        goalZCor = zStart;
        xDirection = xDirection,
        yDirection = yDirection,
        targetGoal = length,
    }
    table.insert(droneManager.dronePlans, 1, dronePlan)
end