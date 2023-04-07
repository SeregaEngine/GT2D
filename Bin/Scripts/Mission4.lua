----------------------------------------------------------------------
--| * Mission4.lua *
--|
--| Police raid the garage
----------------------------------------------------------------------

---- Includes
require "GarageBlueprint"

---- Resources
Textures["John"] = Resource.defineTexture("Textures/Actors/John.png", TW_ACTOR, TH_ACTOR)
Textures["Serega"] = Resource.defineTexture("Textures/Actors/Serega.png", TW_ACTOR, TH_ACTOR)

---- Mission
function Mission.onEnter(Location)
    -- Garage
    GarageBlueprint.onEnter()
    GarageBlueprint.DayTime = GarageBlueprint.Night
    Fire:delete()
    Dodge:delete()
    Anthony:delete()
    Zhenek:delete()
    Player:delete()
    IsPlayerControllable = false

    -- Entities
    Serega = Actor:new(GW_LOCATION * 1.5, GROUND_Y, GW_ACTOR, GH_ACTOR, Textures["Serega"])
    Serega:toggleCollidable(false)
    Serega:setState("scene1")

    John = Actor:new(GW_LOCATION * 1.75, GROUND_Y + 1, GW_ACTOR, GH_ACTOR, Textures["John"])
    John:toggleCollidable(false)

    -- Mission
    defineCutscenes()
end

function Mission.onUpdate(dt)
    GarageBlueprint.onUpdate(dt)
end

function Mission.onRender()
    GarageBlueprint.onRender()
end

function defineCutscenes()
    States.scene1 = Cutscene.new(
        function(TActor)
            return {
                { Serega, false, AITASK_FADE_IN, 5000 },

                { Serega, false, AITASK_GOTO, 80, GROUND_Y },
                { John, true, AITASK_GOTO, 94, GROUND_Y+1 },

                { Serega, true, AITASK_WAIT, 250 },
                { Serega, false, AITASK_PUSH_COMMAND, AICMD_TURN_RIGHT },
                { Serega, true, AITASK_WAIT, 250 },

                { Serega, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "They've already hit the road..", 6, Serega, Textures["DialogSquare"]) },
                { Serega, true, AITASK_WAIT, 250 },

                { John, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Don't worry, we'll catch 'em up", 5, John, Textures["DialogSquare"]) },
                { John, true, AITASK_WAIT, 250 },

                { Serega, false, AITASK_PUSH_COMMAND, AICMD_TURN_LEFT },
                { Serega, true, AITASK_WAIT, 250 },
                { Serega, false, AITASK_GOTO, -100, GROUND_Y },

                { John, true, AITASK_WAIT, 250 },
                { John, false, AITASK_GOTO, -100, GROUND_Y+1 },
                { John, true, AITASK_WAIT, 250 },
                { John, true, AITASK_FADE_OFF, 2000 },
                { John, false, AITASK_FADE_IN, 0 },
            }
        end,
        function(TActor)
            Saver.save("Scripts/Mission5.lua", 1)
            Mission.switch("Scripts/Mission5.lua", 1)
            TActor:setState("")
        end
    )
end