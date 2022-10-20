----------------------------------------------------------------------
--| * Mission3.lua *
--|
--| Texas mission, where Petrol steals trash car near bar
----------------------------------------------------------------------

---- Includes
require "Mission"

---- Resources
Textures["Background1"] = Resource.defineTexture("Textures/Locations/Mission3-1.png", TW_LOCATION*4, TH_LOCATION)
Textures["Background2"] = Resource.defineTexture("Textures/Locations/Mission3-2.png", TW_LOCATION, TH_LOCATION)
Textures["Background3"] = Textures["Background3"]
Textures["Parallax1"] = Resource.defineTexture("Textures/Locations/Mission3-1_Parallax.png", TW_LOCATION*2, TH_LOCATION)
Textures["Parallax3"] = Textures["Parallax1"]

Textures["Pickup"] = Resource.defineTexture("Textures/Cars/Pickup.png", TW_CAR, TH_CAR)
Textures["PoliceCar"] = Resource.defineTexture("Textures/Cars/PoliceCar.png", TW_CAR, TH_CAR)

Textures["Player"] = Resource.defineTexture("Textures/Actors/Player.png", TW_ACTOR, TH_ACTOR)
Textures["Zhenek"] = Resource.defineTexture("Textures/Actors/Zhenek.png", TW_ACTOR, TH_ACTOR)
Textures["Serega"] = Resource.defineTexture("Textures/Actors/Serega.png", TW_ACTOR, TH_ACTOR)
Textures["John"] = Resource.defineTexture("Textures/Actors/John.png", TW_ACTOR, TH_ACTOR)
Textures["Mex1"] = Resource.defineTexture("Textures/Actors/Mex1.png", TW_ACTOR, TH_ACTOR)
Textures["Mex2"] = Textures["Mex1"] -- Placeholder
Textures["Mex3"] = Textures["Mex1"] -- Placeholder
Textures["Artem"] = Textures["Mex1"] -- Placeholder
Textures["Kirill"] = Textures["Mex1"] -- Placeholder

Sounds["PickupThrottling"] = Resource.defineSound("Sounds/PickupThrottling.wav")
Sounds["PoliceStart"] = Resource.defineSound("Sounds/PoliceCarStart.wav")
Sounds["PoliceStop"] = Resource.defineSound("Sounds/PoliceCarStop.wav")

Sounds["PoliceHit1"] = Resource.defineSound("Sounds/PoliceBatonHit1.wav")
Sounds["PoliceHit2"] = Resource.defineSound("Sounds/PoliceBatonHit2.wav")
Sounds["PoliceHit3"] = Resource.defineSound("Sounds/PoliceBatonHit3.wav")

Sounds["Colt1"] = Resource.defineSound("Sounds/ColtShot1.wav")
Sounds["Colt2"] = Resource.defineSound("Sounds/ColtShot2.wav")
Sounds["Colt3"] = Resource.defineSound("Sounds/ColtShot3.wav")

Musics["Ambient1"] = Resource.defineMusic("Music/VnatureBgSound.wav") -- Placeholder
Musics["Ambient2"] = Musics["Ambient1"] -- Placeholder
Musics["Ambient3"] = Musics["Ambient1"]

Anims["PlayerDead"] = Resource.defineAnimation(5, 3, 1000.0 / 2)
Anims["MexFist"] = Resource.defineAnimation(4, 3, 1000.0 / 2)
Anims["MexDead"] = Resource.defineAnimation(5, 3, 1000.0 / 2)
Anims["MexDraw"] = Resource.defineAnimation(6, 3, 1000.0 / 10)

-- DEBUG(sean) Remove this fist
Weapons["Fist"] = Resource.defineWeapon(Resource.defineAnimation(4, 3, 1000.0 / 2.0), 8, 8, 50.0, Sounds["Punch1"], Sounds["Punch2"], Sounds["Punch3"], Sounds["Punch4"])
Weapons["MexFist"] = Resource.defineWeapon(Anims["MexFist"], 8, 8, 5, Sounds["Punch1"], Sounds["Punch2"], Sounds["Punch3"], Sounds["Punch4"])

---- Mission
L1 = {}
L2 = {}
L3 = {}

function Mission.onEnter(Location)
    if Location == 1 then
        L1.onEnter()
    elseif Location == 2 then
        L2.onEnter()
    elseif Location == 3 then
        L3.onEnter()
    end
end

---- Location1
function L1.onEnter()
    -- Functions
    Mission.onUpdate = L1.onUpdate
    Mission.onRender = L1.onRender

    -- Defines
    GROUND_WIDTH = GW_LOCATION * 4
    GROUND_HEIGHT = 20
    GROUND_X = 0
    GROUND_Y = GH_LOCATION - GROUND_HEIGHT

    -- Entities
    Blank = Actor:new(0, 0, 0, 0, Textures["Blank"])
    Blank:toggleGodMode(true)
    Blank:setState("playerFightMexCameraFix")

    Player = Actor:new(128, 60, GW_ACTOR, GH_ACTOR, Textures["Player"])
    Player:setActorAnim(ACTOR_ANIMATION_DEAD, Anims["PlayerDead"])
    Player:setDeathSound(Sounds["ActorDeath"])
    Player:setWeapon(Weapons["Fist"])
    Player:setTeam(ACTOR_TEAM_FRIENDS)
    Player:setState("introCutscene")

    Zhenek = Actor:new(0, 0, GW_ACTOR, GH_ACTOR, Textures["Zhenek"])
    Zhenek:setTeam(ACTOR_TEAM_FRIENDS)

    Pickup = Car:new(30, 68, 107, 30, Textures["Pickup"])
    Pickup:setRenderMode(RENDER_MODE_FOREGROUND)
    Pickup:setZIndex(-1)
    Pickup:setMaxSpeed(0.075, 0)
    Pickup:setPlacePosition(0, 10, -5)
    Pickup:putActor(Zhenek, 0)

    Mex1 = Actor:new(215, 48, GW_ACTOR, GH_ACTOR, Textures["Mex1"])
    Mex1:setTeam(ACTOR_TEAM_ENEMIES)
    Mex1:setActorAnim(ACTOR_ANIMATION_DEAD, Anims["MexDead"])
    Mex1:setDeathSound(Sounds["ActorDeath"])
    Mex1:setWeapon(Weapons["MexFist"])
    Mex1:playAnimLooped(Anims["MexDraw"])

    MoreMex = {}
    for i = 1, 3 do
        local Mex = Actor:new(-SCREEN_WIDTH, SCREEN_HEIGHT*2, GW_ACTOR, GH_ACTOR, i == 1 and Textures["Mex2"] or Textures["Mex3"])
        Mex:setTeam(ACTOR_TEAM_ENEMIES)
        Mex:setActorAnim(ACTOR_ANIMATION_DEAD, Anims["MexDead"])
        Mex:setDeathSound(Sounds["ActorDeath"])
        Mex:setWeapon(Weapons["MexFist"])

        MoreMex[i] = Mex
    end

    Serega = Actor:new(0, 0, GW_ACTOR, GH_ACTOR, Textures["Serega"])
    Serega:toggleCollidable(false)
    Serega:setState("policeDriving")

    John = Actor:new(0, 0, GW_ACTOR, GH_ACTOR, Textures["John"])
    John:toggleCollidable(false)

    PoliceCar = Car:new(GW_LOCATION*4, 66, 90, 32, Textures["PoliceCar"])
    PoliceCar:setMaxSpeed(0.135, 0)
    PoliceCar:setPlacePosition(0, 0, -4)
    PoliceCar:setPlacePosition(1, 7, -3)
    PoliceCar:setPlacePosition(2, 9, -5)
    PoliceCar:putActor(Serega, 0)
    PoliceCar:putActor(John, 1)
    PoliceCar:putActor(Blank, 2) -- Walkie-talkie
    PoliceCar:turnLeft()

    -- Mission
    L1.defineTriggers()
    L1.defineCutscenes()
    L1.defineStates()

    TimeTicks = 0
    Camera.attach(Player)
    Camera.setBounds({ 0, 0, GROUND_WIDTH, SCREEN_HEIGHT })
    Mission.setGroundBounds({ GROUND_X, GROUND_Y, GROUND_WIDTH, GROUND_HEIGHT })
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

    -- Background
    Graphics.drawFrame(RENDER_MODE_BACKGROUND, 1, false, { 0, 0, GW_LOCATION*4, GH_LOCATION }, Textures["Background1"], 0, 0)
end

function L1.defineTriggers()
    Trigger:new({ GW_LOCATION*1.45, GROUND_Y, 2, GH_LOCATION }, Player, "startMexCutscene")
    Trigger:new({ GW_LOCATION*2.2, GROUND_Y, 2, GH_LOCATION }, Player, "startMoreMexCutscene")
    Trigger:new({ GW_LOCATION*3, SCREEN_HEIGHT/2, 2, SCREEN_HEIGHT }, PoliceCar, "policeStop")

    function Triggers.startMexCutscene(TTrigger, TEntity)
        setmetatable(TEntity, Actor)
        TEntity:setState("mexCutscene")
    end

    function Triggers.startMoreMexCutscene(TTrigger, TEntity)
        setmetatable(TEntity, Actor)
        TEntity:setState("moreMexCutscene")
    end

    function Triggers.policeStop(TTrigger, TEntity)
        PoliceCar:setAcceleration(0.00006, 0)
    end
end

function L1.defineCutscenes()
    States.playerKilledCutscene = Cutscene.new(
        function(TActor)
            return {
                { TActor, true, GTT_WAIT, 500.0 },
                { TActor, true, GTT_FADE_OFF, 1000.0 },
                { TActor, false, GTT_FADE_IN, 0.0 },
            }
        end,
        function(TActor)
            Mission.switchLocation(1)
        end
    )

    States.introCutscene = Cutscene.new(
        function(TActor)
            Pickup:turnLeft()
            Sounds["CarDoorClose"]:play()

            return {
                { Player, true, GTT_FADE_IN, 1000.0 },
                { Zhenek, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "See you later", 0.25, Zhenek, Textures["DialogSquare"]) },
            }
        end,
        function(TActor)
            Sounds["PickupThrottling"]:play()
            Pickup:setAcceleration(-0.00001, 0)
            TActor:setState("")
        end
    )

    States.mexCutscene = Cutscene.new(
        function(TActor)
            Mission.setGroundBounds({ GW_LOCATION, GROUND_Y, GW_LOCATION, GROUND_HEIGHT })
            Mex1:toggleGodMode(true)

            return {
                { Player, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Hey, what're you doing?", 0.25, Player, Textures["DialogSquare"]) },
                { Player, true, GTT_WAIT, 250.0 },

                { Mex1, false, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "KILL ME IF YOU CAN", 0.25, Mex1, Textures["DialogSquare"]) },
                { Mex1, true, GTT_WAIT, 250.0 },
                { Mex1, false, GTT_PUSH_COMMAND, GTC_TURN_LEFT },
                { Mex1, true, GTT_PUSH_COMMAND, GTC_IDLE },
            }
        end,
        function(TActor)
            TActor:setState("playerFightMex")
            Mex1:pushTask(GTT_NONE)
            Mex1:setState("killPlayer")
            Mex1:toggleGodMode(false)
        end
    )

    States.moreMexCutscene = Cutscene.new(
        function(TActor)
            Mission.setGroundBounds({ GW_LOCATION*2, GROUND_Y, GW_LOCATION, GROUND_HEIGHT })
            IsPlayerControllable = false

            for i,v in ipairs(MoreMex) do
                v:setPosition(GW_LOCATION*3.3 + i*10, GROUND_Y + 5 + i*3)
                v:toggleCollidable(false)
            end

            return {
                { Player, false, GTT_GOTO, GW_LOCATION*2.5, GROUND_Y + GROUND_HEIGHT/4},
                { MoreMex[3], false, GTT_GOTO, GW_LOCATION * 2.75, GROUND_Y + GROUND_HEIGHT/4 },
                { MoreMex[2], false, GTT_GOTO, GW_LOCATION * 2.75, GROUND_Y + GROUND_HEIGHT/1.8 },
                { MoreMex[1], false, GTT_GOTO, GW_LOCATION * 2.60, GROUND_Y + GROUND_HEIGHT/2 },

                { MoreMex[1], true, GTT_WAIT, 2500.0 },
                { MoreMex[1], true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Who are you?", 0.25, MoreMex[1], Textures["DialogSquare"]) },

                { Player, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Shit...", 0.25, Player, Textures["DialogSquare"]) },
                { Player, true, GTT_WAIT, 250.0 },
                { Player, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Guys, i don't have problems", 0.25, Player, Textures["DialogSquare"]) },

                { MoreMex[1], true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Listen to me, bald cabron..", 0.25, MoreMex[1], Textures["DialogSquare"]) },
                { MoreMex[1], false, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "You give us everything you have and we will not touch you", 2, MoreMex[1], Textures["DialogSquare"]) },
            }
        end,
        function(TActor)
            Sounds["PoliceStop"]:play()
            TActor:setState("moreMexCutscene2")
        end
    )

    States.moreMexCutscene2 = Cutscene.new(
        function(TActor)
            PoliceCar:setAcceleration(-0.00009, 0)

            return {
                { Player, true, GTT_WAIT, 2500 },
                { MoreMex[3], false, GTT_GOTO, GW_LOCATION * 1.8, GROUND_Y + 1 },
                { MoreMex[2], false, GTT_GOTO, GW_LOCATION * 3.2, GROUND_Y + 1 },
                { MoreMex[2], true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Police...", 1, MoreMex[2], Textures["DialogSquare"]) },

                { Serega, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Hey, what is going on?", 1, Serega, Textures["DialogSquare"]) },
                { Serega, true, GTT_WAIT, 250 },

                { Blank, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Blah-blah", 1, Blank, Textures["DialogSquare"]) },
                { Blank, true, GTT_WAIT, 250 },

                { John, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "We are too busy to help this bald guy", 1, John, Textures["DialogSquare"]) },
                { John, true, GTT_WAIT, 250 },
            }
        end,
        function(TActor)
            PoliceCar:setMaxSpeed(0.135, 0)
            PoliceCar:setAcceleration(-0.00002, 0)
            Sounds["PoliceStart"]:play()

            MoreMex[1]:pushTask(GTT_NONE)
            MoreMex[1]:toggleCollidable(true)
            MoreMex[1]:setState("killPlayer")

            IsPlayerControllable = true
            TActor:setState("moreMexFight1")
        end
    )

    States.moreMexCutscene3 = Cutscene.new(
        function(TActor)
            MoreMex[2]:toggleCollidable(false)
            return {
                { MoreMex[2], false, GTT_GOTO, GW_LOCATION * 2.75, GROUND_Y + 1 },
                { MoreMex[2], true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Come to me, baby", 1, MoreMex[2], Textures["DialogSquare"]) },
                { MoreMex[2], true, GTT_WAIT, 250.0 },

                { Player, false, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Don't call mommy when i kick your ass", 1, Player, Textures["DialogSquare"]) },
            }
        end,
        function(TActor)
            MoreMex[2]:pushTask(GTT_NONE)
            MoreMex[2]:toggleCollidable(true)
            MoreMex[2]:setState("killPlayer")
            TActor:setState("moreMexFight2")
        end
    )

    States.moreMexCutscene4 = Cutscene.new(
        function(TActor)
            MoreMex[3]:toggleCollidable(false)
            return {
                { MoreMex[3], false, GTT_GOTO, GW_LOCATION * 2.25, GROUND_Y + 1 },
                { MoreMex[3], true, GTT_WAIT, 1000.0 },

                { Player, false, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Come on cabrons", 1, Player, Textures["DialogSquare"]) },
            }
        end,
        function(TActor)
            MoreMex[3]:pushTask(GTT_NONE)
            MoreMex[3]:toggleCollidable(true)
            MoreMex[3]:setState("killPlayer")
            TActor:setState("moreMexFight3")
        end
    )
end

function L1.defineStates()
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

    function States.playerFightMexCameraFix(TActor)
        local X,Y = Camera.getPosition()
        if X > GW_LOCATION then
            Camera.setBounds({ GW_LOCATION, 0, GW_LOCATION*2, SCREEN_HEIGHT })
            TActor:setState("")
        end
    end

    function States.playerFightMoreMexCameraFix(TActor)
        local X,Y = Camera.getPosition()
        if X > GW_LOCATION * 2 then
            Camera.setBounds({ GW_LOCATION*2, 0, GW_LOCATION*2, SCREEN_HEIGHT })
            TActor:setState("")
        end
    end

    function States.playerFightMex(TActor)
        if not Mex1:isAlive() then
            Mission.setGroundBounds({ GW_LOCATION, GROUND_Y, GW_LOCATION*2, GROUND_HEIGHT })
            Camera.setBounds({ GW_LOCATION, 0, GW_LOCATION*3, SCREEN_HEIGHT })

            Blank:setState("playerFightMoreMexCameraFix")
            Player:setHealth(100.0)
            TActor:setState("")
        end
    end

    function States.policeDriving(TActor)
        local X,Y = PoliceCar:getVelocity()
        if X > 0.01 then
            PoliceCar:setMaxSpeed(0, 0)
        end
    end

    function States.moreMexFight1(TActor)
        if not MoreMex[1]:isAlive() then
            Player:setHealth(100.0)
            TActor:setState("moreMexCutscene3")
        end
    end

    function States.moreMexFight2(TActor)
        if not MoreMex[2]:isAlive() then
            Player:setHealth(100.0)
            TActor:setState("moreMexCutscene4")
        end
    end

    function States.moreMexFight3(TActor)
        if not MoreMex[3]:isAlive() then
            Mission.setGroundBounds({ GW_LOCATION * 2, GROUND_Y, GW_LOCATION*2, GROUND_HEIGHT })
            Player:setHealth(100.0)
            TActor:setState("")
        end
    end
end
