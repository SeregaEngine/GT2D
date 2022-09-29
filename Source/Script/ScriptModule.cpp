/* ====== INCLUDES ====== */
extern "C"
{
#include "lauxlib.h"
#include "lualib.h"
}

#include "GraphicsModule.h"
#include "GTUnit.h"
#include "SoundModule.h"
#include "InputModule.h"
#include "Console.h"
#include "Game.h"
#include "Actor.h"
#include "GotoTask.h"
#include "GotoEntityTask.h"
#include "KillTask.h"
#include "Weapon.h"
#include "Trigger.h"
#include "Dialog.h"

#include "ScriptModule.h"

/* ====== VARIABLES ====== */
ScriptModule g_scriptModule;

/* ====== METHODS ====== */
b32 ScriptModule::StartUp()
{
    // Init lua
    m_pLoader = luaL_newstate();
    luaL_openlibs(m_pLoader);

    DefineFunctions(m_pLoader);
    DefineSymbols(m_pLoader);

    // Init loader script
    if (!CheckLua(m_pLoader, luaL_dofile(m_pLoader, "Scripts/Loader.lua")))
        return false;

    AddNote(PR_NOTE, "Module started");

    return true;
}

void ScriptModule::ShutDown()
{
    if (m_pMission)
    {
        lua_close(m_pMission);
        m_pMission = nullptr;
    }

    if (m_pLoader)
    {
        lua_close(m_pLoader);
        m_pLoader = nullptr;
    }

    AddNote(PR_NOTE, "Module shut down");
}

void ScriptModule::DefineFunctions(lua_State* L)
{
    /* Log */
    lua_register(L, "GT_LOG", _GT_LOG);

    /* Graphics */
    // Textures
    lua_register(L, "defineTexture", _defineTexture);

    // Draw
    lua_register(L, "setDrawColor", _setDrawColor);
    lua_register(L, "drawFrame", _drawFrame);
    lua_register(L, "fillRect", _fillRect);
    lua_register(L, "drawRect", _drawRect);

    // Camera
    lua_register(L, "attachCamera", _attachCamera);
    lua_register(L, "detachCamera", _detachCamera);
    lua_register(L, "setCameraPosition", _setCameraPosition);
    lua_register(L, "setCameraBounds", _setCameraBounds);

    /* Sound */
    lua_register(L, "defineSound", _defineSound);
    lua_register(L, "playSound", _playSound);

    /* Music */
    lua_register(L, "defineMusic", _defineMusic);
    lua_register(L, "playMusic", _playMusic);

    /* Input */
    lua_register(L, "isKeyDown", _isKeyDown);
    lua_register(L, "isMouseDown", _isMouseDown);
    lua_register(L, "getMousePosition", _getMousePosition);

    // Console
    lua_register(L, "isConsoleShown", _isConsoleShown);
    lua_register(L, "cls", _cls);

    /* AI */
    lua_register(L, "defineState", _defineState);

    /* Animation */
    lua_register(L, "defineAnimation", _defineAnimation);

    /* Game */
    lua_register(L, "stopGame", _stopGame);

    /* World */
    lua_register(L, "switchLocation", _switchLocation);
    lua_register(L, "setGroundBounds", _setGroundBounds);

    // Entities
    lua_register(L, "addEntity", _addEntity);
    lua_register(L, "updateEntity", _updateEntity);

    lua_register(L, "getEntityPosition", _getEntityPosition);
    lua_register(L, "getEntityHitBox", _getEntityHitBox);

    // Actor
    lua_register(L, "addActor", _addActor);
    lua_register(L, "setActorHealth", _setActorHealth);
    lua_register(L, "getActorHealth", _getActorHealth);
    lua_register(L, "toggleActorGodMode", _toggleActorGodMode);

    lua_register(L, "setActorState", _setActorState);
    lua_register(L, "setActorTask", _setActorTask);
    lua_register(L, "sendActorCmd", _sendActorCmd);
    lua_register(L, "checkActorTask", _checkActorTask);
    lua_register(L, "getActorCurrentTask", _getActorCurrentTask);
    lua_register(L, "setActorWeapon", _setActorWeapon);

    // Weapon
    lua_register(L, "defineWeapon", _defineWeapon);

    // Trigger
    lua_register(L, "addTrigger", _addTrigger);

    // Dialog
    lua_register(L, "addDialog", _addDialog);
}

void ScriptModule::DefineSymbols(lua_State* L)
{
    /* Log */
    lua_pushinteger(L, PR_NOTE);
    lua_setglobal(L, "PR_NOTE");
    lua_pushinteger(L, PR_WARNING);
    lua_setglobal(L, "PR_WARNING");
    lua_pushinteger(L, PR_ERROR);
    lua_setglobal(L, "PR_ERROR");

    /* Graphics */
    lua_pushinteger(L, UNIT_SCREEN_WIDTH);
    lua_setglobal(L, "SCREEN_WIDTH");
    lua_pushinteger(L, UNIT_SCREEN_HEIGHT);
    lua_setglobal(L, "SCREEN_HEIGHT");

    lua_pushinteger(L, RENDER_MODE_BACKGROUND);
    lua_setglobal(L, "RENDER_MODE_BACKGROUND");
    lua_pushinteger(L, RENDER_MODE_DYNAMIC);
    lua_setglobal(L, "RENDER_MODE_DYNAMIC");
    lua_pushinteger(L, RENDER_MODE_FOREGROUND);
    lua_setglobal(L, "RENDER_MODE_FOREGROUND");
    lua_pushinteger(L, RENDER_MODE_DEBUG);
    lua_setglobal(L, "RENDER_MODE_DEBUG");

    /* Input */
    // WASD/Arrows
    lua_pushinteger(L, SDLK_w);
    lua_setglobal(L, "GTK_W");
    lua_pushinteger(L, SDLK_a);
    lua_setglobal(L, "GTK_A");
    lua_pushinteger(L, SDLK_s);
    lua_setglobal(L, "GTK_S");
    lua_pushinteger(L, SDLK_d);
    lua_setglobal(L, "GTK_D");

    lua_pushinteger(L, SDLK_UP);
    lua_setglobal(L, "GTK_UP");
    lua_pushinteger(L, SDLK_LEFT);
    lua_setglobal(L, "GTK_LEFT");
    lua_pushinteger(L, SDLK_DOWN);
    lua_setglobal(L, "GTK_DOWN");
    lua_pushinteger(L, SDLK_RIGHT);
    lua_setglobal(L, "GTK_RIGHT");

    // Some special symbols
    lua_pushinteger(L, SDLK_ESCAPE);
    lua_setglobal(L, "GTK_ESCAPE");
    lua_pushinteger(L, SDLK_RETURN);
    lua_setglobal(L, "GTK_RETURN");
    lua_pushinteger(L, SDLK_SPACE);
    lua_setglobal(L, "GTK_SPACE");

    // Mouse
    lua_pushinteger(L, GTM_LEFT);
    lua_setglobal(L, "GTM_LEFT");
    lua_pushinteger(L, GTM_RIGHT);
    lua_setglobal(L, "GTM_RIGHT");
    lua_pushinteger(L, GTM_MIDDLE);
    lua_setglobal(L, "GTM_MIDDLE");

    /* AI */
    lua_pushinteger(L, GTC_MOVE_UP);
    lua_setglobal(L, "GTC_MOVE_UP");
    lua_pushinteger(L, GTC_MOVE_LEFT);
    lua_setglobal(L, "GTC_MOVE_LEFT");
    lua_pushinteger(L, GTC_MOVE_DOWN);
    lua_setglobal(L, "GTC_MOVE_DOWN");
    lua_pushinteger(L, GTC_MOVE_RIGHT);
    lua_setglobal(L, "GTC_MOVE_RIGHT");
    lua_pushinteger(L, GTC_ATTACK);
    lua_setglobal(L, "GTC_ATTACK");

    lua_pushinteger(L, GTT_NONE);
    lua_setglobal(L, "GTT_NONE");
    lua_pushinteger(L, GTT_INPROCESS);
    lua_setglobal(L, "GTT_INPROCESS");
    lua_pushinteger(L, GTT_IMPOSSIBLE);
    lua_setglobal(L, "GTT_IMPOSSIBLE");
    lua_pushinteger(L, GTT_DONE);
    lua_setglobal(L, "GTT_DONE");

    lua_pushinteger(L, GTT_GOTO);
    lua_setglobal(L, "GTT_GOTO");
    lua_pushinteger(L, GTT_GOTO_ENTITY);
    lua_setglobal(L, "GTT_GOTO_ENTITY");
    lua_pushinteger(L, GTT_KILL);
    lua_setglobal(L, "GTT_KILL");
}

b32 ScriptModule::LoadMission()
{
    // Get getMission()
    lua_getglobal(m_pLoader, "getMission");
    if (!lua_isfunction(m_pLoader, -1))
    {
        lua_pop(m_pLoader, 1); // Pop "getMission"
        return false;
    }

    // Call getMission()
    if (!CheckLua(m_pLoader, lua_pcall(m_pLoader, 0, 1, 0)))
        return false;

    // Check returned variable
    if (!lua_isstring(m_pLoader, -1))
    {
        lua_pop(m_pLoader, 1); // Pop "getMission"
        return false;
    }

    // Create mission lua state
    m_pMission = luaL_newstate();
    luaL_openlibs(m_pMission);

    // Define all engine stuff
    DefineFunctions(m_pMission);
    DefineSymbols(m_pMission);

    // Try to open script
    if (!CheckLua(m_pMission, luaL_dofile(m_pMission, lua_tostring(m_pLoader, -1))))
    {
        lua_pop(m_pLoader, 1); // Pop "getMission"
        return false;
    }

    // Pop "getMission"
    lua_pop(m_pLoader, 1);

    // Get onEnter()
    lua_getglobal(m_pMission, "onEnter");
    if (!lua_isfunction(m_pMission, -1))
    {
        lua_pop(m_pMission, 1); // Pop "onEnter"
        return false;
    }

    // Call onEnter()
    if (!CheckLua(m_pMission, lua_pcall(m_pMission, 0, 0, 0)))
        return false;

    return true;
}

void ScriptModule::UnloadMission()
{
    if (m_pMission)
    {
        lua_close(m_pMission);
        m_pMission = nullptr;
    }
}

void ScriptModule::UpdateMission(f32 dtTime)
{
    // Check if we have onUpdate() function
    lua_getglobal(m_pMission, "onUpdate");
    if (!lua_isfunction(m_pMission, -1))
    {
        AddNote(PR_ERROR, "UpdateMission(): There're no lua <onUpdate()> function");
        lua_pop(m_pMission, 1); // Pop "onUpdate"
        return;
    }

    // Call onUpdate()
    lua_pushnumber(m_pMission, dtTime);
    lua_pcall(m_pMission, 1, 0, 0);
}

void ScriptModule::RenderMission()
{
    CallFunction("onRender");
}

void ScriptModule::CallFunction(const char* functionName, void* userdata)
{
    // Check for null
    if (!functionName)
    {
        AddNote(PR_WARNING, "CallFunction() called with null functionName");
        return;
    }

    // Get function
    lua_getglobal(m_pMission, functionName);
    if (!lua_isfunction(m_pMission, -1))
    {
        lua_pop(m_pMission, 1);
        AddNote(PR_WARNING, "CallFunction(): there're no %s function", functionName);
        return;
    }

    // Call function
    lua_pushlightuserdata(m_pMission, userdata);
    lua_pcall(m_pMission, 1, 0, 0);
}

void ScriptModule::CallFunction(const char* functionName)
{
    // Check for null
    if (!functionName)
    {
        AddNote(PR_WARNING, "CallFunction() called with null functionName");
        return;
    }

    // Get function
    lua_getglobal(m_pMission, functionName);
    if (!lua_isfunction(m_pMission, -1))
    {
        lua_pop(m_pMission, 1);
        AddNote(PR_WARNING, "CallFunction(): there're no %s function", functionName);
        return;
    }

    // Call function
    lua_pcall(m_pMission, 0, 0, 0);
}

void ScriptModule::Interpret(const char* text)
{
    if (0 != luaL_dostring(m_pMission, text))
    {
        LuaNote(PR_WARNING, lua_tostring(m_pMission, -1));
        lua_pop(m_pMission, 1);
    }
}

void ScriptModule::LuaNote(s32 priority, const char* fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    g_debugLogMgr.VAddNote(CHANNEL_SCRIPT, priority, "Lua", fmt, vl);
    va_end(vl);
}

b32 ScriptModule::LuaExpect(lua_State* L, const char* funName, s32 expect)
{
    s32 given;
    if ((given = lua_gettop(L)) == expect)
    {
        return true;
    }
    else
    {
        LuaNote(PR_ERROR, "%s(): Expected %d arguments, but %d given", funName, expect, lua_gettop(L));
        return false;
    }
}

b32 ScriptModule::CheckLua(lua_State* L, s32 res)
{
    if (res != LUA_OK)
    {
        AddNote(PR_WARNING, "CheckLua(): %s", lua_tostring(L, -1));
        lua_pop(L, 1); // Pop error
        return false;
    }

    return true;
}

s32 ScriptModule::_GT_LOG(lua_State* L)
{
    if (!LuaExpect(L, "GT_LOG", 2))
        return -1;

    if (lua_isinteger(L, 1) && lua_isstring(L, 2))
        LuaNote((s32)lua_tointeger(L, 1), lua_tostring(L, 2));

    return 0;
}

s32 ScriptModule::_defineTexture(lua_State* L)
{
    if (!LuaExpect(L, "defineTexture", 3))
        return -1;

    lua_pushlightuserdata(L, (void*)g_graphicsModule.DefineTexture(lua_tostring(L, 1),
                                                                   (s32)lua_tointeger(L, 2),
                                                                   (s32)lua_tointeger(L, 3)));

    return 1;
}

s32 ScriptModule::_setDrawColor(lua_State* L)
{
    if (!LuaExpect(L, "setDrawColor", 4))
        return -1;

    g_graphicsModule.SetDrawColor((u8)lua_tointeger(L, 1), (u8)lua_tointeger(L, 2),
                                (u8)lua_tointeger(L, 3), (u8)lua_tointeger(L, 4));

    return 0;
}

s32 ScriptModule::_drawFrame(lua_State* L)
{
    i32f argsCount = lua_gettop(L);
    if (argsCount != 10 && argsCount != 12)
    {
        LuaNote(PR_ERROR, "drawFrame(): Expected 10 or 12 arguments but %d given", argsCount);
        return -1;
    }

    SDL_Rect dest = {
        (s32)GTU::UnitToScreenX((f32)lua_tonumber(L, 4)),
        (s32)GTU::UnitToScreenY((f32)lua_tonumber(L, 5)),
        (s32)GTU::UnitToScreenX((f32)lua_tonumber(L, 6)),
        (s32)GTU::UnitToScreenY((f32)lua_tonumber(L, 7))
    };
    if (argsCount == 10)
        g_graphicsModule.DrawFrame((s32)lua_tointeger(L, 1), (s32)lua_tointeger(L, 2), (b32)lua_toboolean(L, 3), dest, (const GT_Texture*)lua_touserdata(L, 8), (s32)lua_tointeger(L, 9), (s32)lua_tointeger(L, 10));
    else
        g_graphicsModule.DrawFrame((s32)lua_tointeger(L, 1), (s32)lua_tointeger(L, 2), (b32)lua_toboolean(L, 3), dest, (const GT_Texture*)lua_touserdata(L, 8), (s32)lua_tointeger(L, 9), (s32)lua_tointeger(L, 10), (f32)lua_tonumber(L, 11), (SDL_RendererFlip)lua_tointeger(L, 12));

    return 0;
}

s32 ScriptModule::_fillRect(lua_State* L)
{
    if (!LuaExpect(L, "fillRect", 7))
        return -1;

    SDL_Rect dest = {
        (s32)GTU::UnitToScreenX((f32)lua_tonumber(L, 4)),
        (s32)GTU::UnitToScreenY((f32)lua_tonumber(L, 5)),
        (s32)GTU::UnitToScreenX((f32)lua_tonumber(L, 6)),
        (s32)GTU::UnitToScreenY((f32)lua_tonumber(L, 7))
    };

    g_graphicsModule.FillRect((s32)lua_tointeger(L, 1), (s32)lua_tointeger(L, 2), (s32)lua_toboolean(L, 3), dest);

    return 0;
}

s32 ScriptModule::_drawRect(lua_State* L)
{
    if (!LuaExpect(L, "drawRect", 7))
        return -1;

    SDL_Rect dest = {
        (s32)GTU::UnitToScreenX((f32)lua_tonumber(L, 4)),
        (s32)GTU::UnitToScreenY((f32)lua_tonumber(L, 5)),
        (s32)GTU::UnitToScreenX((f32)lua_tonumber(L, 6)),
        (s32)GTU::UnitToScreenY((f32)lua_tonumber(L, 7))
    };

    g_graphicsModule.DrawRect((s32)lua_tointeger(L, 1), (s32)lua_tointeger(L, 2), (s32)lua_toboolean(L, 3), dest);
    return 0;
}

s32 ScriptModule::_attachCamera(lua_State* L)
{
    if (!LuaExpect(L, "attachCamera", 1))
        return -1;

    g_graphicsModule.GetCamera().Attach( (Entity*)lua_touserdata(L, 1) );

    return 0;
}

s32 ScriptModule::_detachCamera(lua_State* L)
{
    if (!LuaExpect(L, "detachCamera", 0))
        return -1;

    g_graphicsModule.GetCamera().Detach();

    return 0;
}

s32 ScriptModule::_setCameraPosition(lua_State* L)
{
    if (!LuaExpect(L, "setCameraPosition", 2))
        return -1;

    g_graphicsModule.GetCamera().SetPosition((s32)GTU::UnitToScreenX((f32)lua_tonumber(L, 1)),
                                             (s32)GTU::UnitToScreenY((f32)lua_tonumber(L, 2)));

    return 0;
}

s32 ScriptModule::_setCameraBounds(lua_State* L)
{
    if (!LuaExpect(L, "setCameraBounds", 4))
        return -1;

    SRect rect;
    rect.x1 = (s32)( GTU::UnitToScreenX((f32)lua_tonumber(L, 1)) );
    rect.y1 = (s32)( GTU::UnitToScreenY((f32)lua_tonumber(L, 2)) );
    rect.x2 = rect.x1 + (s32)( GTU::UnitToScreenX((f32)lua_tonumber(L, 3)) ) - 1;
    rect.y2 = rect.y1 + (s32)( GTU::UnitToScreenY((f32)lua_tonumber(L, 4)) ) - 1;

    g_graphicsModule.GetCamera().SetBounds(rect);

    return 0;
}

s32 ScriptModule::_switchLocation(lua_State* L)
{
    if (!LuaExpect(L, "switchLocation", 1))
        return -1;

    g_game.GetWorld().SwitchLocation(lua_tostring(L, 1));

    return 0;
}

s32 ScriptModule::_setGroundBounds(lua_State* L)
{
    if (!LuaExpect(L, "setGroundBounds", 4))
        return -1;

    SRect rect;
    rect.x1 = (s32)( GTU::UnitToScreenX((f32)lua_tonumber(L, 1)) );
    rect.y1 = (s32)( GTU::UnitToScreenY((f32)lua_tonumber(L, 2)) );
    rect.x2 = rect.x1 + (s32)( GTU::UnitToScreenX((f32)lua_tonumber(L, 3)) ) - 1;
    rect.y2 = rect.y1 + (s32)( GTU::UnitToScreenY((f32)lua_tonumber(L, 4)) ) - 1,

    g_game.GetWorld().SetGroundBounds(rect);

    return 0;
}

s32 ScriptModule::_defineSound(lua_State* L)
{
    if (!LuaExpect(L, "defineSound", 1))
        return -1;

    lua_pushlightuserdata(L, g_soundModule.DefineWAV(lua_tostring(L, 1)));

    return 1;
}

s32 ScriptModule::_playSound(lua_State* L)
{
    if (!LuaExpect(L, "playSound", 1))
        return -1;

    g_soundModule.PlaySound( (GT_Sound*)lua_touserdata(L, 1) );

    return 0;
}

s32 ScriptModule::_defineMusic(lua_State* L)
{
    if (!LuaExpect(L, "defineMusic", 1))
        return -1;

    lua_pushlightuserdata(L, g_soundModule.DefineMusic(lua_tostring(L, 1)));

    return 1;
}

s32 ScriptModule::_playMusic(lua_State* L)
{
    if (!LuaExpect(L, "playMusic", 1))
        return -1;

    g_soundModule.PlayMusic( (GT_Music*)lua_touserdata(L, 1) );

    return 0;
}

s32 ScriptModule::_isKeyDown(lua_State* L)
{
    if (!LuaExpect(L, "isKeyDown", 1))
        return -1;

    lua_pushboolean(L, g_inputModule.IsKeyDown((SDL_Keycode)lua_tointeger(L, 1)));

    return 1;
}

s32 ScriptModule::_isMouseDown(lua_State* L)
{
    if (!LuaExpect(L, "isMouseDown", 1))
        return -1;

    lua_pushboolean(L, g_inputModule.IsMouseDown((Uint32)lua_tointeger(L, 1)));

    return 1;
}

s32 ScriptModule::_getMousePosition(lua_State* L)
{
    if (!LuaExpect(L, "getMousePosition", 0))
        return -1;

    // Get mouse screen position
    s32 x, y;
    g_inputModule.GetMousePosition(x, y);

    // Return
    lua_pushinteger(L, (lua_Integer)( GTU::ScreenToUnitX((f32)x) ));
    lua_pushinteger(L, (lua_Integer)( GTU::ScreenToUnitY((f32)y) ));

    return 2;
}

s32 ScriptModule::_isConsoleShown(lua_State* L)
{
    lua_pushboolean(L, g_console.IsShown());

    return 1;
}

s32 ScriptModule::_cls(lua_State* L)
{
    g_console.Clear();

    return 0;
}

s32 ScriptModule::_defineState(lua_State* L)
{
    if (!LuaExpect(L, "defineState", 1))
        return -1;

    lua_pushlightuserdata(L, (void*)g_AIModule.DefineState(lua_tostring(L, 1)));

    return 1;
}

s32 ScriptModule::_defineAnimation(lua_State* L)
{
    if (!LuaExpect(L, "defineAnimation", 3))
        return -1;

    GT_Animation anim = { (s32)lua_tointeger(L, 1), (s32)lua_tointeger(L, 2), (f32)lua_tonumber(L, 3) };
    lua_pushlightuserdata(L, (void*)g_animModule.DefineAnimation(anim));

    return 1;
}

s32 ScriptModule::_stopGame(lua_State* L)
{
    if (!LuaExpect(L, "stopGame", 0))
        return -1;

    g_game.Stop();

    return 0;
}

s32 ScriptModule::_addEntity(lua_State* L)
{
    if (!LuaExpect(L, "addEntity", 5))
        return -1;

    // Init entity
    Entity* pEntity = new Entity();

    Vector2 vPosition = { GTU::UnitToScreenX((f32)lua_tonumber(L, 1)),
                          GTU::UnitToScreenY((f32)lua_tonumber(L, 2)) };
    s32 width  = (s32)( GTU::UnitToScreenX((f32)lua_tonumber(L, 3)) );
    s32 height = (s32)( GTU::UnitToScreenY((f32)lua_tonumber(L, 4)) );
    GT_Texture* pTexture = (GT_Texture*)lua_touserdata(L, 5);

    pEntity->Init(vPosition, width, height, pTexture);

    // Push him to the world
    g_game.GetWorld().PushEntity(pEntity);

    // Return pointer to lua
    lua_pushlightuserdata(L, pEntity);

    return 1;
}

s32 ScriptModule::_updateEntity(lua_State* L)
{
    if (!LuaExpect(L, "updateEntity", 2))
        return -1;

    Entity* pEntity = (Entity*)lua_touserdata(L, 1);
    if (pEntity)
    {
        pEntity->Update((f32)lua_tonumber(L, 2));
    }
    else
    {
        LuaNote(PR_WARNING, "updateEntity(): function called with null entity");
        return -1;
    }

    return 0;
}

s32 ScriptModule::_getEntityPosition(lua_State* L)
{
    if (!LuaExpect(L, "getEntityPosition", 1))
        return -1;

    Entity* pEntity = (Entity*)lua_touserdata(L, 1);
    if (!pEntity)
    {
        LuaNote(PR_WARNING, "getEntityPosition(): function called with null entity");
        return -1;
    }

    const Vector2& vPosition = pEntity->GetPosition();
    lua_pushnumber(L, GTU::ScreenToUnitX(vPosition.x));
    lua_pushnumber(L, GTU::ScreenToUnitY(vPosition.y));

    return 2;
}

s32 ScriptModule::_getEntityHitBox(lua_State* L)
{
    if (!LuaExpect(L, "getEntityHitBox", 1))
        return -1;

    Entity* pEntity = (Entity*)lua_touserdata(L, 1);
    if (!pEntity)
    {
        LuaNote(PR_WARNING, "getEntityHitBox(): function called with null entity");
        return -1;
    }

    const FRect& hitBox = pEntity->GetHitBox();
    lua_pushnumber(L, GTU::ScreenToUnitX(hitBox.x1));
    lua_pushnumber(L, GTU::ScreenToUnitY(hitBox.y1));
    lua_pushnumber(L, GTU::ScreenToUnitX(hitBox.x2));
    lua_pushnumber(L, GTU::ScreenToUnitY(hitBox.y2));

    return 4;
}

s32 ScriptModule::_addActor(lua_State* L)
{
    if (!LuaExpect(L, "addActor", 5))
        return -1;

    // Init actor
    Actor* pActor = new Actor();

    Vector2 vPosition = { GTU::UnitToScreenX((f32)lua_tonumber(L, 1)),
                          GTU::UnitToScreenY((f32)lua_tonumber(L, 2)) };
    s32 width  = (s32)( GTU::UnitToScreenX((f32)lua_tonumber(L, 3)) );
    s32 height = (s32)( GTU::UnitToScreenY((f32)lua_tonumber(L, 4)) );
    GT_Texture* pTexture = (GT_Texture*)lua_touserdata(L, 5);

    pActor->Init(vPosition, width, height, pTexture);

    // Push him to the world
    g_game.GetWorld().PushEntity(pActor);

    // Return pointer to lua
    lua_pushlightuserdata(L, pActor);

    return 1;
}

s32 ScriptModule::_setActorHealth(lua_State* L)
{
    if (!LuaExpect(L, "setActorHealth", 2))
        return -1;

    Actor* pActor = static_cast<Actor*>(lua_touserdata(L, 1));
    if (pActor)
    {
        pActor->SetHealth((f32)lua_tointeger(L, 2));
    }
    else
    {
        LuaNote(PR_WARNING, "setActorHealth() called with null actor");
        return -1;
    }

    return 0;
}

s32 ScriptModule::_getActorHealth(lua_State* L)
{
    if (!LuaExpect(L, "getActorHealth", 1))
        return -1;

    Actor* pActor = static_cast<Actor*>(lua_touserdata(L, 1));
    f32 health;

    if (pActor)
    {
        health = pActor->GetHealth();
    }
    else
    {
        health = 0;
        LuaNote(PR_WARNING, "getActorHealth() called with null actor");
        return -1;
    }

    lua_pushnumber(L, health);

    return 1;
}

s32 ScriptModule::_toggleActorGodMode(lua_State* L)
{
    if (!LuaExpect(L, "toggleActorGodMode", 2))
        return -1;

    Actor* pActor = static_cast<Actor*>(lua_touserdata(L, 1));
    if (pActor)
    {
        pActor->ToggleGodMode((b32)lua_toboolean(L, 2));
    }
    else
    {
        LuaNote(PR_WARNING, "toggleActorGodMode() called with null actor");
        return -1;
    }

    return 0;
}

s32 ScriptModule::_sendActorCmd(lua_State* L)
{
    if (lua_gettop(L) < 2)
    {
        LuaNote(PR_ERROR, "sendActorCmd(): expected at least 2 arguments but %d given", lua_gettop(L));
        return -1;
    }

    // Check for errors
    Actor* pActor = static_cast<Actor*>(lua_touserdata(L, 1));
    if (!pActor)
    {
        LuaNote(PR_WARNING, "sendActorCmd() called with null actor");
        return -1;
    }

    // Init command
    GT_Command cmd;
    cmd.cmd = (s32)lua_tointeger(L, 2);
    for (i32f i = 3; i <= lua_gettop(L); i++)
    {
        f32 arg = (f32)lua_tonumber(L, i);
        cmd.lstArgument.PushBack(arg);
    }

    // Send command
    pActor->SendCommand(cmd);

    return 0;
}

s32 ScriptModule::_setActorState(lua_State* L)
{
    if (!LuaExpect(L, "setActorState", 2))
        return -1;

    Actor* pActor = static_cast<Actor*>(lua_touserdata(L, 1));
    if (pActor)
    {
        pActor->SetState((GT_State*)lua_touserdata(L, 2));
    }
    else
    {
        LuaNote(PR_WARNING, "setActorState() called with null actor");
        return -1;
    }

    return 0;
}

s32 ScriptModule::_setActorTask(lua_State* L)
{
    if (lua_gettop(L) < 2)
    {
        LuaNote(PR_WARNING, "setActorTask(): expected at least 2 arguments but %d given", lua_gettop(L));
        return -1;
    }

    // Check for erros
    Actor* pActor = (Actor*)lua_touserdata(L, 1);
    if (!pActor)
    {
        LuaNote(PR_WARNING, "setActorTask() called with null actor");
        return -1;
    }

    // Set task
    switch (lua_tointeger(L, 2))
    {

    case GTT_NONE:
    {
        pActor->SetTask(nullptr);
    } break;

    case GTT_GOTO:
    {
        Vector2 vDestination = { GTU::UnitToScreenX((f32)lua_tonumber(L, 3)),
                                 GTU::UnitToScreenY((f32)lua_tonumber(L, 4))};
        pActor->SetTask(new GotoTask(pActor, vDestination));
    } break;

    case GTT_GOTO_ENTITY:
    {
        pActor->SetTask(new GotoEntityTask(pActor, (Entity*)lua_touserdata(L, 3)));
    } break;

    case GTT_KILL:
    {
        pActor->SetTask(new KillTask(pActor, (Actor*)lua_touserdata(L, 3)));
    } break;

    default:
    {
        LuaNote(PR_WARNING, "setActorTask(): undefined task given: %d", lua_tointeger(L, 2));
        return -1;
    } break;

    }

    return 0;
}

s32 ScriptModule::_checkActorTask(lua_State* L)
{
    if (!LuaExpect(L, "checkActorState", 1))
        return -1;

    Actor* pActor = static_cast<Actor*>(lua_touserdata(L, 1));
    if (pActor)
    {
        GT_Task* pTask = pActor->GetTask();
        if (pTask)
            lua_pushinteger(L, pTask->GetStatus());
        else
            lua_pushinteger(L, GTT_NONE);
    }
    else
    {
        LuaNote(PR_WARNING, "checkActorTask() called with null actor");
        return -1;
    }

    return 1;
}

s32 ScriptModule::_getActorCurrentTask(lua_State* L)
{
    if (!LuaExpect(L, "getActorCurrentTask", 1))
        return -1;

    Actor* pActor = static_cast<Actor*>(lua_touserdata(L, 1));
    if (pActor)
    {
        GT_Task* pTask = pActor->GetTask();
        if (pTask)
            lua_pushinteger(L, pTask->GetID());
        else
            lua_pushinteger(L, GTT_NONE);
    }
    else
    {
        LuaNote(PR_WARNING, "getActorCurrentTask() called with null actor");
        return -1;
    }

    return 1;
}

s32 ScriptModule::_setActorWeapon(lua_State* L)
{
    if (!LuaExpect(L, "setActorWeapon", 2))
        return -1;

    Actor* pActor = static_cast<Actor*>(lua_touserdata(L, 1));
    if (pActor)
    {
    pActor->SetWeapon((const Weapon*)lua_touserdata(L, 2));
    }
    else
    {
        LuaNote(PR_WARNING, "setActorWeapon() called with null actor");
        return -1;
    }

    return 0;
}

s32 ScriptModule::_defineWeapon(lua_State* L)
{
    if (lua_gettop(L) < 5)
    {
        LuaNote(PR_ERROR, "defineWeapon(): expected at least 5 arguments");
        return -1;
    }
    else if (lua_gettop(L) != 5 + lua_tointeger(L, 2))
    {
        LuaNote(PR_ERROR, "defineWeapon(): expected 5 required + soundCount arguments");
        return -1;
    }

    // Init weapon
    const GT_Animation* pAnim = (const GT_Animation*)lua_touserdata(L, 1);
    s32 soundCount = (s32)lua_tointeger(L, 2);

    FRect hitBox;
    hitBox.x1 = -GTU::UnitToScreenX((f32)lua_tonumber(L, 3));
    hitBox.y1 = -GTU::UnitToScreenY((f32)lua_tonumber(L, 4));
    hitBox.x2 = -hitBox.x1;
    hitBox.y2 = -hitBox.y1;

    f32 damage = (f32)lua_tonumber(L, 5);

    // Allocate weapon
    Weapon* pWeapon = new Weapon(pAnim, soundCount, hitBox, damage);

    // Init weapon's soundpack
    GT_Sound** aSounds = pWeapon->GetSoundPack().GetSounds();

    for (i32f i = 0; i < soundCount; ++i)
        aSounds[i] = (GT_Sound*)lua_touserdata(L, i + 6);

    // Push to the world
    g_game.GetWorld().PushWeapon(pWeapon);
    // Return to script
    lua_pushlightuserdata(L, (void*)pWeapon);

    return 1;
}

s32 ScriptModule::_addTrigger(lua_State* L)
{
    if (!LuaExpect(L, "addTrigger", 6))
        return -1;

    // Allocate trigger
    Trigger* pTrigger = new Trigger();

    // Init trigger
    Vector2 vPosition = { GTU::UnitToScreenX((f32)lua_tonumber(L, 1)),
                          GTU::UnitToScreenY((f32)lua_tonumber(L, 2)) };
    s32 width  = (s32)( GTU::UnitToScreenX((f32)lua_tonumber(L, 3)) );
    s32 height = (s32)( GTU::UnitToScreenY((f32)lua_tonumber(L, 4)) );

    pTrigger->Init(vPosition, width, height, nullptr);
    pTrigger->Attach((Entity*)lua_touserdata(L, 5));
    pTrigger->SetFunctionName(lua_tostring(L, 6));

    // Push entity to the world and lua
    g_game.GetWorld().PushEntity(pTrigger);
    lua_pushlightuserdata(L, (void*)pTrigger);

    return 1;
}

s32 ScriptModule::_addDialog(lua_State* L)
{
    if (!LuaExpect(L, "addDialog", 6))
        return -1;

    // Params
    s32 width = (s32)GTU::UnitToScreenX((f32)lua_tonumber(L, 1));
    s32 height = (s32)GTU::UnitToScreenX((f32)lua_tonumber(L, 2));
    const char* text = lua_tostring(L, 3);
    f32 time = (f32)lua_tonumber(L, 4) * 1000.0f;
    Actor* pActor = (Actor*)lua_touserdata(L, 5);
    const GT_Texture* pTexture = (const GT_Texture*)lua_touserdata(L, 6);

    // Allocate and init dialog
    Dialog* pDialog = new Dialog();
    pDialog->Init(Vector2(0.0f, 0.0f), width, height, pTexture);
    pDialog->Attach(pActor);
    pDialog->SetTime(time);
    pDialog->SetText(text);

    // Push dialog to world and lua
    g_game.GetWorld().PushEntity(pDialog);
    lua_pushlightuserdata(L, (void*)pDialog);

    return 1;
}
