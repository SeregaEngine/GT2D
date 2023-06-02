# GameTemplate2D

## Summary
![](Project/Images/Header.png)

GameTemplate2D is game engine build with C++/SDL with Lua for scripting.

It was used to create [Petrol: The Fastest](https://snowfall-eagle.itch.io/petrol-the-fastest) game.

Watch [Petrol: The Fastest Trailer on YouTube](https://www.youtube.com/watch?v=pXLk-8X7ILQ)

![Screenshot](Project/Images/Screenshot1.png)

## Features

### AI
Actors are controlled by sending them a commands like GTC_TURN_LEFT or GTC_ATTACK.
Tasks are used to send this commands to actor for stuff like GTT_GOTO_ENTITY or GTT_KILL.
States are just Lua functions that you wrote in your mission's script file.

Also you can create cutscenes with Cutscene.new(FunInit, FunEnd) -> cutscene function
FunInit has declaration: function (TActor) -> Table of actors and tasks
and FunEnd: function (TActor) -> void

For more information you can check any mission script used in Petrol: The Fastest

### Rendering
When you want to render some stuff you have to specify it's render mode, z-index and is
it HUD (true if it's position should be in screen coordinates rather than world coordinates).

Also you can use dynamic render mode so you haven't worry about how to draw stuff.
Dynamic mode will sort dynamic render elements by their position:
if Entity1 has position (100.0, 50.0) and Entity2 (100.0, 60.0) then Entity2 will be presented on screen
It's default render mode for entities, but of course you can specify it.

### Scripting
Bin/Scripts/Internal contains all API that you need for scripting.

### Saving
You can save your game by using Saver.save(PathToMissionScript, Location)

To load from "Save" file you can just do Mission.switch("Scripts/Internal/Loader.lua", 1)

## Petrol: The Fastest

You can check out game made with this engine
[Petrol: The Fastest on itch.io](https://snowfall-eagle.itch.io/petrol-the-fastest)

![Screenshot](Project/Images/Screenshot2.png)
