#pragma once

#include "Types.h"
#include "SoundModule.h"
#include "GTSound.h"

class GT_SoundPack
{
    GT_Sound** m_aSounds;
    s32 m_count;

public:
    GT_SoundPack() : m_aSounds(nullptr), m_count(0) {}
    GT_SoundPack(s32 count) :
        m_aSounds(count > 0 ? new GT_Sound*[count] : nullptr), m_count(count)
    {
        memset(m_aSounds, 0, count * sizeof(GT_Sound*));
    }

    ~GT_SoundPack()
    {
        if (m_aSounds)
        {
            delete[] m_aSounds;
        }
    }

    GT_Sound** GetSounds() { return m_aSounds; }
    s32 GetCount() const { return m_count; }

    void Allocate(s32 count)
    {
        Clean();
        if (count > 0)
        {
            m_aSounds = new GT_Sound*[count];
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
