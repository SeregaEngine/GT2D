#pragma once

#include "Game/Game.h"
#include "Script/ScriptModule.h"

class Actor;

class AIState
{
    static constexpr i32f AISTATE_STRSIZE = 32;

private:
    Actor* m_pActor;
    char m_functionName[AISTATE_STRSIZE];

public:
    AIState() : m_functionName("") {}

    forceinline void SetActor(Actor* pActor) { m_pActor = pActor; }
    forceinline void SetFunctionName(const char* functionName) { std::strncpy(m_functionName, functionName, AISTATE_STRSIZE); }
    forceinline const char* GetFunctionName() const { return m_functionName; }

    void Handle()
    {
        if (m_functionName[0])
        {
            g_scriptModule.CallState(g_game.GetScript(), m_functionName, m_pActor);
        }
    }
};
