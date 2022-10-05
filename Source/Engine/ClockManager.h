#ifndef CLOCKMANAGER_H_
#define CLOCKMANAGER_H_

/* ====== INCLUDES ====== */
#include "Types.h"

/* ====== STRUCTURES ====== */
class ClockManager
{
    u32 m_startTime;
    f32 m_dtTime;
    u32 m_msSyncDelay;
public:
    b32 StartUp(s32 fps);
    void ShutDown();

    f32 ComputeDelta();
    f32 GetDelta() const { return m_dtTime; };
    void Sync() const;
};

extern ClockManager g_clockMgr;

#endif // CLOCKMANAGER_H_