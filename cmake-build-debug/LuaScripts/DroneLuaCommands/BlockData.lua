Block = {
    Air = 1,

    -- Basic
    Dirt = 2,
    CrackedEarth = 3,
    Hive = 4,
    Cobble = 5,
    Core = 6,
    Sand = 7,
    Debug = 8,

    -- Stones
    Granite = 9,
    Stone = 10,
    Magma = 11,

    -- Grasses
    GreenGrass = 12,
    BlueGrass = 13,

    -- Trees
    Leave = 14,
    PurpleWood = 15,
    PurpleWoodPlanks = 16,

    BrownWood = 17,
    BrownWoodPlanks = 18,

    -- LargeDandi
    Dandi = 19,
    DandiStem = 20,

    -- Large Mushrooms
    MushroomStem = 21,
    BlueMushroomBlock = 22,
    PinkMushroomBlock = 23,

    -- Large Fungi
    Fungi = 24,

    -- Transparent Plants
    Water = 25,
    YellowFlowers = 26,
    WhiteFlowers = 27,
    Mushroom = 28,
    Flour = 29,
    Glass = 30,
    Bulb = 31,
    Rock = 32,

    -- Metals
    Iron = 33,
    Copper = 34,

    MudBrick = 35,
    ClayBrick = 36,
    Coral = 37,
    StoneBrick = 38,
    FloweringStoneBrick = 39,

    -- Factory
    LBM = 40,
    Factory = 41,
    Crate = 42,
    Metal = 43,

    -- Transparent Factory
    ConveyorBelt = 44,
    Furnace = 45,
    StoneFurnaceOn = 46,
    StoneFurnaceOff = 47,

    -- Creature
    WormBody = 48,
    WormEyesLevel = 49,
    WormEyesUp = 50,
    WormMouth = 51,

    -- Drone
    Log = 52,
    DroneLeftForward = 53,
    DroneRightForward = 54,
    DroneRightBack = 55,
    DroneLeftBack = 56,
    DroneDead = 57,
}

DroneTool = {
    ToolNull = 0,
    ToolStoneDrill = 1,
    ToolStoneSaw = 2,
    ToolIronDrill = 3,
    ToolIronSaw = 4,
    ToolIronBattery = 5,
    ToolIronReceptacle = 6,
    ToolIronCamera = 7,
    ToolTitaniumDrill = 8,
    ToolTitaniumSaw = 9,
    ToolTitaniumBattery = 10,
    ToolTitaniumReceptacle = 11,
    ToolTitaniumCamera = 12,
    ToolExplosiveCamera = 13
}

DroneItem = {
    ItemNull = 0,
    ToolStoneDrill = 1,
    ToolStoneSaw = 2,
    ToolIronDrill = 3,
    ToolIronSaw = 4,
    ToolIronBattery = 5,
    ToolIronReceptacle = 6,
    ToolIronCamera = 7,
    ToolTitaniumDrill = 8,
    ToolTitaniumSaw = 9,
    ToolTitaniumBattery = 10,
    ToolTitaniumReceptacle = 11,
    ToolTitaniumCamera = 12,
    ToolExplosiveCamera = 13,
    ItemDirt = 14,
    ItemPlantMatter = 15,
    ItemLog = 16,
    ItemStone = 17,
    ItemStoneBrick = 18,
    ItemBrick = 19,
    ItemIronOar = 20,
    ItemIronBar = 21,
    ItemCopperOar = 22,
    ItemCopperBar = 23,
    ItemSand = 24,
    ItemGlass = 25,
    ItemTitaniumOre = 26,
    ItemTitaniumBar = 27,
    ItemPurpleLens = 28,
    ItemCharcoal = 29,
    ItemSulfur = 30
}

-- Reverse lookup table
local BlockReverseLookup = {}
for name, value in pairs(Block) do
    BlockReverseLookup[value] = name
end

-- Function to convert C enum value to block name
function getBlockEmByValue(value)
    return BlockNames[value + 1] or "Unknown block"  -- Add 1 to the C enum value to match Lua's 1-based indexing
end