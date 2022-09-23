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

    ACTOR_ANIMATION_ATTACK,

    MAX_ACTOR_ANIMATIONS
};

/* ====== STRUCTURES ====== */
class Actor : public Entity
{
protected:
    /* Actor */
    s32 m_actorState;
    b32 m_bWatchRight;
    b32 m_bWantAttack;

    /* AI */
    const GT_State* m_pState;
    GT_Task* m_pTask;
    TList<GT_Command> m_lstCommand;

    /* Animations */
    const GT_Animation* m_aActorAnims[MAX_ACTOR_ANIMATIONS];

public:
    virtual void Init(const Vector2& vPosition, s32 width, s32 height, GT_Texture* pTexture) override;
    virtual void Clean() override { Entity::Clean(); RemoveTask(); }
    virtual void Update(f32 dtTime) override;

    /* AI */
    const GT_State* GetState() const { return m_pState; }
    GT_Task* GetTask() const { return m_pTask; }

    void SetState(const GT_State* pState) { m_pState = pState; }
    void SetTask(GT_Task* pTask) { RemoveTask(); m_pTask = pTask; }
    void RemoveTask() { if (m_pTask) delete m_pTask; m_pTask = nullptr; }
    void SendCommand(GT_Command& cmd) { m_lstCommand.Push(cmd); }
    void SendCommand(s32 enumCmd) {
        GT_Command cmd(enumCmd);
        m_lstCommand.Push(cmd);
    }

    /* Animations */
    void SetActorAnims(const GT_Animation* aActorAnims[]);

private:
    /* AI */
    // Handle AI stuff
    void HandleState() { g_AIModule.HandleState(this); }
    void HandleTask() { if (m_pTask) m_pTask->Handle(); }
    void HandleCommand(f32 dtTime);

    // Commands
    void Move(s32 cmd, f32 dtTime);
    void Attack();

    /* Animations */
    void HandleAnimation(f32 dtTime);
};

#endif // ACTOR_H_