----------------------------------------------------------------------
--| * Mission0.lua *
--|
--| First meeting with Mechanic "Zhenek" in
--| his garage after Petrol's car accident
----------------------------------------------------------------------

---- Includes
require "GarageBlueprint"

---- Resources
Textures["Car"] = Resource.defineTexture("Textures/Cars/Dodge.png", TW_CAR, TH_CAR)
Anims["PlayerSleep"] = Resource.defineAnimation(6, 1, 1000.0)
Anims["PlayerWakeUp"] = Resource.defineAnimation(6, 3, 1000.0 / 1)

---- Mission functions
function Mission.onEnter(Location)
    GT_LOG(PR_NOTE, "Mission 0 entered")

    -- Function
    Mission.onRender = onRender

    --- Init garage blueprint
    GarageBlueprint.onEnter()
    Dodge:setTexture(Textures["Car"])
    Dodge:setAnim(Resource.defineAnimation(1, 1, 999999))

    --- Init mission
    defineCutscenes()
    Player:setState("mainCutscene")

    -- Location
    Mission.setGroundBounds({ GROUND_X, GROUND_Y, GROUND_WIDTH * 2, GROUND_HEIGHT })
end

function Mission.onUpdate(dt)
    GarageBlueprint.onUpdate(dt)
    Input.defaultHandle()
end

function onRender()
    GarageBlueprint.onRender()
end

function onRenderWithHelp()
    -- Garage
    GarageBlueprint.onRender()

    -- Text
    Graphics.setDrawColor(255, 255, 255, 160)
    Graphics.drawText(RENDER_MODE_BACKGROUND, 50, true, { 0, SCREEN_HEIGHT-5, 35, 5 }, "WASD to move")
end

---- Triggers
function Triggers.leaveCutscene(TTrigger, TEntity)
    setmetatable(TEntity, Actor)
    TEntity:setState("leaveCutscene")
end

---- Cutscenes
function defineCutscenes()
    States.mainCutscene = Cutscene.new(
        function(TActor)
            IsZhenekBusy = true
            IsPlayerControllable = false

            -- We use Player for Anthony's tasks to prevent canceling Anthony's tasks
            return {
                { Player, false, AITASK_FADE_IN, 4000.0 },
                { Player, false, AITASK_PUSH_COMMAND, AICMD_TURN_LEFT },
                { Player, true, AITASK_ANIMATE_FOR, Anims["PlayerSleep"], 3000.0 },
                { Player, true, AITASK_WAIT_ANIMATION, Anims["PlayerWakeUp"] },
                { Player, false, AITASK_PUSH_COMMAND, AICMD_TURN_LEFT },
                { Player, false, AITASK_PUSH_COMMAND, AICMD_IDLE },

                { Player, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Uh...", 2, Player, Textures["DialogSquare"]) },
                { Player, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Where am i?", 3, Player, Textures["DialogSquare"]) },

                { Zhenek, false, AITASK_PUSH_COMMAND, AICMD_TURN_RIGHT },
                { Zhenek, true, AITASK_WAIT, 500.0 },
                { Zhenek, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Oh, you are alive!", 3.5, Zhenek, Textures["DialogSquare"]) },
                { Zhenek, true, AITASK_WAIT, 250.0 },
                { Zhenek, false, AITASK_PUSH_COMMAND, AICMD_TURN_LEFT },
                { Zhenek, true, AITASK_WAIT, 250.0 },
                { Zhenek, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Anthony, did you hear?", 4, Zhenek, Textures["DialogSquare"]) },
                { Zhenek, true, AITASK_WAIT, 250.0 },

                { Player, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Man, i don't care", 3, Anthony, Textures["DialogSquare"]) },

                { Zhenek, true, AITASK_WAIT, 250.0 },
                { Zhenek, true, AITASK_PUSH_COMMAND, AICMD_TURN_RIGHT },

                { Player, false, AITASK_GOTO_ENTITY, Zhenek },
                { Zhenek, true, AITASK_WAIT, 250.0 },
                { Zhenek, true, AITASK_GOTO_ENTITY, Player },

                { Player, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "What the fuck, man?", 3, Player, Textures["DialogSquare"]) },
                { Player, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Who are you and this Anthony?", 4, Player, Textures["DialogSquare"]) },

                { Player, true, AITASK_WAIT, 250.0 },
                { Player, false, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "I was a gangster in early 90's, now i'm businnesman who love riding a taxi..", 8, Anthony, Textures["DialogSquare"]) },

                { Zhenek, true, AITASK_WAIT, 250.0 },
                { Zhenek, true, AITASK_PUSH_COMMAND, AICMD_TURN_LEFT },
                { Zhenek, true, AITASK_WAIT_TALKING, Anthony },

                { Player, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "..sell houses and drink 30-year-old cognac.", 6, Anthony, Textures["DialogSquare"]) },

                { Zhenek, true, AITASK_WAIT, 250.0 },
                { Zhenek, true, AITASK_PUSH_COMMAND, AICMD_TURN_RIGHT },
                { Zhenek, true, AITASK_WAIT, 250.0 },

                { Zhenek, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "He's just homeless, don't pay attention to him.", 6, Zhenek, Textures["DialogSquare"]) },
                { Zhenek, true, AITASK_WAIT, 250.0 },

                { Player, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Damn man...", 3, Player, Textures["DialogSquare"]) },
                { Player, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "I need to get to my family", 4, Player, Textures["DialogSquare"]) },
                { Player, true, AITASK_WAIT, 250.0 },

                { Zhenek, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Yeah, so you have a little trouble..", 3, Zhenek, Textures["DialogSquare"]) },
                { Zhenek, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Your car, man... It's dead.", 3, Zhenek, Textures["DialogSquare"]) },
                { Zhenek, true, AITASK_WAIT, 250.0 },

                { Player, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Don't cry kid, we can help you.", 4, Anthony, Textures["DialogSquare"]) },
                { Player, true, AITASK_WAIT, 250.0 },

                { Zhenek, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Of course we can.", 3, Zhenek, Textures["DialogSquare"]) },
                { Zhenek, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "We have to find some parts for car and it'll be a long journey", 6, Zhenek, Textures["DialogSquare"]) },
                { Zhenek, true, AITASK_WAIT, 250.0 },

                { Player, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Ok, i got it", 3, Player, Textures["DialogSquare"]) },
                { Player, true, AITASK_WAIT, 250.0 },

                { Zhenek, true, AITASK_WAIT_DIALOG, Dialog:new(GW_DIALOG, GH_DIALOG, "Cool, bro. Go outside when you'll be ready", 6, Zhenek, Textures["DialogSquare"]) },
            }
        end,
        function(TActor)
            Mission.onRender = onRenderWithHelp
            Trigger:new({ GROUND_WIDTH, GROUND_Y-5, 2, GROUND_HEIGHT*2 }, Player, "leaveCutscene")
            IsZhenekBusy = false
            IsPlayerControllable = true
            TActor:setState("")
        end
    )

    States.leaveCutscene = Cutscene.new(
        function(TActor)
            Mission.onRender = onRender
            IsPlayerControllable = false
            return {
                { Player, false, AITASK_GOTO, GROUND_WIDTH*2, GROUND_Y + GROUND_HEIGHT/4 },
                { Player, true, AITASK_FADE_OFF, 4500.0 },
                { Player, false, AITASK_FADE_IN, 0.0 }, -- Black screen on last frame
            }
        end,
        function(TActor)
            Saver.save("Scripts/Mission1.lua", 1)
            Mission.switch("Scripts/Internal/Loader.lua", 1)
            TActor:setState("")
        end
    )
end