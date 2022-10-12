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
Textures["Background"] = Resource.defineTexture("Textures/Locations/Mission0-1.png", TW_LOCATION, TH_LOCATION)
Textures["Player"] = Resource.defineTexture("Textures/Actors/Player.png", TW_ACTOR, TH_ACTOR)
Textures["Zhenek"] = Resource.defineTexture("Textures/Actors/Zhenek.png", TW_ACTOR, TH_ACTOR)
Textures["Anthony"] = Resource.defineTexture("Textures/Actors/Anthony.png", TW_ACTOR, TH_ACTOR)
Textures["PlaceholderCar"] = Resource.defineTexture("Textures/Cars/TrashCar.png", TW_CAR, TH_CAR)

Anims["SlowMoving"] = Resource.defineAnimation(1, 5, 1000.0 / 13.5)
Anims["RepairCar"] = Resource.defineAnimation(4, 2, 1000.0 / 1)
Anims["TakeInstruments"] = Resource.defineAnimation(5, 2, 1000.0 / 1)

---- Garage Blueprint
GarageBlueprint = {}

function GarageBlueprint.onEnter()
    -- Entities
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
    Mission.setGroundBounds({ GROUND_X, GROUND_Y, GROUND_WIDTH, GROUND_HEIGHT })
    Camera.setBounds({ 0, 0, GW_LOCATION, GH_LOCATION })
    Camera.setPosition(0, 0)
end

function GarageBlueprint.onRender()
    Graphics.drawFrame(RENDER_MODE_BACKGROUND, 0, false, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, Textures["Background"], 0, 0)
end

---- Internal functions
function GarageBlueprint._defineCutscenes()
	function States._upCar(TActor)
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