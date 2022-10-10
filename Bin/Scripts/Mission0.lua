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
Anims["PlayerWakeUp"] = Resource.defineAnimation(6, 3, 1000.0 / 1.5)
States["MainCutscene"] = Resource.defineState("stateMainCutscene")
States["LeaveCutscene"] = Resource.defineState("stateLeaveCutscene")

---- Mission functions
function Mission.onEnter(Location)
    GT_LOG(PR_NOTE, "Mission 0 entered")

    -- Init garage blueprint
    GarageBlueprint.onEnter()
    Dodge:setTexture(Textures["Car"])

    -- Init mission
    Player:setState(States["MainCutscene"])

    local Dialogs = {
        ["Player1"] = Dialog:new(GW_DIALOG, GH_DIALOG, "Uh...", 0.5, Player, Textures["DialogSquare"]),
        ["Player2"] = Dialog:new(GW_DIALOG, GH_DIALOG, "Where am i?", 0.5, Player, Textures["DialogSquare"]),
        ["Player3"] = Dialog:new(GW_DIALOG, GH_DIALOG, "What the fuck, man?", 0.5, Player, Textures["DialogSquare"]),
        ["Player4"] = Dialog:new(GW_DIALOG, GH_DIALOG, "Who are you and this Anthony?", 0.5, Player, Textures["DialogSquare"]),
        ["Player5"] = Dialog:new(GW_DIALOG, GH_DIALOG, "Damn man...", 0.5, Player, Textures["DialogSquare"]),
        ["Player6"] = Dialog:new(GW_DIALOG, GH_DIALOG, "I need to get to my family", 0.5, Player, Textures["DialogSquare"]),
        ["Player7"] = Dialog:new(GW_DIALOG, GH_DIALOG, "Ok, i got it", 0.5, Player, Textures["DialogSquare"]),

        ["Zhenek1"] = Dialog:new(GW_DIALOG, GH_DIALOG, "Oh, you are alive!", 0.5, Zhenek, Textures["DialogSquare"]),
        ["Zhenek2"] = Dialog:new(GW_DIALOG, GH_DIALOG, "Anthony, did you hear?", 0.5, Zhenek, Textures["DialogSquare"]),
        ["Zhenek3"] = Dialog:new(GW_DIALOG, GH_DIALOG, "He's just homeless, don't pay attention to him.", 0.5, Zhenek, Textures["DialogSquare"]),
        ["Zhenek4"] = Dialog:new(GW_DIALOG, GH_DIALOG, "Yeah, so you have little trouble..", 0.5, Zhenek, Textures["DialogSquare"]),
        ["Zhenek5"] = Dialog:new(GW_DIALOG, GH_DIALOG, "Your car, man... It's dead.", 0.5, Zhenek, Textures["DialogSquare"]),
        ["Zhenek6"] = Dialog:new(GW_DIALOG, GH_DIALOG, "Of course we can.", 0.5, Zhenek, Textures["DialogSquare"]),
        ["Zhenek7"] = Dialog:new(GW_DIALOG, GH_DIALOG, "We have to find some parts for car and it'll be a long journey", 0.5, Zhenek, Textures["DialogSquare"]),
        ["Zhenek8"] = Dialog:new(GW_DIALOG, GH_DIALOG, "Cool, bro. Go outside when you'll ready", 0.5, Zhenek, Textures["DialogSquare"]),

        ["Anthony1"] = Dialog:new(GW_DIALOG, GH_DIALOG, "Man, i don't care.", 0.5, Anthony, Textures["DialogSquare"]),
        ["Anthony2"] = Dialog:new(GW_DIALOG, GH_DIALOG, "I was a gangster in early 90's, now i'm businnesman who love riding a taxi..", 0.5, Anthony, Textures["DialogSquare"]),
        ["Anthony3"] = Dialog:new(GW_DIALOG, GH_DIALOG, "..sell houses and drink 30-year-old cognac.", 0.5, Anthony, Textures["DialogSquare"]),
        ["Anthony4"] = Dialog:new(GW_DIALOG, GH_DIALOG, "Don't cry kid, we can help you.", 0.5, Anthony, Textures["DialogSquare"]),
    }

    MainCutscene = {
        { Player, false, GTT_FADE_IN, 2000.0 },
        { Player, false, GTT_PUSH_COMMAND, GTC_TURN_LEFT },
        { Player, true, GTT_ANIMATE_FOR, Anims["PlayerSleep"], 1000.0 },
        { Player, true, GTT_WAIT_ANIMATION, Anims["PlayerWakeUp"] },
        { Player, false, GTT_PUSH_COMMAND, GTC_TURN_LEFT },
        { Player, false, GTT_PUSH_COMMAND, GTC_IDLE },

        { Player, true, GTT_WAIT_DIALOG, Dialogs["Player1"] },
        { Player, true, GTT_WAIT_DIALOG, Dialogs["Player2"] },

        { Zhenek, false, GTT_PUSH_COMMAND, GTC_TURN_RIGHT },
        { Zhenek, true, GTT_WAIT, 500.0 },
        { Zhenek, true, GTT_WAIT_DIALOG, Dialogs["Zhenek1"] },
        { Zhenek, true, GTT_WAIT, 250.0 },
        { Zhenek, false, GTT_PUSH_COMMAND, GTC_TURN_LEFT },
        { Zhenek, true, GTT_WAIT, 250.0 },
        { Zhenek, true, GTT_WAIT_DIALOG, Dialogs["Zhenek2"] },
        { Zhenek, true, GTT_WAIT, 250.0 },

        { Player, false, GTT_RUN_DIALOG, Dialogs["Anthony1"] }, -- Don't loose Anthony's current task

        { Zhenek, true, GTT_WAIT, 250.0 },
        { Zhenek, true, GTT_PUSH_COMMAND, GTC_TURN_RIGHT },

        { Player, false, GTT_GOTO_ENTITY, Zhenek },
        { Zhenek, true, GTT_WAIT, 250.0 },
        { Zhenek, true, GTT_GOTO_ENTITY, Player },

        { Player, true, GTT_WAIT_DIALOG, Dialogs["Player3"] },
        { Player, true, GTT_WAIT_DIALOG, Dialogs["Player4"] },

        { Anthony, true, GTT_WAIT, 250.0 },
        { Anthony, false, GTT_WAIT_DIALOG, Dialogs["Anthony2"] },

        { Zhenek, true, GTT_WAIT, 250.0 },
        { Zhenek, true, GTT_PUSH_COMMAND, GTC_TURN_LEFT },
        { Zhenek, true, GTT_WAIT_DIALOG, Dialogs["Anthony2"] },

        { Anthony, true, GTT_WAIT_DIALOG, Dialogs["Anthony3"] },

        { Zhenek, true, GTT_WAIT, 250.0 },
        { Zhenek, true, GTT_PUSH_COMMAND, GTC_TURN_RIGHT },
        { Zhenek, true, GTT_WAIT, 250.0 },

        { Zhenek, true, GTT_WAIT_DIALOG, Dialogs["Zhenek3"] },
        { Zhenek, true, GTT_WAIT, 250.0 },

        { Player, true, GTT_WAIT_DIALOG, Dialogs["Player5"] },
        { Player, true, GTT_WAIT_DIALOG, Dialogs["Player6"] },
        { Player, true, GTT_WAIT, 250.0 },

        { Zhenek, true, GTT_WAIT_DIALOG, Dialogs["Zhenek4"] },
        { Zhenek, true, GTT_WAIT_DIALOG, Dialogs["Zhenek5"] },
        { Zhenek, true, GTT_WAIT, 250.0 },

        { Anthony, true, GTT_WAIT_DIALOG, Dialogs["Anthony4"] },
        { Anthony, true, GTT_WAIT, 250.0 },

        { Zhenek, true, GTT_WAIT_DIALOG, Dialogs["Zhenek6"] },
        { Zhenek, true, GTT_WAIT_DIALOG, Dialogs["Zhenek7"] },
        { Zhenek, true, GTT_WAIT, 250.0 },

        { Player, true, GTT_WAIT_DIALOG, Dialogs["Player7"] },
        { Player, true, GTT_WAIT, 250.0 },

        { Zhenek, true, GTT_WAIT_DIALOG, Dialogs["Zhenek8"] },
    }
    MainCutsceneStage = 0

    LeaveCutscene = {
        { Player, false, GTT_GOTO, GROUND_WIDTH*2, GROUND_Y + GROUND_HEIGHT/2 },
        { Player, true, GTT_FADE_OFF, 2500.0 },
        { Player, false, GTT_FADE_IN, 0.0 }, -- Black screen on last frame
    }
    LeaveCutsceneStage = 0

    -- Triggers
    Trigger:new({ GROUND_WIDTH, GROUND_Y-5, 2, GROUND_HEIGHT*2 }, Player, "triggerLeaveCutscene")

    -- Location
    Mission.setGroundBounds({ GROUND_X, GROUND_Y, GROUND_WIDTH * 2, GROUND_HEIGHT })

    -- DEBUG(sean)
    Resource.defineMusic("Music/MainGarageAmbient.wav"):play()
    Resource.defineSound("Sounds/ColtShot1.wav"):play()
    GT_LOG(PR_NOTE, package.path)
end

function Mission.onUpdate(dt)
    handleInput()
end

function Mission.onRender()
    GarageBlueprint.onRender()
end

---- Triggers
function triggerLeaveCutscene(TTrigger, TEntity)
    setmetatable(TEntity, Actor)
    TEntity:setState(States["LeaveCutscene"])
end

---- Cutscenes
stateMainCutscene = Cutscene.new(
    function()
        return MainCutscene
    end,
    function(Change)
        MainCutsceneStage = MainCutsceneStage + Change
        return MainCutsceneStage
    end,
    function(TActor)
        IsZhenekBusy = true
        PlayerControllable = false
    end,
    function(TActor)
        IsZhenekBusy = false
        PlayerControllable = true

        MainCutsceneStage = 0
        TActor:setState(nil)
    end
)

stateLeaveCutscene = Cutscene.new(
    function()
        return LeaveCutscene
    end,
    function(Change)
        LeaveCutsceneStage = LeaveCutsceneStage + Change
        return LeaveCutsceneStage
    end,
    function(TActor)
        PlayerControllable = false
    end,
    function(TActor)
        Mission.restart(1)
        TActor:setState(nil)
    end
)