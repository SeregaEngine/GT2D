#ifndef DAMAGEMANAGER_H_
#define DAMAGEMANAGER_H_

/* ====== INCLUDES ====== */
#include "EngineModule.h"
#include "WorldEvent.h"

/* ====== STRUCTURES ====== */
class DamageManager final : public EngineModule
{
public:
    DamageManager() : EngineModule("DamageManager", CHANNEL_GAME) {}

    b32f StartUp();
    void ShutDown(); 

    void HandleAttack(const AttackEvent& event);
};

extern DamageManager g_damageMgr;

#endif // DAMAGEMANAGER_H_