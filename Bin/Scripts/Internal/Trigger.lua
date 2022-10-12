----------------------------------------------------------------------
--| * Trigger.lua *
----------------------------------------------------------------------

Trigger = Entity:inherit()

function Trigger:new(Rect, Entity, FunctionName)
    local Object = self:inherit()
    Object.Pointer = addTrigger(Rect[1], Rect[2], Rect[3], Rect[4], Entity, FunctionName)
    return Object
end

