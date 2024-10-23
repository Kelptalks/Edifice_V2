



function ExecuteNavigateToCords(droneManager)
    local droneId = droneManager.droneId;
    local dronePlan = droneManager.dronePlans[1];

    local droneX, droneY, droneZ = getDroneCords(droneId);


    -- Get Drone diffrences
    local xDistance = (droneX or 0) - (dronePlan.goalXCor or 0)
    local yDistance = (droneY or 0) - (dronePlan.goalYCor or 0)
    local zDistance = (droneZ or 0) - (dronePlan.goalZCor or 0)

    -- Get Drone Directions
    local xDirection = (xDistance ~= 0) and (-xDistance / math.abs(xDistance)) or 0
    local yDirection = (yDistance ~= 0) and (-yDistance / math.abs(yDistance)) or 0
    local zDirection = (zDistance ~= 0) and (-zDistance / math.abs(zDistance)) or 0

    --[[
    ReportDroneBug("+++++++++++++++++++++++++++++++++++++++++++++++++")
    local debug = string.format("xDistance : %s | yDistance : %s | zDistance : %s ", xDistance or 0, yDistance or 0, zDistance or 0)
        ReportDroneBug(debug);

    local debug = string.format("xGoalCor : %s | yGoalCor : %s | zGoalCor : %s ", dronePlan.goalXCor or 0, dronePlan.goalYCor or 0, dronePlan.goalZCor or 0)
        ReportDroneBug(debug);

    debug = string.format("droneX : %s | droneY : %s | droneZ : %s ", droneX or 0, droneY or 0, droneZ or 0)
        ReportDroneBug(debug);
        --]]

    if dronePlan.goal == 2 then
        if (xDistance == 0 and yDistance == 0) then
            dronePlan.goal = 0;
            return;
        end

        -- If the x Direction is safe to move
        local xDirectionSafe = "False";
        if (xDirection ~= 0) then
            if getDroneBlock(droneId, xDirection, 0, 0) == Block.Air then
                xDirectionSafe = "true";
            else if getDroneBlock(droneId, xDirection, 0, 1) == Block.Air then
                xDirectionSafe = "trueWithJump";
            end
            end

            --If xDirection is save move drone in xDirection
            if xDirectionSafe ~= "False" then
                local jump = 0;
                if xDirectionSafe == "trueWithJump" then
                    jump = 1;
                end
                moveDrone(droneId, xDirection, 0, jump)
                return;
            end
        end


        -- If the x Direction is safe to move
        local yDirectionSafe = "False";
        if (yDirection ~= 0) then
            if getDroneBlock(droneId, 0, yDirection, 0) == Block.Air then
                yDirectionSafe = "true";
            else if getDroneBlock(droneId, 0, yDirection, 1) == Block.Air then
                yDirectionSafe = "trueWithJump";
            end
            end

            --If yDirection is save then move drone in yDirection
            if yDirectionSafe ~= "False" then
                local jump = 0;
                if yDirectionSafe == "trueWithJump" then
                    jump = 1;
                end
                moveDrone(droneId, 0, yDirection, jump)
                return;
            end
        end

        -- If the drone cannot move twards the goal 
        if (xDirectionSafe == "False" and yDirectionSafe == "False") then
            dronePlan.goal = 1;
        end
    end

    -- Get out of stuck location
    if dronePlan.goal == 1 then
        if (droneX + xDirection == dronePlan.goalXCor and droneY + yDirection == dronePlan.goalYCor) then
            dronePlan.goal = 0
            return
        end
        
        
        dronePlan.goal = 2;
        local xCor = droneX + (-xDirection * 2 + 1);
        local yCor = droneY + (yDirection * 2 + 1);

        PlanNavigateToCords(droneManager, xCor, yCor, droneZ);

        yCor = droneY + (-yDirection * 2 + 1);
        PlanNavigateToCords(droneManager, xCor, yCor, droneZ);

    end

    if (dronePlan.goal == 0) then

        table.remove(droneManager.dronePlans, 1);
        
    end
end


function PlanNavigateToCords(droneManager, xCor, yCor, zCor)
    local dronePlan = {
        planType = DronePlanType.navigateToCords;
        goalXCor = xCor;
        goalYCor = yCor;
        goalZCor = zCor;

        goal = 2;
    }
    table.insert(droneManager.dronePlans, 1, dronePlan)
end
