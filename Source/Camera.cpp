#include "Entity.h"

#include "Camera.h"

void Camera::GetPosition(s32& x, s32& y) const
{
    if (m_pAttached)
    {
        Vec2 vPosition = m_pAttached->GetPosition();

        x = (s32)vPosition.x - g_graphicsModule.GetScreenWidth() / 2;
        if (x < m_boundary.x1)
            x = m_boundary.x1;
        else if (x > m_boundary.x2)
            x = (m_boundary.x2 + 1) - g_graphicsModule.GetScreenWidth();

        y = (s32)vPosition.y - g_graphicsModule.GetScreenHeight() / 2;
        if (y < m_boundary.y1)
            y = m_boundary.y1;
        else if (y > m_boundary.y2)
            y = (m_boundary.y2 + 1) - g_graphicsModule.GetScreenHeight();
    }
    else
    {
        x = m_x;
        y = m_y;
    }
}