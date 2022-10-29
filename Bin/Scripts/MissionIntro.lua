----------------------------------------------------------------------
--| * MissionIntro.lua *
----------------------------------------------------------------------

---- Includes
require "Mission"

---- Resources
Textures["Background"] = Resource.defineTexture("Textures/Locations/MissionIntro-LA.png", TW_LOCATION*2, TH_LOCATION)
Textures["Parallax"] = Resource.defineTexture("Textures/Locations/MissionIntro-LA_Parallax.png", TW_LOCATION, TH_LOCATION)
Textures["Barrier"] = Resource.defineTexture("Textures/Locations/MissionIntro-Barrier.png", TW_LOCATION, TH_LOCATION)
Textures["Road"] = Resource.defineTexture("Textures/Locations/MissionIntro-Road.png", TW_LOCATION, TH_LOCATION)
Textures["Player"] = Resource.defineTexture("Textures/Actors/Player.png", TW_ACTOR, TH_ACTOR)
Textures["Dodge"] = Resource.defineTexture("Textures/Cars/Dodge.png", TW_CAR, TH_CAR)

Anims["DodgeRiding"] = Resource.defineAnimation(2, 4, 1000.0/15)

Sounds["Crush"] = Resource.defineSound("Sounds/CarAccident.wav")
Sounds["Throttling"] = Resource.defineSound("Sounds/DodgeThrottlingLong.wav")
Musics["LA"] = Resource.defineMusic("Music/LA.mp3")

---- Mission
function Mission.onEnter(Location)
    -- Entities
    Player = Actor:new(0, 0, 10, 10, Textures["Player"])
    Player:setState("riding")
    IsPlayerControllable = false

    Dodge = Car:new(75, 60, 51, 17, Textures["Dodge"])
    Dodge:turnLeft()
    Dodge:setPlacePosition(0, 1, -3)
    Dodge:putActor(Player, 0)
    Dodge:setMaxSpeed(0.03, 0.01)
    Dodge:setAcceleration(-1, 0)
    Dodge:setAnim(Anims["DodgeRiding"])

    -- Cutscenes
    defineCutscenes()

    -- Level
    local LevelWidth = SCREEN_WIDTH * 10
    Camera.setBounds({ -LevelWidth, 0, LevelWidth + SCREEN_WIDTH, SCREEN_HEIGHT })
    Camera.attach(Player)
    TimeTicks = Clock.getTicks()

    Musics["LA"]:play()
    Sounds["Throttling"]:play()
end

function Mission.onUpdate(dt)
    TimeTicks = Clock.getTicks()
end

function Mission.onRender()
    local X,Y = getCameraPosition()

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
    Graphics.fillRect(RENDER_MODE_BACKGROUND, 0, true, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT })
end

function defineCutscenes()
    States.riding = Cutscene.new(
        function(TActor)
            return {
                { Player, true, GTT_FADE_IN, 15000.0 },

                -- TODO(sean) Paste dialogs
                { Player, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "", 0.25, Player, Textures["DialogSquare"]) },
                { Player, true, GTT_WAIT, 20000.0 },
            }
        end,
        function(TActor)
            TActor:setState("crushing")
        end
    )

    States.crushing = Cutscene.new(
        function(TActor)
            Sounds["Crush"]:play()
            Dodge:setAcceleration(-1, 1)
            return {
                { Player, true, GTT_WAIT, 500.0 },
                { Player, true, GTT_FADE_OFF, 5000.0 },
            }
        end,
        function(TActor)
            Mission.onRender = onRenderFaded
            TActor:setState("crushed")
        end
    )

    States.crushed = Cutscene.new(
        function(TActor)
            return {
                { Player, true, GTT_WAIT, 10000.0 },
            }
        end,
        function(TActor)
            Saver.save("Scripts/Mission0.lua", 1)
            Mission.switch("Scripts/Internal/Loader.lua", 1)
            TActor:setState("")
        end
    )
end