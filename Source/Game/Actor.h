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
    const GT_State* m_pState;
    GT_Task* m_pTask;
    TList<GT_Command> m_lstCommand;

    const GT_Animation* m_aActorAnims[MAX_ACTOR_ANIMATIONS];

public:
    virtual void Init(const Vector2& vPosition, s32 width, s32 height, GT_Texture* pTexture) override;
    virtual void Clean() override { RemoveTask(); }
    virtual void Update(f32 dtTime) override;

    const GT_State* GetState() const { return m_pState; }

    void SetState(const GT_State* pState) { m_pState = pState; }
    void SetTask(GT_Task* pTask) { RemoveTask(); m_pTask = pTask; }
    void RemoveTask() { if (m_pTask) delete m_pTask; m_pTask = nullptr; }
    void SendCommand(GT_Command& cmd) { m_lstCommand.Push(cmd); }
    void SendCommand(s32 enumCmd) {
        GT_Command cmd(enumCmd);
        m_lstCommand.Push(cmd);
    }

    void SetActorAnims(const GT_Animation* aActorAnims[]);

private:
    void HandleState() { g_AIModule.HandleState(this); }
    void HandleTask() { if (m_pTask) m_pTask->Handle(); }
    void HandleCommand(f32 dtTime);

    void HandleAnimation(f32 dtTime);
};

#endif // ACTOR_H_