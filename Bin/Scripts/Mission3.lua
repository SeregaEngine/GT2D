----------------------------------------------------------------------
--| * Mission3.lua *
--|
--| Texas mission, where Petrol steals trash car near bar
----------------------------------------------------------------------

---- Includes
require "Mission"

---- Resources
Textures["Background1"] = Resource.defineTexture("Textures/Locations/Mission3-1.png", TW_LOCATION*4, TH_LOCATION)
Textures["Foreground1"] = Resource.defineTexture("Textures/Locations/Mission3-1_2.png", TW_LOCATION*4, TH_LOCATION)
Textures["Background2"] = Resource.defineTexture("Textures/Locations/Mission3-2.png", TW_LOCATION, TH_LOCATION)
Textures["Background3"] = Textures["Background1"]
Textures["Foreground3"] = Textures["Foreground1"]
Textures["Parallax1"] = Resource.defineTexture("Textures/Locations/Mission3-1_Parallax.png", TW_LOCATION*2, TH_LOCATION)
Textures["Parallax3"] = Textures["Parallax1"]

Textures["Pickup"] = Resource.defineTexture("Textures/Cars/Pickup.png", TW_CAR, TH_CAR)
Textures["TrashCar"] = Resource.defineTexture("Textures/Cars/TrashCar.png", TW_CAR, TH_CAR)
Textures["PoliceCar"] = Resource.defineTexture("Textures/Cars/PoliceCar.png", TW_CAR, TH_CAR)

Textures["Player"] = Resource.defineTexture("Textures/Actors/Player.png", TW_ACTOR, TH_ACTOR)
Textures["Zhenek"] = Resource.defineTexture("Textures/Actors/Zhenek.png", TW_ACTOR, TH_ACTOR)
Textures["Serega"] = Resource.defineTexture("Textures/Actors/Serega.png", TW_ACTOR, TH_ACTOR)
Textures["John"] = Resource.defineTexture("Textures/Actors/John.png", TW_ACTOR, TH_ACTOR)
Textures["Mex1"] = Resource.defineTexture("Textures/Actors/Mex1.png", TW_ACTOR, TH_ACTOR)
Textures["Mex2"] = Resource.defineTexture("Textures/Actors/Mex2.png", TW_ACTOR, TH_ACTOR)
Textures["Mex3"] = Resource.defineTexture("Textures/Actors/Mex3.png", TW_ACTOR, TH_ACTOR)
Textures["Dog"] = Resource.defineTexture("Textures/Actors/Dog.png", TW_ACTOR, TH_ACTOR)
Textures["Vlassanov"] = Resource.defineTexture("Textures/Actors/Vlassanov.png", TW_ACTOR, TH_ACTOR)
Textures["Stranger"] = Resource.defineTexture("Textures/Actors/Stranger.png", TW_ACTOR, TH_ACTOR)

Sounds["PickupThrottling"] = Resource.defineSound("Sounds/PickupThrottling.wav")
Sounds["PoliceStart"] = Resource.defineSound("Sounds/PoliceCarStart.wav")
Sounds["PoliceStop"] = Resource.defineSound("Sounds/PoliceCarStop.wav")
Sounds["DogDeath"] = Resource.defineSound("Sounds/DogDyingSound.wav")
Sounds["DogPunch1"] = Resource.defineSound("Sounds/DogPunch1.wav")
Sounds["DogPunch2"] = Resource.defineSound("Sounds/DogPunch2.wav")
Sounds["DogPunch3"] = Resource.defineSound("Sounds/DogPunch3.wav")
Sounds["PickUp"] = Resource.defineSound("Sounds/ItemPickUp.wav")

Sounds["Police1"] = Resource.defineSound("Sounds/PoliceBatonHit1.wav")
Sounds["Police2"] = Resource.defineSound("Sounds/PoliceBatonHit2.wav")
Sounds["Police3"] = Resource.defineSound("Sounds/PoliceBatonHit3.wav")

Sounds["Colt1"] = Resource.defineSound("Sounds/ColtShot1.wav")
Sounds["Colt2"] = Resource.defineSound("Sounds/ColtShot2.wav")
Sounds["Colt3"] = Resource.defineSound("Sounds/ColtShot3.wav")

Musics["Ambient1"] = Resource.defineMusic("Music/Nature.mp3")
Musics["Ambient2"] = Resource.defineMusic("Music/TexasPub.mp3")
Musics["Ambient3"] = Musics["Ambient1"]

Anims["PlayerDead"] = Resource.defineAnimation(5, 3, 1000.0 / 2)
Anims["MexFist"] = Resource.defineAnimation(4, 3, 1000.0 / 2)
Anims["MexDead"] = Resource.defineAnimation(5, 3, 1000.0 / 2)
Anims["MexDraw"] = Resource.defineAnimation(6, 3, 1000.0 / 10)
Anims["DogAttack"] = Resource.defineAnimation(4, 3, 1000.0 / 2)
Anims["DogWalk"] = Resource.defineAnimation(1, 5, 1000.0 / 12)
Anims["DogDead"] = Resource.defineAnimation(5, 3, 1000.0 / 2)

Weapons["Fist"] = Resource.defineWeapon(Resource.defineAnimation(4, 3, 1000.0 / 2.0), 8, 8, 20, Sounds["Punch1"], Sounds["Punch2"], Sounds["Punch3"], Sounds["Punch4"])
Weapons["MexFist"] = Resource.defineWeapon(Anims["MexFist"], 8, 8, 10, Sounds["Punch1"], Sounds["Punch2"], Sounds["Punch3"], Sounds["Punch4"])
Weapons["DogFist"] = Resource.defineWeapon(Anims["DogAttack"], 8, 8, 3, Sounds["DogPunch1"], Sounds["DogPunch2"], Sounds["DogPunch3"])

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

    Player = Actor:new(50, 55, GW_ACTOR, GH_ACTOR, Textures["Player"])
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

    Dog1 = Actor:new(GW_LOCATION * 3.6, 48, GW_ACTOR, GH_ACTOR, Textures["Dog"])
    Dog1:setTeam(ACTOR_TEAM_ENEMIES)
    Dog1:setActorAnim(ACTOR_ANIMATION_HORIZONTAL, Anims["DogWalk"])
    Dog1:setActorAnim(ACTOR_ANIMATION_DEAD, Anims["DogDead"])
    Dog1:setDeathSound(Sounds["DogDeath"])
    Dog1:setWeapon(Weapons["DogFist"])

    Dog2 = Actor:new(GW_LOCATION * 3.6, 56, GW_ACTOR, GH_ACTOR, Textures["Dog"])
    Dog2:setTeam(ACTOR_TEAM_ENEMIES)
    Dog2:setActorAnim(ACTOR_ANIMATION_HORIZONTAL, Anims["DogWalk"])
    Dog2:setActorAnim(ACTOR_ANIMATION_DEAD, Anims["DogDead"])
    Dog2:setDeathSound(Sounds["DogDeath"])
    Dog2:setWeapon(Weapons["DogFist"])

    -- Mission
    L1.defineTriggers()
    L1.defineCutscenes()
    L1.defineStates()

    TimeTicks = 0
    Camera.attach(Player)
    Camera.setBounds({ 0, 0, GROUND_WIDTH, SCREEN_HEIGHT })
    Mission.setGroundBounds({ GROUND_X, GROUND_Y, GROUND_WIDTH, GROUND_HEIGHT })
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

    -- Background
    Graphics.drawFrame(RENDER_MODE_BACKGROUND, 1, false, { 0, 0, GW_LOCATION*4, GH_LOCATION }, Textures["Background1"], 0, 0)

    -- Foreground
    Graphics.drawFrame(RENDER_MODE_FOREGROUND, 1, false, { 0, 0, GW_LOCATION*4, GH_LOCATION }, Textures["Foreground1"], 0, 0)

    Graphics.drawFrame(RENDER_MODE_BACKGROUND, 2, false, { GW_LOCATION*4 - 85, 30, 64, 18 }, Textures["TrashCar"])
end

function L1.defineTriggers()
    Trigger:new({ GW_LOCATION*1.45, GROUND_Y, 2, GH_LOCATION }, Player, "startMexCutscene")
    Trigger:new({ GW_LOCATION*2.2, GROUND_Y, 2, GH_LOCATION }, Player, "startMoreMexCutscene")
    Trigger:new({ GW_LOCATION*3, SCREEN_HEIGHT/2, 2, SCREEN_HEIGHT }, PoliceCar, "policeStop")
    Trigger:new({ GROUND_WIDTH - 20, SCREEN_HEIGHT/2, 2, SCREEN_HEIGHT }, Player, "comeToBar")

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

    function Triggers.comeToBar(TTrigger, TEntity)
        Player:setState("comeToBarCutscene")
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
                { Player, false, GTT_FADE_IN, 3500.0 },
                { Player, true, GTT_WAIT, 1000 },
                { Zhenek, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "See you later", 2, Zhenek, Textures["DialogSquare"]) },
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
                { Player, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Hey, what're you doing?", 2, Player, Textures["DialogSquare"]) },
                { Player, true, GTT_WAIT, 250.0 },

                { Mex1, false, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "It's not your busisness, cabron", 2, Mex1, Textures["DialogSquare"]) },
                { Mex1, true, GTT_WAIT, 1500.0 },
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
                { MoreMex[3], false, GTT_GOTO, GW_LOCATION * 2.75, GROUND_Y + GROUND_HEIGHT/6 },
                { MoreMex[2], false, GTT_GOTO, GW_LOCATION * 2.75, GROUND_Y + GROUND_HEIGHT/1.8 },
                { MoreMex[1], false, GTT_GOTO, GW_LOCATION * 2.65, GROUND_Y + GROUND_HEIGHT/3 },

                { MoreMex[1], true, GTT_WAIT, 2500.0 },
                { MoreMex[1], true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Well, well, look at there..", 3, MoreMex[1], Textures["DialogSquare"]) },

                { Player, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Shit...", 1, Player, Textures["DialogSquare"]) },
                { Player, true, GTT_WAIT, 250.0 },

                { MoreMex[1], true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "What are you doing on my block?", 2.5, MoreMex[1], Textures["DialogSquare"]) },
                { MoreMex[1], true, GTT_WAIT, 250.0 },

                { Player, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Guys, i don't have problems", 2, Player, Textures["DialogSquare"]) },
                { Player, true, GTT_WAIT, 250.0 },

                { MoreMex[1], false, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Gimme all your money, now!", 2, MoreMex[1], Textures["DialogSquare"]) },
                { MoreMex[1], true, GTT_WAIT, 500.0 },

                { MoreMex[3], false, GTT_GOTO, GW_LOCATION * 1.8, GROUND_Y + 1 },
                { MoreMex[2], false, GTT_GOTO, GW_LOCATION * 3.2, GROUND_Y + 1 },
                { MoreMex[2], false, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Police...", 1, MoreMex[2], Textures["DialogSquare"]) },
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
                { Player, true, GTT_WAIT, 3500 },

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

                { Player, false, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Don't call mommy when i kick your ass", 2, Player, Textures["DialogSquare"]) },
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

                { Player, false, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Come on, cabrons", 1, Player, Textures["DialogSquare"]) },
            }
        end,
        function(TActor)
            MoreMex[3]:pushTask(GTT_NONE)
            MoreMex[3]:toggleCollidable(true)
            MoreMex[3]:setState("killPlayer")
            TActor:setState("moreMexFight3")
        end
    )

    States.comeToBarCutscene = Cutscene.new(
        function(TActor)
            IsPlayerControllable = false
            Player:toggleCollidable(false)

            return {
                { Player, false, GTT_GOTO, GROUND_WIDTH * 2, GROUND_Y + 1 },
                { Player, true, GTT_FADE_OFF, 2000.0 },
                { Player, false, GTT_FADE_IN, 0 },
            }
        end,
        function(TActor)
            Saver.save("Scripts/Mission3.lua", 2)
            Mission.switchLocation(2)
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
            Dialog:new(GW_DIALOG, GH_DIALOG, "Ohh, madre...", 1.5, Mex1, Textures["DialogSquare"]):run()
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
            Dialog:new(GW_DIALOG, GH_DIALOG, "Ok-ok, you won..", 1.5, MoreMex[3], Textures["DialogSquare"]):run()

            Mission.setGroundBounds({ GW_LOCATION * 2, GROUND_Y, GW_LOCATION*2, GROUND_HEIGHT })
            Player:setHealth(100.0)
            TActor:setState("addDogs")
        end
    end

    function States.addDogs(TActor)
        Dog1:setState("killPlayer")
        Dog2:setState("killPlayer")
        TActor:setState("fightDogs")
    end

    function States.fightDogs(TActor)
        if not Dog1:isAlive() and not Dog2:isAlive() then
            Mission.setGroundBounds({ 0, GROUND_Y, GROUND_WIDTH, GROUND_HEIGHT })
            Player:setHealth(100.0)
            TActor:setState("")
        end
    end
end

---- Location 2
function L2.onEnter()
    -- Functions
    Mission.onUpdate = L2.onUpdate
    Mission.onRender = L2.onRender

    -- Defines
    GROUND_WIDTH = GW_LOCATION
    GROUND_HEIGHT = 20
    GROUND_X = 0
    GROUND_Y = GH_LOCATION - GROUND_HEIGHT

    -- Entities
    Player = Actor:new(10, 50, GW_ACTOR, GH_ACTOR, Textures["Player"])
    Player:setActorAnim(ACTOR_ANIMATION_DEAD, Anims["PlayerDead"])
    Player:setDeathSound(Sounds["ActorDeath"])
    Player:setWeapon(Weapons["Fist"])
    Player:setTeam(ACTOR_TEAM_FRIENDS)
    Player:setState("introCutscene")

    Vlassanov = Actor:new(70, 49.5, GW_ACTOR, GH_ACTOR, Textures["Vlassanov"])
    Vlassanov:setTeam(ACTOR_TEAM_ENEMIES)
    Vlassanov:setActorAnim(ACTOR_ANIMATION_DEAD, Anims["MexDead"]) -- Placeholders
    Vlassanov:setDeathSound(Sounds["ActorDeath"])
    Vlassanov:setWeapon(Weapons["MexFist"])

    Stranger = Actor:new(86, 48, GW_ACTOR, GH_ACTOR, Textures["Stranger"])
    Stranger:setTeam(ACTOR_TEAM_ENEMIES)
    Stranger:setActorAnim(ACTOR_ANIMATION_DEAD, Anims["MexDead"]) -- Placeholders
    Stranger:setDeathSound(Sounds["ActorDeath"])
    Stranger:setWeapon(Weapons["MexFist"])

    -- Cutscenes and triggers
    L2.defineTriggers()
    L2.defineCutscenes()
    L2.defineStates()

    -- Mission
    Camera.attach(Player)
    Camera.setBounds({ 0, 0, GROUND_WIDTH, SCREEN_HEIGHT })
    Mission.setGroundBounds({ GROUND_X, GROUND_Y, GROUND_WIDTH, GROUND_HEIGHT })

    Musics["Ambient2"]:play()
end

function L2.onUpdate(dt)
    Input.defaultHandle()
end

function L2.onRender()
    Graphics.drawFrame(RENDER_MODE_BACKGROUND, 0, true, { 0, 0, GW_LOCATION, GH_LOCATION }, Textures["Background2"])
end

function L2.defineTriggers()
    function Triggers.leave(TTriger, TEntity)
        Player:setState("leaveCutscene")
    end
end

function L2.defineCutscenes()
    States.playerKilledCutscene = Cutscene.new(
        function(TActor)
            return {
                { TActor, true, GTT_WAIT, 500.0 },
                { TActor, true, GTT_FADE_OFF, 1000.0 },
                { TActor, false, GTT_FADE_IN, 0.0 },
            }
        end,
        function(TActor)
            Mission.switchLocation(2)
        end
    )

    States.introCutscene = Cutscene.new(
        function(TActor)
            IsPlayerControllable = false
            Stranger:turnLeft()

            return {
                { Player, false, GTT_FADE_IN, 3500 },
                { Player, true, GTT_WAIT, 1000 },

                { Vlassanov, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "..and I told her that I am the son of an oil magnate", 4, Vlassanov, Textures["DialogSquare"]) },
                { Vlassanov, true, GTT_WAIT, 250 },

                { Stranger, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "That's how we roll, man", 2.5, Stranger, Textures["DialogSquare"]) },
                { Stranger, true, GTT_WAIT, 250 },

                { Player, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "I think they have keys", 2, Player, Textures["DialogSquare"]) },
                { Player, true, GTT_WAIT, 250 },

                { Stranger, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Wait, who is this guy?", 3, Stranger, Textures["DialogSquare"]) },
                { Stranger, true, GTT_WAIT, 250 },

                { Vlassanov, true, GTT_PUSH_COMMAND, GTC_TURN_LEFT },
                { Vlassanov, true, GTT_WAIT, 250 },
                { Vlassanov, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Let's show him where is his place", 2, Vlassanov, Textures["DialogSquare"]) },
                { Vlassanov, true, GTT_WAIT, 250 },

                { Player, false, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Fuck..", 1, Player, Textures["DialogSquare"]) },
                { Player, true, GTT_WAIT, 500 },

                { Vlassanov, false, GTT_NONE },
                { Stranger, false, GTT_NONE },
            }
        end,
        function(TActor)
            Vlassanov:setState("killPlayer")

            IsPlayerControllable = true
            TActor:setState("fight")
        end
    )

    States.leaveCutscene = Cutscene.new(
        function(TActor)
            Player:toggleCollidable(false)
            IsPlayerControllable = false

            return {
                { Player, false, GTT_GOTO, -50, GROUND_Y },
                { Player, true, GTT_FADE_OFF, 2500 },
                { Player, false, GTT_FADE_IN, 0 },
            }
        end,
        function(TActor)
            Saver.save("Scripts/Mission3.lua", 3)
            Mission.switchLocation(3)
        end
    )
end

function L2.defineStates()
    IsStrangerTalked = false

    function States.fight(TActor)
        if not Vlassanov:isAlive() then
            if not Stranger:isAlive() then
				Trigger:new({ 1, SCREEN_HEIGHT/2, 2, SCREEN_HEIGHT }, Player, "leave")
				Dialog:new(GW_DIALOG, GH_DIALOG, "I found keys", 3, Player, Textures["DialogSquare"]):run()
				Sounds["PickUp"]:play()
				TActor:setState("")
            else
                if not IsStrangerTalked then
					Dialog:new(GW_DIALOG, GH_DIALOG, "Come here, babe", 1.5, Stranger, Textures["DialogSquare"]):run()
                    IsStrangerTalked = true
				end
                Stranger:setState("killPlayer")
            end
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

---- Location 3
function L3.onEnter()
    -- Functions
    Mission.onUpdate = L3.onUpdate
    Mission.onRender = L3.onRender

    -- Defines
    GROUND_WIDTH = GW_LOCATION * 4
    GROUND_HEIGHT = 20
    GROUND_X = 0
    GROUND_Y = GH_LOCATION - GROUND_HEIGHT

    -- Entities
    Blank = Actor:new(GROUND_WIDTH-5, GROUND_Y, 1, 1, Textures["Blank"])

    Player = Actor:new(GROUND_WIDTH, 60, GW_ACTOR, GH_ACTOR, Textures["Player"])
    Player:setActorAnim(ACTOR_ANIMATION_DEAD, Anims["PlayerDead"])
    Player:setDeathSound(Sounds["ActorDeath"])
    Player:setWeapon(Weapons["Fist"])
    Player:setTeam(ACTOR_TEAM_FRIENDS)
    Player:setState("introCutscene")
    Player:toggleCollidable(false)
    IsPlayerControllable = false

    Zhenek = Actor:new(0, 0, GW_ACTOR, GH_ACTOR, Textures["Zhenek"])
    Zhenek:setTeam(ACTOR_TEAM_FRIENDS)
    Zhenek:setState("zhenekDriving")

    Pickup = Car:new(GROUND_WIDTH - 110, 68, 107, 30, Textures["Pickup"])
    Pickup:setRenderMode(RENDER_MODE_FOREGROUND)
    Pickup:setZIndex(-1)
    Pickup:setMaxSpeed(0.075, 0)
    Pickup:setPlacePosition(0, 10, -5)
    Pickup:putActor(Zhenek, 0)
    Pickup:turnLeft()

    Trash = Car:new(GROUND_WIDTH - 5, 68, 90, 25.2, Textures["TrashCar"])
    Trash:setRenderMode(RENDER_MODE_FOREGROUND)
    Trash:setZIndex(-1)
    Trash:setMaxSpeed(0.075, 0)
    Trash:setPlacePosition(0, 5, -4)
    Trash:turnLeft()

    Serega = Actor:new(GROUND_WIDTH - GW_LOCATION * 1.5, GROUND_Y, GW_ACTOR, GH_ACTOR, Textures["Serega"])
    Serega:toggleCollidable(false)

    John = Actor:new(GROUND_WIDTH - GW_LOCATION * 1.3, GROUND_Y + 1, GW_ACTOR, GH_ACTOR, Textures["John"])
    John:toggleCollidable(false)

    -- Mission
    L3.defineCutscenes()
    L3.defineStates()

    TimeTicks = 0
    Camera.setBounds({ 0, 0, GROUND_WIDTH, SCREEN_HEIGHT })
    Camera.attach(Player)
    Camera.detach()
    Mission.setGroundBounds({ GROUND_X, GROUND_Y, GROUND_WIDTH, GROUND_HEIGHT })
    Musics["Ambient3"]:play()
end

function L3.onUpdate(dt)
    TimeTicks = Clock.getTicks()
end

function L3.onRender()
    -- Parallax
    local XCamera, YCamera = getCameraPosition()
    local X = -(TimeTicks/1000.0 + XCamera/2.0) % (GW_LOCATION*2)

    Graphics.drawFrame(RENDER_MODE_BACKGROUND, 0, true, { X, 0, GW_LOCATION*2, GH_LOCATION }, Textures["Parallax3"])
    Graphics.drawFrame(RENDER_MODE_BACKGROUND, 0, true, { X-GW_LOCATION*2, 0, GW_LOCATION*2, GH_LOCATION }, Textures["Parallax3"])

    -- Background
    Graphics.drawFrame(RENDER_MODE_BACKGROUND, 1, false, { 0, 0, GW_LOCATION*4, GH_LOCATION }, Textures["Background3"], 0, 0)

    -- Foreground
    Graphics.drawFrame(RENDER_MODE_FOREGROUND, -5, false, { 0, 0, GW_LOCATION*4, GH_LOCATION }, Textures["Foreground3"], 0, 0)

    -- Fade
    Graphics.setDrawColor(0, 0, 0, 40)
    Graphics.fillRect(RENDER_MODE_FOREGROUND, -999, true, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT })

    -- Rope between cars
    Graphics.setDrawColor(120, 60, 40, 255)
    local X1,Y1 = Pickup:getPosition()
    local X2,Y2 = Trash:getPosition()
    Graphics.fillRect(RENDER_MODE_FOREGROUND, -2, false, { X1, Y1, X2-X1, 2 })
end

function L3.defineCutscenes()
    States.introCutscene = Cutscene.new(
        function(TActor)
            Sounds["StartEngine"]:play()
            local X,Y = Trash:getPosition()

            return {
                { Player, false, GTT_GOTO, GROUND_WIDTH - 30, GROUND_Y },
                { Player, true, GTT_FADE_IN, 2000 },

                { Zhenek, true, GTT_WAIT, 500 },
                { Zhenek, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Come on, Petrol! Sit in the car", 3, Zhenek, Textures["DialogSquare"]) },

                { Player, true, GTT_WAIT, 500 },
                { Player, false, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Man.. how you did this", 4, Player, Textures["DialogSquare"]) },
                { Player, true, GTT_WAIT, 100 },
                { Player, true, GTT_GOTO, X, Y },
            }
        end,
        function(TActor)
            Sounds["CarDoorOpen"]:play()
            Sounds["PickupThrottling"]:play()
            Trash:putActor(Player, 0)
            TActor:setState("scene2")
        end
    )

    States.scene2 = Cutscene.new(
        function(TActor)
            Pickup:setAcceleration(-0.0001, 0)

            return {
                { Serega, false, GTT_GOTO, GROUND_WIDTH + 10, GROUND_Y },
                { John, true, GTT_GOTO, GROUND_WIDTH - 50, GROUND_Y + 1 },
                { John, false, GTT_RUN_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Blah-blah", 0.25, John, Textures["DialogSquare"]) },

                { John, true, GTT_GOTO, GROUND_WIDTH, GROUND_Y + 1 },
                { John, false, GTT_GOTO, GROUND_WIDTH + 10, GROUND_Y + 1 },
                { John, true, GTT_FADE_OFF, 1000 },
                { John, true, GTT_FADE_IN, 1000 },

                { Blank, true, GTT_WAIT, 250, },
                { Blank, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Blah-blah", 0.25, Blank, Textures["DialogSquare"]) },
                { Blank, true, GTT_WAIT, 250, },
                { Blank, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Blah-blah", 0.25, Blank, Textures["DialogSquare"]) },
            }
        end,
        function(TActor)
            Sounds["Colt1"]:play()
            TActor:setState("scene3")
        end
    )

    States.scene3 = Cutscene.new(
        function(TActor)
            return {
                { Blank, true, GTT_WAIT, 500 },
            }
        end,
        function(TActor)
            Sounds["Colt2"]:play()
            TActor:setState("scene4")
        end
    )

    States.scene4 = Cutscene.new(
        function(TActor)
            return {
                { Blank, true, GTT_WAIT, 100 },
            }
        end,
        function(TActor)
            Sounds["Colt3"]:play()
            TActor:setState("scene5")
        end
    )

    States.scene5 = Cutscene.new(
        function(TActor)
            return {
                { Blank, true, GTT_WAIT, 750 },
                { Blank, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Shit... man", 0.25, Blank, Textures["DialogSquare"]) },
                { Blank, true, GTT_WAIT, 100 },
            }
        end,
        function(TActor)
            Sounds["Colt1"]:play()
            TActor:setState("scene6")
        end
    )

    States.scene6 = Cutscene.new(
        function(TActor)
            return {
                { Blank, true, GTT_WAIT, 250 },
                { Blank, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Come on", 0.25, Blank, Textures["DialogSquare"]) },
            }
        end,
        function(TActor)
            Sounds["Police1"]:play()
            TActor:setState("scene7")
        end
    )

    States.scene7 = Cutscene.new(
        function(TActor)
            return {
                { Blank, true, GTT_WAIT, 250 },
            }
        end,
        function(TActor)
            Sounds["Police2"]:play()
            TActor:setState("scene8")
        end
    )

    States.scene8 = Cutscene.new(
        function(TActor)
            return {
                { Blank, true, GTT_WAIT, 350 },
            }
        end,
        function(TActor)
            Sounds["Police3"]:play()
            TActor:setState("scene9")
        end
    )

    States.scene9 = Cutscene.new(
        function(TActor)
            return {
                { Blank, true, GTT_WAIT, 650 },
            }
        end,
        function(TActor)
            Sounds["Colt2"]:play()
            TActor:setState("scene10")
        end
    )

    States.scene10 = Cutscene.new(
        function(TActor)
            return {
                { Blank, true, GTT_WAIT, 1000 },
            }
        end,
        function(TActor)
            Sounds["Colt3"]:play()
            TActor:setState("scene11")
        end
    )

    States.scene11 = Cutscene.new(
        function(TActor)
            return {
                { Blank, true, GTT_FADE_OFF, 5000 },
                { Blank, false, GTT_FADE_IN, 0 },
            }
        end,
        function(TActor)
			Saver.save("Scripts/Mission4.lua", 1)
			Mission.switch("Scripts/Mission4.lua", 1)
            TActor:setState("")
        end
    )
end

function L3.defineStates()
    function States.zhenekDriving(TActor)
        local X,Y = Pickup:getVelocity()
        Trash:setVelocity(X, Y)
    end
end
