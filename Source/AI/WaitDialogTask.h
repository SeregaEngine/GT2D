#pragma once

#include "AI/GTTask.h"
#include "Game/Dialog.h"

class WaitDialogTask final : public GT_Task
{
    Dialog* m_pDialog;

public:
    WaitDialogTask(Actor* pActor, Dialog* pDialog) : GT_Task(pActor, GTT_WAIT_DIALOG), m_pDialog(pDialog)
    {
        if (m_pDialog)
        {
            m_pDialog->Run();
        }
    }

    virtual void Handle() override
    {
        if (m_status != GTT_INPROCESS)
        {
            return;
        }

        if (!g_game.GetWorld().HasEntity(m_pDialog))
        {
            m_status = GTT_DONE;
        }
    }
};
