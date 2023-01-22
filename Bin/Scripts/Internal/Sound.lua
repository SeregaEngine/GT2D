----------------------------------------------------------------------
--| * Sound.lua *
----------------------------------------------------------------------

Sound = { Pointer = nil }

function Sound:new(Path)
    local Object = {}
    Object.Pointer = defineSound(Path)
    setmetatable(Object, self)
    self.__index = self
    return Object
end

function Sound:play()
    playSound(self.Pointer)
end

function Sound:playLooped()
    playSoundLooped(self.Pointer)
end

function Sound.stopAll()
    stopAllSounds()
end

