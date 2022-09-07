#ifndef SCRIPTMODULE_H_
#define SCRIPTMODULE_H_

#include "EngineModule.h"

class ScriptModule : public EngineModule
{
public:
    ScriptModule() : EngineModule("ScriptModule", CHANNEL_SCRIPT) {}
    virtual ~ScriptModule() {}

    b32 StartUp();
    void ShutDown();
};

extern ScriptModule g_scriptModule;

#endif // SCRIPTMODULE_H_