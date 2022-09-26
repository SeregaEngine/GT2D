-- Includes
dofile "Scripts/GraphicsDefines.lua"

-- Defines
CAMERA_X = 0
CAMERA_Y = 0
CAMERA_WIDTH = SCREEN_WIDTH * 2
CAMERA_HEIGHT = SCREEN_HEIGHT

GROUND_WIDTH = SCREEN_WIDTH * 2
GROUND_HEIGHT = 19
GROUND_X = 0
GROUND_Y = SCREEN_HEIGHT - GROUND_HEIGHT

-- Variables
Textures = {}
Sounds = {}
Music = {}
Anims = {}
Weapons = {}
States = {}
Entities = {}

Player = {}

function onEnter()
    GT_LOG(PR_NOTE, "Mission1 entered")

    -- Textures
    Textures["Background"] = defineTexture("Textures/Locations/Mission1-1.png", TW_LOCATION, TH_LOCATION)
    Textures["Parallax"] = defineTexture("Textures/Locations/Mission1-1_Parallax.png", TW_PARALLAX, TH_PARALLAX)
    Textures["Player"] = defineTexture("Textures/Actors/Player.png", TW_ACTOR, TH_ACTOR)
    Textures["DarkLord"] = defineTexture("Textures/Actors/DarkLord.png", TW_ACTOR, TH_ACTOR)
    Textures["Zhenek"] = defineTexture("Textures/Actors/Zhenek.png", TW_ACTOR, TH_ACTOR)

    -- Sounds
    Sounds["Test"] = defineSound("Sounds/TestSound.wav")
    Sounds["Punch1"] = defineSound("Sounds/Punch1.wav")
    Sounds["Punch2"] = defineSound("Sounds/Punch2.wav")
    Sounds["Punch3"] = defineSound("Sounds/Punch3.wav")
    Sounds["Punch4"] = defineSound("Sounds/Punch4.wav")

    -- Music
    Music["Test"] = defineMusic("Music/TestMusic.mp3")

    -- Animations
    Anims["Attack"] = defineAnimation(4, 3, 1000.0 / 2.0)

    -- Weapons
    Weapons["Fist"] = defineWeapon(Anims["Attack"], 4, 8, 8, 1.0, Sounds["Punch1"], Sounds["Punch2"], Sounds["Punch3"], Sounds["Punch4"])

    -- States
    States["NPC"] = defineState("stateNPC")
    States["KillPlayer"] = defineState("stateKillPlayer")

    -- Entities
    Entities["Player"] = addActor(10, 60, TW_ACTOR, TH_ACTOR, Textures["Player"])
    toggleActorGodMode(Entities["Player"], true)
    setActorWeapon(Entities["Player"], Weapons["Fist"])
    Player = Entities["Player"]

    Entities["NPC"] = addActor(20, 60, TW_ACTOR, TH_ACTOR, Textures["Zhenek"])
    setActorState(Entities["NPC"], States["NPC"])

    Entities["Enemy"] = addActor(128, 59, TW_ACTOR, TH_ACTOR, Textures["DarkLord"])
    setActorWeapon(Entities["Enemy"], Weapons["Fist"])
    setActorState(Entities["Enemy"], States["KillPlayer"])

    -- Triggers
    Entities["Trigger"] = addTrigger(120, SCREEN_HEIGHT-8, 30, 8, Entities["Player"], "onTrigger")

    -- Set up level
    setBackground(Textures["Background"])
    setParallax(Textures["Parallax"])
    setGroundBounds(GROUND_X, GROUND_Y, GROUND_WIDTH, GROUND_HEIGHT)

    setCameraBounds(CAMERA_X, CAMERA_Y, CAMERA_WIDTH, CAMERA_HEIGHT)
    attachCamera(Entities["Player"])
end

function onUpdate(dt)
    handleInput()
end

local CanAttack = true
function handleInput()
    -- Leave if console is shown
    if isConsoleShown() then
        return
    end

    -- Stop game on escape
    if isKeyDown(GTK_ESCAPE) then
        stopGame()
    end

    -- Handle Player's behaviour
    if Player then
        if isKeyDown(GTK_W) then sendActorCmd(Player, GTC_MOVE_UP) end
        if isKeyDown(GTK_A) then sendActorCmd(Player, GTC_MOVE_LEFT) end
        if isKeyDown(GTK_S) then sendActorCmd(Player, GTC_MOVE_DOWN) end
        if isKeyDown(GTK_D) then sendActorCmd(Player, GTC_MOVE_RIGHT) end

        -- Handle attack
        -- Player have to press space many times
        local IsSpaceDown = isKeyDown(GTK_SPACE)
        if IsSpaceDown and CanAttack then
            sendActorCmd(Player, GTC_ATTACK)
            CanAttack = false
        elseif not IsSpaceDown then
            CanAttack = true
        end
    end
end

---- Triggers

local onTrigger_Count = 0 -- DEBUG(sean)
function onTrigger(entity)
    onTrigger_Count = onTrigger_Count + 1
    GT_LOG(PR_NOTE, string.format("onTrigger() entered %d times", onTrigger_Count))
end

---- AI States

--- state KillPlayer

function stateKillPlayer(Actor)
    local Task = getActorCurrentTask(Actor)
    local Status = checkActorTask(Actor)

    if Task == GTT_NONE then
        setActorTask(Actor, GTT_GOTO_ENTITY, Player)
    elseif Status == GTT_INPROCESS then
        return
    elseif Status == GTT_DONE then
        if Task == GTT_GOTO_ENTITY then
            setActorTask(Actor, GTT_KILL, Player)
        elseif Task == GTT_KILL then
            setActorTask(Actor, GTT_NONE)
            setActorState(Actor, nil)
        end
    elseif Status == GTT_IMPOSSIBLE then
        if Task == GTT_KILL then
            setActorTask(Actor, GTT_GOTO_ENTITY, Player)
        else
            setActorTask(Actor, GTT_NONE)
            setActorState(Actor, nil)
        end
    end
end

local stateNPC_Tasks = {
    [1] = {
        ["Task"] = GTT_GOTO,
        ["X"] = 30.0,
        ["Y"] = 56.0
    },

    [2] = {
        ["Task"] = GTT_GOTO,
        ["X"] = 40.0,
        ["Y"] = 60.0
    },

    [3] = {
        ["Task"] = GTT_GOTO,
        ["X"] = 50.0,
        ["Y"] = 60.0
    },

    [4] = {
        ["Task"] = GTT_GOTO,
        ["X"] = 70.0,
        ["Y"] = 64.0
    },

    [5] = {
        ["Task"] = GTT_GOTO,
        ["X"] = 80.0,
        ["Y"] = 64.0
    },

    [6] = {
        ["Task"] = GTT_GOTO,
        ["X"] = 128.0,
        ["Y"] = 64.0
    },

    [7] = {
        ["Task"] = GTT_NONE
    }
}
local stateNPC_Counter = 0

function stateNPC(Actor)
    if stateNPC_Counter == 0 or checkActorTask(Actor) == GTT_DONE then
        stateNPC_Counter = stateNPC_Counter + 1
        if stateNPC_Tasks[stateNPC_Counter].Task == GTT_NONE then
            stateNPC_Counter = 0
        else
            setActorTask(Actor, stateNPC_Tasks[stateNPC_Counter].Task, stateNPC_Tasks[stateNPC_Counter].X, stateNPC_Tasks[stateNPC_Counter].Y)
        end
    end
end

