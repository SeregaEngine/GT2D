#ifndef GOTOTASK_H_
#define GOTOTASK_H_

#include "GTTask.h"
#include "GTMath.h"

class GotoTask final : public GT_Task
{
    Vector2 m_vDestination;
    b32 m_bCompletedX, m_bCompletedY;
public:
    GotoTask(Actor* pActor, const Vector2& vDestination) :
        GT_Task(pActor, GTT_GOTO), m_vDestination(vDestination),
        m_bCompletedX(false), m_bCompletedY(false) {}

    virtual void Handle() override;
};

#endif // GOTOTASK_H_