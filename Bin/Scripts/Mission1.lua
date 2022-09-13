dofile "Scripts/GraphicsDefines.lua"

local TID_BG = 0
local TID_BG = 1

function onEnter()
  GT_LOG(PR_NOTE, "Mission1: onEnter()")

  local bg = defineTexture(TID_BG, "Textures/Locations/Mission1-1.png", TW_LOCATION, TH_LOCATION)
  local pl = defineTexture(TID_PL, "Textures/Locations/Mission1-1_Parallax.png", TW_PARALLAX, TH_PARALLAX)

  setBackground(bg)
  setParallax(pl)
end
