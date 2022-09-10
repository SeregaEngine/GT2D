/* TODO
 * - Maybe we can define hitbox in init without hitbox in args? We can use given width and height
 */

#ifndef ENTITY_H_
#define ENTITY_H_

/* ====== INCLUDES ====== */
#include "GraphicsModule.h"

/* ====== STRUCTURES ====== */
struct GT_Animation
{
    s32 row;
    s32 count;
    f32 frameDuration;
    SDL_RendererFlip flip;
};

class Entity
{
protected:
    Vec2 m_vPosition;
    Vec2 m_vVelocity;
    s32 m_width;
    s32 m_height;
    FRect m_hitBox; // Relative to entity position
    f32 m_angle;

    s32 m_animFrame;
    f32 m_animElapsed;
    const GT_Animation* m_pAnim;
    GT_Texture* m_pTexture;
public:
    virtual ~Entity() {}

    virtual void Init(const Vec2& vPosition, s32 width, s32 height,
                      const FRect& hitBox, GT_Texture* pTexture);
    virtual void Clean() {}

    virtual void Update(f32 dtTime) {}
    virtual void Draw();

    const Vec2& GetPosition() const { return m_vPosition; }
    const Vec2& GetVelocity() const { return m_vVelocity; }
    s32 GetWidth() const            { return m_width; }
    s32 GetHeight() const           { return m_height; }
    const FRect& GetHitBox() const  { return m_hitBox; }
    f32 GetAngle() const            { return m_angle; }

    void SetPosition(const Vec2& vPosition) { m_vPosition = vPosition; }
    void SetVelocity(const Vec2& vVelocity) { m_vVelocity = vVelocity; }
    void SetPosition(f32 x, f32 y) { m_vPosition.x = x; m_vPosition.y = y; }
    void SetVelocity(f32 x, f32 y) { m_vVelocity.x = x; m_vVelocity.y = y; }

    void SetWidth(s32 width)   { m_width = width; }
    void SetHeight(s32 height) { m_height = height; }
    void SetAngle(f32 angle)   { m_angle = angle; }

    void SetTexture(GT_Texture* pTexture) { m_pTexture = pTexture; }
};

/* ====== METHODS ====== */
inline void Entity::Init(const Vec2& vPosition, s32 width, s32 height, const FRect& hitBox, GT_Texture* pTexture) {
    m_vPosition = vPosition;
    m_vVelocity = { 0.0f, 0.0f };
    m_width = width;
    m_height = height;
    m_hitBox = hitBox;
    m_angle = 0.0f;

    m_animFrame = 0;
    m_animElapsed = 0.0f;
    m_pAnim = nullptr;

    m_pTexture = pTexture;
}

inline void Entity::Draw() {
    // TODO(sean) count w/2 and h/2 before drawing. Don't use HitBox because it can be different
    // m_width >> 1 == m_width/2
    SDL_Rect dstRect = { (s32)m_vPosition.x - (m_width >> 1),
                         (s32)m_vPosition.y - (m_height >> 1),
                         m_width, m_height };
    if (m_pAnim)
        g_graphicsModule.Draw(m_pTexture, m_pAnim->row, m_animFrame, &dstRect, m_angle, m_pAnim->flip);
    else
        g_graphicsModule.Draw(m_pTexture, 0, 0, &dstRect, m_angle);
}


#endif // ENTITY_H_