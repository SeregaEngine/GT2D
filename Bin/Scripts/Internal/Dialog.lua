----------------------------------------------------------------------
--| * Dialog.lua *
----------------------------------------------------------------------

Dialog = Entity:inherit()

function Dialog:new(W, H, Text, DurationSeconds, Actor, Texture)
    local Object = self:inherit()
    Object.Pointer = addDialog(W, H, Text, DurationSeconds, Actor, Texture)
    return Object
end

function Dialog:run()
    runDialog(self.Pointer)
end

