#include "Game/Entity.h"
#include "Game/Game.h"
#include "Graphics/Camera.h"

void Camera::Detach()
{
    s32 x, y;
    GetPosition(x, y);

    m_x = x;
    m_y = y;
    m_pAttached = nullptr;
}

void Camera::GetPosition(s32& x, s32& y)
{
    // Check if our entity was attached
    if (m_pAttached && !g_game.GetWorld().HasEntity(m_pAttached))
    {
        m_pAttached = nullptr;
    }

    if (m_pAttached)
    {
        const Vector2& vPosition = m_pAttached->m_vPosition;

        x = (s32)(vPosition.x + 0.5f) - g_graphicsModule.GetScreenWidth() / 2;
        if (x < m_bounds.x1)
        {
            x = m_bounds.x1;
        }
        else if (x + g_graphicsModule.GetScreenWidth() > m_bounds.x2 + 1)
        {
            x = (m_bounds.x2 + 1) - g_graphicsModule.GetScreenWidth();
        }

        y = (s32)(vPosition.y + 0.5f) - g_graphicsModule.GetScreenHeight() / 2;
        if (y < m_bounds.y1)
        {
            y = m_bounds.y1;
        }
        else if (y + g_graphicsModule.GetScreenHeight() > m_bounds.y2 + 1)
        {
            y = (m_bounds.y2 + 1) - g_graphicsModule.GetScreenHeight();
        }
    }
    else
    {
        x = m_x;
        y = m_y;
    }
}
