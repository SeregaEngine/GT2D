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
        { Player, false, GTT_ANIMATE_FOR, defineAnimation(0, 2, 1000/20), 2000 },
        { Zhenek, false, GTT_WAIT_DIALOG, addDialog(GW_DIALOG, GH_DIALOG, "", 1, Zhenek, Textures["DialogSquare"]) },
        { Player, false, GTT_WAIT_DIALOG, addDialog(GW_DIALOG, GH_DIALOG, "", 1, Player, Textures["DialogSquare"]) },
        { Player, false, GTT_GOTO_ENTITY, Anthony },
        { Player, true, GTT_WAIT, 5000 }
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
