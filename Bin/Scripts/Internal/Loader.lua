----------------------------------------------------------------------
--| * Loader.lua *
----------------------------------------------------------------------

---- Includes
require "Mission"

---- Loader
function Mission.onEnter(Location)
	GT_LOG(PR_NOTE, "Loader entered")

	-- Set default value
	local SaveInfo = {
		Path = "Scripts/MissionIntro.lua",
		Location = 1
	}

	-- Read save file or write default one
	local Test = io.open("Save", "r")
	if Test then
		Test:close()
		SaveInfo = dofile("Save")
		GT_LOG(PR_NOTE, "Save file found")
	else
		Saver.save(SaveInfo.Path, SaveInfo.Location)
		GT_LOG(PR_NOTE, "Save file didn't find, made new")
	end

	Mission.switch(SaveInfo.Path, SaveInfo.Location)
end

function Mission.onUpdate(dt)
end

function Mission.onRender()
	Graphics.setDrawColor(0, 0, 0, 255)
	Graphics.fillRect(DRAW_FRAME_BACKGROUND, 999, true, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT })
end

