#pragma once

#include "SDL_mixer.h"
#include "Engine/Types.h"
#include "Engine/EngineModule.h"

struct Sound;
struct Music;

class SoundModule final : public EngineModule
{
    Sound* m_aSounds;
    Music* m_aMusics;

public:
    SoundModule() : EngineModule("SoundModule", CHANNEL_SOUND) {}

    void StartUp();
    void ShutDown();

    Sound* DefineWAV(const char* fileName);
    Music* DefineMusic(const char* fileName);

    void UndefineSounds();
    void UndefineMusics();
    void UndefineResources() { UndefineSounds(); UndefineMusics(); }

    b32 PlaySound(Sound* pSound, b32 bLoop = false);
    b32 PlayMusic(Music* pMusic);
    void StopSounds() { Mix_HaltChannel(-1); }
    void StopMusic() { Mix_HaltMusic(); }
    void StopSoundsAndMusic() { StopSounds(); StopMusic(); }
};

inline SoundModule g_soundModule;