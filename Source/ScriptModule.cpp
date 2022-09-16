/* TODO
 * - More stringent check of lua arguments
 */

/* ====== INCLUDES ====== */
extern "C"
{
#include "lauxlib.h"
#include "lualib.h"
}

#include "GraphicsModule.h"
#include "SoundModule.h"
#include "InputModule.h"
#include "Game.h"
#include "Actor.h"

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

    // Camera
    lua_register(L, "attachCamera", _attachCamera);
    lua_register(L, "detachCamera", _detachCamera);
    lua_register(L, "setCameraPos", _setCameraPos);
    lua_register(L, "setLevelSize", _setLevelSize);

    /* Sound */
    lua_register(L, "defineSound", _defineSound);
    lua_register(L, "playSound", _playSound);

    /* Music */
    lua_register(L, "defineMusic", _defineMusic);
    lua_register(L, "playMusic", _playMusic);

    /* Input */
    lua_register(L, "isKeyDown", _isKeyDown);
    lua_register(L, "isMouseDown", _isMouseDown);
    lua_register(L, "getMousePos", _getMousePos);

    /* Game */
    lua_register(L, "stopGame", _stopGame);

    /* World */
    // Background stuff
    lua_register(L, "setBackground", _setBackground);
    lua_register(L, "setParallax", _setParallax);

    // Entities
    lua_register(L, "addEntity", _addEntity);
    lua_register(L, "updateEntity", _updateEntity);

    // Actor
    lua_register(L, "addActor", _addActor);
    lua_register(L, "sendActorCmd", _sendActorCmd);
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

    lua_pushinteger(L, TW_LOCATION);
    lua_setglobal(L, "TW_LOCATION");
    lua_pushinteger(L, TH_LOCATION);
    lua_setglobal(L, "TH_LOCATION");

    lua_pushinteger(L, TW_PARALLAX);
    lua_setglobal(L, "TW_PARALLAX");
    lua_pushinteger(L, TH_PARALLAX);
    lua_setglobal(L, "TH_PARALLAX");

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
}

b32 ScriptModule::LoadMission()
{
    // Get getMission()
    lua_getglobal(m_pLoader, "getMission");
    if (!lua_isfunction(m_pLoader, -1))
    {
        lua_pop(m_pLoader, 1);
        return false;
    }

    // Call getMission()
    if (!CheckLua(m_pLoader, lua_pcall(m_pLoader, 0, 1, 0)))
        return false;

    // Check returned variable
    if (!lua_isstring(m_pLoader, -1))
    {
        lua_pop(m_pLoader, 1);
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
        lua_pop(m_pLoader, 1);
        return false;
    }

    // Clean loader's stack
    lua_pop(m_pLoader, 1);

    // Get onEnter()
    lua_getglobal(m_pMission, "onEnter");
    if (!lua_isfunction(m_pMission, -1))
    {
        lua_pop(m_pMission, 1);
        return false;
    }

    // Call onEnter()
    if (!CheckLua(m_pMission, lua_pcall(m_pMission, 0, 0, 0)))
    {
        lua_pop(m_pMission, 1);
        return false;
    }

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
        return;
    }

    // Call onUpdate()
    lua_pushnumber(m_pMission, dtTime);
    lua_pcall(m_pMission, 1, 0, 0);
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
        lua_pop(L, 1);
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

    lua_pushlightuserdata(L, g_graphicsModule.DefineTexture(lua_tostring(L, 1),
                                                            (s32)lua_tointeger(L, 2),
                                                            (s32)lua_tointeger(L, 3)));

    return 1;
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

s32 ScriptModule::_setCameraPos(lua_State* L)
{
    if (!LuaExpect(L, "setCameraPos", 2))
        return -1;

    s32 x = (s32)( (f32)lua_tonumber(L, 1) * g_unitX );
    s32 y = (s32)( (f32)lua_tonumber(L, 2) * g_unitY );

    g_graphicsModule.GetCamera().SetPosition(x, y);

    return 0;
}

s32 ScriptModule::_setLevelSize(lua_State* L)
{
    if (!LuaExpect(L, "setLevelSize", 2))
        return -1;

    SRect rect = {
        0, // x1
        0, // y1
        (s32)( (f32)lua_tonumber(L, 1) * g_unitX ) - 1, // x2
        (s32)( (f32)lua_tonumber(L, 2) * g_unitY ) - 1, // y2
    };

    g_graphicsModule.GetCamera().SetBoundary(rect);

    return 0;
}

s32 ScriptModule::_setBackground(lua_State* L)
{
    if (!LuaExpect(L, "setBackground", 1))
        return -1;

    g_game.GetWorld().SetBackground( (GT_Texture*)lua_touserdata(L, 1) );

    return 0;
}

s32 ScriptModule::_setParallax(lua_State* L)
{
    if (!LuaExpect(L, "setParallax", 1))
        return -1;

    g_game.GetWorld().SetParallax( (GT_Texture*)lua_touserdata(L, 1) );

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

s32 ScriptModule::_getMousePos(lua_State* L)
{
    if (!LuaExpect(L, "getMousePos", 0))
        return -1;

    // Get mouse position
    s32 x, y;
    g_inputModule.GetMousePos(x, y);

    // Return it
    lua_pushinteger(L, x);
    lua_pushinteger(L, y);

    return 2;
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

    Vector2 vPosition = { (f32)lua_tonumber(L, 1) * g_unitX, (f32)lua_tonumber(L, 2) * g_unitY };
    s32 width  = (s32)( (f32)lua_tonumber(L, 3) * g_unitX );
    s32 height = (s32)( (f32)lua_tonumber(L, 4) * g_unitY );
    GT_Texture* pTexture = (GT_Texture*)lua_touserdata(L, 5);

    pEntity->Init(vPosition, width, height, pTexture);

    // Push him to the world
    g_game.GetWorld().AddEntity(pEntity);

    // Return pointer to lua
    lua_pushlightuserdata(L, pEntity);

    return 1;
}

s32 ScriptModule::_updateEntity(lua_State* L)
{
    if (!LuaExpect(L, "updateEntity", 2))
        return -1;

    static_cast<Entity*>(lua_touserdata(L, 1))->Update((f32)lua_tonumber(L, 2));

    return 0;
}

s32 ScriptModule::_addActor(lua_State* L)
{
    if (!LuaExpect(L, "addActor", 5))
        return -1;

    // Init actor
    Actor* pActor = new Actor();

    Vector2 vPosition = { (f32)lua_tonumber(L, 1) * g_unitX, (f32)lua_tonumber(L, 2) * g_unitY };
    s32 width  = (s32)( (f32)lua_tonumber(L, 3) * g_unitX );
    s32 height = (s32)( (f32)lua_tonumber(L, 4) * g_unitY );
    GT_Texture* pTexture = (GT_Texture*)lua_touserdata(L, 5);

    pActor->Init(vPosition, width, height, pTexture);

    // Push him to the world
    g_game.GetWorld().AddEntity(pActor);

    // Return pointer to lua
    lua_pushlightuserdata(L, pActor);

    return 1;
}

s32 ScriptModule::_sendActorCmd(lua_State* L)
{
    if (lua_gettop(L) < 2)
    {
        LuaNote(PR_ERROR, "sendActorCmd: expected at least 2 arguments but %d given", lua_gettop(L));
        return -1;
    }

    // Init command
    GT_Command cmd;
    cmd.cmd = (u32)lua_tointeger(L, 2);
    for (s32 i = 3; i <= lua_gettop(L); i++)
    {
        f32 arg = (f32)lua_tonumber(L, i);
        cmd.lstArgument.PushBack(arg);
    }

    // Send command
    static_cast<Actor*>(lua_touserdata(L, 1))->SendCommand(cmd);

    return 0;
}
