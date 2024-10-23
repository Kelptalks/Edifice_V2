

function ExecuteCraftStoneTools(droneManager)
    local droneId = droneManager.droneId;
    local dronePlan = droneManager.dronePlans[1];

    if (dronePlan.goal == 2) then
        local stoneCount = getDroneInventoryItemCount(droneId, DroneItem.ItemStone)

        if (stoneCount < 6) then
            PlanScavengeSurface(droneManager, 100, 0, 0, 6)
        else
            dronePlan.goal = 1
        end
    end
    if (dronePlan.goal == 1) then
        if (getDroneToolSlot(droneId, 0) ~= DroneItem.ToolStoneDrill) then
            droneCraft(droneId, DroneItem.ToolStoneDrill);

        else if (getDroneToolSlot(droneId, 1) ~= DroneItem.ToolStoneSaw) then
                droneCraft(droneId, DroneItem.ToolStoneSaw);
        else
            dronePlan.goal = 0;
        end
        end
    end
    if (dronePlan.goal == 0) then
        table.remove(droneManager.dronePlans, 1);
    end
end

function PlanCraftStoneTools(droneManager)
    local dronePlan = {
        planType = DronePlanType.craftStoneTools;
        goal = 2;

    }
    table.insert(droneManager.dronePlans, 1, dronePlan)
end


function ExecuteCraftScaffolding(droneManager)
    local droneId = droneManager.droneId;
    local dronePlan = droneManager.dronePlans[1];


    if (dronePlan.goal == 2) then
        local LogCount = getDroneInventoryItemCount(droneId, DroneItem.ItemLog)
        local LogsNeeded = dronePlan.goalQuantity;

        local plantMatterCount = getDroneInventoryItemCount(droneId, DroneItem.ItemLog)
        local plantMatterNeeded = dronePlan.goalQuantity;
        if (plantMatterCount < plantMatterNeeded or LogCount < LogsNeeded) then
            PlanScavengeSurface(droneManager, 100, plantMatterNeeded, LogsNeeded, 0)
        else
            dronePlan.goal = 1
        end
    end

    if (dronePlan.goal == 1) then
        local ScaffoldingCount =  getDroneInventoryItemCount(droneId, DroneItem.ItemScaffolding)
        if (ScaffoldingCount/8 < dronePlan.goalQuantity) then
            droneCraft(droneId, DroneItem.ItemScaffolding)
        else
            dronePlan.goal = 0
        end
    end

    if (dronePlan.goal == 0) then
        table.remove(droneManager.dronePlans, 1);
    end
end

function PlanCraftScaffolding(droneManager, quantity)
    local dronePlan = {
        planType = DronePlanType.craftScaffolding;
        goal = 2;
        goalQuantity = quantity
    }
    table.insert(droneManager.dronePlans, 1, dronePlan)
end