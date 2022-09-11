#ifndef SCRIPTMODULE_H_
#define SCRIPTMODULE_H_

/* ====== INCLUDES ====== */
extern "C"
{
#include "lua.h"
}

#include "EngineModule.h"

/* ====== STRUCTURES ====== */
class ScriptModule final : public EngineModule
{
    lua_State* L;
public:
    ScriptModule() : EngineModule("ScriptModule", CHANNEL_SCRIPT) {}

    b32 StartUp();
    void ShutDown();
private:
    void DefineFunctions();
    void DefineSymbols();

    b32 CheckLua(s32 res);

    void _AddNote(s32 priority, const char* fmt, ...) const;
    static s32 _GT_LOG(lua_State* L);
};

extern ScriptModule g_scriptModule;

#endif // SCRIPTMODULE_H_