#ifndef SCRIPTMODULE_H_
#define SCRIPTMODULE_H_

/* ====== INCLUDES ====== */
extern "C"
{
#include "lua.h"
}

#include "EngineModule.h"

/* ====== STRUCTURES ====== */
class ScriptModule : public EngineModule
{
    lua_State* L;
public:
    ScriptModule() : L(nullptr), EngineModule("ScriptModule", CHANNEL_SCRIPT) {}
    virtual ~ScriptModule() {}

    b32 StartUp();
    void ShutDown();
private:
    void Lua_AddNote(s32 priority, const char* fmt, ...) const;
    b32 Lua_Check(s32 res);

    static s32 _GT_LOG(lua_State* L);
};

extern ScriptModule g_scriptModule;

#endif // SCRIPTMODULE_H_