----------------------------------------------------------------------
--| * Mission.lua *
--|
--| Contains default defines, resources
--| and functions for every mission
----------------------------------------------------------------------

---- Defines
DEBUG = true

---- Globals
--- *** Will be free after Mission.switchLocation() *** ---
Entities = {}

Player = nil
IsPlayerControllable = true
---

---- Singleton
Mission = {}

--- *** Define this functions
Mission.onEnter = nil
Mission.onUpdate = nil
Mission.onRender = nil
--- ***

function Mission.stop()
    stopGame()
end

function Mission.switch(Path, Location)
    switchMission(Path, Location)
end

function Mission.restart(Location)
    restartMission(Location)
end

function Mission.pause()
    pauseMission()
end

function Mission.resume()
    resumeMission()
end

function Mission.exitToMainMenu()
    exitToMainMenu()
end

function Mission.setGroundBounds(Rect)
    setGroundBounds(Rect[1], Rect[2], Rect[3], Rect[4])
end

function Mission.switchLocation(Location)
    -- Set defaults
    Entities = {}
    Player = nil
    IsPlayerControllable = true

    -- Switch
    hostSwitchLocation(Location)
end

---- Includes
require "Console"
require "Graphics"
require "Camera"
require "Input"
require "Sound"
require "Music"
require "Clock"
require "Resource"

require "Entity"
require "Actor"
require "Car"
require "Dialog"
require "Trigger"

require "Saver"
require "Cutscene"
