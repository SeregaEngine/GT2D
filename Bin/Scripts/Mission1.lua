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
Textures["Pamella"] = Resource.defineTexture("Textures/Actors/Pamella.png", TW_ACTOR, TH_ACTOR)
Textures["DarkLord"] = Resource.defineTexture("Textures/Actors/DarkLord.png", TW_ACTOR, TH_ACTOR)
Textures["Serega"] = Resource.defineTexture("Textures/Actors/Serega.png", TW_ACTOR, TH_ACTOR)
Textures["John"] = Resource.defineTexture("Textures/Actors/John.png", TW_ACTOR, TH_ACTOR)

Textures["Wheels"] = Resource.defineTexture("Textures/Props/Wheels.png", 16, 16)

Sounds["OpenGate"] = Resource.defineSound("Sounds/MetalGateOpening.wav")
Sounds["PickupThrottling"] = Resource.defineSound("Sounds/PickupThrottling.wav")
Sounds["Police"] = Resource.defineSound("Sounds/PoliceScenario.wav")

Music["Ambient1"] = Resource.defineMusic("Music/VnatureBgSound.wav")
Music["Ambient2"] = Music["Ambient1"]
Music["Ambient3"] = Resource.defineMusic("Music/Mission1GarageAmbient.wav")
Music["Ambient4"] = Music["Ambient1"]

Anims["DarkLordFist"] = Resource.defineAnimation(4, 3, 1000.0 / 2)
Anims["DarkLordDead"] = Resource.defineAnimation(5, 3, 1000.0 / 2)
Anims["PlayerDead"] = Resource.defineAnimation(5, 3, 1000.0 / 2)

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

    Pamella = Actor:new(185, 25, GW_ACTOR/2, GH_ACTOR/2, Textures["Pamella"])

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
                { Player, true, GTT_GOTO, 185, 35 },
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

    -- TODO(sean)
    Mission.switchLocation(3)
end

function L2.onUpdate(dt)
    Input.defaultHandle()
end

function L2.onRender()
end

function L2.defineTriggers()
end

function L2.defineCutscenes()
end

---- Location 3
function L3.onEnter()
    -- Functions
    Mission.onUpdate = L3.onUpdate
    Mission.onRender = L3.onRender

    -- Defines
    GROUND_WIDTH = SCREEN_WIDTH - 10
    GROUND_HEIGHT = 10
    GROUND_X = 7
    GROUND_Y = SCREEN_HEIGHT - GROUND_HEIGHT

    -- Entities
    Player = Actor:new(SCREEN_WIDTH - 20, 62, GW_ACTOR, GH_ACTOR, Textures["Player"])
    Player:setActorAnim(ACTOR_ANIMATION_DEAD, Anims["PlayerDead"])
    Player:setDeathSound(Sounds["ActorDeath"])
    Player:setWeapon(Weapons["Fist"])
    Player:setTeam(ACTOR_TEAM_FRIENDS)
    Player:setState("cutscene")

    DarkLord = Actor:new(20, 60, GW_ACTOR, GH_ACTOR, Textures["DarkLord"])
    DarkLord:setActorAnim(ACTOR_ANIMATION_DEAD, Anims["DarkLordDead"])
    DarkLord:setDeathSound(Sounds["ActorDeath"])
    DarkLord:setWeapon(Weapons["DarkLordFist"])

    Pamella = Actor:new(28, 55, GW_ACTOR, GH_ACTOR, Textures["Blank"])
    Pamella:toggleGodMode(true)

    TrashCar = Car:new(76, 54, 75, 21, Textures["TrashCarWheels"])
    TrashCar:setRenderMode(RENDER_MODE_BACKGROUND)
    TrashCar:setZIndex(3)

    -- Triggers and States
    L3.defineTriggers()
    L3.defineCutscenes()
    L3.defineStates()

    -- Level
    Mission.setGroundBounds({ GROUND_X, GROUND_Y, GROUND_WIDTH, GROUND_HEIGHT })
    Camera.setBounds({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT })
    Camera.attach(Player)

    -- Music
    Music["Ambient3"]:play()
end

function L3.onUpdate(dt)
    Input.defaultHandle()
end

function L3.onRender()
    Graphics.drawFrame(RENDER_MODE_BACKGROUND, 0, true, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, Textures["Background3"], 0, 0)
end

function L3.defineTriggers()
    function Triggers.takeWheel(TTrigger, TEntity)
        TriggerPointerToWheel[TTrigger.Pointer]:delete()
    end

    function Triggers.leaveGarage(TTrigger, TEntity)
        setmetatable(TEntity, Actor)
        TEntity:setState("leavingGarageCutscene")
    end
end

function L3.defineCutscenes()
    States.cutscene = Cutscene.new(
        function(TActor)
            Player:turnLeft()
            IsPlayerControllable = false
            DarkLord:turnLeft()
            return {
                --[[ DEBUG(sean)
                { Player, true, GTT_FADE_IN, 1000.0 },
                { Player, true, GTT_WAIT, 250.0 },

                { DarkLord, false, GTT_PUSH_COMMAND, GTC_TURN_RIGHT },
                { DarkLord, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Hmm?", 0.25, DarkLord, Textures["DialogSquare"]) },
                { DarkLord, true, GTT_WAIT, 250.0 },
                { DarkLord, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "What the hell? Who are you?!", 0.25, DarkLord, Textures["DialogSquare"]) },

                { Player, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "I came for your wheels, dawg", 0.25, Player, Textures["DialogSquare"]) },
                { Player, true, GTT_WAIT, 250.0 },

                { DarkLord, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Pamella!!!", 0.25, DarkLord, Textures["DialogSquare"]) },
                { DarkLord, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Call the police! There's someone in our garage", 0.25, DarkLord, Textures["DialogSquare"]) },
                { DarkLord, true, GTT_WAIT, 250.0 },

                { Pamella, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "What? Honey, i didn't hear you!", 0.25, Pamella, Textures["DialogSquare"]) },
                { Pamella, true, GTT_WAIT, 250.0 },

                { DarkLord, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "I'll not give my wheels, bald idiot", 0.25, DarkLord, Textures["DialogSquare"]) },
                { DarkLord, true, GTT_WAIT, 250.0 },
                ]]--
            }
        end,
        function(TActor)
            DarkLord:pushTask(GTT_NONE) -- Clear tasks to init killPlayer state
            DarkLord:setState("killPlayer")
            TActor:setState("playerFighting")
            IsPlayerControllable = true
        end
    )

    States.playerKilledCutscene = Cutscene.new(
        function(TActor)
            return {
                { DarkLord, true, GTT_WAIT, 250.0 },
                { DarkLord, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "You shouldn't have come...", 0.25, DarkLord, Textures["DialogSquare"]) },
                { DarkLord, true, GTT_FADE_OFF, 1000.0 },
                { DarkLord, false, GTT_FADE_IN, 0.0 },
            }
        end,
        function(TActor)
            Mission.switchLocation(3)
        end
    )

    States.removeWheelsCutscene = Cutscene.new(
        function(TActor)
            return {
                { Pamella, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Honey?!", 0.25, Pamella, Textures["DialogSquare"]) },
                { Player, true, GTT_WAIT, 250.0 },
                { Player, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "I should take these wheels and run away", 0.25, Player, Textures["DialogSquare"]) },
                { Player, true, GTT_FADE_OFF, 250.0 },
                { Player, false, GTT_FADE_IN, 0.0 },
            }
        end,
        function(TActor)
            TActor:setState("wheelsRemovedCutscene")
        end
    )

    States.wheelsRemovedCutscene = Cutscene.new(
        function(TActor)
            return {
                { Player, false, GTT_FADE_IN, 250.0 },
            }
        end,
        function(TActor)
            TrashCar:setTexture(Textures["TrashCar"])

			-- Add wheels and triggers
            local GW_PROP = 8
            local GH_PROP = 8
            TriggerPointerToWheel = {}

			for i = 1,4 do
				local X = 20 + GW_PROP * (i - 1)
				local Y = 60
				local Wheel = Entity:new(X, Y, GW_PROP, GH_PROP, Textures["Wheels"])

				TriggerPointerToWheel[Trigger:new({ X, Y, GW_PROP/4, GH_PROP/4 }, Player, "takeWheel").Pointer] = Wheel

				if i > 2 then
					Wheel:setAnimFrame(1)
				end
			end

            TActor:setState("takingWheels")
        end
    )

    States.leavingGarageCutscene = Cutscene.new(
        function(TActor)
            IsPlayerControllable = false
            return {
                { Player, false, GTT_GOTO, GROUND_WIDTH*3, GROUND_Y + GROUND_HEIGHT/2 },
                { Player, true, GTT_FADE_OFF, 250.0 },
                { Player, false, GTT_FADE_IN, 0.0 },
            }
        end,
        function(TActor)
            Mission.switchLocation(4)
            TActor:setState("")
        end
    )
end

function L3.defineStates()
    function States.killPlayer(TActor)
        local Task = TActor:getCurrentTask()
        local Status = TActor:checkCurrentTask()

        if Task == GTT_NONE then
            TActor:pushTask(GTT_GOTO_ENTITY, Player)
        elseif Status == GTT_INPROCESS then
            return
        elseif Status == GTT_DONE then
            if Task == GTT_GOTO_ENTITY then
                TActor:pushTask(GTT_KILL, Player)
            elseif Task == GTT_KILL then
                TActor:setState("playerKilledCutscene")
            end
        elseif Status == GTT_IMPOSSIBLE then
            if Task == GTT_KILL then
                TActor:pushTask(GTT_GOTO_ENTITY, Player)
            else
                TActor:setState("") -- Just do nothing on strange error
            end
        end
    end

    function States.playerFighting(TActor)
        if not DarkLord:isAlive() then
            TActor:setState("removeWheelsCutscene")
        end
    end

    function States.takingWheels(TActor)
        for k,v in pairs(TriggerPointerToWheel) do
            if v:isAvailable() then
                return
            end
        end

		Trigger:new({ SCREEN_WIDTH, SCREEN_HEIGHT/2, GW_ACTOR, SCREEN_HEIGHT }, Player, "leaveGarage")
        Mission.setGroundBounds({ GROUND_X, GROUND_Y, GROUND_WIDTH*2, GROUND_HEIGHT })
        TActor:setState("")
    end
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

function L4.defineTriggers()
end

function L4.defineCutscenes()
end
