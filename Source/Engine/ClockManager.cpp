/* ====== INCLUDES ====== */
#include "SDL.h"

#include "ClockManager.h"

/* ====== VARIABLES ====== */
ClockManager g_clockMgr;

/* ====== METHODS ====== */
b32 ClockManager::StartUp(s32 fps)
{
    m_startTime = SDL_GetTicks();
    m_dtTime = 0.0f;
    m_msSyncDelay = (u32)(1000.0f / fps);

    return true;
}

void ClockManager::ShutDown()
{
}

f32 ClockManager::ComputeDelta()
{
    u32 curTime = SDL_GetTicks();
    m_dtTime = (f32)(curTime - m_startTime);
    m_startTime = curTime;

    return m_dtTime;
}

void ClockManager::Sync() const
{
    while (SDL_GetTicks() - m_startTime < m_msSyncDelay)
        {}
}