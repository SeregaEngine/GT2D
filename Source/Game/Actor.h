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

    MAX_ACTOR_STATES
};

enum eActorAnimation
{
    ACTOR_ANIMATION_IDLE = 0,
    ACTOR_ANIMATION_MOVE_HORIZONTAL,
    ACTOR_ANIMATION_TOP,
    ACTOR_ANIMATION_BOTTOM,

    MAX_ACTOR_ANIMATIONS
};

enum eActorTeam
{
    ACTOR_TEAM_DEFAULT = 0,
};

/* ====== STRUCTURES ====== */
class Weapon;

class Actor final : public Entity
{
protected:
    /* Actor */
    s32 m_actorState;
    s32 m_actorTeam;

    Vector2 m_vSpeed;
    f32 m_health;

    b32 m_bGodMode;
    b32 m_bLookRight;

    f32 m_attackRate;
    const Weapon* m_pWeapon;

    /* AI */
    const GT_State* m_pState;
    GT_Task* m_pTask;
    TList<GT_Command> m_lstCommand;

    /* Animations */
    const GT_Animation* m_aActorAnims[MAX_ACTOR_ANIMATIONS];

public:
    virtual void Init(const Vector2& vPosition, s32 width, s32 height, const GT_Texture* pTexture) override;
    virtual void Clean() override { Entity::Clean(); RemoveTask(); }
    virtual void Update(f32 dtTime) override;

    /* Actor */
    void SetTeam(s32 team) { m_actorTeam = team; }
    s32 GetTeam() const { return m_actorTeam; }

    void TurnRight() { m_bLookRight = true; }
    void TurnLeft() { m_bLookRight = false; }
    b32 IsLookRight() const { return m_bLookRight; }

    void SetSpeed(const Vector2& vSpeed) { m_vSpeed = vSpeed; }
    const Vector2& GetSpeed() const { return m_vSpeed; }

    void AddHealth(f32 diff) { if (!m_bGodMode) m_health += diff; }
    void SetHealth(f32 health) { m_health = health; }
    f32 GetHealth() const { return m_health; }

    void ToggleGodMode(b32 bToggle) { m_bGodMode = bToggle; }
    b32 IsInGodMode() const { return m_bGodMode; }

    void SetAttackRate(f32 attackRate) { m_attackRate = attackRate; }
    void SetWeapon(const Weapon* pWeapon) { m_pWeapon = pWeapon; }
    f32 GetAttackRate() const { return m_attackRate; }
    const Weapon* GetWeapon() const { return m_pWeapon; }

    /* AI */
    void SetState(const GT_State* pState) { m_pState = pState; }
    const GT_State* GetState() const { return m_pState; }

    void SetTask(GT_Task* pTask) { RemoveTask(); m_pTask = pTask; }
    void RemoveTask() { if (m_pTask) delete m_pTask; m_pTask = nullptr; }
    GT_Task* GetTask() const { return m_pTask; }

    void SendCommand(GT_Command& cmd) { m_lstCommand.Push(cmd); }
    void SendCommand(s32 enumCmd) {
        GT_Command cmd(enumCmd);
        m_lstCommand.Push(cmd);
    }

    /* Animations */
    void SetActorAnims(const GT_Animation* aActorAnims[])
        { memcpy(m_aActorAnims, aActorAnims, sizeof(m_aActorAnims[0]) * MAX_ACTOR_ANIMATIONS); }

private:
    /* Actor */
    b32f HandleDeath();

    /* AI */
    // Handle AI stuff
    void HandleState() { g_AIModule.HandleState(this); }
    void HandleTask() { if (m_pTask) m_pTask->Handle(); }
    void HandleCommand(f32 dtTime);

    // Commands
    void CommandMove(s32 cmd, f32 dtTime);
    void CommandAttack();

    /* Animations */
    void HandleAnimation(f32 dtTime);

    // Animate actor states
    void AnimateIdle();
    void AnimateMove();
    void AnimateAttack();
};

#endif // ACTOR_H_