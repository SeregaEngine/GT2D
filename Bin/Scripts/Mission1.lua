-- Includes
dofile "Scripts/GraphicsDefines.lua"

-- Variables
Textures = {}
Sounds = {}
Music = {}
Anims = {}
Weapons = {}
States = {}
Entities = {}

Player = {}

-- Functions
onUpdate = {}
onRender = {}

---- >>>> Enter
function onEnter()
    GT_LOG(PR_NOTE, "Mission1 entered")

    defineResources()
    onEnterLocation3()
end

function defineResources()
    -- Textures
    Textures["Background1"] = defineTexture("Textures/Locations/Mission1-1.png", TW_LOCATION, TH_LOCATION)
    Textures["Background2"] = defineTexture("Textures/Locations/Mission1-2.png", TW_LOCATION, TH_LOCATION)
    Textures["Background3"] = defineTexture("Textures/Locations/Mission1-3.png", TW_LOCATION, TH_LOCATION)
    Textures["Parallax"] = defineTexture("Textures/Locations/Mission1-1_Parallax.png", TW_PARALLAX, TH_PARALLAX)

    Textures["BrownTrashCar"] = defineTexture("Textures/Cars/BrownTrashCar.png", TW_CAR, TH_CAR)

    Textures["Player"] = defineTexture("Textures/Actors/Player.png", TW_ACTOR, TH_ACTOR)
    Textures["DarkLord"] = defineTexture("Textures/Actors/DarkLord.png", TW_ACTOR, TH_ACTOR)
    Textures["Zhenek"] = defineTexture("Textures/Actors/Zhenek.png", TW_ACTOR, TH_ACTOR)

    -- Sounds
    Sounds["Punch1"] = defineSound("Sounds/Punch1.wav")
    Sounds["Punch2"] = defineSound("Sounds/Punch2.wav")
    Sounds["Punch3"] = defineSound("Sounds/Punch3.wav")
    Sounds["Punch4"] = defineSound("Sounds/Punch4.wav")

    -- Music
    Music["Ambient1"] = defineMusic("Music/VnatureBgSound.wav")
    Music["Ambient3"] = defineMusic("Music/MainGarageAmbient.wav")

    -- Animations
    Anims["Attack"] = defineAnimation(4, 3, 1000.0 / 2.0)

    -- Weapons
    Weapons["Fist"] = defineWeapon(Anims["Attack"], 4, 8, 8, 1.0, Sounds["Punch1"], Sounds["Punch2"], Sounds["Punch3"], Sounds["Punch4"])

    -- States
    States["KillPlayer"] = defineState("stateKillPlayer")
end

function onEnterLocation1()
    -- Functions
    onUpdate = onUpdateLocation1
    onRender = onRenderLocation1

    -- Local defines
    local GROUND_WIDTH = SCREEN_WIDTH * 2
    local GROUND_HEIGHT = 19
    local GROUND_X = 0
    local GROUND_Y = SCREEN_HEIGHT - GROUND_HEIGHT

    -- Level
    setGroundBounds(GROUND_X, GROUND_Y, GROUND_WIDTH, GROUND_HEIGHT)

    -- Entities
    Entities["Player"] = addActor(10, 60, TW_ACTOR, TH_ACTOR, Textures["Player"])
    toggleActorGodMode(Entities["Player"], true)
    setActorWeapon(Entities["Player"], Weapons["Fist"])
    Player = Entities["Player"]

    Entities["SwitchLocation"] = addTrigger(GROUND_WIDTH - 70, GROUND_Y + 10, 50, 50, Player, "triggerSwitchLocation")

    -- Camera
    setCameraBounds(0, 0, GROUND_WIDTH, SCREEN_HEIGHT)
    attachCamera(Entities["Player"])

    -- Music
    playMusic(Music["Ambient1"])
end

function onEnterLocation3()
    -- Function
    onUpdate = onUpdateLocation3
    onRender = onRenderLocation3

    -- Local defines
    local GROUND_WIDTH = SCREEN_WIDTH - 10
    local GROUND_HEIGHT = 10
    local GROUND_X = 7
    local GROUND_Y = SCREEN_HEIGHT - GROUND_HEIGHT

    -- Level
    setGroundBounds(GROUND_X, GROUND_Y, GROUND_WIDTH, GROUND_HEIGHT)

    -- Entities
    Entities["Player"] = addActor(SCREEN_WIDTH - 20, 64, TW_ACTOR, TH_ACTOR, Textures["Player"])
    Player = Entities["Player"]
    toggleActorGodMode(Player, true)
    setActorWeapon(Player, Weapons["Fist"])

    Entities["DarkLord"] = addActor(20, 60, TW_ACTOR, TH_ACTOR, Textures["DarkLord"])
    setActorWeapon(Entities["DarkLord"], Weapons["Fist"])
    setActorState(Entities["DarkLord"], States["KillPlayer"])

    -- Camera
    setCameraBounds(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)
    attachCamera(Player)

    -- Music
    playMusic(Music["Ambient3"])
end
---- <<<< Enter

---- >>>> Update
function onUpdateLocation1(dt)
    handleInput()
end

function onUpdateLocation3(dt)
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
---- <<<< Update

---- >>>> Render
function onRenderLocation1()
    drawFrame(RENDER_MODE_BACKGROUND, 0, false, 0,0,SCREEN_WIDTH*2,SCREEN_HEIGHT, Textures["Parallax"], 0, 0)
    drawFrame(RENDER_MODE_BACKGROUND, 1, false, 0,0,SCREEN_WIDTH,SCREEN_HEIGHT, Textures["Background1"], 0, 0)
    drawFrame(RENDER_MODE_BACKGROUND, 1, false, SCREEN_WIDTH,0,SCREEN_WIDTH,SCREEN_HEIGHT, Textures["Background1"], 0, 1)
end

function onRenderLocation3()
    drawFrame(RENDER_MODE_BACKGROUND, 0, false, 0,0,SCREEN_WIDTH,SCREEN_HEIGHT, Textures["Background3"], 0, 0)
    drawFrame(RENDER_MODE_BACKGROUND, 1, false, 42,45,68,20, Textures["BrownTrashCar"], 0, 0)
end
---- <<<< Render

---- >>>> Triggers
function triggerSwitchLocation(Entity)
    GT_LOG(PR_NOTE, "SwitchLocation triggerred")
    switchLocation("onEnterLocation3")
end
---- <<<< Triggers

---- >>>> AI States
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
---- <<<< AI States

