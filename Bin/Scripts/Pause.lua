----------------------------------------------------------------------
--| * Pause.lua *
--|
--| Have no resources to prevent leaks, cause of UndefineStuff()
--| behavior, which undefine everything, so we
--| can't free memory on PauseState.
----------------------------------------------------------------------

require "Mission"

function Mission.onEnter(Location)
	GT_LOG(PR_NOTE, "Game paused")
end

function Mission.onUpdate(dt)
	if Input.isKeyDown(GTK_SPACE) then
		Mission.resume()
	end
end

function Mission.onRender()
	Graphics.setDrawColor(0, 0, 0, 160)
	Graphics.fillRect(RENDER_MODE_FOREGROUND, true, 999, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT })
end
