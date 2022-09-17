#ifndef GOTOTASK_H_
#define GOTOTASK_H_

#include "GTTask.h"
#include "GTMath.h"

class Actor;

class GotoTask final : public GT_Task
{
    Actor* m_pActor;
    Vector2 m_vDestination;
    // TODO(sean) m_bCompletedX, m_bCompletedY to define when to stop
public:
    GotoTask(Actor* pActor, const Vector2& vDestination)
        : GT_Task(), m_pActor(pActor), m_vDestination(vDestination) {}

    virtual void Handle() override;
};

#endif // GOTOTASK_H_