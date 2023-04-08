#include "Engine/ClockManager.h"

void ClockManager::StartUp(s32 fps)
{
    m_startTime = SDL_GetTicks();
    m_dtTime = 0.0f;
}
