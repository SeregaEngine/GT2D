/* ====== INCLUDES ====== */
extern "C"
{
#include "lauxlib.h"
#include "lualib.h"
}

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

b32 ScriptModule::CheckLua(lua_State* L, s32 res)
{
    if (res != LUA_OK)
    {
        _AddNote(PR_WARNING, "Lua_Check(): %s", lua_tostring(L, -1));
        lua_pop(L, 1);
        return false;
    }

    return true;
}

void ScriptModule::DefineFunctions(lua_State* L)
{
    lua_register(L, "GT_LOG", _GT_LOG);
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

void ScriptModule::_AddNote(s32 priority, const char* fmt, ...) const
{
    va_list vl;
    va_start(vl, fmt);
    g_debugLogMgr.VAddNote(CHANNEL_SCRIPT, priority, "Lua", fmt, vl);
    va_end(vl);
}

s32 ScriptModule::_GT_LOG(lua_State* L)
{
    if (lua_gettop(L) == 2)
        if (lua_isinteger(L, 1) && lua_isstring(L, 2))
            g_scriptModule._AddNote((s32)lua_tointeger(L, 1), lua_tostring(L, 2));

    return 0;
}
