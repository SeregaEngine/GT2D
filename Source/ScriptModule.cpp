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
    L = luaL_newstate();
    luaL_openlibs(L);

    DefineFunctions();
    DefineSymbols();

    if ( CheckLua(luaL_dofile(L, "Scripts/Test.lua")) )
    {
    }

    AddNote(PR_NOTE, "Module started");

    return true;
}

void ScriptModule::ShutDown()
{
    lua_close(L);

    AddNote(PR_NOTE, "Module shut down");
}

b32 ScriptModule::CheckLua(s32 res)
{
    if (res != LUA_OK)
    {
        _AddNote(PR_WARNING, "Lua_Check(): %s", lua_tostring(L, -1));
        return false;
    }

    return true;
}

void ScriptModule::DefineFunctions()
{
    lua_register(L, "GT_LOG", _GT_LOG);
}

void ScriptModule::DefineSymbols()
{
    lua_pushinteger(L, PR_NOTE);
    lua_setglobal(L, "PR_NOTE");

    lua_pushinteger(L, PR_WARNING);
    lua_setglobal(L, "PR_WARNING");

    lua_pushinteger(L, PR_ERROR);
    lua_setglobal(L, "PR_ERROR");
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
