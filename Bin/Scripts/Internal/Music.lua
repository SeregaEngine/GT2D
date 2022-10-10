Music = { Pointer = nil }

function Music:new(Path)
    local Object = {}
    Object.Pointer = defineMusic(Path)
    setmetatable(Object, self)
    self.__index = self
    return Object
end

function Music:play()
    playMusic(self.Pointer)
end

