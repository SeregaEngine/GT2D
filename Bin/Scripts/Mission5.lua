----------------------------------------------------------------------
--| * Mission5.lua *
--|
--| Petrol driving from police
----------------------------------------------------------------------

---- Includes
require "Mission"

---- Resources
Textures["Background"] = Resource.defineTexture("Textures/Locations/MissionIntro-LA.png", TW_LOCATION*2, TH_LOCATION)
Textures["Parallax"] = Resource.defineTexture("Textures/Locations/MissionIntro-LA_Parallax.png", TW_LOCATION, TH_LOCATION)
Textures["Barrier"] = Resource.defineTexture("Textures/Locations/MissionIntro-Barrier.png", TW_LOCATION, TH_LOCATION)
Textures["Road"] = Resource.defineTexture("Textures/Locations/MissionIntro-Road.png", TW_LOCATION, TH_LOCATION)
Textures["Player"] = Resource.defineTexture("Textures/Actors/Player.png", TW_ACTOR, TH_ACTOR)
Textures["Serega"] = Resource.defineTexture("Textures/Actors/Serega.png", TW_ACTOR, TH_ACTOR)
Textures["John"] = Resource.defineTexture("Textures/Actors/John.png", TW_ACTOR, TH_ACTOR)
Textures["Dodge"] = Resource.defineTexture("Textures/Cars/Dodge.png", TW_CAR, TH_CAR)
Textures["PoliceCar"] = Resource.defineTexture("Textures/Cars/PoliceCar.png", TW_CAR, TH_CAR)

Anims["DodgeRiding"] = Resource.defineAnimation(2, 4, 1000.0/30)
Anims["PoliceRiding"] = Resource.defineAnimation(0, 4, 1000.0/30)
Anims["PlayerDead"] = Resource.defineAnimation(6, 1, 1)

Sounds["DodgeThrottling"] = Resource.defineSound("Sounds/DodgeThrottlingLong.wav")
Sounds["PoliceThrottling"] = Resource.defineSound("Sounds/PoliceThrottling.wav")
Sounds["PoliceSiren"] = Resource.defineSound("Sounds/PoliceSiren.wav")
Sounds["Crash"] = Resource.defineSound("Sounds/FinalCrash.wav")

Musics["LA"] = Resource.defineMusic("Music/LA.mp3")
Musics["End"] = Resource.defineMusic("Music/End5.mp3")

---- Mission
function Mission.onEnter(Location)
    -- Functions
    Mission.onRender = onRender

    -- Entities
    Player = Actor:new(0, 0, 10, 10, Textures["Player"])
    Player:setState("scene1")
    IsPlayerControllable = false

    Serega = Actor:new(0, 0, 10, 10, Textures["Serega"])
    Serega:toggleCollidable(false)
    local X,Y = Serega:getSpeed()
    Serega:setSpeed(X/2, Y/2)
    John = Actor:new(0, 0, 10, 10, Textures["John"])
    John:toggleCollidable(false)
    John:setSpeed(X/2, Y/2)

    Dodge = Car:new(75, 60, 51, 17, Textures["Dodge"])
    Dodge:turnLeft()
    Dodge:setPlacePosition(0, 1, -3)
    Dodge:putActor(Player, 0)
    Dodge:setMaxSpeed(0.03, 0.01)
    Dodge:setAcceleration(-1, 0)
    Dodge:setAnim(Anims["DodgeRiding"])

    PoliceCar = Car:new(300, 62, 51, 17, Textures["PoliceCar"])
    PoliceCar:turnLeft()
    PoliceCar:setPlacePosition(0, 0, -2)
    PoliceCar:setPlacePosition(1, 4, -1)
    PoliceCar:setMaxSpeed(0, 0)
    PoliceCar:setAcceleration(-1, 0)
    PoliceCar:setAnim(Anims["PoliceRiding"])
    PoliceCar:putActor(Serega, 0)
    PoliceCar:putActor(John, 1)

    -- Cutscenes
    defineCutscenes()

    -- Level
    TimeTicks = Clock.getTicks()
    local LevelWidth = SCREEN_WIDTH * 10
    Camera.setBounds({ -LevelWidth, 0, LevelWidth + SCREEN_WIDTH, SCREEN_HEIGHT })
    Camera.attach(Player)

    Musics["LA"]:play()
    Sounds["DodgeThrottling"]:play()
end

function Mission.onUpdate(dt)
    TimeTicks = Clock.getTicks()
end

function onRender()
    local X,Y = Camera.getPosition()

    -- LA
    local ParallaxX = (-X*0.075 + TimeTicks/750) % GW_LOCATION
    Graphics.drawFrame(RENDER_MODE_BACKGROUND, -1, true, { ParallaxX, Y, GW_LOCATION, GH_LOCATION }, Textures["Parallax"], 0, 0)
    Graphics.drawFrame(RENDER_MODE_BACKGROUND, -1, true, { ParallaxX - GW_LOCATION, Y, GW_LOCATION, GH_LOCATION }, Textures["Parallax"], 0, 0)

    Graphics.drawFrame(RENDER_MODE_BACKGROUND, 0, true, { -GW_LOCATION - X*0.1, Y, GW_LOCATION*2, GH_LOCATION }, Textures["Background"], 0, 0)

    -- Barrier and road
    local FastX = -(X*4) % GW_LOCATION
    local FastX2 = FastX - GW_LOCATION

    Graphics.drawFrame(RENDER_MODE_BACKGROUND, 1, true, { FastX, 0, GW_LOCATION, GH_LOCATION }, Textures["Barrier"], 0, 0)
    Graphics.drawFrame(RENDER_MODE_BACKGROUND, 1, true, { FastX2, 0, GW_LOCATION, GH_LOCATION }, Textures["Barrier"], 0, 0)

    Graphics.drawFrame(RENDER_MODE_BACKGROUND, 2, true, { FastX, 0, GW_LOCATION, GH_LOCATION }, Textures["Road"], 0, 0)
    Graphics.drawFrame(RENDER_MODE_BACKGROUND, 2, true, { FastX2, 0, GW_LOCATION, GH_LOCATION }, Textures["Road"], 0, 0)
end

function onRenderFaded()
    Graphics.setDrawColor(0, 0, 0, 255)
    Graphics.fillRect(RENDER_MODE_FOREGROUND, 999, true, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT })
end

function defineCutscenes()
    States.scene1 = Cutscene.new(
        function(TActor)
            return {
                { Player, true, GTT_FADE_IN, 5000 },
                { Player, true, GTT_WAIT, 1000 },
                { Player, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "It's the end.", 5, Player, Textures["DialogSquare"]) },
                { Player, true, GTT_WAIT, 250 },
                { Player, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "I'll back to my family soon...", 6, Player, Textures["DialogSquare"]) },
                { Player, true, GTT_WAIT, 2000 },
            }
        end,
        function(TActor)
            TActor:setState("scene2")
        end
    )

    States.scene2 = Cutscene.new(
        function(TActor)
            Sounds["PoliceThrottling"]:play()
            Sounds["PoliceSiren"]:play()
            return {
                { Player, true, GTT_WAIT, 2000 },
            }
        end,
        function(TActor)
            TActor:setState("scene3")
        end
    )

    States.scene3 = Cutscene.new(
        function(TActor)
            local X,Y = Camera.getPosition()
            PoliceCar:setPosition(X + GW_LOCATION*1.5, 60)
            PoliceCar:setMaxSpeed(0.04, 0.01)
            return {
                { Player, true, GTT_WAIT, 7500 },
            }
        end,
        function(TActor)
            TActor:setState("scene4")
        end
    )

    States.scene4 = Cutscene.new(
        function(TActor)
            PoliceCar:setMaxSpeed(0.030, 0.01)
            return {
                { Serega, true, GTT_WAIT, 250 },
                { Serega, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Petrol, stop the car right now!", 3, Serega, Textures["DialogSquare"]) },
                { Serega, true, GTT_WAIT, 250 },

                { Player, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Shit, man...", 2, Player, Textures["DialogSquare"]) },
                { Player, true, GTT_WAIT, 2500 },
            }
        end,
        function(TActor)
            TActor:setState("scene5")
        end
    )

    States.scene5 = Cutscene.new(
        function(TActor)
            Dodge:setMaxSpeed(0.027, 0.01)
            return {
                { Player, true, GTT_WAIT, 3000 },
                { Player, true, GTT_FADE_OFF, 500 },
            }
        end,
        function(TActor)
            Sound.stopAll()
            Mission.onRender = onRenderFaded
            TActor:setState("scene6")
        end
    )

    States.scene6 = Cutscene.new(
        function(TActor)
            Sounds["Crash"]:play()
            Musics["End"]:play()
            return {
                { Player, true, GTT_WAIT, 6000 },
            }
        end,
        function(TActor)
            TActor:setState("scene7")
        end
    )

    States.scene7 = Cutscene.new(
        function(TActor)
            Mission.onRender = onRender
            local X,Y = Camera.getPosition()

            PoliceCar:setPosition(X, Y - 999)
            Dodge:setPosition(X, Y - 999)
            Dodge:ejectActor(0)
            PoliceCar:ejectActor(0)
            PoliceCar:ejectActor(1)

            Player:setPosition(X + GW_LOCATION/2, 60)
            Player:playAnimLooped(Anims["PlayerDead"])

            Serega:setPosition(X - 48, 56)
            John:setPosition(X - 40, 54)

            return {
                { Player, true, GTT_FADE_IN, 2000 },
                { Player, true, GTT_WAIT, 2500 },
            }
        end,
        function(TActor)
            TActor:setState("scene8")
        end
    )

    States.scene8 = Cutscene.new(
        function(TActor)
            local X,Y = Player:getPosition()
            return {
                { Serega, false, GTT_GOTO, X - 12, Y + 3 },
                { John, true, GTT_GOTO, X - 7, Y + 1 },
                { Serega, true, GTT_WAIT, 1000 },
                { John, false, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "God bless you..", 6, John, Textures["DialogSquare"]) },
                { John, true, GTT_WAIT, 3500 },
                { John, true, GTT_FADE_OFF, 20000 },
            }
        end,
        function(TActor)
            Mission.onRender = onRenderFaded
            Mission.switch("Scripts/Credits.lua", 1)
            TActor:setState("")
        end
    )
end
