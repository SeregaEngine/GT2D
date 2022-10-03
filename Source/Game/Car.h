#ifndef CAR_H_
#define CAR_H_

/* ====== INCLUDES ====== */
#include "Actor.h"

/* ====== DEFINES ====== */
#define MAX_CAR_PLACES 4

/* ====== STRUCTURES ====== */
class Car final : public Entity
{
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
    void HandleActor(s32 place);
};

#endif // CAR_H_