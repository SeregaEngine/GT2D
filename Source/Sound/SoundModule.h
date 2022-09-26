#ifndef SOUNDMODULE_H_
#define SOUNDMODULE_H_

/* ====== INCLUDES ====== */
#include "SDL_mixer.h"

#include "Types.h"
#include "EngineModule.h"

/* ====== DEFINES====== */

/* ====== STRUCTURES ====== */
struct GT_Sound;
struct GT_Music;

class SoundModule final : public EngineModule
{
    GT_Sound* m_aSounds;
    GT_Music* m_aMusics;
public:
    SoundModule() : EngineModule("SoundModule", CHANNEL_SOUND) {}

    b32 StartUp();
    void ShutDown();

    GT_Sound* DefineWAV(const char* fileName); // -1 on error
    GT_Music* DefineMusic(const char* fileName);

    void UndefineSounds();
    void UndefineMusics();
    void UndefineResources() { UndefineSounds(); UndefineMusics(); }

    b32 PlaySound(GT_Sound* pSound);
    b32 PlayMusic(GT_Music* pMusic);
    void StopSounds() { Mix_HaltChannel(-1); }
    void StopMusic() { Mix_HaltMusic(); }
    void StopSoundsAndMusic() { StopSounds(); StopMusic(); }
};

extern SoundModule g_soundModule;

#endif // SOUNDMODULE_H_