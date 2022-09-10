/* ====== TODO ======
 * - Loop sounds, music
 * - Array of music
 * - Fade out music
 * - Dynamic allocation for arrays
 */

/* ====== INCLUDES ====== */
#include "SoundModule.h"

/* ====== DEFINES ====== */

/* ====== VARIABLES ====== */
SoundModule g_soundModule;

/* ====== METHODS ====== */
b32 SoundModule::StartUp()
{
    // Init sounds
    m_pMusic = nullptr;
    for (s32 i = 0; i < MAX_SOUNDS; ++i)
        m_aSounds[i] = nullptr;

    AddNote(PR_NOTE, "Module started");

    return true;
}

void SoundModule::ShutDown()
{
    AddNote(PR_NOTE, "Module shut down");
}

s32 SoundModule::LoadWAV(const char* fileName)
{
    for (s32 i = 0; i < MAX_SOUNDS; ++i)
    {
        if (!m_aSounds[i])
        {
            m_aSounds[i] = Mix_LoadWAV(fileName);

            if (!m_aSounds[i])
            {
                AddNote(PR_WARNING, "Can't load sound %s: %s", fileName, Mix_GetError());
                return -1;
            }

            return i;
        }
    }

    return -1;
}

void SoundModule::UnloadSound(s32 id)
{
    if (id != -1 && m_aSounds[id])
        Mix_FreeChunk(m_aSounds[id]);
    else
        AddNote(PR_NOTE, "Trying to unload null sound with %d id", id);
}

b32 SoundModule::PlaySound(s32 id)
{
    if (id != -1 && m_aSounds[id])
    {
        Mix_PlayChannel(-1, m_aSounds[id], 0);
        return true;
    }
    else
    {
        AddNote(PR_WARNING, "There're no sound with %d id", id);
        return false;
    }
}

b32 SoundModule::LoadMusic(const char* fileName)
{
    // Check if we already have one
    if (m_pMusic)
        UnloadMusic();

    // Try to load
    m_pMusic = Mix_LoadMUS(fileName);
    if (!m_pMusic)
    {
        AddNote(PR_WARNING, "Can't load music %s: %s", fileName, Mix_GetError());
        return false;
    }

    return true;
}

void SoundModule::UnloadMusic()
{
    if (m_pMusic)
    {
        Mix_FreeMusic(m_pMusic);
        m_pMusic = nullptr;
    }
}

b32 SoundModule::PlayMusic()
{
    if (m_pMusic)
    {
        return 0 == Mix_PlayMusic(m_pMusic, 0) ? true : false;
    }
    else
    {
        AddNote(PR_WARNING, "There're no music to play");
        return false;
    }
}
