#ifndef GTTASK_H_
#define GTTASK_H_

/* ====== INCLUDES ====== */
#include <Types.h>

/* ====== DEFINES ====== */
enum eGTTaskStatus
{
    GTT_NONE = 0,
    GTT_DONE = 1,
    GTT_INPROCESS = 2
};

enum eGTTask
{
    GTT_GOTO
};

/* ====== STRUCTURES ====== */
// Tasks send commands to Actors
class GT_Task
{
protected:
    s32 m_status;
public:
    GT_Task() : m_status(GTT_INPROCESS) {}
    virtual ~GT_Task() {}

    virtual void Handle() = 0;
    s32 GetStatus() const { return m_status; }
};

#endif // GTTASK_H_