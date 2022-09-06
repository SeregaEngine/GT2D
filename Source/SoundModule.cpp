/* ====== TODO ======
 *
 */

/* ====== INCLUDES ====== */
#include "SoundModule.h"

/* ====== DEFINES ====== */

/* ====== VARIABLES ====== */
SoundModule g_soundModule;

/* ====== METHODS ====== */
b32 SoundModule::StartUp()
{
    // Init array of sounds
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

