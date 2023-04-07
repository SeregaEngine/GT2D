#pragma once

#include "SDL.h"
#include "Engine/Types.h"

class ClockManager
{
    u32 m_startTime;
    f32 m_dtTime;
    u32 m_msSyncDelay;

public:
    void StartUp(s32 fps);
    void ShutDown() {}

    f32 ComputeDelta()
    {
        u32 curTime = SDL_GetTicks();
        m_dtTime = (f32)(curTime - m_startTime);
        m_startTime = curTime;

        return m_dtTime;
    }

    f32 GetDelta() const { return m_dtTime; };
};

inline ClockManager g_clockMgr;
