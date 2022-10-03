/* ====== INCLUDES ====== */
#include "Game.h"

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

    m_vMaxSpeed.Zero();
    m_vAcceleration.Zero();
}

void Car::Update(f32 dtTime)
{
    // Handle velocity
    m_vVelocity += m_vAcceleration;
    if (fabsf(m_vVelocity.x) > fabsf(m_vMaxSpeed.x) ||
        fabsf(m_vVelocity.y) > fabsf(m_vMaxSpeed.y))
        m_vVelocity = m_vMaxSpeed;

    // Handle actors
    for (i32f i = 0; i < MAX_CAR_PLACES; ++i)
    {
        if (m_aPlaces[i] && g_game.GetWorld().HasEntity(m_aPlaces[i]))
        {
            // TODO(sean) Handle zIndex
            HandleActorPosition(i);
        }
        else
        {
            m_aPlaces[i] = nullptr;
        }
    }
}

void Car::PutActor(Actor* pActor, s32 place)
{
    // Check place and eject previous actor from it
    if (place < 0 || place >= 4)
        place = 0;
    if (m_aPlaces[place])
        EjectActor(place);

    // Place actor and set params
    m_aPlaces[place] = pActor;
    pActor->m_actorState = ACTOR_STATE_INCAR;
    pActor->m_renderMode = RENDER_MODE_FOREGROUND;
    pActor->m_zIndex = m_zIndex - (place+1); // TODO(sean) But what if we flipped?

    // Handle their position
    HandleActorPosition(place);
}

void Car::EjectActor(s32 place)
{
    // Reset actor's params
    if (g_game.GetWorld().HasEntity(m_aPlaces[place]))
    {
        m_aPlaces[place]->m_actorState = ACTOR_STATE_IDLE;
        m_aPlaces[place]->m_renderMode = RENDER_MODE_DYNAMIC;
    }

    // Free place
    m_aPlaces[place] = nullptr;
}

void Car::HandleActorPosition(s32 place)
{
    m_aPlaces[place]->m_vPosition = m_vPosition += m_aPlacePositions[place];
}
