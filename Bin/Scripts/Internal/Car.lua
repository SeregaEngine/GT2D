----------------------------------------------------------------------
--| * Car.lua *
----------------------------------------------------------------------

Car = Entity:inherit()

function Car:new(X, Y, W, H, Texture)
    local Object = self:inherit()
    Object.Pointer = addCar(X, Y, W, H, Texture)
    return Object
end

function Car:turnLeft()
    turnCarLeft(self.Pointer)
end

function Car:turnRight()
    turnCarRight(self.Pointer)
end

function Car:setMaxSpeed(X, Y)
    setCarMaxSpeed(self.Pointer, X, Y)
end

function Car:setAcceleration(X, Y)
    setCarAcceleration(self.Pointer, X, Y)
end

function Car:setPlacePosition(Place, X, Y)
    setCarPlacePosition(self.Pointer, Place, X, Y)
end

function Car:putActor(TActor, Place)
    putActorInCar(TActor.Pointer, self.Pointer, Place)
end

function Car:ejectActor(Place)
    ejectActorFromCar(self.Pointer, Place)
end
