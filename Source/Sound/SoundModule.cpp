#include "Sound/Sound.h"
#include "Sound/SoundModule.h"

static constexpr i32f MAX_SOUNDS = 256;
static constexpr i32f MAX_MUSICS = 256;

struct Music
{
    Mix_Music* pMusic;
};

void SoundModule::StartUp()
{
    // Init sounds
    m_aSounds = new Sound[MAX_SOUNDS];
    memset(m_aSounds, 0, MAX_SOUNDS * sizeof(Sound));

    m_aMusics = new Music[MAX_MUSICS];
    memset(m_aMusics, 0, MAX_MUSICS * sizeof(Music));

    AddNote(PR_NOTE, "Module started");
}

void SoundModule::ShutDown()
{
    StopSoundsAndMusic();
    UndefineResources();
    delete[] m_aMusics;
    delete[] m_aSounds;

    AddNote(PR_NOTE, "Module shut down");
}

Sound* SoundModule::DefineWAV(const char* fileName)
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

Music* SoundModule::DefineMusic(const char* fileName)
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
    StopSounds();

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
    StopMusic();

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

b32 SoundModule::PlaySound(Sound* pSound, b32 bLoop)
{
    if (pSound)
    {
        Mix_PlayChannel(-1, pSound->pSound, bLoop ? -1 : 0);
        return true;
    }
    else
    {
        AddNote(PR_WARNING, "PlaySound() called with null sound");
        return false;
    }
}

b32 SoundModule::PlayMusic(Music* pMusic)
{
    if (pMusic)
    {
        // @NOTE: 65535 it's like infinite loop, i don't think it's possible to reach this limit...
        Mix_PlayMusic(pMusic->pMusic, 65535);
        return true;
    }
    else
    {
        AddNote(PR_WARNING, "PlayMusic() called with null music");
        return false;
    }
}
