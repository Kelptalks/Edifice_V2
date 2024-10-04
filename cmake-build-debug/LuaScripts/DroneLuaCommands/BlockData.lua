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

    -- Creature
    WormBody = 46,
    WormEyesLevel = 47,
    WormEyesUp = 48,
    WormMouth = 49,

    -- Drone
    DroneLeftForward = 50,
    DroneRightForward = 51,
    DroneRightBack = 52,
    DroneLeftBack = 53,

    -- Shaders
    GreyShader = 54,
    RedShader = 55,
    WhiteShader = 56,
    GreenShader = 57,

    -- Test
    HalfBlockTest = 58,

    -- Masking blocks
    MaskingBlock = 59,
    ShadowMaskingBlock = 60,
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