# Lua defines and functions

## Defines
### Debug
- PR_NOTE
- PR_WARNING
- PR_ERROR

### Screen
- SCREEN_WIDTH
- SCREEN_HEIGHT

### Render mode
- RENDER_MODE_BACKGROUND
- RENDER_MODE_DYNAMIC
- RENDER_MODE_FOREGROUND
- RENDER_MODE_DEBUG

### Keys
- GTK_*
- GTK_UP/LEFT/DOWN/RIGHT
- GTK_ESCAPE/SPACE/RETURN
- GTM_LEFT/MIDDLE/RIGHT

### Actor commands
- GTC_MOVE_UP
- GTC_MOVE_LEFT
- GTC_MOVE_RIGHT
- GTC_MOVE_DOWN
- GTC_ATTACK

### Task status
- GTT_NONE
- GTT_INPROCESS
- GTT_DONE
- GTT_IMPOSSIBLE

### Tasks
- GTT_NONE
- GTT_GOTO
- GTT_GOTO_ENTITY
- GTT_KILL

## Functions
### Debug
- void GT_LOG(priority, string)

### Graphics
- defineTexture(FilePath, SpriteWidth, SpriteHeight) -> Texture ## Sprite size can be less than whole texture

- setDrawColor(r, g, b, a) ## 0-255
- drawFrame(RenderMode, ZIndex, IsHUD, x1,y1,x2,y2, Texture, AnimationRow, AnimationColumn) 
- fillRect(RenderMode, ZIndex, IsHUD, x1,y1,x2,y2) 
- drawRect(RenderMode, ZIndex, IsHUD, x1,y1,x2,y2) 

- attachCamera(Entity)
- detachCamera()
- setCameraPosition(x, y)
- setCameraBounds(x1, y1, x2, y2)

### Sound and Music
- defineSound(FilePath) -> Sound
- defineMusic(FilePath) -> Music
- playSound(Sound)
- playMusic(Music)

### Input
- isKeyDown(Key) -> Boolean
- isMouseDown(MouseButton) -> Boolean
- getMousePosition() -> X,Y

### Console
- isConsoleShown() -> Boolean
- cls() ## Clear console screen

### AI
- defineState(StringFunctionName) -> State

### Animation
- defineAnimation(AnimationRow, AnimationCount, FrameTime) -> Animation

### Game
- stopGame()

### World
- hostSwitchLocation(StringEnterFunctionName) ## Use switchLocation function instead
- setGroundBounds(x1, y1, x2, y2)
- hasWorldEntity(Entity) -> Boolean

### Entity
- addEntity(X, Y, Width, Height, Texture) -> Entity
- removeEntity(Entity)
- updateEntity(Entity, dt)

- getEntityPosition(Entity) -> X,Y
- getEntityHitBox(Entity) -> X1,Y1,X2,Y2 ## Relative to entity position

### Actor
- addActor(X, Y, Width, Height, Texture)
- setActorHealth(Actor, Health)
- getActorHealth(Actor) -> Health
- toggleActorGodMode(Actor, Boolean)
- turnActorLeft(Actor)
- turnActorRight(Actor)

- setActorState(Actor, State)
- setActorTask(Actor, Task)
- sendActorCmd(Actor, Command)
- checkActorTask(Actor) -> GTT_NONE, GTT_INPROCESS, GTT_DONE, GTT_IMPOSSIBLE
- getActorCurrentTask(Actor) -> Task
- setActorWeapon(Actor, Weapon)

### Weapon
- defineWeapon(Animation, SoundCount, RangeX, RangeY, Damage,  ...Sounds) -> Weapon ## ...Sounds variables count is SoundCount

### Trigger
- addTrigger(X, Y, Width, Height, AttachedEntity, StringFunctionName) -> Trigger ## Trigger will be removed on touch with AttachedEntity and StringFunctionName'll be called

### Dialog
- addDialog(Width, Height, Text, DurationInSeconds, AttachedActor, Texture) -> Dialog
- runDialog(Dialog)
