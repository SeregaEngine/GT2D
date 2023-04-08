#pragma once

#include "AI/AITask.h"

class Entity;

class GotoEntityTask final : public AITask
{
    Entity* m_pEntity;

public:
    GotoEntityTask(Actor* pActor, Entity* pEntity) :
        AITask(pActor, AITASK_GOTO_ENTITY), m_pEntity(pEntity) {}

    virtual void Handle() override;

private:
    b32 IsDone() const;
    void HandleActor();

    void MoveX(const Vector2& vActor, const Vector2& vEntity, const Vector2& vError);
    void MoveY(const Vector2& vActor, const Vector2& vEntity, const Vector2& vError);
};
