----------------------------------------------------------------------
--| * Resource.lua *
----------------------------------------------------------------------

---- Singleton
Resource = {}

function Resource.defineTexture(Path, SpriteWidth, SpriteHeight)
    return defineTexture(Path, SpriteWidth, SpriteHeight)
end

function Resource.defineSound(Path)
    return Sound:new(Path)
end

function Resource.defineMusic(Path)
    return Music:new(Path)
end

function Resource.defineAnimation(Row, Count, FrameTime)
    return defineAnimation(Row, Count, FrameTime)
end

function Resource.defineWeapon(Anim, RangeX, RangeY, Damage, ...) -- <...> is sounds
    return defineWeapon(Anim, RangeX, RangeY, Damage, ...)
end

---- Basic resources
Textures = {}
Sounds = {}
Musics = {}
Anims = {}
Weapons = {}
Triggers = {}
States = {}

Textures["Blank"] = Resource.defineTexture("Textures/Special/Blank.png", 1, 1)
Textures["DialogSquare"] = Resource.defineTexture("Textures/DialogBox/Square.png", TW_DIALOG, TH_DIALOG)

Sounds["Punch1"] = Resource.defineSound("Sounds/Punch1.wav")
Sounds["Punch2"] = Resource.defineSound("Sounds/Punch2.wav")
Sounds["Punch3"] = Resource.defineSound("Sounds/Punch3.wav")
Sounds["Punch4"] = Resource.defineSound("Sounds/Punch4.wav")
Sounds["ActorDeath"] = Resource.defineSound("Sounds/ActorDyingSound.wav")
Sounds["CarDoorOpen"] = Resource.defineSound("Sounds/CarDoorOpening.wav")
Sounds["CarDoorClose"] = Resource.defineSound("Sounds/CarDoorClose.wav")
Sounds["StartEngine"] = Resource.defineSound("Sounds/DodgeEngineStart.wav")

Weapons["Fist"] = Resource.defineWeapon(Resource.defineAnimation(4, 3, 1000.0 / 2.0), 8, 8, 7.5, Sounds["Punch1"], Sounds["Punch2"], Sounds["Punch3"], Sounds["Punch4"])

