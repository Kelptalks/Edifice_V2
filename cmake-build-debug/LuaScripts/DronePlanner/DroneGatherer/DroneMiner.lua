function ExecuteMineOar(droneManager)
    local droneId = droneManager.droneId;
    local dronePlan = droneManager.dronePlans[1];
    

    local mine = dronePlan.mine
    if (dronePlan.goal == 3) then
        if (not mine.hasStairsDug) then
            PlanDigMineStairs(droneManager, mine)
        else
            dronePlan.goal = 2
        end
        return
    end
    -- Get to tunnel Location
    if (dronePlan.goal == 2) then
        PlanDigTunnel(droneManager, mine.currentTunnel * 3, 1, 0)
        mine.currentTunnel = mine.currentTunnel + 1
        dronePlan.goal = 1;
    end

    --At tunnel
    if (dronePlan.goal == 1) then
        local stoneCount = getDroneInventoryItemCount(droneId, DroneItem.ItemStone)
        local ironCount = getDroneInventoryItemCount(droneId, DroneItem.ItemIronOar)
        local copperCount = getDroneInventoryItemCount(droneId, DroneItem.ItemCopperOar)

        if (stoneCount >= dronePlan.goalStone and ironCount >= dronePlan.GoalIronOar and copperCount >= dronePlan.goalCopperOar) then
            dronePlan.goal = 0
            return
        else
            PlanDigTunnel(droneManager, 3, 0, -1)
            dronePlan.tunnelLength = dronePlan.tunnelLength + 3
        end
    end

    if (dronePlan.goal == 0) then
        -- Plan the to leave the mine
        local droneX, droneY, droneZ = getDroneCords(droneId)

        --2 Navigate Out of mine
        PlanNavigateToCords(droneManager, mine.xCor, mine.yCor, mine.zCor)

        --1 Navigate out of tunnel
        local tunnelExitX = droneX;
        local tunnelExitY = droneY + dronePlan.tunnelLength;
        local tunnelExitZ = droneZ;
        PlanNavigateToCords(droneManager, tunnelExitX, tunnelExitY, tunnelExitZ)
        
        table.remove(droneManager.dronePlans, 1);
    end

end

function PlanMineForOar(droneManager, mine, goalStone, goalCopperOar, GoalIronOar)
    local dronePlan = {
        planType = DronePlanType.mineOar;
        
        mine = mine;
        goal = 3;

        goalStone = goalStone;
        GoalIronOar = GoalIronOar;
        goalCopperOar = goalCopperOar;

        tunnelLength = 0
    }
    table.insert(droneManager.dronePlans, 1, dronePlan)
end

function ExecuteDigTunnel(droneManager)
    local droneId = droneManager.droneId;
    local dronePlan = droneManager.dronePlans[1];

    if (dronePlan.goal == 2) then
        local stepClear = true
        for z = 0, 1, 1 do
            for o = -1, 1, 1 do
                if (dronePlan.xDirection == 0) then
                    if (getDroneBlock(droneId, o, dronePlan.yDirection, z) ~= Block.Air) then
                        mineDroneBlock(droneId, o, dronePlan.yDirection, z);
                        stepClear = false;
                    end
                else
                    if (getDroneBlock(droneId, dronePlan.xDirection, o, z) ~= Block.Air) then
                        mineDroneBlock(droneId, dronePlan.xDirection, o, z);
                        stepClear = false;
                    end    
                end
            end
        end
        if (stepClear) then
            dronePlan.goal = 1
        end
    end

    if (dronePlan.goal == 1) then
        moveDrone(droneId, dronePlan.xDirection, dronePlan.yDirection, 0)
        dronePlan.distance = dronePlan.distance - 1
        if (dronePlan.distance > 0) then
            dronePlan.goal = 2; 
        else
            dronePlan.goal = 0
        end
    end

    if (dronePlan.goal == 0) then
        table.remove(droneManager.dronePlans, 1);
    end
end

function PlanDigTunnel(droneManager, distance, xDirection, yDirection)
    local dronePlan = {
        planType = DronePlanType.digTunnel;
        goal = 2;
        distance = distance;

        xDirection = xDirection;
        yDirection = yDirection;
    }
    table.insert(droneManager.dronePlans, 1, dronePlan)
end

function ExecuteDigMineStairs(droneManager)
    local droneId = droneManager.droneId;
    local dronePlan = droneManager.dronePlans[1];

    local mine = dronePlan.mine
    local droneX, droneY, DroneZ = getDroneCords(droneId)

    if (dronePlan.goal == 3) then
        PlanNavigateToCords(droneManager, mine.xCor, mine.yCor, mine.zCor)
        dronePlan.goal = 1
        return
    end

    -- Mine foward
    if (dronePlan.goal == 2) then
        
        if (getDroneBlock(droneId, 1, 0, 0) ~= Block.Air) then
            mineDroneBlock(droneId, 1, 0, 0)
        else
            moveDrone(droneId, 1, 0, 0)
            dronePlan.goal = 1
        end
        return
    end

    --Dig down
    if (dronePlan.goal == 1) then
        if (mineDroneBlock(droneId, 0, 0, -1) == 1) then
            if (mine.zDepthCor >= DroneZ) then
                dronePlan.goal = 0
            else
                dronePlan.goal = 2
            end
        end
        return
    end

    if (dronePlan.goal == 0) then
        mine.hasStairsDug = true
        table.remove(droneManager.dronePlans, 1);
    end
end

function PlanDigMineStairs(droneManager, mine)
    local dronePlan = {
        planType = DronePlanType.digMineStairs;
        goal = 3;
        mine = mine;
    }
    table.insert(droneManager.dronePlans, 1, dronePlan)
end

function CreateMine(xCor, yCor, zCor)
    local Mine = {
        xCor = xCor;
        yCor = yCor;
        zCor = zCor;


        hasStairsDug = false,

        zDepthCor = zCor - 50,
        currentTunnel = 1,
    }
    return Mine
end