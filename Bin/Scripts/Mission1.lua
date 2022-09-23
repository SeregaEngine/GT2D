dofile "Scripts/GraphicsDefines.lua"

-- Defines
CAMERA_X = 0
CAMERA_Y = 0
CAMERA_WIDTH = SCREEN_WIDTH * 2
CAMERA_HEIGHT = SCREEN_HEIGHT

GROUND_WIDTH = SCREEN_WIDTH * 2
GROUND_HEIGHT = 19
GROUND_X = 0
GROUND_Y = SCREEN_HEIGHT - GROUND_HEIGHT

-- Variables
textures = {}
sounds = {}
music = {}
states = {}
entities = {}

player = {}

function onEnter()
  GT_LOG(PR_NOTE, "Mission1 entered")

  -- Textures
  textures["background"] = defineTexture("Textures/Locations/Mission1-1.png", TW_LOCATION, TH_LOCATION)
  textures["parallax"] = defineTexture("Textures/Locations/Mission1-1_Parallax.png", TW_PARALLAX, TH_PARALLAX)
  textures["player"] = defineTexture("Textures/Actors/Player.png", TW_ACTOR, TH_ACTOR)

  -- Sound and music
  sounds["test"] = defineSound("Sounds/TestSound.wav")
  music["test"] = defineMusic("Music/TestMusic.mp3")

  -- States
  states["NPC"] = defineState("stateNPC")

  -- Entities
  entities["player"] = addActor(10, 60, TW_ACTOR, TH_ACTOR, textures["player"])
  player = entities["player"]
  entities["NPC"] = addActor(20, 60, TW_ACTOR, TH_ACTOR, textures["player"])

  -- Triggers
  entities["trigger"] = addTrigger(120, SCREEN_HEIGHT-8, 30, 8, entities["player"], "onTrigger")

  -- Set up level
  setBackground(textures["background"])
  setParallax(textures["parallax"])
  setGroundBounds(GROUND_X, GROUND_Y, GROUND_WIDTH, GROUND_HEIGHT)

  setCameraBounds(CAMERA_X, CAMERA_Y, CAMERA_WIDTH, CAMERA_HEIGHT)
  attachCamera(entities["player"])

  -- Set up Actors
  setActorState(entities["NPC"], states["NPC"])
end

function onUpdate(dt)
  handleInput()
end

function handleInput()
  -- Leave if console is shown
  if isConsoleShown() then
    return
  end

  -- Stop game on escape
  if isKeyDown(GTK_ESCAPE) then
    stopGame()
  end

  -- Handle player's behaviour
  if player then
    if isKeyDown(GTK_W) then sendActorCmd(player, GTC_MOVE_UP) end
    if isKeyDown(GTK_A) then sendActorCmd(player, GTC_MOVE_LEFT) end
    if isKeyDown(GTK_S) then sendActorCmd(player, GTC_MOVE_DOWN) end
    if isKeyDown(GTK_D) then sendActorCmd(player, GTC_MOVE_RIGHT) end

    if isKeyDown(GTK_SPACE) then sendActorCmd(player, GTC_ATTACK) end
  end
end

local onTrigger_count = 0 -- DEBUG(sean)
function onTrigger(entity)
  onTrigger_count = onTrigger_count + 1
  GT_LOG(PR_NOTE, string.format("onTrigger() entered %d times", onTrigger_count))
end

local stateNPC_tasks = {
  [1] = {
    ["task"] = GTT_GOTO,
    ["x"] = 30.0,
    ["y"] = 56.0
  },

  [2] = {
    ["task"] = GTT_GOTO,
    ["x"] = 40.0,
    ["y"] = 60.0
  },

  [3] = {
    ["task"] = GTT_GOTO,
    ["x"] = 50.0,
    ["y"] = 60.0
  },

  [4] = {
    ["task"] = GTT_GOTO,
    ["x"] = 70.0,
    ["y"] = 64.0
  },

  [5] = {
    ["task"] = GTT_GOTO,
    ["x"] = 80.0,
    ["y"] = 64.0
  },

  [6] = {
    ["task"] = GTT_GOTO,
    ["x"] = 128.0,
    ["y"] = 64.0
  },

  [7] = {
      ["task"] = GTT_NONE
  }
}
local stateNPC_counter = 0

function stateNPC(actor)
  if stateNPC_counter == 0 or checkActorTask(actor) == GTT_DONE then
    stateNPC_counter = stateNPC_counter + 1
    if stateNPC_tasks[stateNPC_counter].task == GTT_NONE then
      stateNPC_counter = 0
      --[[
      setActorTask(actor, GTT_NONE)
      setActorState(actor, nil)
      ]]--
    else
      setActorTask(actor, stateNPC_tasks[stateNPC_counter].task, stateNPC_tasks[stateNPC_counter].x, stateNPC_tasks[stateNPC_counter].y)
    end
  end
end

