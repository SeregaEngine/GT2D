dofile "Scripts/GraphicsDefines.lua"

-- Defines

-- Variables
local entities = {}
local textures = {}
local sounds = {}
local music = {}

function onEnter()
  GT_LOG(PR_NOTE, "Mission entered")

  -- Set background stuff
  textures["background"] = defineTexture("Textures/Locations/Mission1-1.png", TW_LOCATION, TH_LOCATION)
  textures["parallax"] = defineTexture("Textures/Locations/Mission1-1_Parallax.png", TW_PARALLAX, TH_PARALLAX)

  setBackground(textures["background"])
  setParallax(textures["parallax"])

  -- Sound and music
  sounds["test"] = defineSound("Sounds/TestSound.wav")
  music["test"] = defineMusic("Music/TestMusic.mp3")

  --[[
  playSound(sounds["test"])
  playMusic(music["test"])
  ]]--

  -- Player
  textures["player"] = defineTexture("Textures/Actors/Player.png", TW_ACTOR, TH_ACTOR)
  entities["player"] = addActor(10, 60, TW_ACTOR, TH_ACTOR, textures["player"])

  -- Test entity
  entities["test"] = addEntity(TW_LOCATION, TH_LOCATION - TH_ACTOR/2, TW_ACTOR, TH_ACTOR, textures["player"])

  -- Camera
  setLevelSize(TW_LOCATION * 2, TH_LOCATION)
  attachCamera(entities["player"])
end

function onUpdate(dt)
  for k,v in pairs(entities) do
	updateEntity(v, dt)
  end
end
