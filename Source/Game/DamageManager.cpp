/* ====== INCLUDES ====== */
#include "Actor.h"
#include "Weapon.h"
#include "CollisionManager.h"

#include "DamageManager.h"

/* ====== METHODS ====== */
b32 DamageManager::StartUp()
{
    AddNote(PR_NOTE, "Manager started");

    return true;
}

void DamageManager::ShutDown()
{
    AddNote(PR_NOTE, "Manager shut down");
}

void DamageManager::HandleAttack(const Actor* pAttacker)
{
    // Get attacker's weapon
    const Weapon* pWeapon = pAttacker->m_pWeapon;

    // Get point for the hit registration
    Vector2 vPoint = pAttacker->m_vPosition;
    vPoint.x += pAttacker->m_bLookRight ? pWeapon->GetHitBox().x2 : pWeapon->GetHitBox().x1;

    // Get collided actors with this hit
    TList<Entity*> lstActor;
    g_collisionMgr.CheckCollision(vPoint, pWeapon->GetHitBox(), [](auto pEntity, auto pActor) -> b32 {
        if (pEntity->GetType() == ENTITY_TYPE_ACTOR &&
            (static_cast<Actor*>(pActor)->m_actorTeam == ACTOR_TEAM_DEFAULT ||
             static_cast<Actor*>(pActor)->m_actorTeam != static_cast<Actor*>(pEntity)->m_actorTeam))
            return true;
        return false;
    }, (void*)pAttacker, lstActor, pAttacker);

    // Remove health from collided actors
    auto end = lstActor.End();
    for (auto it = lstActor.Begin(); it != end; ++it)
        static_cast<Actor*>(it->data)->AddHealth(-pWeapon->GetDamage());
}
