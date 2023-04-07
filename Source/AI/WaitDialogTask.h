#pragma once

#include "AI/AITask.h"
#include "Game/Dialog.h"

class WaitDialogTask final : public AITask
{
    Dialog* m_pDialog;

public:
    WaitDialogTask(Actor* pActor, Dialog* pDialog) : AITask(pActor, AITASK_WAIT_DIALOG), m_pDialog(pDialog)
    {
        if (m_pDialog)
        {
            m_pDialog->Run();
        }
    }

    virtual void Handle() override
    {
        if (m_status != AITASK_INPROCESS)
        {
            return;
        }

        if (!g_game.GetWorld().HasEntity(m_pDialog))
        {
            m_status = AITASK_DONE;
        }
    }
};
