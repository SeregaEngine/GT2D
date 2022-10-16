----------------------------------------------------------------------
--| * MainMenu.lua *
----------------------------------------------------------------------

---- Includes
require "Mission"

---- Menu
function Mission.onEnter(Location)
	-- Defines
	ARROW_TRY_RATE = 150

	BUTTON_CHAR_WIDTH = 4
	BUTTON_HEIGHT = 8
	MAX_BUTTONS = 4

	-- Globals
	LastArrowTry = 0
	IgnoreClick = (Input.isKeyDown(GTK_RETURN) or Input.isMouseDown(GTM_LEFT)) and true or false

	Buttons = {}
	for i = 1,MAX_BUTTONS do Buttons[i] = {} end

	Buttons[1].IsAvailable = Saver.hasSave() and true or false
	Buttons[1].Text = "Continue"
	Buttons[1].Width = string.len(Buttons[1].Text) * BUTTON_CHAR_WIDTH
	Buttons[1].X = (SCREEN_WIDTH - Buttons[1].Width)/2
	Buttons[1].Y = (SCREEN_HEIGHT - BUTTON_HEIGHT*MAX_BUTTONS)/2
	Buttons[1].Action = function() Mission.switch("Scripts/Internal/Loader.lua", 1) end
	
	Buttons[2].IsAvailable = true
	Buttons[2].Text = "New game"
	Buttons[2].Width = string.len(Buttons[2].Text) * BUTTON_CHAR_WIDTH
	Buttons[2].X = (SCREEN_WIDTH - Buttons[2].Width)/2
	Buttons[2].Y = Buttons[1].Y + BUTTON_HEIGHT
	Buttons[2].Action = function() Saver.delete(); Mission.switch("Scripts/Internal/Loader.lua", 1) end

	Buttons[3].IsAvailable = true
	Buttons[3].Text = "Credits"
	Buttons[3].Width = string.len(Buttons[3].Text) * BUTTON_CHAR_WIDTH
	Buttons[3].X = (SCREEN_WIDTH - Buttons[3].Width)/2
	Buttons[3].Y = Buttons[2].Y + BUTTON_HEIGHT
	Buttons[3].Action = function() Mission.switch("Scripts/Credits.lua", 1) end

	Buttons[4].IsAvailable = true
	Buttons[4].Text = "Leave"
	Buttons[4].Width = string.len(Buttons[4].Text) * BUTTON_CHAR_WIDTH
	Buttons[4].X = (SCREEN_WIDTH - Buttons[4].Width)/2
	Buttons[4].Y = Buttons[3].Y + BUTTON_HEIGHT
	Buttons[4].Action = function() Mission.stop() end

	-- Some global stuff
	Active = Buttons[1].IsAvailable and 1 or 2
end

function Mission.onUpdate(dt)
	if Console.isShown() then
		return
	end

	-- Handle arrow keys
	if Input.isKeyDown(GTK_UP) and Clock.getTicks() - LastArrowTry > ARROW_TRY_RATE and Buttons[Active-1] and Buttons[Active-1].IsAvailable then
		Active = Active - 1
		LastArrowTry = Clock.getTicks()
	elseif Input.isKeyDown(GTK_DOWN) and Clock.getTicks() - LastArrowTry > ARROW_TRY_RATE and Buttons[Active+1] and Buttons[Active+1].IsAvailable then
		Active = Active + 1
		LastArrowTry = Clock.getTicks()
	end

	-- Handle mouse
	local X,Y = Input.getMousePosition()
	for i,v in ipairs(Buttons) do
	   if Buttons[i].IsAvailable and
	      X >= Buttons[i].X and X < Buttons[i].X + Buttons[i].Width and
	      Y >= Buttons[i].Y and Y < Buttons[i].Y + BUTTON_HEIGHT then
		Active = i
		break
	  end
	end

	-- Handle button enter
	if IgnoreClick and not Input.isKeyDown(GTK_RETURN) and not Input.isMouseDown(GTM_LEFT) then
		IgnoreClick = false
	end

	if not IgnoreClick and (Input.isKeyDown(GTK_RETURN) or Input.isMouseDown(GTM_LEFT)) then
		Buttons[Active].Action()
	end
end

function Mission.onRender()
	Graphics.setDrawColor(190, 80, 0, 255)
	Graphics.fillRect(RENDER_MODE_FOREGROUND, 999, true, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT })

	for i,v in ipairs(Buttons) do
		setButtonColor(i)
		Graphics.drawText(RENDER_MODE_FOREGROUND, 1000, true, { Buttons[i].X, Buttons[i].Y, Buttons[i].Width, BUTTON_HEIGHT }, Buttons[i].Text)
	end
end

function setButtonColor(Index)
	if Active == Index then
		Graphics.setDrawColor(255, 255, 255, 170)
	elseif not Buttons[Index].IsAvailable then
		Graphics.setDrawColor(255, 255, 255, 60)
	else
		Graphics.setDrawColor(255, 255, 255, 255)
	end
end
