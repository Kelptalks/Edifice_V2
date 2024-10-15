


function ExecuteUseFurnaceToSmeltItems(droneManager)
    local dronePlan = droneManager.dronePlans[1]
    local droneId = droneManager.droneId
    if (dronePlan.goal == 3) then
        if (getDroneBlock(droneId, 1, 0, 0) ~= Block.Air) then
            mineDroneBlock(droneId, 1, 0, 0)
        else
            PlaceRelativeBlock(droneId, 1, 0, 0, Block.StoneFurnaceOff)
            dronePlan.goal = 2
        end
    end

    if (dronePlan.goal == 2) then
        if DroneAddSmeltingItemToFurnace(droneId, 1, 0, 0, DroneItem.ItemIronOar) == 1 then
            dronePlan.goal = 1;
        end
    

    end

    if (dronePlan.goal == 1) then
        if DroneAddSmeltingFuelToFurnace(droneId, 1, 0, 0, DroneItem.ItemLog, 1) == 1 then
            dronePlan.goal = 0;
        end
    end

    if (dronePlan.goal == 0) then
        if (GetRelativeFurnaceBusyTime(droneId, 1, 0, 0) < 0) then
            RemoveSmeltingItemFromFurnace(droneId, 1, 0, 0)
            dronePlan.goalItemCount = dronePlan.goalItemCount - 1;
            if (dronePlan.goalItemCount <= 0) then
                table.remove(droneManager.dronePlans, 1)
            end
            dronePlan.goal = 2
        end
    end
end


function PlanUseFurnaceToSmeltItems(droneManager, itemToSmelt, quantityToSmelt)

    ReportDroneBug("Planned : PlanToUseFurnaceToSmeltItems")
    local dronePlan = {
        planType = DronePlanType.useFurnaceToSmeltItems,
        goal = 3;
        goalXCor = 0;
        goalYCor = 0;
        goalItemCount = quantityToSmelt;
        goalItemType = itemToSmelt;
    }
    table.insert(droneManager.dronePlans, 1, dronePlan)
end