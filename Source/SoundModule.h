#ifndef SOUNDMODULE_H_
#define SOUNDMODULE_H_

/* ====== INCLUDES ====== */
#include "SDL_mixer.h"

#include "Types.h"
#include "EngineModule.h"

/* ====== DEFINES====== */

/* ====== STRUCTURES ====== */
class SoundModule final: public EngineModule
{
    static const s32 MAX_SOUNDS = 256;

    Mix_Music* m_pMusic;
    Mix_Chunk* m_aSounds[MAX_SOUNDS];
public:
    SoundModule() : EngineModule("SoundModule", CHANNEL_SOUND) {}

    b32 StartUp();
    void ShutDown();

    s32 LoadWAV(const char* fileName); // -1 on error
    void UnloadSound(s32 id);
    b32 PlaySound(s32 id);

    b32 LoadMusic(const char* fileName);
    void UnloadMusic();
    b32 PlayMusic();
    void HaltMusic() { Mix_HaltMusic(); }
};

extern SoundModule g_soundModule;

#endif // SOUNDMODULE_H_