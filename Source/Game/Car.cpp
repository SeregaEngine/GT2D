/* ====== INCLUDES ====== */
#include "Car.h"

/* ====== METHODS ====== */
void Car::Init(const Vector2& vPosition, s32 width, s32 height, const GT_Texture* pTexture)
{
    Entity::Init(vPosition, width, height, pTexture);
    m_type = ENTITY_TYPE_CAR;
    m_renderMode = RENDER_MODE_FOREGROUND;

    // Defaults
    for (i32f i = 0; i < MAX_CAR_PLACES; ++i)
    {
        m_aPlaces[i] = nullptr;
        m_aPlacePositions[i] = { 0.0f, 0.0f };
    }

    m_vMaxSpeed = { 0.0f, 0.0f };
    m_vAcceleration = { 0.0f, 0.0f };
}

void Car::Update(f32 dtTime)
{

}

#if 0 // DEBUG(sean)
void Car::Draw()
{

}
#endif