/* TODO
 */

/* ====== INCLUDES ====== */
#include "SoundModule.h"
#include "ScriptModule.h"

#include "PlayState.h"

/* ====== METHODS ====== */
b32 PlayState::OnEnter()
{
    // Start up world
    m_world.StartUp();

    // Load mission from lua
    g_scriptModule.LoadMission();

    return true;
}

void PlayState::OnExit()
{
    // Unload all resourses
    g_graphicsModule.UndefineTextures();
    g_animModule.UndefineAnimations();
    g_soundModule.HaltMusic();
    g_soundModule.UndefineResources();

    // Unload mission
    g_scriptModule.UnloadMission();

    // Shut down world
    m_world.ShutDown();
}

void PlayState::Update(f32 dtTime)
{
    // Update world
    m_world.Update(dtTime);

    // Update mission
    g_scriptModule.UpdateMission(dtTime);
}
