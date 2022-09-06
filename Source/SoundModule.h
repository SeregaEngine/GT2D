#ifndef SOUNDMODULE_H_
#define SOUNDMODULE_H_

/* ====== INCLUDES ====== */
#include "Types.h"
#include "EngineModule.h"

/* ====== DEFINES====== */
#define MAX_SOUNDS 256 // NOTE(sean) check if we need this

/* ====== STRUCTURES ====== */
class SoundModule : public EngineModule
{
public:
    SoundModule() : EngineModule("SoundModule", CHANNEL_SOUND) {}
    virtual ~SoundModule() {}

    b32 StartUp();
    void ShutDown();

#if 0 // TODO(sean)
    /* Sound */
    // Returns buffer's ID, -1 on error
    s32 LoadWAV(const char* fileName);
    void UnloadBuffer(s32 id);

    b32 PlayBuffer(s32 id, b32 loop = false);
    b32 StopBuffer(s32 id);

    b32 SetBufferVolume(s32 id, s32 volume) // volume = [0..100]
        { return m_aSounds[id].pDSBuffer->SetVolume(volume > 0 ? -50 * (100-volume) : DSBVOLUME_MIN); }
    b32 SetBufferFrequency(s32 id, s32 frequency) // frequency = [100..100000]
        { return m_aSounds[id].pDSBuffer->SetFrequency(frequency); }
    b32 SetBufferPan(s32 id, s32 pan) // pan = [-10000..10000]
        { return m_aSounds[id].pDSBuffer->SetPan(pan); }

    /* Midi */
    // -1 on error
    s32 LoadMIDI(const char* fileName);
    void UnloadMIDI(s32 id);

    b32 PlayMIDI(s32 id);
    b32 StopMIDI(s32 id)
#endif
};

extern SoundModule g_soundModule;

#endif // SOUNDMODULE_H_