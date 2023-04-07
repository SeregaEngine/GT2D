#pragma once

#include "AI/GTTask.h"
#include "Game/Dialog.h"

class RunDialogTask final : public GT_Task
{
    Dialog* m_pDialog;

public:
    RunDialogTask(Actor* pActor, Dialog* pDialog) : GT_Task(pActor, GTT_RUN_DIALOG), m_pDialog(pDialog)
    {
        if (m_pDialog)
        {
            m_pDialog->Run();
        }
        m_status = GTT_DONE;
    }
};
