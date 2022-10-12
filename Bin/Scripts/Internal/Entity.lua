----------------------------------------------------------------------
--| * Entity.lua *
----------------------------------------------------------------------

Entity = { Pointer = nil }

function Entity:inherit(Object)
    Object = Object or {} -- Optional argument

    setmetatable(Object, self)
    self.__index = self

    return Object
end

function Entity:new(X, Y, W, H, Texture)
    local Object = self:inherit()
    Object.Pointer = addEntity(X, Y, W, H, Texture)
    return Object
end

function Entity:delete()
    removeEntity(self.Pointer)
    self.Pointer = nil
end

function Entity:isAvailable()
    return hasWorldEntity(Entity.Pointer)
end

function Entity:setPosition(X, Y)
    setEntityPosition(self.Pointer, X, Y)
end

function Entity:getPosition()
    return getEntityPosition(self.Pointer)
end

function Entity:setVelocity(X, Y)
    setEntityVelocity(self.Pointer, X, Y)
end

function Entity:getVelocity()
    return getEntityVelocity(self.Pointer)
end

function Entity:setHitBox(X1, Y1, X2, Y2)
    setEntityHitBox(self.Pointer, X1, Y1, X2, Y2)
end

function Entity:getHitBox()
    return getEntityHitBox(self.Pointer)
end

function Entity:toggleCollidable(Boolean)
    toggleEntityCollidable(self.Pointer, Boolean)
end

function Entity:isCollidable()
    return getEntityCollidable(self.Pointer)
end

function Entity:setAnimFrame(Frame)
    setEntityAnimFrame(self.Pointer, Frame)
end

function Entity:getAnimFrame()
    return getEntityAnimFrame(self.Pointer)
end

function Entity:setAnimElapsed(Elapsed)
    setEntityAnimElapsed(self.Pointer, Elapsed)
end

function Entity:getAnimElapsed()
    return getEntityAnimElapsed(self.Pointer)
end

function Entity:setAnim(Anim)
    setEntityAnim(self.Pointer, Anim)
end

function Entity:getAnim()
    return getEntityAnim(self.Pointer)
end

function Entity:setRenderMode(Mode)
    setEntityRenderMode(self.Pointer, Mode)
end

function Entity:getRenderMode()
    return getEntityRenderMode(self.Pointer)
end

function Entity:setZIndex(ZIndex)
    setEntityZIndex(self.Pointer, ZIndex)
end

function Entity:getZIndex()
    return getEntityZIndex(self.Pointer)
end

function Entity:toggleHUD(Boolean)
    toggleEntityHUD(self.Pointer, Boolean)
end

function Entity:isHUD()
    return getEntityHUD(self.Pointer)
end

function Entity:setTexture(Texture)
    setEntityTexture(self.Pointer, Texture)
end

function Entity:getTexture()
    return getEntityTexture(self.Pointer)
end

