#ifndef ACTOR_H_
#define ACTOR_H_

/* ====== INCLUDES ====== */
#include "Entity.h"
#include "AIModule.h"

/* ====== STRUCTURES ====== */
class Actor : public Entity
{
public:
    enum eActorAnimation
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
    TList<GT_Command> m_lstCommand;

public:
    virtual void Init(const Vector2& vPosition, s32 width, s32 height, GT_Texture* pTexture) override;
    virtual void Update(f32 dtTime) override;

    void SetActorAnims(const GT_Animation* aActorAnims[]);

    void SendCommand(GT_Command& cmd) { m_lstCommand.Push(cmd); }
private:
    void HandleCommand(f32 dtTime);
    void HandleAnimation(f32 dtTime);
};

#endif // ACTOR_H_