#include "Game/Game.h"
#include "Game/Car.h"

void Car::Init(const Vector2& vPosition, s32 width, s32 height, const Texture* pTexture)
{
    Entity::Init(vPosition, width, height, pTexture);
    m_type = ENTITY_TYPE_CAR;
    m_renderMode = RENDER_MODE_FOREGROUND;

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
    HandleVelocity(dtTime);
    HandlePosition(dtTime);
    HandleAnimation(dtTime);
    HandleActors();
}

void Car::PutActor(Actor* pActor, s32 place)
{
    // Check place and eject previous actor from it
    if (place < 0 || place >= 4)
    {
        place = 0;
    }
    if (m_aPlaces[place])
    {
        EjectActor(place);
    }

    // Place actor and set params
    m_aPlaces[place] = pActor;
    pActor->m_actorState = ACTOR_STATE_INCAR;
    pActor->m_renderMode = RENDER_MODE_FOREGROUND;
    HandleActor(place);
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

void Car::HandleVelocity(f32 dtTime)
{
    // Velocity
    m_vVelocity += m_vAcceleration * dtTime;

    // X
    if (fabsf(m_vVelocity.x) > fabsf(m_vMaxSpeed.x))
    {
        m_vVelocity.x = m_vMaxSpeed.x;
        if (m_vAcceleration.x < 0)
        {
            m_vVelocity.x = -m_vVelocity.x;
        }
    }

    // Y
    if (fabsf(m_vVelocity.y) > fabsf(m_vMaxSpeed.y))
    {
        m_vVelocity.y = m_vMaxSpeed.y;
        if (m_vAcceleration.y < 0)
        {
            m_vVelocity.y = -m_vVelocity.y;
        }
    }
}

void Car::HandleAnimation(f32 dtTime)
{
    if (!m_pAnim)
    {
        return;
    }

    // Update frames
    if (m_animElapsed >= m_pAnim->frameDuration)
    {
        m_animElapsed = 0;
        ++m_animFrame;

        if (m_animFrame >= m_pAnim->count)
        {
            m_animFrame = 0;
        }
    }

    // Update timer
    m_animElapsed += dtTime;
}

void Car::HandleActors()
{
    // Handle actors
    for (i32f i = 0; i < MAX_CAR_PLACES; ++i)
    {
        if (!m_aPlaces[i])
        {
            continue;
        }

        if (g_game.GetWorld().HasEntity(m_aPlaces[i]))
        {
            HandleActor(i);
        }
        else
        {
            m_aPlaces[i] = nullptr;
        }
    }
}

void Car::HandleActor(s32 place)
{
    // Position
    m_aPlaces[place]->m_vPosition = {
        m_vPosition.x + (m_aPlacePositions[place].x * (m_flip == SDL_FLIP_NONE ? 1 : -1)),
        m_vPosition.y + m_aPlacePositions[place].y
    };

    // zIndex
    if (m_flip == SDL_FLIP_NONE)
    {
        m_aPlaces[place]->m_zIndex = m_zIndex-1 - (place % 2 == 0 ? 1 : 0);
    }
    else
    {
        m_aPlaces[place]->m_zIndex = m_zIndex-1 - (place % 2 == 0 ? 0 : 1);
    }

    // Flip
    m_aPlaces[place]->m_flip = m_flip;
    m_aPlaces[place]->m_bLookRight = m_flip == SDL_FLIP_NONE ? true : false;
}
