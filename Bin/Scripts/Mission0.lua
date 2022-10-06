----------------------------------------------------------------------
--| * Mission0.lua *
--|
--| First meeting with Mechanic "Zhenek" in
--| his garage after Petrol's car accident
----------------------------------------------------------------------

---- Includes
dofile "Scripts/MissionDefines.lua"

---- Defines
local GROUND_X
local GROUND_Y
local GROUND_WIDTH
local GROUND_HEIGHT

---- Functions
function onEnter(Location)
	GT_LOG(PR_NOTE, "Mission 0 entered")

	-- Resources
	defineResources()

	-- Entities
	Player = addActor(GW_LOCATION - GW_ACTOR, GH_LOCATION - GH_ACTOR, GW_ACTOR, GH_ACTOR, Textures["Player"])
	turnActorLeft(Player)

	-- Ground
	GROUND_WIDTH = GW_LOCATION
	GROUND_HEIGHT = 18
	GROUND_X = 0
	GROUND_Y = GH_LOCATION - GROUND_HEIGHT
	setGroundBounds(GROUND_X, GROUND_Y, GROUND_WIDTH, GROUND_HEIGHT)

	-- Camera
	setCameraBounds(0, 0, GW_LOCATION, GH_LOCATION)
	setCameraPosition(0, 0)
end

function defineResources()
	Textures["Background"] = defineTexture("Textures/Locations/Mission0-1.png", TW_LOCATION, TH_LOCATION)
	Textures["Player"] = defineTexture("Textures/Actors/Player.png", TW_ACTOR, TH_ACTOR)
end

function onUpdate(dt)
	handleInput()
end

function onRender()
	drawFrame(RENDER_MODE_BACKGROUND, 0, false, 0,0,SCREEN_WIDTH,SCREEN_HEIGHT, Textures["Background"], 0, 0)
end