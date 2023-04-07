#pragma once

#include "AI/AITask.h"
#include "Game/Dialog.h"

class RunDialogTask final : public AITask
{
    Dialog* m_pDialog;

public:
    RunDialogTask(Actor* pActor, Dialog* pDialog) : AITask(pActor, AITASK_RUN_DIALOG), m_pDialog(pDialog)
    {
        if (m_pDialog)
        {
            m_pDialog->Run();
        }
        m_status = AITASK_DONE;
    }
};
