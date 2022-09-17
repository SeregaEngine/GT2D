#ifndef AIMODULE_H_
#define AIMODULE_H_

/* ====== INCLUDES ====== */
#include "TList.h"
#include "GTTask.h"
#include "GTCommand.h"

/* ====== STRUCTURES ====== */

// States handle which tasks to do
struct GT_State;

/* === AI MODULE === */
class Actor;

class AIModule
{
    GT_State* m_aStates;
    s32 m_usedStates;
public:
    b32 StartUp();
    void ShutDown();

    const GT_State* DefineState(const char* functionName);
    void UndefineStates() { m_usedStates = 0; }

    void HandleState(Actor* pActor);

private:
    void AddNote(s32 priority, const char* fmt, ...);
};

extern AIModule g_AIModule;

#endif // AIMODULE_H_