#include "Sound/SoundModule.h"
#include "Script/ScriptModule.h"
#include "Engine/Console.h"
#include "Game/PlayState.h"

b32 PlayState::OnEnter()
{
    m_bEntered = true; // Mark that we been in OnEnter() once

    m_world.StartUp();
    m_pScript = g_scriptModule.EnterMission(m_scriptPath, m_loadLocation);

    return m_pScript != nullptr;
}

void PlayState::OnExit()
{
    // Unload all resourses
    g_graphicsModule.UndefineTextures();
    g_animModule.UndefineAnimations();
    g_soundModule.UndefineResources();

    // Unload mission
    g_scriptModule.ExitMission(m_pScript);

    // Shut down world
    m_world.ShutDown();
}

void PlayState::Update(f32 dtTime)
{
    g_scriptModule.UpdateMission(m_pScript, dtTime);
    m_world.Update(dtTime);
}

void PlayState::Render()
{
    g_scriptModule.RenderMission(m_pScript);
    m_world.Render();
    if (g_console.IsShown())
    {
        g_console.Render();
    }
}
