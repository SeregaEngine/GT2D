#ifndef AIMODULE_H_
#define AIMODULE_H_

/* ====== INCLUDES ====== */
#include "TList.h"

/* ====== DEFINES ====== */
enum eAICommand
{
    GTC_MOVE_UP = 0,
    GTC_MOVE_LEFT,
    GTC_MOVE_DOWN,
    GTC_MOVE_RIGHT
};

#define COMMAND_ARGUMENT_STRSIZE 16

/* ====== STRUCTURES ====== */
struct GT_Command
{
    s32 cmd;
    TList<f32> lstArgument;
};

class AIModule
{
public:
    b32 StartUp();
    void ShutDown();

private:
    void AddNote(s32 priority, const char* fmt, ...);
};

extern AIModule g_AIModule;

#endif // AIMODULE_H_