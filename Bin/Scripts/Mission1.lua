dofile "Scripts/GraphicsDefines.lua"

-- Defines

-- Variables
local entities = {}
local textures = {}
local sounds = {}
local music = {}

function onEnter()
  GT_LOG(PR_NOTE, "onEnter() called")

  -- Set background stuff
  textures["background"] = defineTexture("Textures/Locations/Mission1-1.png", TW_LOCATION, TH_LOCATION)
  textures["parallax"] = defineTexture("Textures/Locations/Mission1-1_Parallax.png", TW_PARALLAX, TH_PARALLAX)

  setBackground(textures["background"])
  setParallax(textures["parallax"])

  -- Sound and music
  sounds["test"] = defineSound("Sounds/TestSound.wav")
  music["test"] = defineMusic("Music/TestMusic.mp3")

  --[[
  playSound(sounds["test"])
  playMusic(music["test"])
  ]]--

  -- Player
  textures["player"] = defineTexture("Textures/Actors/Player.png", TW_ACTOR, TH_ACTOR)
  entities["player"] = addActor(10, 60, TW_ACTOR, TH_ACTOR, textures["player"])

  -- Second player
  entities["player2"] = addActor(TW_LOCATION, TH_LOCATION - TH_ACTOR/2, TW_ACTOR, TH_ACTOR, textures["player"])

  -- Camera
  setLevelSize(TW_LOCATION * 2, TH_LOCATION)
  attachCamera(entities["player"])
end

function onUpdate(dt)
  handleInput()

  for k,v in pairs(entities) do
    updateEntity(v, dt)
  end

  x,y = getMousePosition()
  GT_LOG(PR_NOTE, string.format("%f %f", x, y))
end

function handleInput()
  if isKeyDown(GTK_ESCAPE) then
    stopGame()
  end

  if isKeyDown(GTK_UP) then
    sendActorCmd(entities["player2"], GTC_MOVE_UP)
  end
  if isKeyDown(GTK_LEFT) then
    sendActorCmd(entities["player2"], GTC_MOVE_LEFT)
  end
  if isKeyDown(GTK_DOWN) then
    sendActorCmd(entities["player2"], GTC_MOVE_DOWN)
  end
  if isKeyDown(GTK_RIGHT) then
    sendActorCmd(entities["player2"], GTC_MOVE_RIGHT)
  end

  if isKeyDown(GTK_W) then
    sendActorCmd(entities["player"], GTC_MOVE_UP)
  end
  if isKeyDown(GTK_A) then
    sendActorCmd(entities["player"], GTC_MOVE_LEFT)
  end
  if isKeyDown(GTK_S) then
    sendActorCmd(entities["player"], GTC_MOVE_DOWN)
  end
  if isKeyDown(GTK_D) then
    sendActorCmd(entities["player"], GTC_MOVE_RIGHT)
  end
end
