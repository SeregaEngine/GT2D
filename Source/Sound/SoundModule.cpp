/* ====== TODO ======
 * - Loop sounds
 * - Fade out music
 */

/* ====== INCLUDES ====== */
#include "SDL_mixer.h"

#include "GTSound.h"

#include "SoundModule.h"

/* ====== DEFINES ====== */
#define MAX_SOUNDS 256
#define MAX_MUSICS 256

/* ====== STRUCTURES ====== */
struct GT_Music
{
    Mix_Music* pMusic;
};

/* ====== VARIABLES ====== */
SoundModule g_soundModule;

/* ====== METHODS ====== */
b32 SoundModule::StartUp()
{
    // Init sounds
    m_aSounds = new GT_Sound[MAX_SOUNDS];
    for (i32f i = 0; i < MAX_SOUNDS; ++i)
        m_aSounds[i].pSound = nullptr;

    m_aMusics = new GT_Music[MAX_MUSICS];
    for (i32f i = 0; i < MAX_MUSICS; ++i)
        m_aMusics[i].pMusic = nullptr;

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

GT_Sound* SoundModule::DefineWAV(const char* fileName)
{
    for (i32f i = 0; i < MAX_SOUNDS; ++i)
    {
        if (!m_aSounds[i].pSound)
        {
            m_aSounds[i].pSound = Mix_LoadWAV(fileName);

            if (!m_aSounds[i].pSound)
            {
                AddNote(PR_WARNING, "Can't define sound %s: %s", fileName, Mix_GetError());
                return nullptr;
            }

            return &m_aSounds[i];
        }
    }

    return nullptr;
}

GT_Music* SoundModule::DefineMusic(const char* fileName)
{
    for (i32f i = 0; i < MAX_MUSICS; ++i)
    {
        if (!m_aMusics[i].pMusic)
        {
            m_aMusics[i].pMusic = Mix_LoadMUS(fileName);

            if (!m_aMusics[i].pMusic)
            {
                AddNote(PR_WARNING, "Can't define music %s: %s", fileName, Mix_GetError());
                return nullptr;
            }

            return &m_aMusics[i];
        }
    }

    return nullptr;
}

void SoundModule::UndefineSounds()
{
    if (m_aSounds)
    {
        for (i32f i = 0; i < MAX_SOUNDS; ++i)
        {
            if (m_aSounds[i].pSound)
            {
                Mix_FreeChunk(m_aSounds[i].pSound);
                m_aSounds[i].pSound = nullptr;
            }
        }
    }
}

void SoundModule::UndefineMusics()
{
    if (m_aMusics)
    {
        for (i32f i = 0; i < MAX_MUSICS; ++i)
        {
            if (m_aMusics[i].pMusic)
            {
                Mix_FreeMusic(m_aMusics[i].pMusic);
                m_aMusics[i].pMusic = nullptr;
            }
        }
    }
}

b32 SoundModule::PlaySound(GT_Sound* pSound)
{
    if (pSound)
    {
        Mix_PlayChannel(-1, pSound->pSound, 0);
        return true;
    }
    else
    {
        AddNote(PR_WARNING, "PlaySound() called with null sound");
        return false;
    }
}

b32 SoundModule::PlayMusic(GT_Music* pMusic)
{
    if (pMusic)
    {
        Mix_PlayMusic(pMusic->pMusic, 65535); // Play 65535 times
        return true;
    }
    else
    {
        AddNote(PR_WARNING, "PlayMusic() called with null music");
        return false;
    }
}

void SoundModule::HaltMusic()
{
    Mix_HaltMusic();
}
