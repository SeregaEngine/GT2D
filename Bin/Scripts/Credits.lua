----------------------------------------------------------------------
--| * Credits.lua *
----------------------------------------------------------------------

---- Includes
require "Mission"

function Mission.onEnter(Location)
	-- Defines
	TITLE_CHAR_WIDTH = 5
	TITLE_HEIGHT = 10

	POSITION_CHAR_WIDTH = 2.5
	POSITION_HEIGHT = 5

	NAME_CHAR_WIDTH = 2
	NAME_HEIGHT = 4

	-- Globals
	Title = "Petrol: The Fastest"
	Credits = {
		" ",
		" ",
		"GAME DESIGNER",
		"Ahmed Said",
		"GAME DIRECTOR",
		"Sergey Nikonov",
		"ART DIRECTOR",
		"Kirill Sednev",
		" ",
		" ",
		"CONCEPT ART DIRECTOR",
		"Ahmed Said",
		"CINEMATIC DIRECTOR",
		"Sergey Nikonov",
		"DIRECTOR DIRECTOR",
		"Kirill Sednev",
		" ",
		" ",
		"QUEST DESIGN DIRECTOR",
		"Ahmed Said",
		"PERSON STORIES DIRECTOR",
		"Sergey Nikonov",
		"HEAD OF ANIMAITON / ANIMATION DIRECTOR",
		"Kirill Sednev",
		" ",
		" ",
		"STORY DIRECTOR",
		"Ahmed Said",
		"TECHNICAL ART DIRECTOR",
		"Sergey Nikonov",
		"ENVIRONMENT ART DIRECTOR",
		"Kirill Sednev",
		" ",
		" ",
		"DESIGN, STORY AND LORE CONSULTATION DIRECTOR",
		"Ahmed Said",
		"MUSIC DIRECTOR",
		"Sergey Nikonov",
		"CHARACTER, VEHICLES AND WEAPON ART DIRECTOR",
		"Kirill Sednev",
		" ",
		" ",
		"DESIGN LEAD",
		"Ahmed Said",
		"LEAD PROGRAMMER",
		"Sergey Nikonov",
		"ART LEAD",
		"Kirill Sednev",
	}
	Y = SCREEN_HEIGHT
	YMax = -(TITLE_HEIGHT + #Credits/2 * POSITION_HEIGHT + #Credits/2 * NAME_HEIGHT) * 1.1
end

function Mission.onUpdate(dt)
	Input.defaultHandle()
	Y = Y - (dt * 0.005)

	if Y < YMax then
		Mission.switch("Scripts/MainMenu.lua", 1)
	end
end

function Mission.onRender()
	Graphics.setDrawColor(0, 0, 0, 255)
	Graphics.fillRect(RENDER_MODE_BACKGROUND, 0, true, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT })

	Graphics.setDrawColor(255, 255, 255, 255)
	Graphics.drawText(RENDER_MODE_BACKGROUND, 1, true, { (SCREEN_WIDTH - string.len(Title)*TITLE_CHAR_WIDTH)/2, Y, string.len(Title)*TITLE_CHAR_WIDTH, TITLE_HEIGHT }, Title)

	local YPos = Y + TITLE_HEIGHT
	for i,v in ipairs(Credits) do
		local Width
		local Height
		if i % 2 == 1 then
			Width = POSITION_CHAR_WIDTH * string.len(v)
			Height = POSITION_HEIGHT
		else
			Width = NAME_CHAR_WIDTH * string.len(v)
			Height = NAME_HEIGHT
		end

		Graphics.drawText(RENDER_MODE_BACKGROUND, 1, true, { (SCREEN_WIDTH - Width)/2, YPos, Width, Height }, v)
		YPos = YPos + Height
	end
end
