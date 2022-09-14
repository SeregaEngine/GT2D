#ifndef ACTOR_H_
#define ACTOR_H_

/* ====== INCLUDES ====== */
#include "Entity.h"
#include "TList.h"

/* ====== STRUCTURES ====== */
// TODO(sean) AI module
#define COMMAND_ARGUMENT_STRSIZE 16

struct GT_CommandArgument
{
    union
    {
        f32 f;
        s32 n;
        char str[COMMAND_ARGUMENT_STRSIZE];
    };
};

struct GT_Command
{
    u32 cmd;
    TList<GT_CommandArgument> lstArgument;
};

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
    virtual void Init(const Vec2& vPosition, s32 width, s32 height, GT_Texture* pTexture) override;
    virtual void Update(f32 dtTime) override;

    void SetActorAnims(const GT_Animation* aActorAnims[]);
private:
    void HandleCommand(f32 dtTime);
    void HandleAnimation(f32 dtTime);
};

#endif // ACTOR_H_