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
Textures["Mex1"] = Resource.defineTexture("Textures/Actors/DarkLord.png", TW_ACTOR, TH_ACTOR) -- Placeholder
Textures["Mex2"] = Textures["Mex1"] -- Placeholder
Textures["Mex3"] = Textures["Mex1"] -- Placeholder
Textures["Artem"] = Textures["Mex1"] -- Placeholder
Textures["Kirill"] = Textures["Mex1"] -- Placeholder

Musics["Ambient1"] = Resource.defineMusic("Music/VnatureBgSound.wav") -- Placeholder
Musics["Ambient2"] = Musics["Ambient1"] -- Placeholder
Musics["Ambient3"] = Musics["Ambient1"]

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
    Player = Actor:new(30, 60, GW_ACTOR, GH_ACTOR, Textures["Player"])
    Player:setWeapon(Weapons["Fist"])
    Player:setTeam(ACTOR_TEAM_FRIENDS)
    Player:setState("")

    Zhenek = Actor:new(0, 0, GW_ACTOR, GH_ACTOR, Textures["Zhenek"])
    Zhenek:setTeam(ACTOR_TEAM_FRIENDS)

    Pickup = Car:new(30, 68, 107, 30, Textures["Pickup"])
    Pickup:setPlacePosition(0, 15, -5)
    Pickup:setPlacePosition(1, 6, -5)
    --Pickup:putActor(Player, 0)
    Pickup:putActor(Zhenek, 1)

    -- Mission
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
end

function L1.defineCutscenes()
end

function L1.defineStates()
end
