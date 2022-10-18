----------------------------------------------------------------------
--| * Actor.lua *
----------------------------------------------------------------------

---- Defines
ACTOR_TEAM_FRIENDS = ACTOR_TEAM_DEFAULT + 1
ACTOR_TEAM_ENEMIES = ACTOR_TEAM_FRIENDS + 1

---- Singleton
Actor = Entity:inherit()

function Actor:new(X, Y, W, H, Texture)
    local Object = self:inherit()
    Object.Pointer = addActor(X, Y, W, H, Texture)
    return Object
end

function Actor:setTeam(Team)
    setActorTeam(self.Pointer, Team)
end

function Actor:getTeam()
    return getActorTeam(self.Pointer)
end

function Actor:setHealth(Health)
    setActorHealth(self.Pointer, Health)
end

function Actor:getHealth()
    return getActorHealth(self.Pointer)
end

function Actor:setHealth(Health)
    setActorHealth(self.Pointer, Health)
end

function Actor:getHealth()
    return getActorHealth(self.Pointer)
end

function Actor:isAlive()
    return isActorAlive(self.Pointer)
end

function Actor:toggleGodMode(Boolean)
    toggleActorGodMode(self.Pointer, Boolean)
end

function Actor:isLookRight()
    return isActorLookRight(self.Pointer)
end

function Actor:turnLeft()
    turnActorLeft(self.Pointer)
end

function Actor:turnRight()
    turnActorLeft(self.Pointer)
end

function Actor:setSpeed(X, Y)
    setActorSpeed(self.Pointer, X, Y)
end

function Actor:getSpeed()
    return getActorSpeed(self.Pointer)
end

function Actor:setState(State)
    setActorState(self.Pointer, State)
end

function Actor:pushTask(...)
    pushActorTask(self.Pointer, ...)
end

function Actor:pushCommand(Command)
    pushActorCommand(self.Pointer, Command)
end

function Actor:checkCurrentTask()
    return checkActorCurrentTask(self.Pointer)
end

function Actor:getCurrentTask()
    return getActorCurrentTask(self.Pointer)
end

function Actor:setDeathSound(Sound)
    setActorDeathSound(self.Pointer, Sound.Pointer)
end

function Actor:setWeapon(Weapon)
    setActorWeapon(self.Pointer, Weapon)
end

function Actor:setAttackRate(Rate)
    setActorAttackRate(self.Pointer, Rate)
end

function Actor:getAttackRate()
    return getActorAttackRate(self.Pointer)
end

function Actor:setActorAnim(WhichAnim, Anim)
    setActorAnim(self.Pointer, WhichAnim, Anim)
end

function Actor:stopAnim()
    stopActorAnim(self.Pointer)
end

function Actor:playAnimOnce(Anim)
    playActorAnimOnce(self.Pointer, Anim)
end

function Actor:playAnimLooped(Anim)
    playActorAnimLooped(self.Pointer, Anim)
end

