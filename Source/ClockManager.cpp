/* ====== INCLUDES ====== */
#include "SDL.h"

#include "ClockManager.h"

/* ====== VARIABLES ====== */
ClockManager g_clockMgr;

/* ====== METHODS ====== */
b32 ClockManager::StartUp(s32 fps)
{
    m_startTime = SDL_GetTicks();
    m_msSyncDelay = (u32)(1000.0f / fps);

    return true;
}

void ClockManager::ShutDown()
{
}

f32 ClockManager::GetDelta()
{
    u32 curTime = SDL_GetTicks();
    f32 dtTime = (f32)(curTime - m_startTime);
    m_startTime = curTime;

    return dtTime;
}

void ClockManager::Sync() const
{
    while (SDL_GetTicks() - m_startTime < m_msSyncDelay)
        {}
}