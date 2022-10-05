/* TODO
 * - Make :1 flags from b32
 * - Delete useless functions for public class members
 */

#ifndef ENTITY_H_
#define ENTITY_H_

/* ====== INCLUDES ====== */
#include "GraphicsModule.h"
#include "AnimationModule.h"

/* ====== DEFINES ====== */
enum eEntityType
{
    ENTITY_TYPE_ENTITY = 0,
    ENTITY_TYPE_ACTOR,
    ENTITY_TYPE_CAR,
    ENTITY_TYPE_TRIGGER,
    ENTITY_TYPE_DIALOG,
};

/* ====== STRUCTURES ====== */
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

    FRect m_hitBox; // Relative to entity position
    b32 m_bCollidable;

    s32 m_animFrame;
    f32 m_animElapsed;
    const GT_Animation* m_pAnim;

    s32 m_renderMode;
    s32 m_zIndex;
    b32 m_bHUD;
    const GT_Texture* m_pTexture;
public:
    virtual ~Entity() {}

    virtual void Init(const Vector2& vPosition, s32 width, s32 height, const GT_Texture* pTexture);
    virtual void Clean() {}

    virtual void Update(f32 dtTime) {}
    virtual void Draw();

    s32 GetType() const { return m_type; }
};

#endif // ENTITY_H_