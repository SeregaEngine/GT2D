----------------------------------------------------------------------
--| * Mission1.lua *
--|
--| Mission, where Petrol steals Dark Lord's wheels.
----------------------------------------------------------------------

---- Includes
require "Mission"

---- Resources
Textures["Background1"] = Resource.defineTexture("Textures/Locations/Mission1-1.png", TW_LOCATION, TH_LOCATION)
Textures["Parallax1"] = Resource.defineTexture("Textures/Locations/Mission1-1_Parallax.png", TW_LOCATION*2, TH_LOCATION)
Textures["Background2"] = Resource.defineTexture("Textures/Locations/Mission1-2.png", TW_LOCATION, TH_LOCATION)
Textures["Background3"] = Resource.defineTexture("Textures/Locations/Mission1-3.png", TW_LOCATION, TH_LOCATION)
Textures["Background4"] = Textures["Background1"]
Textures["Parallax4"] = Textures["Parallax1"]

Textures["Pickup"] = Resource.defineTexture("Textures/Cars/Pickup.png", TW_CAR, TH_CAR)
Textures["PoliceCar"] = Resource.defineTexture("Textures/Cars/PoliceCar.png", TW_CAR, TH_CAR)
Textures["TrashCar"] = Resource.defineTexture("Textures/Cars/BrownTrashCar.png", TW_CAR, TH_CAR)
Textures["TrashCarWheels"] = Resource.defineTexture("Textures/Cars/BrownTrashCarWithWheels.png", TW_CAR, TH_CAR)

Textures["Player"] = Resource.defineTexture("Textures/Actors/Player.png", TW_ACTOR, TH_ACTOR)
Textures["Zhenek"] = Resource.defineTexture("Textures/Actors/Zhenek.png", TW_ACTOR, TH_ACTOR)
Textures["DarkLord"] = Resource.defineTexture("Textures/Actors/DarkLord.png", TW_ACTOR, TH_ACTOR)
Textures["Serega"] = Resource.defineTexture("Textures/Actors/Serega.png", TW_ACTOR, TH_ACTOR)
Textures["John"] = Resource.defineTexture("Textures/Actors/John.png", TW_ACTOR, TH_ACTOR)

Textures["Wheels"] = Resource.defineTexture("Textures/Props/Wheels.png", TW_PROP, TH_PROP)

Sounds["OpenGate"] = Resource.defineSound("Sounds/MetalGateOpening.wav")
Sounds["PickupThrottling"] = Resource.defineSound("Sounds/PickupThrottling.wav")
Sounds["Police"] = Resource.defineSound("Sounds/PoliceScenario.wav")

Music["Ambient1"] = Resource.defineMusic("Music/VnatureBgSound.wav")
Music["Ambient2"] = Music["Ambient1"]
Music["Ambient3"] = Resource.defineMusic("Music/Mission1GarageAmbient.wav")
Music["Ambient4"] = Music["Ambient1"]

Anims["DarkLordDying"] = Resource.defineAnimation(5, 3, 1000.0 / 2)
Anims["PlayerDying"] = Resource.defineAnimation(5, 3, 1000.0 / 2)

Weapons["DarkLordFist"] = Resource.defineWeapon(Anims["DarkLordFist"], 8, 8, 10.0, Sounds["Punch1"], Sounds["Punch2"], Sounds["Punch3"], Sounds["Punch4"])

---- Globals
L1 = {}
L2 = {}
L3 = {}
L4 = {}

---- Mission
function Mission.onEnter(Location)
    GT_LOG(PR_NOTE, "Mission1 entered with " .. Location .. " location")

    if Location == 1 then
        L1.onEnter()
    elseif Location == 2 then
        L2.onEnter()
    elseif Location == 3 then
        L3.onEnter()
    elseif Location == 4 then
        L4.onEnter()
    else
        L1.onEnter()
    end
end

---- Location 1
function L1.onEnter()
    -- Functions
    Mission.onUpdate = L1.onUpdate
    Mission.onRender = L1.onRender

    -- Defines
    GROUND_WIDTH = SCREEN_WIDTH * 2
    GROUND_HEIGHT = 19
    GROUND_X = 0
    GROUND_Y = SCREEN_HEIGHT - GROUND_HEIGHT

    -- Entities
    BlankActor = Actor:new(0, 0, 0, 0, Textures["Blank"])

    Player = Actor:new(0, 0, GW_ACTOR, GH_ACTOR, Textures["Player"])
    Player:setWeapon(Weapons["Fist"])
    Player:setTeam(ACTOR_TEAM_FRIENDS)
    Player:setState("dialogInCar")

    Zhenek = Actor:new(0, 0, GW_ACTOR, GH_ACTOR, Textures["Zhenek"])
    Zhenek:setTeam(ACTOR_TEAM_FRIENDS)

    Pickup = Car:new(30, 68, 107, 30, Textures["Pickup"])
    Pickup:setPlacePosition(0, 15, -5)
    Pickup:setPlacePosition(1, 6, -5)
    Pickup:putActor(Player, 0)
    Pickup:putActor(Zhenek, 1)

    Trigger:new({ GROUND_WIDTH - 80, GROUND_Y + 30, 20, 100 }, Player, "playerComing")

    -- Triggers and Cutscenes
    L1.defineTriggers()
    L1.defineCutscenes()

    -- Level
    Mission.setGroundBounds({ GROUND_X, GROUND_Y, GROUND_WIDTH, GROUND_HEIGHT })
    Camera.setBounds({ 0, 0, GROUND_WIDTH, SCREEN_HEIGHT })
    Camera.attach(Player)

    Music["Ambient1"]:play()
end

function L1.onUpdate(dt)
    Input.defaultHandle()
end

function L1.onRender()
    -- Parallax
    X,Y = getCameraPosition()
    Graphics.drawFrame(RENDER_MODE_BACKGROUND, 0, true, { -X/2, -Y/2, GW_LOCATION*2, GH_LOCATION }, Textures["Parallax1"], 0, 0)

    -- Background
    Graphics.drawFrame(RENDER_MODE_BACKGROUND, 1, false, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, Textures["Background1"], 0, 0)
    Graphics.drawFrame(RENDER_MODE_BACKGROUND, 1, false, { SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, Textures["Background1"], 0, 1)
end

function L1.defineTriggers()
    function Triggers.playerComing(TTrigger, TEntity)
        setmetatable(TEntity, Actor)
        TEntity:setState("playerComing")
    end
end

function L1.defineCutscenes()
    States.dialogInCar = Cutscene.new(
        function(TActor)
            IsPlayerControllable = false
            return {
                { Player, true, GTT_FADE_IN, 1000.0 },
                { Zhenek, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "", 0.25, Zhenek, Textures["DialogSquare"]) },
                { Player, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "", 0.25, Player, Textures["DialogSquare"]) },
            }
        end,
        function(TActor)
            local X,Y = Pickup:getPosition()
            Sounds["CarDoorClose"]:play()
            Pickup:ejectActor(0)
            Player:setPosition(X + 17, Y - 8)

            Player:setState("")
            IsPlayerControllable = true
        end
    )

    States.playerComing = Cutscene.new(
        function(TActor)
            BlankActor:setState("fadeOff")
            Player:toggleCollidable(false)
            IsPlayerControllable = false
            Camera.detach()

            return {
                { Player, true, GTT_GOTO, 185, 50 },
                { Player, true, GTT_GOTO, 185, 37.5 },
                { Player, true, GTT_GOTO, 165, 25 },
            }
        end,
        function(TActor)
            Player:setState("")
        end
    )

    States.fadeOff = Cutscene.new(
        function(TActor)
            return {
                { BlankActor, true, GTT_FADE_OFF, 2000.0 },
                { BlankActor, false, GTT_FADE_IN, 0.0 },
            }
        end,
        function(TActor)
            Mission.switchLocation(2)
        end
    )
end

---- Location 2
function L2.onEnter()
    -- Functions
    Mission.onUpdate = L2.onUpdate
    Mission.onRender = L2.onRender
end

function L2.onUpdate(dt)
    Input.defaultHandle()
end

function L2.onRender()
end

function L2.defineCutscenes()
end

function L2.defineTriggers()
end

---- Location 3
function L3.onEnter()
    -- Functions
    Mission.onUpdate = L3.onUpdate
    Mission.onRender = L3.onRender
end

function L3.onUpdate(dt)
    Input.defaultHandle()
end

function L3.onRender()
end

function L3.defineCutscenes()
end

function L3.defineTriggers()
end

---- Location 4
function L4.onEnter()
    -- Functions
    Mission.onUpdate = L4.onUpdate
    Mission.onRender = L4.onRender
end

function L4.onUpdate(dt)
    Input.defaultHandle()
end

function L4.onRender()
end

function L4.defineCutscenes()
end

function L4.defineTriggers()
end
