#pragma once

#include "GTTask.h"
#include "Dialog.h"
#include "Game.h"

class WaitTalkingTask final : public GT_Task
{
    Dialog* m_pDialog;

public:
    WaitTalkingTask(Actor* pActor, Actor* pTarget) : GT_Task(pActor, GTT_WAIT_TALKING), m_pDialog(nullptr)
    {
        auto& lstEntity = g_game.GetWorld().GetEntityList();

        auto end = lstEntity.End();
        for (auto it = lstEntity.Begin(); it != end; ++it)
        {
            if (it->data->GetType() == ENTITY_TYPE_DIALOG &&
                static_cast<Dialog*>(it->data)->m_pAttached == pTarget &&
                static_cast<Dialog*>(it->data)->Running())
            {
                m_pDialog = (Dialog*)it->data;
                break;
            }
        }

        if (!m_pDialog)
        {
            m_status = GTT_DONE;
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

