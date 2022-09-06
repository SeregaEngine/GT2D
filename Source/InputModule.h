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
    const Uint8* m_keyState;
public:
    b32 StartUp();
    void ShutDown();

    b32 HandleEvents();

    // Keyboard
    b32 IsKeyDown_s(SDL_Scancode scan) const { return m_keyState[scan]; }
    b32 IsKeyDown(SDL_Keycode key) const { return m_keyState[SDL_GetScancodeFromKey(key)]; }

    // Mouse
    /*
    b32 IsMouseDown(s32 key) const { return m_mouseState.rgbButtons[key] & 0x80; }
    s32 GetMouseRelX() const { return m_mouseState.lX; }
    s32 GetMouseRelY() const { return m_mouseState.lY; }
    s32 GetMouseRelZ() const { return m_mouseState.lZ; }*/
};

extern InputModule g_inputModule;

#endif // INPUTMODULE_H_
