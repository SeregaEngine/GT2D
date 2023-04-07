#pragma once

#include "AI/AITask.h"
#include "Graphics/GraphicsModule.h"
#include "Engine/ClockManager.h"

class FadeOffTask final : public AITask
{
    f32 m_alpha;
    f32 m_alphaPerMs;
    SDL_Rect m_destRect;

public:
    FadeOffTask(Actor* pActor, f32 duration) :
        AITask(pActor, AITASK_FADE_OFF), m_alpha(0.0f), m_alphaPerMs(255.0f/duration),
        m_destRect({ 0, 0, g_graphicsModule.GetScreenWidth(), g_graphicsModule.GetScreenHeight() }) {}

    virtual void Handle() override
    {
        if (m_status != AITASK_INPROCESS)
        {
            return;
        }

        if (m_alpha > 255.0f)
        {
            m_alpha = 255.0f;
            m_status = AITASK_DONE;
        }

        g_graphicsModule.SetDrawColor(0, 0, 0, (Uint8)m_alpha);
        g_graphicsModule.FillRect(RENDER_MODE_FOREGROUND, 500, true, m_destRect);
        m_alpha += m_alphaPerMs * g_clockMgr.GetDelta();
    }
};
