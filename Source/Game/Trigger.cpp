/* ====== INCLUDES ====== */
#include "CollisionManager.h"
#include "ScriptModule.h"
#include "TList.h"

#include "Trigger.h"

/* ====== METHODS ====== */
void Trigger::Init(const Vector2& vPosition, s32 width, s32 height, GT_Texture* pTexture)
{
    Entity::Init(vPosition, width, height, pTexture);
    m_bCollidable = false;

    memset(m_functionName, 0, TRIGGER_STRSIZE);
    m_pAttached = nullptr;
}

void Trigger::Update(f32 dtTime)
{
    if (!m_pAttached)
        return;

    // Get collided with trigger entities
    TList<Entity*> lstEntity;
    g_collisionMgr.GetCollidedEntities(m_pAttached->GetPosition(), m_pAttached->GetHitBox(), lstEntity);

    // Try to find our Attached entity
    auto end = lstEntity.End();
    for (auto it = lstEntity.Begin(); it != end; ++it)
    {
        if (it->data == m_pAttached)
        {
            g_scriptModule.CallFunction(m_functionName, m_pAttached);
            break;
        }
    }

    // Ask to remove this trigger
    // TODO(sean) Use remove list or remove here?..
}
