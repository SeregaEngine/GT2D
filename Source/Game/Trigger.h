#pragma once

#include <cstring>
#include "Game/Entity.h"

static constexpr i32f TRIGGER_STRSIZE = 32;

class Trigger final : public Entity
{
    char m_functionName[TRIGGER_STRSIZE];

public:
    Entity* m_pAttached;

public:
    virtual void Init(const Vector2& vPosition, s32 width, s32 height, const GT_Texture* pTexture) override;
    virtual void Update(f32 dtTime) override;
    virtual void Draw() override {} /** No drawing */

    void SetFunctionName(const char* functionName) { strncpy(m_functionName, functionName, TRIGGER_STRSIZE); }
    void Attach(Entity* pEntity) { m_pAttached = pEntity; }
};

