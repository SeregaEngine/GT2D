#pragma once

#include "SDL_mixer.h"
#include "Engine/Types.h"
#include "Engine/EngineModule.h"

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

    GT_Sound* DefineWAV(const char* fileName);
    GT_Music* DefineMusic(const char* fileName);

    void UndefineSounds();
    void UndefineMusics();
    void UndefineResources() { UndefineSounds(); UndefineMusics(); }

    b32 PlaySound(GT_Sound* pSound, b32 bLoop = false);
    b32 PlayMusic(GT_Music* pMusic);
    void StopSounds() { Mix_HaltChannel(-1); }
    void StopMusic() { Mix_HaltMusic(); }
    void StopSoundsAndMusic() { StopSounds(); StopMusic(); }
};

inline SoundModule g_soundModule;