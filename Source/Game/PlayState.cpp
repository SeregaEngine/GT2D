/* TODO
 */

/* ====== INCLUDES ====== */
#include "SoundModule.h"
#include "ScriptModule.h"
#include "AIModule.h"
#include "Console.h"

#include "PlayState.h"

/* ====== METHODS ====== */
b32 PlayState::OnEnter()
{
    m_world.StartUp();
    g_scriptModule.LoadMission();

    return true;
}

void PlayState::OnExit()
{
    // Unload all resourses
    g_graphicsModule.UndefineTextures();
    g_animModule.UndefineAnimations();
    g_soundModule.UndefineResources();
    g_AIModule.UndefineStates();

    // Unload mission
    g_scriptModule.UnloadMission();

    // Shut down world
    m_world.ShutDown();
}

void PlayState::Update(f32 dtTime)
{
    g_scriptModule.UpdateMission(dtTime);
    m_world.Update(dtTime);
}

void PlayState::Render()
{
    m_world.Render();
    // TODO(sean) g_scriptModule.RenderMission();
    if (g_console.IsShown())
        g_console.Render();
}
