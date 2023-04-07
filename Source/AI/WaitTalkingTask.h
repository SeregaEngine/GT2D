#pragma once

#include "AI/AITask.h"
#include "Game/Dialog.h"
#include "Game/Game.h"

class WaitTalkingTask final : public AITask
{
    Dialog* m_pDialog;

public:
    WaitTalkingTask(Actor* pActor, Actor* pTarget) : AITask(pActor, AITASK_WAIT_TALKING), m_pDialog(nullptr)
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
            m_status = AITASK_DONE;
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

