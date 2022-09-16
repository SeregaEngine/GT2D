dofile "Scripts/GraphicsDefines.lua"

-- Defines

-- Variables
local textures = {}
local sounds = {}
local music = {}

local states = {}
local entities = {}

function onEnter()
  GT_LOG(PR_NOTE, "Mission1 entered")

  -- Set background stuff
  textures["background"] = defineTexture("Textures/Locations/Mission1-1.png", TW_LOCATION, TH_LOCATION)
  textures["parallax"] = defineTexture("Textures/Locations/Mission1-1_Parallax.png", TW_PARALLAX, TH_PARALLAX)

  setBackground(textures["background"])
  setParallax(textures["parallax"])

  -- Sound and music
  sounds["test"] = defineSound("Sounds/TestSound.wav")
  music["test"] = defineMusic("Music/TestMusic.mp3")

  -- AI state
  states["NPC"] = defineState("stateNPC")

  -- Player
  textures["player"] = defineTexture("Textures/Actors/Player.png", TW_ACTOR, TH_ACTOR)
  entities["player"] = addActor(10, 60, TW_ACTOR, TH_ACTOR, textures["player"])

  -- NPC
  entities["NPC"] = addActor(TW_LOCATION, TH_LOCATION - TH_ACTOR/2, TW_ACTOR, TH_ACTOR, textures["player"])
  setActorState(entities["NPC"], states["NPC"])

  -- Camera
  setLevelSize(TW_LOCATION * 2, TH_LOCATION)
  attachCamera(entities["player"])
end

function onUpdate(dt)
  handleInput()
  updateAllEntities(dt)
end

function handleInput()
  if isKeyDown(GTK_ESCAPE) then
    stopGame()
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

function stateNPC(actor)
  local n = math.random(1, 4)
  if     n == 1 then sendActorCmd(actor, GTC_MOVE_UP)
  elseif n == 2 then sendActorCmd(actor, GTC_MOVE_LEFT)
  elseif n == 3 then sendActorCmd(actor, GTC_MOVE_DOWN)
  elseif n == 4 then sendActorCmd(actor, GTC_MOVE_RIGHT)
  end
end
