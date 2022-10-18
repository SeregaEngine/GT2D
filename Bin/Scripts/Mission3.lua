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
    Blank = Actor:new(-SCREEN_WIDTH, SCREEN_HEIGHT*2, 0, 0, Textures["Blank"])
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

    function Triggers.startMexCutscene(TTrigger, TEntity)
        setmetatable(TEntity, Actor)
        TEntity:setState("mexCutscene")
    end

    function Triggers.startMoreMexCutscene(TTrigger, TEntity)
        setmetatable(TEntity, Actor)
        TEntity:setState("moreMexCutscene")
    end
end

function L1.defineCutscenes()
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
            Pickup:setAcceleration(-0.0001, 0)
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
                v:setPosition(GW_LOCATION*3.5 + i*10, GROUND_Y + 5 + i*3)
                v:toggleCollidable(false)
            end

            return {
                { Player, false, GTT_GOTO, GW_LOCATION*2.5, GROUND_Y + GROUND_HEIGHT/4},
                { MoreMex[3], false, GTT_GOTO, GW_LOCATION * 2.75, GROUND_Y + GROUND_HEIGHT/4 },
                { MoreMex[2], false, GTT_GOTO, GW_LOCATION * 2.75, GROUND_Y + GROUND_HEIGHT/1.8 },
                { MoreMex[1], true, GTT_GOTO, GW_LOCATION * 2.60, GROUND_Y + GROUND_HEIGHT/2 },

                { Player, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Hey, what're you doing?", 0.25, Player, Textures["DialogSquare"]) },
                { Player, true, GTT_WAIT, 1000.0 },
            }
        end,
        function(TActor)
            for i,v in ipairs(MoreMex) do
                v:pushTask(GTT_NONE)
                v:setState("killPlayer")
                v:toggleCollidable(true)
            end

            IsPlayerControllable = true
            TActor:setState("playerMoreFightMex")
        end
    )

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
end

function L1.defineStates()
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
            GT_LOG(PR_NOTE, tostring(X))
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
end
