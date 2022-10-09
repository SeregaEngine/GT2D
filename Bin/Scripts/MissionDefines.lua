----------------------------------------------------------------------
--| * MissionDefines.lua *
--|
--| Contains default defines, resources
--| and functions for every mission
----------------------------------------------------------------------

---- Defines
DEBUG = true

-- Location
TW_LOCATION = SCREEN_WIDTH
TH_LOCATION = SCREEN_HEIGHT

GW_LOCATION = TW_LOCATION
GH_LOCATION = TH_LOCATION

-- Actor
TW_ACTOR = 16
TH_ACTOR = 16

GW_ACTOR = TW_ACTOR
GH_ACTOR = TH_ACTOR

-- Car
TW_CAR = 72
TH_CAR = 21

-- Dialog
TW_DIALOG = 320
TH_DIALOG = 200

GW_DIALOG = 32
GH_DIALOG = 20

---- Resources
Textures = {}
Sounds = {}
Music = {}
Anims = {}
Weapons = {}
States = {}

Textures["Blank"] = defineTexture("Textures/Special/Blank.png", 1, 1)
Textures["DialogSquare"] = defineTexture("Textures/DialogBox/Square.png", TW_DIALOG, TH_DIALOG)

Sounds["Punch1"] = defineSound("Sounds/Punch1.wav")
Sounds["Punch2"] = defineSound("Sounds/Punch2.wav")
Sounds["Punch3"] = defineSound("Sounds/Punch3.wav")
Sounds["Punch4"] = defineSound("Sounds/Punch4.wav")
Sounds["ActorDeath"] = defineSound("Sounds/ActorDyingSound.wav")
Sounds["CarDoor"] = defineSound("Sounds/CarDoorOpening.wav")
Sounds["StartEngine"] = defineSound("Sounds/DodgeEngineStart.wav")

Weapons["Fist"] = defineWeapon(defineAnimation(4, 3, 1000.0 / 2.0), 4, 8, 8, 1.0, Sounds["Punch1"], Sounds["Punch2"], Sounds["Punch3"], Sounds["Punch4"])

---- Globals
Entities = {}

Player = nil
PlayerControllable = true

---- Singletons
-- Graphics
Graphics = {}

function Graphics.defineTexture(Path, SpriteWidth, SpriteHeight)
    return defineTexture(Path, SpriteWidth, SpriteHeight)
end

function Graphics.setDrawColor(R, G, B, A)
    setDrawColor(R, G, B, A)
end

--- *** Rect[1] = X, Rect[2] = Y, Rect[3] = W, Rect[4] = H *** ---
function Graphics.drawFrame(RenderMode, ZIndex, IsHUD, Rect, Texture, Row, Frame)
    drawFrame(RenderMode, ZIndex, IsHUD, Rect[1], Rect[2], Rect[3], Rect[4], Texture, Row, Frame)
end

function Graphics.drawText(RenderMode, ZIndex, IsHUD, Rect, Text)
    drawText(RenderMode, ZIndex, IsHUD, Rect[1], Rect[2], Rect[3], Rect[4], Text)
end

function Graphics.fillRect(RenderMode, ZIndex, IsHUD, Rect)
    fillRect(RenderMode, ZIndex, IsHUD, Rect[1], Rect[2], Rect[3], Rect[4])
end

function Graphics.drawRect(RenderMode, ZIndex, IsHUD, Rect)
    drawRect(RenderMode, ZIndex, IsHUD, Rect[1], Rect[2], Rect[3], Rect[4])
end

-- Camera
Camera = {}

function Camera.attach(TEntity)
    attachCamera(TEntity.Pointer)
end

function Camera.detach()
    detachCamera()
end

function Camera.setPosition(X, Y)
    setCameraPosition(X, Y)
end

function Camera.getPosition()
    return getCameraPosition()
end

function Camera.setBounds(Rect)
    setCameraBounds(Rect[1], Rect[2], Rect[3], Rect[4])
end

-- Sound
Sound = {}

function Sound.defineSound(Path)
    return defineSound(Path)
end

function Sound.defineMusic(Path)
    return defineMusic(Path)
end

function Sound.playSound(SoundObject)
    playSound(SoundObject)
end

function Sound.playMusic(MusicObject)
    playMusic(MusicObject)
end

-- Input
Input = {}

function Input.isKeyDown(Key)
    return isKeyDown(Key)
end

function Input.isMouseDown(Button)
    return isMouseDown(Button)
end

function Input.getMousePosition()
    return getMousePosition()
end

-- Console
Console = {}

function Console.isShown()
    return isConsoleShown()
end

function Console.cls()
    cls()
end

-- AI
AI = {}

function AI.defineState(FunctionName)
    return defineState(FunctionName)
end

-- Animation
Animation = {}

function Animation.define(Row, Count, FrameTime)
    return defineAnimation(Row, Count, FrameTime)
end

-- Clock
Clock = {}

function Clock.getTicks()
    return getTicks()
end

-- Mission
Mission = {}

function Mission.stop()
    stopGame()
end

function Mission.switch(Path, Location)
    switchMission(Path, Location)
end

function Mission.restart(Location)
    restartMission(Location)
end

function Mission.setGroundBounds(Rect)
    setGroundBounds(Rect[1], Rect[2], Rect[3], Rect[4])
end

---- Classes
-- Entity
Entity = { Pointer = nil }

function Entity:inherit(Object)
    Object = Object or {} -- Optional argument

    setmetatable(Object, self)
    self.__index = self

    return Object
end

function Entity:new(X, Y, W, H, Texture)
    local Object = inherit()
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

-- Actor
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
    setActorDeathSound(self.Pointer, Sound)
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

-- Car
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

-- Dialog
Dialog = Entity:inherit()

function Dialog:new(W, H, Text, DurationSeconds, Actor, Texture)
    local Object = self:inherit()
    Object.Pointer = addDialog(W, H, Text, DurationSeconds, Actor, Texture)
    return Object
end

function Dialog:run()
    runDialog(self.Pointer)
end

-- Trigger
Trigger = Entity:inherit()

function Trigger:new(Rect, Actor, FunctionName)
    local Object = self:inherit()
    Object.Pointer = addTrigger(Rect[1], Rect[2], Rect[3], Rect[4], Actor, FunctionName)
    return Object
end

---- Functions
function handleInput()
    -- Leave if console is shown
    if Console.isShown() then
        return
    end

    -- Stop game on escape
    if Input.isKeyDown(GTK_ESCAPE) then
        stopGame()
    end

    -- Handle Player's behaviour
    if Player and PlayerControllable then
        if Input.isKeyDown(GTK_W) then Player:pushCommand(GTC_MOVE_UP) end
        if Input.isKeyDown(GTK_A) then Player:pushCommand(GTC_MOVE_LEFT) end
        if Input.isKeyDown(GTK_S) then Player:pushCommand(GTC_MOVE_DOWN) end
        if Input.isKeyDown(GTK_D) then Player:pushCommand(GTC_MOVE_RIGHT) end

        -- Handle attack
        -- Player have to press space many times
        local IsSpaceDown = Input.isKeyDown(GTK_SPACE)
        if IsSpaceDown and CanAttack then
            Player:pushCommand(GTC_ATTACK)
            CanAttack = false
        elseif not IsSpaceDown then
            CanAttack = true
        end
    end
end

function createCutscene(FunGetActions, FunChangeAndGetActionStage, FunInit, FunEnd)
    return function(TActor)
        if FunChangeAndGetActionStage(0) == 0 then
            FunInit(TActor)
        end

        local Actions = FunGetActions()
        local Stage = FunChangeAndGetActionStage(0)

        while Stage == 0 or Stage > #Actions or not Actions[Stage][2] or Actions[Stage][1]:checkCurrentTask() == GTT_DONE do
            Stage = FunChangeAndGetActionStage(1)

            if Stage > #Actions then
                FunEnd(TActor)
                return
            end

            Actions[Stage][1]:pushTask(Actions[Stage][3], Actions[Stage][4], Actions[Stage][5])
        end
    end
end

