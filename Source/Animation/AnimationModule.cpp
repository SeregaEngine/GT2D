#include "Animation/AnimationModule.h"

static constexpr i32f MAX_ANIMATIONS = 256;

b32 AnimationModule::StartUp()
{
    m_aAnims = new Animation[MAX_ANIMATIONS];
    m_usedAnims = 0;

    AddNote(PR_NOTE, "Module started");
    return true;
}

void AnimationModule::ShutDown()
{
    delete[] m_aAnims;

    AddNote(PR_NOTE, "Module shut down");
}

const Animation* AnimationModule::DefineAnimation(const Animation& anim)
{
    if (m_usedAnims >= MAX_ANIMATIONS)
    {
        AddNote(PR_WARNING, "There're no free slot for animations");
        return nullptr;
    }

    m_aAnims[m_usedAnims] = anim;
    ++m_usedAnims;
    return &m_aAnims[m_usedAnims-1];
}
