#pragma once

#include "Engine/StdHeaders.h"
#include "Engine/Types.h"
#include "Sound/SoundModule.h"
#include "Sound/Sound.h"

class SoundPack
{
    Sound** m_aSounds;
    s32 m_count;

public:
    SoundPack() : m_aSounds(nullptr), m_count(0) {}
    SoundPack(s32 count) :
        m_aSounds(count > 0 ? new Sound*[count] : nullptr), m_count(count)
    {
        std::memset(m_aSounds, 0, count * sizeof(Sound*));
    }

    ~SoundPack()
    {
        if (m_aSounds)
        {
            delete[] m_aSounds;
        }
    }

    forceinline Sound** GetSounds() const { return m_aSounds; }
    forceinline s32 GetCount() const { return m_count; }

    void Allocate(s32 count)
    {
        Clean();
        if (count > 0)
        {
            m_aSounds = new Sound*[count];
            for (i32f i = 0; i < count; ++i)
            {
                m_aSounds[i] = nullptr;
            }
            m_count = count;
        }
    }

    void Clean()
    {
        if (m_aSounds)
        {
            delete[] m_aSounds;
            m_aSounds = nullptr;
        }
        m_count = 0;
    }

    void Play(i32f index) const
    {
        if (index >= 0 && index < m_count && m_aSounds[index])
        {
            g_soundModule.PlaySound(m_aSounds[index]);
        }
        else
        {
            g_debugLogMgr.AddNote(CHANNEL_GAME, PR_WARNING, "SoundPack", "Play() called with wrong index %d", index);
        }
    }
};
