#ifndef ENTITY_H_
#define ENTITY_H_

#include "GraphicsModule.h"

class Entity
{
protected:
    Vec2 m_vPosition;
    Vec2 m_vVelocity;
    s32 m_width, m_height;
    f32 m_angle;

    s32 m_animCol, m_animRow;
    GT_Texture* m_pTexture;
public:
    Entity() : m_angle(0.0f), m_animCol(0), m_animRow(0), m_pTexture(nullptr) {}
    virtual ~Entity() {}

    virtual void Update() {}
    virtual void Draw();

    const Vec2& GetPosition() const { return m_vPosition; }
    const Vec2& GetVelocity() const { return m_vVelocity; }
    s32 GetWidth() const { return m_width; }
    s32 GetHeight() const { return m_height; }
    f32 GetAngle() const { return m_angle; }

    void SetPosition(const Vec2& vPosition) { GTM::CopyVec2(&m_vPosition, &vPosition); }
    void SetVelocity(const Vec2& vVelocity) { GTM::CopyVec2(&m_vVelocity, &vVelocity); }
    void SetPosition(f32 x, f32 y) { m_vPosition.x = x; m_vPosition.y = y; }
    void SetVelocity(f32 x, f32 y) { m_vVelocity.x = x; m_vVelocity.y = y; }

    void SetWidth(s32 width) { m_width = width; }
    void SetHeight(s32 height) { m_height = height; }
    void SetAngle(f32 angle) { m_angle = angle; }

    void SetAnimCol(s32 col) { m_animCol = col; }
    void SetAnimRow(s32 row) { m_animRow = row; }
    void SetTexture(GT_Texture* pTexture) { m_pTexture = pTexture; }
};

inline void Entity::Draw()
{
    SDL_Rect dstRect = { (s32)m_vPosition.x, (s32)m_vPosition.y, m_width, m_height };
    g_graphicsModule.Draw(m_pTexture, m_animCol, m_animRow, &dstRect, m_angle);
}

#endif // ENTITY_H_