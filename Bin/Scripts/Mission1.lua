-- Includes
dofile "Scripts/GraphicsDefines.lua"

-- Defines
DEBUG = false

local GROUND_WIDTH
local GROUND_HEIGHT
local GROUND_X
local GROUND_Y

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
    onEnterL4()
end

function defineResources()
    -- Textures
    Textures["Blank"] = defineTexture("Textures/Special/Blank.png", 1, 1)

    Textures["Background1"] = defineTexture("Textures/Locations/Mission1-1.png", TW_LOCATION, TH_LOCATION)
    Textures["Background2"] = defineTexture("Textures/Locations/Mission1-2.png", TW_LOCATION, TH_LOCATION)
    Textures["Background3"] = defineTexture("Textures/Locations/Mission1-3.png", TW_LOCATION, TH_LOCATION)
    Textures["Parallax"] = defineTexture("Textures/Locations/Mission1-1_Parallax.png", TW_PARALLAX, TH_PARALLAX)

    Textures["Pickup"] = defineTexture("Textures/Cars/Pickup.png", TW_CAR, TH_CAR)
    Textures["PoliceCar"] = defineTexture("Textures/Cars/PoliceCar.png", TW_CAR, TH_CAR)
    Textures["TrashCar"] = defineTexture("Textures/Cars/TrashCar.png", TW_CAR, TH_CAR)
    Textures["BrownTrashCar"] = defineTexture("Textures/Cars/BrownTrashCar.png", TW_CAR, TH_CAR)
    Textures["BrownTrashCarWithWheels"] = defineTexture("Textures/Cars/BrownTrashCarWithWheels.png", TW_CAR, TH_CAR)

    Textures["Player"] = defineTexture("Textures/Actors/Player.png", TW_ACTOR, TH_ACTOR)
    Textures["DarkLord"] = defineTexture("Textures/Actors/DarkLord.png", TW_ACTOR, TH_ACTOR)
    Textures["Zhenek"] = defineTexture("Textures/Actors/Zhenek.png", TW_ACTOR, TH_ACTOR)
    Textures["Serega"] = defineTexture("Textures/Actors/Serega.png", TW_ACTOR, TH_ACTOR)
    Textures["John"] = defineTexture("Textures/Actors/John.png", TW_ACTOR, TH_ACTOR)

    Textures["DialogSquare"] = defineTexture("Textures/DialogBox/Square.png", TW_DIALOG, TH_DIALOG)
    Textures["DialogCloud"] = defineTexture("Textures/DialogBox/Cloud.png", TW_DIALOG, TH_DIALOG)

    Textures["Wheels"] = defineTexture("Textures/Props/Wheels.png", TW_PROP, TH_PROP)

    -- Sounds
    Sounds["Punch1"] = defineSound("Sounds/Punch1.wav")
    Sounds["Punch2"] = defineSound("Sounds/Punch2.wav")
    Sounds["Punch3"] = defineSound("Sounds/Punch3.wav")
    Sounds["Punch4"] = defineSound("Sounds/Punch4.wav")
    Sounds["ActorDeath"] = defineSound("Sounds/ActorDyingSound.wav")
    Sounds["OpenGate"] = defineSound("Sounds/MetalGateOpening.wav")
    Sounds["CarDoor"] = defineSound("Sounds/CarDoorOpening.wav")
    Sounds["StartEngine"] = defineSound("Sounds/DodgeEngineStart.wav")
    Sounds["PickupThrottling"] = defineSound("Sounds/PickupThrottling.wav")
    Sounds["Police"] = defineSound("Sounds/PoliceScenario.wav")

    -- Music
    Music["Ambient1"] = defineMusic("Music/VnatureBgSound.wav")
    Music["Ambient3"] = defineMusic("Music/MainGarageAmbient.wav")

    -- Animations
    Anims["Attack"] = defineAnimation(4, 3, 1000.0 / 2.0)
    Anims["ZhenekDriving"] = defineAnimation(4, 2, 1000.0 / 0.5)
    Anims["DarkLordDead"] = defineAnimation(5, 3, 1000.0 / 2)
    Anims["PlayerDead"] = defineAnimation(5, 3, 1000.0 / 2)

    -- Weapons
    Weapons["Fist"] = defineWeapon(Anims["Attack"], 4, 8, 8, 1.0, Sounds["Punch1"], Sounds["Punch2"], Sounds["Punch3"], Sounds["Punch4"])

    -- States
    States["PlayerComing"] = defineState("statePlayerComing")
    States["PlayerDialog"] = defineState("statePlayerDialog")
    States["DarkLordDialog"] = defineState("stateDarkLordDialog")
    States["KillPlayer"] = defineState("stateKillPlayer")
    States["PlayerFightingForWheels"] = defineState("statePlayerFightingForWheels")
    States["PlayerTakeWheels"] = defineState("statePlayerTakeWheels")
    States["PlayerLeavingGarage"] = defineState("statePlayerLeavingGarage")
    States["PlayerLeaving"] = defineState("statePlayerLeaving")
    States["SeregaDriving"] = defineState("stateSeregaDriving")
    States["PoliceDialog"] = defineState("statePoliceDialog")
    States["PoliceGoToHouse"] = defineState("statePoliceGoToHouse")
end

function onEnterL1()
    -- Functions
    onUpdate = onUpdateL1
    onRender = onRenderL1

    -- Local defines
    GROUND_WIDTH = SCREEN_WIDTH * 2
    GROUND_HEIGHT = 19
    GROUND_X = 0
    GROUND_Y = SCREEN_HEIGHT - GROUND_HEIGHT

    -- Level
    setGroundBounds(GROUND_X, GROUND_Y, GROUND_WIDTH, GROUND_HEIGHT)

    -- Entities
    Entities["Player"] = addActor(45, 50, GW_ACTOR, GH_ACTOR, Textures["Player"])
    toggleActorGodMode(Entities["Player"], true)
    setActorWeapon(Entities["Player"], Weapons["Fist"])
    Player = Entities["Player"]

    Entities["Zhenek"] = addActor(0, 0, GW_ACTOR, GH_ACTOR, Textures["Zhenek"])
    toggleActorGodMode(Entities["Zhenek"], true)
    setActorAnim(Entities["Zhenek"], ACTOR_ANIMATION_INCAR, Anims["ZhenekDriving"])

    local Dialog = addDialog(GW_DIALOG, GH_DIALOG, "I'll wait you", 1, Entities["Zhenek"], Textures["DialogSquare"])
    setEntityZIndex(Dialog, 1)
    runDialog(Dialog)

    Entities["Car"] = addCar(30, 64, 90, 30, Textures["Pickup"])
    setCarPlacePosition(Entities["Car"], 0, 6, -5)
    putActorInCar(Entities["Zhenek"], Entities["Car"], 0)

    Triggers["SwitchLocation"] = addTrigger(GROUND_WIDTH - 80, GROUND_Y + 30, 20, 100, Player, "triggerPlayerComing")

    -- States
    PlayerComing = {
        { ["Task"] = GTT_GOTO, ["X"] = 185, ["Y"] = 50 },
        { ["Task"] = GTT_GOTO, ["X"] = 185, ["Y"] = 35 },
        { ["Task"] = GTT_WAIT, ["Duration"] = 1000 },
        { ["Task"] = GTT_NONE }
    }
    PlayerComingState = 0
    FadeTicks = 0

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
    GROUND_WIDTH = SCREEN_WIDTH - 10
    GROUND_HEIGHT = 10
    GROUND_X = 7
    GROUND_Y = SCREEN_HEIGHT - GROUND_HEIGHT

    -- Level
    setGroundBounds(GROUND_X, GROUND_Y, GROUND_WIDTH, GROUND_HEIGHT)

    -- Entities
    Entities["Player"] = addActor(SCREEN_WIDTH - 20, 64, TW_ACTOR, TH_ACTOR, Textures["Player"])
    Player = Entities["Player"]
    PlayerControllable = false
    setActorDeathSound(Player, Sounds["ActorDeath"])
    setActorAnim(Player, ACTOR_ANIMATION_DEAD, Anims["PlayerDead"])
    setActorWeapon(Player, Weapons["Fist"])
    setActorState(Player, States["PlayerDialog"])
    toggleActorGodMode(Player, true)
    turnActorLeft(Player)

    Entities["DarkLord"] = addActor(20, 60, GW_ACTOR, GH_ACTOR, Textures["DarkLord"])
    setActorAnim(Entities["DarkLord"], ACTOR_ANIMATION_DEAD, Anims["DarkLordDead"])
    setActorDeathSound(Entities["DarkLord"], Sounds["ActorDeath"])
    setActorWeapon(Entities["DarkLord"], Weapons["Fist"])
    setActorState(Entities["DarkLord"], States["DarkLordDialog"])
    turnActorLeft(Entities["DarkLord"])

    Entities["Pamella"] = addActor(28, 55, GW_ACTOR, GH_ACTOR, Textures["Blank"])
    setActorAnim(Entities["Pamella"], ACTOR_ANIMATION_IDLE, nil) -- No anims

    Entities["Car"] = addEntity(76, 55, 68, 20, Textures["BrownTrashCarWithWheels"])
    setEntityRenderMode(Entities["Car"], RENDER_MODE_BACKGROUND)
    setEntityZIndex(Entities["Car"], 3)

    -- Dialogs
    Dialogs["DarkLordDialog1"] = addDialog(GW_DIALOG, GH_DIALOG, "Hmm?", 1, Entities["DarkLord"], Textures["DialogSquare"])
    Dialogs["DarkLordDialog2"] = addDialog(GW_DIALOG, GH_DIALOG, "What the hell? Who are you?!", 1, Entities["DarkLord"], Textures["DialogSquare"])
    Dialogs["DarkLordDialog3"] = addDialog(GW_DIALOG, GH_DIALOG, "Pamella!!!", 1, Entities["DarkLord"], Textures["DialogSquare"])
    Dialogs["DarkLordDialog4"] = addDialog(GW_DIALOG, GH_DIALOG, "Call the police! There's a bum in our garage", 1, Entities["DarkLord"], Textures["DialogSquare"])
    Dialogs["DarkLordDialog5"] = addDialog(GW_DIALOG, GH_DIALOG, "I'm not gonna give you my wheels, asshole!", 1, Entities["DarkLord"], Textures["DialogSquare"])
    Dialogs["DarkLordKilledPlayer"] = addDialog(GW_DIALOG, GH_DIALOG, "You shouldn't have come", 1, Entities["DarkLord"], Textures["DialogSquare"])
    Dialogs["PlayerDialog1"] = addDialog(GW_DIALOG, GH_DIALOG, "I came for your wheels, dawg", 1, Player, Textures["DialogSquare"])
    Dialogs["PlayerDialogAfterFight"] = addDialog(GW_DIALOG, GH_DIALOG, "I should take these wheels and run away from here", 1, Player, Textures["DialogSquare"])
    Dialogs["PamellaAsking"] = addDialog(GW_DIALOG, GH_DIALOG, "Honey?", 1, Entities["Pamella"], Textures["DialogSquare"])

    DialogL3_1 = {
        Dialogs["DarkLordDialog1"],
        Dialogs["DarkLordDialog2"],
        Dialogs["PlayerDialog1"],
        Dialogs["DarkLordDialog3"],
        Dialogs["DarkLordDialog4"],
        Dialogs["DarkLordDialog5"],
    }
    DialogStateL3_1 = 0

    -- States
    TriggerToWheel = {}
    DarkLordDialogTicks = 0
    FadeTicks = 0

    -- Camera
    setCameraBounds(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)
    attachCamera(Player)

    -- Music
    playMusic(Music["Ambient3"])
end

function onEnterL4()
    -- Functions
    onUpdate = onUpdateL4
    onRender = onRenderL4

    -- Local defines
    GROUND_WIDTH = SCREEN_WIDTH * 2
    GROUND_HEIGHT = 19
    GROUND_X = 0
    GROUND_Y = SCREEN_HEIGHT - GROUND_HEIGHT

    -- Level
    setGroundBounds(GROUND_X, GROUND_Y, GROUND_WIDTH, GROUND_HEIGHT)

    -- Entities
    Entities["Player"] = addActor(185, 35, GW_ACTOR, GH_ACTOR, Textures["Player"])
    toggleEntityCollidable(Entities["Player"], false)
    setActorWeapon(Entities["Player"], Weapons["Fist"])
    setActorState(Entities["Player"], States["PlayerLeaving"])
    Player = Entities["Player"]
    PlayerControllable = false

    Entities["Zhenek"] = addActor(0, 0, GW_ACTOR, GH_ACTOR, Textures["Zhenek"])
    setActorAnim(Entities["Zhenek"], ACTOR_ANIMATION_INCAR, Anims["ZhenekDriving"])

    Entities["Serega"] = addActor(0, 0, GW_ACTOR, GH_ACTOR, Textures["Serega"])
    toggleEntityCollidable(Entities["Serega"], false)
    local X, Y = getActorSpeed(Entities["Serega"])
    setActorSpeed(Entities["Serega"], X/1.75, Y/1.75)
    setActorState(Entities["Serega"], States["SeregaDriving"])
    setActorTask(Entities["Serega"], GTT_WAIT, 5000) -- Don't check car velocity 5 seconds

    Entities["John"] = addActor(0, 0, GW_ACTOR, GH_ACTOR, Textures["John"])
    toggleEntityCollidable(Entities["John"], false)
    setActorSpeed(Entities["John"], X/2.25, Y/2.25)

    Entities["Car"] = addCar(SCREEN_WIDTH + 75, 66, 90, 30, Textures["Pickup"])
    setCarMaxSpeed(Entities["Car"], 0.075, 0)
    setCarPlacePosition(Entities["Car"], 0, 6, -5)
    setCarPlacePosition(Entities["Car"], 1, 10, -5)
    turnCarLeft(Entities["Car"])
    putActorInCar(Entities["Zhenek"], Entities["Car"], 0)

    Entities["PoliceCar"] = addCar(SCREEN_WIDTH*12, 66, 90, 32, Textures["PoliceCar"])
    setCarMaxSpeed(Entities["PoliceCar"], 0.135, 0)
    setCarAcceleration(Entities["PoliceCar"], -1, 0)
    setCarPlacePosition(Entities["PoliceCar"], 0, 0, -4)
    setCarPlacePosition(Entities["PoliceCar"], 1, 7, -3)
    turnCarLeft(Entities["PoliceCar"])
    putActorInCar(Entities["Serega"], Entities["PoliceCar"], 0)
    putActorInCar(Entities["John"], Entities["PoliceCar"], 1)

    -- Triggers
    Triggers["PoliceStop"] = addTrigger(SCREEN_WIDTH*2.3, SCREEN_HEIGHT/2, 1, SCREEN_HEIGHT, Entities["PoliceCar"], "triggerPoliceStop")

    -- Dialogs
    Dialogs["ZhenekJump"] = addDialog(GW_DIALOG, GH_DIALOG, "Petrol! Jump in", 1, Entities["Zhenek"], Textures["DialogSquare"])

    Dialogs["Police1"] = addDialog(GW_DIALOG, GH_DIALOG, "I don't like it.", 1, Entities["John"], Textures["DialogSquare"])
    Dialogs["Police2"] = addDialog(GW_DIALOG, GH_DIALOG, "C'mon, John! Are you a little girl?", 1, Entities["Serega"], Textures["DialogSquare"])
    Dialogs["Police3"] = addDialog(GW_DIALOG, GH_DIALOG, "I am a grown forty-year-old divorced man with two children and...", 1, Entities["John"], Textures["DialogSquare"])
    Dialogs["Police4"] = addDialog(GW_DIALOG, GH_DIALOG, "a loan for a house that I have been giving for 10 years", 1, Entities["John"], Textures["DialogSquare"])
    Dialogs["Police5"] = addDialog(GW_DIALOG, GH_DIALOG, "I wish i had peace...", 1, Entities["John"], Textures["DialogSquare"])
    Dialogs["Police6"] = addDialog(GW_DIALOG, GH_DIALOG, "Just shut up and let's go", 1, Entities["Serega"], Textures["DialogSquare"])

    DialogL4_1 = {
        Dialogs["Police1"],
        Dialogs["Police2"],
        Dialogs["Police3"],
        Dialogs["Police4"],
        Dialogs["Police5"],
        Dialogs["Police6"],
    }
    DialogStateL4_1 = 1

    -- States
    FadeTicks = 0

    PlayerLeaving = {
        { ["Task"] = GTT_GOTO, ["X"] = 185, ["Y"] = 60 },
        { ["Task"] = GTT_WAIT, ["Duration"] = 1000 },
        { ["Task"] = GTT_GOTO, ["X"] = 195, ["Y"] = 60 },
        { ["Task"] = GTT_WAIT, ["Duration"] = 350 },
        { ["Task"] = GTT_NONE }
    }
    PlayerLeavingState = 0

    PoliceGoToHouse = {
        { ["Task"] = GTT_GOTO, ["X"] = 185, ["Y"] = 55 },
        { ["Task"] = GTT_GOTO, ["X"] = 180, ["Y"] = 40 },
        { ["Task"] = GTT_GOTO, ["X"] = 165, ["Y"] = 25 },
        { ["Task"] = GTT_NONE }
    }
    PoliceGoToHouseState = 0

    -- Camera
    setCameraBounds(0, 0, GROUND_WIDTH, SCREEN_HEIGHT)
    attachCamera(Player)
    detachCamera() -- Leave camera near player

    -- Music
    playMusic(Music["Ambient1"])
    playSound(Sounds["Police"])
end
---- <<<< Enter

---- >>>> Update
function onUpdateL1(dt)
    handleInput()
end

function onUpdateL3(dt)
    handleInput()
end

function onUpdateL4(dt)
    handleInput()

    if DEBUG then
		setDrawColor(255, 255, 255, 255)
		local X,Y = getEntityPosition(Entities["PoliceCar"])
		drawText(RENDER_MODE_DEBUG, 999, true, 0,0,10,2, string.format("%.1f", X))

		X,Y = getEntityVelocity(Entities["PoliceCar"])
		drawText(RENDER_MODE_DEBUG, 999, true, 0,2,10,2, string.format("%.1f", X))
    end
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
    -- Parallax
    X,Y = getCameraPosition()
    drawFrame(RENDER_MODE_BACKGROUND, 0, true, -X/2,-Y/2,GW_PARALLAX,GH_PARALLAX, Textures["Parallax"], 0, 0)

    -- Background
    drawFrame(RENDER_MODE_BACKGROUND, 1, false, 0,0,SCREEN_WIDTH,SCREEN_HEIGHT, Textures["Background1"], 0, 0)
    drawFrame(RENDER_MODE_BACKGROUND, 1, false, SCREEN_WIDTH,0,SCREEN_WIDTH,SCREEN_HEIGHT, Textures["Background1"], 0, 1)
end

function onRenderL3()
    -- Background
    drawFrame(RENDER_MODE_BACKGROUND, 0, false, 0,0,SCREEN_WIDTH,SCREEN_HEIGHT, Textures["Background3"], 0, 0)
end

function onRenderL4()
    -- Parallax
    X,Y = getCameraPosition()
    drawFrame(RENDER_MODE_BACKGROUND, 0, true, -X/2,-Y/2,GW_PARALLAX,GH_PARALLAX, Textures["Parallax"], 0, 0)

    -- Background
    drawFrame(RENDER_MODE_BACKGROUND, 1, false, 0,0,SCREEN_WIDTH,SCREEN_HEIGHT, Textures["Background1"], 0, 0)
    drawFrame(RENDER_MODE_BACKGROUND, 1, false, SCREEN_WIDTH,0,SCREEN_WIDTH,SCREEN_HEIGHT, Textures["Background1"], 0, 1)

    -- Fade
    setDrawColor(0, 0, 0, 20)
    fillRect(RENDER_MODE_BACKGROUND, 2, true, 0,0,SCREEN_WIDTH,SCREEN_HEIGHT)
end
---- <<<< Render

---- >>>> Triggers
function triggerPlayerComing(Trigger, Entity)
    setActorState(Entity, States["PlayerComing"])
end

function triggerTakeWheel(Trigger, Entity)
    removeEntity(TriggerToWheel[Trigger])
end

function triggerPlayerLeavingGarage(Trigger, Entity)
    PlayerControllable = false
    local X,Y = getEntityPosition(Entity)
    setActorTask(Entity, GTT_GOTO, 300.0, Y)
    setActorState(Entity, States["PlayerLeavingGarage"])
end

function triggerPoliceStop(Trigger, Entity)
    GT_LOG(PR_NOTE, "Stop!")
    setCarAcceleration(Entity, 0.00006, 0)
end
---- <<<< Triggers

---- >>>> AI States
function statePlayerComing(Actor)
    Task = getActorCurrentTask(Actor)
    Status = checkActorTask(Actor)

    if PlayerComingState == 0 then
        FadeTicks = getTicks()
        PlayerControllable = false
        toggleEntityCollidable(Player, false)
    end

    local Alpha = (getTicks() - FadeTicks) * 0.2
    if Alpha > 255 then
        Alpha = 255
    end
    setDrawColor(0, 0, 0, math.floor(Alpha))
    fillRect(RENDER_MODE_FOREGROUND, 999, true, 0,0,SCREEN_WIDTH,SCREEN_HEIGHT)

    if Status == GTT_DONE or PlayerComingState == 0 then
        PlayerComingState = PlayerComingState + 1

        if PlayerComing[PlayerComingState].Task == GTT_NONE then
            if Alpha < 255 then
                PlayerComingState = PlayerComingState - 1
                return
            end

			switchLocation("onEnterL3")
            return
        end

        if PlayerComing[PlayerComingState].Task == GTT_WAIT then
            playSound(Sounds["OpenGate"])
        end

        if PlayerComing[PlayerComingState].Task == GTT_GOTO then
			setActorTask(Actor, PlayerComing[PlayerComingState].Task, PlayerComing[PlayerComingState].X, PlayerComing[PlayerComingState].Y)
        elseif PlayerComing[PlayerComingState].Task == GTT_WAIT then
			setActorTask(Actor, PlayerComing[PlayerComingState].Task, PlayerComing[PlayerComingState].Duration)
		end
    end
end

function statePlayerDialog(Actor)
    if DialogStateL3_1 == 3 then
        if hasWorldEntity(DialogL3_1[DialogStateL3_1]) then
            runDialog(DialogL3_1[DialogStateL3_1])
        else
            DialogStateL3_1 = DialogStateL3_1 + 1
        end
    elseif DialogStateL3_1 > #DialogL3_1 then
        setActorState(Player, States["PlayerFightingForWheels"])
        PlayerControllable = true
    end
end

function stateDarkLordDialog(Actor)
    -- Handle dialog
    if (DialogStateL3_1 >= 1 and DialogStateL3_1 <= 2) or (DialogStateL3_1 >= 4 and DialogStateL3_1 <= 6) then
        if hasWorldEntity(DialogL3_1[DialogStateL3_1]) then
            runDialog(DialogL3_1[DialogStateL3_1])
        else
            DialogStateL3_1 = DialogStateL3_1 + 1
        end
    elseif DialogStateL3_1 > #DialogL3_1 then
        setActorState(Actor, States["KillPlayer"])
        return
    end

    -- Handle behaviour
    if DialogStateL3_1 == 0 then
        if DarkLordDialogTicks == 0 then
            DarkLordDialogTicks = getTicks()
        end

        if getTicks() - DarkLordDialogTicks >= 1000 then
            DialogStateL3_1 = 1
            turnActorRight(Actor)
        end
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
            runDialog(Dialogs["DarkLordKilledPlayer"])
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

function statePlayerFightingForWheels(Actor)
    -- Waiting for Dark Lord's death
    if isActorAlive(Entities["DarkLord"]) then
        return
    end

    -- Run and wait for dialogs
    if hasWorldEntity(Dialogs["PamellaAsking"]) then
        runDialog(Dialogs["PamellaAsking"])
        return
    end

    if hasWorldEntity(Dialogs["PlayerDialogAfterFight"]) then
        runDialog(Dialogs["PlayerDialogAfterFight"])
        return
    end

    -- Fade off
    if FadeTicks == 0 then
        FadeTicks = getTicks()
    end

    local Elapsed = getTicks() - FadeTicks
    local Alpha = Elapsed * 0.5
    if Alpha <= 255 then
        setDrawColor(0, 0, 0, math.floor(Alpha))
        fillRect(RENDER_MODE_FOREGROUND, 999, true, 0,0,SCREEN_WIDTH,SCREEN_HEIGHT)
        return
    end

    -- Remove wheels from the car
    setEntityTexture(Entities["Car"], Textures["BrownTrashCar"])

    -- Add wheels and triggers
    for i = 1,4 do
        local X = 20 + GW_PROP * (i - 1)
        local Y = 60
        local Wheel = addEntity(X, Y, GW_PROP, GH_PROP, Textures["Wheels"])
        setEntityRenderMode(Wheel, RENDER_MODE_BACKGROUND)
        setEntityZIndex(Wheel, 10+i)

        TriggerToWheel[addTrigger(X, Y, GW_PROP/4, GH_PROP/4, Actor, "triggerTakeWheel")] = Wheel

        if i % 2 == 0 then
            setEntityAnimFrame(Wheel, 1)
        end
    end

    -- Leave this state and restore FadeTicks
    setActorState(Actor, States["PlayerTakeWheels"])
    FadeTicks = 0
end

function statePlayerTakeWheels(Actor)
    -- Wait for player taking wheels
    for k,v in pairs(TriggerToWheel) do
        if hasWorldEntity(v) then
            return
        end
    end

    -- Now player can leave garage
    setGroundBounds(GROUND_X, GROUND_Y, GROUND_WIDTH + 50, GROUND_HEIGHT)
    addTrigger(SCREEN_WIDTH, SCREEN_HEIGHT/2, GW_ACTOR, SCREEN_HEIGHT, Actor, "triggerPlayerLeavingGarage")

    setActorState(Actor, nil)
end

function statePlayerLeavingGarage(Actor)
    if FadeTicks == 0 then
        FadeTicks = getTicks()
    end

    local Elapsed = getTicks() - FadeTicks
    local Alpha = Elapsed * 0.2
    if Alpha > 255 or Elapsed > 3000 then
        Alpha = 255
        switchLocation("onEnterL4")
    end

    setDrawColor(0, 0, 0, math.floor(Alpha))
    fillRect(RENDER_MODE_FOREGROUND, 999, true, 0,0,SCREEN_WIDTH,SCREEN_HEIGHT)
end

function statePlayerLeaving(Actor)
    -- Init
    if PlayerLeavingState == 0 then
        FadeTicks = getTicks()
    end

    -- Fade
    local Elapsed = getTicks() - FadeTicks
    local Alpha = 255 - (Elapsed * 0.2)
    if Alpha > 0 then
        setDrawColor(0, 0, 0, math.floor(Alpha))
        fillRect(RENDER_MODE_FOREGROUND, 999, true, 0,0,SCREEN_WIDTH,SCREEN_HEIGHT)
    end

    if checkActorTask(Actor) == GTT_DONE or PlayerLeavingState == 0 then
        PlayerLeavingState = PlayerLeavingState + 1

        if PlayerLeavingState == 1 then
            playSound(Sounds["StartEngine"])
        elseif PlayerLeavingState == 2 then
            runDialog(Dialogs["ZhenekJump"])
        elseif PlayerLeavingState == 4 then
            playSound(Sounds["CarDoor"])
        end

        if PlayerLeaving[PlayerLeavingState].Task == GTT_NONE then
            -- Wait for fade in
            if Alpha > 0.0 then
                PlayerLeavingState = PlayerLeavingState - 1
                return
            end

            putActorInCar(Player, Entities["Car"], 1)
            setCarAcceleration(Entities["Car"], -0.0001, 0)
            playSound(Sounds["PickupThrottling"])

            FadeTicks = 0
            setActorTask(Actor, nil)
            setActorState(Actor, nil)
            return
        elseif PlayerLeaving[PlayerLeavingState].Task == GTT_GOTO then
            setActorTask(Actor, PlayerLeaving[PlayerLeavingState].Task, PlayerLeaving[PlayerLeavingState].X, PlayerLeaving[PlayerLeavingState].Y)
        elseif PlayerLeaving[PlayerLeavingState].Task == GTT_WAIT then
            setActorTask(Actor, PlayerLeaving[PlayerLeavingState].Task, PlayerLeaving[PlayerLeavingState].Duration)
        end
    end
end

function stateSeregaDriving(Actor)
    -- Wait
    if checkActorTask(Actor) ~= GTT_DONE then
        return
    end

    -- Handle velocity
    local X,Y = getEntityVelocity(Entities["PoliceCar"])
    if X > -0.04 then
        -- Stop car, start dialog
        setCarMaxSpeed(Entities["PoliceCar"], 0, 0)
        setActorTask(Actor, GTT_WAIT, 500)
        setActorState(Actor, States["PoliceDialog"])
    end
end

function statePoliceDialog(Actor)
    -- Wait task
    if checkActorTask(Actor) ~= GTT_DONE then
        return
    end

    -- Play dialog and eject from the car
    if hasWorldEntity(DialogL4_1[DialogStateL4_1]) then
        runDialog(DialogL4_1[DialogStateL4_1])
    else
        DialogStateL4_1 = DialogStateL4_1 + 1

        if DialogStateL4_1 > #DialogL4_1 then
            ejectActorFromCar(Entities["PoliceCar"], 0)
            ejectActorFromCar(Entities["PoliceCar"], 1)
            playSound(Sounds["CarDoor"])
            playSound(Sounds["CarDoor"])

            local X, Y = getEntityPosition(Entities["Serega"])
            setEntityPosition(Entities["Serega"], X, Y-5)
            setEntityPosition(Entities["John"], X+16, Y-5)
            setActorState(Actor, States["PoliceGoToHouse"])
        end
    end
end

function statePoliceGoToHouse(Actor)
    if PoliceGoToHouseState == 0 then
        FadeTicks = getTicks()
    end

    local Alpha = (getTicks() - FadeTicks) * 0.125
    if Alpha > 255 then
        GT_LOG(PR_NOTE, "Mission ended")
        setActorState(Actor, nil)
        return
    else
        setDrawColor(0, 0, 0, math.floor(Alpha))
        fillRect(RENDER_MODE_FOREGROUND, 999, true, 0,0,SCREEN_WIDTH,SCREEN_HEIGHT)
    end

    local Status = checkActorTask(Actor)
    if Status == GTT_DONE or PoliceGoToHouseState == 0 then
        PoliceGoToHouseState = PoliceGoToHouseState + 1
        setActorTask(Entities["Serega"], PoliceGoToHouse[PoliceGoToHouseState].Task, PoliceGoToHouse[PoliceGoToHouseState].X, PoliceGoToHouse[PoliceGoToHouseState].Y)
        setActorTask(Entities["John"], PoliceGoToHouse[PoliceGoToHouseState].Task, PoliceGoToHouse[PoliceGoToHouseState].X, PoliceGoToHouse[PoliceGoToHouseState].Y)
    end
end
---- <<<< AI States

