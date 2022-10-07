#ifndef FADEOFFTASK_H_
#define FADEOFFTASK_H_

/* ====== INCLUDES ====== */
#include "GTTask.h"
#include "GraphicsModule.h"
#include "ClockManager.h"

/* ====== STRUCTURES ====== */
class FadeOffTask final : public GT_Task
{
    f32 m_alpha;
    f32 m_alphaPerMs;
    SDL_Rect m_destRect;
public:
    FadeOffTask(Actor* pActor, f32 duration) :
        GT_Task(pActor, GTT_FADE_IN), m_alpha(0.0f), m_alphaPerMs(255.0f/duration),
        m_destRect({ 0, 0, g_graphicsModule.GetScreenWidth(), g_graphicsModule.GetScreenHeight() }) {}

    virtual void Handle() override
    {
        if (m_status != GTT_INPROCESS)
            return;

        if (m_alpha > 255.0f)
        {
            m_alpha = 255.0f;
            m_status = GTT_DONE;
        }

        g_graphicsModule.SetDrawColor(0, 0, 0, (Uint8)m_alpha);
        g_graphicsModule.FillRect(RENDER_MODE_FOREGROUND, 999, true, m_destRect);
        m_alpha += m_alphaPerMs * g_clockMgr.GetDelta();
    }
};

#endif // FADEOFFTASK_H_