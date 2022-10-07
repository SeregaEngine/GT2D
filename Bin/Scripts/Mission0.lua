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
end

function defineResources()

end

function onUpdate(dt)
    handleInput()
end

function onRender()
    onGarageRender()
end
