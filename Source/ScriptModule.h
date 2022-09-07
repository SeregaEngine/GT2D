#ifndef SCRIPTMODULE_H_
#define SCRIPTMODULE_H_

extern "C"
{
#include "lua.h"
}

#include "EngineModule.h"

class ScriptModule : public EngineModule
{
    lua_State* L;
public:
    ScriptModule() : EngineModule("ScriptModule", CHANNEL_SCRIPT) {}
    virtual ~ScriptModule() {}

    b32 StartUp();
    void ShutDown();
private:
    void Lua_AddNote(s32 priority, const char* fmt, ...) const;
    b32 Lua_Check(s32 res);
};

extern ScriptModule g_scriptModule;

#endif // SCRIPTMODULE_H_