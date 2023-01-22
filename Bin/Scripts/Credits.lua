----------------------------------------------------------------------
--| * Credits.lua *
----------------------------------------------------------------------

---- Includes
require "Mission"

---- Resources
Musics["Music"] = Resource.defineMusic("Music/Credits.mp3")

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
		"GAME DIRECTOR",
		"Sergey Nikonov",
		"GAME DESIGNER",
		"Ahmed Said",
		" ",
		" ",
		"CONCEPT ART DIRECTOR",
		"Ahmed Said",
		"TECHNICAL ART DIRECTOR",
		"Sergey Nikonov",
		" ",
		" ",
		"HEAD OF ANIMATION / ANIMATION DIRECTOR",
		"Sergey Nikonov",
		"ENVIRONMENT ART DIRECTOR",
		"Ahmed Said",
		" ",
		" ",
		"QUEST DESIGN DIRECTOR",
		"Ahmed Said",
		"PERSON STORIES DIRECTOR",
		"Sergey Nikonov",
		" ",
		" ",
		"CINEMATIC DIRECTOR",
		"Sergey Nikonov",
		"STORY DIRECTOR",
		"Ahmed Said",
		" ",
		" ",
		"LORE CONSULTATION DIRECTOR",
		"Ahmed Said",
		"MUSIC DIRECTOR",
		"Sergey Nikonov",
		" ",
		" ",
		"LEAD PROGRAMMER",
		"Sergey Nikonov",
		"DESIGN LEAD",
		"Ahmed Said",
	}
	Y = SCREEN_HEIGHT * 1.1
	YMax = -(TITLE_HEIGHT + #Credits/2 * POSITION_HEIGHT + #Credits/2 * NAME_HEIGHT) * 1.1

	Musics["Music"]:play()
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
