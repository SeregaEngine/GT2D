#ifndef GOTOENTITYTASK_H_
#define GOTOENTITYTASK_H_

/* ====== INCLUDES ====== */
#include "GTTask.h"

/* ====== STRUCTURES ====== */
class Entity;

class GotoEntityTask final : public GT_Task
{
    Entity* m_pEntity;
public:
    GotoEntityTask(Actor* pActor, Entity* pEntity)
        : GT_Task(pActor, GTT_GOTO_ENTITY), m_pEntity(pEntity) {}

    virtual void Handle() override;
private:
    b32 IsDone();
    void HandleActor();

    void MoveX(const Vector2& vActor, const Vector2& vEntity, const Vector2& vError);
    void MoveY(const Vector2& vActor, const Vector2& vEntity, const Vector2& vError);
};

#endif // GOTOENTITYTASK_H_