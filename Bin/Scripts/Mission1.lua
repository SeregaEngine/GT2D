dofile "Scripts/GraphicsDefines.lua"

-- Defines

-- Globals
local entity_list = {}

function onEnter()
  GT_LOG(PR_NOTE, "Mission1: onEnter()")

  -- Set background stuff
  local bg = defineTexture("Textures/Locations/Mission1-1.png", TW_LOCATION, TH_LOCATION)
  local pl = defineTexture("Textures/Locations/Mission1-1_Parallax.png", TW_PARALLAX, TH_PARALLAX)

  setBackground(bg)
  setParallax(pl)

  --[[ Music/sound test
  local sound = defineSound("Sounds/TestSound.wav")
  local music = defineMusic("Music/TestMusic.mp3")

  playSound(sound)
  playMusic(music)
  ]]--

  local player_texture = defineTexture("Textures/Actors/Player.png", TW_ACTOR, TH_ACTOR)
  entity_list["player"] = addPlayer(0, 0, TW_ACTOR, TH_ACTOR, player_texture)

end
