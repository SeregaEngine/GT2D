----------------------------------------------------------------------
--| * GarageBlueprint.lua *
--|
--| Contains all stuff for garage missions
----------------------------------------------------------------------

---- Includes
dofile "Scripts/MissionDefines.lua"

---- Defines
ACTOR_TEAM_FRIENDS = ACTOR_TEAM_DEFAULT + 1

---- Resources
Textures["Background"] = Graphics.defineTexture("Textures/Locations/Mission0-1.png", TW_LOCATION, TH_LOCATION)
Textures["Player"] = Graphics.defineTexture("Textures/Actors/Player.png", TW_ACTOR, TH_ACTOR)
Textures["Zhenek"] = Graphics.defineTexture("Textures/Actors/Zhenek.png", TW_ACTOR, TH_ACTOR)
Textures["Anthony"] = Graphics.defineTexture("Textures/Actors/Anthony.png", TW_ACTOR, TH_ACTOR)
Textures["PlaceholderCar"] = Graphics.defineTexture("Textures/Cars/TrashCar.png", TW_CAR, TH_CAR)

Anims["SlowMoving"] = Animation.define(1, 5, 1000.0 / 13.5)
Anims["RepairCar"] = Animation.define(4, 2, 1000.0 / 1)
Anims["TakeInstruments"] = Animation.define(5, 2, 1000.0 / 1)

States["UpCar"] = AI.defineState("stateUpCar")
States["TakeInstruments"] = AI.defineState("stateTakeInstruments")
States["RandomTalk"] = AI.defineState("stateRandomTalk")
States["RepairCar"] = AI.defineState("stateRepairCar")

---- Required functions
function onGarageEnter()
    -- Entities
    Player = Actor:new(GW_LOCATION - GW_ACTOR, GH_LOCATION - GH_ACTOR, GW_ACTOR, GH_ACTOR, Textures["Player"])
    local XDefault,YDefault = Player:getSpeed()
    Player:setSpeed(XDefault/1.75, YDefault/2)
    Player:setActorAnim(ACTOR_ANIMATION_HORIZONTAL, Anims["SlowMoving"])
    Player:setTeam(ACTOR_TEAM_FRIENDS)
    Player:setWeapon(Weapons["Fist"])

    Zhenek = Actor:new(85, 47, GW_ACTOR, GH_ACTOR, Textures["Zhenek"])
    Zhenek:setSpeed(XDefault/1.75, YDefault/2)
    Zhenek:setActorAnim(ACTOR_ANIMATION_HORIZONTAL, Anims["SlowMoving"])
    Zhenek:setTeam(ACTOR_TEAM_FRIENDS)
    Zhenek:turnLeft()
    IsZhenekBusy = false -- Change this when you cut-scene require Zhenek

    Anthony = Actor:new(50, 50, GW_ACTOR, GH_ACTOR, Textures["Anthony"])
    Anthony:setSpeed(XDefault/2, YDefault/2)
    Anthony:setActorAnim(ACTOR_ANIMATION_HORIZONTAL, Anims["SlowMoving"])
    Anthony:setTeam(ACTOR_TEAM_FRIENDS)
    Anthony:setState(States["UpCar"])
    Anthony:turnLeft()

    Dodge = Car:new(25, 50, 65, 20, Textures["PlaceholderCar"])
    Dodge:setRenderMode(RENDER_MODE_FOREGROUND)
    Dodge:setZIndex(-1)
    Dodge:setMaxSpeed(0, 0.005)
    Dodge:setAcceleration(0, -0.000001)

    -- Cutscenes
    TakeInstruments = {
        { Anthony, true, GTT_GOTO, 63, 47.5 },
        { Anthony, true, GTT_ANIMATE_FOR, Anims["TakeInstruments"], math.random(2000, 5000) },
        { Anthony, true, GTT_PUSH_COMMAND, GTC_MOVE_IDLE },
        { Anthony, true, GTT_WAIT, 500.0 },
    }
    TakeInstrumentsStage = 0

    RepairCar = {
        { Anthony, true, GTT_GOTO, 25, 53 },
        { Anthony, true, GTT_PUSH_COMMAND, GTC_TURN_RIGHT },
        { Anthony, true, GTT_ANIMATE_FOR, Anims["RepairCar"], math.random(5000, 15000) },
        { Anthony, true, GTT_PUSH_COMMAND, GTC_MOVE_IDLE },
        { Anthony, true, GTT_WAIT, 500.0 },
    }
    RepairCarStage = 0

    RandomTalk = {}
    RandomTalkStage = 0

    -- Ground
    GROUND_WIDTH = GW_LOCATION
    GROUND_HEIGHT = 18
    GROUND_X = 0
    GROUND_Y = GH_LOCATION - GROUND_HEIGHT

    Mission.setGroundBounds({ GROUND_X, GROUND_Y, GROUND_WIDTH, GROUND_HEIGHT })

    -- Camera
    Camera.setBounds({ 0, 0, GW_LOCATION, GH_LOCATION })
    Camera.setPosition(0, 0)
end

function onGarageRender()
    Graphics.drawFrame(RENDER_MODE_BACKGROUND, 0, false, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, Textures["Background"], 0, 0)
end

---- Internal functions
function stateUpCar(TActor)
    local X,Y = Dodge:getPosition()

    if Y >= 44 and Y <= 45 then
        Dodge:setAcceleration(0, 0.0000003)
    elseif Y <= 40 then
        Dodge:setPosition(25, 40)
        Dodge:setMaxSpeed(0, 0)
        TActor:setState(States["TakeInstruments"])
    end
end

stateTakeInstruments = Cutscene.new(
    function()
        return TakeInstruments
    end,
    function(Change)
        TakeInstrumentsStage = TakeInstrumentsStage + Change
        return TakeInstrumentsStage
    end,
    function(TActor)
    end,
    function(TActor)
        TakeInstruments[2][5] = math.random(2000, 5000)
        TakeInstrumentsStage = 0

        if not IsZhenekBusy and math.random(0, 1) == 1 then
            TActor:setState(States["RandomTalk"])
        else
            TActor:setState(States["RepairCar"])
        end
    end
)

stateRepairCar = Cutscene.new(
    function()
        return RepairCar
    end,
    function(Change)
        RepairCarStage = RepairCarStage + Change
        return RepairCarStage
    end,
    function(TActor)
    end,
    function(TActor)
        RepairCar[2][5] = math.random(5000, 15000) -- Wait time
        RepairCarStage = 0
        TActor:setState(States["TakeInstruments"])
    end
)

stateRandomTalk = Cutscene.new(
    function()
        return RandomTalk
    end,
    function(Change)
        RandomTalkStage = RandomTalkStage + Change
        return RandomTalkStage
    end,
    function(TActor)
        local Res = math.random(1, 2)
        if Res == 1 then
            RandomTalk = {
                { Anthony, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Sometimes i want to change my job", 4, Anthony, Textures["DialogSquare"]) },
                { Zhenek, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Your problems.", 1.5, Zhenek, Textures["DialogSquare"]) },
                { Anthony, true, GTT_WAIT, 1000 }
            }
        elseif Res == 2 then
            RandomTalk = {
                { Anthony, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "How you doing, bruh?", 3, Anthony, Textures["DialogSquare"]) },
                { Zhenek, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Can..", 0.5, Zhenek, Textures["DialogSquare"]) },
                { Zhenek, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "You..", 0.5, Zhenek, Textures["DialogSquare"]) },
                { Zhenek, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "PhIl MaHaAar", 2.5, Zhenek, Textures["DialogSquare"]) },
                { Anthony, true, GTT_WAIT, 1000 }
            }
        end
    end,
    function(TActor)
        RandomTalkStage = 0
        TActor:setState(States["RepairCar"])
    end
)
