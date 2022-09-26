#ifndef WORLDEVENT_H_
#define WORLDEVENT_H_

/* ====== INCLUDES ====== */
#include "GTMath.h"

/* ====== DEFINES ====== */
enum eWorldEvent
{
    WORLD_EVENT_ATTACK = 0,
    WORLD_EVENT_DEATH,
};

/* ====== STRUCTURES ====== */
class Actor;

struct AttackEvent
{
    Actor* pAttacker;
};

struct DeathEvent
{
    Actor* pDead;
};

struct WorldEvent
{
    s32 type;
    union
    {
        AttackEvent attack;
        DeathEvent death;
    };
};

#endif // WORLDEVENT_H_