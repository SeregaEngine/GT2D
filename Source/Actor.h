#ifndef ACTOR_H_
#define ACTOR_H_

/* ====== INCLUDES ====== */
#include "Entity.h"

/* ====== STRUCTURES ====== */
struct GT_AIState
{
    s32 (*cmd)[3]; // [0] - cmd, [1] - arg1, [2] - arg2
    s32 count;
};

class Actor : public Entity
{
protected:
    b32 m_bControllable;

    const GT_AIState* m_state;
    s32 m_cmdCounter;

public:
    virtual void Init(const Vec2& vPosition, s32 width, s32 height, GT_Texture* pTexture) override;
protected:
    void HandleEvents(f32 dtTime);
    void HandleAnimation(f32 dtTime);
private:
    void HandleCommand();
    void HandleInput(f32 dtTime);
};

#endif // ACTOR_H_