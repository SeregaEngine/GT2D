#ifndef ACTOR_H_
#define ACTOR_H_

/* ====== INCLUDES ====== */
#include "Entity.h"

/* ====== STRUCTURES ====== */
struct GT_AIState // TODO(sean) AIModule
{
    s32 (*cmd)[3]; // [0] - cmd, [1] - arg1, [2] - arg2
    s32 count;
};

class Actor : public Entity
{
public:
    enum eActorAnimation // TODO(sean) Maybe enum class?
    {
        ACTOR_ANIMATION_IDLE_RIGHT = 0,
        ACTOR_ANIMATION_IDLE_LEFT,
        ACTOR_ANIMATION_RIGHT,
        ACTOR_ANIMATION_LEFT,
        ACTOR_ANIMATION_TOP,
        ACTOR_ANIMATION_BOTTOM,

        MAX_ACTOR_ANIMATIONS
    };

protected:
    const GT_Animation* m_aActorAnims[MAX_ACTOR_ANIMATIONS]; // Default actor's animations

    b32 m_bControllable;
    const GT_AIState* m_state;
    s32 m_cmdCounter;

public:
    virtual void Init(const Vec2& vPosition, s32 width, s32 height, GT_Texture* pTexture) override;
    void SetActorAnims(const GT_Animation* aActorAnims[]);
protected:
    void HandleEvents(f32 dtTime);
    void HandleAnimation(f32 dtTime);
private:
    void HandleCmd();
    void HandleInput(f32 dtTime);
};

#endif // ACTOR_H_