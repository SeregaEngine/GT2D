#include "Script/ScriptModule.h"
#include "Engine/Console.h"
#include "Game/PauseState.h"

b32 PauseState::OnEnter()
{
    m_bEntered = true; // Mark that we been in OnEnter() once
    m_pScript = g_scriptModule.EnterMission("Scripts/Pause.lua", 1);
    return m_pScript != nullptr;
}

void PauseState::OnExit()
{
    g_scriptModule.ExitMission(m_pScript);
}

void PauseState::Render()
{
    g_scriptModule.RenderMission(m_pScript);
    g_scriptModule.RenderMission(m_pPrevious);
    m_world.Render();
    if (g_console.IsShown())
    {
        g_console.Render();
    }
}
