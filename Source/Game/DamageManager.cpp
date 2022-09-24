/* ====== INCLUDES ====== */
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
    // DEBUG(sean)
    AddNote(PR_NOTE, "HandleAttack()");
}
