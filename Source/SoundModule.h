#ifndef SOUNDMODULE_H_
#define SOUNDMODULE_H_

/* ====== INCLUDES ====== */
#include "SDL_mixer.h"

#include "Types.h"
#include "EngineModule.h"

/* ====== DEFINES====== */

/* ====== STRUCTURES ====== */
class SoundModule final : public EngineModule
{
    Mix_Music** m_aMusics;
    Mix_Chunk** m_aSounds;
public:
    SoundModule() : EngineModule("SoundModule", CHANNEL_SOUND) {}

    b32 StartUp();
    void ShutDown();

    s32 DefineWAV(const char* fileName); // -1 on error
    b32 DefineMusic(const char* fileName);

    void UndefineSounds();
    void UndefineMusics();
    void UndefineResources() { UndefineSounds(); UndefineMusics(); }

    b32 PlaySound(s32 id);
    b32 PlayMusic(s32 id);
    void HaltMusic() { Mix_HaltMusic(); }
};

extern SoundModule g_soundModule;

#endif // SOUNDMODULE_H_