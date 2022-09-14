#ifndef AIMODULE_H_
#define AIMODULE_H_

#include "Types.h"

class AIModule
{
public:
    b32 StartUp();
    void ShutDown();

private:
    void AddNote(s32 priority, const char* fmt, ...);
};

extern AIModule g_AIModule;

#endif AIMODULE_H_