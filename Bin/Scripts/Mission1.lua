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

Sounds["OpenGarage"] = Resource.defineSound("Sounds/GarageDoorOpening.wav")
Sounds["PickupThrottling"] = Resource.defineSound("Sounds/PickupThrottling.wav")
Sounds["Police"] = Resource.defineSound("Sounds/PoliceScenario.wav")
Sounds["LockpickStart"] = Resource.defineSound("Sounds/LockpickStart.wav")
Sounds["LockpickFinish"] = Resource.defineSound("Sounds/LockpickFinish.wav")
Sounds["LockpickSuccess"] = Resource.defineSound("Sounds/LockpickSuccess.wav")
Sounds["LockpickFail"] = Resource.defineSound("Sounds/LockpickFail.wav")
Sounds["PickUp"] = Resource.defineSound("Sounds/ItemPickUp.wav")

Musics["Ambient1"] = Resource.defineMusic("Music/Nature.mp3")
Musics["Ambient2"] = Musics["Ambient1"]
Musics["Ambient3"] = Resource.defineMusic("Music/M1Fight.mp3")
Musics["Ambient4"] = Resource.defineMusic("Music/M1AfterFight.mp3")

Anims["DarkLordFist"] = Resource.defineAnimation(4, 3, 1000.0 / 2)
Anims["DarkLordDead"] = Resource.defineAnimation(5, 3, 1000.0 / 2)
Anims["PlayerDead"] = Resource.defineAnimation(5, 3, 1000.0 / 2)

Weapons["DarkLordFist"] = Resource.defineWeapon(Anims["DarkLordFist"], 8, 8, 5, Sounds["Punch1"], Sounds["Punch2"], Sounds["Punch3"], Sounds["Punch4"])

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
    TimeTicks = Clock.getTicks()
    Mission.setGroundBounds({ GROUND_X, GROUND_Y, GROUND_WIDTH, GROUND_HEIGHT })
    Camera.setBounds({ 0, 0, GROUND_WIDTH, SCREEN_HEIGHT })
    Camera.attach(Player)
    Musics["Ambient1"]:play()
end

function L1.onUpdate(dt)
    TimeTicks = Clock.getTicks()
    Input.defaultHandle()
end

function L1.onRender()
    -- Parallax
    local XCamera, YCamera = getCameraPosition()
    local X = -(TimeTicks/1000.0 + XCamera/2.0) % (GW_LOCATION*2)

    Graphics.drawFrame(RENDER_MODE_BACKGROUND, 0, true, { X, 0, GW_LOCATION*2, GH_LOCATION }, Textures["Parallax1"])
    Graphics.drawFrame(RENDER_MODE_BACKGROUND, 0, true, { X-GW_LOCATION*2, 0, GW_LOCATION*2, GH_LOCATION }, Textures["Parallax1"])

    -- Help
    Graphics.setDrawColor(255, 255, 255, 255)
    Graphics.drawText(RENDER_MODE_BACKGROUND, 1, false, { 128 - XCamera/5.0, 0, 50, 10 }, "Press space to attack")

    -- Background
    Graphics.drawFrame(RENDER_MODE_BACKGROUND, 2, false, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, Textures["Background1"], 0, 0)
    Graphics.drawFrame(RENDER_MODE_BACKGROUND, 2, false, { SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, Textures["Background1"], 0, 1)
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
                { Player, true, AITASK_FADE_IN, 3500.0 },

                { Zhenek, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "So all the way we talked, you break in and steal the wheels", 4, Zhenek, Textures["DialogSquare"]) },
                { Zhenek, true, AITASK_WAIT, 250.0 },

                { Player, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Ok, where we will meet?", 3, Player, Textures["DialogSquare"]) },
                { Player, true, AITASK_WAIT, 250.0 },

                { Zhenek, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "I'll be around the corner, let's go", 4, Zhenek, Textures["DialogSquare"]) },
                { Zhenek, true, AITASK_WAIT, 250.0 },

                { Player, true, AITASK_WAIT, 1000.0 },
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
                { Player, true, AITASK_GOTO, 180, 30 },
                { Player, true, AITASK_GOTO, 165, 25 },
            }
        end,
        function(TActor)
            Player:setState("")
        end
    )

    States.fadeOff = Cutscene.new(
        function(TActor)
            return {
                { BlankActor, true, AITASK_FADE_OFF, 2000.0 },
                { BlankActor, false, AITASK_FADE_IN, 0.0 },
            }
        end,
        function(TActor)
            Saver.save("Scripts/Mission1.lua", 2)
            Mission.switchLocation(2)
        end
    )
end

---- Location 2
function L2.onEnter()
    -- Functions
    Mission.onUpdate = L2.onUpdate
    Mission.onRender = L2.onRender

    -- Defines
    GW_SQUARE = 10
    GH_SQUARE = 10

    GW_LOCKPICK = 5
    GH_LOCKPICK = 5
    LOCKPICK_TOP = 20
    LOCKPICK_BOTTOM = SCREEN_HEIGHT - LOCKPICK_TOP
    LOCKPICK_YSPEED = 0.03
    LOCKPICK_FAIL_SOUND_RATE = 500

    -- Entities
    Player = Actor:new(0, 0, 0, 0, Textures["Blank"])
    Player:setState("fadeInCutscene")
    IsPlayerControllable = false

    Squares = {}
    for i = 1,4 do
        Squares[i] = Entity:new(20 + GW_SQUARE/2 + GW_SQUARE * (i-1) + 16 * (i-1), SCREEN_HEIGHT/2, GW_SQUARE, GH_SQUARE, Textures["Blank"])
    end

    local X,_ = Squares[1]:getPosition()
    Lockpick = Entity:new(X, LOCKPICK_TOP, GW_LOCKPICK, GH_LOCKPICK, Textures["Blank"])
    LockpickingStage = 1
    LockpickGoBottom = true
    LockpickLastTry = 0

    -- States
    L2.defineCutscenes()
    L2.defineStates()

    -- Level
    Camera.setPosition(0, 0)
    Musics["Ambient2"]:play()
end

function L2.onUpdate(dt)
    DT = dt -- Just workaround for global delta time

    Input.defaultHandle()
end

function L2.onRender()
    -- Background
    Graphics.drawFrame(RENDER_MODE_BACKGROUND, 0, true, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, Textures["Background2"], 0, 0)
    Graphics.setDrawColor(68, 68, 68, 168)
    Graphics.fillRect(RENDER_MODE_BACKGROUND, 1, true, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT })

    -- Squares
    for i,v in ipairs(Squares) do
        if i < LockpickingStage then
            Graphics.setDrawColor(135, 200, 96, 255)
        else
            Graphics.setDrawColor(232, 232, 232, 255)
        end

        X,Y = v:getPosition()
        Graphics.fillRect(RENDER_MODE_BACKGROUND, 2, true, { X - GW_SQUARE/2 , Y - GH_SQUARE/2, GW_SQUARE, GH_SQUARE })
    end

    -- Lockpick
    local X,Y = Lockpick:getPosition()
    Graphics.setDrawColor(228, 87, 129, 255)
    Graphics.fillRect(RENDER_MODE_BACKGROUND, 3, true, { X - GW_LOCKPICK/2, Y - GH_LOCKPICK/2, GW_LOCKPICK, GH_LOCKPICK })

    -- Help
    Graphics.setDrawColor(255, 255, 255, 160)
    Graphics.drawText(RENDER_MODE_BACKGROUND, 4, true, { 14, LOCKPICK_BOTTOM + 5, 100, 5 }, "Press space when lockpick'll be in square")
end

function L2.onRenderFaded()
    Graphics.setDrawColor(0, 0, 0, 255)
    Graphics.fillRect(RENDER_MODE_BACKGROUND, 1, true, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT })
end

function L2.defineCutscenes()
    States.fadeInCutscene = Cutscene.new(
        function(TActor)
            Sounds["LockpickStart"]:play()
            return {
                { Player, true, AITASK_FADE_IN, 1000.0 },
            }
        end,
        function(TActor)
            TActor:setState("lockpicking")
        end
    )

    States.fadeOffCutscene1 = Cutscene.new(
        function(TActor)
            Sounds["LockpickFinish"]:play()
            return {
                { Player, true, AITASK_FADE_OFF, 1500.0 },
            }
        end,
        function(TActor)
            Mission.onRender = L2.onRenderFaded
            TActor:setState("fadeOffCutscene2")
        end
    )

    States.fadeOffCutscene2 = Cutscene.new(
        function(TActor)
            Sounds["OpenGarage"]:play()
            return {
                { Player, true, AITASK_WAIT, 3000.0 },
            }
        end,
        function(TActor)
            Saver.save("Scripts/Mission1.lua", 3)
            Mission.switchLocation(3)
            TActor:setState("")
        end
    )
end

function L2.defineStates()
    function States.lockpicking(TActor)
        -- Update lockpick position
        local X,Y = Lockpick:getPosition()
        if Y <= LOCKPICK_TOP then
            LockpickGoBottom = true
        elseif Y >= LOCKPICK_BOTTOM then
            LockpickGoBottom = false
        end

        if LockpickGoBottom then
            Y = Y + (LOCKPICK_YSPEED * DT)
        else
            Y = Y - (LOCKPICK_YSPEED * DT)
        end
        Lockpick:setPosition(X, Y)

        -- Handle input
        if Input.isKeyDown(GTK_SPACE) then
            local LX,LY = Lockpick:getPosition()
            local SX,SY = Squares[LockpickingStage]:getPosition()

            -- Check collision with square
            if (LY - GH_LOCKPICK/2 >= SY - GH_SQUARE/2) and
               (LY + GH_LOCKPICK/2) <= SY + GH_SQUARE/2 then
                LockpickingStage = LockpickingStage + 1
                if (LockpickingStage > 4) then
                    TActor:setState("fadeOffCutscene1")
                    return
                end

                Sounds["LockpickSuccess"]:play()
                LockpickLastTry = Clock.getTicks()

                SX,SY = Squares[LockpickingStage]:getPosition()
                LX = SX
            else
                if Clock.getTicks() - LockpickLastTry >= LOCKPICK_FAIL_SOUND_RATE then
                    Sounds["LockpickFail"]:play()
                    LockpickLastTry = Clock.getTicks()
                end

                LX = SX
            end
            Lockpick:setPosition(LX, LOCKPICK_TOP)
        end
    end
end

---- Location 3
function L3.onEnter()
    -- Functions
    Mission.onUpdate = L3.onUpdate
    Mission.onRender = L3.onRenderBeforeTutorial

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
    Musics["Ambient3"]:play()
end

function L3.onUpdate(dt)
    Input.defaultHandle()

    if DarkLord:getHealth() < 95.0 then
        Mission.onRender = L3.onRenderAfterTutorial
    end
end

function L3.onRenderBeforeTutorial()
    Graphics.drawFrame(RENDER_MODE_BACKGROUND, 0, true, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, Textures["Background3"], 0, 0)

    Graphics.setDrawColor(255, 255, 255, 168)
    Graphics.drawText(RENDER_MODE_BACKGROUND, 1, true, { 8, SCREEN_HEIGHT - 8, 21 * 3, 8 }, "Press space to attack")
end

function L3.onRenderAfterTutorial()
    Graphics.drawFrame(RENDER_MODE_BACKGROUND, 0, true, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, Textures["Background3"], 0, 0)
end

function L3.defineTriggers()
    function Triggers.takeWheel(TTrigger, TEntity)
        TriggerPointerToWheel[TTrigger.Pointer]:delete()
        Sounds["PickUp"]:play()
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
                { Player, true, AITASK_FADE_IN, 1000.0 },
                { Player, true, AITASK_WAIT, 500.0 },

                { DarkLord, false, AITASK_PUSH_COMMAND, AICMD_TURN_RIGHT },
                { DarkLord, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Hmm?", 2, DarkLord, Textures["DialogSquare"]) },
                { DarkLord, true, AITASK_WAIT, 250.0 },
                { DarkLord, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "What the hell? Who are you?!", 4, DarkLord, Textures["DialogSquare"]) },

                { Player, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "I came for your wheels, dawg", 4, Player, Textures["DialogSquare"]) },
                { Player, true, AITASK_WAIT, 250.0 },

                { DarkLord, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Pamella!!!", 2, DarkLord, Textures["DialogSquare"]) },
                { DarkLord, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Call the police! There's someone in our garage", 6, DarkLord, Textures["DialogSquare"]) },
                { DarkLord, true, AITASK_WAIT, 250.0 },

                { Pamella, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "What? Honey, i didn't hear you!", 3, Pamella, Textures["DialogSquare"]) },
                { Pamella, true, AITASK_WAIT, 250.0 },

                { DarkLord, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "I'll not give my wheels, bald idiot", 4, DarkLord, Textures["DialogSquare"]) },
                { DarkLord, true, AITASK_WAIT, 250.0 },
            }
        end,
        function(TActor)
            DarkLord:pushTask(AITASK_NONE) -- Clear tasks to init killPlayer state
            DarkLord:setState("killPlayer")
            TActor:setState("playerFighting")
            IsPlayerControllable = true
        end
    )

    States.playerKilledCutscene = Cutscene.new(
        function(TActor)
            return {
                { DarkLord, true, AITASK_WAIT, 250.0 },
                { DarkLord, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "You shouldn't have come...", 3, DarkLord, Textures["DialogSquare"]) },
                { DarkLord, true, AITASK_FADE_OFF, 3000.0 },
                { DarkLord, false, AITASK_FADE_IN, 0.0 },
            }
        end,
        function(TActor)
            Mission.switchLocation(3)
        end
    )

    States.removeWheelsCutscene = Cutscene.new(
        function(TActor)
            return {
                { Player, true, AITASK_WAIT, 1750.0 },
                { Pamella, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Honey?!", 2, Pamella, Textures["DialogSquare"]) },
                { Player, true, AITASK_WAIT, 250.0 },
                { Player, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "I should take these wheels and run away", 4, Player, Textures["DialogSquare"]) },
                { Player, true, AITASK_FADE_OFF, 1000.0 },
                { Player, false, AITASK_FADE_IN, 0.0 },
            }
        end,
        function(TActor)
            TActor:setState("wheelsRemovedCutscene")
        end
    )

    States.wheelsRemovedCutscene = Cutscene.new(
        function(TActor)
            return {
                { Player, false, AITASK_FADE_IN, 750.0 },
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
                { Player, false, AITASK_GOTO, GROUND_WIDTH*3, GROUND_Y - 3 },
                { Player, true, AITASK_FADE_OFF, 2000.0 },
                { Player, false, AITASK_FADE_IN, 0.0 },
            }
        end,
        function(TActor)
            Saver.save("Scripts/Mission1.lua", 4)
            Mission.switchLocation(4)
            TActor:setState("")
        end
    )
end

function L3.defineStates()
    function States.killPlayer(TActor)
        local Task = TActor:getCurrentTask()
        local Status = TActor:checkCurrentTask()

        if Task == AITASK_NONE then
            TActor:pushTask(AITASK_GOTO_ENTITY, Player)
        elseif Status == AITASK_INPROCESS then
            return
        elseif Status == AITASK_DONE then
            if Task == AITASK_GOTO_ENTITY then
                TActor:pushTask(AITASK_KILL, Player)
            elseif Task == AITASK_KILL then
                TActor:setState("playerKilledCutscene")
            end
        elseif Status == AITASK_IMPOSSIBLE then
            if Task == AITASK_KILL then
                TActor:pushTask(AITASK_GOTO_ENTITY, Player)
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

    -- Defines
    GROUND_WIDTH = SCREEN_WIDTH * 2
    GROUND_HEIGHT = 19
    GROUND_X = 0
    GROUND_Y = SCREEN_HEIGHT - GROUND_HEIGHT

    -- Entities
    Player = Actor:new(180, 35, GW_ACTOR, GH_ACTOR, Textures["Player"])
    Player:setState("comingToCarCutscene")

    Zhenek = Actor:new(0, 0, GW_ACTOR, GH_ACTOR, Textures["Zhenek"])
    Zhenek:setTeam(ACTOR_TEAM_FRIENDS)

    Pickup = Car:new(SCREEN_WIDTH + 75, 65, 107, 30, Textures["Pickup"])
    Pickup:setMaxSpeed(0.075, 0)
    Pickup:setPlacePosition(0, 10, -5)
    Pickup:setPlacePosition(1, 6, -5)
    Pickup:putActor(Zhenek, 0)

    Serega = Actor:new(0, 0, GW_ACTOR, GH_ACTOR, Textures["Serega"])
    Serega:toggleCollidable(false)
    Serega:pushTask(AITASK_WAIT, 5000) -- Don't check car velocity 5 seconds
    Serega:setState("policeControllingCar")

    John = Actor:new(0, 0, GW_ACTOR, GH_ACTOR, Textures["John"])
    John:toggleCollidable(false)
    local X,Y = John:getSpeed()
    John:setSpeed(X*0.75, Y*0.75)

    PoliceCar = Car:new(SCREEN_WIDTH*12, 66, 90, 32, Textures["PoliceCar"])
    PoliceCar:setMaxSpeed(0.135, 0)
    PoliceCar:setAcceleration(-1, 0)
    PoliceCar:setPlacePosition(0, 0, -4)
    PoliceCar:setPlacePosition(1, 7, -3)
    PoliceCar:putActor(Serega, 0)
    PoliceCar:putActor(John, 1)
    PoliceCar:turnLeft()

    Trigger:new({ SCREEN_WIDTH*2.3, SCREEN_HEIGHT/2, 1, SCREEN_HEIGHT }, PoliceCar, "policeStop")

    -- Triggers and States
    L4.defineTriggers()
    L4.defineStates()
    L4.defineCutscenes()

    -- Level
    TimeTicks = Clock.getTicks()

    Mission.setGroundBounds({ GROUND_X, GROUND_Y, GROUND_WIDTH, GROUND_HEIGHT })
    Camera.setBounds({ 0, 0, GROUND_WIDTH, SCREEN_HEIGHT })
    Camera.attach(Player)
    Camera.detach()

    Musics["Ambient4"]:play()
    Sounds["Police"]:play()
    Sounds["StartEngine"]:play()
end

function L4.onUpdate(dt)
    TimeTicks = Clock.getTicks()
end

function L4.onRender()
    -- Parallax
    local X = -(TimeTicks/1000.0) % (GW_LOCATION*2)
    Graphics.drawFrame(RENDER_MODE_BACKGROUND, 0, true, { X, 0, GW_LOCATION*2, GH_LOCATION }, Textures["Parallax4"], 0, 0)
    Graphics.drawFrame(RENDER_MODE_BACKGROUND, 0, true, { X-GW_LOCATION*2, 0, GW_LOCATION*2, GH_LOCATION }, Textures["Parallax4"], 0, 0)

    -- Background
    Graphics.drawFrame(RENDER_MODE_BACKGROUND, 1, false, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, Textures["Background4"], 0, 0)
    Graphics.drawFrame(RENDER_MODE_BACKGROUND, 1, false, { SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, Textures["Background4"], 0, 1)

    -- Evening
    Graphics.setDrawColor(0, 0, 0, 50)
    Graphics.fillRect(RENDER_MODE_BACKGROUND, 2, true, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT })
end

function L4.defineTriggers()
    function Triggers.policeStop(TTrigger, TEntity)
        PoliceCar:setAcceleration(0.00006, 0)
    end
end

function L4.defineStates()
    function States.policeControllingCar(TActor)
        -- Wait
        if TActor:checkCurrentTask() ~= AITASK_DONE then
            return
        end

        -- Handle velocity
        local X,Y = PoliceCar:getVelocity()
        if X > -0.025 then
            -- Stop car, start dialog
            PoliceCar:setMaxSpeed(0, 0)
            TActor:setState("policeTalkingCutscene")
        end
    end
end

function L4.defineCutscenes()
    States.comingToCarCutscene = Cutscene.new(
        function(TActor)
            Player:toggleCollidable(false)
            IsPlayerControllable = false
            Pickup:turnLeft()
            local CarX,CarY = Pickup:getPosition()
            CarY = CarY - 5
            local PlayerX,PlayerY = Player:getPosition()
            return {
                { Player, false, AITASK_FADE_IN, 2000.0 },
                { Player, true, AITASK_GOTO, PlayerX, CarY },
                { Player, true, AITASK_WAIT, 500.0 },

                { Zhenek, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Faster! Jump in car", 2, Zhenek, Textures["DialogSquare"]) },
                { Zhenek, true, AITASK_WAIT, 250.0 },

                { Player, true, AITASK_GOTO, CarX, CarY },
            }
        end,
        function(TActor)
            Sounds["CarDoorOpen"]:play()
            Sounds["PickupThrottling"]:play()
            Pickup:putActor(Player, 1)
            Pickup:setAcceleration(-0.0001, 0)
            TActor:setState("")
        end
    )

    States.policeTalkingCutscene = Cutscene.new(
        function(TActor)
            return {
                { John, true, AITASK_WAIT, 500.0 },
                { John, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "I don't like it...", 2, John, Textures["DialogSquare"]) },
                { John, true, AITASK_WAIT, 250.0 },

                { Serega, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "C'mon, John! Are you a little girl?", 4, Serega, Textures["DialogSquare"]) },
                { Serega, true, AITASK_WAIT, 250.0 },

                { John, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "I am a grown forty-year-old divorced man with two children and...", 8, John, Textures["DialogSquare"]) },
                { John, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "a loan for a house that I have been giving for 10 years", 6, John, Textures["DialogSquare"]) },
                { John, true, AITASK_WAIT, 250.0 },
                { John, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Yeah, i'm a little girl.", 4, John, Textures["DialogSquare"]) },
                { John, true, AITASK_WAIT, 250.0 },

                { Serega, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Just shut up and let's go", 4, Serega, Textures["DialogSquare"]) },
                { Serega, true, AITASK_WAIT, 250.0 },
            }
        end,
        function(TActor)
            Sounds["CarDoorClose"]:play()
            Sounds["CarDoorClose"]:play()
            PoliceCar:ejectActor(0)
            PoliceCar:ejectActor(1)

            local X,Y = PoliceCar:getPosition()
            Serega:setPosition(X - 7.5, Y - 5)
            Serega:turnLeft()
            John:setPosition(X, Y - 5)
            John:turnLeft()

            TActor:setState("policeComingHouseCutscene")
        end
    )

    States.policeComingHouseCutscene = Cutscene.new(
        function(TActor)
            return {
                { Serega, false, AITASK_GOTO, 175, 30 },
                { John, false, AITASK_GOTO, 180, 30 },
                { Serega, true, AITASK_FADE_OFF, 3000.0 },
                { Serega, false, AITASK_FADE_IN, 0.0 },
            }
        end,
        function(TActor)
            Saver.save("Scripts/Mission2.lua", 1)
            Mission.switch("Scripts/Internal/Loader.lua", 1)
            TActor:setState("")
        end
    )
end
