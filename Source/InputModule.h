#ifndef INPUTMODULE_H_
#define INPUTMODULE_H_

/* ====== INCLUDES ====== */
#include "SDL.h"

#include "Types.h"
#include "EngineModule.h"

/* ====== DEFINES ====== */

/* ====== STRUCTURES ====== */
class InputModule : public EngineModule
{

public:
    b32 StartUp();
    void ShutDown();

    b32 HandleEvents();
    /* DEBUG(sean)
    // Keyboard
    b32 IsKeyDown(s32 key) const { return m_keyState[key] & 0x80; }

    // Mouse
    b32 IsMouseDown(s32 key) const { return m_mouseState.rgbButtons[key] & 0x80; }
    s32 GetMouseRelX() const { return m_mouseState.lX; }
    s32 GetMouseRelY() const { return m_mouseState.lY; }
    s32 GetMouseRelZ() const { return m_mouseState.lZ; }*/
};

extern InputModule g_inputModule;

#endif // INPUTMODULE_H_
