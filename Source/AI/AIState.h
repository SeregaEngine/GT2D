#pragma once

#include "Game/Game.h"
#include "Script/ScriptModule.h"

class Actor;

class AIState
{
    static constexpr i32f AIState_STRSIZE = 32;

private:
    Actor* m_pActor;
    char m_functionName[AIState_STRSIZE];

public:
    AIState() : m_functionName("") {}

    void SetActor(Actor* pActor) { m_pActor = pActor; }
    void SetFunctionName(const char* functionName) { strncpy(m_functionName, functionName, AIState_STRSIZE); }
    const char* GetFunctionName() const { return m_functionName; }

    void Handle()
    {
        if (m_functionName[0])
        {
            g_scriptModule.CallState(g_game.GetScript(), m_functionName, m_pActor);
        }
    }
};
