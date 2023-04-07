#pragma once

#include "EngineModule.h"

struct GT_Animation
{
    s32 row;
    s32 count;
    f32 frameDuration;
};

class AnimationModule final : public EngineModule
{
    GT_Animation* m_aAnims;
    s32 m_usedAnims;

public:
    AnimationModule() : EngineModule("AnimationModule", CHANNEL_ANIMATION) {}

    b32 StartUp();
    void ShutDown();

    const GT_Animation* DefineAnimation(const GT_Animation& anim);
    void UndefineAnimations() { m_usedAnims = 0; }
};

inline AnimationModule g_animModule;
