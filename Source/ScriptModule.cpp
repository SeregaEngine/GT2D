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
#include "Game.h"
#include "PlayState.h"

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

    /* World */
    lua_register(L, "setBackground", _setBackground);
    lua_register(L, "setParallax", _setParallax);
    lua_register(L, "addPlayer", _addPlayer);
}

void ScriptModule::DefineSymbols(lua_State* L)
{
    lua_pushinteger(L, PR_NOTE);
    lua_setglobal(L, "PR_NOTE");

    lua_pushinteger(L, PR_WARNING);
    lua_setglobal(L, "PR_WARNING");

    lua_pushinteger(L, PR_ERROR);
    lua_setglobal(L, "PR_ERROR");
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
    if (!LuaExpect(L, "playSound", 1))
        return -1;

    g_soundModule.PlayMusic( (GT_Music*)lua_touserdata(L, 1) );

    return 0;
}

s32 ScriptModule::_addPlayer(lua_State* L)
{
    if (!LuaExpect(L, "addPlayer", 5))
        return -1;

    // Init player
    Player* pPlayer = new Player();

    Vec2 vPosition = { (f32)lua_tonumber(L, 1) * g_unitX, (f32)lua_tonumber(L, 2) * g_unitY };
    s32 width  = (s32)( (f32)lua_tonumber(L, 3) * g_unitX );
    s32 height = (s32)( (f32)lua_tonumber(L, 4) * g_unitY );
    GT_Texture* pTexture = (GT_Texture*)lua_touserdata(L, 5);

    pPlayer->Init(vPosition, width, height, pTexture);

    // Push him to the world
    g_game.GetWorld().AddPlayer(pPlayer);

    // Return pointer to lua
    lua_pushlightuserdata(L, pPlayer);

    return 1;
}

