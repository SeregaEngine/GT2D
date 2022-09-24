#ifndef WORLDEVENT_H_
#define WORLDEVENT_H_

/* ====== INCLUDES ====== */
#include "GTMath.h"

/* ====== DEFINES ====== */
enum eWorldEvent
{
    WORLD_EVENT_ATTACK = 0,
};

/* ====== STRUCTURES ====== */
class Actor;

struct AttackEvent
{
    Actor* pAttacker;
};

struct WorldEvent
{
    s32 type;
    union
    {
        AttackEvent attack;
    };

    WorldEvent() = default;
    WorldEvent(const WorldEvent& event) { memcpy(this, &event, sizeof(*this)); };
};


#endif // WORLDEVENT_H_