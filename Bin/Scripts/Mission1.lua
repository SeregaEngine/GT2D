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
  entities["NPC"] = addActor(10, 60, TW_ACTOR, TH_ACTOR, textures["player"])

  -- Set up level
  setBackground(textures["background"])
  setParallax(textures["parallax"])
  setLevelSize(TW_LOCATION * 2, TH_LOCATION)
  attachCamera(entities["player"])

  -- Set up Actors
  setActorState(entities["NPC"], states["NPC"])
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

local stateNPC_tasks = {
  [1] = {
    ["task"] = GTT_GOTO,
    ["x"] = 30.0,
    ["y"] = 56.0
  },

  [2] = {
    ["task"] = GTT_GOTO,
    ["x"] = 85.0,
    ["y"] = 50.0
  },

  [3] = {
    ["task"] = GTT_GOTO,
    ["x"] = 85.0,
    ["y"] = 30.0
  },

  [4] = {
    ["task"] = GTT_GOTO,
    ["x"] = 130.0,
    ["y"] = 43.0
  },

  [5] = {
    ["task"] = GTT_GOTO,
    ["x"] = 70.0,
    ["y"] = 60.0
  },

  [6] = {
    ["task"] = GTT_GOTO,
    ["x"] = 70.0,
    ["y"] = 67.0
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

