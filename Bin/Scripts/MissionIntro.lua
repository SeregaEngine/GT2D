----------------------------------------------------------------------
--| * MissionIntro.lua *
----------------------------------------------------------------------

---- Includes
require "Mission"

---- Resources
Textures["Background"] = Resource.defineTexture("Textures/Locations/MissionIntro-LA.png", TW_LOCATION*2, TH_LOCATION)
Textures["Barrier"] = Resource.defineTexture("Textures/Locations/MissionIntro-Barrier.png", TW_LOCATION, TH_LOCATION)
Textures["Road"] = Resource.defineTexture("Textures/Locations/MissionIntro-Road.png", TW_LOCATION, TH_LOCATION)
Textures["Player"] = Resource.defineTexture("Textures/Actors/Player.png", TW_ACTOR, TH_ACTOR)
Textures["Dodge"] = Resource.defineTexture("Textures/Cars/Dodge.png", TW_CAR, TH_CAR)
Anims["DodgeRiding"] = Resource.defineAnimation(2, 3, 1000.0/15)
Music["LA"] = Resource.defineMusic("Music/AmbientLA.wav")

---- Mission
function Mission.onEnter(Location)
	Player = Actor:new(0, 0, 10, 10, Textures["Player"])
	IsPlayerControllable = false

	Dodge = Car:new(75, 60, 51, 17, Textures["Dodge"])
	Dodge:turnLeft()
	Dodge:setPlacePosition(0, 1, -3)
	Dodge:putActor(Player, 0)
	Dodge:setMaxSpeed(0.05, 0)
	Dodge:setAcceleration(-1, 0)
	Dodge:setAnim(Anims["DodgeRiding"])

	-- Level
	local LevelWidth = SCREEN_WIDTH * 10
	Camera.setBounds({ -LevelWidth, 0, LevelWidth + SCREEN_WIDTH, SCREEN_HEIGHT })
	Camera.attach(Player)

	Music["LA"]:play()
end

function Mission.onUpdate(dt)
	Input.defaultHandle()

	if DEBUG then
		GT_LOG(PR_NOTE, string.format("%.1f, %.1f", Camera.getPosition()))
	end
end

function Mission.onRender()
	local X,Y = getCameraPosition()

	-- Background LA
	Graphics.drawFrame(RENDER_MODE_BACKGROUND, 0, true, { -GW_LOCATION - X*0.1, Y, GW_LOCATION*2, GH_LOCATION }, Textures["Background"], 0, 0)

	-- Barrier and road
	FastX = math.abs(X*1.5) % 128
	FastX2 = FastX - GW_LOCATION

	Graphics.drawFrame(RENDER_MODE_BACKGROUND, 1, true, { FastX, 0, GW_LOCATION, GH_LOCATION }, Textures["Barrier"], 0, 0)
	Graphics.drawFrame(RENDER_MODE_BACKGROUND, 1, true, { FastX2, 0, GW_LOCATION, GH_LOCATION }, Textures["Barrier"], 0, 0)

	Graphics.drawFrame(RENDER_MODE_BACKGROUND, 2, true, { FastX, 0, GW_LOCATION, GH_LOCATION }, Textures["Road"], 0, 0)
	Graphics.drawFrame(RENDER_MODE_BACKGROUND, 2, true, { FastX2, 0, GW_LOCATION, GH_LOCATION }, Textures["Road"], 0, 0)
end
