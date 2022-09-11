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
    lua_State* m_pLoader;
    lua_State* m_pMission;
public:
    ScriptModule() : EngineModule("ScriptModule", CHANNEL_SCRIPT) {}

    b32 StartUp();
    void ShutDown();

    b32 LoadMission();
    void UnloadMission();
private:
    void DefineFunctions(lua_State* L);
    void DefineSymbols(lua_State* L);

    b32 CheckLua(lua_State* L, s32 res);

    void _AddNote(s32 priority, const char* fmt, ...) const;
    static s32 _GT_LOG(lua_State* L);
};

extern ScriptModule g_scriptModule;

#endif // SCRIPTMODULE_H_