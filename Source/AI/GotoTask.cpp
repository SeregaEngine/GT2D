#include "DebugLogManager.h"
#include "Actor.h"
#include "GTUnit.h"

#include "GotoTask.h"

// TODO(sean) count error by using Actor's speed
#define ERROR_X GTU::UnitToScreenX(2.0f)
#define ERROR_Y GTU::UnitToScreenY(1.0f)

void GotoTask::Handle()
{
    if (m_status != GTT_INPROCESS)
        return;

    Vector2 vPosition = m_pActor->GetPosition();

    if (!m_bCompletedX)
    {
        if (m_vDestination.x < vPosition.x - ERROR_X)
            m_pActor->SendCommand(GTC_MOVE_LEFT);
        else if (m_vDestination.x > vPosition.x + ERROR_X)
            m_pActor->SendCommand(GTC_MOVE_RIGHT);
        else
            m_bCompletedX = true;
    }

    if (!m_bCompletedY)
    {
        if (m_vDestination.y < vPosition.y - ERROR_Y)
            m_pActor->SendCommand(GTC_MOVE_UP);
        else if (m_vDestination.y > vPosition.y + ERROR_Y)
            m_pActor->SendCommand(GTC_MOVE_DOWN);
        else
            m_bCompletedY = true;
    }

    if (m_bCompletedX && m_bCompletedY)
        m_status = GTT_DONE;
}
