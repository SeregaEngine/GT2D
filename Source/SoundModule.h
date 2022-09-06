#ifndef SOUNDMODULE_H_
#define SOUNDMODULE_H_

/* ====== INCLUDES ====== */
#include "SDL_mixer.h"

#include "Types.h"
#include "EngineModule.h"

/* ====== DEFINES====== */
#define MAX_SOUNDS 256

/* ====== STRUCTURES ====== */
class SoundModule : public EngineModule
{
    Mix_Chunk* m_aSounds[MAX_SOUNDS];
public:
    SoundModule() : EngineModule("SoundModule", CHANNEL_SOUND) {}
    virtual ~SoundModule() {}

    b32 StartUp();
    void ShutDown();

    s32 LoadWAV(const char* fileName); // -1 on error
    void UnloadSound(s32 id);

    b32 PlaySound(s32 id);
};

extern SoundModule g_soundModule;

#endif // SOUNDMODULE_H_