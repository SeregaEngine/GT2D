#pragma once

#include "SDL.h"
#include "Engine/Types.h"

class ClockManager
{
    u32 m_startTime;
    f32 m_dtTime;
    u32 m_msSyncDelay;

public:
    b32 StartUp(s32 fps);
    void ShutDown() {}

    f32 ComputeDelta()
    {
        u32 curTime = SDL_GetTicks();
        m_dtTime = (f32)(curTime - m_startTime);
        m_startTime = curTime;

        return m_dtTime;
    }

    void Sync() const
    {
        while (SDL_GetTicks() - m_startTime < m_msSyncDelay)
            {}
    }

    f32 GetDelta() const { return m_dtTime; };
};

inline ClockManager g_clockMgr;
