/* TODO
 */

/* ====== INCLUDES ====== */
#include "SoundModule.h"
#include "ScriptModule.h"
#include "Player.h"

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
    g_graphicsModule.UndefineTextures();
    g_animModule.UndefineAnimations();
    g_soundModule.HaltMusic();
    g_soundModule.UndefineResources();

    g_scriptModule.UnloadMission();

    m_world.ShutDown();
}

