dofile "Scripts/GraphicsDefines.lua"

function onEnter()
  GT_LOG(PR_NOTE, "Mission1: onEnter()")

  local bg = defineTexture("Textures/Locations/Mission1-1.png", TW_LOCATION, TH_LOCATION)
  local pl = defineTexture("Textures/Locations/Mission1-1_Parallax.png", TW_PARALLAX, TH_PARALLAX)

  setBackground(bg)
  setParallax(pl)

  local sound = defineSound("Sounds/TestSound.wav")
  local music = defineMusic("Music/TestMusic.mp3")

  playSound(sound)
  playMusic(music)
end
