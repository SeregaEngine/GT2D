#include "Engine/CollisionManager.h"
#include "Script/ScriptModule.h"
#include "Containers/List.h"
#include "Game/Game.h"
#include "Game/Trigger.h"

void Trigger::Init(const Vector2& vPosition, s32 width, s32 height, const GT_Texture* pTexture)
{
    Entity::Init(vPosition, width, height, pTexture);
    m_type = ENTITY_TYPE_TRIGGER;
    m_bCollidable = false;

    memset(m_functionName, 0, TRIGGER_STRSIZE);
    m_pAttached = nullptr;
}

void Trigger::Update(f32 dtTime)
{
    if (!m_pAttached)
    {
        return;
    }

    // Get collided with trigger entities
    TList<Entity*> lstEntity;
    g_collisionMgr.CheckCollision(
        m_vPosition,
        m_hitBox,
        [] (auto pEntity, auto pAttached) -> b32 { return pEntity == pAttached; },
        m_pAttached,
        lstEntity,
        this
    );

    if (!lstEntity.IsEmpty())
    {
        // Call trigger's function and remove
        g_scriptModule.CallTrigger(g_game.GetScript(), m_functionName, this, m_pAttached);
        g_game.GetWorld().RemoveEntity(this);
    }
}
