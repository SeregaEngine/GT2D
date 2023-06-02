----------------------------------------------------------------------
--| * Pause.lua *
--|
--| Have no resources to prevent leaks, cause of UndefineStuff()
--| behavior, which undefine everything, so we
--| can't free memory on PauseState.
----------------------------------------------------------------------

require "Mission"

---- Defines
local BUTTON_CHAR_WIDTH = 4
local BUTTON_HEIGHT = 8

local BUTTON_CONTINUE_TEXT = "Continue"
local BUTTON_CONTINUE_WIDTH = string.len(BUTTON_CONTINUE_TEXT) * BUTTON_CHAR_WIDTH
local BUTTON_CONTINUE_X = (SCREEN_WIDTH - BUTTON_CONTINUE_WIDTH)/2
local BUTTON_CONTINUE_Y = (SCREEN_HEIGHT - BUTTON_HEIGHT*2)/2

local BUTTON_EXIT_TEXT = "Exit"
local BUTTON_EXIT_WIDTH = string.len(BUTTON_EXIT_TEXT) * BUTTON_CHAR_WIDTH
local BUTTON_EXIT_X = (SCREEN_WIDTH - BUTTON_EXIT_WIDTH)/2
local BUTTON_EXIT_Y = BUTTON_CONTINUE_Y + BUTTON_HEIGHT

---- Global
local Active

function Mission.onEnter(Location)
	GT_LOG(PR_NOTE, "Game paused")
	showCursor()

	-- Defines
	Active = BUTTON_CONTINUE_TEXT 
end

function Mission.onUpdate(dt)
	if Console.isShown() then
		return
	end

	local X,Y = Input.getMousePosition()
	if (Input.isKeyDown(GTK_UP)) or
	   (X >= BUTTON_CONTINUE_X and X < BUTTON_CONTINUE_X + BUTTON_CONTINUE_WIDTH and
	    Y >= BUTTON_CONTINUE_Y and Y < BUTTON_CONTINUE_Y + BUTTON_HEIGHT) then
		Active = BUTTON_CONTINUE_TEXT
	elseif (Input.isKeyDown(GTK_DOWN)) or
	       (X >= BUTTON_EXIT_X and X < BUTTON_EXIT_X + BUTTON_EXIT_WIDTH and
	        Y >= BUTTON_EXIT_Y and Y < BUTTON_EXIT_Y + BUTTON_HEIGHT) then
		Active = BUTTON_EXIT_TEXT
	end

	if Input.isKeyDown(GTK_RETURN) or Input.isMouseDown(GTM_LEFT) then
		if Active == BUTTON_CONTINUE_TEXT then
			Mission.resume()
			GT_LOG(PR_NOTE, "Game resumed")
		else
			Mission.exitToMainMenu()
			GT_LOG(PR_NOTE, "Game exited to main menu")
		end
	end
end

function Mission.onRender()
	Graphics.setDrawColor(160, 50, 0, 160)
	Graphics.fillRect(RENDER_MODE_FOREGROUND, 999, true, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT })

	setButtonColor(BUTTON_CONTINUE_TEXT)
	Graphics.drawText(RENDER_MODE_FOREGROUND, 1000, true, { BUTTON_CONTINUE_X, BUTTON_CONTINUE_Y, BUTTON_CONTINUE_WIDTH, BUTTON_HEIGHT }, BUTTON_CONTINUE_TEXT, FONT_LARGE)
	setButtonColor(BUTTON_EXIT_TEXT)
	Graphics.drawText(RENDER_MODE_FOREGROUND, 1000, true, { BUTTON_EXIT_X, BUTTON_EXIT_Y, BUTTON_EXIT_WIDTH, BUTTON_HEIGHT }, BUTTON_EXIT_TEXT, FONT_LARGE)
end

function setButtonColor(ButtonName)
	if ButtonName == Active then
		Graphics.setDrawColor(255, 255, 255, 170)
	else
		Graphics.setDrawColor(255, 255, 255, 255)
	end
end
