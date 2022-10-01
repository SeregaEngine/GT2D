-- Includes
dofile "Scripts/GraphicsDefines.lua"

-- Resources
Textures = {}
Sounds = {}
Music = {}
Anims = {}
Weapons = {}
States = {}

-- Location's stuff
Entities = {}
Triggers = {}
Dialogs = {}

-- Player
Player = nil
PlayerControllable = true

-- Functions
onUpdate = nil
onRender = nil

---- >>>> Enter
function onEnter()
    GT_LOG(PR_NOTE, "Mission1 entered")

    defineResources()
    onEnterL1()
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

    Textures["DialogSquare"] = defineTexture("Textures/DialogBox/Square.png", TW_DIALOG, TH_DIALOG)
    Textures["DialogCloud"] = defineTexture("Textures/DialogBox/Cloud.png", TW_DIALOG, TH_DIALOG)

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
    States["PlayerDialog"] = defineState("statePlayerDialog")
    States["DarkLordDialog"] = defineState("stateDarkLordDialog")
end

function onEnterL1()
    -- Functions
    onUpdate = onUpdateL1
    onRender = onRenderL1

    -- Local defines
    local GROUND_WIDTH = SCREEN_WIDTH * 2
    local GROUND_HEIGHT = 19
    local GROUND_X = 0
    local GROUND_Y = SCREEN_HEIGHT - GROUND_HEIGHT

    -- Level
    setGroundBounds(GROUND_X, GROUND_Y, GROUND_WIDTH, GROUND_HEIGHT)

    -- Entities
    Entities["Player"] = addActor(120, 60, GW_ACTOR, GH_ACTOR, Textures["Player"])
    toggleActorGodMode(Entities["Player"], true)
    setActorWeapon(Entities["Player"], Weapons["Fist"])
    Player = Entities["Player"]

    Triggers["SwitchLocation"] = addTrigger(GROUND_WIDTH - 70, GROUND_Y + 30, 20, 100, Player, "triggerSwitchLocation")

    -- Camera
    setCameraBounds(0, 0, GROUND_WIDTH, SCREEN_HEIGHT)
    attachCamera(Entities["Player"])

    -- Music
    playMusic(Music["Ambient1"])
end

function onEnterL3()
    -- Function
    onUpdate = onUpdateL3
    onRender = onRenderL3

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
    PlayerControllable = false
    setActorWeapon(Player, Weapons["Fist"])
    setActorState(Player, States["PlayerDialog"])
    toggleActorGodMode(Player, true)
    turnActorLeft(Player)

    Entities["DarkLord"] = addActor(20, 60, GW_ACTOR, GH_ACTOR, Textures["DarkLord"])
    setActorWeapon(Entities["DarkLord"], Weapons["Fist"])
    setActorState(Entities["DarkLord"], States["DarkLordDialog"])

    Dialogs["DarkLordDialog1"] = addDialog(GW_DIALOG, GH_DIALOG, "What are you doing here, Petrol?",
                                           1, Entities["DarkLord"], Textures["DialogSquare"])
    Dialogs["PlayerDialog1"] = addDialog(GW_DIALOG, GH_DIALOG, "Just walking around, my lord",
                                         1, Player, Textures["DialogSquare"])
    Dialogs["DarkLordDialog2"] = addDialog(GW_DIALOG, GH_DIALOG, "Let's fight for these wheels, Petrol!",
                                           1, Entities["DarkLord"], Textures["DialogSquare"])

    DialogL3_1 = {
        Dialogs["DarkLordDialog1"],
        Dialogs["PlayerDialog1"],
        Dialogs["DarkLordDialog2"],
    }
    DialogStateL3_1 = 1

    -- Camera
    setCameraBounds(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)
    attachCamera(Player)

    -- Music
    playMusic(Music["Ambient3"])
end
---- <<<< Enter

---- >>>> Update
function onUpdateL1(dt)
    handleInput()
end

function onUpdateL3(dt)
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
    if Player and PlayerControllable then
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

function switchLocation(funName)
    -- Set defaults
    Entities = {}
    Triggers = {}
    Dialogs = {}
    Player = nil
    PlayerControllable = true

    -- Switch
    hostSwitchLocation(funName)
end
---- <<<< Update

---- >>>> Render
function onRenderL1()
    -- Background
    drawFrame(RENDER_MODE_BACKGROUND, 0, false, 0,0,SCREEN_WIDTH*2,SCREEN_HEIGHT, Textures["Parallax"], 0, 0)
    drawFrame(RENDER_MODE_BACKGROUND, 1, false, 0,0,SCREEN_WIDTH,SCREEN_HEIGHT, Textures["Background1"], 0, 0)
    drawFrame(RENDER_MODE_BACKGROUND, 1, false, SCREEN_WIDTH,0,SCREEN_WIDTH,SCREEN_HEIGHT, Textures["Background1"], 0, 1)

    -- DEBUG(sean)
    setDrawColor(255, 255, 255, 255)
    X,Y = getCameraPosition()
    drawText(RENDER_MODE_DEBUG, 0, true, 0,0,10,3, string.format("%d %d", X, Y))

    -- Debug draw trigger
    if hasWorldEntity(Triggers["SwitchLocation"]) then
        local X,Y = getEntityPosition(Triggers["SwitchLocation"])
        local X1,Y1,X2,Y2 = getEntityHitBox(Triggers["SwitchLocation"])
        local W = -X1 + X2
        local H = -Y1 + Y2
        X = X + X1
        Y = Y + Y1
        setDrawColor(255, 0, 0, 255)
        drawRect(RENDER_MODE_DEBUG, 0, false, X,Y,W,H)
    end
end

function onRenderL3()
    -- Background
    drawFrame(RENDER_MODE_BACKGROUND, 0, false, 0,0,SCREEN_WIDTH,SCREEN_HEIGHT, Textures["Background3"], 0, 0)
    drawFrame(RENDER_MODE_BACKGROUND, 1, false, 42,45,68,20, Textures["BrownTrashCar"], 0, 0)
end
---- <<<< Render

---- >>>> Triggers
function triggerSwitchLocation(Entity)
    GT_LOG(PR_NOTE, "SwitchLocation triggerred")
    switchLocation("onEnterL3")
end
---- <<<< Triggers

---- >>>> AI States
function statePlayerDialog(Actor)
    if DialogStateL3_1 == 2 then
        if hasWorldEntity(DialogL3_1[DialogStateL3_1]) then
            runDialog(DialogL3_1[DialogStateL3_1])
        else
            DialogStateL3_1 = DialogStateL3_1 + 1
        end
    elseif DialogStateL3_1 > 3 then
        setActorState(Player, nil)
        PlayerControllable = true
    end
end

function stateDarkLordDialog(Actor)
    if DialogStateL3_1 == 1 or DialogStateL3_1 == 3 then
        if hasWorldEntity(DialogL3_1[DialogStateL3_1]) then
            runDialog(DialogL3_1[DialogStateL3_1])
        else
            DialogStateL3_1 = DialogStateL3_1 + 1
        end
    elseif DialogStateL3_1 > 3 then
        setActorState(Actor, States["KillPlayer"])
    end
end

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
---- <<<< AI States

