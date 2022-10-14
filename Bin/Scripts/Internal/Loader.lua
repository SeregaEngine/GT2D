----------------------------------------------------------------------
--| * Loader.lua *
----------------------------------------------------------------------

-- TODO(sean) Read save file
---- Includes
require "Mission"

---- Loader
function Mission.onEnter(Location)
	GT_LOG(PR_NOTE, "Loader entered")
	Mission.switch("Scripts/Mission2.lua", 1)
end

function Mission.onUpdate(dt)
end

function Mission.onRender()
	Graphics.setDrawColor(0, 0, 0, 255)
	Graphics.fillRect(DRAW_FRAME_BACKGROUND, 999, true, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT })
end

