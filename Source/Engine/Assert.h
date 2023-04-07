#pragma once

#include "Engine/Platform.h"
#include "Engine/DebugLogManager.h"

#define ShipAssert(EXPR) \
    if (EXPR) \
    {} \
    else \
    { \
        g_debugLogMgr.AddNote(CHANNEL_GT2D, PR_ERROR, "Assertion", "Shipping assertion \"%s\" failed at %s:%d", #EXPR, __FILE__, __LINE__); \
        ForceShutDown(); \
    }

#if _DEBUG
    #define DebugAssert(EXPR) \
        if (EXPR) \
        {} \
        else \
        { \
            g_debugLogMgr.AddNote(CHANNEL_GT2D, PR_ERROR, "Assertion", "Debug assertion \"%s\" failed at %s:%d", #EXPR, __FILE__, __LINE__); \
            ForceShutDown(); \
        }
#else
    #define DebugAssert(EXPR)
#endif

#define AssertNoEntry() ShipAssert(!"No Entry")
