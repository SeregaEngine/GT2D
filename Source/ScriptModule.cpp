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
    AddNote(PR_NOTE, "Module started");

    L = luaL_newstate();
    luaL_openlibs(L);

    s32 res = luaL_dostring(L, "a = 7 + 11 + math.sin(0.5)");

    if (Lua_Check(res))
    {
        lua_getglobal(L, "a");
        if (lua_isnumber(L, -1))
        {
            f32 a = (f32)lua_tonumber(L, -1);
            Lua_AddNote(PR_NOTE, "7 + 11 = %f", a);
        }
    }

    return true;
}

void ScriptModule::ShutDown()
{
    lua_close(L);

    AddNote(PR_NOTE, "Module shut down");
}

void ScriptModule::Lua_AddNote(s32 priority, const char* fmt, ...) const
{
    va_list vl;
    va_start(vl, fmt);
    g_debugLogMgr.VAddNote(CHANNEL_SCRIPT, priority, "Lua", fmt, vl);
    va_end(vl);
}

b32 ScriptModule::Lua_Check(s32 res)
{
    if (res != LUA_OK)
    {
        Lua_AddNote(PR_WARNING, "Lua_Check(): %s", lua_tostring(L, -1));
        return false;
    }

    return true;
}