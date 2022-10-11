#ifndef AIMODULE_H_
#define AIMODULE_H_

/* ====== INCLUDES ====== */
#include "TList.h"
#include "GTTask.h"
#include "GTCommand.h"

/* ====== STRUCTURES ====== */
class Actor;

class AIModule final : public EngineModule
{
public:
    AIModule() : EngineModule("AIModule", CHANNEL_SCRIPT) {}

    b32 StartUp();
    void ShutDown();

    void HandleState(Actor* pActor);
};

extern AIModule g_AIModule;

#endif // AIMODULE_H_