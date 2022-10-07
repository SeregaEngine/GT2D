#ifndef RUNDIALOGTASK_H_
#define RUNDIALOGTASK_H_

/* ====== INCLUDES ====== */
#include "GTTask.h"
#include "Dialog.h"

/* ====== STRUCTURES ====== */
class RunDialogTask final : public GT_Task
{
    Dialog* m_pDialog;
public:
    RunDialogTask(Actor* pActor, Dialog* pDialog)
        : GT_Task(pActor, GTT_RUN_DIALOG), m_pDialog(pDialog)
        { if (m_pDialog) m_pDialog->Run(); m_status = GTT_DONE; }

    virtual void Handle() override {}
};

#endif RUNDIALOGTASK_H_