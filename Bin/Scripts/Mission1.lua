--[[ TODO
    - Restyle code
]]--

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
textures = {}
sounds = {}
music = {}
anims = {}
weapons = {}
states = {}
entities = {}

player = {}

function onEnter()
    GT_LOG(PR_NOTE, "Mission1 entered")

    -- Textures
    textures["background"] = defineTexture("Textures/Locations/Mission1-1.png", TW_LOCATION, TH_LOCATION)
    textures["parallax"] = defineTexture("Textures/Locations/Mission1-1_Parallax.png", TW_PARALLAX, TH_PARALLAX)
    textures["player"] = defineTexture("Textures/Actors/Player.png", TW_ACTOR, TH_ACTOR)
    textures["dark_lord"] = defineTexture("Textures/Actors/DarkLord.png", TW_ACTOR, TH_ACTOR)
    textures["zhenek"] = defineTexture("Textures/Actors/Zhenek.png", TW_ACTOR, TH_ACTOR)

    -- Sounds
    sounds["test"] = defineSound("Sounds/TestSound.wav")
    sounds["punch1"] = defineSound("Sounds/Punch1.wav")
    sounds["punch2"] = defineSound("Sounds/Punch2.wav")
    sounds["punch3"] = defineSound("Sounds/Punch3.wav")
    sounds["punch4"] = defineSound("Sounds/Punch4.wav")

    -- Music
    music["test"] = defineMusic("Music/TestMusic.mp3")

    -- Animations
    anims["attack"] = defineAnimation(4, 3, 1000.0 / 2.0)

    -- Weapons
    weapons["fist"] = defineWeapon(anims["attack"], 4,  -8, -8, 8, 8,  1.0,  sounds["punch1"], sounds["punch2"], sounds["punch3"], sounds["punch4"])

    -- States
    states["NPC"] = defineState("stateNPC")
    states["kill_player"] = defineState("stateKillPlayer")

    -- Entities
    entities["player"] = addActor(10, 60, TW_ACTOR, TH_ACTOR, textures["player"])
    toggleActorGodMode(entities["player"], true)
    setActorWeapon(entities["player"], weapons["fist"])
    player = entities["player"]

    entities["NPC"] = addActor(20, 60, TW_ACTOR, TH_ACTOR, textures["zhenek"])
    setActorState(entities["NPC"], states["NPC"])

    entities["enemy"] = addActor(128, 60, TW_ACTOR, TH_ACTOR, textures["dark_lord"])
    setActorWeapon(entities["enemy"], weapons["fist"])
    setActorState(entities["enemy"], states["kill_player"])

    -- Triggers
    entities["trigger"] = addTrigger(120, SCREEN_HEIGHT-8, 30, 8, entities["player"], "onTrigger")

    -- Set up level
    setBackground(textures["background"])
    setParallax(textures["parallax"])
    setGroundBounds(GROUND_X, GROUND_Y, GROUND_WIDTH, GROUND_HEIGHT)

    setCameraBounds(CAMERA_X, CAMERA_Y, CAMERA_WIDTH, CAMERA_HEIGHT)
    attachCamera(entities["player"])
end

function onUpdate(dt)
    handleInput()
end

local canAttack = true
function handleInput()
    -- Leave if console is shown
    if isConsoleShown() then
        return
    end

    -- Stop game on escape
    if isKeyDown(GTK_ESCAPE) then
        stopGame()
    end

    -- Handle player's behaviour
    if player then
        if isKeyDown(GTK_W) then sendActorCmd(player, GTC_MOVE_UP) end
        if isKeyDown(GTK_A) then sendActorCmd(player, GTC_MOVE_LEFT) end
        if isKeyDown(GTK_S) then sendActorCmd(player, GTC_MOVE_DOWN) end
        if isKeyDown(GTK_D) then sendActorCmd(player, GTC_MOVE_RIGHT) end

        -- Handle attack
        -- Player have to press space many times
        local isSpaceDown = isKeyDown(GTK_SPACE)
        if isSpaceDown and canAttack then
            sendActorCmd(player, GTC_ATTACK)
            canAttack = false
        elseif not isSpaceDown then
            canAttack = true
        end
    end
end

---- Triggers

local onTrigger_count = 0 -- DEBUG(sean)
function onTrigger(entity)
    onTrigger_count = onTrigger_count + 1
    GT_LOG(PR_NOTE, string.format("onTrigger() entered %d times", onTrigger_count))
end

---- AI States

--- state KillPlayer

function stateKillPlayer(actor)
    local task = getActorCurrentTask(actor)
    local status = checkActorTask(actor)

    if task == GTT_NONE then
        setActorTask(actor, GTT_GOTO_ENTITY, player)
    elseif status == GTT_INPROCESS then
        return
    elseif status == GTT_DONE then
        if task == GTT_GOTO_ENTITY then
            setActorTask(actor, GTT_KILL, player)
        elseif task == GTT_KILL then
            setActorTask(actor, GTT_NONE)
            setActorState(actor, nil)
        end
    elseif status == GTT_IMPOSSIBLE then
        if task == GTT_KILL then
            setActorTask(actor, GTT_GOTO_ENTITY, player)
        else
            setActorTask(actor, GTT_NONE)
            setActorState(actor, nil)
        end
    end
end

local stateNPC_tasks = {
    [1] = {
        ["task"] = GTT_GOTO,
        ["x"] = 30.0,
        ["y"] = 56.0
    },

    [2] = {
        ["task"] = GTT_GOTO,
        ["x"] = 40.0,
        ["y"] = 60.0
    },

    [3] = {
        ["task"] = GTT_GOTO,
        ["x"] = 50.0,
        ["y"] = 60.0
    },

    [4] = {
        ["task"] = GTT_GOTO,
        ["x"] = 70.0,
        ["y"] = 64.0
    },

    [5] = {
        ["task"] = GTT_GOTO,
        ["x"] = 80.0,
        ["y"] = 64.0
    },

    [6] = {
        ["task"] = GTT_GOTO,
        ["x"] = 128.0,
        ["y"] = 64.0
    },

    [7] = {
        ["task"] = GTT_NONE
    }
}
local stateNPC_counter = 0

function stateNPC(actor)
    if stateNPC_counter == 0 or checkActorTask(actor) == GTT_DONE then
        stateNPC_counter = stateNPC_counter + 1
        if stateNPC_tasks[stateNPC_counter].task == GTT_NONE then
            stateNPC_counter = 0
        else
            setActorTask(actor, stateNPC_tasks[stateNPC_counter].task, stateNPC_tasks[stateNPC_counter].x, stateNPC_tasks[stateNPC_counter].y)
        end
    end
end

