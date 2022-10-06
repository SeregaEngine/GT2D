----------------------------------------------------------------------
--| * Mission0.lua *
--|
--| First meeting with Mechanic "Zhenek" in
--| his garage after Petrol's car accident
----------------------------------------------------------------------

--[[ TODO
    -- Maybe make something like helper for states that do something?
]]--

---- Includes
dofile "Scripts/MissionDefines.lua"

---- Defines
ACTOR_TEAM_FRIENDS = ACTOR_TEAM_DEFAULT + 1

---- Globals
local GROUND_X
local GROUND_Y
local GROUND_WIDTH
local GROUND_HEIGHT

Zhenek = nil
Anthony = nil
Car = nil

IsZhenekBusy = false

---- Functions
function onEnter(Location)
    GT_LOG(PR_NOTE, "Mission 0 entered")

    -- Resources
    defineResources()

    -- Entities
    Player = addActor(GW_LOCATION - GW_ACTOR, GH_LOCATION - GH_ACTOR, GW_ACTOR, GH_ACTOR, Textures["Player"])
    local XDefault,YDefault = getActorSpeed(Player)
    setActorSpeed(Player, XDefault/1.75, YDefault/2)
    setActorAnim(Player, ACTOR_ANIMATION_MOVE_HORIZONTAL, Anims["SlowMoving"])
    setActorTeam(Player, ACTOR_TEAM_FRIENDS)
    setActorWeapon(Player, Weapons["Fist"])

    Zhenek = addActor(85, 47, GW_ACTOR, GH_ACTOR, Textures["Zhenek"])
    setActorSpeed(Zhenek, XDefault/2, YDefault/2)
    setActorAnim(Zhenek, ACTOR_ANIMATION_MOVE_HORIZONTAL, Anims["SlowMoving"])
    setActorTeam(Zhenek, ACTOR_TEAM_FRIENDS)
    turnActorLeft(Zhenek)

    Anthony = addActor(50, 50, GW_ACTOR, GH_ACTOR, Textures["Anthony"])
    setActorSpeed(Anthony, XDefault/2, YDefault/2)
    setActorAnim(Anthony, ACTOR_ANIMATION_MOVE_HORIZONTAL, Anims["SlowMoving"])
    setActorTeam(Anthony, ACTOR_TEAM_FRIENDS)
    setActorState(Anthony, States["UpCar"])
    turnActorLeft(Anthony)

    Car = addCar(25, 50, 65, 20, Textures["Car"])
    setEntityRenderMode(Car, RENDER_MODE_FOREGROUND)
    setEntityZIndex(Car, -1)
    setCarMaxSpeed(Car, 0, 0.005)
    setCarAcceleration(Car, 0, -0.000001)

    -- States
    TakeInstruments = {
        { GTT_GOTO, 63, 47.5 },
        { GTT_WAIT, 1000 },
    }
    TakeInstrumentsStage = 0

    RepairCar = {
        { GTT_GOTO, 25, 50 },
        { GTT_WAIT, 1000 }
    }
    RepairCarStage = 0

    -- Ground
    GROUND_WIDTH = GW_LOCATION
    GROUND_HEIGHT = 18
    GROUND_X = 0
    GROUND_Y = GH_LOCATION - GROUND_HEIGHT
    setGroundBounds(GROUND_X, GROUND_Y, GROUND_WIDTH, GROUND_HEIGHT)

    -- Camera
    setCameraBounds(0, 0, GW_LOCATION, GH_LOCATION)
    setCameraPosition(0, 0)
end

function defineResources()
    Textures["Background"] = defineTexture("Textures/Locations/Mission0-1.png", TW_LOCATION, TH_LOCATION)
    Textures["Player"] = defineTexture("Textures/Actors/Player.png", TW_ACTOR, TH_ACTOR)
    Textures["Zhenek"] = defineTexture("Textures/Actors/Zhenek.png", TW_ACTOR, TH_ACTOR)
    Textures["Anthony"] = defineTexture("Textures/Actors/John.png", TW_ACTOR, TH_ACTOR) -- Workaround
    Textures["Car"] = defineTexture("Textures/Cars/TrashCar.png", TW_CAR, TH_CAR)

    Anims["SlowMoving"] = defineAnimation(1, 5, 1000.0 / 13.5)

    States["UpCar"] = defineState("stateUpCar")
    States["TakeInstruments"] = defineState("stateTakeInstruments")
    States["RandomTalk"] = defineState("stateRandomTalk")
    States["RepairCar"] = defineState("stateRepairCar")
end

function onUpdate(dt)
    handleInput()
end

function onRender()
    drawFrame(RENDER_MODE_BACKGROUND, 0, false, 0,0,SCREEN_WIDTH,SCREEN_HEIGHT, Textures["Background"], 0, 0)
end

function stateUpCar(Actor)
    local X,Y = getEntityPosition(Car)

    if Y >= 44 and Y <= 45 then
        setCarAcceleration(Car, 0, 0.000001)
    elseif Y <= 40 then
        setEntityPosition(Car, 25, 40)
        setCarMaxSpeed(Car, 0, 0)
        setActorState(Actor, States["TakeInstruments"])
    end
end

function stateTakeInstruments(Actor)
    if TakeInstrumentsStage == 0 then

    end

    if checkActorTask(Actor) == GTT_DONE or TakeInstrumentsStage == 0 then
        TakeInstrumentsStage = TakeInstrumentsStage + 1

        if TakeInstrumentsStage == 2 then
            --playActorAnimation() ?
        elseif TakeInstrumentsStage > #TakeInstruments then
            if not IsZhenekBusy and math.random(0, 1) == 1 then
                setActorState(Actor, States["RandomTalk"])
            else
                setActorState(Actor, States["RepairCar"])
            end

            TakeInstrumentsStage = 0
            return
        end

        setActorTask(Actor, TakeInstruments[TakeInstrumentsStage][1], TakeInstruments[TakeInstrumentsStage][2], TakeInstruments[TakeInstrumentsStage][3])
    end
end

function stateRepairCar(Actor)
    if RepairCarStage == 0 then

    end

    if checkActorTask(Actor) == GTT_DONE or RepairCarStage == 0 then
        RepairCarStage = RepairCarStage + 1

        if RepairCarStage == 2 then
            --playActorAnimation() ?
        elseif RepairCarStage > #RepairCar then
			setActorState(Actor, States["TakeInstruments"])
            RepairCarStage = 0
            return
        end

        setActorTask(Actor, RepairCar[RepairCarStage][1], RepairCar[RepairCarStage][2], RepairCar[RepairCarStage][3])
    end
end

function stateRandomTalk(Actor)
    setActorState(Actor, States["RepairCar"])
end