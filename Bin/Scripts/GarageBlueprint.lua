----------------------------------------------------------------------
--| * GarageBlueprint.lua *
--|
--| Contains all stuff for garage missions
----------------------------------------------------------------------

---- Includes
require "Mission"

---- Globals
GROUND_WIDTH = GW_LOCATION
GROUND_HEIGHT = 18
GROUND_X = 0
GROUND_Y = GH_LOCATION - GROUND_HEIGHT

---- Resources
Textures["Background"] = Resource.defineTexture("Textures/Locations/GarageBlueprint.png", TW_LOCATION, TH_LOCATION)
Textures["Player"] = Resource.defineTexture("Textures/Actors/Player.png", TW_ACTOR, TH_ACTOR)
Textures["Zhenek"] = Resource.defineTexture("Textures/Actors/Zhenek.png", TW_ACTOR, TH_ACTOR)
Textures["Anthony"] = Resource.defineTexture("Textures/Actors/Anthony.png", TW_ACTOR, TH_ACTOR)
Textures["PlaceholderCar"] = Resource.defineTexture("Textures/Cars/TrashCar.png", TW_CAR, TH_CAR)
Textures["Fire"] = Resource.defineTexture("Textures/Props/Fire.png", TW_ACTOR, TH_ACTOR)

Anims["SlowMoving"] = Resource.defineAnimation(1, 5, 1000.0 / 13.5)
Anims["RepairCar"] = Resource.defineAnimation(4, 2, 1000.0 / 1)
Anims["TakeInstruments"] = Resource.defineAnimation(5, 2, 1000.0 / 1)
Anims["Fire"] = Resource.defineAnimation(0, 10, 1000.0/10)

Musics["Garage"] = Resource.defineMusic("Music/Garage.mp3")

---- Garage Blueprint
GarageBlueprint = {}

GarageBlueprint.Day = Resource.defineTexture("Textures/Locations/GarageBlueprint-Day.png", TW_LOCATION, TH_LOCATION)
GarageBlueprint.Night = Resource.defineTexture("Textures/Locations/GarageBlueprint-Night.png", TW_LOCATION, TH_LOCATION)
GarageBlueprint.TimeTicks = Clock.getTicks()

function GarageBlueprint.onEnter()

    -- Entities
	Fire = Actor:new(76, 36.5, GW_ACTOR, GH_ACTOR, Textures["Fire"])
	Fire:setRenderMode(RENDER_MODE_BACKGROUND)
	Fire:setZIndex(4)
	Fire:toggleGodMode(true)
	Fire:setActorAnim(ACTOR_ANIMATION_IDLE, Anims["Fire"])

    Player = Actor:new(GW_LOCATION - GW_ACTOR, GH_LOCATION - GH_ACTOR, GW_ACTOR, GH_ACTOR, Textures["Player"])
    local XDefault,YDefault = Player:getSpeed()
    Player:setSpeed(XDefault/1.2, YDefault/1.2)
    Player:setActorAnim(ACTOR_ANIMATION_HORIZONTAL, Anims["SlowMoving"])
    Player:setTeam(ACTOR_TEAM_FRIENDS)
    Player:setWeapon(Weapons["Fist"])

    Zhenek = Actor:new(85, 47, GW_ACTOR, GH_ACTOR, Textures["Zhenek"])
    Zhenek:setSpeed(XDefault/1.2, YDefault/1.2)
    Zhenek:setActorAnim(ACTOR_ANIMATION_HORIZONTAL, Anims["SlowMoving"])
    Zhenek:setTeam(ACTOR_TEAM_FRIENDS)
    Zhenek:turnLeft()
    IsZhenekBusy = false -- Change this when you cut-scene require Zhenek

    Anthony = Actor:new(50, 50, GW_ACTOR, GH_ACTOR, Textures["Anthony"])
    Anthony:setSpeed(XDefault/1.2, YDefault/1.2)
    Anthony:setActorAnim(ACTOR_ANIMATION_HORIZONTAL, Anims["SlowMoving"])
    Anthony:setTeam(ACTOR_TEAM_FRIENDS)
    Anthony:setState("_upCar")
    Anthony:turnLeft()

    Dodge = Car:new(25, 50, 65, 20, Textures["PlaceholderCar"])
    Dodge:setRenderMode(RENDER_MODE_FOREGROUND)
    Dodge:setZIndex(-1)
    Dodge:setMaxSpeed(0, 0.005)
    Dodge:setAcceleration(0, -0.000001)

    -- Cutscenes
    GarageBlueprint._defineCutscenes()

    -- Set up
	GarageBlueprint.DayTime = GarageBlueprint.Day
    Mission.setGroundBounds({ GROUND_X, GROUND_Y, GROUND_WIDTH, GROUND_HEIGHT })
    Camera.setBounds({ 0, 0, GW_LOCATION, GH_LOCATION })
    Camera.setPosition(0, 0)
	Musics["Garage"]:play()
end

function GarageBlueprint.onUpdate(dt)
	GarageBlueprint.TimeTicks = Clock.getTicks()
end

function GarageBlueprint.onRender()
	-- Parallax
    local X = -(GarageBlueprint.TimeTicks/1000.0) % GW_LOCATION
    Graphics.drawFrame(RENDER_MODE_BACKGROUND, 0, true, { X, 0, GW_LOCATION, GH_LOCATION }, GarageBlueprint.DayTime)
    Graphics.drawFrame(RENDER_MODE_BACKGROUND, 0, true, { X-GW_LOCATION, 0, GW_LOCATION, GH_LOCATION }, GarageBlueprint.DayTime)

	-- Background
    Graphics.drawFrame(RENDER_MODE_BACKGROUND, 1, false, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, Textures["Background"], 0, 0)
end

---- Internal functions
function GarageBlueprint._defineCutscenes()
	function States._upCar(TActor)
		if not Dodge:isAvailable() then
			return
		end

		local X,Y = Dodge:getPosition()

		if Y >= 44 and Y <= 45 then
			Dodge:setAcceleration(0, 0.0000003)
		elseif Y <= 40 then
			Dodge:setPosition(25, 40)
			Dodge:setMaxSpeed(0, 0)
			TActor:setState("_takeInstruments")
		end
	end

	States._takeInstruments = Cutscene.new(
		function(TActor)
			return {
				{ Anthony, true, GTT_GOTO, 63, 47.5 },
				{ Anthony, true, GTT_ANIMATE_FOR, Anims["TakeInstruments"], math.random(2000, 5000) },
				{ Anthony, true, GTT_PUSH_COMMAND, GTC_MOVE_IDLE },
				{ Anthony, true, GTT_WAIT, 500.0 },
			}
		end,
		function(TActor)
			if not IsZhenekBusy and math.random(0, 1) == 1 then
				TActor:setState("_randomTalk")
			else
				TActor:setState("_repairCar")
			end
		end
	)

	States._repairCar = Cutscene.new(
		function(TActor)
			return {
				{ Anthony, true, GTT_GOTO, 25, 53 },
				{ Anthony, true, GTT_PUSH_COMMAND, GTC_TURN_RIGHT },
				{ Anthony, true, GTT_ANIMATE_FOR, Anims["RepairCar"], math.random(5000, 15000) },
				{ Anthony, true, GTT_PUSH_COMMAND, GTC_MOVE_IDLE },
				{ Anthony, true, GTT_WAIT, 500.0 },
			}
		end,
		function(TActor)
			TActor:setState("_takeInstruments")
		end
	)

	States._randomTalk = Cutscene.new(
		function(TActor)
			local Res = math.random(1, 2)
			if Res == 1 then
				return {
					{ Anthony, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Sometimes i want to change my job", 4, Anthony, Textures["DialogSquare"]) },
					{ Zhenek, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Your problems.", 1.5, Zhenek, Textures["DialogSquare"]) },
					{ Anthony, true, GTT_WAIT, 1000 }
				}
			elseif Res == 2 then
				return {
					{ Anthony, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "How you doing, bruh?", 3, Anthony, Textures["DialogSquare"]) },
					{ Zhenek, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Can..", 0.5, Zhenek, Textures["DialogSquare"]) },
					{ Zhenek, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "You..", 0.5, Zhenek, Textures["DialogSquare"]) },
					{ Zhenek, true, GTT_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "PhIl MaHaAar", 2.5, Zhenek, Textures["DialogSquare"]) },
					{ Anthony, true, GTT_WAIT, 1000 }
				}
			end
		end,
		function(TActor)
			TActor:setState("_repairCar")
		end
	)
end