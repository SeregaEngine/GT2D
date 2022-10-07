-- TODO(sean) Read save file

function onEnter(Location)
	GT_LOG(PR_NOTE, "Loader entered")
	switchMission("Scripts/Mission0.lua", 1)
end

function onUpdate(dt)
end

function onRender()
	setDrawColor(0, 0, 0, 255)
	fillRect(DRAW_FRAME_BACKGROUND, 999, true, 0,0,SCREEN_WIDTH,SCREEN_HEIGHT)
end

