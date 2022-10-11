#ifndef ACTOR_H_
#define ACTOR_H_

/* ====== INCLUDES ====== */
#include "Entity.h"
#include "GTState.h"
#include "GTTask.h"
#include "GTCommand.h"

/* ====== DEFINES ====== */
enum eActorState
{
    ACTOR_STATE_IDLE = 0,
    ACTOR_STATE_AFTER_ANIMATION,
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
    GT_State m_state;
    TList<GT_Task*> m_lstTask;
    TList<s32> m_lstCommand;
public:
    /* Animations */
    const GT_Animation* m_aActorAnims[MAX_ACTOR_ANIMATIONS];

public:
    virtual void Init(const Vector2& vPosition, s32 width, s32 height, const GT_Texture* pTexture) override;
    virtual void Clean() override { Entity::Clean(); RemoveTasks(); }
    virtual void Update(f32 dtTime) override;

    /* Actor */
    void AddHealth(f32 diff) { if (!m_bGodMode) m_health += diff; }

    /* AI */
    void SetState(const char* functionName) { m_state.SetFunctionName(functionName); }
    const GT_State& GetState() const { return m_state; }

    void PushTask(GT_Task* pTask) { if (pTask) m_lstTask.Push(pTask); }
    void RemoveTasks() { m_lstTask.Mapcar([](auto pTask) { delete pTask; }); m_lstTask.Clean(); }
    const GT_Task* GetCurrentTask() { return m_lstTask.IsEmpty() ? nullptr : m_lstTask.Front(); }

    void PushCommand(s32 enumCmd) { m_lstCommand.Push(enumCmd); }
private:
    /* Actor */
    b32 HandleDeath();
    void HandleActorState(f32 dtTime);

    /* AI */
    void HandleAIState() { m_state.Handle(); }
    void HandleAITasks();
    void HandleAICommand(f32 dtTime);

    // Commands
    void CommandIdle() { m_actorState = ACTOR_STATE_IDLE; }
    void CommandTurnLeft() { m_bLookRight = false; }
    void CommandTurnRight() { m_bLookRight = true; }
    void CommandMove(s32 cmd, f32 dtTime);
    void CommandAttack();

    /* Animations */
    void HandleAnimation(f32 dtTime);

    // Animate actor states
    void AnimateIdle();
    void AnimateAfterAnimation();
    void AnimateMove();
    void AnimateAttack();
    b32 AnimateDead();
    void AnimateInCar();
};

#endif // ACTOR_H_