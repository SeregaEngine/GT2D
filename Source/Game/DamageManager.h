#pragma once

#include "Engine/EngineModule.h"

class Actor;

class DamageManager final : public EngineModule
{
public:
    DamageManager() : EngineModule("DamageManager", CHANNEL_GAME) {}

    b32 StartUp();
    void ShutDown(); 

    void HandleAttack(const Actor* pAttacker);
};

inline DamageManager g_damageMgr;