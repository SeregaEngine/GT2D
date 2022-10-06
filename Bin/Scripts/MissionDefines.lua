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

---- Functions
local CanAttack = true
function handleInput()
    -- Leave if console is shown
    if isConsoleShown() then
        return
    end

    -- Stop game on escape
    if isKeyDown(GTK_ESCAPE) then
        stopGame()
    end

    -- Handle Player's behaviour
    if Player and PlayerControllable then
        if isKeyDown(GTK_W) then sendActorCmd(Player, GTC_MOVE_UP) end
        if isKeyDown(GTK_A) then sendActorCmd(Player, GTC_MOVE_LEFT) end
        if isKeyDown(GTK_S) then sendActorCmd(Player, GTC_MOVE_DOWN) end
        if isKeyDown(GTK_D) then sendActorCmd(Player, GTC_MOVE_RIGHT) end

        -- Handle attack
        -- Player have to press space many times
        local IsSpaceDown = isKeyDown(GTK_SPACE)
        if IsSpaceDown and CanAttack then
            sendActorCmd(Player, GTC_ATTACK)
            CanAttack = false
        elseif not IsSpaceDown then
            CanAttack = true
        end
    end
end
