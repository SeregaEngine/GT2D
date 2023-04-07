#pragma once

#include "Actor.h"

class Car final : public Entity
{
private:
    static constexpr i32f MAX_CAR_PLACES = 4;

private:
    Actor* m_aPlaces[MAX_CAR_PLACES];

public:
    Vector2 m_aPlacePositions[MAX_CAR_PLACES];

    Vector2 m_vMaxSpeed;
    Vector2 m_vAcceleration;

public:
    virtual void Init(const Vector2& vPosition, s32 width, s32 height, const GT_Texture* pTexture) override;
    virtual void Update(f32 dtTime) override;

    void PutActor(Actor* pActor, s32 place);
    void EjectActor(s32 place);

private:
    void HandleVelocity(f32 dtTime);
    void HandlePosition(f32 dtTime) { m_vPosition += m_vVelocity * dtTime; }
    void HandleAnimation(f32 dtTIme);
    void HandleActors();

    void HandleActor(s32 place);
};
