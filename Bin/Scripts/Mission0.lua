----------------------------------------------------------------------
--| * Mission0.lua *
--|
--| First meeting with Mechanic "Zhenek" in
--| his garage after Petrol's car accident
----------------------------------------------------------------------

---- Includes
dofile "Scripts/GarageBlueprint.lua"

---- Functions
function onEnter(Location)
    GT_LOG(PR_NOTE, "Mission 0 entered")

    defineResources()
    onGarageEnter()

    setActorState(Player, States["MainCutscene"])

    MainCutscene = {
        { Player, false, GTT_PUSH_COMMAND, GTC_MOVE_UP },
        { Player, true, GTT_FADE_IN, 1000 },
        { Player, true, GTT_PUSH_COMMAND, GTC_MOVE_RIGHT },
        { Player, true, GTT_WAIT, 1000 },
    }
    MainCutsceneStage = 0
end

function defineResources()
    Anims["PlayerDead"] = defineAnimation(5, 1, 1)
    Anims["PlayerWakeUp"] = defineAnimation(6, 3, 1000.0 / 0.1)
    States["MainCutscene"] = defineState("stateMainCutscene")
end

function onUpdate(dt)
    handleInput()
end

function onRender()
    onGarageRender()
end

stateMainCutscene = createCutscene(
    function()
        return MainCutscene
    end,
    function(Change)
        MainCutsceneStage = MainCutsceneStage + Change
        return MainCutsceneStage
    end,
    function(Actor)
		ZhenekIsBusy = true
        PlayerControllable = false
        turnActorLeft(Actor)
    end,
    function(Actor)
        ZhenekIsBusy = false
        PlayerControllable = true
        MainCutsceneStage = 0
        setActorState(Actor, nil)
    end
)
