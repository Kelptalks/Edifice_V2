function ExecuteNavigateToCords(droneManager)
    local dronePlan = droneManager.dronePlans[1]
    
    if (dronePlan.goal == 2) then
        -- Navigate to closesest build up location
        --Calculate closest build up commands
        local xGoal, yGoal = GetClosestBuildUpLocation(droneManager.droneId, dronePlan.goalXCor, dronePlan.goalYCor, dronePlan.goalZCor);

        -- If at build up location update Goal
        if BasicWalkInDirection(droneManager.droneId, xGoal, yGoal, 0) == -1 then
            dronePlan.goal = 1;
        end

    else if (dronePlan.goal == 1) then
        -- Build stairs to up to build up location
        if BuildStairsInDirectionToZCor(droneManager.droneId, dronePlan.goalXCor, dronePlan.goalYCor, dronePlan.goalZCor) == -1 then
            -- Mark plan as complete 
            dronePlan.goal = 0
        end
    else if (dronePlan.goal == 0) then
        --Remove the plan from drone manager
        table.remove(droneManager.dronePlans, 1)
    end
    end
    end
end

function PlanDroneNavigateToCords(droneManager, goalXCor, goalYCor, goalZCor)
    ReportDroneBug("planned navigateToCords")
    local dronePlan = {
        planType = DronePlanType.navigateToCords,
        goal = 2;
        goalXCor = goalXCor;
        goalYCor = goalYCor;
        goalZCor = goalZCor;
    }

    table.insert(droneManager.dronePlans, 1, dronePlan)
end


function ExecuteBuildSpiralStairsOfHeight(droneManager)
    local dronePlan = droneManager.dronePlans[1]
    local x, y, z = getDroneCords(droneManager.droneId)
    if dronePlan.goalZCor >= z then
        local xDirection = 0;
        local yDirection = 0;
            -- Correcting the elseif structure
        if dronePlan.goal == 1 then
            xDirection = 1
        elseif dronePlan.goal == 2 then
            yDirection = -1
        elseif dronePlan.goal == 3 then
            xDirection = -1
        elseif dronePlan.goal == 4 then
            yDirection = 1
        end


        
        if BuildStairInDirection(droneManager.droneId, xDirection, yDirection) == "Finished" then
            dronePlan.goal = dronePlan.goal + 1
            if (dronePlan.goal == 5) then
                dronePlan.goal = 1
            end
        end

    else
        table.remove(droneManager.dronePlans, 1)
    end
end

function PlanSpiralStairsOfHeight(droneManager, goalAmount)
    ReportDroneBug("planned BuildSpiralStairs")
    local dronePlan = {
        planType = DronePlanType.spiralStairsOfHeight,
        goal = 1;
        goalXCor = 0;
        goalYCor = 0;
        goalZCor = goalAmount;
    }
    table.insert(droneManager.dronePlans, 1, dronePlan)
end