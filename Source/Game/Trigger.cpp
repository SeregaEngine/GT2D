/* ====== INCLUDES ====== */
#include "CollisionManager.h"

#include "Trigger.h"

/* ====== METHODS ====== */
void Trigger::Init(const Vector2& vPosition, s32 width, s32 height, GT_Texture* pTexture)
{
    Entity::Init(vPosition, width, height, pTexture);

    memset(m_functionName, 0, TRIGGER_STRSIZE);
    m_pAttached = nullptr;
}

void Trigger::Update(f32 dtTime)
{
    if (m_pAttached)
    {
        // TODO(sean) Call collision manager, check collided list for our attached entity
    }
}
