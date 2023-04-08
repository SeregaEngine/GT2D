----------------------------------------------------------------------
--| * Mission2.lua *
--|
--| Petrol and Zhenek return to garage and plan next mission
----------------------------------------------------------------------

---- Includes
require "GarageBlueprint"

---- Resources
Textures["Car"] = Resource.defineTexture("Textures/Cars/Dodge.png", TW_CAR, TH_CAR)
Textures["Pickup"] = Resource.defineTexture("Textures/Cars/Pickup.png", TW_CAR, TH_CAR)
Textures["Wheel"] = Resource.defineTexture("Textures/Props/Wheels.png", 16, 16)
Textures["Background2"] = Resource.defineTexture("Textures/Locations/Mission2-2.png", TW_LOCATION, TH_LOCATION)
Textures["Parallax2"] = Resource.defineTexture("Textures/Locations/Mission2-2_Parallax.png", TW_LOCATION, TH_LOCATION)

Anims["PlayerSleep"] = Resource.defineAnimation(6, 1, 1000.0)
Anims["PlayerWakeUp"] = Resource.defineAnimation(6, 3, 1000.0 / 1.5)

Sounds["PickupThrottling"] = Resource.defineSound("Sounds/PickupThrottling.wav")
Musics["Ambient2"] = Resource.defineMusic("Music/Nature.mp3")
Musics["Morning"] = Musics["Ambient2"]

---- Levels
local L1 = {}
local L2 = {}

---- Mission
function Mission.onEnter(Location)
    GT_LOG(PR_NOTE, "Mission 2 entered")

    if Location == 1 then
        L1.onEnter()
    elseif Location == 2 then
        L2.onEnter()
    else
        L1.onEnter()
    end
end

---- Location 1
function L1.onEnter()
    -- Functions
    Mission.onUpdate = L1.onUpdate
    Mission.onRender = L1.onRender

    --- Init garage blueprint
    GarageBlueprint.onEnter()

    Dodge:setTexture(Textures["Car"])
    Dodge:setAnim(Resource.defineAnimation(0, 1, 999999))

    Wheels = {}
    for i = 1,4 do
        local X,Y
        if i <= 2 then
            X = 85
        else
            X = 90
        end

        if i % 2 == 1 then
            Y = 53
            AnimFrame = 0
        else
            Y = 48
            AnimFrame = 1
        end

        Wheels[i] = Entity:new(X, Y, 8, 8, Textures["Wheel"])
        Wheels[i]:setAnimFrame(AnimFrame)
        Wheels[i]:setRenderMode(RENDER_MODE_BACKGROUND)
        Wheels[i]:setZIndex(10+i)
    end

    --- Init mission
    L1.defineTriggers()
    L1.defineCutscenes()
    Player:setState("mainCutscene")
    Mission.setGroundBounds({ GROUND_X, GROUND_Y, GROUND_WIDTH * 3, GROUND_HEIGHT })
end

function L1.onUpdate(dt)
    GarageBlueprint.onUpdate(dt)
    Input.defaultHandle()
end

function L1.onRender()
    GarageBlueprint.onRender()
end

function L1.defineTriggers()
    function Triggers.leaveCutscene(TTrigger, TEntity)
        setmetatable(TEntity, Actor)
        TEntity:setState("leaveCutscene")
    end
end

function L1.defineCutscenes()
    States.mainCutscene = Cutscene.new(
        function(TActor)
            IsZhenekBusy = true
            IsPlayerControllable = false

            Zhenek:setPosition(GROUND_WIDTH * 1.8, GROUND_Y + GROUND_HEIGHT/2.5)
            Player:setPosition(GROUND_WIDTH * 1.9, GROUND_Y + GROUND_HEIGHT/2)

            GarageBlueprint.DayTime = GarageBlueprint.Night

            -- We use Player for Anthony's tasks to prevent canceling Anthony's tasks
            return {
                { Player, false, AITASK_FADE_IN, 3000.0 },
                { Zhenek, false, AITASK_GOTO, 70, GROUND_Y + GROUND_HEIGHT/2.5 },
                { Player, true, AITASK_GOTO, 87.5, GROUND_Y + GROUND_HEIGHT/2 },

                { Zhenek, true, AITASK_WAIT, 500.0 },
                { Zhenek, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Wassup Anthony", 2, Zhenek, Textures["DialogSquare"]) },
                { Zhenek, true, AITASK_WAIT, 250.0 },

                { Player, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Sup man", 2, Anthony, Textures["DialogSquare"]) },
                { Player, true, AITASK_WAIT, 250.0 },
                { Player, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "I thought you guys died", 4, Anthony, Textures["DialogSquare"]) },
                { Player, true, AITASK_WAIT, 250.0 },

                { Zhenek, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Maybe next time", 3, Zhenek, Textures["DialogSquare"]) },
                { Zhenek, true, AITASK_WAIT, 250.0 },

                { Player, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "So", 2, Player, Textures["DialogSquare"]) },
                { Player, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "What's next?", 4, Player, Textures["DialogSquare"]) },
                { Player, true, AITASK_WAIT, 250.0 },

                { Zhenek, false, AITASK_PUSH_COMMAND, AICMD_TURN_RIGHT },
                { Zhenek, true, AITASK_WAIT, 250.0 },

                { Zhenek, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "We got the wheels, but we need engine for your baby", 6, Zhenek, Textures["DialogSquare"]) },
                { Zhenek, true, AITASK_WAIT, 250.0 },
                { Zhenek, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "It's really hard to find familiar engine like yours", 6, Zhenek, Textures["DialogSquare"]) },
                { Zhenek, true, AITASK_WAIT, 250.0 },

                { Zhenek, false, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Our next goal is sport car in Texas.", 6, Zhenek, Textures["DialogSquare"]) },
                { Zhenek, true, AITASK_WAIT, 1000.0 },
                { Zhenek, true, AITASK_FADE_OFF, 4000.0 },
                { Zhenek, false, AITASK_FADE_IN, 0.0 },
            }
        end,
        function(TActor)
            TActor:setState("morningCutscene")
        end
    )

    States.morningCutscene = Cutscene.new(
        function(TActor)
            Musics["Morning"]:play()
            Anthony:delete()
            Zhenek:delete()
            Dodge:delete()
            Fire:delete()
            for i,v in ipairs(Wheels) do
                v:delete()
            end
            Player:setPosition(GW_LOCATION - GW_ACTOR, GH_LOCATION - GH_ACTOR)

            GarageBlueprint.DayTime = GarageBlueprint.Day

            return {
                { Player, false, AITASK_FADE_IN, 4000.0 },
                { Player, false, AITASK_PUSH_COMMAND, AICMD_TURN_LEFT },
                { Player, true, AITASK_ANIMATE_FOR, Anims["PlayerSleep"], 3000.0 },
                { Player, true, AITASK_WAIT_ANIMATION, Anims["PlayerWakeUp"] },
                { Player, false, AITASK_PUSH_COMMAND, AICMD_TURN_LEFT },
                { Player, false, AITASK_PUSH_COMMAND, AICMD_IDLE },

                { Player, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Where is my car?", 4, Player, Textures["DialogSquare"]) },
                { Player, false, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "What the fuck is going on", 4, Player, Textures["DialogSquare"]) },
            }
        end,
        function(TActor)
            Trigger:new({ GROUND_WIDTH, GROUND_Y-5, 2, GROUND_HEIGHT*2 }, Player, "leaveCutscene")
            IsPlayerControllable = true
            TActor:setState("")
        end
    )

    States.leaveCutscene = Cutscene.new(
        function(TActor)
            IsPlayerControllable = false
            return {
                { Player, false, AITASK_GOTO, GROUND_WIDTH*2, GROUND_Y + GROUND_HEIGHT },
                { Player, true, AITASK_FADE_OFF, 1500.0 },
                { Player, false, AITASK_FADE_IN, 0.0 }, -- Black screen on last frame
            }
        end,
        function(TActor)
            Saver.save("Scripts/Mission2.lua", 2)
            Mission.switchLocation(2)
            TActor:setState("")
        end
    )
end

---- Location 2
function L2.onEnter()
    -- Functions
    Mission.onUpdate = L2.onUpdate
    Mission.onRender = L2.onRender

    -- Defines
    GROUND_WIDTH = SCREEN_WIDTH
    GROUND_HEIGHT = 20
    GROUND_X = 0
    GROUND_Y = SCREEN_HEIGHT - GROUND_HEIGHT

    -- Globals
    TimeTicks = Clock.getTicks()

    -- Entities
    Player = Actor:new(0, 0, GW_ACTOR, GH_ACTOR, Textures["Player"])
    local XDefault,YDefault = Player:getSpeed()
    Player:setSpeed(XDefault/1.2, YDefault/1.2)
    Player:setActorAnim(ACTOR_ANIMATION_HORIZONTAL, Anims["SlowMoving"])
    Player:setTeam(ACTOR_TEAM_FRIENDS)
    Player:setWeapon(Weapons["Fist"])
    Player:setState("scene1")

    Zhenek = Actor:new(0, 0, GW_ACTOR, GH_ACTOR, Textures["Zhenek"])
    Zhenek:setSpeed(XDefault/1.2, YDefault/1.2)
    Zhenek:setActorAnim(ACTOR_ANIMATION_HORIZONTAL, Anims["SlowMoving"])
    Zhenek:setTeam(ACTOR_TEAM_FRIENDS)
    IsZhenekBusy = false

    Anthony = Actor:new(0, 0, GW_ACTOR, GH_ACTOR, Textures["Anthony"])
    Anthony:setSpeed(XDefault/1.2, YDefault/1.2)
    Anthony:setActorAnim(ACTOR_ANIMATION_HORIZONTAL, Anims["SlowMoving"])
    Anthony:setTeam(ACTOR_TEAM_FRIENDS)

    Dodge = Car:new(25, 60, TW_CAR + 18, 26, Textures["Car"])
    Dodge:setRenderMode(RENDER_MODE_FOREGROUND)
    Dodge:setZIndex(-1)
    Dodge:setAnim(Resource.defineAnimation(2, 1, 999999))
    Dodge:setMaxSpeed(0.0, 0.0)
    Dodge:setPlacePosition(0, 3, -4.5)
    Dodge:setPlacePosition(1, -5, -4.5)
    Dodge:putActor(Zhenek, 0)
    Dodge:putActor(Anthony, 1)

    Pickup = Car:new(130, 63, 107, 30, Textures["Pickup"])
    Pickup:setRenderMode(RENDER_MODE_FOREGROUND)
    Pickup:setZIndex(-1)
    Pickup:setMaxSpeed(0.075, 0)
    Pickup:setPlacePosition(0, 10, -5)
    Pickup:setPlacePosition(1, 6, -5)

    -- Cutscenes
    L2.defineCutscenes()

    -- Mission
    Mission.setGroundBounds({ GROUND_X, GROUND_Y, GROUND_WIDTH, GROUND_HEIGHT })
    Camera.setPosition(0, 0)
    Musics["Ambient2"]:play()
end

function L2.onUpdate(dt)
    TimeTicks = Clock.getTicks()
    Input.defaultHandle()
end

function L2.onRender()
    -- Parallax
    local X = (-TimeTicks/1000 % GW_LOCATION)
    Graphics.drawFrame(RENDER_MODE_BACKGROUND, 0, true, { X, 0, GW_LOCATION, GH_LOCATION }, Textures["Parallax2"])
    Graphics.drawFrame(RENDER_MODE_BACKGROUND, 0, true, { X-GW_LOCATION, 0, GW_LOCATION, GH_LOCATION }, Textures["Parallax2"])

    -- Background
    Graphics.drawFrame(RENDER_MODE_BACKGROUND, 1, true, { 0, 0, GW_LOCATION, GH_LOCATION }, Textures["Background2"])
end

function L2.defineCutscenes()
    States.scene1 = Cutscene.new(
        function(TActor)
            Zhenek:toggleCollidable(false)
            Player:setPosition(70, 35)
            Player:toggleCollidable(false)
            IsPlayerControllable = false

            return {
                { Player, false, AITASK_FADE_IN, 5000.0 },
                { Player, false, AITASK_GOTO, 70, 52 },
                { Player, false, AITASK_PUSH_COMMAND, AICMD_TURN_LEFT },

                { Zhenek, true, AITASK_WAIT, 1000.0 },
                { Zhenek, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Yeah, man, we can do this", 4, Zhenek, Textures["DialogSquare"]) },
                { Zhenek, true, AITASK_WAIT, 250.0 },

                { Anthony, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Deal, bro", 3, Anthony, Textures["DialogSquare"]) },
                { Anthony, true, AITASK_WAIT, 250.0 },

                { Player, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "What the fuck guys?", 4, Player, Textures["DialogSquare"]) },
                { Player, true, AITASK_WAIT, 500.0 },

                { Zhenek, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Yo you're woke up", 3, Zhenek, Textures["DialogSquare"]) },
                { Zhenek, true, AITASK_WAIT, 250.0 },
            }
        end,
        function(TActor)
            TActor:setState("scene2")
        end
    )

    States.scene2 = Cutscene.new(
        function(TActor)
            Sounds["CarDoorClose"]:play()
            Dodge:ejectActor(0)
            local X,Y = Zhenek:getPosition()
            Zhenek:setPosition(X, Y - 5)

            local PX, PY = Pickup:getPosition()

            return {
                { Zhenek, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "We just tested your new wheels", 4, Zhenek, Textures["DialogSquare"]) },
                { Zhenek, true, AITASK_WAIT, 250.0 },

                { Player, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Ok-ok..", 2, Player, Textures["DialogSquare"]) },
                { Player, true, AITASK_WAIT, 500.0 },

                { Zhenek, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Are you ready for Texas?!", 4, Zhenek, Textures["DialogSquare"]) },
                { Zhenek, true, AITASK_WAIT, 250.0 },

                { Player, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Ughh.. let's go", 3, Player, Textures["DialogSquare"]) },
                { Player, true, AITASK_WAIT, 500.0 },
                { Player, false, AITASK_GOTO, PX+5, PY-5 },
                { Zhenek, true, AITASK_GOTO, PX, PY-5 },
                { Zhenek, true, AITASK_WAIT, 250.0 },
            }
        end,
        function(TActor)
            TActor:setState("scene3")
        end
    )

    States.scene3 = Cutscene.new(
        function(TActor)
            Sounds["CarDoorOpen"]:play()
            Sounds["CarDoorOpen"]:play()
            Pickup:putActor(Zhenek, 0)
            Pickup:putActor(Player, 1)

            return {
                { Player, true, AITASK_WAIT, 1000.0 },
            }
        end,
        function(TActor)
            TActor:setState("scene4")
        end
    )

    States.scene4 = Cutscene.new(
        function(TActor)
            Sounds["StartEngine"]:play()

            return {
                { Player, true, AITASK_WAIT, 2500.0 },
            }
        end,
        function(TActor)
            TActor:setState("scene5")
        end
    )

    States.scene5 = Cutscene.new(
        function(TActor)
            Sounds["PickupThrottling"]:play()
            Pickup:setAcceleration(0.0001, 0)

            return {
                { Player, true, AITASK_FADE_OFF, 5000.0 },
                { Player, false, AITASK_FADE_IN, 0.0 },
            }
        end,
        function(TActor)
            Saver.save("Scripts/Mission3.lua", 1)
            Mission.switch("Scripts/Internal/Loader.lua", 1)
            TActor:setState("")
        end
    )
end