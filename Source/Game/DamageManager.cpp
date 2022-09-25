/* ====== INCLUDES ====== */
#include "Actor.h"
#include "Weapon.h"
#include "CollisionManager.h"

#include "DamageManager.h"

/* ====== VARIABLES ====== */
DamageManager g_damageMgr;

/* ====== METHODS ====== */
b32f DamageManager::StartUp()
{
    AddNote(PR_NOTE, "Manager started");

    return true;
}

void DamageManager::ShutDown()
{
    AddNote(PR_NOTE, "Manager shut down");
}

void DamageManager::HandleAttack(const AttackEvent& event)
{
    // Get attacker's weapon
    const Weapon* pWeapon = event.pAttacker->GetWeapon();

    // Get point for the hit registration
    Vector2 vPoint = event.pAttacker->GetPosition();
    vPoint.x += event.pAttacker->IsLookRight() ? pWeapon->GetHitBox().x2 : pWeapon->GetHitBox().x1;

    // Get collided actors with this hit
    TList<Entity*> lstActor;
    g_collisionMgr.CheckCollision(vPoint, pWeapon->GetHitBox(), [](auto pEntity, auto pAttacker) -> b32f {
        if (pEntity->GetType() == ENTITY_TYPE_ACTOR &&
            (static_cast<Actor*>(pAttacker)->GetTeam() == ACTOR_TEAM_DEFAULT ||
             static_cast<Actor*>(pAttacker)->GetTeam() != static_cast<Actor*>(pEntity)->GetTeam()))
            return true;
        return false;
    }, event.pAttacker, lstActor, event.pAttacker);

    // Remove health from collided actors
    auto end = lstActor.End();
    for (auto it = lstActor.Begin(); it != end; ++it)
    {
        static_cast<Actor*>(it->data)->SetHealth(
            static_cast<Actor*>(it->data)->GetHealth() - pWeapon->GetDamage());
        AddNote(PR_NOTE, "Here");
    }
}
