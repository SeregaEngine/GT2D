#include "DebugLogManager.h"
#include "Actor.h"

#include "GotoTask.h"

void GotoTask::Handle()
{
    if (m_status != GTT_INPROCESS)
        return;

    Vector2 vPosition = m_pActor->GetPosition();

    if (m_vDestination.x < vPosition.x)
        m_pActor->SendCommand(GTC_MOVE_LEFT);
    else if (m_vDestination.x > vPosition.x)
        m_pActor->SendCommand(GTC_MOVE_RIGHT);

    if (m_vDestination.y < vPosition.y)
        m_pActor->SendCommand(GTC_MOVE_UP);
    else if (m_vDestination.y > vPosition.y)
        m_pActor->SendCommand(GTC_MOVE_DOWN);
}
