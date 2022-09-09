#ifndef ENTITY_H_
#define ENTITY_H_

/* ====== INCLUDES ====== */
#include "GraphicsModule.h"

/* ====== STRUCTURES ====== */
struct HitBox
{
    // Relative to entity position
    f32 x1, y1;
    f32 x2, y2;

    HitBox()
        : x1(0.0f), y1(0.0f), x2(0.0f), y2(0.0f) {}
    HitBox(f32 _x1, f32 _y1, f32 _x2, f32 _y2)
        : x1(_x1), y1(_y1), x2(_x2), y2(_y2) {}
};

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
    s32 m_width, m_height;
    HitBox m_hitBox;
    f32 m_angle;

    s32 m_animFrame;
    f32 m_animElapsed;
    const GT_Animation* m_pAnim;
    GT_Texture* m_pTexture; // TODO(sean) maybe const?
public:
    Entity();
    virtual ~Entity() {}

    virtual void Init(const Vec2& vPosition, s32 width, s32 height,
                      const HitBox& hitBox, GT_Texture* pTexture);
    virtual void Clean() {}

    virtual void Update(f32 dtTime) {}
    virtual void Draw();

    const Vec2& GetPosition() const { return m_vPosition; }
    const Vec2& GetVelocity() const { return m_vVelocity; }
    s32 GetWidth() const { return m_width; }
    s32 GetHeight() const { return m_height; }
    const HitBox& GetHitBox() const { return m_hitBox; }
    f32 GetAngle() const { return m_angle; }

    void SetPosition(const Vec2& vPosition) { m_vPosition = vPosition; }
    void SetVelocity(const Vec2& vVelocity) { m_vVelocity = vVelocity; }
    void SetPosition(f32 x, f32 y) { m_vPosition.x = x; m_vPosition.y = y; }
    void SetVelocity(f32 x, f32 y) { m_vVelocity.x = x; m_vVelocity.y = y; }

    void SetWidth(s32 width) { m_width = width; }
    void SetHeight(s32 height) { m_height = height; }
    void SetAngle(f32 angle) { m_angle = angle; }

    void SetTexture(GT_Texture* pTexture) { m_pTexture = pTexture; }
};

inline Entity::Entity() :
    m_vPosition(-1000.0f, -1000.0f), m_vVelocity(0.0f, 0.0f),
    m_width(0), m_height(0),
    m_hitBox(), m_angle(0.0f),
    m_animFrame(0), m_animElapsed(0.0f), m_pAnim(nullptr), m_pTexture(nullptr) {}

inline void Entity::Draw() {
    // m_width >> 1 == m_width/2
    // TODO(sean) count w/2 and h/2 before drawing. Don't use HitBox because it can be different
    SDL_Rect dstRect = { (s32)m_vPosition.x - (m_width >> 1),
                         (s32)m_vPosition.y - (m_height >> 1),
                         m_width, m_height };
    if (m_pAnim)
        g_graphicsModule.Draw(m_pTexture, m_pAnim->row, m_animFrame, &dstRect, m_angle, m_pAnim->flip);
    else
        g_graphicsModule.Draw(m_pTexture, 0, 0, &dstRect, m_angle);
}

inline void Entity::Init(const Vec2& vPosition, s32 width, s32 height, const HitBox& hitBox, GT_Texture* pTexture) {
    m_vPosition = vPosition;
    m_width = width;
    m_height = height;
    m_hitBox = hitBox;
    m_pTexture = pTexture;
}

#endif // ENTITY_H_