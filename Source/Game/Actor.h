#ifndef ACTOR_H_
#define ACTOR_H_

/* ====== INCLUDES ====== */
#include "Entity.h"
#include "AIModule.h"

/* ====== DEFINES ====== */
enum eActorState
{
    ACTOR_STATE_IDLE = 0,
    ACTOR_STATE_MOVE,
    ACTOR_STATE_ATTACK,
    ACTOR_STATE_DEAD,
    ACTOR_STATE_INCAR,
    ACTOR_STATE_ANIMATE_ONCE,
    ACTOR_STATE_ANIMATE_LOOPED,

    MAX_ACTOR_STATES
};

enum eActorAnimation
{
    ACTOR_ANIMATION_IDLE = 0,
    ACTOR_ANIMATION_HORIZONTAL,
    ACTOR_ANIMATION_TOP,
    ACTOR_ANIMATION_BOTTOM,
    ACTOR_ANIMATION_DEAD,
    ACTOR_ANIMATION_INCAR,

    MAX_ACTOR_ANIMATIONS
};

enum eActorTeam
{
    ACTOR_TEAM_DEFAULT = 0,
};

/* ====== STRUCTURES ====== */
class Weapon;
struct GT_Sound;

class Actor final : public Entity
{
public:
    /* Actor */
    s32 m_actorState;
    s32 m_actorTeam;

    Vector2 m_vSpeed;
    f32 m_health;

    b32 m_bGodMode;
    b32 m_bLookRight;

    GT_Sound* m_pDeathSound;

    f32 m_attackRate;
    const Weapon* m_pWeapon;
private:
    /* AI */
    const GT_State* m_pState;
    GT_Task* m_pTask;
    TList<s32> m_lstCommand;
public:
    /* Animations */
    const GT_Animation* m_aActorAnims[MAX_ACTOR_ANIMATIONS];

public:
    virtual void Init(const Vector2& vPosition, s32 width, s32 height, const GT_Texture* pTexture) override;
    virtual void Clean() override { Entity::Clean(); RemoveTask(); }
    virtual void Update(f32 dtTime) override;

    /* Actor */
    void AddHealth(f32 diff) { if (!m_bGodMode) m_health += diff; }

    /* AI */
    void SetState(const GT_State* pState) { m_pState = pState; }
    const GT_State* GetState() const { return m_pState; }

    void SetTask(GT_Task* pTask) { RemoveTask(); m_pTask = pTask; }
    void RemoveTask() { if (m_pTask) delete m_pTask; m_pTask = nullptr; }
    GT_Task* GetTask() const { return m_pTask; }

    void SendCommand(s32 enumCmd) { m_lstCommand.Push(enumCmd); }
private:
    /* Actor */
    b32 HandleDeath();
    void HandleActorState(f32 dtTime);

    /* AI */
    void HandleAIState() { g_AIModule.HandleState(this); }
    void HandleAITask() { if (m_pTask) m_pTask->Handle(); }
    void HandleAICommand(f32 dtTime);

    // Commands
    void CommandMove(s32 cmd, f32 dtTime);
    void CommandAttack();

    /* Animations */
    void HandleAnimation(f32 dtTime);

    // Animate actor states
    void AnimateIdle();
    void AnimateMove();
    void AnimateAttack();
    b32 AnimateDead();
    void AnimateInCar();
};

#endif // ACTOR_H_