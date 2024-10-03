-- init.lua

-- Setup

print("Setting Up Lua")
local test = 0;

function onTick()
    local droneCount = getDroneCount()

    for i = 0, droneCount - 1, 1
    do
        local xMod = 1;
        local yMod = 0;
        local zMod = 0;

        if getBlockRelativeToDrone(i, xMod, yMod, zMod) ~= 0
        then
            xMod = 0;
            yMod = 1;
            if getBlockRelativeToDrone(i, xMod, yMod, zMod) ~= 0
            then
                xMod = 0;
                yMod = -1;
            end
        end
        
        moveDrone(i, xMod, yMod, zMod)
    end
end