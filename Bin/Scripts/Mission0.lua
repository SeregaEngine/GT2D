----------------------------------------------------------------------
--| * Mission0.lua *
--|
--| First meeting with Mechanic "Zhenek" in
--| his garage after Petrol's car accident
----------------------------------------------------------------------

---- Includes
dofile "Scripts/MissionDefines.lua"

---- Defines
ACTOR_TEAM_FRIENDS = ACTOR_TEAM_DEFAULT + 1

---- Globals
local GROUND_X
local GROUND_Y
local GROUND_WIDTH
local GROUND_HEIGHT

Zhenek = nil
Anthony = nil
Car = nil

---- Functions
function onEnter(Location)
	GT_LOG(PR_NOTE, "Mission 0 entered")

	-- Resources
	defineResources()

	-- Entities
	Player = addActor(GW_LOCATION - GW_ACTOR, GH_LOCATION - GH_ACTOR, GW_ACTOR, GH_ACTOR, Textures["Player"])
	setActorTeam(Player, ACTOR_TEAM_FRIENDS)
	setActorWeapon(Player, Weapons["Fist"])

	Zhenek = addActor(85, 47, GW_ACTOR, GH_ACTOR, Textures["Zhenek"])
	setActorTeam(Zhenek, ACTOR_TEAM_FRIENDS)
	turnActorLeft(Zhenek)

	Anthony = addActor(60, 48, GW_ACTOR, GH_ACTOR, Textures["Anthony"])
	setActorTeam(Anthony, ACTOR_TEAM_FRIENDS)
	setActorState(Anthony, States["UpCar"])
	turnActorLeft(Anthony)
	--playActorAnimation(Anthony, Anims["TakeInstruments"])

	Car = addCar(25, 50, 65, 20, Textures["Car"])
	setEntityRenderMode(Car, RENDER_MODE_FOREGROUND)
	setEntityZIndex(Car, -1)
	setCarMaxSpeed(Car, 0, 0.005)
	setCarAcceleration(Car, 0, -0.000001)

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
	Textures["Zhenek"] = defineTexture("Textures/Actors/Zhenek.png", TW_ACTOR, TH_ACTOR)
	Textures["Anthony"] = defineTexture("Textures/Actors/John.png", TW_ACTOR, TH_ACTOR) -- Workaround
	Textures["Car"] = defineTexture("Textures/Cars/TrashCar.png", TW_CAR, TH_CAR)

	States["UpCar"] = defineState("stateUpCar")
end

function onUpdate(dt)
	handleInput()
end

function onRender()
	drawFrame(RENDER_MODE_BACKGROUND, 0, false, 0,0,SCREEN_WIDTH,SCREEN_HEIGHT, Textures["Background"], 0, 0)
end

function stateUpCar(Actor)
	local X,Y = getEntityPosition(Car)

	if Y >= 39 and Y <= 40 then
		setCarAcceleration(Car, 0, 0.000001)
	elseif Y >= 35 and Y <= 36 then
		setCarMaxSpeed(Car, 0, 0)
		setActorState(Actor, nil)
	end
end