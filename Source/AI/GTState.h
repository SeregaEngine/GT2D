#ifndef GTSTATE_H_
#define GTSTATE_H_

/* ====== INCLUDES ====== */
#include "Game.h"
#include "ScriptModule.h"

/* ====== DEFINES ====== */
#define GT_STATE_STRSIZE 32

/* ====== STRUCTURES ====== */
class Actor;

class GT_State
{
    Actor* m_pActor;
    char m_functionName[GT_STATE_STRSIZE];
public:
    GT_State() : m_functionName("") {}

    void SetActor(Actor* pActor) { m_pActor = pActor; }
    void SetFunctionName(const char* functionName) { strncpy(m_functionName, functionName, GT_STATE_STRSIZE); }
    const char* GetFunctionName() const { return m_functionName; }

    void Handle() { if (m_functionName[0]) g_scriptModule.CallState(g_game.GetScript(), m_functionName, m_pActor); }
};

#endif // GTSTATE_H_
