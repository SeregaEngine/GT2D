#ifndef DAMAGEMANAGER_H_
#define DAMAGEMANAGER_H_

/* ====== INCLUDES ====== */
#include "EngineModule.h"

/* ====== STRUCTURES ====== */
class Actor;

class DamageManager final : public EngineModule
{
public:
    DamageManager() : EngineModule("DamageManager", CHANNEL_GAME) {}

    b32f StartUp();
    void ShutDown(); 

    void HandleAttack(const Actor* pAttacker);
};

extern DamageManager g_damageMgr;

#endif // DAMAGEMANAGER_H_