#include "Engine/ClockManager.h"

b32 ClockManager::StartUp(s32 fps)
{
    m_startTime = SDL_GetTicks();
    m_dtTime = 0.0f;
    m_msSyncDelay = (u32)(1000.0f / fps);

    return true;
}
