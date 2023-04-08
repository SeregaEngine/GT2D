#pragma once

#include "Engine/EngineModule.h"

struct Animation
{
    s32 row;
    s32 count;
    f32 frameDuration;
};

class AnimationModule final : public EngineModule
{
    Animation* m_aAnims;
    s32 m_usedAnims;

public:
    AnimationModule() : EngineModule("AnimationModule", CHANNEL_ANIMATION) {}

    void StartUp();
    void ShutDown();

    const Animation* DefineAnimation(const Animation& anim);
    forceinline void UndefineAnimations() { m_usedAnims = 0; }
};

inline AnimationModule g_animModule;
