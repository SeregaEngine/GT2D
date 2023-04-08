#pragma once

#include "SDL.h"
#include "Engine/Types.h"
#include "Engine/Platform.h"

class ClockManager
{
private:
    static constexpr f32 MAX_DELTA_TIME = 25.0f;

private:
    u32 m_startTime;
    f32 m_dtTime;

public:
    void StartUp(s32 fps);
    void ShutDown() {}

    forceinline f32 ComputeDelta()
    {
        u32 curTime = SDL_GetTicks();
        m_dtTime = (f32)(curTime - m_startTime);
        m_startTime = curTime;

        if (m_dtTime > MAX_DELTA_TIME)
        {
            m_dtTime = MAX_DELTA_TIME;
        }

        return m_dtTime;
    }

    forceinline f32 GetDelta() const { return m_dtTime; };
};

inline ClockManager g_clockMgr;
