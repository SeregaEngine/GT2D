/* ====== TODO ======
 * - Loop sounds, music
 * - Array of music
 * - Fade out music
 * - Dynamic allocation for arrays
 */

/* ====== INCLUDES ====== */
#include "SoundModule.h"

/* ====== DEFINES ====== */
#define MAX_SOUNDS 256
#define MAX_MUSICS 256

/* ====== VARIABLES ====== */
SoundModule g_soundModule;

/* ====== METHODS ====== */
b32 SoundModule::StartUp()
{
    // Init sounds
    m_aSounds = new Mix_Chunk*[MAX_SOUNDS];
    for (s32 i = 0; i < MAX_SOUNDS; ++i)
        m_aSounds[i] = nullptr;

    m_aMusics = new Mix_Music*[MAX_MUSICS];
    for (s32 i = 0; i < MAX_MUSICS; ++i)
        m_aMusics[i] = nullptr;

    AddNote(PR_NOTE, "Module started");

    return true;
}

void SoundModule::ShutDown()
{
    HaltMusic();
    UndefineResources();
    delete[] m_aMusics;
    delete[] m_aSounds;

    AddNote(PR_NOTE, "Module shut down");
}

s32 SoundModule::DefineWAV(const char* fileName)
{
    for (s32 i = 0; i < MAX_SOUNDS; ++i)
    {
        if (!m_aSounds[i])
        {
            m_aSounds[i] = Mix_LoadWAV(fileName);

            if (!m_aSounds[i])
            {
                AddNote(PR_WARNING, "Can't define sound %s: %s", fileName, Mix_GetError());
                return -1;
            }

            return i;
        }
    }

    return -1;
}

b32 SoundModule::DefineMusic(const char* fileName)
{
    for (s32 i = 0; i < MAX_MUSICS; ++i)
    {
        if (!m_aMusics[i])
        {
            m_aMusics[i] = Mix_LoadMUS(fileName);

            if (!m_aMusics[i])
            {
                AddNote(PR_WARNING, "Can't define music %s: %s", fileName, Mix_GetError());
                return -1;
            }

            return i;
        }
    }

    return -1;
}

void SoundModule::UndefineSounds()
{
    if (m_aSounds)
    {
        for (s32 i = 0; i < MAX_SOUNDS; ++i)
        {
            if (m_aSounds[i])
            {
                Mix_FreeChunk(m_aSounds[i]);
                m_aSounds[i] = nullptr;
            }
        }
    }
}

void SoundModule::UndefineMusics()
{
    if (m_aMusics)
    {
        for (s32 i = 0; i < MAX_MUSICS; ++i)
        {
            if (m_aMusics[i])
            {
                Mix_FreeMusic(m_aMusics[i]);
                m_aMusics[i] = nullptr;
            }
        }
    }
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

b32 SoundModule::PlayMusic(s32 id)
{
    if (id != -1 && m_aMusics[id])
    {
        Mix_PlayMusic(m_aMusics[id], 65535); // Play 65535 times
        return true;
    }
    else
    {
        AddNote(PR_WARNING, "There're no music with %d id", id);
        return false;
    }
}
