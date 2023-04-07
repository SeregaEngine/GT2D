#pragma once

#include "Graphics/GraphicsModule.h"
#include "Animation/AnimationModule.h"

enum eEntityType
{
    ENTITY_TYPE_ENTITY = 0,
    ENTITY_TYPE_ACTOR,
    ENTITY_TYPE_CAR,
    ENTITY_TYPE_TRIGGER,
    ENTITY_TYPE_DIALOG,
};

class Entity
{
protected:
    s32 m_type;

public:
    Vector2 m_vPosition;
    Vector2 m_vVelocity;

    s32 m_width;
    s32 m_height;

    f32 m_angle;
    SDL_RendererFlip m_flip;

    FRect m_hitBox; /** Relative to entity position */

    s32 m_animFrame;
    f32 m_animElapsed;
    const Animation* m_pAnim;

    s32 m_renderMode;
    s32 m_zIndex;
    const Texture* m_pTexture;

    b32 m_bCollidable : 1;
    b32 m_bHUD : 1;

public:
    virtual ~Entity() = default;

    virtual void Init(const Vector2& vPosition, s32 width, s32 height, const Texture* pTexture);
    virtual void Clean() {}

    virtual void Update(f32 dtTime) {}
    virtual void Draw();

    s32 GetType() const { return m_type; }
};
